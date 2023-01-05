#include <GL/gl.h>
#include <GL/glut.h>
#include<stdio.h>
#include<math.h>
void timer1(int);
void timer2(int);
void timer3(int);
void timer4(int);
void timer5(int);
void timer11(int);
void timer22(int);
void timer33(int);
void timer44(int);
void timer55(int);




void display();
void reshape(int,int);
void init0(){
glClearColor(1.0,1.0,0.0,1.0);

}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //double buffer display mode + rgb display mode
glutInitWindowPosition(200,100);
glutInitWindowSize(900,900);
glutCreateWindow("Real-Time 1st PROJ");
glutDisplayFunc(display);
glutReshapeFunc(reshape);


int option = 33 ;
switch(option){

case 1 :

glutTimerFunc(1000,timer1,0);
break;

case 2:
glutTimerFunc(1000,timer2,0);
break;

case 3:
glutTimerFunc(1000,timer3,0);
break;
case 4 :
glutTimerFunc(1000,timer4,0);
break;
case 5:
glutTimerFunc(1000,timer5,0);
break;
case 11:
glutTimerFunc(1000,timer11,0);
break;
case 22:
glutTimerFunc(1000,timer22,0);
break;
case 33:
glutTimerFunc(1000,timer33,0);
break;
case 44:
glutTimerFunc(1000,timer44,0);
break;
case 55:
glutTimerFunc(1000,timer55,0);
break;
default :
printf("wrong input");






}
init0 ();


glutMainLoop();
}


//Previouspositions (x,y)
float x_position1 = -40;
float x_position2 = -20;
float x_position3 = 0;
float x_position4 = 20;
float x_position5 = 40;

float x_position11 = -40;
float x_position22 = -20;
float x_position33 = 0;
float x_position44 = 20;
float x_position55 = 40;

void display(){//draw things here


glClear(GL_COLOR_BUFFER_BIT);

glLoadIdentity();

//Fixed points
glPointSize(10.0);
glBegin(GL_POINTS);
glColor3ub(109, 194, 187);
glVertex2f(-40,0);
glVertex2f(-20,0);
glVertex2f(0,0);
glVertex2f(20,0);
glVertex2f(40,0);

glEnd();

glPointSize(20.0);
glBegin(GL_POINTS);
glColor3f(1.0,0.0,0.0);
glVertex2f(x_position1,10);
glVertex2f(x_position2,10);
glVertex2f(x_position3,10);
glVertex2f(x_position4,10);
glVertex2f(x_position5,10);




glColor3f(0.0,1.0,0.0);
//2nd Team
glVertex2f(x_position11,-10);
glVertex2f(x_position22,-10);
glVertex2f(x_position33,-10);
glVertex2f(x_position44,-10);
glVertex2f(x_position55,-10);






glEnd();




glutSwapBuffers();
}


void reshape(int w , int h){

glViewport(0,0,(GLsizei)w,(GLsizei)h);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-60,60,-30,30);
glMatrixMode(GL_MODELVIEW);



}
/* 

1 
THESE TIMERS FOR 1ST TEAM (5 TIMERS)
*/


void timer1(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer1,0);
if(x_position1< -10)
	x_position1 += 0.15;


}


void timer2(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer2,0);
if(x_position2< 0)
	x_position2 += 0.15;


}


void timer3(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer3,0);
if(x_position3< 20)
	x_position3 += 0.15;


}


void timer4(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer4,0);
if(x_position4< 40)
	x_position4 += 0.15;


}


void timer5(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer5,0);
if(x_position5< 60)
	x_position5 += 0.15;


}


void timer11(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer11,0);
if(x_position11< -10)
	x_position11 += 0.15;


}


void timer22(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer22,0);
if(x_position22< 0)
	x_position22 += 0.15;


}


void timer33(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer33,0);
if(x_position33< 20)
	x_position33 += 0.15;


}

void timer44(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer44,0);
if(x_position44< 40)
	x_position44 += 0.15;


}


void timer55(int){

glutPostRedisplay();//call display func
glutTimerFunc(1000/60,timer55,0);
if(x_position55<60)
	x_position55 += 0.15;


}
