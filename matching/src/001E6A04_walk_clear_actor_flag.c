typedef struct RetailWalkOwner {
    unsigned char pad00[4];
    unsigned char *actor04;
} RetailWalkOwner;

void match_001E6A04(RetailWalkOwner *self)
{
    self->actor04[0x1A8] = 0;
}
