#ifndef KH_TITLE_MAINMENU_H
#define KH_TITLE_MAINMENU_H
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct MenuSelector { int current00; int field04; int displayed08; u8 pad0c[0x14]; int busy20; } MenuSelector;
typedef struct MenuConnection { u8 pad00[0x10]; int state10; int requested14; u8 pad18; u8 field19; u8 field1a; } MenuConnection;
typedef struct MenuVirtualEntry { short thisDelta; short reserved; void (*call)(void *); } MenuVirtualEntry;
typedef struct TitleMainmenu {
    u32 field00; void *scene04; u32 state08; u32 requested0c; int ticks10;
    u8 pad14[8]; MenuVirtualEntry *vtable1c; MenuConnection *connection20; void *dialog24; u8 pad28[12];
    MenuSelector *mainSelector34; u32 field38; MenuSelector *listSelector3c;
    u8 pad40[0x14]; void *parent54; void *resources58; u8 pad5c[0x34];
    void *cse90; u8 pad94[4]; u8 transition98; u8 dialog99; u8 active9a; u8 pad9b[5];
    int visibleCountA0; u8 flagA4;
} TitleMainmenu;
typedef struct MenuGameState { u8 pad00[6]; signed char flags06; u8 pad07; u8 extra08; u8 pad09[3]; int storyMode0c; u8 pad10[0x18]; u8 flag28; } MenuGameState;
typedef struct MenuPad { u32 field00; u32 pressed04; u8 pad08[0x1c]; u32 enabled24; } MenuPad;
typedef struct MenuInput { u8 pad00[0x10]; MenuPad *pad10; } MenuInput;
typedef struct MenuGlobals { u8 pad00[0x20]; MenuGameState *game20; u32 field24; void *progress28; u8 pad2c[0x54]; void *unlocks80; } MenuGlobals;
#endif
