/* Selector prefix recovered from the title menu's called functions. */
typedef unsigned int SelectorU32;
typedef unsigned char SelectorU8;
typedef struct Selector {
 int current00; SelectorU32 count04; int displayed08; SelectorU32 visible0c;
 SelectorU32 first10,range14; SelectorU8 wrap18,changed19,field1a,animating1b;
 float timer1c; int moved20,direction24,mode28; void *vtable2c;
} Selector;
extern const float retail_00605CA4;
extern int retail_002E0DF8(Selector *);
extern int retail_002E0FC0(Selector *);
extern void retail_002E10C0(Selector *,int);
extern void retail_002E1534(Selector *);
extern void retail_002E1518(Selector *);
extern void retail_002E12DC(Selector *,SelectorU32);
extern void retail_002E1408(Selector *,SelectorU32);
extern int retail_002E1454(Selector *,int,int,int,SelectorU8);
extern float retail_003D194C(float,float,float);
typedef struct SelectorPad {
 volatile SelectorU32 unused00,pressed04,unused08,repeated0c;
 volatile SelectorU32 unused10[5],enabled24;
} SelectorPad;
typedef struct SelectorInput { SelectorU32 unused00[4]; SelectorPad *pad10; } SelectorInput;
extern SelectorInput *retail_003C6764(void);
extern int retail_003C69E4(SelectorInput *,int);

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0A6C
void match_002E0A6C(Selector *self,SelectorU32 count,SelectorU32 visible,SelectorU32 range,SelectorU8 wrap,SelectorU8 field1a){
 self->current00=0;self->count04=count;self->displayed08=0;self->visible0c=visible;self->first10=0;self->range14=range;self->wrap18=wrap;self->changed19=0;self->field1a=field1a;{float timer=retail_00605CA4;self->moved20=0;self->timer1c=timer;}self->animating1b=0;self->direction24=0;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E12DC
void match_002E12DC(Selector *self,SelectorU32 position){
 self->displayed08=(SelectorU32)retail_003D194C((float)position,0.0f,(float)(self->visible0c-1));
 self->displayed08=(SelectorU32)retail_003D194C((float)(SelectorU32)self->displayed08,0.0f,(float)(self->count04-1));
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E1408
void match_002E1408(Selector *self,SelectorU32 first){
 if(!(SelectorU8)(self->visible0c<self->count04))return;
 if(first>self->count04-self->visible0c)return;
 self->first10=first;self->changed19=1;
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E1454
int match_002E1454(Selector *self,int current,int delta,int count,SelectorU8 wrap){
 int result=delta+current;
 if(delta>0){if(result>=count && wrap)result%=count;else if(result>=count)result=count-1;}
 else if(delta<0){if(result<0){if(wrap)result=(int)retail_003D194C((float)(count-(-result)%count),0.0f,(float)(self->count04-1));else{result=0;goto finish;}}}
 finish:return result;
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E1518
void match_002E1518(Selector *self){self->changed19=0;self->timer1c=retail_00605CA4;self->moved20=7;}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E10C0
void match_002E10C0(Selector *self,int movement){
 SelectorU32 next=retail_002E1454(self,self->current00,movement,self->count04,self->wrap18);
 if(next==0){
  retail_002E12DC(self,0);
  if(self->current00==self->count04-1 && movement>0){
   self->moved20=5;retail_002E1408(self,0);
  }else{int direction=self->field1a?3:1;self->moved20=direction;}
 }else if(next>=self->count04-1){
  retail_002E12DC(self,self->visible0c-1);
  if(self->current00==0 && movement<0){
   self->moved20=6;retail_002E1408(self,self->count04-self->visible0c);
  }else{int direction=self->field1a?4:2;self->moved20=direction;}
 }else{
  if(movement<0){
   if(self->displayed08==1){
    if(self->first10!=0)retail_002E1408(self,self->first10-1);
    else retail_002E12DC(self,0);
   }else retail_002E12DC(self,self->displayed08-1);
   {int direction=self->field1a?3:1;self->moved20=direction;}
  }else if(movement>0){
   if((SelectorU32)self->displayed08>=self->visible0c-2){
    if(self->first10<self->count04-self->visible0c)retail_002E1408(self,self->first10+1);
    else retail_002E12DC(self,self->visible0c-1);
   }else retail_002E12DC(self,self->displayed08+1);
   {int direction=self->field1a?4:2;self->moved20=direction;}
  }
 }
 self->current00=next;
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0AB4
void match_002E0AB4(void){}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0ABC
void match_002E0ABC(Selector *self,SelectorU8 disabled){
 int movement=0;
 self->moved20=0;self->direction24=0;self->changed19=0;
 if(!disabled){if(self->mode28==0)movement=retail_002E0DF8(self);else if(self->mode28==1)movement=retail_002E0FC0(self);}
 if(movement)retail_002E10C0(self,movement);
 else if(self->animating1b)retail_002E1534(self);
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0B58
int match_002E0B58(Selector *self){
 if(self->visible0c<self->count04&&self->range14){
  SelectorU32 difference=self->count04-self->visible0c;
  if(self->first10<difference)return (int)(((float)self->range14/(float)difference)*(float)self->first10);
  return self->range14;
 }
 return 0;
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0C0C
void match_002E0C0C(Selector *self){self->current00=0;self->displayed08=0;self->first10=0;retail_002E1518(self);}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0C30
int match_002E0C30(Selector *self,SelectorU32 selection,int position){
 if(selection<self->count04){
  int relative;
  retail_002E1518(self);
  relative=selection-self->first10;
  if(relative>0 && (SelectorU32)relative<self->visible0c-1 && position<0){
   retail_002E12DC(self,relative);self->current00=selection;return 0;
  }else{
   if(selection==0){self->first10=0;retail_002E12DC(self,0);}
   else{
    SelectorU32 maximum=self->count04-self->visible0c;
    if(position>=0){
     self->first10=(SelectorU32)retail_003D194C((float)(int)(selection-position),0.0f,(float)maximum);
     retail_002E12DC(self,selection-self->first10);
    }else{
     self->first10=(SelectorU32)retail_003D194C((float)(int)(selection-1),0.0f,(float)maximum);
     retail_002E12DC(self,selection-self->first10);
    }
   }
   self->current00=selection;return 1;
  }
 }else return 0;
}
#endif

#define SELECTOR_PRESSED(p,mask) ((SelectorU8)(((p)->pressed04 & (mask) & (p)->enabled24)!=0))
#define SELECTOR_REPEATED(p,mask) ((SelectorU8)(((p)->repeated0c & (mask) & (p)->enabled24)!=0))

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0DF8
int match_002E0DF8(Selector *self){
 SelectorInput *input=retail_003C6764();
 int movement=0;
 int old=retail_003C69E4(input,1);
 int selection=self->current00;
 SelectorPad *pad=input->pad10;
 if(self->field1a){
  if(selection==0){if(SELECTOR_PRESSED(pad,0x80))movement=-1;}
  else if(SELECTOR_REPEATED(pad,0x80))movement=-1;
  if(selection==self->count04-1){if(SELECTOR_PRESSED(pad,0x20))movement=1;}
  else if(SELECTOR_REPEATED(pad,0x20))movement=1;
 }else{
  if(selection==0){if(SELECTOR_PRESSED(pad,0x10))movement=-1;}
  else if(SELECTOR_REPEATED(pad,0x10))movement=-1;
  if(selection==self->count04-1){if(SELECTOR_PRESSED(pad,0x40))movement=1;}
  else if(SELECTOR_REPEATED(pad,0x40))movement=1;
 }
 retail_003C69E4(input,old);return movement;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x002E0FC0
int match_002E0FC0(Selector *self){
 SelectorInput *input=retail_003C6764();
 int movement=0;
 int old=retail_003C69E4(input,1);
 SelectorPad *pad=input->pad10;
 if(self->field1a){
  if(SELECTOR_PRESSED(pad,0x80))movement=-1;
  else if(SELECTOR_PRESSED(pad,0x20))movement=1;
 }else{
  if(SELECTOR_PRESSED(pad,0x10))movement=-1;
  else if(SELECTOR_PRESSED(pad,0x40))movement=1;
 }
 retail_003C69E4(input,old);return movement;
}
#endif
