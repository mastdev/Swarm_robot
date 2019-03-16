#define mlf 2
#define mlb 3
#define mlp 9           
#define mrf 4                               
#define mrb 5                   
#define mrp 10          

#include <RH_ASK.h>
#include <SPI.h> 
 
RH_ASK rf_driver;
int mlpwm=0,mrpwm=0,mls=173,mrs=173;
int reading[5];
int dread[5];
int perr=0, derr=0, corr=0, kp=17, kd=25, sen_thr=300,sum=0,err=0,wsum=0;

void setup()
{
  Serial.begin(9600);
  pinMode(mlf, OUTPUT);
  pinMode(mlb, OUTPUT);
  pinMode(mlp, OUTPUT);
  pinMode(mrp, OUTPUT);
  pinMode(mrf, OUTPUT);
  pinMode(mrb, OUTPUT);
  if (!rf_driver.init())
    Serial.println("init failed");
}

void sensor_read(){
      reading[0]=analogRead(A0);
      reading[1]=analogRead(A1);
      reading[2]=analogRead(A2);
      reading[3]=analogRead(A3);
      reading[4]=analogRead(A4);
      
      for(int l=0; l<5; l++)
    {
      if(reading[l]<sen_thr) dread[l]=0;
      else dread[l]=1;
      }    
    }  
void calc_error(){
      sum=0;
    for(int l=0; l<5;l++)
      sum=sum+dread[l];

      if (sum!=0)
     {int wsum=10*dread[0]+3*dread[1]+0*dread[2]-3*dread[3]-10*dread[4];//0,1 right
    err=wsum/sum;
      }
      else err=0;
    }
           
    void motor(){ 
      derr=err-perr;
    corr=kp*err+kd*derr;
    perr=err;
       
    
        mrpwm=mrs-corr;
         mlpwm=mls+corr;
      if(mlpwm>254) mlpwm=254;
      if(mrpwm>254) mrpwm=254;
      if(mlpwm<0) {
        mlpwm=(-1)*mlpwm;
        digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      if(mrpwm<0) {
        mrpwm=(-1)*mrpwm;
        if(mrpwm>254) mrpwm=254;
        digitalWrite(mrf,LOW);
      digitalWrite(mlf,HIGH);
      digitalWrite(mrb,HIGH);
      digitalWrite(mlb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
        }
      if(mlpwm>0 && mrpwm>0){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      }

void line_follow(){
     sensor_read();
     calc_error();
     motor();
      }
      
void loop()
{
 line_follow();
 uint16_t data = corr;
 rf_driver.send((uint8_t*)&data, sizeof(data));

 }      
