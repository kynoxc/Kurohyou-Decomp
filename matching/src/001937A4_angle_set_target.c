typedef struct A{float cur;float target;float step;int ticks;}A;
extern const float retail_005E6E4C;
extern float retail_00193948(A*,float);
void match_001937A4(A*self,float target,float step){float current,delta,distance;if(step<=0.0f){self->cur=target;return;}target=retail_00193948(self,target);current=self->cur;delta=target-current;if(step<0.0f)step=-step;distance=delta;if(distance<0.0f)distance=-distance;if(!(distance<180.0f))distance=retail_005E6E4C-distance;self->ticks=(int)(distance/step);if(target<=current){retail_00193948(self,current+180.0f);if((self->cur-target)<180.0f)step=-step;}else if(!(delta<=180.0f))step=-step;self->step=step;self->target=target;}
