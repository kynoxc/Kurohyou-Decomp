typedef struct RetailAngleScalar {
    float current00;
    float target04;
    float step08;
    int ticks0c;
    void *vtable10;
} RetailAngleScalar;

extern char retail_00681368;
extern const float retail_005E6E50;

RetailAngleScalar *match_001935BC(RetailAngleScalar *self, float value)
{
    self->vtable10 = &retail_00681368;
    self->current00 = value;
    self->ticks0c = 0;
    self->target04 = retail_005E6E50;
    self->step08 = retail_005E6E50;
    return self;
}
