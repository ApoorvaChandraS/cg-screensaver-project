#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include "ScreenSaver.c"
#define pi 3.14159263
#include<string.h>

//Global declarations and prototypes
int count = 0;
int xa,ya,xb,yb,xc,yc,xd,yd;

void motion(int x, int y);	// a rubberbanding procedure

int glbx,glby,id;//id is id number of a window where we 'play with Mr.smiles'
float smred=1,smgreen=1,smblue=0;

float b_red=25, b_green=25, b_blue=25;
int prtw1=0;

struct pos{   // data structure used for rubber banding
float x;
float y;
int s;
};
typedef struct pos pos;

pos strt, fin;

struct color{

float r;
float g;
float b;
};

typedef struct color color;

color red, green, blue;

void colorInit()
{
red.r = asin(1);  // a red colour
red.g = acos(0);
red.b = asin(0);

green.r = asin(0);//a green colour 
green.g = acos(1);
green.b = asin(0);

blue.r = asin(0); // a blue colour
blue.g = acos(0);
blue.b = asin(1);

}

struct button{ // buttons made

int w1;//button width
int w2;
int h1;//button height
int h2;
};

typedef struct button button;

button b1, b2, b3,b4;
//j is the obId



void triangularBoundary(int j,int prt)//to draw the triangluar boundary
{
 glColor3f(b_green,b_blue,b_red);
 if(j==2)
 {
 //for(prt=0; prt < 70; prt=prt+2)//loop from left to right at top
 //{
 glBegin(GL_POLYGON);
 glVertex2f(-35+prt,35);
 glVertex2f(-33+prt,33);
 glVertex2f(-35+prt,31);
 glEnd();
 //}
 
 }
 if(j==3)
 {
 //for(prt=0; prt < 70; prt=prt+2)//loop from top to bottom at right
 //{
 glBegin(GL_POLYGON);
 glVertex2f(35,-35+prt);
 glVertex2f(33,-33+prt);
 glVertex2f(31,-35+prt);
 glEnd();
 //}
 }
 if(j==4)
{
 //for(prt=0; prt < 70; prt=prt+2)//loop from left to right at top
 //{
 glBegin(GL_POLYGON);
 glVertex2f(-35+prt,-35);
 glVertex2f(-33+prt,-33);
 glVertex2f(-35+prt,-31);
 glEnd();
 //}
 }
 if(j==5)
{
 //for(prt=0; prt < 70; prt=prt+2)//loop from left to right at top
 //{
 glBegin(GL_POLYGON);
 glVertex2f(-35,-35+prt);
 glVertex2f(-33,-33+prt);
 glVertex2f(-31,-35+prt);
 glEnd();
 //}
}
 glFlush();  

}




void buttonInit()
{
//Initialize Buttons
b1.w1=-10;
b1.w2=10;
b1.h1=-28;
b1.h2=-24;


b2.w1=-10;
b2.w2=10;
b2.h1=-23;
b2.h2=-19;

b3.w1 = -10;
b3.w2 = 10;
b3.h1 = -33;
b3.h2 = -29;


b4.w1=-10;
b4.w2=10;
b4.h1=-28;
b4.h2=-24;

//Buttons are initialized
}


int i;

struct dispFile
{
    int op;	//tells whether circle(0) triangle(2) or arc(1) is to be drawn (OpCodes)
    float x0;	// center in case of circle endpt in case of a line
    float y0;
    float x;
    float y;
    float r;	//radius
    int obID;	//object ID

};


void drawarc(float xa,float ya,float rd,int callfrom)//function to draw an arc for given centre (xa,ya)
{
  float k=rd-2;
  float j,rad,r;

  if(rd>13&&callfrom==1)
  ya=ya-22;
  if((ya>0||callfrom==0)||ya<0&&rd<13)//happy smiley face
  { 
  for(r=k;r<=k+rd/20;r+=0.01)
  {
  glBegin(GL_LINES);
  for(j=210;j<=330;j+=0.1)
  {
   rad=j*3.14159263/180;
   glVertex2f(xa+r*cos(rad),ya+r*sin(rad));
  }
 glEnd();
 }
 }
 else if(ya<0&&callfrom==1)//sad smiley face
 {
  for(r=k;r<=k+rd/20;r+=0.01)
  {
  glBegin(GL_LINES);
  for(j=50;j<=130;j+=0.1)
  {
   rad=j*3.14159263/180;
   glVertex2f(xa+r*cos(rad),ya+r*sin(rad));
  }
 glEnd();
 } 
 }
glFlush();
}


void dispWrite()
{
    int prt=0; //For the triangular boundary
    int i,k=5;
    FILE* fd=NULL;
    struct dispFile d;
    fd = fopen("smidisplay.txt","w");
    for(i=1;i<=284;i++)	//4 + 70*(4)
     {
      if(i<4)
      d.op=0;
      
      if(i==1)//face of the smiley
      {
      d.x0=glbx;
      d.y0=glby;
      d.x=glbx;
      d.y=glby;
      d.r=10;
      d.obID=1;
      }
      if(i==2)//left eye
      {
      d.x0=glbx-5;
      d.y0=glby+8-5;
      d.x=glbx-5;
      d.y=glby+8-5; 
      d.r=1;
      d.obID=2;
      }
      if(i==3)//right eye
      {
      d.x0=glbx+5;
      d.y0=glby+8-5;
      d.x=glbx+5;
      d.y=glby+8-5;
      d.r=1;
      d.obID=3;
      }
      if(i==4)//mouth of the smiley
      {
      d.op=1;
      d.x0=glbx;
      d.y0=glby;
      d.x=glbx;
      d.y=glby;
      d.r=10;
      d.obID=4;
      }
      
      if(i>4)//triangular boundary 
      {
      if(i==5)
      d.op=2;
      
      d.x0=prt;
      d.y0=glby;
      d.x=glbx;
      d.y=glby;
      d.r=10;
      
      prt+=2;
      if(prt>=70)
      {
      	prt=0;	
      	d.op+=1;
      }
      
      d.obID=k;
      k++;  
      }  
      fprintf(fd,"%d %f %f %f %f %f %d\n",d.op,d.x0,d.y0,d.x,d.y,d.r,d.obID);//write into the file
     }
  fclose(fd);
}

void button2Draw()
{

 glColor3f(b_red,b_green,b_blue);
 glBegin(GL_POLYGON);
 glVertex2f(b2.w1,b2.h1);
 glVertex2f(b2.w2,b2.h1);
 glVertex2f(b2.w2,b2.h2);
 glVertex2f(b2.w1,b2.h2);
 glEnd();


//Writing Text
glColor3f(0,0,0);
char text2[]="Smiley Color";
glRasterPos2i(-8,-21);
for(i = 0; i < strlen(text2); i++)
{ 
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
}
glFlush();
}




void startscreen()
{

  FILE* fp;
 struct dispFile d;
 fp=fopen("smidisplay.txt","r");
 if(fp==NULL)
 printf("\nError in reading the file\n");
 else
 {
 glClear(GL_COLOR_BUFFER_BIT);
 while(fscanf(fp,"%d%f%f%f%f%f%d\n",&d.op,&d.x0,&d.y0,&d.x,&d.y,&d.r,&d.obID)!=EOF)//read until end of file
 {
 switch(d.op)
 {
 case 0:
 radius=d.r;
 if(radius>2)
 drawCircle(d.x0,d.y0,smred,smgreen,smblue,0);	//This is the face of the smiley
 else
 drawCircle(d.x0,d.y0,0,pi/2,0,0);	// This draws the 2 eyes
 break;
 case 1:  //for drawing an arc opcode is 1
 drawarc(d.x0,d.y0,10,0);
 break;
 default :
 triangularBoundary(d.op,d.x0);	//d.x0 contains prt
 break;
 } 
 }

//Button 1
 glColor3f(1,1,1);//start screen saver button
 glBegin(GL_POLYGON);
 glVertex2f(b1.w1,b1.h1);
 glVertex2f(b1.w2,b1.h1);
 glVertex2f(b1.w2,b1.h2);
 glVertex2f(b1.w1,b1.h2);
 glEnd();


//Writing Text
glColor3f(0,0,0);
glRasterPos2i(-9,-26);
char text[]="Start Screen Saver";
 for(i = 0; i < strlen(text); i++)
{ 
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

//Button 2
button2Draw();//drawn separetely to show smiley color instantaneosly when the button is clicked 

//Button 3
 glColor3f(1,1,1);//play with Mr.smiles
 glBegin(GL_POLYGON);
 glVertex2f(b3.w1,b3.h1);
 glVertex2f(b3.w2,b3.h1);
 glVertex2f(b3.w2,b3.h2);
 glVertex2f(b3.w1,b3.h2);
 glEnd();

 //Writing Text
glColor3f(0,0,0);
glRasterPos2i(-9,(b3.h1+b3.h2)/2);
char text3[]="Play With Mr.Smiles";
 
 for(i = 0; i < strlen(text3); i++)
{ 
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text3[i]);
}

glFlush();  
 }
}

void smileyMouse(int button,int state,int x,int y)//mouse callback for smiley play window  
{


 if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
 {
 

  y=600-y;  //Converting from Computer perspective to Human Perspective


//Push each value based on its Quadrant
  if(x==300)
  x=0;

  else if(x>300)
  x=x-300;

  else
  x=-(300-x);

  if(y==300)
  y=0;

  else if(y>300)
  y=y-300;

  else
  y=-(300-y);

  glbx=x/8.57;
  glby=y/8.57;
  
  if((glbx>=b4.w1&&glbx<=b4.w2)&&(glby>=b4.h1&&glby<=b4.h2))//exit play 
  {
   if(button==GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
     glutDestroyWindow(id);
  }
  
  else{
  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_XOR);
  strt.x=glbx;
  strt.y=glby;
  fin.x=glbx;
  fin.y=glby;
  }
  }
 }

 void smileyDisplay()
 {
 int i;
  glColor3f(1,1,1);
 glBegin(GL_POLYGON);
 glVertex2f(b4.w1,b4.h1);
 glVertex2f(b4.w2,b4.h1);
 glVertex2f(b4.w2,b4.h2);
 glVertex2f(b4.w1,b4.h2);
 glEnd();
 //Writing Text
glColor3f(0,0,0);
glRasterPos2i(-9,(b4.h1+b4.h2)/2);
char text4[]="Exit play";
 for(i = 0; i < strlen(text4); i++)
 { 
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text4[i]);
 } 
 glFlush();
 }

void clipWindow(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd)
{

glColor3f(0,0,0);
glBegin(GL_POLYGON);
glVertex2f(xa,ya);
glVertex2f(xb,yb);
glVertex2f(xc,yc);
glVertex2f(xd,yd);
glEnd();
glFlush();

}


void mymouse(int button,int state,int x, int y)	//Mouse handler for positioning smiley on opening screen
{

int k;
static int flag=0;

 if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
 {
 

  y=600-y;  //Converting from Computer perspective to Human Perspective


//Push each value based on its Quadrant
  if(x==300)
  x=0;

  else if(x>300)
  x=x-300;

  else
  x=-(300-x);

  if(y==300)
  y=0;

  else if(y>300)
  y=y-300;

  else
  y=-(300-y);

  glbx=x/8.57;
  glby=y/8.57;


  if((glbx>=b1.w1&&glbx<=b1.w2)&&(glby>=b1.h1&&glby<=b1.h2))
  {
  glutInitWindowSize(600,600); 
  glutCreateWindow("Screen saver");  
  Init();
  glutDisplayFunc(display);
  //glutKeyboardFunc(keyboard);
  }
  
  else if((glbx>=b3.w1&&glbx<=b3.w2)&&(glby>=b3.h1&&glby<=b3.h2))
  {
  glutInitWindowSize(600,600);
  id=glutCreateWindow("Smiley Play");
  Init();
  glutDisplayFunc(smileyDisplay);
  glutMouseFunc(smileyMouse);
  //glutKeyboardFunc(keyboard);
  glutMotionFunc(motion);
  }
  
  else if((glbx>=b1.w1&&glbx<=b2.w2)&&(glby>=b2.h1&&glby<=b2.h2))
  {

  srand(time(0)+rand());
  k = rand()%50;


 if(k%3==0)
{
 b_red = red.r;
 b_green = red.g;
 b_blue = red.b;
}

else if(k%3==1)
{
 b_red = green.r;
 b_green = green.g;
 b_blue = green.b;
}

else
{
 b_red = blue.r;
 b_green = blue.g;
 b_blue = blue.b;
}


smred = b_red;
smgreen = b_green;
smblue = b_blue;


  b_red = sin(b_red);
  b_green = cos(b_green);
  b_blue = sin(b_blue);

//printf("r : %f\t g : %f\t b : %f\n",b_red, b_green, b_blue);

  button2Draw();
  
  } 
  else
  {
  dispWrite();
  startscreen();
  }
 }

  else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
{

	y=600-y;  //Converting from Computer perspective to Human Perspective


//Push each value based on its Quadrant
  if(x==300)
  x=0;

  else if(x>300)
  x=x-300;

  else
  x=-(300-x);

  if(y==300)
  y=0;

  else if(y>300)
  y=y-300;

  else
  y=-(300-y);

  x=x/8.57;
  y=y/8.57;

 if(count==0)
{
  if(flag==1)
{
  startscreen();
  flag=0;
}

  xa = x;
  ya = y;
  count++;
  radius = 0.5;
  drawCircle(xa,ya,asin(1),acos(1),asin(1),0);
}

 else if(count==1)
{
  xb = x;
  yb = y;
  count++;
  radius = 0.5;
  ddaline(xa,ya,xb,yb,asin(1),acos(0),asin(0));
  drawCircle(xb,yb,asin(1),acos(1),asin(1),0);
}

 else if(count==2)
{
  xc = x;
  yc = y;
  count++;
  radius = 0.5;
  ddaline(xb,yb,xc,yc,asin(1),acos(0),asin(0));
  drawCircle(xc,yc,asin(1),acos(1),asin(1),0);
}

 else if(count==3)
{
  xd = x;
  yd = y;

  radius = 0.5;
  ddaline(xc,yc,xd,yd,asin(1),acos(0),asin(0));
  ddaline(xd,yd,xa,ya,asin(1),acos(0),asin(0));
  drawCircle(xd,yd,asin(1),acos(1),asin(1),0);
  flag = 1;
  count = 0;
  
}


}
  
}

void keyboard(unsigned char key, int x, int y)
{
  if(key=='c')
{
 startscreen();
 clipWindow(xa,ya,xb,yb,xc,yc,xd,yd);
}

}


void drawSmiley(float xc, float yc, float r)
{
drawCircle(xc,yc,pi/2,0,0,0);
radius = r/10;
drawCircle(xc-r/2,yc+r/3,pi/2,0,pi/2,0);
radius=r/10;
drawCircle(xc+r/2,yc+r/3,pi/2,0,pi/2,0);
drawarc(xc,yc,r,1);

glFlush();
}

void motion(int x, int y)
{
float xc, yc, myradius;
//Repeat the coordinate conversions

 y=600-y;  //Converting from Computer perspective to Human Perspective


//Push each value based on its Quadrant
  if(x==300)
  x=0;

  else if(x>300)
  x=x-300;

  else
  x=-(300-x);

  if(y==300)
  y=0;

  else if(y>300)
  y=y-300;

  else
  y=-(300-y);
  
  x=x/8.57;
  y=y/8.57;
//Conversions done


//Euclid's Distance Formula
myradius = sqrt((fin.x-strt.x)*(fin.x-strt.x)+(fin.y-strt.y)*(fin.y-strt.y))/2;
xc = (fin.x+strt.x)/2;
yc = (fin.y+strt.y)/2;
//We now have centre and radius

radius = myradius;
drawSmiley(xc, yc, myradius);	

fin.x = x;
fin.y = y;

myradius = sqrt((fin.x-strt.x)*(fin.x-strt.x)+(fin.y-strt.y)*(fin.y-strt.y))/2;
xc = (fin.x+strt.x)/2;
yc = (fin.y+strt.y)/2;

radius = myradius;

drawSmiley(xc,yc,myradius);
glFlush();
}


int main(int argc,char **argv)
{

 buttonInit();
 colorInit(); 
 glutInit(&argc,argv);
 glutInitWindowSize(600,600); 
 glutCreateWindow("Screen saver");  
 Init();
 glutDisplayFunc(startscreen);
 glutMouseFunc(mymouse);
 glutKeyboardFunc(keyboard);
 glutMainLoop();
}
