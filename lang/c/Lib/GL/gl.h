#ifndef _GL_INCLUDE
#define _GL_INCLUDE	1

typedef float GLfloat;

enum GlMatrixModeType {
    GL_PROJECTION = 0
    , GL_MODELVIEW = 1
};

enum GlBeginModeType {
    GL_POINTS = 0
    , GL_LINES
    , GL_LINE_STRIP
    , GL_LINE_LOOP
    , GL_TRIANGLES
    , GL_TRIANGLE_STRIP
    , GL_TRIANGLE_FAN
    , GL_QUADS
    , GL_QUAD_STRIP
    , GL_POLYGON
    , GL_INVALID_BEGIN = 0xf
};

enum GLClearModeType {
    GL_COLOR_BUFFER_BIT = 1
    , GL_DEPTH_BUFFER_BIT = 2
    , GL_STENCIL_BUFFER_BIT = 4
};

enum GLPolygonMode0Type {
    GL_FRONT_AND_BACK = 1
};

enum GLPolygonMode1Type {
    GL_LINE = 1
};

void glViewport(int X, int Y, int Width, int Height);
void glFrustum(float left,float right,float bottom,float top,float near,float far);
void glOrtho(float left,float right,float bottom,float top,float near,float far);
void glOrtho2D(float left,float right,float bottom,float top);
void glMatrixMode(enum GlMatrixModeType Which);
void glLoadIdentity(void);
void glScalef(float Sx,float Sy,float Sz);
void glTranslatef(float Tx, float Ty, float Tz);
void glRotatef(float angle, float x, float y, float z);
void glVertex3f(float X, float Y, float Z);
void glVertex3fv(float In[3]);
void glColor3f(float R,float G,float B);
void glColor3fv(float In[3]);
void glNormal3f(float X, float Y, float Z);
void glNormal3fv(float In[3]);
void glTexCoord2f(float S, float T);
void glTexCoord2fv(float In[2]);
void glBegin(enum GlBeginModeType Mode);
void glEnd(void);

void glClearColor(float R,float G,float B,float A);

void glClear(enum GLClearModeType Mode);

void glPushMatrix(void);
void glPopMatrix(void);
void glMultMatrixf(float *Xform);

void glFlush();
void glFinish();

void glPolygonMode(enum GLPolygonMode0Type Face,enum GLPolygonMode1Type Mode);

#endif
