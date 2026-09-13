typedef signed int s32;enum ActorClass{AC0=0,AC1=1,AC2=2,AC3=3,AC4=4,AC5=5};
ActorClass match_001E2858(s32 id){if(id>=0&&id<301)return AC0;if(id>=501&&id<505)return AC1;if(id>=505&&id<508)return AC2;if(id>=852&&id<855)return AC3;if(id>=550&&id<555)return AC4;return AC5;}
