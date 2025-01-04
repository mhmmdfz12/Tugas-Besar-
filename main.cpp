#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

//variabel global untuk rotasi setiap objek
static int m=0,M=0,v=0,V=0,E=0,e=0,r=0,R=0,j=0,J=0,s=0,S=0,U=0,u=0,n=0,N=0,X=0,z=0,B=0,b=0,c=0;
static GLint axis=2; //variabel untuk menentukan sumbu rotasi
GLfloat diffuseMaterial[4]={0.5,0.5,0.5,1.0}; //material diffuse untuk pencahayaan
//initialize material property,light soure,lighting model,and depth buffer/

void myinit(void)
{
	glClearColor(0.0,0.0,0.0,0.0); // Mengatur warna latar belakang menjadi hitam.
	glShadeModel(GL_SMOOTH); // Menggunakan model shading yang mulus (smooth shading).
	glEnable(GL_DEPTH_TEST); // Mengaktifkan depth test untuk pengujian kedalaman.
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0}; // Properti material untuk kilauan (specular).
	GLfloat light_position[]={1.0,1.0,1.0,0.0}; // Menentukan posisi sumber cahaya.
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseMaterial); // Mengatur material difus untuk objek.
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular); // Mengatur material specular untuk objek.
	glMaterialf(GL_FRONT,GL_SHININESS,25.0); // Mengatur tingkat kilap material.
	glEnable(GL_LIGHTING); // Mengaktifkan sistem pencahayaan OpenGL.
	glEnable(GL_LIGHT0); // Mengaktifkan sumber cahaya 0.
	glLightfv(GL_LIGHT0,GL_POSITION,light_position); // Mengatur posisi sumber cahaya.
	glColorMaterial(GL_FRONT,GL_DIFFUSE); // Menentukan bahwa warna material sesuai dengan warna objek.
	glEnable(GL_COLOR_MATERIAL); // Mengaktifkan fitur warna material.
}

void  drawOrbit(float adius)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i <360; i++) {
		float angle = i * M_PI / 180.0f;
		glVertex3f(radius * cos(angle), 0.0f, radius * sin(angle));
	}
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLoadIdentity();
	
	gluLookAt(0.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.0);
	glutSolidSphere(2.5, 50, 50);
	glPopMatrix();
	
	for (float radius = 3.0; radius < 10.0; radius += 1.5) {
		drawOrbit(radius);
		
		glPushMatrix();
		glRotatef(gglutGet(GLUT_ELAPSED_TIME)* 0.01 * (10.0 / radius), 0.0, 1.0, 0.0);
		glTranslatef(radius, 0.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidSphere(0.5, 30, 30);
		glPopMatrix();
		
		GLfloat position[]={0.0,0.0,1.5,1.0}; // Posisi dinamis sumber cahaya.
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Membersihkan buffer warna dan kedalaman.
	glColor3f(1.0,0.5,0.0); // Mengatur warna matahari.
	glPushMatrix(); // Menyimpan matriks transformasi saat ini.
	glRotatef((GLfloat)z,1.0,1.0,1.0); // Mengatur rotasi matahari.
	glLightfv(GL_LIGHT0,GL_POSITION,position); // Memperbarui posisi sumber cahaya.
	glDisable(GL_LIGHTING); // Menonaktifkan pencahayaan agar matahari tetap terang.
	glutSolidSphere(0.8,40,16);   //draw sun/ // Menggambar matahari sebagai bola padat.
	glPopMatrix(); // Mengembalikan matriks transformasi sebelumnya.
	
	glPushMatrix(); // Menyimpan matriks transformasi.
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	glColor3f(1.5,0.5,0.0); // Mengatur warna objek torus.
	glutSolidTorus(0.2,0.9,6,20); // Menggambar torus sebagai cincin.
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Merkurius.
	glRotatef((GLfloat)M,0.0,1.0,0.0); // Rotasi planet di orbitnya.
	glTranslatef(1.5,0.0,0.0); // Posisi planet dari pusat orbit.
	glRotatef((GLfloat)m,0.0,1.0,0.0); // Rotasi planet pada sumbu sendiri.
	glColor3f(1.0,0.0,0.0); // Mengatur warna planet.
	glutSolidSphere(0.2,20,8);  //draw smaller planet mercury/ // Menggambar planet Merkurius sebagai bola.
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Venus.
	glRotatef((GLfloat)V,0.0,1.0,0.0);
	glTranslatef(2.0,0.0,1.0);
	glRotatef((GLfloat)v,0.0,1.0,0.0);
	glColor3f(7.5,9.5,1.0);
	glutSolidSphere(0.2,20,8);   //draw smaller plant venus/
	glPopMatrix();
	
	glPushMatrix(); // Menggambar planet Bumi
	glRotatef((GLfloat)E,0.0,1.0,0.0);
	glTranslatef(3.5,0.0,0.0);
	glRotatef((GLfloat)e,0.0,1.0,0.0);
	glColor3f(0.1,6.5,2.0);
	glutSolidSphere(0.2,20,8);    //draw smaller plant earth/
	
	glRotatef((GLfloat)X,0.0,1.0,0.0); // Rotasi bulan di orbitnya.
	glTranslatef(0.3,0.2,0.0); // Posisi bulan dari planet Bumi.
	glColor3f(4.3,3.5,8.0); // Mengatur warna bulan.
	glutSolidSphere(0.1,20,14);   //draw moon/
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Mars.
	glRotatef((GLfloat)R,0.0,1.0,0.0);
	glTranslatef(5.0,0.0,3.0);
	glRotatef((GLfloat)r,0.0,1.0,0.0);
	glColor3f(1.0,0.2,0.0);
	glutSolidSphere(0.2,20,8);   //draw smaller planet mars/
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Jupiter.
	glRotatef((GLfloat)J,0.0,1.0,0.0);
	glTranslatef(-2.5,0.0,1.0);
	glRotatef((GLfloat)j,0.0,1.0,0.0);
	glColor3f(0.9,0.7,0.3);
	glutSolidSphere(0.2,20,8);//draw smaller planet Jupiter/
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Saturnus.
	glRotatef((GLfloat)S,0.0,1.0,0.0);
	glTranslatef(-5.0,0.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)s,0.0,0.0,5.0);
	glColor3f(4.5,0.5,0.0);
	glutSolidSphere(0.5,20,16);  //draw smaller plant Saturn/
	}
	glutSwapBuffers();
	
	GLfloat position[]={0.0,0.0,1.5,1.0}; // Posisi dinamis sumber cahaya.
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Membersihkan buffer warna dan kedalaman.
	glColor3f(1.0,0.5,0.0); // Mengatur warna matahari.
	glPushMatrix(); // Menyimpan matriks transformasi saat ini.
	glRotatef((GLfloat)z,1.0,1.0,1.0); // Mengatur rotasi matahari.
	glLightfv(GL_LIGHT0,GL_POSITION,position); // Memperbarui posisi sumber cahaya.
	glDisable(GL_LIGHTING); // Menonaktifkan pencahayaan agar matahari tetap terang.
	glutSolidSphere(0.8,40,16);   //draw sun/ // Menggambar matahari sebagai bola padat.
	glPopMatrix(); // Mengembalikan matriks transformasi sebelumnya.
	
	glPushMatrix(); // Menyimpan matriks transformasi.
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	glColor3f(1.5,0.5,0.0); // Mengatur warna objek torus.
	glutSolidTorus(0.2,0.9,6,20); // Menggambar torus sebagai cincin.
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Merkurius.
	glRotatef((GLfloat)M,0.0,1.0,0.0); // Rotasi planet di orbitnya.
	glTranslatef(1.5,0.0,0.0); // Posisi planet dari pusat orbit.
	glRotatef((GLfloat)m,0.0,1.0,0.0); // Rotasi planet pada sumbu sendiri.
	glColor3f(1.0,0.0,0.0); // Mengatur warna planet.
	glutSolidSphere(0.2,20,8);  //draw smaller planet mercury/ // Menggambar planet Merkurius sebagai bola.
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Venus.
	glRotatef((GLfloat)V,0.0,1.0,0.0);
	glTranslatef(2.0,0.0,1.0);
	glRotatef((GLfloat)v,0.0,1.0,0.0);
	glColor3f(7.5,9.5,1.0);
	glutSolidSphere(0.2,20,8);   //draw smaller plant venus/
	glPopMatrix();
	
	glPushMatrix(); // Menggambar planet Bumi
	glRotatef((GLfloat)E,0.0,1.0,0.0);
	glTranslatef(3.5,0.0,0.0);
	glRotatef((GLfloat)e,0.0,1.0,0.0);
	glColor3f(0.1,6.5,2.0);
	glutSolidSphere(0.2,20,8);    //draw smaller plant earth/
	
	glRotatef((GLfloat)X,0.0,1.0,0.0); // Rotasi bulan di orbitnya.
	glTranslatef(0.3,0.2,0.0); // Posisi bulan dari planet Bumi.
	glColor3f(4.3,3.5,8.0); // Mengatur warna bulan.
	glutSolidSphere(0.1,20,14);   //draw moon/
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Mars.
	glRotatef((GLfloat)R,0.0,1.0,0.0);
	glTranslatef(5.0,0.0,3.0);
	glRotatef((GLfloat)r,0.0,1.0,0.0);
	glColor3f(1.0,0.2,0.0);
	glutSolidSphere(0.2,20,8);   //draw smaller planet mars/
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Jupiter.
	glRotatef((GLfloat)J,0.0,1.0,0.0);
	glTranslatef(-2.5,0.0,1.0);
	glRotatef((GLfloat)j,0.0,1.0,0.0);
	glColor3f(0.9,0.7,0.3);
	glutSolidSphere(0.2,20,8);//draw smaller planet Jupiter/
	glPopMatrix();
	
	glPushMatrix(); // Untuk planet Saturnus.
	glRotatef((GLfloat)S,0.0,1.0,0.0);
	glTranslatef(-5.0,0.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)s,0.0,0.0,5.0);
	glColor3f(4.5,0.5,0.0);
	glutSolidSphere(0.5,20,16);  //draw smaller plant Saturn/

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
	glRotatef ((GLfloat) U, 0.0, 1.0,0.0);
	glTranslatef (-6.5, 0.0, 0.0);
	gluLookAt (10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.0, 1.0); // Melihat ke arah Uranus.
	glRotatef((GLfloat) u, 0.0, 0.0, 5.0); // Rotasi planet pada sumbu sendiri.
	glColor3f( 1.2, 0.6,0.2);
	glutSolidSphere (0.5, 20, 16); /* draw smaller planet Uranus*/
	glBegin(GL_QUAD_STRIP);
	
for(i=0; i<=360; i++)
{
	glVertex3f(sin(i*3.1416/180)*0.5,cos(i*3.1416/180)*0.5, 0);
	glVertex3f(sin(i*3.1416/180)*0.7, cos(i*3.1416/180)*0.7,0);
}
	glEnd();
	glPopMatrix();


	glPushMatrix(); // Untuk planet Neptunus.
	glRotatef ((GLfloat) N,0.0, 1.0, 0.0);
	glTranslatef (-8.0, 0.0, 0.0);
	glRotatef ((GLfloat) n, 0.0, 1.0, 0.0);
	glColor3f(1.0, 2.0, 0.0);
	glutSolidSphere(0.4, 20, 8);
	glPopMatrix();/* draw smaller planet Neptune */
	
	glPushMatrix(); // Menyimpan matriks transformasi saat ini ke dalam stack
	glRotatef ((GLfloat) c, 6.0, -14.0,-6.0); // Merotasi objek sebesar sudut 'c' di sepanjang sumbu yang diberikan
	glTranslatef (5.0,3.0,-1.0); // Mentranslasikan objek dengan nilai x, y, dan z yang ditentukan
	glScalef(0.60,0.0,2.5); // Menskalakan objek di sepanjang sumbu x, y, dan z
	glColor3f (7.5, 9.5, 2.0); // Mengatur warna objek dengan nilai RGB yang ditentukan
	glutSolidSphere (0.2, 12, 6); // Menggambar bola padat dengan radius 0.2, 12 irisan, dan 6 tumpukan
	glPopMatrix();//draw comet/ // Mengembalikan matriks transformasi sebelumnya dari stack (menggambar komet)
	
	//to put the stars as a background // Untuk menampilkan bintang sebagai latar belakang
	glPushMatrix(); // Menyimpan matriks transformasi saat ini ke dalam stack
	glTranslatef(0.0,-2.0,0.0); // Mentranslasikan objek ke posisi (-2, 0, 0)
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0); // Mengatur posisi dan orientasi kamera
	glRotatef((GLfloat)b,0.0,0.0,0.0); // Merotasi latar belakang sebesar sudut 'b' (tanpa sumbu rotasi)
	glScalef(200.0,0.0,0.0); // Menskalakan latar belakang secara signifikan di sepanjang sumbu x
	glColor3f(4.3,3.5,1.0); // Mengatur warna bintang dengan nilai RGB yang ditentukan
	glutSolidSphere(0.04,20,8); // Menggambar bola kecil padat (mewakili sebuah bintang)
	glPopMatrix(); // Mengembalikan matriks transformasi sebelumnya
	
	// Mengulang proses yang sama untuk posisi bintang yang berbeda dengan offset y yang berbeda (2, -4, 4, -6, 6, dan -8)
	glPushMatrix();
	glTranslatef(0.0,2.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,-4.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,4.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,-6.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,6.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(0.0,-8.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	
	
	
	glPushMatrix();
	glTranslatef(0.0,8.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(8.0,0.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.0,-2.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6.0,4.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-6.0,4.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(5.0,-4.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-7.0,3.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	 glPushMatrix();
	glTranslatef(-7.0,2.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(7.0,-2.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(7.0,-3.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-7.0,-3.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(7.0,2.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.0,-7.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.0,-5.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,3.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(5.0,-1.0,0.0);
	gluLookAt(0.0,10.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.07,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-6.0,7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.07,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.5,3.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.07,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.5,4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.07,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-9.0,3.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.07,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(9.0,-5.9,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6.5,8.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(5.0,7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-9.0,6.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.1,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10.5,9.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.07,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-11.0,-7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.07,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-11.0,5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-7.0,-5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10.0,3.7,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-7.0,-2.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-8.0,5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.03,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-8.0,-5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11.0,-4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6.0,-5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-6.9,7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(5.0,-4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6.0,4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.0,-4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(4.0,-7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat) b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-4.0,-3.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	  glPushMatrix();
	glTranslatef(4.0,-7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	     glTranslatef(11.0,-4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	  glTranslatef(9.0,-9.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	  glTranslatef(8.0,-4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	  glTranslatef(9.0,5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef (7.0,7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.9,7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.0,6.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.8,-5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.0,-7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.0,5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.0,4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-9.0,0.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10.0,4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(9.0,3.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10.0,-6.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(10.0,0.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-9.0,-7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-3.0,4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-9.9,-7.5,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.0,5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.0,6.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-2.0,-5.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-3.0,-2.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-4.0,-8.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(8.3,-7.1,0.0);
	gluLookAt (0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10.0,7.6,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-3.0,7.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.4,7.5,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.0,6.5,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-6.0,4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-6.0,-6.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.05,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.7,4.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8); // Menggambar bola padat dengan radius 0.04, 20 irisan, dan 8 tumpukan
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.0,2.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,0.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,-1.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	 glTranslatef(0.0,1.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	 glTranslatef(0.0,2.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,0.0,0.0,0.0);
	glScalef(200.0,0.0,0.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(8.7,9.0,0.0);
	gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0);
	glRotatef((GLfloat)b,1.0,7.0,5.0);
	glColor3f(4.3,3.5,1.0);
	glutSolidSphere(0.04,20,8);
	glPopMatrix();
	glutSwapBuffers(); // Menukar buffer untuk memperbarui tampilan pada layar
}

// Fungsi untuk menangani perubahan ukuran jendela
void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h); // Mengatur ukuran tampilan berdasarkan ukuran jendela
	glMatrixMode(GL_PROJECTION); // Mengatur mode matriks menjadi proyeksi
	glLoadIdentity(); // Memuat identitas matriks untuk mengatur perspektif
	gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,20.0); // Mengatur perspektif dengan FOV 60 derajat
	glMatrixMode(GL_MODELVIEW); // Mengatur mode matriks kembali ke model tampilan
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

// Fungsi untuk menangani input dari keyboard
void keyboard(unsigned char key,int x,int y)
{
	switch(key) {
	case 'z':z=(z+50)%360; // Menambah rotasi z dan memanggil redisplay
		glutPostRedisplay();
		break;
	case 'm':m=(m+3)%360;
		glutPostRedisplay();
		break;
	case 'M':M=(M+12)%360;
		glutPostRedisplay();
		break;
	case 'v':v=(v+2)%360;
		glutPostRedisplay();
		break;
	case 'V':V=(V+10)%360;
		glutPostRedisplay();
		break;
	case 'e':e=(e+5)%360;
		glutPostRedisplay();
		break;
	case 'E':E=(E+8)%360;
		glutPostRedisplay();
			break;
	case 'r':r=(r+6)%360;
		glutPostRedisplay();
		break;
	case 'R':R=(R+6)%360;
		glutPostRedisplay();
		break;
	case 'j':j=(j+10)%360;
		glutPostRedisplay();
		break;
	case 'J':J=(J+4)%360;
		glutPostRedisplay();
			break;
	case 's':s=(s+9)%360;
		glutPostRedisplay();
			break;
	case 'S':S=(S+3)%360;
		glutPostRedisplay();
			break;
	case 'u':u=(u+8)%360;
		glutPostRedisplay();
		break;
	case 'U':U=(U+2)%360;
		glutPostRedisplay();
		break;
	case 'n':n=(n+7)%360;
		glutPostRedisplay();
		break;
	case 'N':N=(N+1)%360;
		glutPostRedisplay();
		break;
	case 'b':b=(b+10)%360;
		glutPostRedisplay();
		break;
	case 'c':c=(c+1)%360; // Menambah rotasi c dan b, kemudian redisplay
		b=(b+10)%360;
		glutPostRedisplay();
		break;
	case 'X':X=(X+5)%360;
		glutPostRedisplay();
		break;
	case 'a': // Menambah rotasi untuk beberapa variabel sekaligus dan memanggil redisplay
		z=(z+50)%360;
		b=(b+10)%360;
		m=(m+3)%360;
		v=(v+2)%360;
		e=(e+5)%360;
		r=(r+6)%360;
		j=(j+10)%360;
		s=(s+9)%360;
		u=(u+8)%360;
		n=(n+7)%360;
		c=(c+1)%360;
		glutPostRedisplay();
		break;
	case 'A': // Menambah rotasi untuk beberapa variabel sekaligus dan memanggil redisplay
		z=(z+50)%360;
		b=(b+10)%360;
		M=(M+12)%360;
		V=(V+10)%360;
		E=(E+8)%360;
		R=(R+6)%360;
		J=(J+4)%360;
		S=(S+3)%360;
		U=(U+2)%360;
		N=(N+1)%360;
		c=(c+1)%360;
			glutPostRedisplay();
		break;
	case 'B':
		z=(z+50)%360;
		b=(b+10)%360;
		c=(c+1)%360;
		m=(m+3)%360;M=(M+12)%360;
		v=(v+2)%360;V=(V+10)%360;
		e=(e+5)%360;E=(E+8)%360;
		r=(r+6)%360;R=(R+6)%360;
			j=(j+10)%360;J=(J+4)%360;
			s=(s+9)%360;S=(S+3)%360;
			u=(u+8)%360;U=(U+2)%360;
		n=(n+7)%360;N=(N+1)%360;
		glutPostRedisplay();
		break;
	case 27: // Keluar dari program ketika tombol Escape ditekan
		exit(0);
		break;
	default:break; // Tidak melakukan apa-apa untuk tombol lain
	}
}

// Fungsi untuk menangani input mouse
void mouse(int btn ,int state,int x,int y)
{
	// Jika tombol kiri mouse ditekan
if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
	// Menambahkan rotasi pada berbagai variabel untuk animasi objek
	z=(z+50)%360; // Rotasi z
	b=(b+10)%360;
	c=(c+1)%360;
	m=(m+3)%360;M=(M+12)%360;
	v=(v+2)%360;V=(V+10)%360;
	e=(e+5)%360;E=(E+8)%360;
	r=(r+6)%360;R=(R+6)%360;
	j=(j+10)%360;J=(J+4)%360;
	s=(s+9)%360;S=(S+3)%360;
	u=(u+8)%360;U=(U+2)%360;
	n=(n+7)%360;N=(N+1)%360;
	glutPostRedisplay(); // Memperbarui tampilan setelah perubahan rotasi
}

// Jika tombol tengah mouse ditekan
if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
{
	 // Mengubah rotasi objek dengan nilai yang sedikit berbeda
	z=(z+50)%360;
	b=(b+10)%360;
	c=(c+1)%360;
	m=(m+3)%360;M=(M+12)%360;
	v=(v-2)%360;V=(V-10)%360;
	e=(e+5)%360;E=(E+8)%360;
	r=(r-6)%360;R=(R-6)%360;
	j=(j+10)%360;J=(J+4)%360;
	s=(s-9)%360;S=(S-3)%360;
	u=(u+8)%360;U=(U+2)%360;
	n=(n-7)%360;N=(N-1)%360;

	 // Memperbarui tampilan setelah perubahan rotasi
	glutPostRedisplay();
}

// Jika tombol kanan mouse ditekan
if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
{
	// Mengurangi rotasi objek dengan nilai tertentu
	z=(z-50)%360;
	b=(b-10)%360;
	c=(c+1)%360;
	m=(m-3)%360;M=(M-12)%360;
	v=(v-2)%360;V=(V-10)%360;
	e=(e-5)%360;E=(E-8)%360;
	r=(r-6)%360;R=(R-6)%360;
	j=(j-10)%360;J=(J-4)%360;
	s=(s-9)%360;S=(S-3)%360;
	u=(u-8)%360;U=(U-2)%360;
	n=(n-7)%360;N=(N-1)%360;
	glutPostRedisplay();
	}
}

// Fungsi utama program
int main(int argc,char **argv)
{
	glutInit(&argc,argv); // Inisialisasi GLUT dengan argumen dari command line
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); // Menentukan mode tampilan untuk jendela OpenGL (double buffer, RGB, dan depth)
	glutInitWindowSize(500,500); // Mengatur ukuran jendela
	glutInitWindowPosition(100,100);  // Mengatur posisi jendela pada layar
	glutCreateWindow("planets amidst stars"); // Membuat jendela dengan judul
	myinit(); // Fungsi inisialisasi pengguna
	glutDisplayFunc(display); // Menetapkan fungsi untuk menggambar objek
	glutReshapeFunc(reshape); // Menetapkan fungsi untuk menangani perubahan ukuran jendela
	glutKeyboardFunc(keyboard); // Menetapkan fungsi untuk menangani input keyboard
	glutMouseFunc(mouse); // Menetapkan fungsi untuk menangani input mouse
	glEnable(GL_DEPTH_TEST); // Mengaktifkan pengujian kedalaman untuk rendering 3D yang benar
	glutMainLoop(); // Memulai loop utama GLUT yang akan terus menjalankan aplikasi
	return 0; // Return 0 sebagai tanda bahwa program selesai
}
