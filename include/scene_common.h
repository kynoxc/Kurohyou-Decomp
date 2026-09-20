#ifndef KH_SCENE_COMMON_H
#define KH_SCENE_COMMON_H
typedef unsigned int SceneU32;
typedef unsigned short SceneU16;
typedef unsigned char SceneU8;
typedef struct SceneFade { int current; int previous; } SceneFade;
/* Verified prefix, not the complete allocation size of every derived scene. */
typedef struct SceneCommon {
    SceneFade *fade00;
    void *scene04;
    int current08;
    int requested0c;
    int previous10;
    int delay14;
    SceneU8 useFade18;
    SceneU8 leaving19;
    SceneU8 entering1a;
    void *vtable1c;
} SceneCommon;
#endif
