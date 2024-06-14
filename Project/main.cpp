#include <gl/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float xrot = 0;
float yrot = 180;
float xdiff = 0;
float ydiff = 0;
bool mouseDown = false;

float xpos = 0;
float ypos = 0;
float zpos = -300;

GLuint dindingTexture;
GLuint lantaiTexture;
GLuint mejaTexture;
GLuint alasmejaTexture;
GLuint tvTexture;
GLuint layartvTexture;
GLuint kakisofaTexture;
GLuint bawahsofaTexture;
GLuint atassofaTexture;

GLuint LoadTexture(const char *filename) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);

    if (data == NULL) {
        printf("Error loading texture %s\n", filename);
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return textureID;
}

void ukur(int lebar, int tinggi) {
    if (tinggi == 0) tinggi = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)lebar / (float)tinggi, 5, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void myinit(void) {
    glClearColor(0.1, 0.1, 0.1, 0.0);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0); // Enable light 0
    glMatrixMode(GL_MODELVIEW);
    glPointSize(10.0);
    glLineWidth(7.0f);
    
    dindingTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/dinding.jpg");
    lantaiTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/lantai.jpg");
    mejaTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/meja.jpg");
    alasmejaTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/biru_kain.jpg");
    tvTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/tv.jpg");
    layartvTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/layar_tv.jpg");
    kakisofaTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/kaki_sofa.jpg");
    bawahsofaTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/bawah_sofa.jpg");
    atassofaTexture = LoadTexture("C:/Users/ACER/Desktop/living_room/image/atas_sofa.jpg");
    
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { -25.0f, -25.0f, 25.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    GLfloat mat_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
}

void idle() {
    if (!mouseDown) {
        xrot += 0.3;
        yrot += 0.4;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else {
        mouseDown = false;
    }
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            zpos += 5;
            break;
        case 's':
            zpos -= 5;
            break;
        case 'a':
            yrot -= 5;
            break;
        case 'd':
            yrot += 5;
            break;
    }
    glutPostRedisplay();
}

void tampilan(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xpos, ypos, zpos, 0, 0, 0, 0, 1, 0);
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glEnable(GL_LIGHTING);
	
	glPushMatrix();
	
	// Gambar ruang 3D
	// Dinding belakang
	glBindTexture(GL_TEXTURE_2D, dindingTexture);
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-60, 50, -70); // bawah kiriws
	glTexCoord2f(1, 0); glVertex3f(70, 50, -70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -45, -70); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -45, -70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(70, 50, -70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(70, 50, -75); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -45, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(70, -45, -70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-60, 50, -75); // bawah kiriws
	glTexCoord2f(1, 0); glVertex3f(70, 50, -75); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -45, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -45, -75); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-60, 50, -70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-60, 50, -75); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-60, -45, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -45, -70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-60, 50, -70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(70, 50, -70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, 50, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, 50, -75); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//bawah
	glTexCoord2f(0, 0); glVertex3f(-60, -45, -70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(70, -45, -70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -45, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -45, -75); // atas kiri
	glEnd();
	
	// Dinding kiri
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-65, 50, 70); // bawah kiriws
	glTexCoord2f(1, 0); glVertex3f(-60, 50, 70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-60, -45, 70); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-65, -45, 70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-60, 50, 70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-60, 50, -70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-60, -45, -70); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -45, 70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-65, 50, -75); // bawah kiriws
	glTexCoord2f(1, 0); glVertex3f(-60, 50, -75); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-60, -45, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-65, -45, -75); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-65, 50, 70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-65, 50, -75); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-65, -45, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-65, -45, 70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-65, 50, 70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-60, 50, 70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-60, 50, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-65, 50, -75); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//bawah
	glTexCoord2f(0, 0); glVertex3f(-65, -45, 70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-60, -45, 70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-60, -45, -75); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-65, -45, -75); // atas kiri
	glEnd();
	
	// Lantai
	glBindTexture(GL_TEXTURE_2D, lantaiTexture);
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-60, -40, 70); // bawah kiriws
	glTexCoord2f(1, 0); glVertex3f(70, -40, 70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -45, 70); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -45, 70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(70, -40, 70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(70, -40, -70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -45, -70); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(70, -45, 70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-60, -40, 70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(70, -40, 70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -40, -70); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -40, -70); // atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//bawah
	glTexCoord2f(0, 0); glVertex3f(-60, -45, 70); // bawah kiri
	glTexCoord2f(1, 0); glVertex3f(70, -45, 70); // bawah kanan
	glTexCoord2f(1, 1); glVertex3f(70, -45, -70); // atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60, -45, -70); // atas kiri
	glEnd();
	
	//meja
	glBindTexture(GL_TEXTURE_2D, mejaTexture);
	//alas meja
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(25,-15,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(45,-15,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(45,-15,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(25,-15,15);//atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(45,-15,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-15,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-15,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(45,-15,-30);//atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//belakang	
	glTexCoord2f(0, 0); glVertex3f(25,-15,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(45,-15,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(45,-15,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(25,-15,-30);//atas kiri
	glEnd();
	
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(20,-15,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(25,-15,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(25,-15,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-15,-30);//atas kiri
	glEnd();
	
	//bagian alas meja
	glBegin(GL_POLYGON);//bawah
	glTexCoord2f(0, 0); glVertex3f(20,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-20,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-20,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(20,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-20,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-15,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-15,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(50,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-20,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-15,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(50,-15,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(20,-20,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-20,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-15,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-15,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(20,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(20,-20,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(20,-15,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-15,20);//atas kiri
	glEnd();
	
	//kaki meja 1
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(20,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(25,-40,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(25,-20,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-20,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(25,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(25,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(25,-20,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(25,-20,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(20,-40,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(25,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(25,-20,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-20,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(20,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(20,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(20,-20,15);//atas kanan
	glTexCoord2f(0, 1);glVertex3f(20,-20,20);//atas kiri
	glEnd();
	
	//kaki meja 2
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(45,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-40,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-20,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(45,-20,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(50,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-20,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(50,-20,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(45,-40,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-20,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(45,-20,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(45,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(45,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(45,-20,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(45,-20,20);//atas kiri
	glEnd();
	
	//kaki meja 3
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(45,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-40,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-20,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(45,-20,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(50,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(50,-20,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(45,-40,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(50,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(50,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(45,-20,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(45,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(45,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(45,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(45,-20,-25);//atas kiri
	glEnd();
	
	//kaki meja 4
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(20,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(25,-40,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(25,-20,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-20,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(25,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(25,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(25,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(25,-20,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(20,-40,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(25,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(25,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-20,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(20,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(20,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(20,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(20,-20,-25);//atas kiri
	glEnd();
	
	//alas meja
	glBindTexture(GL_TEXTURE_2D, alasmejaTexture);
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(25,-15,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(45,-15,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(45,-15,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(25,-15,-25);//atas kiri
	glEnd();
	
	//tv
	//bawah tv
	glBindTexture(GL_TEXTURE_2D, tvTexture);
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(30,-15,5);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(40,-15,5);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(40,-13,5);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,-13,5);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(40,-15,5);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(40,-15,-15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(40,-13,-15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(40,-13,5);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(30,-15,-15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(40,-15,-15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(40,-13,-15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,-13,-15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(30,-15,5);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(30,-15,-15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(30,-13,-15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,-13,5);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(30,-13,5);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(40,-13,5);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(40,-13,-15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,-13,-15);//atas kiri
	glEnd();
	
	//stand tv
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(33,-13,-2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(37,-13,-2);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(37,4,-2);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(33,4,-2);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(37,-13,-2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(37,-13,-8);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(37,4,-8);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(37,4,-2);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(33,-13,-8);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(37,-13,-8);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(37,4,-8);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(33,4,-8);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(33,-13,-2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(33,-13,-8);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(33,4,-8);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(33,4,-2);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(33,4,-2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(37,4,-2);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(37,4,-8);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(33,4,-8);//atas kiri
	glEnd();
	
	//kerangka layar
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(30,-10,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(33,-10,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(33,22,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,22,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(33,-10,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(33,-10,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(33,22,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(33,22,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(30,-10,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(33,-10,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(33,22,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,22,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(30,22,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(33,22,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(33,22,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,22,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//bawah
	glTexCoord2f(0, 0); glVertex3f(30,-10,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(33,-10,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(33,-10,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,-10,-25);//atas kiri
	glEnd();
	
	//frame layar
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(30,-10,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(30,-10,14);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(30,22,14);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,22,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(30,-10,-24);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(30,-10,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(30,22,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,22,-24);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(30,21,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(30,21,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(30,22,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,22,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//bawah
	glTexCoord2f(0, 0); glVertex3f(30,-10,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(30,-10,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(30,-9,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(30,-9,15);//atas kiri
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, layartvTexture);
	glBegin(GL_POLYGON);//layar
	glVertex3f(30,-9,14);//bawah kiri
	glVertex3f(30,-9,-24);//bawah kanan
	glVertex3f(30,21,-24);//atas kanan
	glVertex3f(30,21,14);//atas kiri
	glEnd();
	
	//sofa
	glBindTexture(GL_TEXTURE_2D, kakisofaTexture);
	//kaki sofa 1
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-58,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-53,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-53,-35,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-58,-40,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-58,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-58,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-58,-35,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,20);//atas kiri
	glEnd();
	
	//kaki sofa 2
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-37,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-32,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-32,-35,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-37,-40,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-37,-40,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-37,-40,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-37,-35,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,20);//atas kiri
	glEnd();
	
	//kaki sofa 3
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-58,-40,2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,2);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,2);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,2);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-53,-40,2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-3);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-3);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-53,-35,2);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-58,-40,-3);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-3);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-3);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,-3);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-58,-40,2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-58,-40,-3);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-58,-35,-3);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,2);//atas kiri
	glEnd();
	
	//kaki sofa 4
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-37,-40,2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,2);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,2);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,2);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-32,-40,2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-3);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-3);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-32,-35,2);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-37,-40,-3);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-3);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-3);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,-3);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-37,-40,2);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-37,-40,-3);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-37,-35,-3);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,2);//atas kiri
	glEnd();
	
	//kaki sofa 5
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-58,-40,-7);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-7);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-7);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,-7);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-53,-40,-7);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-12);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-12);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-53,-35,-7);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-58,-40,-12);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-12);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-12);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,-12);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-58,-40,-7);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-58,-40,-12);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-58,-35,-12);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,-7);//atas kiri
	glEnd();
	
	//kaki sofa 6
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-37,-40,-7);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-7);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-7);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,-7);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-32,-40,-7);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-12);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-12);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-32,-35,-7);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-37,-40,-12);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-12);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-12);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,-12);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-37,-40,-7);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-37,-40,-12);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-37,-35,-12);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,-7);//atas kiri
	glEnd();
	
	//kaki sofa 7
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-58,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-53,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-53,-35,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-58,-40,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-53,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-53,-35,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-58,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-58,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-58,-35,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-58,-35,-25);//atas kiri
	glEnd();
	
	//kaki sofa 8
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-37,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-32,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-32,-35,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-37,-40,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-32,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-32,-35,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kiri
	glTexCoord2f(0, 0); glVertex3f(-37,-40,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-37,-40,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-37,-35,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-37,-35,-25);//atas kiri
	glEnd();
	
	//kerangka sofa
	//bawah
	glBindTexture(GL_TEXTURE_2D, bawahsofaTexture);
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-60,-35,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-35,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-25,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60,-25,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-30,-35,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-35,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-25,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-30,-25,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-60,-35,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-35,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-25,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60,-25,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-60,-25,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-25,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-25,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60,-25, -30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//bawah
	glTexCoord2f(0, 0); glVertex3f(-60,-35,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-35,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-35,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60,-35,-30);//atas kiri
	glEnd();
	
	//atas
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-60,-25,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-55,-25,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-55,5,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60,5,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-55,-25,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-55,-25,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-55,5,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,5,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-60,-25,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-55,-25,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-55,5,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60,5,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-60,5,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-55,5,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-55,5,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-60,5,-30);//atas kiri
	glEnd();
	
	//bantalan bawah
	glBindTexture(GL_TEXTURE_2D, atassofaTexture);
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-55,-25,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-25,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-20,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,-20,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-30,-25,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-25,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-30,-20,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-55,-25,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-25,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,-20,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-55,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-20,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-20,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,-20,-30);//atas kiri
	glEnd();
	
	//bantalan kanan
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-50,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-20,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-50,-10,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-30,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-20,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-30,-10,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-50,-20,15);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-20,15);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,-10,15);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-50,-10,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-10,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,15);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-50,-10,15);//atas kiri
	glEnd();
	
	//bantalan kiri
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-50,-20,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-20,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,-25);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-50,-10,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-30,-20,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-20,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-30,-10,-25);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-50,-20,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-20,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-50,-10,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-50,-10,-25);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-30,-10,-25);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-30,-10,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-50,-10,-30);//atas kiri
	glEnd();
	
	//bantalan belakang
	glBegin(GL_POLYGON);//depan
	glTexCoord2f(0, 0); glVertex3f(-55,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-50,-20,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-50,5,20);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,5,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//kanan
	glTexCoord2f(0, 0); glVertex3f(-50,-20,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-50,-20,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-50,5,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-50,5,20);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//belakang
	glTexCoord2f(0, 0); glVertex3f(-55,-20,-30);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-50,-20,-30);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-50,5,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,5,-30);//atas kiri
	glEnd();
	glBegin(GL_POLYGON);//atas
	glTexCoord2f(0, 0); glVertex3f(-55,5,20);//bawah kiri
	glTexCoord2f(1, 0); glVertex3f(-50,5,20);//bawah kanan
	glTexCoord2f(1, 1); glVertex3f(-50,5,-30);//atas kanan
	glTexCoord2f(0, 1); glVertex3f(-55,5,-30);//atas kiri
	glEnd();
	
	
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("LIVING ROOM 3D");
    myinit();
    glutDisplayFunc(tampilan);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(ukur);
    glutMainLoop();
    myinit();
    return 0;
}
