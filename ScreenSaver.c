#include<GL/glut.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include "circle.c"
#include "TeamName.c"
#include "triangle.c"
int counter=0;

struct randomnumbers  // a data structure to hold random color for the three different shapes
{
 float redc,greenc,bluec,reds,blues,greens,redt,greent,bluet; 
}rns;

struct coordinategenerator
{
 int x1,y1,x2,y2,x3,y3,x4,y4;
}cog; 
//function mechanism or method of working: 
// first  psedo random number generator is seeded with a different value each time so that
// it generates a different random number
// the number is adjusted accordingly to suit the range of colors


struct randomnumbers generateRandomColor()// a function to generate the random colors for shapes
{
 int j;
 srand(time(0));
 j=rand()%10;
 rns.redc=j*10/2.6;   //red component of circle
 srand(time(0));
 j=rand()%10;
 rns.greenc=j*10/3;  //green component of circle
 srand(time(0));
 j=rand()%10;
 rns.bluec=j*10/7.4;    // blue component of circle
  

//square's colours
 srand(time(0));  // seeding of the pseudo random number generator
 j=rand()%10;              // generation of a random number in the range 0-9 
 rns.reds=j*10/2.6;
 srand(time(0));
 j=rand()%10;
 rns.greens=j*10/3;
 srand(time(0));
 j=rand()%10;
 rns.blues=j*10/7.4;
 
//traingles's colours 
 srand(time(0));
 j=rand()%10;
 rns.redt=j*10/7.8;
 srand(time(0));
 j=rand()%10;
 rns.greent=j*10/3.6;
 srand(time(0));
 j=rand()%10;
 rns.blues=j*10/4.5;
 return rns;
}


void Init()//initiliase the screen dimensions
{
 glClear(GL_COLOR_BUFFER_BIT);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-35,35,-35,35);
}


void smallDelay()// to create a small time delay less than 1s
{
 int i,j,k;
 for(i=0;i<=1000;i++)
 for(j=0;j<=1000;j++);
}

struct coordinategenerator decideScreen()//function to decide the bouncing coordinates for each shape
{
 int decider;

 //generation of the first bounce point 
 srand(time(0));
 cog.x1=27+(rand()%5);//very close to the rightmost corner of the screen
 smallDelay();
 smallDelay();
 srand(time(0));
 cog.y1=rand()%17;
 srand(time(0)+rand()%655);
 decider=rand()%3;
 if(decider==0)
 cog.y1=-cog.y1;
 else if(decider==1)
 cog.y1=cog.y1;
 else
 cog.y1=0;


 smallDelay();
 smallDelay();
 srand(time(0));

 //generation of 
 cog.x2=rand()%20;
 srand(time(0)+rand()%14);
 decider=rand()%3;
 if(decider==0)
 cog.x2=cog.x2;
 else if(decider==1)
 cog.x2=-cog.x2;
 else
 cog.x2=0;
 smallDelay();  
 smallDelay();
 srand(time(0));//make the random number seeder take different time 
 cog.y2=28+(rand()%5); //very close to the topmost corner of the screen 
 smallDelay();
 smallDelay();
 srand(time(0));
 cog.x3=-27-(rand()%7);//very close to the leftmost corner of the screen
 srand(time(0));
 cog.y3=rand()%25;
 smallDelay();
 smallDelay();
 srand(time(0));
 decider=rand()%3;
 if(decider==0)
 cog.y3=0;
 else if(decider==1)
 cog.y3=cog.x2;
 else
 cog.y3=-cog.y3;
 srand(time(0)+rand()%rand()); 
 cog.y4=-27-(rand()%7);
 smallDelay();
 smallDelay();
 srand(time(0));
 cog.x4=rand()%26;
 srand(time(0)+rand()%rand());
 decider=rand()%3;
 if(decider==0)
 cog.x4=0;
 else if(decider==1)
 cog.x4=-cog.x2;
 else
 cog.x2=cog.x2;
 return cog;
}


void linepath(float x1,float y1,float x2,float y2)//function tht generates points on a straight line 
{                                                 // through (x1,y1) and (x2,y2) for the shapes to move  
 static int shapeDecider=0;                       //using digital differential analyser algorithm 
 struct randomnumbers r;
 radius=7;
 r=generateRandomColor();
 float steps,dx,dy,xinc,yinc,k,x,y,ang=0;
 dx=x2-x1;
 dy=y2-y1;
 
if(abs(dx)>abs(dy))
 steps=abs(dx);
 else
 steps=abs(dy);
 xinc=(float)dx/(float)steps;
 yinc=(float)dy/(float)steps;
 x=x1;
 y=y1;
 //shapeDecider is a variable that decides which shape will appear when on the screen

 for(k=0;k<steps;k++)
 {
  glClear(GL_COLOR_BUFFER_BIT);
  if(shapeDecider%3==0)
  { 
   teamTheme();  // to display the team theme
  drawCircle(x,y,r.redc,r.greenc,r.bluec,0);// to draw circle along the line (x1,y1) to (x2,y2)
  glutSwapBuffers();
  drawSquare(-x,-y,r.reds,r.greens,r.blues,0);
  glutSwapBuffers();
  }
  else if(shapeDecider%3==1)
  {
   teamTheme();
  glutSwapBuffers();
  drawSquare(x,y,r.reds,r.greens,r.blues,0);
  glutSwapBuffers();
  drawCircle(-x,-y,r.redc,r.greenc,r.bluec,0.25);
  smallDelay();
  glutSwapBuffers();
  //smallDelay();
  }
  else
  {
  teamTheme();
  glutSwapBuffers();
  drawTriangle(x,y,1,1,1,ang);
  glutSwapBuffers();
  drawCircle(-x,-y,r.redc,r.greenc,r.bluec,0);
  glutSwapBuffers();
  smallDelay();
  
  } 
  x+=xinc;
  y+=yinc;  
  ang+=100; // this parameter is to rotate the triangle 
 } 
 if(shapeDecider<25)
 shapeDecider++;
 else
 shapeDecider=0;
}


void display()//display function to be called by the DisplayFunc() in mousecoord.c 
{
struct coordinategenerator cgen;
 while(1)
{
 cgen=decideScreen();//deciding the bouncing coordinates for one iteration
 linepath(cgen.x1,cgen.y1,cgen.x2,cgen.y2);//bouncing algorithm
 counter++;
 linepath(cgen.x2,cgen.y2,cgen.x3,cgen.y3);
 counter++;
 linepath(cgen.x3,cgen.y3,cgen.x4,cgen.y4);
 counter++;
 linepath(cgen.x4,cgen.y4,cgen.x1,cgen.y1);
 counter++;
 if(counter%2==0)
 {
  if(counter>=20)
  counter=0;
 s+=4;
 }
 if(s>=20)
 s=12;
 smallDelay();
 smallDelay();
 smallDelay();
}
}

