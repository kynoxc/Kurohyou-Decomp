typedef signed int s32;
typedef struct{unsigned char p[0x10c];s32 id;}A;
typedef struct{A*a;}H;
extern s32 retail_001E2858(s32);
s32 match_001E2810(H*self){s32 k=retail_001E2858(self->a->id),r;if(k==0)goto F;if(k==1)goto F;if(k!=4)goto T;F:r=0;goto E;T:__asm__ volatile("");r=1;E:return r;}
