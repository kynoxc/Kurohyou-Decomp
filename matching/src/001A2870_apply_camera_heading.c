extern float retail_001F77B4(const void *ptr);
extern int retail_001C593C(float current, float target, float tolerance);

void match_001A2870(void *player_ptr, void *camera_ptr) {
    unsigned char *player = (unsigned char *)player_ptr;
    unsigned char *camera = (unsigned char *)camera_ptr;
    if (camera == 0)
        return;
    if (player == 0)
        return;

    float heading = retail_001F77B4(camera + 0x2a0);
    float angle = *(float *)(player + 0x1a0);
    if (*(unsigned char *)(player + 0x1bc))
        *(float *)(player + 0x18c) = heading;
    if (!retail_001C593C(angle, *(float *)(player + 0x1a4), 40.0f)) {
        *(float *)(player + 0x18c) = heading;
        *(float *)(player + 0x1a4) = angle;
    }
    *(float *)(player + 0x190) = heading;
}
