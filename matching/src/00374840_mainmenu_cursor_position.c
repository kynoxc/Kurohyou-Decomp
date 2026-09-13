extern void *retail_0032827C(void *cse, int node_id);
extern int retail_00374F40(void *self, int visible_count);
extern void retail_0032BD80(void *node, int x, int y);

void match_00374840(void *self_ptr, int selection) {
    unsigned char *self = (unsigned char *)self_ptr;
    void *cursor = retail_0032827C(*(void **)(self + 0x90), 0xEE);
    int base_y = retail_00374F40(self, *(int *)(self + 0xA0));
    retail_0032BD80(cursor, 0, selection * 24 + base_y);
}
