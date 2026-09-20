"""Independent expected words for MIPS REL addends and rejection cases."""
import struct
import unittest
from tools.kurohyou.matching import patch_text_relocations


def object_file(words, relocs, local_symbol=False):
    header = bytearray(52)
    header[:7] = b'\x7fELF\x01\x01\x01'
    struct.pack_into('<HHI', header, 16, 1, 8, 1)
    struct.pack_into('<HHHH', header, 40, 52, 0, 0, 40)
    struct.pack_into('<HH', header, 48, 5, 0)
    text = struct.pack('<' + 'I' * len(words), *words)
    symbols = bytes(16) + struct.pack('<IIIBBH', 1, 4 if local_symbol else 0,
                                      0, 0x10, 0, 1 if local_symbol else 0)
    strings = b'\0external\0'
    rel = b''.join(struct.pack('<II', offset, (1 << 8) | kind) for offset, kind in relocs)
    sections = [(0,) * 10]
    data = header
    for typ, flags, payload, link, info, entsize in [
        (1, 6, text, 0, 0, 0), (2, 0, symbols, 3, 0, 16),
        (3, 0, strings, 0, 0, 0), (9, 0, rel, 2, 1, 8),
    ]:
        while len(data) % 4:
            data.append(0)
        sections.append((0, typ, flags, 0, len(data), len(payload), link, info, 4, entsize))
        data.extend(payload)
    while len(data) % 4:
        data.append(0)
    struct.pack_into('<I', data, 32, len(data))
    for section in sections:
        data.extend(struct.pack('<10I', *section))
    return bytes(data)


class RelocationTests(unittest.TestCase):
    def resolve(self, words, relocs, target=0x12348000):
        result, records = patch_text_relocations(object_file(words, relocs), {'external': target})
        return list(struct.unpack('<' + 'I' * len(words), result)), records

    def test_hi_lo_signed_addend_and_carry(self):
        words, records = self.resolve([0x3c080001, 0x2508fffc], [(0, 5), (4, 6)])
        self.assertEqual(words, [0x3c081235, 0x25087ffc])
        self.assertTrue(all(r['resolved'] for r in records))

    def test_multiple_high_relocations_share_low(self):
        words, records = self.resolve([0x3c080000, 0x3c090001, 0x2508fffc], [(0, 5), (4, 5), (8, 6)])
        self.assertEqual(words, [0x3c081234, 0x3c091235, 0x25087ffc])
        self.assertTrue(all(r['resolved'] for r in records))

    def test_jump_preserves_encoded_addend(self):
        words, records = self.resolve([0x0c000003], [(0, 4)], 0x1000)
        self.assertEqual(words, [0x0c000403])
        self.assertTrue(records[0]['resolved'])

    def test_local_symbol_value_and_jump_addend(self):
        result, records = patch_text_relocations(object_file([0x0c000002], [(0, 4)], True), {}, 0x1000)
        self.assertEqual(struct.unpack('<I', result)[0], 0x0c000403)
        self.assertTrue(records[0]['resolved'])

    def test_full_word_addend(self):
        words, _ = self.resolve([5], [(0, 2)], 0x1000)
        self.assertEqual(words, [0x1005])

    def test_missing_low_rejected(self):
        _, records = self.resolve([0x3c080001], [(0, 5)])
        self.assertFalse(records[0]['resolved'])

    def test_unknown_symbol_rejected(self):
        _, records = patch_text_relocations(object_file([0x0c000000], [(0, 4)]), {})
        self.assertFalse(records[0]['resolved'])

    def test_wrong_jump_region_rejected(self):
        _, records = self.resolve([0x0c000000], [(0, 4)], 0x80001000)
        self.assertFalse(records[0]['resolved'])


if __name__ == '__main__':
    unittest.main()
