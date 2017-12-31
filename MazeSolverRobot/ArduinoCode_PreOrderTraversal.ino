float PWM;
float PWM2;
int P; // (Preportional)
float I; // (Integral)
float D; // (Derivative)
int pI; // The sum of the preportional value and the integral value
int PID; 
int val;
int Aval; // All values (see the integral equation)
int Pval1; // The previous value (see the derivative term)
int Pval2;
int Dval; // The subtraction of the current value from the previous value
void setup() {
  Serial.begin(9600);
  Aval=0;
  Pval1=0;
  Pval2=0;
  val=0;
  pinMode(5,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  
  pinMode(13,OUTPUT);//for led
}
int flag=0;//for checking only 1 end possible 
//FUNCTIONS:
  void HardRight(){
    digitalWrite(5,LOW);
    analogWrite(9,110);
    analogWrite(10,110);//RIGHT
    digitalWrite(11,LOW); 
   }
  void HardLeft(){
    digitalWrite(9,LOW);
    analogWrite(5,110);
    analogWrite(11,110);//RIGHT
    digitalWrite(10,LOW);   
  }   
  void SoftRight(){
    digitalWrite(5,LOW);
    digitalWrite(9,LOW);
    analogWrite(10,110);
    digitalWrite(11,LOW);
     
  }
  void SoftLeft(){
    analogWrite(5,110);//NH LEFT
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    }    
  void Move(float x, float y){
    analogWrite(5,x);
    digitalWrite(9,LOW);
    analogWrite(10,y);
    digitalWrite(11,LOW);
   }
  void Reverse(){
    analogWrite(9,110);
    digitalWrite(5,LOW);
    analogWrite(11,110);
    digitalWrite(10,LOW);
    }
  void Stop(){
    digitalWrite(5,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);    
    }

  /*void thisIsTheEnd(){
    //Stylish Reverse
    digitalWrite(13,HIGH);   //LED ON
    digitalWrite(5,LOW);     //HAULT FOR 10 SECONDS
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);     
    delay(5000);
    flag++;
    digitalWrite(13,LOW);    //LED OFF
    analogWrite(9,110);       //Reverse for 0.5s
    digitalWrite(5,LOW);
    analogWrite(11,100);
    digitalWrite(10,LOW); 
    delay(500);
    digitalWrite(5,LOW);     //Hard Right for 0.2s
    analogWrite(9,110);
    analogWrite(10,100);      //RIGHT
    digitalWrite(11,LOW); 
    delay(200);     
  }
  void thisIsTheEnd2(){
    analogWrite(5,110);       //Move forward to check T or end
    digitalWrite(9,LOW);
    analogWrite(10,100);
    digitalWrite(11,LOW);
    delay(200);
    if(!!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3))//if end
    {
    analogWrite(5,110);      //Move on the box
    digitalWrite(9,LOW);
    analogWrite(10,100);
    digitalWrite(11,LOW);
    delay(400);

    digitalWrite(13,HIGH);   //LED ON
 
    digitalWrite(5,LOW);     //HAULT FOR 10 SECONDS
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);     
    delay(5000);

    digitalWrite(13,LOW);   //LED OFF
    /*                                       //commenting bcs no full scanning
    analogWrite(5,110);      //Move little forward
    digitalWrite(9,LOW);
    analogWrite(10,100);
    digitalWrite(11,LOW);
    delay(200);

    digitalWrite(5,LOW);     //HAULT FOR 3 SECONDS
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);     
    delay(3000);    
    
    HardRight();             //U Turn
    delay(770); 
    
    analogWrite(5,110);       //Move forward 
    digitalWrite(9,LOW);
    analogWrite(10,100);
    digitalWrite(11,LOW);
    delay(750); 
        //Program Back to normal   
   }                        
   else//NOT AN END
   {
     HardRight();
     delay(450);  
   } 
 }*/


void loop()
{
 Pval2 = Pval1;
  val = analogRead(A0);//!digitalRead(A0)
//Serial.println(!digitalRead(A0));
//Serial.println(analogRead(A0));
 

  val = constrain (val, 700, 900);
  map (val, 700, 900, -300, 300);
  Pval1=val;
  P=val*3; // Expirement with this value

  Aval=Aval+val;  // Because we need the values from the start of the program to the instantanious time
  
  I=Aval*0.3;  // See the Integral Discription + Expirement with this value

  Dval=Pval2-val;
  D=Dval*0.3;  // See the Integral Discription + Expirement with this value
  pI=I+P;
  PID=pI+D; // Finally, the PID value

  PWM = 110+PID; // Expirement with the "150" value
  PWM2 = 110-PID;
 if(!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//0
  HardLeft();//no giggling effect in left turns
  //HardRight();//no giggling effects in right turn
 }

 if(!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//1
 /* while(!digitalRead(A0))// Error handling when there is giggling between s4 and s5//Right preference case//HardLeft case//now no giggling effect in right turns 
  {//HardRight
    digitalWrite(5,LOW);
    analogWrite(9,110);
    analogWrite(10,100);//RIGHT
    digitalWrite(11,LOW);  
   }*/
  SoftRight();//required if no exception
 }

 if(!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//2
  /*while(!digitalRead(A0))// Error handling when there is giggling between s3 and s4//Right preference case//HardLeft case//now no giggling effect in right turns 
  {//HardRight
    digitalWrite(5,LOW);    
    analogWrite(9,110);
    analogWrite(10,100);//RIGHT
    digitalWrite(11,LOW);   
   }*/
  SoftRight();//required if no exception
 }

 if(!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//3
  HardRight();
 }

 if(!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//4
  Move(PWM,PWM2);
 }

 if(!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//5
  Reverse();
 }

 if(!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//6
 // Reverse();
 Move(PWM,PWM2);
 }

 if(!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//7
  SoftRight();
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//8
  SoftLeft();
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//9
  SoftLeft();
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//10
  SoftLeft();
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//11
  SoftLeft();
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//12
  //Reverse();
  Move(PWM,PWM2);
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//13
  //Reverse();
  SoftRight();
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//14
  //Reverse();
  Move(PWM,PWM2);
 }

 if(!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//15
  //Reverse();
  SoftRight();
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//16
  SoftLeft();
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//17
  SoftLeft();
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//18
  SoftLeft();
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//19
  SoftRight();
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//20
  //Reverse();
  Move(PWM,PWM2);
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//21
  //Reverse();
  SoftRight();
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//22
  //Reverse();
  Move(PWM,PWM2);
 }

 if(!!digitalRead(7)&&!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//23
  //Reverse();
  SoftRight();
 }

 if(!!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//24
  SoftLeft();
 }

 if(!!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//25
  SoftLeft();
 }

 if(!!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//26
   SoftLeft();
 }

 if(!!digitalRead(7)&&!!digitalRead(6)&&!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//27
  while(!digitalRead(A0))
    SoftRight();
 }
 
 if(!!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!digitalRead(3)){//28
  //Move();
 while(!!digitalRead(A0))
  SoftLeft();
  while(!digitalRead(A0))
  SoftLeft();
 }

 if(!!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!digitalRead(4)&&!!digitalRead(3)){//29
  //Reverse();
  SoftRight();
 }

 if(!!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!digitalRead(3)){//30
 // Reverse();
 Move(PWM,PWM2);
 }

 if(!!digitalRead(7)&&!!digitalRead(6)&&!!digitalRead(A0)&&!!digitalRead(4)&&!!digitalRead(3)){//31
   digitalWrite(13,HIGH);
   Stop();delay(2000);
   digitalWrite(13,LOW);
   while(!!digitalRead(A0))
   Move(PWM,PWM2);
 }
}
