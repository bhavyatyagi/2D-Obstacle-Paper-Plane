// ----------------------------- HEADER FILES STARTS ----------------------------------
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <GLUT/glut.h> // uncomment if you are using Mac OS
// #include <GL/glut.h> //uncomment for Windows
using namespace std;
// ----------------------------- HEADER FILES ENDS ------------------------------------

// ----------------------------- CONSTANTS STARTS -------------------------------------
// VARIABLE INITIALIZATIONS AND DECLRATIONS
int xSpeed = 12, ySpeed = 6; // Variables to adjust speed/translation coord in different modes
std::string scoring;         // Score String Global
int score = 0;               // Score
int gameEndFlag = 0;         // flag variable to check wheather the game is ended or still playing
int x = 0;                   // Score x point
int y = 0;                   // Score y point
int px = 0;                  // Plane x coord0
int px1 = 0;                 // Plane x coord1
int px2 = 0;                 // Plane x coord2
int px3 = 0;                 // Plane x coord3
int py = 0;                  // Plane y coord0
int pyvmax = 0;              // Plane y coord max
int pyvmin = 0;              // Plane y coord min
int py1 = 0;                 // Plane y coord1
int py2 = 0;                 // Plane y coord2
int py3 = 0;                 // Plane y coord3
int bx = 0;                  // Obstacle x coord
int by = 0;                  // Obstacle y coord
int bxmax = 0;               // Obstacle x coord max
int bxmin = 0;               // Ostacle x coord min
int bymax = 0;               // Ostacle y coord max
int bymin = 0;               // Ostacle y coord min
// ----------------------------- CONSTANTS ENDS ----------------------------------------

// ----------------------------- HELPER FUNCTIONS STARTS -------------------------------

void drawScore(const char *text)
{
    int x = 280, y = 370;  // defining score coord
    glColor3f(0.95, 0, 0); // Score String color to shade of red
    glRasterPos2f(x, y);   // defining raster position for pixel operations
    while (*text)
    { // for each text character create a glut Bitmap Character to show on screen
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}
void drawInstructions(const char *text)
{
    int x = 135, y = 385; // instruction string coord
    glColor3f(1, 1, 1);   // set color to white
    glRasterPos2f(x, y);  // defining raster position for pixel operations [raster positions are maintain with subpixel accuracy hence required for us when objects overlaps]
    while (*text)
    { // for each text character create a glut Bitmap Character to show on screen
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}
void drawTitleText(const char *text)
{
    int x = 225, y = 10; // title text coord
    glColor3f(1, 1, 1);  // set color to white
    glRasterPos2f(x, y); // defining raster position for pixel operations
    while (*text)
    { // for each text character create a glut Bitmap Character to show on screen
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}
void drawGameOverText()
{
    glColor3f(0.95, 0, 0); // set color to shade of red
    std::string str;
    str = "Game Over !";
    const char *text = str.data(); // retriving string data from string and typecasting to char*
    int x = 280, y = 230;          // coord
    glRasterPos2f(x, y);
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}
void keyboard(unsigned char key, int x, int y)
{
    //    cout<<(key);
    if (key == 'w') // move up key for plane, move left for obstacle
    {
        // base cases -> If fail then endTheGame
        if (py1 > bymin && py1 < bymax && px1 > bxmin && px1 < bxmax)
        {
            bx = bx;
            by = by;
            gameEndFlag++;
        }
        else if (py2 > bymin && py2 < bymax && px2 > bxmin && px2 < bxmax)
        {
            bx = bx;
            by = by;
            gameEndFlag++;
        }
        else if (py3 > bymin && py3 < bymax && px3 > bxmin && px3 < bxmax)
        {
            bx = bx;
            by = by;
            gameEndFlag++;
        }
        else if (pyvmax < 365)
        { // if game is still playing then adjust according to curSpeeds
            py = py + ySpeed;
            bx = bx - xSpeed;
            if (bx < -600)
            {
                bx = 0;
                score++;
                by = rand() % 365; // random obstacle height
            }
        }
        else if (bx < -600)
        {
            bx = 0;
            score++;
            by = rand() % 365; // random obstacle height
        }
        else
        {
            bx = bx - xSpeed;
        }
        glutPostRedisplay(); // marks the current window as needing to be redisplayed.
    }
    else if (key == 's')
    {
        // base cases -> If fail then endTheGame
        if (py1 > bymin && py1 < bymax && px1 > bxmin && px1 < bxmax)
        {
            bx = bx;
            by = by;
            gameEndFlag++;
        }
        else if (py2 > bymin && py2 < bymax && px2 > bxmin && px2 < bxmax)
        {
            bx = bx;
            by = by;
            gameEndFlag++;
        }
        else if (py3 > bymin && py3 < bymax && px3 > bxmin && px3 < bxmax)
        {
            bx = bx;
            by = by;
            gameEndFlag++;
        }
        else if (pyvmin > 0)
        {
            py = py - ySpeed;
            bx = bx - xSpeed;
            if (bx < -600)
            {
                bx = 0;
                score++;
                by = rand() % 365;
            }
        }
        else if (bx < -600)
        {
            bx = 0;
            score++;
            by = rand() % 365;
        }
        else
        {
            bx = bx - xSpeed;
        }
        glutPostRedisplay(); // marks the current window as needing to be redisplayed.
    }
    else if (key == 'r' || key == 'n')
    {
        // if restart or normal is hit then reinitiailize everything to 0 and set speeds
        py = 0;
        bx = 0;
        by = 0;
        score = 0;
        xSpeed = 12;
        ySpeed = 6;
        glutPostRedisplay(); // marks the current window as needing to be redisplayed.
    }
    else if (key == 'l')
    {
        // if low mode is hit then reinitiailize everything to 0 and set speeds to low
        py = 0;
        bx = 0;
        by = 0;
        score = 0;
        xSpeed = 8;
        ySpeed = 2;
        glutPostRedisplay(); // marks the current window as needing to be redisplayed.
    }
    else if (key == 'h')
    {
        // if high mode is hit then reinitiailize everything to 0 and set speeds to high
        py = 0;
        bx = 0;
        by = 0;
        score = 0;
        xSpeed = 20;
        ySpeed = 8;
        glutPostRedisplay(); // marks the current window as needing to be redisplayed.
    }
}
void plane()
{
    // re-initialising positions of plane according to key hit
    px1 = 250 + px;
    py1 = 340 + py;
    pyvmax = py1;
    pyvmin = 310 + py;
    px2 = 165 + px;
    py2 = pyvmin;
    px3 = 170 + px;
    py3 = py1;
    glColor3f(0.747, 0.747, 0.747); // first triangle color
    glBegin(GL_POLYGON);            // plotting traiangle first
    glVertex2i(px2, pyvmin);
    glVertex2i(px1, py1);
    glVertex2i(170 + px, 340 + py);
    glEnd();
    glColor3f(0.847, 0.847, 0.847); // second triangle color
    glBegin(GL_POLYGON);            // plotting triangle second
    glVertex2i(160 + px, 330 + py);
    glVertex2i(250 + px, 340 + py);
    glVertex2i(px3, 340 + py);
    glEnd();
}
void obstacle()
{
    // re-initialising positions of obstacle according to key hit
    bxmax = 600 + bx;
    bxmin = 550 + bx;
    bymax = 200 + by;
    bymin = 0 + by;
    glColor3f(0.0, 0.0, 0.0); // black color obstacle
    glBegin(GL_POLYGON);      // plot 4 points of a rectangle
    glVertex2i(bxmin, bymin);
    glVertex2i(bxmax, bymin);
    glVertex2i(600 + bx, bymax);
    glVertex2i(550 + bx, bymax);
    glEnd();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    plane();    // calling to create plane
    obstacle(); // calling to create obstacle
    string title = "Developed by Bhavya, Prince and Simran";
    string instructions = "Press 'W' and 'S' to go up and Down, 'L' for Low Speed, 'H' for High Speed and 'R' for Normal Mode";
    drawTitleText(title.data());
    drawInstructions(instructions.data());
    scoring = "Score: " + std::to_string(score);
    drawScore(scoring.data());
    glEnd();
    if (gameEndFlag > 0)
    { // checking if positive then end game
        drawGameOverText();
        gameEndFlag = 0;
    }
    glFlush();
}
void myInit(void)
{
    glClearColor(0.27f, 0.6f, 0.87f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION); // set matrix mode to GL_PROJECTION
    glLoadIdentity();            // set proj matrix to I
    gluOrtho2D(0.0, 600.0, 0.0, 400.0);
}
// ----------------------------- HELPER FUNCTIONS EDNS --------------------------------

// ----------------------------- MAIN PROGRAM STARTS ----------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1980, 1080);              // set intiial window size
    glutInitWindowPosition(10, 10);              // set window position
    glutCreateWindow("2D Obstacle Paper Plane"); // Window Title Text
    glutDisplayFunc(myDisplay);                  // main display function
    glutKeyboardFunc(keyboard);                  // keyboard function to take inputs
    myInit();                                    // rest initializations
    glutMainLoop();                              // for further executing methods
    return 0;
}
// ----------------------------- MAIN PROGRAM ENDS ------------------------------------
