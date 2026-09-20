/* Node operations reached by title/menu rendering. Class/TU grouping is provisional. */
#include "../../../include/cse_node.h"
extern int retail_0032F0E8(CseAnimator *);
extern int retail_0032BB54(CseNode *);
extern int retail_0032BB7C(CseNode *);
extern void retail_0032BC3C(CseNode *,float);
extern void retail_0032BCA0(CseNode *,float);
extern void retail_0032F194(CseAnimator *,float);
extern void retail_003D00EC(float *);
extern void *retail_003DDD88(void *,CseU32);
extern CseU32 retail_003DDDCC(const CseU32 *);
extern void retail_0032BE7C(CseNode *,const CseU32 *);
extern void retail_0032BDCC(CseNode *,const CseU32 *);
extern void retail_0032BF84(CseNode *,const CseU32 *);
extern void retail_0032BED4(CseNode *,const CseU32 *);
extern void retail_0032C0C4(CseNode *,CseU8);
extern void retail_0032C014(CseNode *,CseU8);

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BB54
int match_0032BB54(CseNode *self) {
 int result=1;
 if(self->animator40)result=retail_0032F0E8(self->animator40);
 return result;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BB7C
int match_0032BB7C(CseNode *self) {
 CseU32 i;
 int result;
 if(!retail_0032BB54(self))result=0;
 else{
  for(i=0;i<(CseU32)(self->end04-self->begin00);++i)
   if(!retail_0032BB7C(self->begin00[i].node))return 0;
  result=1;
 }
 return result;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BC3C
void match_0032BC3C(CseNode *self,float frame) {
 CseNodeRef *child;
 retail_0032BCA0(self,frame);
 for(child=self->begin00;child!=self->end04;++child)retail_0032BC3C(child->node,frame);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BCA0
void match_0032BCA0(CseNode *self,float frame) {
 CseVirtualEntry *entry=&self->vtablea8[12];
 self->pose0c=*entry->fn.pose((CseU8*)self+entry->delta);
 if(self->animator40){
  retail_0032F194(self->animator40,frame);
  entry=&self->vtablea8[4];entry->fn.update((CseU8*)self+entry->delta,0.0f);
 }
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BD50
void match_0032BD50(CseNode *self){retail_003D00EC(self->matrix50);}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BD6C
void match_0032BD6C(CseNode *self,float x,float y){self->scale94=x;self->scale98=y;}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BD78
void match_0032BD78(CseNode *self,float rotation){self->rotation90=rotation;}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BD80
void match_0032BD80(CseNode *self,int x,int y){self->x9c=(float)x;self->ya0=(float)y;}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BD9C
void match_0032BD9C(CseNode *self,void *color,int index){
 CseU32 *colors=(CseU32*)((CseU8*)self+0x24);
 retail_003DDD88(color,colors[index]);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BDCC
void match_0032BDCC(CseNode *self,const CseU32 *color) {
 CseU32 i;
 retail_0032BE7C(self,color);
 for(i=0;i<(CseU32)(self->end04-self->begin00);++i)retail_0032BDCC(self->begin00[i].node,color);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BE7C
void match_0032BE7C(CseNode *self,const CseU32 *color) {
 CseU32 i;
 for(i=0;i<4;++i)self->pose0c.colors18[i]=retail_003DDDCC(color);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BED4
void match_0032BED4(CseNode *self,const CseU32 *colors) {
 CseU32 i;
 retail_0032BF84(self,colors);
 for(i=0;i<(CseU32)(self->end04-self->begin00);++i)retail_0032BED4(self->begin00[i].node,colors);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BF84
void match_0032BF84(CseNode *self,const CseU32 *colors) {
 CseU32 i;
 for(i=0;i<4;++i)self->pose0c.colors18[i]=retail_003DDDCC(&colors[i]);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032BFE4
CseU8 match_0032BFE4(CseNode *self) {
 if(self->flagsa4&2)return self->flagsa4&1;
 return (self->pose0c.visibility2e&0xffff)!=0;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032C014
void match_0032C014(CseNode *self,CseU8 hidden) {
 CseU32 i;
 retail_0032C0C4(self,hidden);
 for(i=0;i<(CseU32)(self->end04-self->begin00);++i)retail_0032C014(self->begin00[i].node,hidden);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032C0C4
void match_0032C0C4(CseNode *self,CseU8 hidden) {
 self->flagsa4=(self->flagsa4&~1)|(hidden&1);
 self->flagsa4|=2;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032C4EC
CseU16 match_0032C4EC(CseNode *self){CseU16 id=0;if(self->animator40)id=self->animator40->id04;return id;}
#endif

/* Independent virtual entry, referenced at retail 0x00685DBC. */
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0032C504
void match_0032C504(void){}
#endif
