extern const float retail_005E6E30;
extern float retail_004E07B0(float radians);
extern float retail_004E0828(float radians);

void match_001936F0(const float *angle, float *out_x, float *out_z,
                    float speed, float offset_degrees) {
    if (out_x != 0) {
        float radians = (retail_005E6E30 / 180.0f) * (*angle + offset_degrees);
        *out_x = speed * retail_004E07B0(radians);
    }
    if (out_z != 0) {
        float radians = (retail_005E6E30 / 180.0f) * (*angle + offset_degrees);
        *out_z = -(speed * retail_004E0828(radians));
    }
}
