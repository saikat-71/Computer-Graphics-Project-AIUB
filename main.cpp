#include <GL/glut.h>
#include <cmath>
#include<iostream>
using namespace std;

int currentScene = 1;

//train
float trainX = -1.6;
float cloudX0 = -1.2;
float cloudX1 = -0.5;
float cloudX2 = 0.3;
float cloudX3 = 1.0;
float birdX0 = 1.2;
float birdX1 = 0.6;
float birdX2 = -0.2;
float boat1X = -1.2;
float boat2X = 0.5;
bool isNightTrain=false;
bool starsVisibleTrain =true;

bool rainOn = false;
float rainX[300];
float rainY[300];
float rainSpeed = 0.03f;

bool snowOn = false;
float snowX[300];
float snowY[300];
float snowSpeed = 0.012f;

float smokeY = 0.10;
bool isPaused = false;
float globalSpeed = 1.0;

//circle
void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

//bush
void drawBush(float x, float y)
{
    glColor3f(0.1, 0.5, 0.1);
    drawCircle(x, y, 0.03);
    drawCircle(x - 0.02, y + 0.01, 0.024);
    drawCircle(x + 0.02, y + 0.01, 0.024);
}
void drawAllBushes()
{
    drawBush(-0.6, -0.12);
    drawBush(0.4, -0.15);
    drawBush(0.7, -0.1);
}
//sky
void drawSky()
{
    if(isNightTrain==true)

    glColor3f(0.05, 0.05, 0.2);
    else

    glColor3f(0.5, 0.8, 1);//day
    glBegin(GL_QUADS);
    glVertex2f(-1, 0.35);
    glVertex2f( 1, 0.35);
    glVertex2f( 1, 1);
    glVertex2f(-1, 1);
    glEnd();
}
//river
void drawRiver()
{
    glColor3f(0, 0.6,0.8);
    glBegin(GL_QUADS);
    glVertex2f(-1, 0.25);
    glVertex2f( 1, 0.25);
    glVertex2f( 1, -0.07);
    glVertex2f(-1, -0.07);
    glEnd();
}
//boat
void drawBoat()
{
    float y1 = 0.1;
    float y2 = 0.02;

    //boat 1
    float x = boat1X;
//body
    glColor3f(0.6, 0.3, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.08, y1);
    glVertex2f(x + 0.08, y1);
    glVertex2f(x + 0.05, y1 - 0.03);
    glVertex2f(x - 0.05, y1 - 0.03);
    glEnd();
//top
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.03, y1);
    glVertex2f(x + 0.03, y1);
    glVertex2f(x + 0.03, y1 + 0.03);
    glVertex2f(x - 0.03, y1 + 0.03);
    glEnd();
//boat 2
    x = boat2X;

    glColor3f(0.6, 0.3, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.08, y2);
    glVertex2f(x + 0.08, y2);
    glVertex2f(x + 0.05, y2 - 0.03);
    glVertex2f(x - 0.05, y2 - 0.03);
    glEnd();

    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.03, y2);
    glVertex2f(x + 0.03, y2);
    glVertex2f(x + 0.03, y2 + 0.03);
    glVertex2f(x - 0.03, y2 + 0.03);
    glEnd();
}
//sun or moon
void drawSunMoon()
{
    if(isNightTrain==true)
        glColor3f(1, 1, 1);
    else
    glColor3f(1, 1, 0);

    drawCircle(0.75, 0.8,0.06);
}
//star
void drawStars()
{
    if(isNightTrain==false)
        return;
    if(starsVisibleTrain==false)
        return;
    glColor3f(1, 1, 1);
    glPointSize(2);

    glBegin(GL_POINTS);

    glVertex2f(-0.8, 0.85);
    glVertex2f(-0.4, 0.9);
    glVertex2f(-0.1, 0.92);
    glVertex2f(0, 0.87);
    glVertex2f(0.2, 0.95);
    glVertex2f(0.4, 0.88);
    glVertex2f(0.6, 0.83);
    glVertex2f(0.75, 0.91);
    glVertex2f(0.9, 0.86);
    glEnd();
}

//hills
void drawHills()
{
//back
    glColor3f(0.2, 0.5, 0.6);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.2, 0.25); glVertex2f(-0.9, 0.6); glVertex2f(-0.6, 0.25);
    glVertex2f(-0.8, 0.25); glVertex2f(-0.45, 0.65); glVertex2f(-0.1, 0.25);
    glVertex2f(-0.3, 0.25); glVertex2f(0, 0.55);  glVertex2f(0.3, 0.25);
    glVertex2f(0.1, 0.25);  glVertex2f(0.45, 0.6);  glVertex2f(0.8, 0.25);
    glVertex2f(0.6, 0.25);  glVertex2f(0.95, 0.55); glVertex2f(1.2, 0.25);
    glEnd();

//middle
    glColor3f(0.4, 0.7, 0.4);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.1, 0.25); glVertex2f(-0.8, 0.5);  glVertex2f(-0.5, 0.25);
    glVertex2f(-0.6, 0.25); glVertex2f(-0.3, 0.55); glVertex2f(0, 0.25);
    glVertex2f(0.1, 0.25);  glVertex2f(0.4, 0.5);   glVertex2f(0.7, 0.25);
    glVertex2f(0.5, 0.25);  glVertex2f(0.8, 0.55);  glVertex2f(1, 0.25);
    glEnd();

//front
    glColor3f(0.2, 0.6, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1, 0.25); glVertex2f(-0.7, 0.45); glVertex2f(-0.4, 0.25);
    glVertex2f(-0.3, 0.25); glVertex2f(0, 0.4);   glVertex2f(0.3, 0.25);
    glVertex2f(0.2, 0.25);  glVertex2f(0.5, 0.45);  glVertex2f(0.7, 0.25);
    glVertex2f(0.6, 0.25);  glVertex2f(0.85, 0.4);  glVertex2f(1, 0.25);
    glEnd();
}

//field
void drawField()
{

    glColor3f(0.2, 0.7, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(-1, -0.07);
    glVertex2f( 1, -0.07);
    glVertex2f( 1, -1);
    glVertex2f(-1, -1);
    glEnd();

 //tree 1
    float treeBaseY = -0.07;
    float trunkHeight = 0.08;
    float trunkWidth  = 0.02;

    //trunk
    glColor3f(0.55, 0.27, 0.07);
    glBegin(GL_QUADS);
    glVertex2f(-0.5, treeBaseY);
    glVertex2f(-0.5 + trunkWidth, treeBaseY);
    glVertex2f(-0.5 + trunkWidth, treeBaseY + trunkHeight);
    glVertex2f(-0.5, treeBaseY + trunkHeight);
    glEnd();

    //leaves
    glColor3f(0.1, 0.6, 0.1);
    drawCircle(-0.5 + trunkWidth/2, treeBaseY + trunkHeight + 0.03, 0.04);
    drawCircle(-0.5 + trunkWidth/2 - 0.02, treeBaseY + trunkHeight, 0.04);
    drawCircle(-0.5 + trunkWidth/2 + 0.02, treeBaseY + trunkHeight, 0.04);

//tree 2
    glColor3f(0.55, 0.27, 0.07);
    glBegin(GL_QUADS);
    glVertex2f(0, treeBaseY);
    glVertex2f(trunkWidth, treeBaseY);
    glVertex2f(trunkWidth, treeBaseY + trunkHeight);
    glVertex2f(0, treeBaseY + trunkHeight);
    glEnd();

    glColor3f(0.1, 0.6, 0.1);
    drawCircle(trunkWidth/2, treeBaseY + trunkHeight + 0.03, 0.04);
    drawCircle(trunkWidth/2 - 0.02, treeBaseY + trunkHeight, 0.04);
    drawCircle(trunkWidth/2 + 0.02, treeBaseY + trunkHeight, 0.04);

//tree 3
    glColor3f(0.55, 0.27, 0.07);
    glBegin(GL_QUADS);
    glVertex2f(0.6, treeBaseY);
    glVertex2f(0.6 + trunkWidth, treeBaseY);
    glVertex2f(0.6 + trunkWidth, treeBaseY + trunkHeight);
    glVertex2f(0.6, treeBaseY + trunkHeight);
    glEnd();

    glColor3f(0.1, 0.6, 0.1);
    drawCircle(0.6 + trunkWidth/2, treeBaseY + trunkHeight + 0.03, 0.04);
    drawCircle(0.6 + trunkWidth/2 - 0.02, treeBaseY + trunkHeight, 0.04);
    drawCircle(0.6 + trunkWidth/2 + 0.02, treeBaseY + trunkHeight, 0.04);

    drawAllBushes();

}

//rail line
void drawRailLine()
{
    glColor3f(0.3, 0.3, 0.3);

    glBegin(GL_LINES);
    glVertex2f(-1, -0.35);
    glVertex2f(1, -0.35);

    glVertex2f(-1, -0.42);
    glVertex2f(1, -0.42);
    glEnd();

    glBegin(GL_LINES);
    for(float x = -1; x < 1; x += 0.08)
    {
        glVertex2f(x, -0.35);
        glVertex2f(x, -0.42);
    }
    glEnd();
}


// train
void drawTrain()
{
    float baseY = -0.30;
    float topY  =  0.05;
    float wheelY = -0.35;

    //coach 1
    glColor3f(1,0.5,0);
    glBegin(GL_QUADS);
    glVertex2f(-0.85 + trainX, baseY);
    glVertex2f(-0.55 + trainX, baseY);
    glVertex2f(-0.55 + trainX, topY);
    glVertex2f(-0.85 + trainX, topY);
    glEnd();

    glColor3f(0.2,0.2,0.2);
    drawCircle(-0.78 + trainX, wheelY, 0.025);
    drawCircle(-0.62 + trainX, wheelY, 0.025);

    //glass
    glColor3f(0.85,0.95,1);
    glBegin(GL_QUADS);
    glVertex2f(-0.82 + trainX, -0.15);
    glVertex2f(-0.58 + trainX, -0.15);
    glVertex2f(-0.58 + trainX,  0.01);
    glVertex2f(-0.82 + trainX,  0.01);
    glEnd();

    //coach 2
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glVertex2f(-0.50 + trainX, baseY);
    glVertex2f(-0.20 + trainX, baseY);
    glVertex2f(-0.20 + trainX, topY);
    glVertex2f(-0.50 + trainX, topY);
    glEnd();

    glColor3f(0.2,0.2,0.2);
    drawCircle(-0.43 + trainX, wheelY, 0.025);
    drawCircle(-0.27 + trainX, wheelY, 0.025);

    glColor3f(0.85, 0.95, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.47 + trainX, -0.15);
    glVertex2f(-0.23 + trainX, -0.15);
    glVertex2f(-0.23 + trainX,  0.01);
    glVertex2f(-0.47 + trainX,  0.01);
    glEnd();


    //coach 3
    glColor3f(0.7,0.13,0.13);
    glBegin(GL_QUADS);
    glVertex2f(-0.15 + trainX, baseY);
    glVertex2f( 0.15 + trainX, baseY);
    glVertex2f( 0.15 + trainX, topY);
    glVertex2f(-0.15 + trainX, topY);
    glEnd();

    glColor3f(0.2,0.2,0.2);
    drawCircle(-0.08 + trainX, wheelY, 0.025);
    drawCircle( 0.08 + trainX, wheelY, 0.025);

    glColor3f(0.85, 0.95, 1);
    glBegin(GL_QUADS);
    glVertex2f(-0.12 + trainX, -0.15);
    glVertex2f( 0.12 + trainX, -0.15);
    glVertex2f( 0.12 + trainX,  0.01);
    glVertex2f(-0.12 + trainX,  0.01);
    glEnd();

//engine
    // body
    glColor3f(0.3,0,0.5);
    glBegin(GL_QUADS);
    glVertex2f(0.20 + trainX, baseY);
    glVertex2f(0.45 + trainX, baseY);
    glVertex2f(0.45 + trainX, -0.03);
    glVertex2f(0.20 + trainX, -0.03);
    glEnd();

    //nose
    glBegin(GL_TRIANGLES);
    glVertex2f(0.45 + trainX, baseY);
    glVertex2f(0.58 + trainX, (baseY -0.03) / 2);
    glVertex2f(0.45 + trainX, -0.03);
    glEnd();

    // cabin
    glColor3f(0.5,0,0.5);
    glBegin(GL_QUADS);
    glVertex2f(0.25 + trainX, -0.03);
    glVertex2f(0.32 + trainX, -0.03);
    glVertex2f(0.32 + trainX, 0.05);
    glVertex2f(0.25 + trainX, 0.05);
    glEnd();

// Chimney
glColor3f(0.2, 0.2, 0.2);
glBegin(GL_QUADS);
glVertex2f(0.40 + trainX, -0.03);
glVertex2f(0.45 + trainX, -0.03);
glVertex2f(0.45 + trainX, 0.10);
glVertex2f(0.40 + trainX, 0.10);
glEnd();

    // Engine wheel
    glColor3f(0.2,0.2,0.2);
    drawCircle(0.28 + trainX, wheelY, 0.03);
    drawCircle(0.40 + trainX, wheelY, 0.03);

//engine window
glColor3f(0.85, 0.95, 1);
float windowTop    = -0.040;
float windowBottom = -0.1;

// Window 1
glBegin(GL_QUADS);
glVertex2f(0.24 + trainX, windowBottom);
glVertex2f(0.29 + trainX, windowBottom);
glVertex2f(0.29 + trainX, windowTop);
glVertex2f(0.24 + trainX, windowTop);
glEnd();

// Window 2
glBegin(GL_QUADS);
glVertex2f(0.32 + trainX, windowBottom);
glVertex2f(0.37 + trainX, windowBottom);
glVertex2f(0.37 + trainX, windowTop);
glVertex2f(0.32 + trainX, windowTop);
glEnd();
}

//cloud
void drawCloud(float x, float y)
{
    glColor3f(0.9,0.9,0.9);
    drawCircle(x, y, 0.05);
    drawCircle(x + 0.06, y, 0.06);
    drawCircle(x + 0.12, y, 0.05);
}

//bird
void drawBird(float x, float y)
{
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 0.05, y + 0.03);
    glVertex2f(x + 0.05, y + 0.03);
    glVertex2f(x + 0.1, y);
    glEnd();
}

//grass
void drawGrass()
{
    //back
    glColor3f(0.2,0.6,0.2);
    glBegin(GL_TRIANGLES);
    for(float x = -1; x <= 1; x += 0.05)
    {
        glVertex2f(x, -1.0);
        glVertex2f(x + 0.025, -0.72);
        glVertex2f(x + 0.05, -1.0);
    }
    glEnd();

    //front
    glColor3f(0.0,0.5,0.0);
    glBegin(GL_TRIANGLES);
    for(float x = -1; x <= 1; x += 0.04)
    {
        glVertex2f(x, -1);
        glVertex2f(x + 0.02, -0.75);
        glVertex2f(x + 0.04, -1);
    }
    glEnd();
}

// Flower
void drawFlower(float x, float y)
{
    //stem
    glColor3f(0, 0.6, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + 0.05);
    glEnd();

    //yellow flower
    glColor3f(1, 1, 0);
    drawCircle(x, y + 0.06, 0.015);

    //center
    glColor3f(1, 0.5, 0);
    drawCircle(x, y + 0.06, 0.007);
}

void drawFlowers()
{
    drawFlower(-0.8, -0.82);
    drawFlower(-0.5, -0.80);
    drawFlower(-0.2, -0.83);
    drawFlower( 0.2, -0.81);
    drawFlower( 0.5, -0.84);
    drawFlower( 0.8, -0.82);
}
void drawRain()
{
    if(!rainOn) return;

    glColor3f(0.6, 0.6, 1.0);
    glLineWidth(2);
    glBegin(GL_LINES);

    for(int i = 0; i < 300; i++)
    {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i] + 0.008f, rainY[i] - 0.05f);
    }

    glEnd();
}
void drawSnow()
{
    if(!snowOn) return;

    glColor3f(1, 1, 1);
    glPointSize(2);
    glBegin(GL_POINTS);

    for(int i = 0; i < 300; i++)
    {
        glVertex2f(snowX[i], snowY[i]);
    }

    glEnd();
}
void drawSmoke(float x)
{
    glColor4f(0.5, 0.5, 0.5, 0.6);
    drawCircle(x + 0.42, smokeY, 0.02);
    drawCircle(x + 0.45, smokeY + 0.03, 0.015);
}

//display
void displayTrain()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawStars();
    drawSunMoon();
    drawHills();
    drawRiver();
    drawBoat();
    drawField();
    drawRailLine();
    drawTrain();
    drawGrass();
    drawFlowers();
    drawCloud(cloudX0, 0.75);
    drawCloud(cloudX1, 0.82);
    drawCloud(cloudX2, 0.78);
    drawCloud(cloudX3, 0.85);

    drawBird(birdX0, 0.70);
    drawBird(birdX1, 0.75);
    drawBird(birdX2, 0.72);

    drawRain();
    drawSnow();
    drawSmoke(trainX);

    glutSwapBuffers();
}
//airport code........................................................................
float planeX = -1.0f;
float planeY = -0.4f;
float runwayX = 0.0f;
float cloudX11 = -1.2f;
float cloudX22= -0.4f;
float cloudX33= 0.6f;
float carX = 0.65f;
bool isNightAirport= false;
bool runwayLightOn = true;
bool planeNavLightOn = true;
bool tailLightOn = true;
bool starsVisibleAirport = true;
bool floodlightsOn = true;

//SUN/MOON/STARS
void drawSunMoonStars()
{
    if(isNightAirport)
    {
        // Moon
        glColor3f(1,1,1);
        drawCircle(0.75f, 0.6f, 0.1f);

        // Stars(twinkling)
        if(starsVisibleAirport)
        {
            glPointSize(2);
            glBegin(GL_POINTS);
                glVertex2f(-0.8,0.9);
                glVertex2f(-0.5,0.85);
                glVertex2f(-0.2,0.92);
                glVertex2f(0.2,0.88);
                glVertex2f(0.5,0.93);
                glVertex2f(0.8,0.9);
            glEnd();
        }
    }
    else
    {
        // Sun
        glColor3f(1,1,0);
        drawCircle(0.75f, 0.6f, 0.1f);
    }
}
void drawFloodlight(float x)
{
    // Pole
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_QUADS);
        glVertex2f(x, -0.2);
        glVertex2f(x + 0.02, -0.2);
        glVertex2f(x + 0.02, 0.3);
        glVertex2f(x, 0.3);
    glEnd();
    if(isNightAirport && floodlightsOn)
    {
        // Light cone (transparent effect)
        glColor4f(1.0, 1.0, 0.8, 0.3);
        glBegin(GL_TRIANGLES);
            glVertex2f(x + 0.01, 0.3);
            glVertex2f(x - 0.2, -0.6);
            glVertex2f(x + 0.22, -0.6);
        glEnd();

        // Bright light point
        glColor3f(1, 1, 0.9);
        glPointSize(8);
        glBegin(GL_POINTS);
            glVertex2f(x + 0.01, 0.3);
        glEnd();
    }
}
void drawAllFloodlights()
{
    drawFloodlight(-0.7);
    drawFloodlight(0.0);
    drawFloodlight(0.7);
}

//CLOUD
void drawCloudAirport(float x, float y)
{
    glColor3f(0.9,0.9,0.9);
    drawCircle(x, y, 0.05);
    drawCircle(x+0.06, y, 0.06);
    drawCircle(x+0.12, y, 0.05);
}

//RUNWAY
void drawRunway()
{
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f(-1,-0.6);
        glVertex2f( 1,-0.6);
        glVertex2f( 1,-0.2);
        glVertex2f(-1,-0.2);
    glEnd();

    // white strips
    glColor3f(1,1,1);
    for(float x=-1;x<1;x+=0.4)
    {
        glBegin(GL_QUADS);
            glVertex2f(x+runwayX,-0.45);
            glVertex2f(x+0.12+runwayX,-0.45);
            glVertex2f(x+0.12+runwayX,-0.35);
            glVertex2f(x+runwayX,-0.35);
        glEnd();
    }

    // runway lights
    if(isNightAirport && runwayLightOn)
    {
        glColor3f(1,0,0);
        glPointSize(6);
        glBegin(GL_POINTS);
        for(float x=-0.95;x<1;x+=0.2)
            glVertex2f(x,-0.6);
        glEnd();
    }
}

//AIRPORT
void drawWindow(float x, float y)
{
    if(isNightAirport) glColor3f(1, 1, 0.3);   // Night color
    else glColor3f(0.2, 0.4, 0.8);       // Day color

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 0.05, y);
        glVertex2f(x + 0.05, y + 0.07);
        glVertex2f(x, y + 0.07);
    glEnd();
}
void drawAirport()
{
    // Terminal 1
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
        glVertex2f(-0.95, -0.2);
        glVertex2f(-0.65, -0.2);
        glVertex2f(-0.65, 0.12);
        glVertex2f(-0.95, 0.12);
    glEnd();

    // Terminal 2
    glBegin(GL_QUADS);
        glVertex2f(-0.6, -0.2);
        glVertex2f(-0.3, -0.2);
        glVertex2f(-0.3, 0.08);
        glVertex2f(-0.6, 0.08);
    glEnd();

    // Hangar
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
        glVertex2f(-0.2, -0.2);
        glVertex2f(0.15, -0.2);
        glVertex2f(0.1, 0.05);
        glVertex2f(-0.15, 0.05);
    glEnd();

    drawWindow(-0.9, -0.05);
    drawWindow(-0.82, -0.05);
    drawWindow(-0.74, -0.05);

    drawWindow(-0.57, -0.05);
    drawWindow(-0.47, -0.05);
    drawWindow(-0.37, -0.05);

    // Control tower
    glColor3f(0.45, 0.45, 0.45);
    glBegin(GL_QUADS);
        glVertex2f(0.25, -0.2);
        glVertex2f(0.32, -0.2);
        glVertex2f(0.32, 0.22);
        glVertex2f(0.25, 0.22);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.22, 0.22);
        glVertex2f(0.35, 0.22);
        glVertex2f(0.35, 0.28);
        glVertex2f(0.22, 0.28);
    glEnd();
}
//APARTMENT
void drawApartment(float x, float y, int floors)
{
    float floorHeight = 0.12f;
    float width = 0.22f;

    // Building body
    glColor3f(0.55,0.55,0.55);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + floors * floorHeight);
        glVertex2f(x, y + floors * floorHeight);
    glEnd();

    // Roof
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.01f, y + floors * floorHeight);
        glVertex2f(x + width + 0.01f, y + floors * floorHeight);
        glVertex2f(x + width + 0.01f, y + floors * floorHeight + 0.04f);
        glVertex2f(x - 0.01f, y + floors * floorHeight + 0.04f);
    glEnd();

    // Windows
    for(int f = 0; f < floors; f++)
    {
        for(int w = 0; w < 3; w++)
        {
            if(isNightAirport)
                glColor3f(1.0,1.0,0.4); // night windows
            else
                glColor3f(0.2,0.4,0.8); // day windows

            float wx = x + 0.03f + w * 0.07f;
            float wy = y + 0.03f + f * floorHeight;

            glBegin(GL_QUADS);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.04f, wy);
                glVertex2f(wx + 0.04f, wy + 0.05f);
                glVertex2f(wx, wy + 0.05f);
            glEnd();
        }
    }
    // Main door
    glColor3f(0.25,0.15,0.1);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.09f, y);
        glVertex2f(x + 0.15f, y);
        glVertex2f(x + 0.15f, y + 0.1f);
        glVertex2f(x + 0.09f, y + 0.1f);
    glEnd();
}
void drawApartmentArea()
{
    drawApartment(0.25f, -0.1f, 4);
    drawApartment(0.52f, -0.1f, 5);
    drawApartment(0.80f, -0.1f, 3);
}
//ROAD
void drawRoad()
{
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.1f);
        glVertex2f( 1.0f, -0.1f);
        glVertex2f( 1.0f, -0.25f);
        glVertex2f(-1.0f, -0.25f);
    glEnd();

   // Road divider
    glColor3f(1,1,1);
    for(float x=-1; x<1; x+=0.3f)
    {
        glBegin(GL_QUADS);
            glVertex2f(x, -0.17f);
            glVertex2f(x+0.12f, -0.17f);
            glVertex2f(x+0.12f, -0.15f);
            glVertex2f(x, -0.15f);
        glEnd();
    }
}
//CAR
void drawCar(float x, float y)
{
    glPushMatrix();
    glTranslatef(x,y,0);

    // Car body
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(0.25,0);
        glVertex2f(0.25,0.07);
        glVertex2f(0,0.07);
    glEnd();

    // Car top
    glColor3f(0.8,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0.05,0.07);
        glVertex2f(0.20,0.07);
        glVertex2f(0.16,0.12);
        glVertex2f(0.08,0.12);
    glEnd();

    // Windows
    glColor3f(0.6,0.9,1);
    glBegin(GL_QUADS);
        glVertex2f(0.09,0.075);
        glVertex2f(0.14,0.075);
        glVertex2f(0.13,0.11);
        glVertex2f(0.10,0.11);
    glEnd();

    // Wheels
    glColor3f(0,0,0);
    drawCircle(0.05,-0.005,0.025);
    drawCircle(0.20,-0.005,0.025);

        // Car headlights at night
if(isNightAirport)
{
    glColor4f(1, 1, 0.8, 0.4);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.02);
        glVertex2f(-0.35, -0.05);
        glVertex2f(-0.35, 0.09);
    glEnd();
}


    glPopMatrix();
}

void drawPlaneAirport()
{
    glPushMatrix();
    glTranslatef(planeX, planeY, 0);

    //BODY
    glColor3f(0.75,0.75,0.75);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.36f, 0.15f);
        glVertex2f(0.36f, 0.08f);
    glEnd();

    //COCKPIT
    glColor3f(0.35,0.35,0.35);
    glBegin(GL_POLYGON);
        glVertex2f(0.36f, 0.15f);
        glVertex2f(0.40f, 0.135f);
        glVertex2f(0.413f, 0.12f);
        glVertex2f(0.426f, 0.105f);
        glVertex2f(0.36f, 0.105f);
    glEnd();

    //COCKPIT OUTLINE
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.36f, 0.15f);
        glVertex2f(0.40f, 0.135f);
        glVertex2f(0.413f, 0.12f);
        glVertex2f(0.426f, 0.105f);
        glVertex2f(0.36f, 0.105f);
    glEnd();

    //LOWER TRIANGLE
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(0.36f, 0.105f);
        glVertex2f(0.426f, 0.105f);
        glVertex2f(0.426f, 0.098f);
        glVertex2f(0.389f, 0.08f);
        glVertex2f(0.36f, 0.08f);
    glEnd();

    //TAIL
    glColor3f(0.33,0.46,1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.0f, 0.22f);
        glVertex2f(0.03f, 0.22f);
        glVertex2f(0.107f, 0.15f);
    glEnd();

    //LEFT WING
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(0.173f, 0.15f);
        glVertex2f(0.133f, 0.185f);
        glVertex2f(0.2f, 0.185f);
        glVertex2f(0.24f, 0.15f);
    glEnd();

    //RIGHT WING
    glBegin(GL_POLYGON);
        glVertex2f(0.186f, 0.105f);
        glVertex2f(0.267f, 0.105f);
        glVertex2f(0.213f, 0.035f);
        glVertex2f(0.133f, 0.035f);
    glEnd();

    if(isNightAirport)
{
    glColor4f(1, 1, 0.8, 0.4);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.426f, 0.105f);
        glVertex2f(0.7f, 0.0f);
        glVertex2f(0.7f, 0.2f);
    glEnd();
}
    if(planeNavLightOn)
    {
        glPointSize(6);
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
            glVertex2f(0.133f, 0.185f);
        glEnd();

        glColor3f(0,1,0);
        glBegin(GL_POINTS);
            glVertex2f(0.267f, 0.105f);
        glEnd();
    }

    //TAIL BLINKING LIGHT
    if(tailLightOn)
    {
        glColor3f(1,0,0);
        glPointSize(6);
        glBegin(GL_POINTS);
            glVertex2f(0.015f, 0.22f);
        glEnd();
    }

    glPopMatrix();
}

//GRASS FIELD
void drawGrassField()
{
    if(isNightAirport)
        glColor3f(0.05f, 0.25f, 0.05f);
    else
        glColor3f(0.2f, 0.7f, 0.2f);

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.6f);
        glVertex2f(-1.0f, -0.6f);
    glEnd();
}
void displayAirport()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(isNightAirport)
        glClearColor(0.05,0.05,0.2,1);
    else
        glClearColor(0.5,0.9,1,1);

    drawGrassField();
    drawSunMoonStars();

    drawCloud(cloudX1,0.75);
    drawCloud(cloudX2,0.82);
    drawCloud(cloudX3,0.78);

    drawApartmentArea();
    drawRoad();
    drawCar(carX, -0.13f);

    drawRunway();
    drawAirport();
    drawAllFloodlights();
    drawPlaneAirport();
    drawRain();
    drawSnow();

    glutSwapBuffers();
}

//city code...........................................................................
float cloud1X = -1.2f;
float cloud2X = -0.6f;
float cloud3X = 0.3f;

float planeX1 = -1.3f;  // start x axis
float planeY2 = 0.75f;  // height
float planeSpeed = 0.008f;

float carLeftX  = -1.2f;
float carRightX =  1.2f;

bool isNight = false;
bool star1 = true, star2 = true, star3 = true, star4 = true;
int starCounter = 0;
int trafficState = 0;
int trafficTimer = 0;
extern bool isNight;   // or your night variable

//sun moon
void drawSunMoonCity()
{
    float x = -0.75f;
    float y = 0.85f;
    if(isNight)
    {
        glColor3f(1.0f, 1.0f, 0.85f); // Moon
        drawCircle(x, y, 0.07f);
    }
    else
    {
        glColor3f(1.0f, 0.9f, 0.0f); // Sun
        drawCircle(x, y, 0.08f);
    }
}
//star
void drawStar(float x, float y)
{
    glColor3f(1, 1, 1);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawStarsCity()
{
    if(!isNight) return;

    drawStar(-0.8f, 0.85f);
    drawStar(-0.5f, 0.9f);
    drawStar(-0.2f, 0.87f);
    drawStar(0.0f, 0.92f);
    drawStar(0.3f, 0.88f);
    drawStar(0.5f, 0.9f);
    drawStar(0.7f, 0.83f);
    drawStar(0.9f, 0.86f);
    drawStar(-0.9f, 0.9f);
    drawStar(-0.6f, 0.82f);
    drawStar(-0.3f, 0.95f);
    drawStar(0.2f, 0.93f);
    drawStar(0.4f, 0.87f);
    drawStar(0.6f, 0.91f);
    drawStar(0.8f, 0.88f);
}
//sky
void drawSkyCity()
{
    if (isNight)
        glColor3f(0.05f, 0.05f, 0.2f);   //night
    else
        glColor3f(0.53f, 0.81f, 0.98f);
    glBegin(GL_QUADS);
    glVertex2f(-1, 0.3);
    glVertex2f(1, 0.3);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();
}
//cloud
void drawCloudCity(float x, float y)
{
    glColor3f(1, 1, 1);
    drawCircle(x, y, 0.06);
    drawCircle(x + 0.07, y, 0.06);
    drawCircle(x + 0.14, y, 0.06);
}
//buildings
void drawBuildings()
{
    float x = -1.0f;
    float width = 0.25f;

    float colors[8][3] = {
        {0.7f,0.4f,0.4f}, {0.4f,0.6f,0.7f}, {0.6f,0.6f,0.4f},
        {0.5f,0.4f,0.7f}, {0.7f,0.5f,0.3f}, {0.4f,0.7f,0.5f},
        {0.6f,0.5f,0.5f}, {0.3f,0.6f,0.6f}
    };

    for(int i = 0; i < 8; i++)
    {
        float height = 0.3f + (i % 3) * 0.1f;

        // Building body
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        glBegin(GL_QUADS);
        glVertex2f(x, 0.0f);
        glVertex2f(x + width, 0.0f);
        glVertex2f(x + width, height);
        glVertex2f(x, height);
        glEnd();

        // Windows
        glColor3f(isNight ? 1.0f : 0.8f, isNight ? 1.0f : 0.8f, 0.2f);

        for(float wy = 0.05f; wy < height - 0.05f; wy += 0.08f)
        {
            glBegin(GL_QUADS);
            glVertex2f(x + 0.05f, wy);
            glVertex2f(x + 0.10f, wy);
            glVertex2f(x + 0.10f, wy + 0.04f);
            glVertex2f(x + 0.05f, wy + 0.04f);
            glEnd();

            glBegin(GL_QUADS);
            glVertex2f(x + 0.15f, wy);
            glVertex2f(x + 0.20f, wy);
            glVertex2f(x + 0.20f, wy + 0.04f);
            glVertex2f(x + 0.15f, wy + 0.04f);
            glEnd();
        }
        x += width;
    }
}
void drawTreeSet()
{
    // Tree 1
    {
        float x = -0.85f, y = 0.0f, scale = 0.6f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }

    // Tree 2
    {
        float x = -0.60f, y = 0.0f, scale = 0.7f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }
    // Tree 3
    {
        float x = -0.35f, y = 0.0f, scale = 0.5f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }
    // Tree 4
    {
        float x = -0.10f, y = 0.0f, scale = 0.65f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }
    // Tree 5
    {
        float x = 0.15f, y = 0.0f, scale = 0.55f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }
    // Tree 6
    {
        float x = 0.40f, y = 0.0f, scale = 0.7f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }
    // Tree 7
    {
        float x = 0.65f, y = 0.0f, scale = 0.6f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }
    // Tree 8
    {
        float x = 0.90f, y = 0.0f, scale = 0.5f;
        glColor3f(0.55f, 0.27f, 0.07f); // trunk
        glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.06f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.06f*scale);
        glEnd();
        glColor3f(0.0f, 0.6f, 0.0f); // leaves
        drawCircle(x - 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x + 0.025f*scale, y + 0.08f*scale, 0.03f*scale);
        drawCircle(x, y + 0.11f*scale, 0.03f*scale);
    }
}
//road
void drawRoadCity()
{
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.35f);
    glVertex2f( 1.0f, -0.35f);
    glVertex2f( 1.0f,  0.0f);
    glVertex2f(-1.0f,  0.0f);
    glEnd();
}
//stone
void drawStone(float x, float y, float size)
{
    glColor3f(0.4f, 0.4f, 0.4f);
    drawCircle(x, y, size);
}

void drawStonesLeftSide()
{
    float roadY = -0.35f;
    for(float x = -0.95f; x <= 0.95f; x += 0.10f)
    {
        drawStone(x, roadY, 0.015f);
        drawStone(x + 0.03f, roadY + 0.02f, 0.012f);
    }
}
//car
void drawCar(float x, float y, bool leftToRight)
{
    // Car body
    if(leftToRight)
        glColor3f(0.9f, 0.1f, 0.1f);
    else
        glColor3f(0.1f, 0.1f, 0.9f);

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 0.20f, y);
    glVertex2f(x + 0.20f, y + 0.06f);
    glVertex2f(x, y + 0.06f);
    glEnd();

    // Car top
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.04f, y + 0.06f);
    glVertex2f(x + 0.16f, y + 0.06f);
    glVertex2f(x + 0.13f, y + 0.095f);
    glVertex2f(x + 0.07f, y + 0.095f);
    glEnd();

    // WINDOWS
    glColor3f(0.6f, 0.8f, 1.0f);

    // window 1
    glBegin(GL_QUADS);
    glVertex2f(x + 0.06f, y + 0.068f);
    glVertex2f(x + 0.095f, y + 0.068f);
    glVertex2f(x + 0.095f, y + 0.088f);
    glVertex2f(x + 0.06f, y + 0.088f);
    glEnd();

    // window 2
    glBegin(GL_QUADS);
    glVertex2f(x + 0.105f, y + 0.068f);
    glVertex2f(x + 0.14f, y + 0.068f);
    glVertex2f(x + 0.14f, y + 0.088f);
    glVertex2f(x + 0.105f, y + 0.088f);
    glEnd();
    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(x + 0.05f, y - 0.01f, 0.02f);
    drawCircle(x + 0.15f, y - 0.01f, 0.02f);

// HEADLIGHTS
if(isNight)
{
    glColor3f(1.0f, 1.0f, 0.6f);
    if(leftToRight)
    {
        glBegin(GL_TRIANGLES);
        glVertex2f(x + 0.20f, y + 0.04f);
        glVertex2f(x + 0.28f, y + 0.02f);
        glVertex2f(x + 0.28f, y + 0.06f);
        glEnd();
    }
    else
    {
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 0.04f);
        glVertex2f(x - 0.08f, y + 0.02f);
        glVertex2f(x - 0.08f, y + 0.06f);
        glEnd();
    }
}

}

//field
void drawFieldCity()
{
    glColor3f(0.0f, 0.6f, 0.0f);

    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, -0.35);
    glVertex2f(-1, -0.35);
    glEnd();
}
//bush
void drawBushCity(float x, float y)
{
    glColor3f(0.0f, 0.5f, 0.0f);
    drawCircle(x - 0.03f, y, 0.04f);
    drawCircle(x + 0.03f, y, 0.04f);
    drawCircle(x, y + 0.03f, 0.04f);
}
// field flower
void drawFlowerCity(float x, float y)
{
    glColor3f(1, 0, 0);
    drawCircle(x, y, 0.012f);

    glColor3f(1, 1, 0);
    drawCircle(x, y + 0.015f, 0.008f);

    glColor3f(0, 0.6f, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.04f);
    glEnd();
}
//grass
void drawFieldDecor()
{
    //back
    glColor3f(0.25f, 0.70f, 0.35f);
    glBegin(GL_TRIANGLES);
    for(float x = -1; x <= 1; x += 0.05f)
    {
        glVertex2f(x, -1.0f);
        glVertex2f(x + 0.025f, -0.72f);
        glVertex2f(x + 0.05f, -1.0f);
    }
    glEnd();

    //front
    glColor3f(0.10,0.55,0.20);
    glBegin(GL_TRIANGLES);
    for(float x = -1; x <= 1; x += 0.04f)
    {
        glVertex2f(x, -1.0f);
        glVertex2f(x + 0.02f, -0.75f);
        glVertex2f(x + 0.04f, -1.0f);
    }
    glEnd();

    // flower
    float flowerPositions[8][2] = {
        {-0.85f, -0.82f}, {-0.60f, -0.80f}, {-0.35f, -0.83f}, {-0.10f, -0.81f},
        {0.15f, -0.84f}, {0.40f, -0.82f}, {0.65f, -0.83f}, {0.90f, -0.81f}
    };
    for(int i = 0; i < 8; i++)
    {
        float x = flowerPositions[i][0];
        float y = flowerPositions[i][1];

        // stem
        glColor3f(0, 0.6f, 0);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y + 0.05f);
        glEnd();

        //flower
        glColor3f(0.6,0.8,1);
        drawCircle(x, y + 0.06f, 0.015f);

        // flower center
        glColor3f(1, 1, 0);
        drawCircle(x, y + 0.06f, 0.007f);
    }
}
void drawTrafficLight(float x, float y)
{
    // Pole
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 0.02f, y);
        glVertex2f(x + 0.02f, y + 0.35f);
        glVertex2f(x, y + 0.35f);
    glEnd();

    // Light box
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.04f, y + 0.35f);
        glVertex2f(x + 0.06f, y + 0.35f);
        glVertex2f(x + 0.06f, y + 0.52f);
        glVertex2f(x - 0.04f, y + 0.52f);
    glEnd();

    // RED
    if(trafficState == 0) glColor3f(1,0,0);
    else glColor3f(0.3f,0,0);
    drawCircle(x + 0.01f, y + 0.48f, 0.02f);

    // YELLOW
    if(trafficState == 1) glColor3f(1,1,0);
    else glColor3f(0.3f,0.3f,0);
    drawCircle(x + 0.01f, y + 0.435f, 0.02f);

    // GREEN
    if(trafficState == 2) glColor3f(0,1,0);
    else glColor3f(0,0.3f,0);
    drawCircle(x + 0.01f, y + 0.39f, 0.02f);
}
void drawBusStand(float x, float y)
{
    // Roof
    glColor3f(0.2f, 0.2f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.18f);
        glVertex2f(x + 0.30f, y + 0.18f);
        glVertex2f(x + 0.28f, y + 0.22f);
        glVertex2f(x + 0.02f, y + 0.22f);
    glEnd();

    // Pillars
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.02f, y);
        glVertex2f(x + 0.04f, y);
        glVertex2f(x + 0.04f, y + 0.18f);
        glVertex2f(x + 0.02f, y + 0.18f);

        glVertex2f(x + 0.26f, y);
        glVertex2f(x + 0.28f, y);
        glVertex2f(x + 0.28f, y + 0.18f);
        glVertex2f(x + 0.26f, y + 0.18f);
    glEnd();

    // Bench
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.06f, y + 0.04f);
        glVertex2f(x + 0.24f, y + 0.04f);
        glVertex2f(x + 0.24f, y + 0.07f);
        glVertex2f(x + 0.06f, y + 0.07f);
    glEnd();
}
void drawLampPost(float x, float y)
{
    // Pole
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 0.02f, y);
        glVertex2f(x + 0.02f, y + 0.4f);
        glVertex2f(x, y + 0.4f);
    glEnd();

    // Arm
    glBegin(GL_QUADS);
        glVertex2f(x + 0.02f, y + 0.35f);
        glVertex2f(x + 0.10f, y + 0.35f);
        glVertex2f(x + 0.10f, y + 0.33f);
        glVertex2f(x + 0.02f, y + 0.33f);
    glEnd();

    // Lamp bulb
    if(isNight)
        glColor3f(1.0f, 1.0f, 0.6f);
    else
        glColor3f(0.3f, 0.3f, 0.3f);

    drawCircle(x + 0.11f, y + 0.33f, 0.025f);
    // Light glow
    if(isNight)
    {
        glColor4f(1.0f, 1.0f, 0.5f, 0.3f);
        drawCircle(x + 0.11f, y + 0.25f, 0.08f);
    }
}

void displayCity()
{
    glClear(GL_COLOR_BUFFER_BIT);

drawSkyCity();
drawStarsCity();
drawSunMoonCity();

    if (isNight)
{
    drawSunMoonCity();
    if (star1) drawStar(-0.8f, 0.9f);
    if (star2) drawStar(-0.3f, 0.85f);
    if (star3) drawStar(0.2f, 0.9f);
    if (star4) drawStar(0.6f, 0.88f);
}
    drawCloud(cloud1X, 0.8);
    drawCloud(cloud2X, 0.75);
    drawCloud(cloud3X, 0.85);
    drawBuildings();
    drawTreeSet();
    drawRoadCity();
    drawStonesLeftSide();
    drawCar(carLeftX,  -0.28f, true);
    drawCar(carRightX, -0.18f, false);

drawFieldCity();
drawBushCity(-0.8f, -0.6f);
drawBushCity(-0.4f, -0.7f);
drawBushCity(0.2f, -0.65f);
drawBushCity(0.7f, -0.75f);
drawBushCity(-0.9f, -0.6f);
drawBushCity(-0.6f, -0.75f);
drawBushCity(-0.3f, -0.65f);
drawBushCity(0.1f, -0.7f);
drawBushCity(0.4f, -0.6f);
drawBushCity(0.7f, -0.75f);
drawBushCity(0.9f, -0.65f);

drawFlowerCity(-0.6f, -0.55f);
drawFlowerCity(-0.2f, -0.75f);
drawFlowerCity(0.3f, -0.6f);
drawFlowerCity(0.8f, -0.7f);
drawFlowerCity(-0.85f, -0.55f);
drawFlowerCity(-0.55f, -0.7f);
drawFlowerCity(-0.25f, -0.6f);
drawFlowerCity(0.05f, -0.75f);
drawFlowerCity(0.35f, -0.6f);
drawFlowerCity(0.65f, -0.7f);
drawFlowerCity(0.85f, -0.55f);
drawLampPost(-0.7f, -0.35f);
drawLampPost(-0.3f, -0.35f);
drawLampPost(0.1f, -0.35f);
drawLampPost(0.5f, -0.35f);
drawBusStand(0.55f, -0.35f);        // footpath side
drawTrafficLight(-0.15f, -0.35f);   // near road
drawRain();
drawSnow();
drawFieldDecor();

    glutSwapBuffers();
}
void updateTrafficLight()
{
    trafficTimer++;

    if(trafficTimer > 300)   // change every ~3 sec
    {
        trafficState = (trafficState + 1) % 3;
        trafficTimer = 0;
    }
}
void idle()
{
    updateTrafficLight();
    glutPostRedisplay();
}
void update(int)
{
    if(isPaused)
{
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
    return;
}
    if(rainOn)
{
    for(int i = 0; i < 300; i++)
    {
        rainY[i] -= rainSpeed;
        if(rainY[i] < -1.0f)
            rainY[i] = 1.0f + (i % 10) * 0.1f;
    }
}
    if(snowOn)
{
    for(int i = 0; i < 300; i++)
    {
        snowY[i] -= snowSpeed;

        if(i % 2 == 0)
            snowX[i] += 0.0005f;
        else
            snowX[i] -= 0.0005f;

        if(snowY[i] < -1.0f)
            snowY[i] = 1.0f + (i % 10) * 0.1f;
    }
}
    if(currentScene==1)
 {
    planeX += 0.01f * globalSpeed;
    planeY = -0.4 + 0.3*(planeX + 1.0f);

    cloudX1 += 0.002; if(cloudX1 > 1.3) cloudX1 = -1.3;
    cloudX2 += 0.002; if(cloudX2 > 1.3) cloudX2 = -1.3;
    cloudX3 += 0.002; if(cloudX3 > 1.3) cloudX3 = -1.3;

    static int t=0;
    t++;
    if(t>20)
    {
        runwayLightOn = !runwayLightOn;
        planeNavLightOn = !planeNavLightOn;
        tailLightOn = !tailLightOn;
        starsVisibleAirport = !starsVisibleAirport;
        t=0;
    }
    if(planeX > 1.2)
    {
        planeX = -1;
        planeY = -0.4;
    }
carX -= 0.005f;
if(carX < -1.2f)
    carX = 0.65f;
}
else if(currentScene==2){
    trainX += 0.01 * globalSpeed;
    if(trainX > 1.5) trainX = -1.6;

    smokeY += 0.01;
if(smokeY > 0.4) smokeY = 0.10;

// Cloud
cloudX0 += 0.002; if(cloudX0 > 1.4) cloudX0 = -1.4;
cloudX1 += 0.002; if(cloudX1 > 1.4) cloudX1 = -1.4;
cloudX2 += 0.002; if(cloudX2 > 1.4) cloudX2 = -1.4;
cloudX3 += 0.002; if(cloudX3 > 1.4) cloudX3 = -1.4;

// Bird
birdX0 -= 0.01; if(birdX0 < -1.4) birdX0 = 1.4;
birdX1 -= 0.01; if(birdX1 < -1.4) birdX1 = 1.4;
birdX2 -= 0.01; if(birdX2 < -1.4) birdX2 = 1.4;

    boat1X += 0.003;
    if(boat1X > 1.2) boat1X = -1.2;

    boat2X -= 0.002;
    if(boat2X < -1.2) boat2X = 1.2;
// blink star
static int starCounter = 0;
starCounter++;
if(starCounter > 15)
{
    starsVisibleTrain = !starsVisibleTrain;
    starCounter = 0;
}
}
else if(currentScene == 3)
{
    cloud1X += 0.002;
    cloud2X += 0.0015;
    cloud3X += 0.001;

    if (cloud1X > 1.2) cloud1X = -1.2;
    if (cloud2X > 1.2) cloud2X = -1.2;
    if (cloud3X > 1.2) cloud3X = -1.2;

planeX += planeSpeed;
if(planeX > 1.3f)
    planeX = -1.3f;

    carLeftX += 0.01f * globalSpeed;
    if(carLeftX > 1.2f) carLeftX = -1.2f;

    carRightX -= 0.012f * globalSpeed;
    if(carRightX < -1.2f) carRightX = 1.2f;

//star blinking
    starCounter++;
if (starCounter > 20)
{
    star1 = !star1;
    star2 = !star2;
    star3 = !star3;
    star4 = !star4;
    starCounter = 0;
    }
}
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}
void initRain()
{
    for(int i = 0; i < 300; i++)
    {
        rainX[i] = -1.0f + (i % 30) * 0.07f;
        rainY[i] = -1.0f + (i * 0.03f);
    }
}
void initSnow()
{
    for(int i = 0; i < 300; i++)
    {
        snowX[i] = -1.0f + (i % 30) * 0.07f;
        snowY[i] = -1.0f + (i * 0.025f);
    }
}
void display()
{
    if(currentScene == 1)
        displayAirport();
    if(currentScene==2)
        displayTrain();
    if(currentScene==3)
        displayCity();
}
void keyboardInput(unsigned char key,int x,int y)
{
    if(key=='1') currentScene = 1;//Airport
    if(key=='2') currentScene = 2;//train
    if(key=='3') currentScene = 3;//city

    if(key=='n'||key=='N')
    {
        isNightAirport = true;
        isNightTrain   = true;
        isNight= true;
    }
    if(key=='d'||key=='D')
    {
        isNightAirport = false;
        isNightTrain   = false;
        isNight = false;
    }
    if(key == 'r' || key == 'R') {
    rainOn = true;
    snowOn = false;
}
    if(key == 's' || key == 'S'){
    snowOn = false;
    rainOn = false;
    }

    if(key == 'p' || key == 'P')
    isPaused = true;

    if(key == 'c' || key == 'C')
    isPaused = false;

    if(key == '+')
    globalSpeed += 0.2;

    if(key == '-')
    globalSpeed -= 0.2;

    if(key == 'w' || key == 'W') {
    snowOn = true;
    rainOn = false;
}
if(globalSpeed < 0.2) globalSpeed = 0.2;
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Graphics project");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardInput);
    glutTimerFunc(30, update, 0);
    initRain();
    initSnow();
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
