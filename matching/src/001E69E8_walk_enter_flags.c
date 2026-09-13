typedef struct RetailWalkOwner {
    unsigned char pad00[4];
    unsigned char *actor04;
    unsigned char *controller08;
} RetailWalkOwner;

void match_001E69E8(RetailWalkOwner *self)
{
    *(int *)(self->actor04 + 0x104) = 1;
    self->controller08[0x60] = 0;
}
