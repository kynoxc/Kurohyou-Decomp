extern float retail_001C58E4(float v);
extern int retail_001C59D0(float lhs, float rhs);

int match_001C593C(float current, float target, float tolerance) {
    float half = tolerance * 0.5f;
    float lo = retail_001C58E4(current - half);
    float hi = retail_001C58E4(current + half);
    if (retail_001C59D0(lo, target) < 0)
        return 0;
    if (retail_001C59D0(hi, target) > 0)
        return 0;
    return 1;
}
