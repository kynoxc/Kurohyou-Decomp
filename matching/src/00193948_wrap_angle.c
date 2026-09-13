extern const float retail_005E6E48;
extern const float retail_005E6E4C;

float match_00193948(float value)
{
    while (retail_005E6E4C <= value)
        value -= retail_005E6E4C;
    while (!(retail_005E6E48 <= value))
        value += retail_005E6E4C;
    return value;
}
