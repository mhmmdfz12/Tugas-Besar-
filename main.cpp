#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

// ======================Deklarasi variabel global=================================
GLfloat cameraX = 0.0f, cameraY = 0.0f, cameraZ = 10.0f;  // Posisi kamera
GLfloat cameraZoom = 10.0f;  // Jarak zoom kamera
GLfloat cameraAngleX = 0.0f; // Rotasi kamera pada sumbu X
GLfloat cameraAngleY = 0.0f; // Rotasi kamera pada sumbu Y
GLfloat targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;
static int rotasimerkurius=0, Merkurius=0, rotasivenus=0, Venus=0, 
           rotasibumi=0, Bumi=0, Bulan=0, rotasimars=0, Mars=0, rotasijupiter=0, Jupiter=0, 
           rotasisaturnus=0, Saturnus=0, rotasiuranus=0, Uranus=0, rotasineptunus=0, Neptunus=0;
GLfloat diffuseMaterial[4] = {0.5, 0.5, 0.5, 1.0}; // Material diffuse untuk pencahayaan
bool hidden = false;
bool showOrbits = false;  // Variabel untuk menampilkan atau menyembunyikan orbit

// ======================Fungsi utilitas=================================

// Deklarasi fungsi untuk menyembunyikan atau menampilkan sumbu Cartesian
void hiddenCarte();

void drawCartecius()
{
    glColor3f(255.0, 255.0, 255.0); // Mengatur warna hitam untuk sumbu
    glBegin(GL_LINES); // Memulai gambar garis

    // Gambar sumbu x
    glVertex3f(-10.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    // Gambar sumbu y
    glVertex3f(0.0, -10.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    
    // Gambar sumbu z
    glVertex3f(0.0, 0.0, -10.0);
    glVertex3f(0.0, 0.0, 10.0);

    glEnd(); // Mengakhiri gambar garis
}

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

void DrawOrbitRing(GLfloat radius) {
    glBegin(GL_LINE_LOOP); // Mulai menggambar garis loop
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f; // Konversi derajat ke radian
        glVertex3f(cos(angle) * radius, 0.0f, sin(angle) * radius); // Titik-titik pada lingkaran
    }
    glEnd(); // Akhiri menggambar
    glLineWidth(1.0f); // Atur ketebalan garis orbit
}

// ======================Fungsi inisialisasi=================================
void myinit(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Warna latar belakang hitam
    glShadeModel(GL_SMOOTH);          // Smooth shading
    glEnable(GL_DEPTH_TEST);          // Aktifkan depth test
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    // glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

// ======================Fungsi rendering utama=================================
void display(void)
{
GLfloat position[]={0.0,0.0,1.5,1.0}; // Posisi dinamis sumber cahaya.
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Membersihkan buffer warna dan kedalaman.

glLoadIdentity();
GLfloat eyeX = cameraX + cameraZoom * sin(cameraAngleY * M_PI / 180.0f) * cos(cameraAngleX * M_PI / 180.0f);
GLfloat eyeY = cameraY + cameraZoom * sin(cameraAngleX * M_PI / 180.0f);
GLfloat eyeZ = cameraZ + cameraZoom * cos(cameraAngleY * M_PI / 180.0f) * cos(cameraAngleX * M_PI / 180.0f);
gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);

hiddenCarte();

glColor3f(1.0,0.5,0.0); // Mengatur warna matahari.
glPushMatrix(); // Menyimpan matriks transformasi saat ini.
DrawStars();// Mengatur rotasi matahari.
glLightfv(GL_LIGHT0,GL_POSITION,position); // Memperbarui posisi sumber cahaya.
glDisable(GL_LIGHTING); // Menonaktifkan pencahayaan agar matahari tetap terang.
glutSolidSphere(0.8,40,50);   //draw sun/ // Menggambar matahari sebagai bola padat.
glPopMatrix(); // Mengembalikan matriks transformasi sebelumnya.

// Jika showOrbits true, gambar orbit
if (showOrbits) {
        glDisable(GL_LIGHTING); // Nonaktifkan pencahayaan untuk orbit agar terlihat jelas
        glColor3f(0.5f, 0.5f, 0.5f); // Warna orbit (abu-abu)
        DrawOrbitRing(1.5f); // Orbit Merkurius
        DrawOrbitRing(2.0f); // Orbit Venus
        DrawOrbitRing(3.5f); // Orbit Bumi
        DrawOrbitRing(5.0f); // Orbit Mars
        DrawOrbitRing(6.5f); // Orbit Jupiter
        DrawOrbitRing(8.0f); // Orbit Saturnus
        DrawOrbitRing(9.5f); // Orbit Uranus
        DrawOrbitRing(11.0f); // Orbit Neptunus
        glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan
    }

glPushMatrix(); // Menyimpan matriks transformasi.
glLightfv(GL_LIGHT0,GL_POSITION,position);
glDisable(GL_LIGHTING);
glEnable(GL_LIGHTING);
glColor3f(1.5,0.5,0.0); // Mengatur warna objek torus.
glutSolidTorus(0.2,0.9,6,20); // Menggambar torus sebagai cincin.
glPopMatrix();

glPushMatrix(); // Untuk planet Merkurius.
glRotatef((GLfloat)Merkurius,0.0,1.0,0.0); // Rotasi planet di orbitnya.
glTranslatef(1.5,0.0,0.0); // Posisi planet dari pusat orbit.
glRotatef((GLfloat)rotasimerkurius,0.0,1.0,0.0); // Rotasi planet pada sumbu sendiri.
glColor3f(1.0,0.0,0.0); // Mengatur warna planet.
glutSolidSphere(0.2,20,50);  //draw smaller planet mercury/ // Menggambar planet Merkurius sebagai bola.
glPopMatrix();

glPushMatrix(); // Untuk planet Venus.
glRotatef((GLfloat)Venus,0.0,1.0,0.0);
glTranslatef(2.0,0.0,0.5);
glRotatef((GLfloat)rotasivenus,0.0,1.0,0.0);
glColor3f(7.5,9.5,1.0);
glutSolidSphere(0.2,20,50);   //draw smaller plant venus/
glPopMatrix();

glPushMatrix(); // Menggambar planet Bumi
glRotatef((GLfloat)Bumi,0.0,1.0,0.0);
glTranslatef(3.5,0.0,0.0);
glRotatef((GLfloat)rotasibumi,0.0,1.0,0.0);
glColor3f(0.1,6.5,2.0);
glutSolidSphere(0.2,20,50);    //draw smaller plant earth/

glRotatef((GLfloat)Bulan,0.0,1.0,0.0); // Rotasi bulan di orbitnya.
glTranslatef(0.3,0.2,0.0); // Posisi bulan dari planet Bumi.
glColor3f(4.3,3.5,8.0); // Mengatur warna bulan.
glutSolidSphere(0.1,20,14);   //draw moon/
glPopMatrix();

glPushMatrix(); // Untuk planet Mars.
glRotatef((GLfloat)Mars,0.0,1.0,0.0);
glTranslatef(4.0,0.0,3.0);
glRotatef((GLfloat)rotasimars,0.0,1.0,0.0);
glColor3f(1.0,0.2,0.0);
glutSolidSphere(0.2,20,50);   //draw smaller planet mars/
glPopMatrix();

glPushMatrix(); // Untuk planet Jupiter.
glRotatef((GLfloat)Jupiter,0.0,1.0,0.0);
glTranslatef(6.5,0.0,1.0);
glRotatef((GLfloat)rotasijupiter,0.0,1.0,0.0);
glColor3f(0.9,0.7,0.3);
glutSolidSphere(0.5,20,50);//draw smaller planet Jupiter/
glPopMatrix();

glPushMatrix(); // Untuk planet Saturnus.
glRotatef((GLfloat)Saturnus,0.0,1.0,0.0);
glTranslatef(-1.0,0.0,2.0);
gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
glRotatef((GLfloat)rotasisaturnus,0.0,0.0,5.0);
glColor3f(4.5,0.5,0.0);
glutSolidSphere(0.5,20,50);  //draw smaller plant Saturn/

int i=0; // Variabel untuk lingkaran cincin Saturnus.
glBegin(GL_QUAD_STRIP); // Mulai menggambar cincin Saturnus.
for(i=0;i<=360;i++)
{
glVertex3f(sin(i*3.1416/180)*0.5,cos(i*3.1416/180)*0.5,0); // Titik dalam lingkaran.
glVertex3f(sin(i*3.1416/180)*0.7,cos(i*3.1416/180)*0.7,0); // Titik luar lingkaran.
}
glEnd(); // Selesai menggambar cincin.
glPopMatrix(); // Mengembalikan matriks transformasi sebelumnya.

glPushMatrix(); // Untuk planet Uranus.
glRotatef ((GLfloat) Uranus, 0.0, 1.0,0.0);
glTranslatef (-3.0, 0.0, 1.0);
gluLookAt (10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 1.0); // Melihat ke arah Uranus.
glRotatef((GLfloat) rotasiuranus, 0.0, 0.0, 5.0); // Rotasi planet pada sumbu sendiri.
glColor3f( 1.2, 0.6,0.2);
glutSolidSphere (0.5, 20, 50); /* draw smaller planet Uranus*/
glBegin(GL_QUAD_STRIP);
for(i=0; i<=360; i++)
{
glVertex3f(sin(i*3.1416/180)*0.5,cos(i*3.1416/180)*0.5, 0);
glVertex3f(sin(i*3.1416/180)*0.7, cos(i*3.1416/180)*0.7,0);
}
glEnd();
glPopMatrix();

glPushMatrix(); // Untuk planet Neptunus.
glRotatef ((GLfloat) Neptunus,0.0, 1.0, 0.0);
glTranslatef (11.5, 0.0, 0.0);
glRotatef ((GLfloat) rotasineptunus, 0.0, 1.0, 0.0);
glColor3f(1.0, 2.0, 0.0);
glutSolidSphere(0.4, 20, 50);
glPopMatrix();/* draw smaller planet Neptune */

glutSwapBuffers(); // Menukar buffer untuk memperbarui tampilan pada layar
}

// ======================Fungsi event handling=================================
void TimerFunction(int value) {
    rotasimerkurius = (rotasimerkurius + 1) % 360; Merkurius = (Merkurius + 12) % 360;
    rotasivenus = (rotasivenus + 1) % 360; Venus = (Venus + 10) % 360;
    rotasibumi = (rotasibumi + 2) % 360; Bumi = (Bumi + 8) % 360;
    rotasimars = (rotasimars + 3) % 360; Mars = (Mars + 6) % 360;
    rotasijupiter = (rotasijupiter + 4) % 360; Jupiter = (Jupiter + 4) % 360;
    rotasisaturnus = (rotasisaturnus + 4) % 360; Saturnus = (Saturnus + 3) % 360;
    rotasiuranus = (rotasiuranus + 3) % 360; Uranus = (Uranus + 2) % 360;
    rotasineptunus = (rotasineptunus + 3) % 360; Neptunus = (Neptunus + 1) % 360;
    Bulan=(Bulan+5)%360;
    
	glShadeModel(GL_SMOOTH);
    glutPostRedisplay();
    glutTimerFunc(2500/60, TimerFunction, 1);
}

// Fungsi untuk menangani perubahan ukuran jendela
void reshape(int w,int h)
{
glViewport(0,0,(GLsizei)w,(GLsizei)h); // Mengatur ukuran tampilan berdasarkan ukuran jendela
glMatrixMode(GL_PROJECTION); // Mengatur mode matriks menjadi proyeksi
glLoadIdentity(); // Memuat identitas matriks untuk mengatur perspektif

gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f); // Mengatur perspektif dengan FOV 60 derajat
glMatrixMode(GL_MODELVIEW); // Mengatur mode matriks kembali ke model tampilan
glLoadIdentity();
}

// Fungsi untuk menangani input dari keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':  // Zoom in
            cameraZoom -= 0.5f;
            if (cameraZoom < 2.0f) cameraZoom = 2.0f;
            break;
        case '-':  // Zoom out
            cameraZoom += 0.5f;
            if (cameraZoom > 30.0f) cameraZoom = 30.0f;
            break;
        case 'c':  // Toggle sumbu Cartesian
            hidden = !hidden;
            break;
        case 'o':  // Toggle orbit
            showOrbits = !showOrbits;
            break;
        case 27:  // Escape untuk keluar
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();  // Render ulang
}

void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            cameraAngleY -= 5.0f;  // Rotasi kamera ke kiri
            break;
        case GLUT_KEY_RIGHT:
            cameraAngleY += 5.0f;  // Rotasi kamera ke kanan
            break;
        case GLUT_KEY_UP:
            cameraAngleX -= 5.0f;  // Rotasi kamera ke atas
            if (cameraAngleX < -89.0f) cameraAngleX = -89.0f;  // Batas atas
            break;
        case GLUT_KEY_DOWN:
            cameraAngleX += 5.0f;  // Rotasi kamera ke bawah
            if (cameraAngleX > 89.0f) cameraAngleX = 89.0f;  // Batas bawah
            break;
        default:
            break;
    }
    glutPostRedisplay();  // Render ulang
}

// Fungsi untuk menentukan apakah sumbu Cartesian digambar
void hiddenCarte()
{
    if (hidden) // Jika 'hidden' bernilai true
    {
        drawCartecius(); // Menggambar sumbu Cartesian
    }
}

// ======================Fungsi Main=================================
int main(int argc,char **argv)
{
glutInit(&argc,argv); // Inisialisasi GLUT dengan argumen dari command line
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); // Menentukan mode tampilan untuk jendela OpenGL (double buffer, RGB, dan depth)
glutInitWindowSize(500,500); // Mengatur ukuran jendela
glutInitWindowPosition(100,100);  // Mengatur posisi jendela pada layar
glutCreateWindow("TB Kelompok 4-Tata Surya"); // Membuat jendela dengan judul
myinit(); // Fungsi inisialisasi pengguna
glutDisplayFunc(display); // Menetapkan fungsi untuk menggambar objek
glutReshapeFunc(reshape); // Menetapkan fungsi untuk menangani perubahan ukuran jendela
glutKeyboardFunc(keyboard); // Menetapkan fungsi untuk menangani input keyboard
glutSpecialFunc(specialKeyboard);  // Menambahkan fungsi untuk tombol panah
glutTimerFunc(33, TimerFunction, 1);
glEnable(GL_DEPTH_TEST); // Mengaktifkan pengujian kedalaman untuk rendering 3D yang benar
glutMainLoop(); // Memulai loop utama GLUT yang akan terus menjalankan aplikasi
return 0; // Return 0 sebagai tanda bahwa program selesai
}