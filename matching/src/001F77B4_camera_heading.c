extern const float retail_005F32A0;
extern float retail_004E0650(float y, float x);

float match_001F77B4(const void *ptr) {
    const unsigned char *p = (const unsigned char *)ptr;
    float rad_per_deg = retail_005F32A0 / 180.0f;
    float d18 = *(const float *)(p + 0x18) - *(const float *)(p + 0x0c);
    float d10 = *(const float *)(p + 0x10) - *(const float *)(p + 0x04);
    float angle = retail_004E0650(-(rad_per_deg * d18), rad_per_deg * d10);
    return angle * 57.2957916259765625f;
}
