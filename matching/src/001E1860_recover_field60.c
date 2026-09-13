typedef signed int s32;
typedef struct{unsigned char p[0x60];unsigned char f;}C;
typedef struct{unsigned char p[0x28];void*v;}R;
extern R*retail_0023FF88(void);
extern s32 retail_0024B578(void*);
s32 match_001E1860(C*self){R*r=retail_0023FF88();s32 p=retail_0024B578(r->v);if(p<31)return 0;if(!self->f)return 0;self->f=0;return 1;}
