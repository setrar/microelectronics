#include "GL/gl.h"
#include "GL/glu.h"

enum GlutDisplayModeType {
    GLUT_SINGLE = 0
    ,GLUT_DOUBLE = 1
    ,GLUT_RGB  = 0x04
};

enum GlutGetType {
   GLUT_SCREEN_WIDTH
  ,GLUT_SCREEN_HEIGHT
};

void glutWireCube(float Size);
void glutWireCone(float base,float height,int slices,int stacks);
void glutWireTorus(float innerRadius, float outerRadius,int sides,int rings);
void glutWireSphere(float radius,int slices,int stacks);

void glutSwapBuffers(void);
void glutInit(int *argc,char *argv[]);
void glutInitDisplayMode(enum GlutDisplayModeType Mode);
int glutCreateWindow(const char *Name);
void glutDestroyWindow(int win);
void glutInitWindowPosition(int X,int Y);
void glutInitWindowSize(int W,int H);
void glutDisplayFunc(void (*Func)(void));
void glutReshapeFunc(void (*Func)(int w,int h));
void glutMainLoop(void);

void glutPostRedisplay(void);
void glutIdleFunc(void (*Func)(void));

int glutGet(enum GlutGetType Which);
void glutSetWindow(int win);
int glutGetWindow(void);