#include<GL/glut.h>
#include<time.h>
#include<math.h>
float radius=20; // for the associated math library functions
struct crlast    //data structure to store the prevoius positions of the circle 
{
 float xcrmem;
 float ycrmem;
}crl;
//fcirc checks if the point it inputs is inside the circle
//if yes it returns a value<=0 
float fcirc(float x,float y,float x1,float y1,float r)//circle filling primitive
{
 return ((x1-x)*(x1-x)+(y1-y)*(y1-y)-r*r);//x^2+y^2-r^2
}
//function that draws a circle according to midpoint circle drawing algorithm
//parameter           type             function
//x1                  float            x coordinate of the center of the circle
//y1                  float            y coordinate of the center of the circle
//red                 float            red component of the circle's color
//green               float            green component of the circle's color
//blue                float            blue component of the circle's color  
struct crlast drawCircle(float x1,float y1,float red,float green,float blue,float shear)
{
 int j;
 float x,y,p,rad;
 x=0;
 y=radius;  // radius of the circle
 p=1-radius; //initial value of the decision parameter
 glColor3f(sin(red),cos(green),sin(blue));
 glBegin(GL_POINTS);
 while(x<y)
 {
  if(p<0) //choose the adjacent pixel 
  {
   x++;
   y=y+0;
   p=p+2*x+1;
  }  
  else  //choose the lower pixel 
  {
   x++;
   y--;
   p=p+2*(x-y)+1;   
  }
  //first quadrant
  glVertex2f(x+x1+shear*(y+y1),y+y1);  // the other points can be calculated by virtue of the circle's symmetry
  glVertex2f(y+x1+shear*(x+y1),x+y1);
  //second quadrant
  glVertex2f(x+x1+shear*(-y+y1),-y+y1);
  glVertex2f(y+x1+shear*(-x+y1),-x+y1);
  //third quadrant
  glVertex2f(-x+x1+shear*(-y+y1),-y+y1);
  glVertex2f(-y+x1+shear*(-x+y1),-x+y1);
  //fourth quadrant
  glVertex2f(-x+x1+shear*(y+y1),y+y1);
  glVertex2f(-y+x1+shear*(x+y1),x+y1);
 }
 //custom made scan filling for the circle begins
 glColor3f(sin(red),cos(green),sin(blue));
 for(y=-radius+y1;y<=radius+y1;y=y+0.01)//bottom to top
  {
   for(x=-radius+x1;x<=radius+x1;x=x+0.01)//left to right
    {
    if(fcirc(x,y,x1,y1,radius)<=0)//if the point is inside the circle or on the boundary then fill it
    glVertex2f(x+shear*y,y);
    }
  }
 glEnd();
 glFlush();
 crl.xcrmem=x1;
 crl.ycrmem=y1;
//glutSwapBuffers();
//glutPostRedisplay();
return crl; // returning the last position of the circle 
}

