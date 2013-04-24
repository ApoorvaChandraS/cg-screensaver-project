#include<GL/glut.h>
#include<time.h>
#include<math.h>
#include<stdio.h>
//file that contains the rotating facility also for the square
float s=12;
struct sqlast   
{ 
 float xsqmem;  // a data structure that holds the last position of the square
 float ysqmem;
}sql;
struct trans  // a data structure to do the rotation
{
 float ao,bo,co,doo;
}tr;
struct trans rotator(float x0,float y0,float x1,float y1,float rad) // the rotation algorithm->the matrix form
{
 tr.ao=x0*cos(rad)-y0*sin(rad);
 tr.bo=x0*sin(rad)+y0*cos(rad);
 tr.co=x1*cos(rad)-y1*sin(rad);
 tr.doo=x1*sin(rad)+y1*cos(rad);
 return tr;// returning of a structure  object that holds the transformed position
} 
void ddaline(float x1,float y1,float x2,float y2,float r,float g,float b) // the digital differential analyser line drawing algorithm
{                                                                         // to draw the sides of the square 
 float xinc,yinc,k,x=x1,y=y1,steps,dx,dy; 
 dx=x2-x1;   //change in x
 dy=y2-y1;   //change in y
 if(abs(dx)>abs(dy))
 steps=abs(dx);
 else
 steps=abs(dy); 
 xinc=((float)dx/(float)steps);  // increment for the line drawn along the x axis
 yinc=((float)dy/(float)steps);  // increment for the line drawn along the y axis
 glColor3f(sin(r),cos(g),sin(b));
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 for(k=0;k<steps;k++)
  {
     x=x+xinc;
     y=y+yinc;
     glVertex2f(x,y); 
  }
 glEnd();
//glutSwapBuffers();
//glutPostRedisplay();
}
//function that draws a square
//sides are drawn using the dda algorithm
//the filling of the square is done using a custom made "scan line filling" algorithm
//parameters to this function are
//parameter     type                function
// x1           float          x coordinate of transalation of the square 
// y1           float          y coordinate of transalation of the square
// red          float          red component of the square's color
// green        float          green component of the square's color
// blue         float          blue component of the square's color 
//ang           float          angle wrt the horizonatal at which the square is to be drawn->rotational component 
struct sqlast drawSquare(float x1,float y1,float red,float green,float blue,float ang)
{
 int j; 
 float x,y,rad,i;
 rad=ang*3.14159263/180;//conversion of angle in degrees to radians

 rotator(x1,y1-s,x1,y1,rad);  //coordinates are first rotated 
 ddaline(tr.ao,tr.bo,tr.co,tr.doo,red,green,blue);//then drawn
 rotator(x1,y1,s+x1,y1,rad);
 ddaline(tr.ao,tr.bo,tr.co,tr.doo,red,green,blue);
 rotator(x1,y1-s,s+x1,y1-s,rad);
 ddaline(tr.ao,tr.bo,tr.co,tr.doo,red,green,blue);
 rotator(x1+s,y1-s,s+x1,y1,rad);
 ddaline(tr.ao,tr.bo,tr.co,tr.doo,red,green,blue);
 

//custom made scan filling
 glColor3f(sin(red),cos(green),sin(blue));
 glBegin(GL_POINTS);
 for(y=0;y<=s;y=y+0.1)
 {
  for(x=0;x<=s;x=x+0.1)
   {
     tr.ao=(x+x1)*cos(rad)-(y-s+y1)*sin(rad);
     tr.bo=(x+x1)*sin(rad)+(y-s+y1)*cos(rad);
     glVertex2f(tr.ao,tr.bo);// filling is done pixel by pixel
   }
 }
 glEnd();
 glFlush();
 sql.xsqmem=x1; // coordinates  of the square are stored in memory
 sql.ysqmem=y1;  
}

