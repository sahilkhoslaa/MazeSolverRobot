//Pin Connections
int s1=2;
int s2=3;
int s3=4;
int s4=5;
int s5=7;
int s6=8;
int s7=12;
int s8=13;

int r=-1;

int flag=0;
int y=0;
int flag1=0;

int a=0,b=0,c=0,d=0,e=0,f=0;

unsigned char path[1000]={};

int i=0,top=0;
int flag3=0;
int j=145;

float k=1.1*j;

float g=1/1.2;//adjustment Factor

void setup()
{
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(10,OUTPUT);  
  pinMode(11,OUTPUT);
  
  pinMode(12,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(13,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  
  Serial.begin(9600);
  
  for(i=0;i<1000;i++)
    path[i]='X';
}

void pprint()
{
   int x;
   x=top-1;
   
   Serial.print(x);
   Serial.print(" ");
   
   if(path[x]==82) Serial.print("R");
   if(path[x]==66) Serial.print("B");
   if(path[x]==76) Serial.print("L");
   if(path[x]==83) Serial.print("S");
   if(path[x]==77) Serial.print("M");
   if(path[x]==78) Serial.print("N");
   if(path[x]==84) Serial.print("T");
   if(path[x]==89) Serial.print("Y");
   if(path[x]==65) Serial.print("A");
   if(path[x]==85) Serial.print("U");
   
   Serial.print('\n');
   
   if(Serial.available()){}
   
   char val= Serial.read();
}

void ppprint(int x)
{
   Serial.print(x);
   Serial.print(" ");
   if(path[x]==82) Serial.print("R");
   if(path[x]==66) Serial.print("B");
   if(path[x]==76) Serial.print("L");
   if(path[x]==83) Serial.print("S");
   if(path[x]==77) Serial.print("M");
   if(path[x]==78) Serial.print("N");
   if(path[x]==84) Serial.print("T");
   if(path[x]==89) Serial.print("Y");
    if(path[x]==65) Serial.print("A");
     if(path[x]==85) Serial.print("U");
   Serial.print('\n');
}

void straight()
{
    analogWrite(6,0);
    analogWrite(9,j);
    analogWrite(10,0);
    analogWrite(11,j);
}

void Reverse()
{
    analogWrite(6,100);
    analogWrite(9,0);
    analogWrite(10,100);
    analogWrite(11,0);
}

void left()
{
    analogWrite(6,0);
    analogWrite(9,j);
    analogWrite(10,j);
    analogWrite(11,0); 
}

void right()
{
    analogWrite(6,j);
    analogWrite(9,0);
    analogWrite(10,0);
    analogWrite(11,j);  
}

void Stop()
{
    analogWrite(6,0);
    analogWrite(9,0);
    analogWrite(10,0);
    analogWrite(11,0);
}

int calcshortpath()
{
  int y=top-1;
  
  Serial.print("OUTSIDE FOR LOOP");Serial.print('\n');
  int z=1,ch=0,x,getind,i,j,n,fa,k,key,ba,q=0;char temp1,temp2;
  
  for(i=0;(i<y);i++)
  {   
    Serial.print("YOU REACHED IN FOR LOOP");Serial.print(i);Serial.print('\n');
   
    if(path[i]=='U')
    {
      Serial.print("U CHARACTER DETECTDED");Serial.print(++q);Serial.print('\n');
      j=i;
      
      while(!(path[j]==65||path[j]==66||path[j]==77||path[j]==78||path[j]==84||path[j]==89))
      {
        Serial.print("YOU REACHED IN WHILE LOOP");Serial.print('\n');
        j++;
      }
      
      j++;
      fa=j+1;
      n=j-i-1;
      ba=i-n;
      
      temp2=path[j];
      temp1=path[ba];// r=82,s=83,l,76,u=85
      
      Serial.print(temp1);
      Serial.print('\n');
      Serial.print(temp2);
      Serial.print('\n');
      
      if(temp1=='R'&&temp2=='R')
      { 
        if(path[ba-1]=='A')
        path[ba]='S';
        else
        path[ba]='L';
      }
      else if(temp1=='R'&&temp2=='L')
      {
        path[ba]='U';
      }
      else if(temp1=='R'&&temp2=='S')
      {
        path[ba]='L';
      }
      else if(temp1=='L'&&temp2=='L')
      {
        if(path[ba-1]=='B')
        path[ba]='S';
        else
        path[ba]='R';
      }
      else if(temp1=='L'&&temp2=='R')
      {
        path[ba]='U';
      }
      else if(temp1=='L'&&temp2=='S')
      {
        path[ba]='R';
      }
      else if(temp1=='S'&&temp2=='R')
      {
        path[ba]='L';//B
      }
      else if(temp1=='S'&&temp2=='L')
      {
        path[ba]='R';//A
      }
       else if(temp1=='S'&&temp2=='S')
      {
        path[ba]='U';
      }
      
      key=ba-1;
      
      for(x=fa;x<=y;x++)
      {
        path[++ba]=path[x];
      }
      
      y=y-2*n-1;
      
      for(k=0;k<y;k++)
      {
        if(path[k]=='U')
        {
          getind=k;
          getind--;break;
        }
      }
      
      if((path[getind]==65||path[getind]==66||path[getind]==77||path[getind]==78||path[getind]==84||path[getind]==89))
      {
        for(int o=getind;o<y;o++)
        {
          path[o]=path[o+1];
        }
        y--;
      } 
      
      i=0;
      for(i=0;i<=y;i++)
        ppprint(i);
      i=0;
    }
    if(i==y-1)
      return y+1;
  }
  
  return y+1;
}

void loop()
{ 
  //DRY RUN CODE
  flag1=0;  
  flag=0;
 
  if(flag3==0)
  {
    
    if( !digitalRead(s4)&&!digitalRead(s5) || !digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6) || !digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5))
    {
                    //For Straight
                    straight();
  
                    if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6))
                            {
                              //For GIGLING LEFT MOTOR ACTIVATES
                              analogWrite(6,0);  
                              analogWrite(9,j);
                              analogWrite(10,0);
                              analogWrite(11,k);
                            }
                    if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s3))
                            {
                              //For GIGLING RIGHT MOTOR ACTIVATES
                              analogWrite(6,0);
                              analogWrite(9,k);
                              analogWrite(10,0);
                              analogWrite(11,j); 
                            }
                    if(!digitalRead(s6))
                              {
                                analogWrite(6,0);
                                analogWrite(9,0);
                                analogWrite(10,0);
                                analogWrite(11,k);
                              }
                    if(!digitalRead(s3))
                              {
                                  analogWrite(6,0);
                                  analogWrite(9,k);
                                  analogWrite(10,0);
                                  analogWrite(11,0); 
                              }
      }

      if((digitalRead(s1)&&digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&digitalRead(s8))||(digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&digitalRead(s7)&&digitalRead(s8))||(digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&digitalRead(s8)))
      {
              // For Y
              //asliwalaY:
              Stop();
              delay(1000);
              path[top++]='Y';
              pprint();
              straight();
              delay(g*300); 
                        if(f%2==0)
                        {
                          // AT Y if F is even bot Follows RSLB
                           
                          while(digitalRead(s4))
                          {
                            right();
                          }
                          path[top++]='R';
                                 pprint();
                          f++;
                        }
                        else if(f%2!=0)
                        {
                          // AT Y if F is odd bot Follows LSRB
                              
                           while(digitalRead(s5))
                            {
                              left();
                            }
                            path[top++]='L';
                                 pprint();
                          f++;
                        }
      }
    
      if((digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))||(digitalRead(s1)&&digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8)))
      {
          //For RIGHT
          straight();
          delay(g*100);
  
          if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
              goto asliwalaT;
          straight();
          delay(g*200);
          //checking the type of right turn
                      if(!digitalRead(s1)||!digitalRead(s2))
                          goto asliwala135left;
                      straight();
                      delay(g*100);
                      
                      if(!digitalRead(s4)||!digitalRead(s5)){
                          flag++;
                          path[top++]='A';
                          pprint();
                      }
                             if(flag>0&&a%2==0)
                              {
                                    path[top++]='R';
                                    pprint();
                                    // if A is even and bot has to take take decision then bot goes right
                                    do
                                  {
                                    if(flag1==0)                  
                                    {
                                      right();
                                      delay(g*500);
                                      flag1=1;}
                                      right();
                                    }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&digitalRead(s6)&&digitalRead(s7)&&digitalRead(s8)));
                                    a++;
                              }
                             else if(flag>0&&a%2!=0)
                              {
                                    path[top++]='S';
                                    pprint();
                                    // if A is odd and bot has to take take decision then bot goes straight
                                    straight();
                                    delay(g*100);
                                    a++;
                              }
                             else
                             {
                              do
                                {
                                  if(flag1==0)
                                  {
                                    right();
                                    delay(g*500);
                                    flag1=1;}
                                    right();
                                  }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5))); 
                                    path[top++]='R';
                                pprint();
                             }
                      flag=0;
      }
    if((digitalRead(s8)&&digitalRead(s7)&&digitalRead(s6)&&!digitalRead(s5)&&!digitalRead(s4)&&!digitalRead(s3)&&!digitalRead(s2)&&!digitalRead(s1))||(digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s6)&&!digitalRead(s5)&&!digitalRead(s4)&&!digitalRead(s3)&&!digitalRead(s2)&&!digitalRead(s1)))
    {
        //For LEFT
          straight();
          delay(g*100);
    
      if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
          goto asliwalaT; 
      straight();
      delay(g*200);
    
      //checking the type of left turn
                      
                      if(!digitalRead(s7)||!digitalRead(s8))
                          goto asliwala135right;
                      straight();
                      delay(g*100);
                      
                            if(!digitalRead(s4)||!digitalRead(s5))
                            {
                                    flag++;           
                                    path[top++]='B';
                                    pprint();}
                              
                              if(flag>0&&b%2!=0)
                              {  
                                    path[top++]='L';
                                    pprint();
                                    // if B is odd and bot has to take take decision then bot goes straight
                                  do
                                  {
                                    if(flag1==0)                  
                                    {
                                      left();
                                      delay(g*500);
                                      flag1=1;
                                    }
                                    left();
                                  }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5)));
                                    b++;
                              }
                             else if(flag>0&&b%2==0)
                              { 
                                    path[top++]='S';
                                    pprint();
                                    // if B is even and bot has to take take decision then bot goes straight
                                    straight();
                                    delay(g*100);
                                    b++;
                              }
                             else
                             {
                              do
                                {
                                  if(flag1==0)
                                  {
                                    left();
                                    delay(g*500);
                                    flag1=1;}
                                    left();
                                  }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5))); 
                                path[top++]='L';
                                pprint();
                             }
                flag=0;  
}
  //***********************************FOR PERFECT ORIENTATION****************************************
  
                      if(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&digitalRead(s4)&&!digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5))
                              {
                                analogWrite(6,0);
                                analogWrite(9,0);
                                analogWrite(10,0);
                                analogWrite(11,k);
                              }
                      
                      if(digitalRead(s1)&&digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&digitalRead(s5))
                              {
                                  analogWrite(6,0);
                                  analogWrite(9,k);
                                  analogWrite(10,0);
                                  analogWrite(11,0); 
                              }
    
   //****************************************************************************************************
  
    if(!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
     {
    
     
    asliwalaT:
        //For T
        //Stop();
        //delay(5000);
    path[top++]='T';
    pprint();
    straight();
    delay(g*200);
          if(!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
                      {
                        //REACHED END
                        Stop();
                        delay(9999);
                        flag3=1; 
                           goto code0;                   
                      }
            //if((digitalRead(s4)&&(!digitalRead(s1)||!digitalRead(s2)))||(digitalRead(s4)&&(!digitalRead(s7)||!digitalRead(s8)))||(digitalRead(s5)&&(!digitalRead(s1)||!digitalRead(s2)))||(digitalRead(s5)&&(!digitalRead(s7)||!digitalRead(s8))))
            // goto asliwalaY;
      straight();    
      delay(g*100);
                      if(c%2==0)
                         {       path[top++]='R';
                                 pprint();
                                  // Bot reached T following RSLB rule when C is even
                                 do
                                 {
                                  if(flag1==0)
                                  {
                                    right();
                                    delay(g*500);
                                    flag1=1;
                                  }
                                  right();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5)));
                                 
                         }
                      else if(c%2!=0)
                        {        path[top++]='L';
                                 pprint();
                                  // Bot reached T following LSRB rule when C is odd
                                 do
                                 {
                                  if(flag1==0)
                                  {
                                    left();
                                    delay(g*500);
                                    flag1=1;
                                  }
                                  left();
                                 }
                                 while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5)));
                                 
                        }
                        c++;
                       
      }

    if(digitalRead(s4)&&digitalRead(s5)&&digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&digitalRead(s6)&&digitalRead(s7)&&digitalRead(s8))
    {
      //U TURN
      
      path[top++]='U';
      pprint();                            //RBRBLBL
      straight();
      delay(g*200);
      while(digitalRead(s4))
      {
        right();
      }
    }
    if(0)
    { //For 135 deg right and 90 deg left
      asliwala135right:
      path[top++]='N';
      pprint();
      //Stop();delay(9999); 
      straight();
      delay(g*120);
                       if(d%2==0)
                       {
                          path[top++]='R';
                          pprint();
                       
                          right();
                          delay(g*10);
                          while(digitalRead(s4))
                           {
                           right();
                           }
                           d++;
                        }
                        else if(d%2!=0)
                        {
                          path[top++]='L';
                          pprint();
                                do
                                {
                                  if(flag1==0)                  
                                  {
                                    left();
                                   delay(g*500);
                                   flag1=1;
                                  }
                                   left();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)));                    
                            d++;  
                          }
    }
    if(0)
    {
      //For 135 deg left and 90 deg right
      asliwala135left:
      //Stop();delay(9999);  
      path[top++]='M';
      pprint();
      straight();delay(g*120);
  

                            if(e%2==0)
                            {
                       
                                    path[top++]='R';
                                    pprint();
                                do
                                {
                                  if(flag1==0)                  
                                  {
                                    right();
                                    delay(250);
                                    flag1=1;
                                  }
                                    right();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)));
                              e++;
                            }
                        else //if(e%2!=0)
                        {
                        
                          path[top++]='L';
                          pprint();
                          e++;
                        
                            left();
                            delay(g*10);
                        
                          while(digitalRead(s5))
                          {
                            left();
                          }
                        }  
    }
    
  /*if(path[0]==82&&path[1]==66&&path[2]==82)
  {
    Stop();
    delay(5000);
    path[0]='S';
    flag3=1;
  }*/
    
}
 
 f(flag3==1)
 {
   
   code0:
   Stop();
   delay(5000);
   
   for(i=0;i<top;i++)
      ppprint(i);
   
   Serial.print(top);
   Serial.print('\n');
   top=calcshortpath();
   Serial.print('\n');Serial.print('\n');Serial.print(top);
   for(i=0;i<top;i++)
      ppprint(i); 
   Serial.print('\n');Serial.print('\n');Serial.print('\n');Serial.print('\n');Serial.print('\n');
   flag3=2;
   goto code2;
 }

//Shortest path
if(flag3==2)
{ 
  code2:
  
   if( !digitalRead(s4)&&!digitalRead(s5) || !digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6) || !digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5))
  {
    //For Straight
    
    straight();
  
                    if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6))
                            {
                              //For GIGLING LEFT MOTOR ACTIVATES
                              analogWrite(6,0);
                              analogWrite(9,j);
                              analogWrite(10,0);
                              analogWrite(11,k);
                            }
                    if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s3))
                            {
                              //For GIGLING RIGHT MOTOR ACTIVATES
                              analogWrite(6,0);
                              analogWrite(9,k);
                              analogWrite(10,0);
                              analogWrite(11,j); 
                            }
                        if(!digitalRead(s6))
                              {
                                analogWrite(6,0);
                                analogWrite(9,0);
                                analogWrite(10,0);
                                analogWrite(11,k);
                              }
                        if(!digitalRead(s3))
                              {
                                  analogWrite(6,0);
                                  analogWrite(9,k);
                                  analogWrite(10,0);
                                  analogWrite(11,0); 
                              }
  }

   if((digitalRead(s1)&&digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&digitalRead(s8))||(digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&digitalRead(s7)&&digitalRead(s8))||(digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&digitalRead(s8)))
  {
    // For Y
    //asliwalaY:
    //Stop();
    //delay(1000);
   
    straight();
    delay(g*300); 
    
                      if(rPointer()=='L')
                      f=1;
                      else 
                      f=0;    
    
                        if(f%2==0)
                        {// AT Y if F is even bot Follows RSLB
                           
                          while(digitalRead(s4))
                          {
                            right();
                          }
                         
                                
                          
                        }
                        else if(f%2!=0)
                        {// AT Y if F is odd bot Follows LSRB
                              
                           while(digitalRead(s5))
                          {
                            left();
                          }
                         
                               
                         
                        }
  }
  if((digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))||(digitalRead(s1)&&digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8)))
  {
    //For RIGHT
    straight();
    delay(g*100);
    if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
    goto asliwalaT2;
    straight();
    delay(g*200);
    //checking the type of right turn
                      if(!digitalRead(s1)||!digitalRead(s2))
                      goto asliwala135left2;
                      straight();
                      delay(g*100);
                      if(!digitalRead(s4)||!digitalRead(s5))
                      {
                        flag++;
                      
                        if(rPointer()=='S')
                          a=1;
                        else 
                          a=0;   
                              
                        }
                       if(flag>0&&a%2==0)
                       {   
                                
                                // if A is even and bot has to take take decision then bot goes right
                                do
                                {
                                  if(flag1==0)                  
                                  {
                                    right();
                                    delay(g*500);
                                    flag1=1;
                                  }
                                   right();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&digitalRead(s6)&&digitalRead(s7)&&digitalRead(s8)));
                              a++;
                              }
                             else if(flag>0&&a%2!=0)
                              {    
                              
                                // if A is odd and bot has to take take decision then bot goes straight
                               straight();
                               delay(g*100);
                               a++;
                              }
                             else
                             {
                              do
                                {
                                  if(flag1==0)
                                  {right();
                                   delay(g*500);
                                   flag1=1;}
                                   right();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5))); 
                             
                                  
                             }
    flag=0;
    }
  if((digitalRead(s8)&&digitalRead(s7)&&digitalRead(s6)&&!digitalRead(s5)&&!digitalRead(s4)&&!digitalRead(s3)&&!digitalRead(s2)&&!digitalRead(s1))||(digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s6)&&!digitalRead(s5)&&!digitalRead(s4)&&!digitalRead(s3)&&!digitalRead(s2)&&!digitalRead(s1)))
  {
    //For LEFT
    straight();
    delay(g*100);
    if(!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
    goto asliwalaT2; 
    straight();
    delay(g*200);
    
    //checking the type of left turn
                      
                      if(!digitalRead(s7)||!digitalRead(s8))
                      goto asliwala135right2;
                      straight();
                      delay(g*100);
                      if(!digitalRead(s4)||!digitalRead(s5)){
                      flag++;           
                        if(rPointer()=='L')
                      b=1;
                      else 
                      b=0;   
                                  
                                 }
                              if(flag>0&&b%2!=0)
                              {   
                                   
                                // if B is odd and bot has to take take decision then bot goes straight
                                do
                                {
                                  if(flag1==0)                  
                                  {left();
                                   delay(g*500);
                                   flag1=1;}
                                   left();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5)));
                              b++;
                              }
                             else if(flag>0&&b%2==0)
                              {   
                                  
                                // if B is even and bot has to take take decision then bot goes straight
                               straight();
                               delay(g*100);
                               b++;
                              }
                             else
                             {
                              do
                                {
                                  if(flag1==0)
                                  {left();
                                   delay(g*500);
                                   flag1=1;}
                                   left();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5))); 
                            
                                  
                             }
 flag=0;  
}
  //***********************************FOR PERFECT ORIENTATION****************************************
  
                      if(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&digitalRead(s4)&&!digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5))
                              {
                                analogWrite(6,0);
                                analogWrite(9,0);
                                analogWrite(10,0);
                                analogWrite(11,k);
                              }
                      
                      if(digitalRead(s1)&&digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&digitalRead(s5))
                              {
                                  analogWrite(6,0);
                                  analogWrite(9,k);
                                  analogWrite(10,0);
                                  analogWrite(11,0); 
                              }
   //****************************************************************************************************
  
  if(!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
  {
    asliwalaT2:
    //For T
     //Stop();
    //delay(5000);
   

    straight();
    delay(g*200);
          if(!digitalRead(s1)&&!digitalRead(s2)&&!digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&!digitalRead(s6)&&!digitalRead(s7)&&!digitalRead(s8))
                      {
                        //REACHED END
                        Stop();
                        delay(9999);
                        flag3=4;                    
                      }
          //if((digitalRead(s4)&&(!digitalRead(s1)||!digitalRead(s2)))||(digitalRead(s4)&&(!digitalRead(s7)||!digitalRead(s8)))||(digitalRead(s5)&&(!digitalRead(s1)||!digitalRead(s2)))||(digitalRead(s5)&&(!digitalRead(s7)||!digitalRead(s8))))
           // goto asliwalaY;
      straight();    
      delay(g*100);
      
        if(rPointer()=='R')
                      c=0;
                      else 
                      c=1;   
                      if(c%2==0)
                         {      
                             
                           // Bot reached T following RSLB rule when C is even
                                 do
                                 {
                                  if(flag1==0)
                                  {right();
                                  delay(g*500);
                                  flag1=1;}
                                  right();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5)));
                                 
                         }
                      else if(c%2!=0)
                        {        
                                 
                          // Bot reached T following LSRB rule when C is odd
                                 do
                                 {
                                  if(flag1==0)
                                  {left();
                                  delay(g*500);
                                  flag1=1;}
                                  left();
                                 }
                                 while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)&&!digitalRead(s5)));
                                 
                        }
                        c++;
                       
  }

  if(digitalRead(s4)&&digitalRead(s5)&&digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&digitalRead(s6)&&digitalRead(s7)&&digitalRead(s8))
  {
    //U TURN     
     
                              //RBRBLBL
      straight();
      delay(g*200);
      while(digitalRead(s4))
      {
        right();
      }
}
  if(0)
  {
    //For 135 deg right and 90 deg left
    asliwala135right2:
  
 
    //Stop();delay(9999); 
    straight();
    delay(g*120);
  
                    if(rPointer()=='L')
                        d=1;
                    else 
                        d=0;   
                   
                     if(d%2==0)
                     {

                       
                       
                       right();
                       delay(g*10);
                       while(digitalRead(s4))
                           {
                           right();
                           }
                           d++;
                     }
                     else if(d%2!=0)
                     {
                                do
                                {
                                  if(flag1==0)                  
                                  {
                                    left();
                                    delay(g*500);
                                    flag1=1;
                                  }
                                    left();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)));                    
                   d++;  
                   }
    } 
    if(0)
    {
                      //For 135 deg left and 90 deg right
                      asliwala135left2:
                      //Stop();delay(9999);  


                      straight();delay(g*120);
  
                      if(rPointer()=='L')
                        e=1;
                      else 
                        e=0;   
                            if(e%2==0)
                          {
                                do
                                {
                                  if(flag1==0)                  
                                  {
                                    right();
                                    delay(250);
                                    flag1=1;
                                  }
                                   right();
                                }
                                while(!(digitalRead(s1)&&digitalRead(s2)&&digitalRead(s3)&&!digitalRead(s4)&&!digitalRead(s5)&&digitalRead(s6)&&digitalRead(s8)&&digitalRead(s7)));
                            e++;
                          }
                        else //if(e%2!=0)
                        {
                        
                          e++;
                        
                            left();
                            delay(g*10);
                            while(digitalRead(s5))
                            {
                                left();
                            }
                        }  
                  }
  
    }
}

/*void shortpath()
{  label:
  if(path[y]==83)
  {
    straight();
    delay(500);
    y++;
  }
  else if(path[y]==82)
  {
    straight();
    delay(400);
    right();
    delay(500);
    while(digitalRead(s4))
    {
      right();
    }
    y++;
  }
  else if(path[y]==76)
  {
    straight();
    delay(400);
    left();
    delay(500);
    while(digitalRead(s5))
    {
      left();
    }
    y++;
  }
  //else if(path[y]==65||path[y]==66||path[y]==77||path[y]==78||path[y]==84||path[y]==89)
  //{
    //y++;
    //goto label;
  //}
}*/

char rPointer()
{

     for(i=r+1;1;++i)
     {
       if(path[i]==65||path[i]==66||path[i]==77||path[i]==78||path[i]==84||path[i]==89)
       {
         r=i+1;
         break;
       }
     }
  
        ppprint(r-1);
        ppprint(r);
        Serial.print('\n');
        return path[r];  
}
  
  
  
  
