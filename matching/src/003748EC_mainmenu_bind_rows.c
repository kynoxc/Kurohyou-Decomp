extern void *retail_0032827C(void *cse,int node_id);
extern void *retail_00251364(void);
extern void *retail_00251440(void *ctx,unsigned int string_id);
extern void retail_00333250(void *node,void *text);
extern const unsigned int retail_00613770[];
typedef struct X{unsigned char p[0x90];void*cse90;}X;
void match_003748EC(X*self,int count,const unsigned int*ids){int i=0;const unsigned int*nodes=retail_00613770;__asm__ volatile("" : "+r"(count)); __asm__ volatile("" : "+r"(self));const unsigned int*sid=ids;while(i<7&&i<count){
 void*node=retail_0032827C(self->cse90,(int)(*nodes&0xffffu));
 void*ctx=retail_00251364();
 void*text=retail_00251440(ctx,*sid);
 retail_00333250(node,text);
 ++i;++nodes;++sid;
}}
