typedef struct RetailAngleScalar {
    float current00;
    float target04;
    float step08;
    int ticks0c;
} RetailAngleScalar;

extern const float retail_005E6E48;
extern const float retail_005E6E4C;
extern const float retail_005E6E54;

void match_0019363C(RetailAngleScalar *self)
{
    int ticks = self->ticks0c;
    if (ticks != 0) {
        float current = self->current00 + self->step08;
        ticks -= 1;
        self->ticks0c = ticks;
        self->current00 = current;
        if (ticks <= 0) {
            self->step08 = retail_005E6E54;
            self->ticks0c = 0;
            self->current00 = self->target04;
        }
    }

    while (!(self->current00 < retail_005E6E4C))
        self->current00 -= retail_005E6E4C;
    while (self->current00 < retail_005E6E48)
        self->current00 += retail_005E6E4C;
}
