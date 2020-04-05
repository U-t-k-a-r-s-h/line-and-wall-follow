long dist_l=0,dist_r=0,dist_f=0;
int pre_wall=0,Read=2;
int initial_motor_speed=80,max_speed=130;
void motor_control(void);
void ultrasonic_input(void);
void turn_sharp_right(void);
void turn_sharp_left(void);

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);//right motor+
  pinMode(4, OUTPUT);//right motor -
  pinMode(5, OUTPUT);//left motor -
  pinMode(6, OUTPUT);//left motor +
  pinMode(A0, INPUT);//left echo
  pinMode(A1, OUTPUT);//left trig
  pinMode(A2, INPUT);//right echo
  pinMode(A3,OUTPUT);//right trig
  pinMode(A4,INPUT);//front echo
  pinMode(A5,OUTPUT);//front trig
  Serial.begin(9600);
  Serial.println("start");
}
void loop()
{  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  dist_l= pulseIn(A0, HIGH);

  dist_l = dist_l*0.034/2;

  digitalWrite(A3, LOW);
  delayMicroseconds(2);
  digitalWrite(A3, HIGH);
  delayMicroseconds(10);
  digitalWrite(A3, LOW);
  dist_r= pulseIn(A2, HIGH);

  dist_r = dist_r*0.034/2;

  digitalWrite(A5, LOW);
  delayMicroseconds(2);
  digitalWrite(A5, HIGH);
  delayMicroseconds(10); 
  digitalWrite(A5, LOW);
  dist_f= pulseIn(A4, HIGH);
  
  dist_f = dist_f*0.034/2;
  Read=Serial.read();
   if((dist_l<35||dist_r<35||dist_f<35)&&(Read==0)&&(pre_wall!=0))
  { //Serial.println("inside wall following loop");
    Serial.print(1);
    ultrasonic_input();
  }
  Serial.print(0);
}
void ultrasonic_input()
{
   digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  dist_l= pulseIn(A0, HIGH);

  dist_l = dist_l*0.034/2;

  digitalWrite(A3, LOW);
  delayMicroseconds(2);
  digitalWrite(A3, HIGH);
  delayMicroseconds(10);
  digitalWrite(A3, LOW);
  dist_r= pulseIn(A2, HIGH);

  dist_r = dist_r*0.034/2;

  digitalWrite(A5, LOW);
  delayMicroseconds(2);
  digitalWrite(A5, HIGH);
  delayMicroseconds(10); 
  digitalWrite(A5, LOW);
  dist_f= pulseIn(A4, HIGH);
  
  dist_f = dist_f*0.034/2;
   
  //Serial.println("distance from front wall");
//Serial.println(dist_f);
 Serial.println("distances");
 Serial.println(dist_r);
 Serial.println(dist_l);
 Serial.println(dist_f);
 //Serial.println("distance from left wall");
//Serial.println(dist_l);
 
 while(dist_r<20&&dist_l>=20&&dist_f>=20)
  { pre_wall=1;//right wall
    if(dist_r>11)
       {Serial.println("caliberating right");
        analogWrite(3,max_speed+30);
       analogWrite(4,0);
       analogWrite(6,(max_speed-30));
       analogWrite(5,0);
       }
    if(dist_r<9)
       {Serial.println("caliberating left");
        analogWrite(3,max_speed-30);
       analogWrite(4,0);
       analogWrite(6,max_speed+30);
       analogWrite(5,0);
       }   
    if(dist_r>=9&&dist_r<=11)
       {Serial.println("moving forward");
        analogWrite(3,max_speed);
       analogWrite(4,0);
       analogWrite(6,max_speed);
       analogWrite(5,0); 
       }
     digitalWrite(A3, LOW);
     delayMicroseconds(2);
     digitalWrite(A3, HIGH);
     delayMicroseconds(10);
     digitalWrite(A3, LOW);
     dist_r= pulseIn(A2, HIGH);

     dist_r = dist_r*0.034/2;  
      digitalWrite(A1, LOW);
     delayMicroseconds(2);
     digitalWrite(A1, HIGH);
     delayMicroseconds(10);
     digitalWrite(A1, LOW);
     dist_l= pulseIn(A0, HIGH);

     dist_l = dist_l*0.034/2;
     digitalWrite(A5, LOW);
     delayMicroseconds(2);
     digitalWrite(A5, HIGH);
     delayMicroseconds(10);
     digitalWrite(A5, LOW);
     dist_f= pulseIn(A4, HIGH);
     dist_f = dist_f*0.034/2;
  }
  while(dist_l<20&&dist_r>=20&&dist_f>=20)
  { pre_wall=2;//left wall
    if(dist_l>11)
       {Serial.println("caliberating left");
        analogWrite(3,max_speed-30);
       analogWrite(4,0);
       analogWrite(6,(max_speed+30));
       analogWrite(5,0);}
    if(dist_l<9)
       {Serial.println("caliberating right");
        analogWrite(3,(max_speed+30));
       analogWrite(4,0);
       analogWrite(6,max_speed-30);
       analogWrite(5,0);
       }
    if(dist_l>=9&&dist_l<=11)
      {Serial.println("forward");
        analogWrite(3,max_speed);
       analogWrite(4,0);
       analogWrite(6,max_speed);
       analogWrite(5,0);
      }
     digitalWrite(A3, LOW);
     delayMicroseconds(2);
     digitalWrite(A3, HIGH);
     delayMicroseconds(10);
     digitalWrite(A3, LOW);
     dist_r= pulseIn(A2, HIGH);

     dist_r = dist_r*0.034/2;  
      digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  dist_l= pulseIn(A0, HIGH);

  dist_l = dist_l*0.034/2;
   digitalWrite(A5, LOW);
  delayMicroseconds(2);
  digitalWrite(A5, HIGH);
  delayMicroseconds(10);
  digitalWrite(A5, LOW);
  dist_f= pulseIn(A4, HIGH);
  dist_f = dist_f*0.034/2;
    //error=15-dist_r;
  }
 // read_sensor_values();
if(dist_l>=30&&dist_r>=30&&dist_f>=30&&(pre_wall!=0))
{ switch(pre_wall)
  {    
    case 1:Serial.println("next wall to move is right");
         turn_sharp_right();
         break;
    case 2:Serial.println("next wall to move is left");
         turn_sharp_left();
         break;
    default:
       Serial.println("stop");
       analogWrite(3,0);
       analogWrite(4,0);
       analogWrite(6,0);
       analogWrite(5,0);
         break;
  }
}
delay(200);
 if(dist_f<=20&&(dist_l<=28||dist_r<=28))
 {
    switch(pre_wall)
    {
    case 1:Serial.println("forward wall detected turning left"); //case 1 means previous wall was left wall
         turn_sharp_left();
         pre_wall=0;
         break;
    case 2:Serial.println("foward wall detected turning right");// case 2 means that previous wall was right wall
         turn_sharp_right();
         pre_wall=0;
         break;
    default:
        Serial.println("dont know where to go");
        analogWrite(3,0);
        analogWrite(4,0);
        analogWrite(6,0);
        analogWrite(5,0);
         pre_wall=0;
         break;
     }

  }
}
void turn_sharp_right()
{     Serial.println("it has turned right");
       analogWrite(3,max_speed);
       analogWrite(4,0);
       analogWrite(6,0);
       analogWrite(5,0);
       pre_wall=0;
       delay(1200);
        analogWrite(3,max_speed);
       analogWrite(4,0);
       analogWrite(6,max_speed);
       analogWrite(5,0); 
}
void turn_sharp_left()
{
     Serial.println("it has turned left");  
       analogWrite(3,0);
       analogWrite(4,0);
       analogWrite(6,max_speed);
       analogWrite(5,0);
       pre_wall=0;
       delay(1200);
        analogWrite(3,max_speed);
       analogWrite(4,0);
       analogWrite(6,max_speed);
       analogWrite(5,0); 
}
