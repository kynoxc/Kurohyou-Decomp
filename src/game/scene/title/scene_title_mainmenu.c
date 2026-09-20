/* SceneTitleMainmenu: function-level matching; original TU boundaries remain evidence-based candidates. */
#include "../../../../include/title_mainmenu.h"
extern const u32 retail_00613754[], retail_0061378C[];
extern void retail_00389624(void *,void *,u32,int);
extern void *retail_0032827C(void *,int);
extern int retail_00374F40(void *,int);
extern void retail_0032BD80(void *,int,int);
extern void retail_003732F0(TitleMainmenu *);
extern void retail_00373524(TitleMainmenu *);
extern void retail_00373674(TitleMainmenu *);
extern void retail_00373788(TitleMainmenu *);
extern void retail_0037388C(TitleMainmenu *);
extern void retail_00373950(TitleMainmenu *);
extern void retail_00373A24(TitleMainmenu *);
extern void retail_00373B80(TitleMainmenu *);
extern void retail_00373D1C(TitleMainmenu *);
extern void retail_00373E74(TitleMainmenu *);
extern void retail_00373EE0(TitleMainmenu *);
extern void retail_00373FBC(TitleMainmenu *);
extern void retail_0037410C(TitleMainmenu *);
extern void retail_003742F0(TitleMainmenu *);
extern void retail_003744FC(TitleMainmenu *);
extern void retail_003745C0(TitleMainmenu *);
extern void retail_0037468C(TitleMainmenu *);
extern void retail_00374758(TitleMainmenu *);

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0037311C
void match_0037311C(TitleMainmenu *self) {
    u32 i;
    for(i=0;i<7;++i)retail_00389624(self,&self->cse90,retail_0061378C[i],1);
    retail_00389624(self,&self->cse90,0xEE,0);
    switch(self->state08){
    case 0: retail_003732F0(self); break;
    case 1: retail_00373524(self); break;
    case 2: retail_00373674(self); break;
    case 3: retail_00373788(self); break;
    case 4: retail_0037388C(self); break;
    case 5: break;
    case 6: retail_00373950(self); break;
    case 7: retail_00373A24(self); break;
    case 8: retail_00373B80(self); break;
    case 9: retail_00373D1C(self); break;
    case 10: retail_00373E74(self); break;
    case 11: retail_00373EE0(self); break;
    case 12: retail_00373FBC(self); break;
    case 13: retail_0037410C(self); break;
    case 14: retail_003742F0(self); break;
    case 15: retail_003744FC(self); break;
    case 16: retail_003745C0(self); break;
    case 17: retail_0037468C(self); break;
    case 18: retail_00374758(self); break;
    default:break;

    }
    self->transition98=0;
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003749A0
void match_003749A0(TitleMainmenu *self,u32 count) {
    const u32 *rows=retail_00613754;
    const u32 *aux=retail_0061378C;
    u32 i=0;
    for(;i<7;++i,++rows,++aux){
        if(i>=count)retail_00389624(self,&self->cse90,*rows,1);
        else {
            void *node;
            int y;
            retail_00389624(self,&self->cse90,*rows,0);
            node=retail_0032827C(self->cse90,*rows&0xFFFF);
            y=retail_00374F40(self,self->visibleCountA0);
            retail_0032BD80(node,0,y);
            node=retail_0032827C(self->cse90,*aux&0xFFFF);
            y=retail_00374F40(self,self->visibleCountA0);
            retail_0032BD80(node,0,y);
        }
    }
}
#endif

extern MenuGlobals *retail_0023FF88(void);
extern int retail_00246000(void *,int);
extern int retail_00374C70(TitleMainmenu *);
extern int retail_00374DA8(TitleMainmenu *);
extern void retail_002F90A0(void *,int,int);
extern void retail_0036573C(void *,int);

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374C48
int match_00374C48(TitleMainmenu *self) { return retail_0023FF88()->game20->storyMode0c==0; }
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374C70
int match_00374C70(TitleMainmenu *self) { return retail_0023FF88()->game20->extra08!=0; }
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374C98
int match_00374C98(TitleMainmenu *self) { return retail_0023FF88()->game20->storyMode0c==3; }
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374CC4
int match_00374CC4(TitleMainmenu *self) { int count=7; if(!retail_00374C70(self))count=6; return count; }
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374CF8
int match_00374CF8(TitleMainmenu *self) {
 int result=0;
 if(retail_00374C70(self) && retail_00246000(retail_0023FF88()->unlocks80,3))result=1;
 if(retail_00374C70(self) && retail_00246000(retail_0023FF88()->unlocks80,4))result=1;
 if(retail_00374C70(self) && retail_00374DA8(self))result=1;
 return result;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374DA8
int match_00374DA8(TitleMainmenu *self) {
 void *unlocks=retail_0023FF88()->unlocks80;
 int result=0;
 if(retail_00246000(unlocks,10))result=1;
 if(retail_00246000(unlocks,11) && retail_00246000(unlocks,7))result=1;
 if(retail_00246000(unlocks,12) && retail_00246000(unlocks,8))result=1;
 return result;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373E74
void match_00373E74(TitleMainmenu *self) {
 MenuConnection *connection;
 retail_00389624(self,&self->cse90,0xee,1);
 retail_002F90A0(self->scene04,8,0);
 retail_0036573C(self->parent54,0);
 connection=self->connection20;
 connection->state10=4;connection->requested14=1;
 connection->field19=0;connection->field1a=1;
}
#endif

extern void *retail_00251364(void);
extern u32 retail_003E4710(const char *);
extern void *retail_00251440(void *,u32);
extern void retail_0036A22C(TitleMainmenu *,u32);
extern void retail_0036A29C(TitleMainmenu *,void *);
extern void retail_00374840(TitleMainmenu *,int);
extern void retail_003748A4(TitleMainmenu *,u8);
extern void retail_003748EC(TitleMainmenu *,int,const u32 *);
extern void retail_003749A0(TitleMainmenu *,u32);
extern int retail_003693E8(void);
extern void retail_002E0A6C(MenuSelector *,int,int,int,int,int);
extern void retail_002E0C30(MenuSelector *,int,int);
extern void retail_002E2CB0(void *,int,int,void *,void *,void *,int);
extern void retail_002E2E38(void *,int);
extern void retail_002F92A4(void *,int);
extern void retail_002F995C(void *);
extern const u32 retail_00613870[], retail_0061387C[];
extern const char retail_006138C8[];
extern const u32 retail_00613888[], retail_00613890[];
extern const char retail_006138D4[];
extern const char retail_006138E0[];
extern const char retail_006138E0[];
extern const char retail_00613934[];
extern const char retail_00613964[];
extern const char retail_00613970[];
extern const char retail_0061397C[];
extern int retail_00374CC4(TitleMainmenu *);
extern int retail_00374C48(TitleMainmenu *);
extern int retail_00374CF8(TitleMainmenu *);
extern int retail_0024ADDC(void *);
extern int retail_0024B214(void *,int);
extern int retail_0024CB40(void *);
extern const u32 retail_00613798, retail_0061379C, retail_006137A4;
extern const u32 retail_0061381C[], retail_006137F0[], retail_00613838[], retail_0061380C[];
extern const char retail_006138B0[], retail_006138BC[], retail_006138EC[], retail_006138F8[], retail_00613904[];

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003732F0
void match_003732F0(TitleMainmenu *self) {
 void **cse=&self->cse90;
 void *ctx,*text,*progress;u32 key;
 self->visibleCountA0=retail_00374CC4(self);
 retail_00389624(self,cse,0xee,0);
 retail_003748A4(self,0);
 retail_00374840(self,self->mainSelector34->displayed08);
 retail_003748EC(self,7,retail_0061381C);
 retail_0036A22C(self,retail_006137F0[self->mainSelector34->current00]);
 ctx=retail_00251364();key=retail_003E4710(retail_006138B0);text=retail_00251440(ctx,key);
 retail_0036A29C(self,text);
 retail_003749A0(self,retail_00374CC4(self));
 progress=retail_0023FF88()->progress28;
 if(retail_0024ADDC(progress) || retail_0024B214(progress,0) || retail_0024B214(progress,1) || retail_0024CB40(progress))
    retail_00389624(self,cse,retail_00613798,0);
 if((retail_0023FF88()->game20->flags06&0xf0)==0x10)
    retail_00389624(self,cse,retail_0061379C,0);
 if(retail_00374C48(self) && retail_00246000(retail_0023FF88()->unlocks80,5) && retail_00246000(retail_0023FF88()->unlocks80,6))
    retail_00389624(self,cse,retail_0061378C[0],0);
 if(retail_00374CF8(self))retail_00389624(self,cse,retail_006137A4,0);
 retail_002F90A0(self->scene04,8,1);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373524
void match_00373524(TitleMainmenu *self) {
 int count=4;void *ctx,*text;u32 key;
 if(retail_00246000(retail_0023FF88()->unlocks80,5)){
 if(retail_00246000(retail_0023FF88()->unlocks80,6))retail_00389624(self,&self->cse90,retail_0061378C[3],0);
 }else count=3;
 self->visibleCountA0=count;
 retail_002E0A6C(self->listSelector3c,count,count,0,1,0);
 retail_002E0C30(self->listSelector3c,1,-1);
 retail_003748A4(self,0);
 retail_00374840(self,self->listSelector3c->current00);
 retail_003748EC(self,4,retail_00613838);
 retail_0036A22C(self,retail_0061380C[self->listSelector3c->current00]);
 ctx=retail_00251364();key=retail_003E4710(retail_006138BC);text=retail_00251440(ctx,key);
 retail_0036A29C(self,text);
 retail_003749A0(self,count);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373950
void match_00373950(TitleMainmenu *self) {
 void *dialog=self->dialog24,*ctx,*message,*yes,*no;u32 key;
 ctx=retail_00251364();key=retail_003E4710(retail_006138EC);message=retail_00251440(ctx,key);
 ctx=retail_00251364();key=retail_003E4710(retail_006138F8);yes=retail_00251440(ctx,key);
 ctx=retail_00251364();key=retail_003E4710(retail_00613904);no=retail_00251440(ctx,key);
 retail_002E2CB0(dialog,0,1,message,yes,no,0);
 self->dialog99=1;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373674
void match_00373674(TitleMainmenu *self) {
 void *ctx,*text;u32 key;
 self->visibleCountA0=3;
 retail_002E0A6C(self->listSelector3c,3,3,0,1,0);
 if(self->transition98){ MenuSelector *selector=self->listSelector3c;int saved=retail_003693E8();retail_002E0C30(selector,saved,-1);}
 retail_003748A4(self,0);
 retail_00374840(self,self->listSelector3c->displayed08);
 retail_003748EC(self,3,retail_00613870);
 retail_0036A22C(self,retail_0061387C[self->listSelector3c->current00]);
 retail_002F90A0(self->scene04,8,1);

 retail_003749A0(self,3);
 ctx=retail_00251364();key=retail_003E4710(retail_006138C8);text=retail_00251440(ctx,key);
 retail_0036A29C(self,text);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373788
void match_00373788(TitleMainmenu *self) {
 void *ctx,*text;u32 key;
 self->visibleCountA0=2;
 retail_002E0A6C(self->listSelector3c,2,2,0,1,0);
 if(self->transition98){ MenuSelector *selector=self->listSelector3c;int saved=retail_003693E8();retail_002E0C30(selector,saved,-1);}
 retail_003748A4(self,0);
 retail_00374840(self,self->listSelector3c->displayed08);
 retail_003748EC(self,2,retail_00613888);
 retail_0036A22C(self,retail_00613890[self->listSelector3c->current00]);
 
 retail_003749A0(self,2);
 ctx=retail_00251364();key=retail_003E4710(retail_006138D4);text=retail_00251440(ctx,key);
 retail_0036A29C(self,text);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0037388C
void match_0037388C(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 
 dialog=self->dialog24;ctx=retail_00251364();key=retail_003E4710(retail_006138E0);message=retail_00251440(ctx,key);
 ctx=retail_00251364();yes=retail_00251440(ctx,0xCF17C934u);
 ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
 retail_002E2CB0(dialog,0,1,message,yes,no,0);
 retail_002E2E38(self->dialog24,1);self->dialog99=1;self->active9a=0;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003744FC
void match_003744FC(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 
 dialog=self->dialog24;ctx=retail_00251364();key=retail_003E4710(retail_006138E0);message=retail_00251440(ctx,key);
 ctx=retail_00251364();yes=retail_00251440(ctx,0xCF17C934u);
 ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
 retail_002E2CB0(dialog,0,1,message,yes,no,0);
 retail_002E2E38(self->dialog24,1);self->dialog99=1;self->active9a=0;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373EE0
void match_00373EE0(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 retail_00389624(self,&self->cse90,0xee,1);retail_002F90A0(self->scene04,8,0);
 dialog=self->dialog24;ctx=retail_00251364();key=retail_003E4710(retail_00613934);message=retail_00251440(ctx,key);
 ctx=retail_00251364();yes=retail_00251440(ctx,0x106EC838u);
 ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
 retail_002E2CB0(dialog,0,0,message,yes,no,0);
 self->dialog99=1;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003745C0
void match_003745C0(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 retail_00373A24(self);
 dialog=self->dialog24;ctx=retail_00251364();key=retail_003E4710(retail_00613964);message=retail_00251440(ctx,key);
 ctx=retail_00251364();yes=retail_00251440(ctx,0x106EC838u);
 ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
 retail_002E2CB0(dialog,0,0,message,yes,no,0);
 self->dialog99=1;retail_002F90A0(self->scene04,8,0);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0037468C
void match_0037468C(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 retail_003732F0(self);
 dialog=self->dialog24;ctx=retail_00251364();key=retail_003E4710(retail_00613970);message=retail_00251440(ctx,key);
 ctx=retail_00251364();yes=retail_00251440(ctx,0x106EC838u);
 ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
 retail_002E2CB0(dialog,0,0,message,yes,no,0);
 self->dialog99=1;retail_002F90A0(self->scene04,8,0);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374758
void match_00374758(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 retail_003749A0(self,0);retail_00389624(self,&self->cse90,0xee,1);
 dialog=self->dialog24;ctx=retail_00251364();key=retail_003E4710(retail_0061397C);message=retail_00251440(ctx,key);
 ctx=retail_00251364();yes=retail_00251440(ctx,0x106EC838u);
 ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
 retail_002E2CB0(dialog,0,0,message,yes,no,0);
 self->dialog99=1;retail_002F90A0(self->scene04,8,0);
}
#endif

static __inline void sceneFlagA(void *p,u8 v){((u8*)p)[0x3a]=v;}
static __inline void sceneFlagB(void *p,u8 v){((u8*)p)[0x3b]=v;}
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374BAC
void match_00374BAC(TitleMainmenu *self){
 retail_002F92A4(self->scene04,0);
 retail_002F90A0(self->scene04,14,1);retail_002F90A0(self->scene04,15,1);
 retail_002F90A0(self->scene04,8,1);retail_002F90A0(self->scene04,11,1);retail_002F90A0(self->scene04,6,1);
 retail_002F995C(self->scene04);
 sceneFlagA(self->scene04,0);sceneFlagB(self->scene04,0);
}
#endif

extern const u32 retail_00613848[],retail_00613850[],retail_00613858[],retail_00613864[],retail_00613898[],retail_006138A4[];
extern const char retail_00613910[],retail_0061391C[],retail_00613928[],retail_00613940[],retail_0061394C[],retail_00613958[];
extern void retail_002402D8(MenuGlobals *);
extern void retail_00240334(MenuGlobals *);
extern void retail_00245FA4(void *,int);
extern void retail_00245F4C(void *,int);
extern const u32 retail_00613770[];
extern void *retail_003DDD88(void *,u32);
extern void retail_0032BDCC(void *,void *);
extern const float retail_00613748,retail_0061374C;
extern float retail_00671A08,retail_00671A0C;
extern u32 retail_00671A10,retail_00671A14;
extern float retail_00671A18[3],retail_00671A24[3];
extern void retail_003D1234(float,float,float,void *);
extern void *retail_00252150(void);
extern void retail_00252514(void *,int);
extern int retail_003897E4(TitleMainmenu *);
extern int retail_00389774(TitleMainmenu *);
extern void retail_0037311C(TitleMainmenu *);
extern void retail_00375620(TitleMainmenu *,float);
extern void retail_002F8E70(void *,float);
extern void retail_00327FA0(void *,float);
extern void retail_0025406C(void *,float);
extern void retail_00374ABC(TitleMainmenu *);
extern void retail_00328058(void *);
extern void retail_002F9050(void *);
extern void retail_002543D0(void *);
extern int retail_002E2DE0(void *);
extern void retail_003693F4(int);
extern void retail_0036940C(int);
extern void retail_00382A88(void);
extern void retail_003693C8(int,int);
extern void retail_00389730(TitleMainmenu *,int,int,int);
extern MenuInput *retail_003C6764(void);
extern void retail_002E0ABC(MenuSelector *,float,int);
extern void retail_0032BC3C(void *,float);
extern void retail_00389AB4(TitleMainmenu *,u32);
extern void retail_002E3D2C(void *,float);
extern int retail_002E2DEC(void *);
extern void retail_002E2DC4(void *);
extern int retail_00374E48(TitleMainmenu *);

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00375620
void match_00375620(TitleMainmenu *self,float delta) {
 MenuInput *input=retail_003C6764();
 switch(self->state08){
 case 0:{
  MenuSelector *selector;
  retail_002E0ABC(self->mainSelector34,delta,0);
  selector=self->mainSelector34;
  if(selector->busy20){
   retail_00374840(self,selector->displayed08);
   retail_0036A22C(self,retail_006137F0[self->mainSelector34->current00]);
   retail_0032BC3C(retail_0032827C(self->cse90,0xee),0.0f);
   retail_00389AB4(self,0x1BA05DC6u);
  }else{
   MenuPad *pad=input->pad10;
   if((u8)((pad->pressed04&0x2000&pad->enabled24)!=0)){
    int versus=2;
    int acceptStates[]={5,versus,3,5,5,5,8};
    int next=acceptStates[selector->current00];
    if(selector->current00==0&&retail_0023FF88()->game20->storyMode0c==0)next=1;
    if(next==versus&&retail_0023FF88()->game20->flag28){
     retail_0023FF88()->game20->flag28=0;next=18;
    }
    retail_00389730(self,next,0,25);
    retail_003748A4(self,1);
    retail_00389AB4(self,0xBCC3DE48u);
   }else if((u8)((pad->pressed04&0x4000&pad->enabled24)!=0)){
    retail_0037388C(self);
    self->state08=4;self->requested0c=4;self->ticks10=0;
    retail_00389AB4(self,0xC5493A16u);
   }
  }
  break;
 }
 case 1:case 2:case 3:case 8:{
  MenuSelector *selector;
  retail_002E0ABC(self->listSelector3c,delta,0);
  selector=self->listSelector3c;
  if(selector->busy20){
   retail_00374840(self,selector->displayed08);
   retail_0032BC3C(retail_0032827C(self->cse90,0xee),0.0f);
   {
    int state=self->state08;selector=self->listSelector3c;
    if(state==2)retail_0036A22C(self,retail_0061387C[selector->current00]);
    else if(state==1)retail_0036A22C(self,retail_0061380C[selector->current00]);
    else if(state==8)retail_0036A22C(self,retail_00613864[selector->current00]);
    else retail_0036A22C(self,retail_00613890[selector->current00]);
   }
   retail_00389AB4(self,0x1BA05DC5u);
  }else{
   MenuPad *pad=input->pad10;
   if((u8)((pad->pressed04&0x2000&pad->enabled24)!=0)){
    int next=5;int state;
    retail_003748A4(self,1);
    retail_00389AB4(self,0xBCC3DE48u);
    state=self->state08;
    if(state==1){
     MenuGameState *game;int mask=~15;
     switch(self->listSelector3c->current00){
     case 0:game=retail_0023FF88()->game20;game->flags06&=mask;break;
     case 3:
      game=retail_0023FF88()->game20;game->flags06=(game->flags06&mask)|3;
      retail_00245FA4(retail_0023FF88()->unlocks80,6);break;
     case 2:game=retail_0023FF88()->game20;game->flags06=(game->flags06&mask)|2;break;
     case 1:default:game=retail_0023FF88()->game20;game->flags06=(game->flags06&mask)|1;break;
     }
    }else if(state==8){
     if(self->listSelector3c->current00==2){next=13;((int*)retail_0023FF88()->unlocks80)[2]=0;}
    }else{
     u8 *progress=(u8*)retail_0023FF88()->progress28;
     if(progress[0x3864]){next=6;progress[0x3864]=0;}
    }
    retail_00389730(self,next,0,25);
   }else if((u8)((pad->pressed04&0x4000&pad->enabled24)!=0)){
    retail_00389730(self,0,0,1);
    retail_00389AB4(self,0xC5493A16u);
   }
  }
  break;
 }
 case 4:case 15:
  retail_002E3D2C(self->dialog24,delta);
  if(self->dialog99&&retail_002E2DE0(self->dialog24)){
   switch(retail_002E2DEC(self->dialog24)){
   case 0:retail_002E2DC4(self->dialog24);self->active9a=1;self->dialog99=0;break;
   case 1:retail_002E2DC4(self->dialog24);self->active9a=0;self->dialog99=0;break;
   case 2:retail_002E2DC4(self->dialog24);self->active9a=0;self->dialog99=0;break;
   default:break;
   }
  }
  break;
 case 7:{
  MenuSelector *selector;
  retail_002E0ABC(self->listSelector3c,delta,0);
  selector=self->listSelector3c;
  if(selector->busy20){
   retail_00374840(self,selector->displayed08);
   retail_0032BC3C(retail_0032827C(self->cse90,0xee),0.0f);
   retail_0036A22C(self,retail_00613850[self->listSelector3c->current00]);
   retail_00389AB4(self,0x1BA05DC5u);
  }else{
   MenuPad *pad=input->pad10;
   if((u8)((pad->pressed04&0x2000&pad->enabled24)!=0)){
    retail_003748A4(self,1);
    retail_00389AB4(self,0xBCC3DE48u);
    retail_00389730(self,12,0,25);
   }else if((u8)((pad->pressed04&0x4000&pad->enabled24)!=0)){
    retail_003744FC(self);
    self->state08=15;self->requested0c=15;self->ticks10=7;
    retail_00389AB4(self,0xC5493A16u);
   }
  }
  break;
 }
 case 13:{
  int selected=self->listSelector3c->current00;
  MenuPad *pad;
  retail_002E0ABC(self->listSelector3c,delta,0);
  if(self->listSelector3c->current00!=selected){
   retail_0032BC3C(retail_0032827C(self->cse90,0xee),0.0f);
   retail_00374840(self,self->listSelector3c->displayed08);
   retail_0036A22C(self,retail_006138A4[self->listSelector3c->current00]);
   retail_00389AB4(self,0x1BA05DC5u);
  }
  pad=input->pad10;
  if((u8)((pad->pressed04&0x2000&pad->enabled24)!=0)){
   retail_003748A4(self,1);
   retail_00389AB4(self,0xBCC3DE48u);
   {MenuGlobals *globals=retail_0023FF88();((int*)globals->unlocks80)[2]=self->listSelector3c->current00;}
   retail_002E0A6C(self->listSelector3c,3,3,0,1,0);
   retail_002E0C30(self->listSelector3c,2,-1);
   retail_00389730(self,5,0,25);
  }else if((u8)((pad->pressed04&0x4000&pad->enabled24)!=0)){
   retail_003693C8(self->mainSelector34->current00,2);
   self->transition98=1;
   retail_00389730(self,8,0,1);
   retail_00389AB4(self,0xC5493A16u);
  }
  break;
 }
 case 6:{
  void *dialog;
  retail_002E3D2C(self->dialog24,delta);
  dialog=self->dialog24;
  if(self->dialog99){
   if(retail_002E2DE0(dialog)){
    switch(retail_002E2DEC(self->dialog24)){default:break;case 0:self->flagA4=1;self->dialog99=0;retail_002E2DC4(self->dialog24);break;case 1:case 2:self->dialog99=0;retail_002E2DC4(self->dialog24);break;}
   }
  }else if(!retail_002E2DE0(dialog))retail_00389730(self,5,0,1);
  break;
 }
 case 9:case 11:case 12:case 14:case 16:case 17:case 18:{
  void *dialog;
  retail_002E3D2C(self->dialog24,delta);
  dialog=self->dialog24;
  if(self->dialog99){
   if(retail_002E2DE0(dialog)){
    switch(retail_002E2DEC(self->dialog24)){default:break;case 0:self->active9a=1;self->dialog99=0;retail_002E2DC4(self->dialog24);break;case 1:case 2:self->active9a=0;self->dialog99=0;retail_002E2DC4(self->dialog24);break;}
   }
  }else if(!retail_002E2DE0(dialog)){
   int state=self->state08;
   if(state==9){
    if(!self->active9a)retail_00389730(self,11,0,1);
    else retail_00389730(self,10,0,1);
   }else if(state==16)retail_00389730(self,7,0,1);
   else if(state==14){
    if(!retail_00374E48(self))retail_00389730(self,16,0,1);
    else retail_003742F0(self);
   }else if(state==11)retail_00389730(self,0,0,1);
   else if(state==12){
    if(!self->active9a){self->state08=15;self->requested0c=15;self->ticks10=7;}
    else retail_00389730(self,9,0,1);
   }else if(state==17)retail_00389730(self,0,0,1);
   else if(state==18)retail_00389730(self,2,0,1);
   else retail_00389730(self,7,0,1);
  }
  break;
 }
 case 10:
  if(!(u8)(self->connection20->requested14!=0)){
   retail_0036573C(self->parent54,2);
   retail_00389730(self,11,0,1);
  }
  break;
 default:break;
 }
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003752EC
int match_003752EC(TitleMainmenu *self,float delta) {
 MenuVirtualEntry *entry;
 retail_00252514(retail_00252150(),0);
 entry=&self->vtable1c[5];entry->call((u8*)self+entry->thisDelta);
 if(retail_003897E4(self))retail_0037311C(self);
 if(!retail_00389774(self))retail_00375620(self,delta);
 retail_002F8E70(self->scene04,delta);
 retail_00327FA0(self->cse90,delta);
 retail_0025406C(self->connection20,delta);
 retail_00374ABC(self);
 retail_00328058(self->cse90);
 retail_002F9050(self->scene04);
 retail_002543D0(self->connection20);
 switch((int)self->state08){
 case 4:case 15:
  if(!retail_002E2DE0(self->dialog24)){
   if(self->active9a){retail_0036573C(self->parent54,0);retail_003693C8(0,0);return 3;}
   if(self->state08==4){self->state08=0;self->requested0c=0;self->ticks10=4;}
   else if(self->state08==15){self->state08=7;self->requested0c=7;self->ticks10=15;}
  }
  break;
 case 5:{
  int parentResults[]={12,5,5,14,23,24,16};
  int selected=self->mainSelector34->current00;
  int result=parentResults[selected];
  switch(selected){
  case 1:{
   int vsModes[]={2,1,0};
   retail_0036940C(vsModes[self->listSelector3c->current00]);
   break;
  }
  case 2:
   if(self->listSelector3c->current00==0)result=9;
   retail_0036940C(3);retail_00382A88();
   break;
  case 3:retail_003693F4(4);break;
  case 6:
   if(self->listSelector3c->current00==1)retail_00245FA4(retail_0023FF88()->unlocks80,4);
   else if(self->listSelector3c->current00==0){result=17;retail_00245FA4(retail_0023FF88()->unlocks80,3);}
   else if(self->listSelector3c->current00==2)result=18;
   break;
  default:break;
  }
  if(self->flagA4){retail_003693F4(result);result=14;}
  retail_003693C8(self->mainSelector34->current00,self->listSelector3c->current00);
  retail_00389730(self,19,0,0);
  return result;
 }
 default:break;
 }
 return 0;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003761A0
void match_003761A0(void) {
 retail_00671A08=retail_00613748*2.0f;
 retail_003D1234(0.0f,0.0f,0.0f,retail_00671A18);
 retail_003D1234(1.0f,1.0f,1.0f,retail_00671A24);
 retail_00671A0C=1.0f/retail_0061374C;
 retail_003DDD88(&retail_00671A10,0xffffffffu);
 retail_003DDD88(&retail_00671A14,0x88888888u);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374ABC
void match_00374ABC(TitleMainmenu *self) {
 int state=(int)self->state08;
 u32 i;
 if(state>=4&&state<6)state=self->ticks10;
 else state=(int)self->state08;
 for(i=0;i<7;++i){
  void *node;u32 color;
  if(i>=7)break;
  node=retail_0032827C(self->cse90,retail_00613770[i]&0xffff);
  /* Retail retains this empty state switch. Its behavior must not be invented. */
  switch(state){case 0:break;case 2:break;default:break;}
  retail_0032BDCC(node,retail_003DDD88(&color,0xffffffffu));
 }
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373A24
void match_00373A24(TitleMainmenu *self) {
 void *ctx,*text;u32 key;
 retail_002F90A0(self->scene04,8,1);
 self->visibleCountA0=2;
 retail_002E0A6C(self->listSelector3c,2,2,0,1,0);
 retail_003748A4(self,0);
 retail_00374840(self,self->listSelector3c->current00);
 retail_003748EC(self,2,retail_00613848);
 retail_0036A22C(self,retail_00613850[self->listSelector3c->current00]);
 ctx=retail_00251364();key=retail_003E4710(retail_00613910);text=retail_00251440(ctx,key);
 retail_0036A29C(self,text);
 retail_003749A0(self,2);
 if(retail_00246000(retail_0023FF88()->unlocks80,1))retail_00389624(self,&self->cse90,retail_0061378C[0],0);
 if(retail_00246000(retail_0023FF88()->unlocks80,2))retail_00389624(self,&self->cse90,retail_0061378C[1],0);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373B80
void match_00373B80(TitleMainmenu *self) {
 void *ctx,*text;u32 key;
 self->visibleCountA0=3;
 retail_002E0A6C(self->listSelector3c,3,3,0,1,0);
 if(self->transition98){MenuSelector *selector=self->listSelector3c;int saved=retail_003693E8();retail_002E0C30(selector,saved,-1);}
 retail_003748A4(self,0);
 retail_00374840(self,self->listSelector3c->displayed08);
 retail_003748EC(self,3,retail_00613858);
 retail_0036A22C(self,retail_00613864[self->listSelector3c->current00]);
 retail_003749A0(self,3);
 ctx=retail_00251364();key=retail_003E4710(retail_0061391C);text=retail_00251440(ctx,key);
 retail_0036A29C(self,text);
 if(retail_00246000(retail_0023FF88()->unlocks80,3))retail_00389624(self,&self->cse90,retail_0061378C[0],0);
 if(retail_00246000(retail_0023FF88()->unlocks80,4))retail_00389624(self,&self->cse90,retail_0061378C[1],0);
 if(retail_00374DA8(self))retail_00389624(self,&self->cse90,retail_0061378C[2],0);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373D1C
void match_00373D1C(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 if(self->listSelector3c->current00==0){retail_002402D8(retail_0023FF88());retail_00245FA4(retail_0023FF88()->unlocks80,1);}
 else if(self->listSelector3c->current00==1){retail_00240334(retail_0023FF88());retail_00245FA4(retail_0023FF88()->unlocks80,2);}
 retail_003749A0(self,0);
 retail_00389624(self,&self->cse90,0xee,1);
 retail_002F90A0(self->scene04,8,0);
 dialog=self->dialog24;
 ctx=retail_00251364();key=retail_003E4710(retail_00613928);message=retail_00251440(ctx,key);
 ctx=retail_00251364();yes=retail_00251440(ctx,0xCF17C934u);
 ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
 retail_002E2CB0(dialog,0,1,message,yes,no,0);
 self->dialog99=1;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00373FBC
void match_00373FBC(TitleMainmenu *self) {
 void *dialog,*ctx,*message,*yes,*no;u32 key;
 int selection;
 retail_003748A4(self,0);selection=self->listSelector3c->current00;dialog=self->dialog24;
 if(selection==0){
  ctx=retail_00251364();key=retail_003E4710(retail_00613940);message=retail_00251440(ctx,key);
  ctx=retail_00251364();yes=retail_00251440(ctx,0xCF17C934u);
  ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
  retail_002E2CB0(dialog,0,1,message,yes,no,0);
 }else{
  ctx=retail_00251364();key=retail_003E4710(retail_0061394C);message=retail_00251440(ctx,key);
  ctx=retail_00251364();yes=retail_00251440(ctx,0xCF17C934u);
  ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
  retail_002E2CB0(dialog,0,1,message,yes,no,0);
 }
 self->dialog99=1;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0037410C
void match_0037410C(TitleMainmenu *self) {
 void *unlocks=retail_0023FF88()->unlocks80;
 int count=3;MenuSelector *selector;
 void *ctx,*text;u32 key;
 if(!retail_00246000(unlocks,8))count=2;
 if(!retail_00246000(unlocks,7))--count;
 self->visibleCountA0=count;
 retail_002E0A6C(self->listSelector3c,count,count,0,1,0);
 selector=self->listSelector3c;
 retail_002E0C30(selector,((int*)retail_0023FF88()->unlocks80)[2],-1);
 retail_003748A4(self,0);
 retail_00374840(self,self->listSelector3c->displayed08);
 retail_003748EC(self,3,retail_00613898);
 retail_0036A22C(self,retail_006138A4[self->listSelector3c->current00]);
 retail_003749A0(self,self->visibleCountA0);
 ctx=retail_00251364();key=retail_003E4710(retail_00613958);text=retail_00251440(ctx,key);
 retail_0036A29C(self,text);
 if(retail_00246000(unlocks,10))retail_00389624(self,&self->cse90,retail_0061378C[0],0);
 if(retail_00246000(unlocks,11)&&retail_00246000(unlocks,7))retail_00389624(self,&self->cse90,retail_0061378C[1],0);
 if(retail_00246000(unlocks,12)&&retail_00246000(unlocks,8))retail_00389624(self,&self->cse90,retail_0061378C[2],0);
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374E48
int match_00374E48(TitleMainmenu *self) {
 void *unlocks=retail_0023FF88()->unlocks80;
 int result=0;
 if(retail_00374C70(self)){
  int entries[]={13,14,15,16,17,19,20,21,22};
  u32 i;
  for(i=0;i<9;++i)if(!retail_00246000(unlocks,entries[i])){result=1;break;}
  if(!retail_00246000(unlocks,18)&&retail_00246000(unlocks,5))result=1;
 }
 return result;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003742F0
void match_003742F0(TitleMainmenu *self) {
 void *unlocks,*dialog,*ctx,*message,*yes,*no;
 u32 key,i;
 retail_00373A24(self);
 key=0;
 unlocks=retail_0023FF88()->unlocks80;
 {
 int entries[]={13,14,15,16,17,19,20,21,22};
 u32 messages[]={0x8B3B9520u,0x8B3B952Fu,0x0A1EF762u,0x0A1EF763u,0x0A1EF760u,0x890259BDu,0x0A1EF76Au,0x0A1EF76Bu,0x890259BEu};

 for(i=0;i<9;++i)if(!retail_00246000(unlocks,entries[i])){
  retail_00245F4C(unlocks,entries[i]);key=messages[i];break;
 }
 if(!key){
 if(!retail_00246000(unlocks,18)&&retail_00246000(unlocks,5)){
 retail_00245F4C(unlocks,18);key=0x8B3B952Eu;
 }}
 if(key){
  dialog=self->dialog24;
  ctx=retail_00251364();message=retail_00251440(ctx,key);
  ctx=retail_00251364();yes=retail_00251440(ctx,0x106EC838u);
  ctx=retail_00251364();no=retail_00251440(ctx,0xCF17C937u);
  retail_002E2CB0(dialog,0,0,message,yes,no,0);self->dialog99=1;
 }
 retail_002F90A0(self->scene04,8,0);
 }
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374840
void match_00374840(TitleMainmenu *self, int selection) {
    void *cursor = retail_0032827C(self->cse90, 0xEE);
    int base_y = retail_00374F40(self, self->visibleCountA0);
    retail_0032BD80(cursor, 0, selection * 24 + base_y);
}

#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003748A4
extern void retail_003895E0(void *self, void *cse_slot, const char *motion, int node_id);
extern const char retail_00613988[];
extern const char retail_00613994[];

void match_003748A4(TitleMainmenu *self, unsigned char out_motion) {
    if (!out_motion)
        retail_003895E0(self, &self->cse90, retail_00613988, 0xEE);
    else
        retail_003895E0(self, &self->cse90, retail_00613994, 0xEE);
}

#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003748EC
extern void *retail_0032827C(void *cse,int node_id);
extern void *retail_00251364(void);
extern void *retail_00251440(void *ctx,unsigned int string_id);
extern void retail_00333250(void *node,void *text);
extern const unsigned int retail_00613770[];
void match_003748EC(TitleMainmenu *self,int count,const unsigned int*ids){int i=0;const unsigned int*nodes=retail_00613770;const unsigned int*sid=ids;while(i<7&&i<count){
 void*node=retail_0032827C(self->cse90,(int)(*nodes&0xffffu));
 void*ctx=retail_00251364();
 void*text=retail_00251440(ctx,*sid);
 retail_00333250(node,text);
 ++i;++nodes;++sid;
}}

#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00374F40
extern const int retail_006137A8[];

int match_00374F40(void *self, int visible_count) {
    (void)self;
    return retail_006137A8[visible_count];
}

#endif
