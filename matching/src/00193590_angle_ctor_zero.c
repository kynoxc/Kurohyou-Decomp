typedef struct RetailAngleScalar {
    float current00;
    float target04;
    float step08;
    int ticks0c;
    void *vtable10;
} RetailAngleScalar;

extern char retail_00681368;
extern const float retail_005E6E50;

RetailAngleScalar *match_00193590(RetailAngleScalar *self)
{
    self->vtable10 = &retail_00681368;
    self->ticks0c = 0;
    self->current00 = retail_005E6E50;
    self->target04 = retail_005E6E50;
    self->step08 = retail_005E6E50;
    return self;
}
