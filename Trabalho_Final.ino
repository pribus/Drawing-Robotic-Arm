#include <math.h>

float teta1,teta2;
int m = 1;
char lido;

#include <Servo.h>
Servo motor1;
Servo motor2;


// A função reta calcula a equação da reta a partir dos pontos final e inicial. Como saída obter-se-á os pares de ângulos (teta1 e teta2) para os braços se moverem na reta definida:
void reta(float xf,float x0,float yf, float y0){
  float d0, tb, tf, db, alcancavel = 0;
  float dt=0.01;
  float acel = 2;   //20mm/s^2
  float velh = 3;   //30mm/s
  float dx = (xf-x0);
  float dy = (yf-y0);
  float df = sqrt(dx*dx+dy*dy);
  float k,t,d,y,x;
  
  if (acel >= (velh*velh/(df-d0))){
    tb = velh/acel;
    tf = (acel*tb*tb+(df-d0))/(acel*tb);
    db = d0+acel*tb*tb/2;
    alcancavel = 1;
    
  }
  else{
    tf = 2*sqrt((df-d0)/acel);
    alcancavel=0;
  }
  
  for(k=0; k<=(tf/dt+2);k++){
    t = (k-1)*dt;
   
    
    if(alcancavel==1){
        if(t<=tb)
        {
            d=d0+acel*t*t/2;
         
        }
    
        if((tb<t)&&(t<(tf-tb)))
        {
            d=db+velh*(t-tb);
            
        } 
        if((tf-tb)<=t)
        {
            d=df-acel*(tf-t)*(tf-t)/2;
            
        }
    }    
    else
    {
        if(t<=(tf/2)){
            d=d0+acel*t*t/2;
        }
        if((tf/2)<t){
            d=df-acel*(tf-t)*(tf-t)/2;
        }
    }
    
  x=x0+d*(dx/df);
  y=y0+d*(dy/df);
  
  
Serial.println(teta1+90);
Serial.println(teta2+90);
 
cininv_planar(x,y);
  
  
motor1.write(teta1+90);
motor2.write(teta2+90);
  
 delay(1000*dt);
 
  }
}

//Cinemátia inversa:
int cininv_planar(float x, float y)

{
  float L1;
  float L2;
  float c2;
  float s2;
  float k1;
  float k2;
  
  L1=22.5;
  L2=22.5;
  c2=(x*x+y*y-L1*L1-L2*L2)/(2*L1*L2);
  if (abs(c2)>1)
  {
    return(0);
  }
  else
  {
    s2=sqrt(1-c2*c2); //s2 positivo
    teta2=atan2(s2,c2)*180/PI-90;
    k1=L1+L2*c2;
    k2=L2*s2;
    teta1=(atan2(y,x)-atan2(k2,k1))*180/PI;    
    return(1);
  }
}




void setup() {
  // put your setup code here, to run once:
  
  motor1.attach(7);
  motor2.attach(2);
  
  
  Serial.begin(9600);
}






void loop() {
   // put your main code here, to run repeatedly:
   lido=Serial.read();

//Faz o quadrado:
 
  if (lido=='a'){   
  motor1.write(60.64);
  delay(1000);
  motor2.write(87.07);
  delay(1000);
  reta(32.5,32.5,7.5,-7.5);
  delay(1000);
  reta(17.5,32.5,-7.5,-7.5);
  delay(1000);
  reta(17.5,17.5,7.5,-7.5);
  delay(1000);
  reta(32.5,17.5,7.5,7.5);
  delay(1000);
  }

//Faz uma casa:

  if (lido=='b'){   
  motor1.write(50.36);
  delay(1000);
  motor2.write(131.16);
  delay(1000);
  reta(32.5,17.5,7.5,-7.5);
  delay(1000);
  reta(17.5,32.5,7.5,7.5);
  delay(1000);
  reta(17.5,17.5,-7.5,7.5);
  delay(1000);
  reta(32.5,17.5,-7.5,-7.5);
  delay(1000);
  reta(32.5,32.5,7.5,-7.5);
  delay(1000);
  reta(42.5,32.5,0,7.5);
  delay(1000);
  reta(32.5,42.5,-7.5,0);
  delay(1000);
  reta(17.5,32.5,7.5,-7.5);
  delay(1000);
  }

 //Retorna para a posição de descanso:
  if (lido=='r'){
  motor1.write(90);
  delay(1000);
  motor2.write(90);
    delay(1000);
    
    
  }
  
  
  
   
}
