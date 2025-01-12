#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// ======================Deklarasi variabel global=================================
GLfloat cameraX = 0.0f, cameraY = 0.0f, cameraZ = 10.0f;
GLfloat cameraZoom = 10.0f;
GLfloat cameraAngleX = 0.0f, cameraAngleY = 0.0f;
GLfloat targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;

static int rotasimerkurius = 0, Merkurius = 0, rotasivenus = 0, Venus = 0,
           rotasibumi = 0, Bumi = 0, Bulan = 0, rotasimars = 0, Mars = 0,
           rotasijupiter = 0, Jupiter = 0, rotasisaturnus = 0, Saturnus = 0,
           rotasiuranus = 0, Uranus = 0, rotasineptunus = 0, Neptunus = 0,
           rotasimatahari = 0;

GLfloat diffuseMaterial[4] = {0.5f, 0.5f, 0.5f, 1.0f};
bool hidden = false;
bool showOrbits = false;

GLuint matahariTexture, merkuriusTexture, venusTexture, bumiTexture, bulanTexture,
       marsTexture, jupiterTexture, saturnusTexture, uranusTexture, neptunusTexture,
       cincinTexture;
// ======================Fungsi utilitas=================================


void hiddenCarte();

//muhammad fahmi
void drawCartecius()
{
    glColor3f(255.0, 255.0, 255.0); 
    glBegin(GL_LINES); 

    // Gambar sumbu x
    glVertex3f(-10.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    // Gambar sumbu y
    glVertex3f(0.0, -10.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    
    // Gambar sumbu z
    glVertex3f(0.0, 0.0, -10.0);
    glVertex3f(0.0, 0.0, 10.0);

    glEnd();
}

//muhammad fahmi
void DrawStars() {
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 100; ++i) {
        float x = (rand() % 200 - 100) / 10.0f;
        float y = (rand() % 200 - 100) / 10.0f;
        float z = (rand() % 200 - 100) / 10.0f;
        glVertex3f(x, y, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

//muhammad fahmi
void DrawOrbitRing(GLfloat radius) {
    glBegin(GL_LINE_LOOP); 
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex3f(cos(angle) * radius, 0.0f, sin(angle) * radius);
    }
    glEnd(); 
    glLineWidth(1.0f); 
}

//muhammad fahmi 
GLuint loadTexture(const char* filename) {
    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filename, 0), filename);
    if (!bitmap) {
        printf("Gagal memuat tekstur: %s\n", filename);
        exit(1);
    }

    FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
    int width = FreeImage_GetWidth(pImage);
    int height = FreeImage_GetHeight(pImage);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(pImage));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FreeImage_Unload(pImage);
    FreeImage_Unload(bitmap);

    return textureID;
}

//muhammad agus
void drawTexturedSphere(GLuint textureID, GLfloat radius) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, radius, 50, 50);
    gluDeleteQuadric(quad);
    glDisable(GL_TEXTURE_2D);
}

//muhammad faiz
void drawTexturedRing(GLuint textureID, GLfloat innerRadius, GLfloat outerRadius) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);

    glPushMatrix();
    gluDisk(quad, innerRadius, outerRadius, 100, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
    glDisable(GL_TEXTURE_2D);
}


// ======================Fungsi inisialisasi=================================
//muhammad faiz
void myinit(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    glShadeModel(GL_SMOOTH);          
    glEnable(GL_DEPTH_TEST);    

    GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0}; 
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; 
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0}; 

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    matahariTexture = loadTexture("textures/matahari.jpg");
    merkuriusTexture = loadTexture("textures/merkurius.jpg");
    venusTexture = loadTexture("textures/venus.jpg");
    bumiTexture = loadTexture("textures/bumi.png");
    bulanTexture = loadTexture("textures/bulan.jpg");
    marsTexture = loadTexture("textures/mars.jpg");
    jupiterTexture = loadTexture("textures/jupiter.jpg");
    saturnusTexture = loadTexture("textures/saturnus.jpg");
    cincinTexture = loadTexture("textures/saturnusring.png");
    uranusTexture = loadTexture("textures/uranus.jpg");
    neptunusTexture = loadTexture("textures/neptunus.jpg");

    
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

// ======================Fungsi rendering utama=================================
// Muhammad agus
void display(void) 
{
	GLfloat position[]={0.0,0.0,1.5,1.0}; 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	GLfloat eyeX = cameraX + cameraZoom * sin(cameraAngleY * M_PI / 180.0f) * cos(cameraAngleX * M_PI / 180.0f);
	GLfloat eyeY = cameraY + cameraZoom * sin(cameraAngleX * M_PI / 180.0f);
	GLfloat eyeZ = cameraZ + cameraZoom * cos(cameraAngleY * M_PI / 180.0f) * cos(cameraAngleX * M_PI / 180.0f);
	gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);
	
	hiddenCarte();
	
	glPushMatrix(); 
	DrawStars();
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glDisable(GL_LIGHTING);
	glRotatef((GLfloat)rotasimatahari,0.0,1.0,0.0); 
	GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	drawTexturedSphere(matahariTexture, 2.0);  
	glPopMatrix();
	
	// Jika showOrbits true, gambar orbit
	if (showOrbits) {
	        glDisable(GL_LIGHTING);
	        glColor3f(0.5f, 0.5f, 0.5f); // Warna orbit (abu-abu)
	
	        DrawOrbitRing(3.0f); // Orbit Venus
	        DrawOrbitRing(4.5f); // Orbit Bumi
	        DrawOrbitRing(6.0f); // Orbit Mars
	        DrawOrbitRing(7.5f); // Orbit Jupiter
	        DrawOrbitRing(10.0f); // Orbit Saturnus
	        DrawOrbitRing(12.0f); // Orbit Uranus
	        DrawOrbitRing(14.0f); // Orbit Neptunus
	        DrawOrbitRing(16.0f); 
	        glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan
	    }
	
	glPushMatrix();
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	GLfloat light_diffuse[] = {1.0, 1.0, 0.8, 1.0}; 
	GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0}; 
	
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef((GLfloat)Merkurius,0.0,1.0,0.0); 
	glTranslatef(3.0,0.0,0.0); 
	glRotatef((GLfloat)rotasimerkurius,0.0,1.0,0.0); 
	drawTexturedSphere(merkuriusTexture, 0.4);  
	glPopMatrix();
	
	glPushMatrix(); 
	glRotatef((GLfloat)Venus,0.0,1.0,0.0);
	glTranslatef(4.5,0.0,0.5);
	glRotatef((GLfloat)rotasivenus,0.0,1.0,0.0);
	drawTexturedSphere(venusTexture, 0.5);   
	glPopMatrix();
	
	glPushMatrix(); 
	glRotatef((GLfloat)Bumi,0.0,1.0,0.0);
	glTranslatef(6.0,0.0,0.0);
	glRotatef((GLfloat)rotasibumi,0.0,1.0,0.0);
	drawTexturedSphere(bumiTexture, 0.5);  
	
	glRotatef((GLfloat)Bulan,0.0,1.0,0.0); 
	glTranslatef(0.6,0.2,0.0); 
	drawTexturedSphere(bulanTexture, 0.2);   
	glPopMatrix();
	
	glPushMatrix(); 
	glRotatef((GLfloat)Mars,0.0,1.0,0.0);
	glTranslatef(7.5,0.0,0.0);
	glRotatef((GLfloat)rotasimars,0.0,1.0,0.0);
	drawTexturedSphere(marsTexture, 0.6);   
	glPopMatrix();
	
	glPushMatrix();
	glRotatef((GLfloat)Jupiter,0.0,1.0,0.0);
	glTranslatef(10.0,0.0,0.0);
	glRotatef((GLfloat)rotasijupiter,0.0,1.0,0.0);
	drawTexturedSphere(jupiterTexture, 1.0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef((GLfloat)Saturnus, 0.0, 1.0, 0.0); 
	glTranslatef(-12.0, 0.0, 0.0);                
	glRotatef((GLfloat)rotasisaturnus, 0.0, 1.0, 0.0);  
	
	// Gambar cincin
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0); 
	drawTexturedRing(cincinTexture, 0.8, 1.5);   
	glPopMatrix();
	
	
	drawTexturedSphere(saturnusTexture, 0.8);
	glPopMatrix();
	
	glPushMatrix(); 
	glRotatef ((GLfloat) Uranus, 0.0, 1.0,0.0);
	glTranslatef (-12.0, 0.0, 0.0);
	gluLookAt (10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 1.0); 
	glRotatef((GLfloat) rotasiuranus, 0.0, 0.0, 5.0); 
	drawTexturedSphere(uranusTexture, 0.7); 
	glPopMatrix();
	
	glPushMatrix(); 
	glRotatef ((GLfloat) Neptunus,0.0, 1.0, 0.0);
	glTranslatef (-14.0, 0.0, 0.0);
	glRotatef ((GLfloat) rotasineptunus, 0.0, 1.0, 0.0);
	drawTexturedSphere(neptunusTexture, 0.8);
	glPopMatrix();
	
	glutSwapBuffers(); 
	}
	
	// ======================Fungsi event handling=================================
	//muhammad faiz
	void TimerFunction(int value) {
	    rotasimerkurius = (rotasimerkurius + 2) % 360; Merkurius = (Merkurius + 6) % 360;
	    rotasivenus = (rotasivenus + 3) % 360; Venus = (Venus + 5) % 360;
	    rotasibumi = (rotasibumi + 4) % 360; Bumi = (Bumi + 5) % 360;
	    rotasimars = (rotasimars + 5) % 360; Mars = (Mars + 4) % 360;
	    rotasijupiter = (rotasijupiter + 6) % 360; Jupiter = (Jupiter + 4) % 360;
	    rotasisaturnus = (rotasisaturnus + 7) % 360; Saturnus = (Saturnus + 3) % 360;
	    rotasiuranus = (rotasiuranus + 3) % 360; Uranus = (Uranus + 2) % 360;
	    rotasineptunus = (rotasineptunus + 3) % 360; Neptunus = (Neptunus + 1) % 360;
	    rotasimatahari = (rotasimatahari + 3) % 360;
	    Bulan=(Bulan+5)%360;
	    
	
	    glutPostRedisplay();
	    glutTimerFunc(2500/60, TimerFunction, 1);
	}
	
	//muhammad faiz
	void reshape(int w,int h)
	{
	glViewport(0,0,(GLsizei)w,(GLsizei)h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	
	gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Fungsi untuk menangani input dari keyboard
//muhammad fahmi
void keyboard(unsigned char key, int x, int y) { 
    switch (key) {
        case '+':  
            cameraZoom -= 0.5f;
            if (cameraZoom < 2.0f) cameraZoom = 2.0f;
            break;
        case '-':  
            cameraZoom += 0.5f;
            if (cameraZoom > 30.0f) cameraZoom = 30.0f;
            break;
        case 'c':  
            hidden = !hidden;
            break;
        case 'o': 
            showOrbits = !showOrbits;
            break;
        case 27:  
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();  
}

//muhammad agus
void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            cameraAngleY -= 5.0f;  
            break;
        case GLUT_KEY_RIGHT:
            cameraAngleY += 5.0f;  
            break;
        case GLUT_KEY_UP:
            cameraAngleX -= 5.0f; 
            if (cameraAngleX < -89.0f) cameraAngleX = -89.0f;  
            break;
        case GLUT_KEY_DOWN:
            cameraAngleX += 5.0f;  
            if (cameraAngleX > 89.0f) cameraAngleX = 89.0f;  
            break;
        default:
            break;
    }
    glutPostRedisplay();  
}

//muhammad fahmi
void hiddenCarte()
{
    if (hidden)
    {
        drawCartecius();
    }
}

// ======================Fungsi Main=================================
int main(int argc,char **argv) 
//muhammad faiz
{
glutInit(&argc,argv); 
glewInit();
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); 
glutInitWindowSize(500,500); 
glutInitWindowPosition(100,100); 
glutCreateWindow("TB Kelompok 4-Tata Surya"); 
myinit(); 
glutDisplayFunc(display);
glutReshapeFunc(reshape); 
glutKeyboardFunc(keyboard); 
glutSpecialFunc(specialKeyboard);  
glutTimerFunc(33, TimerFunction, 1);
glEnable(GL_DEPTH_TEST);
glutDisplayFunc(display);
glutMainLoop(); 
return 0; 
}
