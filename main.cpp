#include "GL/freeglut.h"
#include <stdio.h>
#include <windows.h>
#include <math.h>

float angle = 0.0;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zoom = -15.0f;
static int lastMouseX = -1;
static int lastMouseY = -1;

static GLfloat earthOrbit = 0.0f;
static GLfloat moonOrbit = 0.0f;
static GLfloat marsOrbit = 0.0f;
//static GLuint mercuryOrbit = 0.0f;
static GLfloat JupiterOrbit = 0.0f;
static GLfloat UranusOrbit = 0.0f;
static GLfloat NeptuneOrbit = 0.0f;
static GLfloat VenusOrbit = 0.0f;
static GLfloat SaturnOrbit = 0.0f;

void TimerFunction(int value) {
    earthOrbit += 0.5f;
    moonOrbit += 2.0f;
    marsOrbit += 0.5f;
    JupiterOrbit += 0.5f;
    UranusOrbit += 0.5f;
    NeptuneOrbit += 0.5f;
    VenusOrbit += 0.5f;
    SaturnOrbit += 0.5f;
    //mercuryOrbit += 0.5f;

    if (earthOrbit > 360.0f) earthOrbit -= 360.0f;
    if (moonOrbit > 360.0f) moonOrbit -= 360.0f;
    if (marsOrbit > 360.0f) marsOrbit -= 360.0f;
    if (JupiterOrbit > 360.0f) JupiterOrbit -= 360.0f;
    if (UranusOrbit > 360.0f) UranusOrbit -= 360.0f;
    if (NeptuneOrbit > 360.0f) NeptuneOrbit -= 360.0f;
    if (VenusOrbit > 360.0f) VenusOrbit -= 360.0f;
    if (SaturnOrbit > 360.0f) SaturnOrbit -= 360.0f;
    //if (mercuryOrbit > 360.0f) mercuryOrbit -= 360.0f;


    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

void DrawOrbitRing(GLfloat radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex3f(cos(angle) * radius, 0.0f, sin(angle) * radius);
    }
    glEnd();
}

void ChangeSize(int w, int h) {
    GLfloat fAspect;

    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, fAspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}
void MouseMotion(int x, int y) {
    if (lastMouseX >= 0 && lastMouseY >= 0) {
        xRot += (y - lastMouseY);
        yRot += (x - lastMouseX);
    }
    lastMouseX = x;
    lastMouseY = y;
    glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        lastMouseX = -1;
        lastMouseY = -1;
    }
}

void KeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            zoom += 1.0f;
            break;
        case '-':
            zoom -= 1.0f;
            break;
        case 27: // Escape key
            exit(0);
    }
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN) xRot += 5.0f;
    if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT) yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);
    glutPostRedisplay();
}
void DrawEllipticalOrbit(GLfloat a, GLfloat b) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex3f(cos(angle) * a, 0.0f, sin(angle) * b);
    }
    glEnd();
}
void DrawStars() {
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 1000; ++i) {
        float x = (rand() % 200 - 100) / 10.0f;
        float y = (rand() % 200 - 100) / 10.0f;
        float z = (rand() % 200 - 100) / 10.0f;
        glVertex3f(x, y, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}
void SetMaterial(float ambient[], float diffuse[], float specular[], float shininess) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
void LookAt() {
    gluLookAt(0.0f, 2.0f, zoom,  // Camera position
              0.0f, 0.0f, 0.0f,   // Look at point
              0.0f, 1.0f, 0.0f);  // Up vector
}
void renderText(float x, float y, float z, const char* text) {
    glRasterPos3f(x, y, z);  // Set the position for the text
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}
void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLUquadricObj *pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    glLoadIdentity();
    glTranslatef(0.0, -0.2, -5.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    LookAt();
    DrawStars();

    // Sun
    float sunAmbient[] = { 1.0f, 0.5f, 0.0f, 1.0f };
    float sunDiffuse[] = { 1.0f, 0.6f, 0.0f, 1.0f };
    float sunSpecular[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    SetMaterial(sunAmbient, sunDiffuse, sunSpecular, 80.0f);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(angle * 0.04, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.5, 30, 30);

    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    DrawEllipticalOrbit(1.2f, 0.8f);
    DrawEllipticalOrbit(2.8f, 2.0f);
    DrawEllipticalOrbit(4.8f, 3.6f);
    DrawEllipticalOrbit(6.2f, 4.8f);
    DrawEllipticalOrbit(7.4f, 6.0f);
    DrawEllipticalOrbit(8.6f, 7.2f);
    DrawEllipticalOrbit(9.8f, 8.4f);
    DrawEllipticalOrbit(11.0f, 9.6f);

    //mercury
    float mercuryAmbient[] = { 0.3f, 0.3f, 0.9f, 1.0f };
    float mercuryDiffuse[] = { 0.2f, 0.2f, 0.8f, 1.0f };
    float mercurySpecular[] = { 0.3f, 0.3f, 0.7f, 1.0f };
    SetMaterial(mercuryAmbient, mercuryDiffuse, mercurySpecular, 60.0f);
    GLfloat a = 1.2f;
    GLfloat b = 0.8f;
    GLfloat mercuryX = a * cos(earthOrbit * 3.14159f / 180.0f);
    GLfloat mercuryZ = b * sin(earthOrbit * 3.14159f / 180.0f);

    glTranslatef(mercuryX, 0.00, mercuryZ);
    glRotatef(angle * 58.6, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.15, 30, 30);

    //venus
    float venusAmbient[] = { 0.4f, 0.4f, 0.8f, 1.0f };
    float venusDiffuse[] = { 0.3f, 0.3f, 0.7f, 1.0f };
    float venusSpecular[] = { 0.4f, 0.4f, 0.8f, 1.0f };
    SetMaterial(venusAmbient, venusDiffuse, venusSpecular, 60.0f);
    a = 1.6f;
    b = 1.2f;
    GLfloat venusX = a * cos(VenusOrbit * 3.14159f / 180.0f);
    GLfloat venusZ = b * sin(VenusOrbit * 3.14159f / 180.0f);

    glTranslatef(venusX, 0.00, venusZ);
    glRotatef(angle * -243, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.2, 30, 30);

    // Earth
    float earthAmbient[] = { 0.2f, 0.2f, 1.0f, 1.0f };
    float earthDiffuse[] = { 0.1f, 0.1f, 0.9f, 1.0f };
    float earthSpecular[] = { 0.2f, 0.2f, 0.6f, 1.0f };
    SetMaterial(earthAmbient, earthDiffuse, earthSpecular, 60.0f);
    a = 2.0f;   // Semi-major axis
    b = 1.6f;   // Semi-minor axis
    GLfloat earthX = a * cos(earthOrbit * 3.14159f / 180.0f);
    GLfloat earthZ = b * sin(earthOrbit * 3.14159f / 180.0f);

    glTranslatef(earthX, 0.0, earthZ);
    glRotatef(angle * 365, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.35, 30, 30);
    //float nameOffset = 0.2f;  // Offset to avoid overlap with the planet
    //renderText(earthX , 0.0f, earthZ, "Earth");

    glColor3f(1.0f, 1.0f, 1.0f);
    DrawOrbitRing(0.8f);
    glPopMatrix();
    // Moon
    glPushMatrix();
    float moonAmbient[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    float moonDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float moonSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    SetMaterial(moonAmbient, moonDiffuse, moonSpecular, 30.0f);
    glRotatef(moonOrbit, 0.0, 1.0, 0.0);
    glTranslatef(0.8, 0.0, 0.0);
    glRotatef(angle * 1.03, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.15, 30, 30);
    glPopMatrix();

    //Mars
    float marsAmbient[] = { 0.4f, 0.2f, 0.1f, 1.0f };
    float marsDiffuse[] = { 0.8f, 0.3f, 0.1f, 1.0f };
    float marsSpecular[] = { 0.3f, 0.2f, 0.1f, 1.0f };
    SetMaterial(marsAmbient, marsDiffuse, marsSpecular, 30.0f);
    a = 1.4f;
    b = 1.2f;
    GLfloat marsX = a * cos(marsOrbit * 3.14159f / 180.0f);
    GLfloat marsZ = b * sin(marsOrbit * 3.14159f / 180.0f);

    glTranslatef(marsX, 0.00, marsZ);
    gluSphere(pObj, 0.18, 30, 30);

    //Jupiter
    float JupiterAmbient[] = { 0.5f, 0.3f, 0.2f, 1.0f };
    float JupiterDiffuse[] = { 0.8f, 0.5f, 0.3f, 1.0f };
    float JupiterSpecular[] = { 0.3f, 0.2f, 0.1f, 1.0f };
    SetMaterial(JupiterAmbient, JupiterDiffuse, JupiterSpecular, 25.0f);
    a = 1.2f;
    b = 1.2f;
    GLfloat JupiterX = a * cos(JupiterOrbit * 3.14159f / 180.0f);
    GLfloat JupiterZ = b * sin(JupiterOrbit * 3.14159f / 180.0f);

    glTranslatef(JupiterX, 0.00, JupiterZ);
    glRotatef(angle * 0.41, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.4, 30, 30);

    //Saturn
    float SaturnAmbient[] = { 0.6f, 0.5f, 0.3f, 1.0f };
    float SaturnDiffuse[] = { 0.9f, 0.8f, 0.6f, 1.0f };
    float SaturnSpecular[] = { 0.3f, 0.3f, 0.2f, 1.0f };
    SetMaterial(SaturnAmbient, SaturnDiffuse, SaturnSpecular, 20.0f);
    a = 1.2f;
    b = 1.2f;
    GLfloat SaturnX = a * cos(SaturnOrbit * 3.14159f / 180.0f);
    GLfloat SaturnZ = b * sin(SaturnOrbit * 3.14159f / 180.0f);

    glTranslatef(SaturnX, 0.0, SaturnZ);
    glRotatef(angle * 0.44, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.26, 30, 30);

    //Uranus
    float UranusAmbient[] = { 0.3f, 0.5f, 0.7f, 1.0f };
    float UranusDiffuse[] = { 0.5f, 0.8f, 0.9f, 1.0f };
    float UranusSpecular[] = { 0.3f, 0.6f, 0.8f, 1.0f };
    SetMaterial(UranusAmbient, UranusDiffuse, UranusSpecular, 30.0f);
    a = 1.2f;
    b = 1.2f;
    GLfloat UranusX = a * cos(UranusOrbit * 3.14159f / 180.0f);
    GLfloat UranusZ = b * sin(UranusOrbit * 3.14159f / 180.0f);

    glTranslatef(UranusX, 0.0, UranusZ);
    glRotatef(angle * -0.72, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.24, 30, 30);

    //Neptune
    float NeptuneAmbient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
    float NeptuneDiffuse[] = { 0.1f, 0.2f, 0.8f, 1.0f };
    float NeptuneSpecular[] = { 0.2f, 0.3f, 0.9f, 1.0f };
    SetMaterial(NeptuneAmbient, NeptuneDiffuse, NeptuneSpecular, 40.0f);
    a = 1.2f;
    b = 1.2f;
    GLfloat NeptuneX = a * cos(NeptuneOrbit * 3.14159f / 180.0f);
    GLfloat NeptuneZ = b * sin(NeptuneOrbit * 3.14159f / 180.0f);

    glTranslatef(NeptuneX, 0.0, NeptuneZ);
    glRotatef(angle * 0.67, 0.0, 1.0, 0.0);
    gluSphere(pObj, 0.23, 30, 30);
    glPopMatrix();

    glutSwapBuffers();
}
void SetupRC() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    float lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Narnii aimag");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);

    glutKeyboardFunc(KeyboardFunc);
    glutMotionFunc(MouseMotion);
    glutMouseFunc(MouseButton);
    SetupRC();
    glutTimerFunc(33, TimerFunction, 1);
    glutMainLoop();
    return 0;
}
