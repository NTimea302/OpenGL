#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float x_position = 0.0;
float angle = 0.0;
float rotspeed = 0.0;
float xc, yc;

void display();
void reshape(int, int); //receives the width and height of the window
void initOpenGl();
void timer(int);
void create_cube();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,0); //reference: top left corner
    glutCreateWindow("My rotating minecraft tree");
    initOpenGl();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0); //the timer function will be called every 0 second
    glutMainLoop();
    return 0;
}

void timer(int)
{
    glutPostRedisplay();              //OpenGl will call the display function
    glutTimerFunc(1000/60, timer, 0); //60 times in 1 second (1000 ms)

    rotspeed += 0.002;
    if(rotspeed > 1)
        rotspeed -= 1;
    angle += 1.5;
    if(angle > 360.0)
        angle -= 360.0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();                            //resets matrix transformations
    glTranslatef(0,-10,0);
    int radius = 25;
    float theta = 2.0f * 3.1415926f * rotspeed;  //get the current angle
    xc = radius * cosf(theta);                   //calculate the x component
    yc = radius * sinf(theta);                   //calculate the y component
    glTranslatef(xc, yc, -70.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    //CREATE TRUNK
    glColor3f(1.0, 0.0, 0.0);
    create_cube();
    glTranslatef(0,2,0);
    create_cube();
    glTranslatef(0,2,0);
    create_cube();
    glTranslatef(0,2,0);
    create_cube();

    //CREATE LEAVES
    glColor3f(0.0, 0.8, 0.3);
    glTranslatef(-5,2,-5);
    for(int ii = 1; ii <= 6; ii++)      //creates plane of tree 6x6
    {
        for(int i = 1; i <= 6; i++)     //creates 1 line of tree
        {
            create_cube();
            glTranslatef(2,0,0);
        }
        glTranslatef(-12,0,2);
    }

    glColor3f(0.2, 0.8, 0.3);
    glTranslatef(2,2,-10);
    for(int ii = 1; ii <= 4; ii++)      //creates plane of tree 4x4 above 6x6 plane
    {
        for(int i = 1; i <= 4; i++)     //creates 1 line of tree
        {
            create_cube();
            glTranslatef(2,0,0);
        }
        glTranslatef(-8,0,2);
    }

    glColor3f(0.3, 0.8, 0.3);
    glTranslatef(1,2,-7);              //create 3x3 plane above 4x4
    for(int ii = 1; ii <= 3; ii++)
    {
        for(int i = 1; i <= 3; i++)     //creates 1 line of tree
        {
            create_cube();
            glTranslatef(2,0,0);
        }
        glTranslatef(-6,0,2);
    }

    //create 5 more cubes
    glColor3f(0.4, 0.8, 0.3);
    glTranslatef(2,2,-2);
    create_cube();
    glTranslatef(0,0,-2);
    create_cube();
    glTranslatef(0,0,-2);
    create_cube();
    glTranslatef(2,0,2);
    create_cube();
    glTranslatef(-4,0,0);
    create_cube();

    //create last top cube
    glColor3f(0.5, 0.8, 0.3);
    glTranslatef(2,2,0);
    create_cube();

    glutSwapBuffers();//we use GLUT_Double buffering.
}

void create_cube()
{
    glBegin(GL_QUADS);
        //front
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        //back
        glVertex3f(1.0,1.0,-1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,1.0,-1.0);
        //right
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(1.0,1.0,-1.0);
        //left
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(-1.0,1.0,1.0);
        //top
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,1.0,-1.0);
        //bottom
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
    glEnd();
}

void reshape(int w, int h) //received the width and height of the window
{
    glViewport(0,0,w,h); //viewport set to window (startpoint, width, height)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-10,10,-10,10);     //for 2D             // <_<_<_<_<_<_<default working space of OpenGL is -1 to 1 on each axis_>_>_>_>_>_
    gluPerspective(60,(float)w/(float)h, 1.0, 80.0);
    glMatrixMode(GL_MODELVIEW);
}

void initOpenGl()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_DEPTH_TEST);
}
