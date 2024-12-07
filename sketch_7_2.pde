import processing.serial.*;
Serial puerto;
color E1 = color (240,218,16);
color E2= color (240,218,16);
color Led1 = color (255,255,255);
color Led2 = color (255,255,255);
void setup()
{
  size(800,500);
  background(#817F7F); 
  puerto = new Serial(this,"COM3",9600);
}

void draw()
{
  //Entrada
  fill(#0087DE);
  strokeWeight(2);
  rect(50,50,150,100);
  
  //E1
  fill(E1);
  strokeWeight(2);
  rect(400,50,100,100);
  
  //E2
  fill(E2);
  strokeWeight(2);
  rect(600,50,100,100);
  
  //Salida
  fill(#F2A920);
  strokeWeight(2);
  rect(50,250,150,100);
  
  //LED1
  fill(Led1);
  strokeWeight(2);
  circle(450,300,100);
  
  //LED2
  fill(Led2);
  strokeWeight(2);
  circle(650,300,100);
  
  //Textos
  textSize(35);
  fill(#050000);
  text("Entradas",60,110);
  text("E1",435,110);
  text("E2",635,110);
  text("Salidas",65,315);
  text("LED1",415,315);
  text("LED2",615,315);
}


void serialEvent (Serial X)
{
  while (puerto.available () == 1)
  {
    char Letra = puerto.readChar();
    print(Letra);
    if(Letra == 'A')
    {
       E1 = color (49,232,59);
       Led1 = color (255,26,26);
    }
    else
    {
      if(Letra == 'C')
      {
       E2 = color (49,232,59);
       Led2 = color (255,26,26);
      }
       else
       {
         if(Letra == 'B')
         {
         E1 = color (240,218,16);
         Led1 = color (255,255,255);
         }
         else
         {
          if(Letra == 'D')
            {
            E2 = color (240,218,16);
            Led2 = color (255,255,255);
          }
        }
      }
    }
  }
}
void mousePressed()
{
  if(pmouseX>400 && pmouseX<500 && mouseY>50 && mouseY<150)
  {
   E1 = color (49,232,59);
   Led1 = color (255,26,26);
   puerto.write('A');
  }
  else
  {
   if (pmouseX>600 && pmouseX<700 && mouseY>50 && mouseY<150)
   {
   E2 = color (49,232,59);
   Led2 = color (255,26,26);
   puerto.write('C');
   }
  }
}

void mouseReleased()
{
  E1 = color(240,218,16);
  Led1 = color(255,255,255);
  puerto.write('B');
  E2 = color(240,218,16);
  Led2 = color(255,255,255);
  puerto.write('D');
}
