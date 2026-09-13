/* NPJH50333 retail 0x001C57E0..0x001C57FF. */
float match_001C57E0(float x0, float y0, float x1, float y1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    float sum = dx * dx + dy * dy;
    return __builtin_sqrtf(sum);
}
