int boton1=2;
int boton2=3;
int Led1=8;
int Led2=9;
boolean bot1=false;
boolean bot2=false;

void setup() 
{
  Serial.begin(9600);
  pinMode(boton1,INPUT);
  pinMode(boton2,INPUT);
  pinMode(Led1,OUTPUT);
  pinMode(Led2,OUTPUT);
}

void loop()
{
  if(digitalRead(boton1)==1 && bot1==false)
  {
    Serial.println("A");
    digitalWrite(Led1,HIGH);
    bot1=true;
  }
  else
    if(digitalRead(boton1)==0 && bot1==true)
    {
      Serial.println("B");
      bot1=false;
      digitalWrite(Led1,LOW);
    }
  if(digitalRead(boton2)==1 && bot2==false)
  {
    Serial.println("C");
    digitalWrite(Led2,HIGH);
    bot2=true;
  }
  else
    if(digitalRead(boton2)==0 && bot2==true)
    {
      Serial.println("D");
      digitalWrite(Led2,LOW);
      bot2=false;
    }
    
  if(Serial.available())
  {
    char Letra=Serial.read();
    if(Letra == 'A')
    {
       digitalWrite(Led1,HIGH);
    }
    else
    {
       if(Letra == 'B')
       {
         digitalWrite(Led1,LOW);
       }
       else
       {
         if(Letra == 'C')
         {
            digitalWrite(Led2,HIGH);
         }
         else
         {
           if(Letra == 'D')
           {
              digitalWrite(Led2,LOW);
           }
         }
       }
     } 
    }
  delay(100);
  }
