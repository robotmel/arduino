import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial myPort;
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;
PFont orcFont;

void setup() {
  
 size (1440, 810); // ***УСТАНОВКА РАЗРЕШЕНИЯ ЭКРАНА***
 smooth();
 myPort = new Serial(this,"/dev/ttyUSB0", 9600); // ***УСТАНОВКА СЕРИЙНОГО ПОРТА***
 myPort.bufferUntil('.');
 orcFont = loadFont("Ubuntu-48.vlw");
}

void draw() {
  
  fill(98,245,31);
  textFont(orcFont);
  noStroke();
  fill(0,4); 
  rect(0, 0, width, height-height*0.065); 
  fill(98,245,31);
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

void serialEvent (Serial myPort) {
  data = myPort.readStringUntil('.');
  data = data.substring(0,data.length()-1);
  
  index1 = data.indexOf(",");
  angle= data.substring(0, index1);
  distance= data.substring(index1+1, data.length());

  iAngle = int(angle);
  iDistance = int(distance);
}

//Расчёт значения функции синус с помощью рядов Тейлора-Маклорена:

float taysin(float x) {
    float next_term;
    float sumsin=0;
    int next_div_fac=3;
    int i;
    next_term = x;
    for( i=0; i<20; ++i )
    {
        sumsin += next_term;
        next_term *= -1*x*x/(next_div_fac*(next_div_fac-1));
        next_div_fac += 2;
    }
    return sumsin;
}

//Расчёт значения функции косинус с помощью ряда Тейлора-Маклорена:

float taycos(float x) {
    float next_term;
    float sumcos=0;
    int next_div_fac=2;
    int i;
    next_term = 1;
    for( i=0; i<20; ++i )
    {
        sumcos += next_term;
        next_term *= -1*x*x/(next_div_fac*(next_div_fac-1));
        next_div_fac += 2;
    }
    return sumcos;
}

void drawRadar() {
  pushMatrix();
  translate(width/2,height-height*0.074);
  noFill();
  strokeWeight(2);
  stroke(98,245,31);

  arc(0,0,(width-width*0.0625),(width-width*0.0625),PI,TWO_PI);
  arc(0,0,(width-width*0.27),(width-width*0.27),PI,TWO_PI);
  arc(0,0,(width-width*0.479),(width-width*0.479),PI,TWO_PI);
  arc(0,0,(width-width*0.687),(width-width*0.687),PI,TWO_PI);

  line(-width/2,0,width/2,0);
  line(0,0,(-width/2)*taycos(radians(30)),(-width/2)*taysin(radians(30)));
  line(0,0,(-width/2)*taycos(radians(60)),(-width/2)*taysin(radians(60)));
  line(0,0,(-width/2)*taycos(radians(90)),(-width/2)*taysin(radians(90)));
  line(0,0,(-width/2)*taycos(radians(120)),(-width/2)*taysin(radians(120)));
  line(0,0,(-width/2)*taycos(radians(150)),(-width/2)*taysin(radians(150)));
  line((-width/2)*taycos(radians(30)),0,width/2,0);
  popMatrix();
}

void drawObject() {
  pushMatrix();
  translate(width/2,height-height*0.074);
  strokeWeight(9);
  stroke(255,10,10);
  pixsDistance = iDistance*((height-height*0.1666)*0.025);

  if(iDistance<40){

  line(pixsDistance*taycos(radians(iAngle)),-pixsDistance*taysin(radians(iAngle)),(width-width*0.505)*taycos(radians(iAngle)),-(width-width*0.505)*taysin(radians(iAngle)));
  }
  popMatrix();
}

void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30,250,60);
  translate(width/2,height-height*0.074);
  line(0,0,(height-height*0.12)*taycos(radians(iAngle)),-(height-height*0.12)*taysin(radians(iAngle)));
  popMatrix();
}

void drawText() {
  
  pushMatrix();
  if(iDistance>40) {
  noObject = "отсутствует";
  }
  else {
  noObject = "обнаружен";
  }
  fill(0,0,0);
  noStroke();
  rect(0, height-height*0.0648, width, height);
  fill(98,245,31);
  textSize(25);
  
  text("10см",width-width*0.3854,height-height*0.0833);
  text("20см",width-width*0.281,height-height*0.0833);
  text("30см",width-width*0.177,height-height*0.0833);
  text("40см",width-width*0.0729,height-height*0.0833);
  textSize(40);
  text("Объект: " + noObject, width-width*0.875, height-height*0.0277);
  text("Угол: " + iAngle +" °", width-width*0.48, height-height*0.0277);
  text("Расстояние: ", width-width*0.26, height-height*0.0277);
  if(iDistance<40) {
  text("                  " + iDistance +" см", width-width*0.225, height-height*0.0277);
  }
  textSize(25);
  fill(98,245,60);
  translate((width-width*0.4994)+width/2*taycos(radians(30)),(height-height*0.0907)-width/2*taysin(radians(30)));
  rotate(-radians(-60));
  text("30°",0,0);
  resetMatrix();
  translate((width-width*0.503)+width/2*taycos(radians(60)),(height-height*0.0888)-width/2*taysin(radians(60)));
  rotate(-radians(-30));
  text("60°",0,0);
  resetMatrix();
  translate((width-width*0.507)+width/2*taycos(radians(90)),(height-height*0.0833)-width/2*taysin(radians(90)));
  rotate(radians(0));
  text("90°",0,0);
  resetMatrix();
  translate(width-width*0.513+width/2*taycos(radians(120)),(height-height*0.07129)-width/2*taysin(radians(120)));
  rotate(radians(-30));
  text("120°",0,0);
  resetMatrix();
  translate((width-width*0.5104)+width/2*taycos(radians(150)),(height-height*0.0574)-width/2*taysin(radians(150)));
  rotate(radians(-60));
  text("150°",0,0);
  popMatrix(); 
}
