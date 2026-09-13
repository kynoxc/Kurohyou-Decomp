typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef struct PlayerStateFactoryMatch {
    volatile u8 dirty00;
    u8 _pad01[3];
    volatile s32 current04;
} PlayerStateFactoryMatch;

void match_001E63D8(PlayerStateFactoryMatch *self, s32 next)
{
    s32 current = self->current04;
    if (current != next) {
        self->current04 = next;
        self->dirty00 = 1;
    }
}
