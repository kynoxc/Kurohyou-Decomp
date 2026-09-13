extern float retail_001C58E4(float);
int match_001C59D0(float lhs,float rhs){int r=0;float a=retail_001C58E4(lhs);float b=retail_001C58E4(rhs);if(a<b){if(!(a+180.0f<=b)){r=1;goto O;}}if(!(a<=b)){if(a-180.0f<b){r=-1;goto O;}}if(a+180.0f<=b){r=-1;goto O;}if(!(a-180.0f<b))r=1;O:return r;}
