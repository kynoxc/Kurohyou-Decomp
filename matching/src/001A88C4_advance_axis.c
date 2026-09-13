float match_001A88C4(float current,float target,float velocity,float frameTicks){
float result=current+frameTicks*velocity;
if(velocity<0.0f){if(result<=target)return target;}
else if(!(result<target))return target;
return result;}
