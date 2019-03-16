//Receiver code
 
#define mlf 2 //in_1
#define mlb 3//in_2
#define mlp 9
#define mrf 4  //in_3
#define mrb 5  //in_4
#define mrp 10


#include <RH_ASK.h>
#include <SPI.h> 
RH_ASK rf_driver;
int mlpwm=0,mrpwm=0,mls=173,mrs=142;

int perr=0, derr=0, corr=0, kp=17, kd=25, sen_thr=300,sum=0,err=0,wsum=0;

void setup()
{  rf_driver.init();
  Serial.begin(9600);
  pinMode(mlf, OUTPUT);
  pinMode(mlb, OUTPUT);
  pinMode(mlp, OUTPUT);
  pinMode(mrp, OUTPUT);
  pinMode(mrf, OUTPUT);
  pinMode(mrb, OUTPUT);
  //digitalWrite(mlen,HIGH);
 // digitalWrite(mren,HIGH);
}

   void motor(){ 
    
        mrpwm=mrs-corr;
         mlpwm=mls+corr;
      if(mlpwm>254) mlpwm=254;
      if(mrpwm>223) mrpwm=223;
      if(mlpwm<0) {
        mlpwm=(-1)*mlpwm;
        if(mlpwm>254) mlpwm=254;
        digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      if(mrpwm<0) {
        mrpwm=(-1)*mrpwm;
        if(mrpwm>216) mrpwm=216;
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
      


      
void loop()
 { 
   motor();
    uint16_t data;
uint8_t datalen = sizeof(data);
if (   rf_driver.recv((uint8_t*)&data, &datalen)
    && datalen == sizeof(data))
{
    // Have the data, so do something with it
    uint16_t xyz = data;
    corr=(int)data;
    Serial.println(corr);
    //delay(70);
}
 }
