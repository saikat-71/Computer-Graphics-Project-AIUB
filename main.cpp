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

//airport
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

void drawPlane()
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
    drawPlane();
    drawRain();
    drawSnow();

    glutSwapBuffers();
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
    planeY = -0.4 + 0.3*(planeX + 1.0f); // rises as it moves right

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
else{
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
    else
        displayTrain();
}

void keyboardInput(unsigned char key,int x,int y)
{
    if(key=='1') currentScene = 1;
    if(key=='2') currentScene = 2;

    if(key=='n'||key=='N')
    {
        isNightAirport = true;
        isNightTrain   = true;
    }
    if(key=='d'||key=='D')
    {
        isNightAirport = false;
        isNightTrain   = false;
    }
    if(key == 'r' || key == 'R') {
    rainOn = true;
    snowOn = false;
}

    if(key == 's' || key == 'S')
    rainOn = false;
    snowOn = false;

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

    glutMainLoop();
    return 0;

}