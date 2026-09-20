#ifndef KH_CSE_NODE_H
#define KH_CSE_NODE_H
typedef unsigned int CseU32;
typedef unsigned short CseU16;
typedef unsigned char CseU8;
typedef struct CseNode CseNode;
typedef struct CseNodeRef { CseNode *node; void *control; } CseNodeRef;
/* Retail uses unaligned word loads/stores for the serialized pose fields. */
#pragma pack(push,1)
typedef struct CsePose {
 CseU8 unknown00[0x18]; CseU32 colors18[4];
 CseU8 unknown28[6]; CseU32 visibility2e; CseU8 unknown32[2];
} CsePose;
#pragma pack(pop)
typedef struct CseVirtualEntry {
 short delta; unsigned short reserved;
 union { CsePose *(*pose)(void *); void (*update)(void *,float); } fn;
} CseVirtualEntry;
typedef struct CseAnimator { CseU32 field00; CseU16 id04; } CseAnimator;
struct CseNode {
 CseNodeRef *begin00,*end04,*capacity08;
 CsePose pose0c;
 CseAnimator *animator40; CseU8 pad44[12];
 float matrix50[16]; float rotation90,scale94,scale98,x9c,ya0;
 signed char flagsa4; CseU8 pada5[3]; CseVirtualEntry *vtablea8;
};
#endif
