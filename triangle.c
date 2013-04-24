#include<GL/glut.h>//standard graphics library
#include<time.h>
#include<math.h> // for associated mathematical functions
#include<stdio.h>
float side=12.5;


struct rota     //data structure to hold the rotated coordinates  
{
 float ao,bo,co,doo;
}rt;
struct rota rotr(float x0,float y0,float x1,float y1,float rad)  // function to rotate the triangle
{
 float rmat[3][3]={cos(rad),-sin(rad),0,sin(rad),cos(rad),0,0,0,1};
 float vset1[3][1]={x0,y0,1};
 float vset2[3][1]={x1,y1,1};
 float nvset1[3][1]={0,0,0};
 float nvset2[3][1]={0,0,0};
 int i,j,k;
 for(i=0;i<3;i++)
 {
  for(j=0;j<1;j++)
   {
     for(k=0;k<3;k++)
     {
      nvset1[i][j]+=rmat[i][k]*vset1[k][j];  //rotation by matrix multiplication 
      nvset2[i][j]+=rmat[i][k]*vset2[k][j];
     }
   }
 }    
 rt.ao=nvset1[0][0];
 rt.bo=nvset1[1][0];
 rt.co=nvset2[0][0];
 rt.doo=nvset2[1][0];
 return rt; // structure holds the position of line ends after rotation
}
//functions usualplot as well specialplot are manifestations of the bresenham's algorithm
//usualplot draws lines for which 0<m<1  
//(x1,y1)->starting coordinate of the line to be drawn
//dx->change along x direction
//dy->change along y direction
void usualplot(float x1,float y1,float dx,float dy,float p,float r,float g,float b)
{
 float x=x1,y=y1,k;
 glColor3f(sin(r),cos(g),sin(b)); //setting of colors to draw the line in a particular color
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 for(k=0;k<(dx-1);k++) //repeat the process "dx-1" times
 {
  if(p<0)   // choosing of the lower pixel 
  {
  x++;
  p=p+2*dy; 
  }
  else     // choosing of the upper pixel
  {
   x++;
   y++;
   p=p+2*(dy-dx);
  }
 glVertex2f(x,y);
 }  
glEnd();
}
//specialplot draws lines for which -1<m<0 i.e. negative slope
void specialplot(float x1,float y1,float dx,float dy,float p,float r,float g,float b)
{
 float x=x1,y=y1,k;
 p=-2*dy+dx;  //notice the difference in the initial value of the decision parameter 
 glColor3f(sin(r),cos(g),sin(b));
 glBegin(GL_POINTS); // drawing of the line point by point 
 for(k=0;k<(dx-1);k++)
 {
  if(p<0)      // choose the adjacent pixel
  {
  x++;
  p=p-2*dy; 
  }
  else        // choose the lower pixel
  {
   x++;
   y--;
   p=p-2*(dy-dx);
  }
 glVertex2f(x,y-abs(dy)/2);
 }  
glEnd();
}
void line(float x1,float y1,float x2,float y2,float r,float g,float b)
{
 float p,dx,dy,k,x=x1,y=y1,m; 
 dx=x2-x1; // change in x direction
 dy=y2-y1; // change in y direction
 m=dy/dx; // calculation of the slope to find if usual plot or special plot is to be used
 p=2*dy-dx; 
 if(m>=0)  // for positive slopes use usualplot
 usualplot(x1,y1,dx,dy,p,r,g,b);
 else     // for negative slopes use specialplot  
 specialplot(x1,y1,dx,dy,p,r,g,b);
 glEnd();
//glutSwapBuffers();
//glutPostRedisplay();
}
//function to draw the triangle
//parameter      type         function
//x1             float        x coordinate part of triangle transalation
//y1             float        y coordinate part of triangle transalation  
//r              float        red component of triangle's color
//g              float        green component of triangle's color
//b              float        blue component of triangle's color
//ang            float        angle wrt horizontal to which the triangle is drawn -> rotation component 
void drawTriangle(float x1,float y1,float r,float g,float b,float ang)
{ 
 float x,y,rad;
 rad=3.14159263*ang/180; // conversion of input angle(degrees) parameter to radians
 rotr(0+x1,side/(sqrt(3))+y1,side/2+x1,-side/(2*sqrt(3))+y1,rad); // endpoints of the line rotated
 //line(rt.ao,rt.bo,rt.co,rt.doo,r,g,b); //line is then drawn
 rotr(side/2+x1,-side/(2*sqrt(3))+y1,-side/2+x1,-side/(2*sqrt(3))+y1,rad);
 //line(rt.ao,rt.bo,rt.co,rt.doo,r,g,b);
 rotr(-side/2+x1,-side/(2*sqrt(3))+y1,0+x1,side/(sqrt(3))+y1,rad);
 //line(rt.ao,rt.bo,rt.co,rt.doo,r,g,b);
//custom made "scan filling for the triangle" begins
 glColor3f(sin(r),sin(g),cos(b)*sin(r*g));
 glBegin(GL_POINTS);
 for(y=-side/(2*sqrt(3));y<=side/(sqrt(3));y=y+0.1)
  {   
   for(x=-side/2;x<=side/2;x=x+0.1)
   {
    if(sqrt(3)*x-y+side/(sqrt(3))>=0)  //the triangle boundary is expressed as an intersection
     {                 //of the inequality planes 2.2x -y -3.6>0 , y>=3 and -2.2x -y +31.6>0 
      if(y>=-side/(2*sqrt(3)))         //when triangle is inclined at an angle of 0 degrees to the horizontal 
       {              
         if(-sqrt(3)*x-y+side/(sqrt(3))>=0)
         {
         rt.ao=x1+(x)*cos(rad)-(y)*sin(rad);
         rt.bo=y1+(x)*sin(rad)+(y)*cos(rad);
         glVertex2f(rt.ao,rt.bo);
         }  
       }
     }
   }
  }  
 glEnd();
 glFlush(); 
}

