extern void retail_003895E0(void *self, void *cse_slot, const char *motion, int node_id);
extern const char retail_00613988[];
extern const char retail_00613994[];

void match_003748A4(void *self_ptr, unsigned char out_motion) {
    unsigned char *self = (unsigned char *)self_ptr;
    if (!out_motion)
        retail_003895E0(self, self + 0x90, retail_00613988, 0xEE);
    else
        retail_003895E0(self, self + 0x90, retail_00613994, 0xEE);
}
