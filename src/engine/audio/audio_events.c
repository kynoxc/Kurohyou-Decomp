/* Event dispatch used by SceneCommon_PlaySound; original object bounds unproven. */
typedef unsigned int AudioU32;
typedef unsigned char AudioU8;
typedef struct AudioEvents { AudioU8 pad00[12]; void *bank0c; } AudioEvents;
typedef struct AudioSystem { AudioU8 pad00[8]; int state08; } AudioSystem;
typedef struct AudioEvent { AudioU32 sound,parameter,bank; } AudioEvent;
extern AudioSystem *retail_00310FF8(void);
extern int retail_003136D8(void *,AudioU32,AudioEvent *);
extern int retail_00313778(void *,AudioU32,AudioU32,AudioEvent *);
extern int retail_0039FB94(AudioU32,AudioU32,AudioU32);
extern void retail_003A03E8(int,AudioU32);
extern AudioU32 retail_003E4710(const char *);
extern int retail_00311F78(AudioEvents *,AudioU32);
extern int retail_00312030(AudioEvents *,AudioU32,AudioU32);
extern void retail_003A098C(int,AudioU32,float);
extern void retail_00312170(AudioEvents *,int,AudioU32,float);
extern void retail_003A0AA8(int,AudioU32);
extern void retail_003A0B60(int);
extern void retail_0039FFC8(AudioU32,int);
extern void retail_0039FFE8(AudioU32,float);
extern void retail_00312254(AudioEvents *,AudioU32,float);
extern void retail_003122CC(AudioEvents *,AudioU32,AudioU32,float);
extern void retail_0039FDE4(int,int);
extern void retail_0039FE28(int,float);
extern void retail_003A0094(int,int);
extern void retail_003A00B4(int,float);
extern int retail_0031357C(void *,AudioU32);
extern void retail_0039FEFC(int,int);
extern void retail_0039FF1C(int,float);

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00311F78
int match_00311F78(AudioEvents *self,AudioU32 event) {
 int handle=-1;AudioEvent entry;
 if((AudioU8)(retail_00310FF8()->state08==2))return handle;
 if(self->bank0c&&retail_003136D8(self->bank0c,event,&entry)){
  handle=retail_0039FB94(entry.sound,entry.bank,0x30000);
  if(handle>=0)retail_003A03E8(handle,entry.parameter);
 }
 return handle;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312030
int match_00312030(AudioEvents *self,AudioU32 group,AudioU32 event) {
 int handle=-1;AudioEvent entry;
 if((AudioU8)(retail_00310FF8()->state08==2))return handle;
 if(self->bank0c&&retail_00313778(self->bank0c,group,event,&entry)){
  handle=retail_0039FB94(entry.sound,entry.bank,0x30000);
  if(handle>=0)retail_003A03E8(handle,entry.parameter);
 }
 return handle;
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003120F8
void match_003120F8(AudioEvents *self,const char *event){retail_00311F78(self,retail_003E4710(event));}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0031212C
void match_0031212C(AudioEvents *self,AudioU32 group,const char *event){retail_00312030(self,group,retail_003E4710(event));}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312170
void match_00312170(AudioEvents *self,int handle,AudioU32 parameter,float seconds) {
 if(handle>=0){if(seconds<0.0f)seconds=0.0f;retail_003A098C(handle,parameter,seconds);}
}
#endif

#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003121B4
void match_003121B4(AudioEvents *self,int handle,AudioU32 parameter,float seconds){
 retail_00312170(self,handle,0,0.0f);
 retail_00312170(self,handle,parameter,seconds);
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312218
void match_00312218(AudioEvents *self,int handle,AudioU32 parameter){retail_003A0AA8(handle,parameter);}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312238
void match_00312238(AudioEvents *self){retail_003A0B60(2);}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312254
void match_00312254(AudioEvents *self,AudioU32 event,float seconds){
 AudioEvent entry;
 if(self->bank0c && retail_003136D8(self->bank0c,event,&entry)){
  if(seconds<=0.0f)retail_0039FFC8(entry.bank,1);
  else retail_0039FFE8(entry.bank,seconds);
 }
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003122CC
void match_003122CC(AudioEvents *self,AudioU32 group,AudioU32 event,float seconds){
 AudioEvent entry;
 if(self->bank0c && retail_00313778(self->bank0c,group,event,&entry)){
  if(seconds<=0.0f)retail_0039FFC8(entry.bank,1);
  else retail_0039FFE8(entry.bank,seconds);
 }
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312344
void match_00312344(AudioEvents *self,const char *event,float seconds){retail_00312254(self,retail_003E4710(event),seconds);}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312388
void match_00312388(AudioEvents *self,AudioU32 group,const char *event,float seconds){retail_003122CC(self,group,retail_003E4710(event),seconds);}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x003123DC
void match_003123DC(AudioEvents *self,int handle,float seconds){
 if(seconds<=0.0f)retail_0039FDE4(handle,1);else retail_0039FE28(handle,seconds);
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x00312420
void match_00312420(AudioEvents *self,int frames){
 if(frames<=0)retail_003A0094(2,1);else retail_003A00B4(2,(float)frames/60.0f);
}
#endif
#if !defined(MATCH_FUNCTION) || MATCH_FUNCTION == 0x0031246C
void match_0031246C(AudioEvents *self,AudioU32 event,int frames){
 if(self->bank0c){
  int handle=retail_0031357C(self->bank0c,event);
  if(handle>=0){if(frames<=0)retail_0039FEFC(handle,1);else retail_0039FF1C(handle,(float)frames/60.0f);}
 }
}
#endif
