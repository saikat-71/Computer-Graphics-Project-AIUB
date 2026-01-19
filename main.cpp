#include <GL/glut.h>
#include <cmath>
using namespace std;

float planeX = -1.0f;
float planeY = -0.4f;
float runwayX = 0.0f;

float cloudX1 = -1.2f;
float cloudX2 = -0.4f;
float cloudX3 = 0.6f;

float carX = 0.65f;

bool isNight = false;
bool runwayLightOn = true;
bool planeNavLightOn = true;
bool tailLightOn = true;
bool starsVisible = true;

//CIRCLE
void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);
    for(int i=0;i<100;i++)
    {
        float a = 2 * 3.1416f * i / 100;
        glVertex2f(x + r*cos(a), y + r*sin(a));
    }
    glEnd();
}

//SUN/MOON/STARS
void drawSunMoonStars()
{
    if(isNight)
    {
        // Moon
        glColor3f(1,1,1);
        drawCircle(0.75f, 0.6f, 0.1f);

        // Stars (twinkling)
        if(starsVisible)
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

//CLOUD
void drawCloud(float x, float y)
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
    if(isNight && runwayLightOn)
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
    if(isNight) glColor3f(1, 1, 0.3);
    else glColor3f(0.2, 0.4, 0.8);

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
            if(isNight)
                glColor3f(1.0,1.0,0.4);
            else
                glColor3f(0.2,0.4,0.8);

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
    drawApartment(0.25f, -0.1f, 4);  // 4-floor
    drawApartment(0.52f, -0.1f, 5);  // 5-floor
    drawApartment(0.80f, -0.1f, 3);  // 3-floor
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

    //NAVIGATION LIGHTS
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
    if(isNight)
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
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(isNight)
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
    drawPlane();

    glutSwapBuffers();
}
void update(int)
{
    planeX += 0.01f;
    planeY = -0.4 + 0.3*(planeX + 1.0f);

    runwayX -= 0.03f;
    if(runwayX < -0.4) runwayX = 0;

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
        starsVisible = !starsVisible;
        t=0;
    }
//MOVEMENT
    if(planeX > 1.2)
    {
        planeX = -1;
        planeY = -0.4;
    }
carX -= 0.005f;
if(carX < -1.2f)
    carX = 0.65f;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void keyboard(unsigned char key,int,int)
{
    if(key=='n'||key=='N') isNight=true;
    if(key=='d'||key=='D') isNight=false;
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(900,600);
    glutCreateWindow("Airplane Takeoff");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, update, 0);
    glutMainLoop();
    return 0;
}
