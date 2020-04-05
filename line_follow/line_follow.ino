float Kp=4,Ki=0.001,Kd=2.8;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int sensor[6],sum=0;
int max_speed=120;
int initial_motor_speed=100;
int i=0;
void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup()
{
 //pinMode(6,OUTPUT); //PWM Pin 1
 //pinMode(3,OUTPUT); //PWM Pin 2
 pinMode(3,OUTPUT); //Left Motor Pin 1
 pinMode(4,OUTPUT); //Left Motor Pin 2
 pinMode(6,OUTPUT); //Right Motor Pin 1
 pinMode(5,OUTPUT);  //Right Motor Pin 2
 pinMode(13,INPUT);//IR-1
 pinMode(12,INPUT);//IR-2     
 pinMode(11,INPUT);//IR-3
 pinMode(10,INPUT);//IR-4
 pinMode(9,INPUT);
 pinMode(8,INPUT);//IR-5
 //Serial.begin(9600); //Enable Serial Communications
}

void loop()
{
    read_sensor_values();
    calculate_pid();
    motor_control();
}

void read_sensor_values()
{ for(i=0;i<=5;i++)
  {
    sensor[i]=digitalRead(13-i);
   // Serial.println(sensor[i]);
  }
  sum=sensor[0]+sensor[1]+sensor[2]+sensor[3]+sensor[4]+sensor[5];
//Serial.println(sensor[2]);
  if(sum==1&&(sensor[5]==1))
  {error=5;
  //Serial.print("error 5");}
  }
 else if((sensor[4]==1)&&(sensor[5]==1)&&sum==2)
  {error=4;
  //Serial.print("error 4");}
  }
 else if((sensor[4]==1)&&sum==1)
  {error=3;
  //Serial.print("error 3");}
  }
  else if((sensor[3]==1)&&(sensor[4]==1)&&sum==2)
  {error=2;
  //Serial.print("error 2");}
  
  }
  else if((sensor[3]==1)&&sum==1)
  {error=1;
  //Serial.print("error 1");}
  }
  else if((sensor[2]==1)&&(sensor[3]==1)&&sum==2)
  {error=0;
  //Serial.println("froward");
  //Serial.print("error 0");}
  }
  else if((sensor[2]==1)&&sum==1)
  {error=-1;
  //Serial.print("error -1");}
  }
  else if((sensor[1]==1)&&(sensor[2]==1)&&sum==2)
  {error=-2;
  }
  else if((sensor[1]==1)&&sum==1)
  {error=-3;
  //Serial.print("error -3");
  }
  else if((sensor[0]==1)&&(sensor[1]==1)&&sum==2)
  {error=-4;
  //Serial.print("error -4");
  }
 
   else if((sensor[0]==1)&&(sensor[1]==sensor[2]==1)&&sum==3)
  {error=-6;
 
  //Serial.print("error -3");
  }
   else if((sensor[4]==sensor[5]==0)&&sum==4)
  {error=-6;
 
  //Serial.print("error -3");
  }
  else if((sensor[3]==1)&&(sensor[4]==sensor[5]==1)&&sum==3)
  {error=6;
  //Serial.print("error -3");
 }
  
   else if((sensor[0]==sensor[1]==0)&&sum==4)
  {error=6;
  //Serial.print("error -3");
 
  }
  else if((sensor[0]==1)&&sum==1)
  {error=-5;
  //Serial.print("error -5");
  }
  else if(sum==6)
  error=6;
}
void calculate_pid()
{
    P = error;
    I = I + previous_I;
    D = error-previous_error;
    
    PID_value = (Kp*P) + (Ki*I)  + (Kd*D);
    
    previous_I=I;
    previous_error=error;
}

void motor_control()
{    
 
    // Calculating the effective motor speed:
    int left_motor_speed = initial_motor_speed-PID_value;
    int right_motor_speed = initial_motor_speed+PID_value;
 //   Serial.println(left_motor_speed);
    
    // The motor speed should not exceed the max PWM value
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);
  
    analogWrite(6,left_motor_speed);   //Left Motor Speed
    analogWrite(3,right_motor_speed);  //Right Motor Speed
    //Serial.println("motor 1 on");
    if(error==0)
    {//Serial.println("forward");
      analogWrite(3,max_speed);
    analogWrite(4,0);
    analogWrite(6,max_speed);
    analogWrite(5,0);
      }
   if(sum==0)
  {//Serial.println("all white");
    if(previous_error<=0)
  {analogWrite(3,max_speed);
    analogWrite(4,0);
    analogWrite(6,0);
    analogWrite(5,0);
    }
    else if(previous_error>0)
    {analogWrite(3,0);
    analogWrite(4,0);
    analogWrite(6,max_speed);
    analogWrite(5,0);
          }
}
}
