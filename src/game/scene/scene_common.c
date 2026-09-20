/* Shared scene helpers called by SceneTitleMainmenu. TU boundaries provisional. */
#include "../../../include/scene_common.h"
extern void *retail_0032827C(void *,int);
extern SceneU32 retail_003E4710(const char *);
extern void retail_00328330(void *,SceneU16,SceneU32);
extern void retail_0032C014(void *,SceneU8);
extern void retail_0032BC3C(void *,float);
extern void retail_0032BD80(void *,int,int);
extern int retail_0032BB54(void *);
extern int retail_0032BB7C(void *);
extern SceneU32 retail_0032817C(void *);
extern void *retail_00328264(void *,SceneU16);
extern void *retail_0031010C(void);
extern void retail_00311F78(void *,SceneU32);
extern char retail_00686AA0[];
extern void retail_003D34F4(void *);
extern void *retail_004088B0(void);
extern void retail_00408F58(void *,int);
typedef struct SceneRenderState { SceneU8 unknown00[0xc70];float stepc70; } SceneRenderState;
typedef struct SceneTiming { SceneU32 unknown00[2];float step08; } SceneTiming;
extern SceneRenderState retail_006BB850;
extern SceneTiming *retail_0023FF88(void);
extern void retail_003F86E0(SceneRenderState *,SceneU32);
extern void retail_003F81A8(SceneRenderState *,int,int,int);
extern void retail_003F812C(SceneRenderState *,int);
extern void retail_003F800C(SceneRenderState *,int,int);
extern SceneU32 *retail_003DDD88(SceneU32 *,SceneU32);
extern void retail_003F86C4(SceneRenderState *,SceneU32 *);
extern void retail_003F8708(SceneRenderState *,int);
extern SceneU32 retail_00389884(SceneCommon *,SceneU16 *,SceneU32,int,SceneU32,SceneU16);
extern void *retail_005C2B0C(void *,const void *,SceneU32);

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00389338
void match_00389338(SceneCommon *self,SceneU32 flags){
 if(self){self->vtable1c=retail_00686AA0;if(flags&1)retail_003D34F4(self);}
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0038936C
void match_0038936C(SceneCommon *self){
 SceneU32 color;
 retail_00408F58(retail_004088B0(),0);
 retail_003F86E0(&retail_006BB850,0xffff);
 retail_003F81A8(&retail_006BB850,6,0,255);
 retail_003F812C(&retail_006BB850,0);
 retail_003F800C(&retail_006BB850,0,1);
 retail_003F86C4(&retail_006BB850,retail_003DDD88(&color,0xff000000));
 retail_003F8708(&retail_006BB850,7);
 retail_006BB850.stepc70=retail_0023FF88()->step08;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003899F4
int match_003899F4(SceneCommon *self,SceneU16 *output,SceneU32 first,SceneU32 second,int capacity,SceneU32 digits){
 SceneU16 separator[3];
 int written=retail_00389884(self,output,first,capacity,digits,0x30);
 output+=written;
 separator[0]=0x20;separator[1]=0x2f;separator[2]=0x20;
 capacity-=written;
 retail_005C2B0C(output,separator,6);
 written+=3;
 return written+retail_00389884(self,output+3,second,capacity-3,digits,0x30);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00389414
int match_00389414(SceneCommon *self,void **cse,const SceneU32 *nodes,SceneU32 count) {
 SceneU32 i;
 for(i=0;i<count;++i){
  void *node=retail_0032827C(*cse,(SceneU16)nodes[i]);
  if(node){if(!retail_0032BB54(node))return 0;}
 }
 return 1;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003894B0
int match_003894B0(SceneCommon *self,void **cse,int id) {
 int result=1;void *node=retail_0032827C(*cse,(SceneU16)id);
 if(node)result=retail_0032BB7C(node);
 return result;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003894F8
void match_003894F8(SceneCommon *self,void **cse,float frame) {
 SceneU32 i;
 for(i=0;i<retail_0032817C(*cse);++i){
  void *node=retail_00328264(*cse,(SceneU16)i);
  if(node)retail_0032BC3C(node,frame);
 }
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00389574
void match_00389574(SceneCommon *self,void **cse,int id,float frame) {
 void *node=retail_0032827C(*cse,(SceneU16)id);
 if(node)retail_0032BC3C(node,frame);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003895B4
void match_003895B4(SceneCommon *self,void **cse,int id) {
 retail_0032BC3C(retail_0032827C(*cse,(SceneU16)id),0.0f);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003895E0
void match_003895E0(SceneCommon *self,void **cse,const char *motion,int id) {
 SceneU32 hash=retail_003E4710(motion);
 retail_00328330(*cse,id,hash);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00389624
void match_00389624(SceneCommon *self,void **cse,int id,SceneU8 hidden) {
 retail_0032C014(retail_0032827C(*cse,(SceneU16)id),hidden);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0038965C
void match_0038965C(SceneCommon *self,void **cse,int id,int x,int y) {
 retail_0032BD80(retail_0032827C(*cse,(SceneU16)id),x,y);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003896A4
int match_003896A4(SceneCommon *self,int current,int delta,int count) {
 int result;
 if(delta<=0){
  if(delta<0){result=delta+current;if(result<0)result=count+current+delta;}
  else result=current;
 }else result=(delta+current)%count;
 return result;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003896F0
void match_003896F0(SceneCommon *self,int state) {
 self->current08=-1;self->requested0c=state;
 self->useFade18=0;self->leaving19=0;
 {SceneFade *fade=self->fade00;SceneU8 entering=0;
 if(fade->current!=0&&*(volatile int*)&fade->current!=6)entering=1;
 self->entering1a=entering;}
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00389730
void match_00389730(SceneCommon *self,int state,SceneU8 fade,int delay) {
 self->useFade18=fade;self->delay14=delay;
 if(!delay){
  if(fade){SceneFade *f=self->fade00;int previous=f->current;f->current=1;f->previous=previous;}
  else{int previous=self->current08;self->current08=state;self->previous10=previous;}
 }
 self->requested0c=state;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00389774
int match_00389774(SceneCommon *self) {
 if(self->current08!=self->requested0c)return 1;
 if(self->leaving19||self->entering1a){
  SceneFade *fade=self->fade00;
  if(fade->current!=0&&*(volatile int*)&fade->current!=6)return 1;
  self->leaving19=0;self->entering1a=0;
 }
 return 0;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003897E4
int match_003897E4(SceneCommon *self) {
 int current=self->current08,requested=self->requested0c;
 if(current!=requested){
  if(self->delay14){
   if(--self->delay14==0&&self->useFade18){
    SceneFade *fade=self->fade00;int previous=fade->current;fade->current=1;fade->previous=previous;
   }
   return 0;
  }
  if(!self->useFade18){self->previous10=current;self->current08=requested;return 1;}
  if(self->fade00->current>2){self->previous10=current;self->current08=requested;return self->leaving19=1;}
 }
 return 0;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00389AB4
void match_00389AB4(SceneCommon *self,SceneU32 id) {
 retail_00311F78((SceneU8*)retail_0031010C()+0x134,id);
}
#endif
