typedef struct RetailAngleScalar {
    float current00;
    float target04;
    float step08;
    int ticks0c;
    void *vtable10;
} RetailAngleScalar;

extern char retail_00681368;
extern void retail_003D34F4(void *ptr);

void match_001935E8(RetailAngleScalar *self, unsigned int flags)
{
    if (self != 0) {
        self->vtable10 = &retail_00681368;
        if (flags & 1)
            retail_003D34F4(self);
    }
}
