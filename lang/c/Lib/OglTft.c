/*
    OglTft: OpenGL for 320x240 TFT display (Just vectors and points).
        Ted Rossin: 4-04-2022
                    6-30-2022
*/

#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "Tft320x240Fb.h"
#include "GL/glut.h"

#define PI2 (3.141593*2.0)

#ifdef TFT_OGL_WINDOWED
  #include "Tft320x240Wfb.h"
  #define DrawPixel(x,y,Color)        wgfDrawPixel(x,y,Color)
  #define Line(x0,y0,x1,y1,Color)     wgfLine(x0, y0, x1, y1, Color)
#else
  #define DrawPixel(x,y,Color)        gfDrawPixel(x,y,Color)
  #define Line(x0,y0,x1,y1,Color)     gfLine(x0, y0, x1, y1, Color)
#endif

#define dtr  (3.14159265358979323846f/180.0f)

    // Physical Size of display
#define PHYS_WIDTH  320
#define PHYS_HEIGHT  240

#define MAX_WINDOWS 4

static int ActiveWindow = 0;
static struct{
    float Sx;
    float Sy;
    float Tx;
    float Ty;
    float PerspXform[4][4];
    float ModelViewXform[4][4];
    float FinalXform[4][4];
    uint8_t MatrixDirty;
    float ModelViewStack[16][4][4];
    float PerspStack[2][4][4];
    int8_t ModelViewStackPtr;
    int8_t PerspStackPtr;
    enum GlMatrixModeType MatrixMode;
    enum GlBeginModeType BeginMode;
    struct {
        int Count;
        float V0[4], V1[4], V2[4], VStart[4];
        int Clip0, Clip1, Clip2,ClipStart;
        uint16_t Color; // 565 RGB color
    } VertState;
}Context[MAX_WINDOWS];

    //   Matrix array format
    //  _                              _
    // | [0][0]  [0][1]  [0][2]  [0][3] |
    // | [1][0]  [1][1]  [1][2]  [1][3] |
    // | [2][0]  [2][1]  [2][2]  [2][3] |
    // | [3][0]  [3][1]  [3][2]  [3][3] |
    // -                               -
static void matrix_1by3mult4by4(float a[3], float b[][4], float Result[4])
{
    Result[0] = a[0] * b[0][0] + a[1] * b[1][0] + a[2] * b[2][0] + b[3][0];
    Result[1] = a[0] * b[0][1] + a[1] * b[1][1] + a[2] * b[2][1] + b[3][1];
    Result[2] = a[0] * b[0][2] + a[1] * b[1][2] + a[2] * b[2][2] + b[3][2];
    Result[3] = a[0] * b[0][3] + a[1] * b[1][3] + a[2] * b[2][3] + b[3][3];
}
    
    // Compute RESULT = A*B  (It is ok to do RESULT = A * RESULT)

static void matrix_mult4by4(float a[][4], float b[][4], float result[][4])
{
    float c[4][4];

    c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0];
    c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1];
    c[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2];
    c[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3];

    c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0];
    c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1];
    c[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2];
    c[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3];

    c[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0];
    c[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1];
    c[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2];
    c[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3];

    c[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0];
    c[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1];
    c[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2];
    c[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3];

    result[0][0] = c[0][0];
    result[0][1] = c[0][1];
    result[0][2] = c[0][2];
    result[0][3] = c[0][3];

    result[1][0] = c[1][0];
    result[1][1] = c[1][1];
    result[1][2] = c[1][2];
    result[1][3] = c[1][3];

    result[2][0] = c[2][0];
    result[2][1] = c[2][1];
    result[2][2] = c[2][2];
    result[2][3] = c[2][3];

    result[3][0] = c[3][0];
    result[3][1] = c[3][1];
    result[3][2] = c[3][2];
    result[3][3] = c[3][3];
}

static void MakeIdentity(float Mat[4][4])
{
    Mat[0][0] = 1.0f;  Mat[0][1] = 0.0f;  Mat[0][2] = 0.0f;  Mat[0][3] = 0.0f;
    Mat[1][0] = 0.0f;  Mat[1][1] = 1.0f;  Mat[1][2] = 0.0f;  Mat[1][3] = 0.0f;
    Mat[2][0] = 0.0f;  Mat[2][1] = 0.0f;  Mat[2][2] = 1.0f;  Mat[2][3] = 0.0f;
    Mat[3][0] = 0.0f;  Mat[3][1] = 0.0f;  Mat[3][2] = 0.0f;  Mat[3][3] = 1.0f;
}

void glMultMatrixf(float *Xform)
{
    int i,j;


    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4((float (*)[4])Xform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4((float (*)[4])Xform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
 }
 
void glPushMatrix(void)
{
    int i,j;

    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
        if(Context[ActiveWindow].ModelViewStackPtr==15) return;
        Context[ActiveWindow].ModelViewStackPtr++;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++) Context[ActiveWindow].ModelViewStack[Context[ActiveWindow].ModelViewStackPtr][i][j] = Context[ActiveWindow].ModelViewXform[i][j];
    }
    else {
        if(Context[ActiveWindow].PerspStackPtr==1) return;
        Context[ActiveWindow].PerspStackPtr++;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++) Context[ActiveWindow].PerspStack[Context[ActiveWindow].PerspStackPtr][i][j] = Context[ActiveWindow].PerspXform[i][j];
    }
}

void glPopMatrix(void)
{
    int i,j;

    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
        if(Context[ActiveWindow].ModelViewStackPtr== -1) return;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++) Context[ActiveWindow].ModelViewXform[i][j] = Context[ActiveWindow].ModelViewStack[Context[ActiveWindow].ModelViewStackPtr][i][j];
        Context[ActiveWindow].ModelViewStackPtr--;    
    }
    else {
        if(Context[ActiveWindow].PerspStackPtr== -1) return;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++) Context[ActiveWindow].PerspXform[i][j] = Context[ActiveWindow].PerspStack[Context[ActiveWindow].PerspStackPtr][i][j];
        Context[ActiveWindow].PerspStackPtr--;    
    }
    Context[ActiveWindow].MatrixDirty = 1;
}

void glViewport(int X, int Y, int Width, int Height)
{
/*
        Display has zero at top of display so need to flip Y:
            The equation is but would like to push HEIGHT-1 into Sy and Ty

        Y0 = HEIGHT-1-(int)(Sy * Out0[1] / Out0[3] + Ty + 0.5f);
        Y0 = HEIGHT-1+(int)(-Sy * Out0[1] / Out0[3] - Ty - 0.5f);
        Y0 = (int)(-Sy * Out0[1] / Out0[3] - Ty - 0.5f + HEIGHT-1);

        New Ty = HEIGHT -1 -Ty - 0.5;
        New Sy = -Sy
*/
    Context[ActiveWindow].Sx = (float)(Width-1) / 2.0;
    Context[ActiveWindow].Sy = -(float)(Height-1) / 2.0; 
#ifdef TFT_OGL_WINDOWED
    Context[ActiveWindow].Tx = (float)(Width-1) / 2.0 + 0.5;
    Context[ActiveWindow].Ty = (float)Height -1.0 - ((float)(Height-1) / 2.0) - 0.5;
#else
    Context[ActiveWindow].Tx = X + (float)(Width-1) / 2.0 + 0.5;
    Context[ActiveWindow].Ty = (float)PHYS_HEIGHT -1.0 - (Y + (float)(Height-1) / 2.0) - 0.5;
#endif    
}

void gluLookAt(float eyex,float eyey,float eyez,float centerx,float centery,float centerz,float upx,float upy,float upz)
{
    float Xform[4][4];
    float x[3], y[3], z[3];
    float mag;

    z[0] = eyex - centerx;
    z[1] = eyey - centery;
    z[2] = eyez - centerz;
    mag = sqrt( z[0]*z[0] + z[1]*z[1] + z[2]*z[2] );
    if (mag) { z[0] /= mag; z[1] /= mag; z[2] /= mag; }

    y[0] = upx;
    y[1] = upy;
    y[2] = upz;

        // X vector = Y cross Z
    x[0] =  y[1]*z[2] - y[2]*z[1];
    x[1] = -y[0]*z[2] + y[2]*z[0];
    x[2] =  y[0]*z[1] - y[1]*z[0];

        // Recompute Y = Z cross X 
    y[0] =  z[1]*x[2] - z[2]*x[1];
    y[1] = -z[0]*x[2] + z[2]*x[0];
    y[2] =  z[0]*x[1] - z[1]*x[0];

    mag = sqrt( x[0]*x[0] + x[1]*x[1] + x[2]*x[2] );
    if (mag) { x[0] /= mag;  x[1] /= mag;  x[2] /= mag; }

    mag = sqrt( y[0]*y[0] + y[1]*y[1] + y[2]*y[2] );
    if (mag) {  y[0] /= mag;  y[1] /= mag; y[2] /= mag; }

    Xform[0][0] = x[0];  Xform[1][0] = x[1];  Xform[2][0] = x[2];  Xform[3][0] = 0.0;
    Xform[0][1] = y[0];  Xform[1][1] = y[1];  Xform[2][1] = y[2];  Xform[3][1] = 0.0;
    Xform[0][2] = z[0];  Xform[1][2] = z[1];  Xform[2][2] = z[2];  Xform[3][2] = 0.0;
    Xform[0][3] = 0.0;   Xform[1][3] = 0.0;   Xform[2][3] = 0.0;   Xform[3][3] = 1.0;
    
    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4(Xform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4(Xform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    glTranslatef(-eyex,-eyey,-eyez);

}

void glOrtho2D(float left,float right,float bottom,float top)
{
    glOrtho(left,right,bottom,top,-1.0,1.0);
}

void glOrtho(float left,float right,float bottom,float top,float near,float far)
{
    float Xform[4][4];

        // Not the same as the OGL redbook as the Z did not map to 0 to 1.0

    Xform[0][0] = 2.0/(right-left);
    Xform[0][1] = 0.0;
    Xform[0][2] = 0.0;
    Xform[0][3] = 0.0;

    Xform[1][0] = 0.0;
    Xform[1][1] = 2.0/(top-bottom);
    Xform[1][2] = 0.0;
    Xform[1][3] = 0.0;

    Xform[2][0] = 0.0;
    Xform[2][1] = 0.0;
    Xform[2][2] = -1.0/(far-near);  // Redbook -2.0/(far-near)
    Xform[2][3] = 0.0;

    Xform[3][0] = (right+left)/(right-left); 
    Xform[3][1] = (top+bottom)/(top-bottom);   
    Xform[3][2] = -near/(far-near);  // Redbook had (far+near)/(far-near)
    Xform[3][3] = 1.0;  

    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4(Xform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4(Xform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
}

void glFrustum(float left,float right,float bottom,float top,float near,float far)
{
    float Xform[4][4];

            // Row 0
    Xform[0][0] = 2.0*near/(right-left);
    Xform[0][1] = 0.0;
    Xform[0][2] = 0.0;
    Xform[0][3] = 0.0;

    Xform[1][0] = 0.0;
    Xform[1][1] = 2.0*near/(top-bottom);
    Xform[1][2] = 0.0;
    Xform[1][3] = 0.0;

    Xform[2][0] = (right+left)/(right-left);
    Xform[2][1] = (top+bottom)/(top-bottom);
    Xform[2][2] = -(far+near)/(far-near);
    Xform[2][3] = -1.0;

    Xform[3][0] = 0.0; 
    Xform[3][1] = 0.0;   
    Xform[3][2] = -2.0*far*near/(far-near);   
    Xform[3][3] = 0.0;  

    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4(Xform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4(Xform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
}

// This makes a matrix that will have an input of near_clip to far_clip
// so setting near to 10 and far to 100 the Z input range is -10 to -100 will map to 0 to 1.0
// The X and Y will map to -1.0 to 1.0 based on the Field of View(FOV) angle in Y
// clip Z if Z/W <0  and Z/W>1.0
// clip X if X/W <-1 and X/W>1.0
// clip Y if Y/W <-1 and Y/W>1.0
// After clipping and divide by W, scale by window width and height and offsets

void gluPerspective(float Fovy, float Aspect, float NearClip, float FarClip)
{
    float Height, Width;
    float Xform[4][4];

    Height = 2.0f * NearClip * (float)sin(0.5 * Fovy * dtr);
    Width = Height * Aspect;

    Xform[0][0] = 2.0f * NearClip / Width;
    Xform[0][1] = 0.0f;
    Xform[0][2] = 0.0f;
    Xform[0][3] = 0.0f;

    Xform[1][0] = 0.0f;
    Xform[1][1] = 2.0f * NearClip / Height;
    Xform[1][2] = 0.0;
    Xform[1][3] = 0.0;

    Xform[2][0] = 0.0;
    Xform[2][1] = 0.0;
    Xform[2][2] = -FarClip / (FarClip - NearClip);
    Xform[2][3] = -1.0f;

    Xform[3][0] = 0.0;
    Xform[3][1] = 0.0;
    Xform[3][2] = -FarClip * NearClip / (FarClip - NearClip);
    Xform[3][3] = 0.0;

    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4(Xform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4(Xform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
}

void glMatrixMode(enum GlMatrixModeType Which)
{
    Context[ActiveWindow].MatrixMode = Which;
}

void glLoadIdentity(void)
{
    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW)
	    MakeIdentity(Context[ActiveWindow].ModelViewXform);
    else
	    MakeIdentity(Context[ActiveWindow].PerspXform);
    Context[ActiveWindow].MatrixDirty = 1;
}

void glScalef(float Sx,float Sy,float Sz)
{
    float ScaleXform[4][4];

    MakeIdentity(ScaleXform);
    ScaleXform[0][0] = Sx;   ScaleXform[1][1] = Sy;   ScaleXform[2][2] = Sz;

    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4(ScaleXform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4(ScaleXform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
}

void glTranslatef(float Tx, float Ty, float Tz)
{
    float TransXform[4][4];

    MakeIdentity(TransXform);
    TransXform[3][0] = Tx;   TransXform[3][1] = Ty;   TransXform[3][2] = Tz;
    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4(TransXform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4(TransXform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
}

void glRotatef(float angle, float x, float y, float z)
{   // Modified and repaired from Nicol Bolas' question on StackOverflow
    float sinAngle, cosAngle,mag;
    float RotXform[4][4];
    
	// Some optimizations for simple cases:

    if (x == 1.0 && y == 0.0 && z == 0.0) {
	    float sinx, cosx;
	    sinx = (float)sin(angle * dtr); cosx = (float)cos(angle * dtr);
	    MakeIdentity(RotXform);
	    RotXform[1][1] = cosx;
	    RotXform[2][2] = cosx;
	    RotXform[2][1] = -sinx;
	    RotXform[1][2] = sinx;
    }
    else if (x == 0.0 && y == 1.0 && z == 0.0) {
	    float siny, cosy;
        siny = (float)sin(angle * dtr); cosy = (float)cos(angle * dtr);
        MakeIdentity(RotXform);
        RotXform[0][0] = cosy;
        RotXform[2][2] = cosy;
        RotXform[2][0] = -siny;
        RotXform[0][2] = siny;
    }
    else if (x == 0.0 && y == 0.0 && z == 1.0) {
        float sinz, cosz;
        sinz = (float)sin(angle * dtr); cosz = (float)cos(angle * dtr);
        MakeIdentity(RotXform);
        RotXform[0][0] = cosz;
        RotXform[1][1] = cosz;
        RotXform[1][0] = -sinz;
        RotXform[0][1] = sinz;
    }
    else { 
        mag = sqrt(x * x + y * y + z * z);
        sinAngle = sin(angle * dtr);
        cosAngle = cos(angle * dtr);

        if (mag > 0.0f) {
            float xx, yy, zz, xy, yz, zx, xs, ys, zs;
            float oneMinusCos;
            
            x /= mag;  y /= mag;  z /= mag;
            xx = x * x;  yy = y * y;  zz = z * z;
            xy = -x * y;  yz = y * -z; zx = -z * -x;
            xs = -x * sinAngle;  ys = y * sinAngle;  zs = -z * sinAngle;
            oneMinusCos = 1.0f - cosAngle;

            RotXform[0][0] = (oneMinusCos * xx) + cosAngle;
            RotXform[0][1] = (oneMinusCos * xy) + zs;
            RotXform[0][2] = (oneMinusCos * zx) - ys;
            RotXform[0][3] = 0.0f;

            RotXform[1][0] = (oneMinusCos * xy) - zs;
            RotXform[1][1] = (oneMinusCos * yy) + cosAngle;
            RotXform[1][2] = (oneMinusCos * yz) + xs;
            RotXform[1][3] = 0.0f;

            RotXform[2][0] = (oneMinusCos * zx) + ys;
            RotXform[2][1] = (oneMinusCos * yz) - xs;
            RotXform[2][2] = (oneMinusCos * zz) + cosAngle;
            RotXform[2][3] = 0.0f;

            RotXform[3][0] = 0.0f;
            RotXform[3][1] = 0.0f;
            RotXform[3][2] = 0.0f;
            RotXform[3][3] = 1.0f;
        }
        else {
            MakeIdentity(RotXform);
        }
    }
    if (Context[ActiveWindow].MatrixMode == GL_MODELVIEW) {
	    matrix_mult4by4(RotXform, Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].ModelViewXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
    else {
	    matrix_mult4by4(RotXform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].PerspXform); 
        Context[ActiveWindow].MatrixDirty = 1;
    }
}

static uint8_t FetchClipClodes(int Start,float Out[4])
{
    uint8_t Clip;
    float W = Out[3];

    Clip = 0;
    if (Start>0) {
        if (Out[0] > W) Clip |= 0x01; // XMax
        if (Out[0] < -W) Clip |= 0x02; // XMin
    }
    if (Start > 1) {
        if (Out[1] > W) Clip |= 0x04; // YMax
        if (Out[1] < -W) Clip |= 0x08; // YMin
    }
    if (Start > 2) {
        if (Out[2] > W) Clip |= 0x10; // ZMax
        if (Out[2] < 0.0) Clip |= 0x20; // ZMin
    }
    return(Clip);
}

static void gfLine3dv(float V0[4], int VClip0,float V1[4], int VClip1)
{
    float t2, W0, W1,Out0[4],Out1[4];
    int Clip0,Clip1,Coord, ClipBitMax, ClipBitMin, i, X0, Y0, X1, Y1;

    if ((VClip0 & VClip1) == 0) { // Can't trivially reject
    	    // Copy values so that they can be modified.
        for (i = 0; i < 4; i++) {
            Out0[i] = V0[i];  Out1[i] = V1[i];
        }
        Clip0 = VClip0;  Clip1 = VClip1;
        if (Clip0 || Clip1) { // Can't trivially accept
            // Need to clip the line
            for(Coord=2;Coord>=0;Coord--){  // Clip Zmin first
                ClipBitMax = 1<<(Coord+Coord);
                ClipBitMin = 1<<(Coord + Coord + 1);
                if ((Clip0 & ClipBitMin) || (Clip1 & ClipBitMin)) {  // min case
                    if (Coord == 2){ W0 = 0.0;      W1 = 0.0;	  }
                    else {	         W0 = Out0[3];  W1 = Out1[3]; }
                    t2 = (W0 + Out0[Coord]) / ((W0 + Out0[Coord]) - (W1 + Out1[Coord]));  // add for min
                    if (Clip0 & ClipBitMin) {
                        for (i = 0; i < 4; i++) Out0[i] = Out0[i] + t2 * (Out1[i] - Out0[i]);
                        Clip0 = FetchClipClodes(Coord, Out0);
                        if (Clip0 & Clip1) return;  // Now trivially reject
                    }
                    if (Clip1 & ClipBitMin) {
                        for (i = 0; i < 4; i++) Out1[i] = Out0[i] + t2 * (Out1[i] - Out0[i]);
                        Clip1 = FetchClipClodes(Coord, Out1);
                        if (Clip0 & Clip1) return;  // Now trivially reject
                    }
                }
                if ((Clip0 & ClipBitMax) || (Clip1 & ClipBitMax)) {  // max case
                    W0 = Out0[3];  W1 = Out1[3];
                    t2 = (W0 - Out0[Coord]) / ((W0 - Out0[Coord]) - (W1 - Out1[Coord]));  // subtract for max
                    if (Clip0 & ClipBitMax) {
                    for (i = 0; i < 4; i++) Out0[i] = Out0[i] + t2 * (Out1[i] - Out0[i]);
                    Clip0 = FetchClipClodes(Coord, Out0);
                    if (Clip0 & Clip1) return;  // Now trivially reject
                    }
                    if (Clip1 & ClipBitMax) {
                    for (i = 0; i < 4; i++) Out1[i] = Out0[i] + t2 * (Out1[i] - Out0[i]);
                    Clip1 = FetchClipClodes(Coord, Out1);
                    if (Clip0 & Clip1) return;  // Now trivially reject
                    }
                }
            }
        }
        X0 = (int)(Context[ActiveWindow].Sx * Out0[0] / Out0[3] + Context[ActiveWindow].Tx);  
        Y0 = (int)(Context[ActiveWindow].Sy * Out0[1] / Out0[3] + Context[ActiveWindow].Ty); 
        X1 = (int)(Context[ActiveWindow].Sx * Out1[0] / Out1[3] + Context[ActiveWindow].Tx);  
        Y1 = (int)(Context[ActiveWindow].Sy * Out1[1] / Out1[3] + Context[ActiveWindow].Ty);       
        if(X0==X1 && Y0==Y1){ // Single dot
            DrawPixel(X0,Y0,Context[ActiveWindow].VertState.Color);
        }
        else{
            Line(X0, Y0, X1, Y1,Context[ActiveWindow].VertState.Color);
        }
    }
}

void glBegin(enum GlBeginModeType Mode)
{
    Context[ActiveWindow].BeginMode = Mode;
    Context[ActiveWindow].VertState.Count = 0;
    if (Context[ActiveWindow].MatrixDirty) {
	    Context[ActiveWindow].MatrixDirty = 0;
	    matrix_mult4by4(Context[ActiveWindow].ModelViewXform, Context[ActiveWindow].PerspXform, Context[ActiveWindow].FinalXform);
    }
}

void glEnd(void)
{
    if (Context[ActiveWindow].BeginMode == GL_LINE_LOOP) {
        if (Context[ActiveWindow].VertState.Count == 1) {
            gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart);
        }
        if (Context[ActiveWindow].VertState.Count == 2) {
            gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart);
        }
    }
    Context[ActiveWindow].BeginMode = GL_INVALID_BEGIN;
}

void glColor3f(float R,float G,float B)
{
    Context[ActiveWindow].VertState.Color = COLOR565((uint8_t)(0x1f*R),(uint8_t)(0x3f*G),(uint8_t)(0x1f*B));
}

void glVertex3f(float X, float Y, float Z)
{
    float In[3];

    In[0] = X;  In[1] = Y;  In[2] = Z;
    glVertex3fv(In);
}

void glVertex3fv(float In[3])
{
    int i;

    switch (Context[ActiveWindow].BeginMode) {
        case GL_POINTS:
            matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
            if (FetchClipClodes(3, Context[ActiveWindow].VertState.V0) == 0) {
                float W = Context[ActiveWindow].VertState.V0[3];
                int X,Y;
                X = (int)(Context[ActiveWindow].Sx * Context[ActiveWindow].VertState.V0[0] / W + Context[ActiveWindow].Tx);  
                Y = (int)(Context[ActiveWindow].Sy * Context[ActiveWindow].VertState.V0[1] / W + Context[ActiveWindow].Ty);
                DrawPixel(X,Y,Context[ActiveWindow].VertState.Color);
            }
            break;

        case GL_LINES:
            if (Context[ActiveWindow].VertState.Count == 0) {
                Context[ActiveWindow].VertState.Count++;
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
            }
            else {
                Context[ActiveWindow].VertState.Count = 0;
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                gfLine3dv(Context[ActiveWindow].VertState.V0,Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);		
            }
            break;

        case GL_LINE_STRIP:
        case GL_LINE_LOOP:
        case GL_POLYGON:
            if (Context[ActiveWindow].VertState.Count == 0) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
                if (Context[ActiveWindow].BeginMode == GL_LINE_LOOP || Context[ActiveWindow].BeginMode==GL_POLYGON) {
                    Context[ActiveWindow].VertState.ClipStart = Context[ActiveWindow].VertState.Clip0;
                    for(i=0;i<4;i++) Context[ActiveWindow].VertState.VStart[i] = Context[ActiveWindow].VertState.V0[i];
                }
                Context[ActiveWindow].VertState.Count++;
            }
            else {
                if (Context[ActiveWindow].VertState.Count == 1) {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                    Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                    Context[ActiveWindow].VertState.Count = 2;
                }
                else {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                    Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                    Context[ActiveWindow].VertState.Count = 1;
                }
            }
            break;

        case GL_TRIANGLES:
            if (Context[ActiveWindow].VertState.Count == 0) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Count = 1;
            }
            else if (Context[ActiveWindow].VertState.Count == 1) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Count = 2;
            }
            else {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V2);
                Context[ActiveWindow].VertState.Clip2 = FetchClipClodes(3, Context[ActiveWindow].VertState.V2);
                gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                Context[ActiveWindow].VertState.Count = 0;
            }
            break;

        case GL_TRIANGLE_STRIP:
            if (Context[ActiveWindow].VertState.Count == 0) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Count = 1;
            }
            else if (Context[ActiveWindow].VertState.Count == 1) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Count = 2;
            }
            else if(Context[ActiveWindow].VertState.Count==2) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V2);
                Context[ActiveWindow].VertState.Clip2 = FetchClipClodes(3, Context[ActiveWindow].VertState.V2);
                gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                Context[ActiveWindow].VertState.Count = 10;
            }
            else {
                if (Context[ActiveWindow].VertState.Count == 10) {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                    Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);	
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                    gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                    Context[ActiveWindow].VertState.Count = 11;
                }
                else if (Context[ActiveWindow].VertState.Count == 11) {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                    Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                    Context[ActiveWindow].VertState.Count = 12;
                }
                else {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V2);
                    Context[ActiveWindow].VertState.Clip2 = FetchClipClodes(3, Context[ActiveWindow].VertState.V2);
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                    gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                    Context[ActiveWindow].VertState.Count = 10;
                }		
            }
            break;

        case GL_TRIANGLE_FAN:
            if (Context[ActiveWindow].VertState.Count == 0) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Count = 1;
            }
            else if (Context[ActiveWindow].VertState.Count == 1) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Count = 2;
            }
            else if(Context[ActiveWindow].VertState.Count==2) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V2);
                Context[ActiveWindow].VertState.Clip2 = FetchClipClodes(3, Context[ActiveWindow].VertState.V2);
                gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                Context[ActiveWindow].VertState.Count = 10;
            }
            else{
                if (Context[ActiveWindow].VertState.Count == 10) {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                    Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);		    
                    Context[ActiveWindow].VertState.Count = 11;
                }
                else {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V2);
                    Context[ActiveWindow].VertState.Clip2 = FetchClipClodes(3, Context[ActiveWindow].VertState.V2);
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                    Context[ActiveWindow].VertState.Count = 10;
                }
            }
            break;

        case GL_QUADS:
        case GL_QUAD_STRIP:
            if (Context[ActiveWindow].VertState.Count == 0) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
                Context[ActiveWindow].VertState.Count = 1;
            }
            else if (Context[ActiveWindow].VertState.Count == 1) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                Context[ActiveWindow].VertState.Count = 2;
            }
            else if (Context[ActiveWindow].VertState.Count == 2) {
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V2);
                Context[ActiveWindow].VertState.Clip2 = FetchClipClodes(3, Context[ActiveWindow].VertState.V2);
                Context[ActiveWindow].VertState.Count = 3;
            }
            else if(Context[ActiveWindow].VertState.Count==3){
                matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.VStart);
                Context[ActiveWindow].VertState.ClipStart = FetchClipClodes(3, Context[ActiveWindow].VertState.VStart);
                if (Context[ActiveWindow].BeginMode == GL_QUADS) {
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);		    
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                    gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart);
                    gfLine3dv(Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                    Context[ActiveWindow].VertState.Count = 0;
                }
                else {
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart);
                    gfLine3dv(Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                    gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                    Context[ActiveWindow].VertState.Count = 10;
                }		
            }
            else {
                if (Context[ActiveWindow].VertState.Count == 10) {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V0);
                    Context[ActiveWindow].VertState.Clip0 = FetchClipClodes(3, Context[ActiveWindow].VertState.V0);
                    Context[ActiveWindow].VertState.Count = 11;
                }
                else if(Context[ActiveWindow].VertState.Count==11){
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V1);
                    Context[ActiveWindow].VertState.Clip1 = FetchClipClodes(3, Context[ActiveWindow].VertState.V1);
                    gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0);
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                    gfLine3dv(Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1, Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart);   
                    Context[ActiveWindow].VertState.Count = 12;
                }
                else if (Context[ActiveWindow].VertState.Count == 12) {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.V2);
                    Context[ActiveWindow].VertState.Clip2 = FetchClipClodes(3, Context[ActiveWindow].VertState.V2);
                    Context[ActiveWindow].VertState.Count = 13;
                }
                else {
                    matrix_1by3mult4by4(In, Context[ActiveWindow].FinalXform, Context[ActiveWindow].VertState.VStart);
                    Context[ActiveWindow].VertState.ClipStart = FetchClipClodes(3, Context[ActiveWindow].VertState.VStart);
                    gfLine3dv(Context[ActiveWindow].VertState.V0, Context[ActiveWindow].VertState.Clip0, Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2);
                    gfLine3dv(Context[ActiveWindow].VertState.V2, Context[ActiveWindow].VertState.Clip2, Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart);
                    gfLine3dv(Context[ActiveWindow].VertState.VStart, Context[ActiveWindow].VertState.ClipStart, Context[ActiveWindow].VertState.V1, Context[ActiveWindow].VertState.Clip1);
                    Context[ActiveWindow].VertState.Count = 10;
                }
            }
            break;
    }
}

void glClearColor(float R,float G,float B,float A)
{
#ifdef TFT_OGL_WINDOWED    
    wgfSetClearColor(COLOR565((uint8_t)(0x1f*R),(uint8_t)(0x3f*G),(uint8_t)(0x1f*B)));
#else
    gfSetClearColor(COLOR565((uint8_t)(0x1f*R),(uint8_t)(0x3f*G),(uint8_t)(0x1f*B)));
#endif    
}

void glClear(enum GLClearModeType Mode)
{
    // Nothing to do as the swap buffer function will clear while transmitting over I2C
}


void glutWireCube(float Size)
{
    float S = Size / 2.0;

    glBegin(GL_LINE_STRIP);
        glVertex3f(-S,  S,  S);
        glVertex3f( S,  S,  S);
        glVertex3f( S, -S,  S);
        glVertex3f(-S, -S,  S);
        glVertex3f(-S,  S,  S);
        glVertex3f(-S,  S, -S);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex3f( S, S, -S);
        glVertex3f(-S, S, -S);
        glVertex3f(-S,-S, -S);
        glVertex3f( S,-S, -S);
        glVertex3f( S, S, -S);
        glVertex3f( S, S,  S);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(-S, -S, S);
        glVertex3f(-S, -S,-S);
        glVertex3f( S, -S, S);
        glVertex3f( S, -S, -S);
    glEnd();
}

                    // TubeRadius, RingRadius, NumTubeSides, NumRingSides
void glutWireTorus(float innerRadius, float outerRadius,int sides,int rings) 
{
    int i,j;
    float Angle,Step,Dx,Dy,X,Y;
    typedef struct {
        float X, Z;
        float LastX, LastY;
        float NewX, NewY;
    }Ring_t;
    Ring_t* Ring;
    
    Ring = (Ring_t*)malloc(sides * sizeof(Ring_t));
    if (Ring == NULL) return;

    Angle = 0.0;  Step = PI2 / (float)sides;
    for (i = 0; i < sides; i++) {
        Ring[i].X = outerRadius + innerRadius * cos(Angle);
        Ring[i].Z = innerRadius * sin(Angle);
        Angle += Step;
    }

    Angle = 0.0;  Step = PI2 / (float)rings;
    for (i = 0; i <= rings; i++) {
        Dx = cos(Angle);
        Dy = sin(Angle);
        if (i == rings) {
            for (j = 0; j < sides; j++) {
                X = Dx * Ring[j].X;
                Y = Dy * Ring[j].X;
                Ring[j].NewX = X;  Ring[j].NewY = Y;
            }
        }
        else {
            glBegin(GL_LINE_LOOP);
                for (j = 0; j < sides; j++) {
                    X = Dx * Ring[j].X;
                    Y = Dy * Ring[j].X;
                    glVertex3f(X, Y, Ring[j].Z);
                    Ring[j].NewX = X;  Ring[j].NewY = Y;
                }
            glEnd();
        }
        if (i != 0) {
            glBegin(GL_LINES);
                for (j = 0; j < sides; j++) {
                    glVertex3f(Ring[j].LastX, Ring[j].LastY, Ring[j].Z);
                    glVertex3f(Ring[j].NewX, Ring[j].NewY, Ring[j].Z);
                }
                glEnd();
        }
        for (j = 0; j < sides; j++) {
            Ring[j].LastX = Ring[j].NewX;   Ring[j].LastY = Ring[j].NewY;
        }
        Angle += Step;
    }
    free(Ring);
}

void glutWireCone(float base,float height,int slices,int stacks)
{
    int i, j;
    float Scale,Angle, Step, X, Y;

    typedef struct {
        float X, Y;
    }Ring_t;
    Ring_t* Ring;

    Ring = (Ring_t*)malloc(slices * sizeof(Ring_t));
    if (Ring == NULL) return;

    Angle = 0.0;  Step = PI2 / (float)slices;
    for (i = 0; i < slices; i++) {
        Ring[i].X = base * cos(Angle);
        Ring[i].Y = base * sin(Angle);
        Angle += Step;
    }
    glBegin(GL_LINES);
      for (i = 0; i < slices; i++) {
        glVertex3f(Ring[i].X, Ring[i].Y, 0.0);
        glVertex3f(0.0, 0.0, height);
      }
    glEnd();
    Step = height / (float)stacks;  Angle = 0.0;
    for (j = 0; j < stacks; j++) {
        Scale = 1.0 - (Angle / height);
        glBegin(GL_LINE_LOOP);
            for (i = 0; i < slices; i++) {
                X = Ring[i].X*Scale;
                Y = Ring[i].Y*Scale;
                glVertex3f(X,Y,Angle);
            }
        glEnd();
        Angle += Step;
    }
    free(Ring);
}

void glutWireSphere(float radius,int slices,int stacks)
{
    int i, j;
    float LastZ,Z,ZStep,LastScale,Scale, Angle, Step, X, Y;
    typedef struct {
        float X, Y;
    }Ring_t;
    Ring_t* Ring;

    Ring = (Ring_t*)malloc(slices * sizeof(Ring_t));
    if (Ring == NULL) return;

    Angle = 0.0;  Step = PI2 / (float)slices;
    for (i = 0; i < slices; i++) {
        Ring[i].X = radius * cos(Angle);
        Ring[i].Y = radius * sin(Angle);
        Angle += Step;
    }

    LastScale = 0.0;
    Angle = 0.0;  Step = 0.5*PI2 / (float)stacks;
    for (i = 0; i < stacks; i++) {
        Scale = sin(Angle);
        Z = radius * cos(Angle);
        glBegin(GL_LINE_LOOP);
            for (j = 0; j < slices; j++) {
                X = Ring[j].X * Scale;
                Y = Ring[j].Y * Scale;
                glVertex3f(X, Y, Z);
            }
        glEnd();
        if (i != 0) {
                for (j = 0; j < slices; j++) {
                    glBegin(GL_LINE_STRIP);
                    X = Ring[j].X * LastScale;
                    Y = Ring[j].Y * LastScale;
                    glVertex3f(X, Y, LastZ);
                    X = Ring[j].X * Scale;
                    Y = Ring[j].Y * Scale;
                    glVertex3f(X, Y, Z);
                    if (i == stacks - 1) {
                        glVertex3f(0.0, 0.0, -radius);
                    }
                    glEnd();
                }
        }
        LastZ = Z;
        Angle += Step;
        LastScale = Scale;
    }
    free(Ring);
}

void glutSwapBuffers(void)
{
#ifdef TFT_OGL_WINDOWED       
    wgfUpdateDisplay(1);
#else    
    gfUpdateDisplay(1);
#endif
}

static int16_t ResizeX,ResizeY;
static int ResizeW,ResizeH;
static int HasBeenInitialized = 0;

void glutInit(int *argc,char *argv[])
{
    if(!HasBeenInitialized){
        gfInit();
        HasBeenInitialized = 1;
    }
    ResizeX = 0;
    ResizeY = 0;
    ResizeW = 50;
    ResizeH = 50;
}

void glutInitDisplayMode(enum GlutDisplayModeType Mode)
{
    // Nothing here yet.  One day switch between double and single buffer
}

int glutCreateWindow(const char *Name)
{
    int WindowId;
#ifdef TFT_OGL_WINDOWED
    WindowId = wgfInit(ResizeX,ResizeY,ResizeW,ResizeH);
#else
    WindowId = 1;   
#endif
    if(WindowId==0){
        ActiveWindow = -1;
        return(0);  // Can't create window
    }
    ActiveWindow = WindowId-1;  // First window allocated is 1 so push back to zero

    MakeIdentity(Context[ActiveWindow].ModelViewXform);
    MakeIdentity(Context[ActiveWindow].PerspXform);
    Context[ActiveWindow].MatrixDirty = 1;
    Context[ActiveWindow].VertState.Color = 1;
    Context[ActiveWindow].VertState.Count = 0;
    gfSetClearColor(COLOR565(0x00,0x00,0x00));
    
    Context[ActiveWindow].Sx = 1.0;
    Context[ActiveWindow].Sy = -1.0;
    Context[ActiveWindow].Tx = 1.0;
    Context[ActiveWindow].Ty = 1.0;
    Context[ActiveWindow].ModelViewStackPtr = -1;
    Context[ActiveWindow].PerspStackPtr = -1;
    Context[ActiveWindow].MatrixMode = GL_MODELVIEW;
    Context[ActiveWindow].BeginMode = GL_INVALID_BEGIN;
    return(WindowId);
}

void glutDestroyWindow(int win)
{
    if(win==0 || win>MAX_WINDOWS) return;
#ifdef TFT_OGL_WINDOWED
    wgfFree(win);
#endif    
}

void glutSetWindow(int win)
{
#ifdef TFT_OGL_WINDOWED
    if(win==0 || win>MAX_WINDOWS){
        ActiveWindow = -1;
    }
    else{ 
        ActiveWindow = win-1;
        wgfSetActiveWindow(win);
    }
#endif
}

int glutGetWindow(void)
{
#ifdef TFT_OGL_WINDOWED
    if(ActiveWindow<0) return(0);
    return(ActiveWindow+1);
#else
    return(1);    
#endif
}

void glutInitWindowPosition(int X,int Y)
{
    ResizeX = X;  ResizeY = Y;
}

void glutInitWindowSize(int W,int H)
{
    ResizeW = W;
    ResizeH = H;
}

static void (*ReshapeFunc)(int w,int h) = NULL;
static void (*DisplayFunc)(void) = NULL;
static void (*IdleFunc)(void) = NULL;
static uint8_t ReDisplay = 1;

void glutReshapeFunc(void (*Func)(int w,int h))
{
    ReshapeFunc = Func;
}

void glutPostRedisplay(void)
{
    ReDisplay = 1;
}

void glutMainLoop(void)
{
    if(ReshapeFunc != NULL){
        (*ReshapeFunc)(ResizeW,ResizeH);
    }

    while(1){
        if(IdleFunc!=NULL){
            (*IdleFunc)();
        }
        if(ReDisplay && DisplayFunc != NULL){
            ReDisplay = 0;
            (*DisplayFunc)();
        }
    }
}

void glutDisplayFunc(void (*Func)(void))
{
    DisplayFunc = Func;
}

void glutIdleFunc(void (*Func)(void))
{
    IdleFunc = Func;
}

int glutGet(enum GlutGetType Which)
{
    switch(Which){
        case GLUT_SCREEN_WIDTH: return(PHYS_WIDTH); break;
        case GLUT_SCREEN_HEIGHT: return(PHYS_HEIGHT); break;
    }
    return(0);
}

void glFlush()
{

}

void glFinish()
{
}

void glPolygonMode(enum GLPolygonMode0Type Face,enum GLPolygonMode1Type Mode)
{
    // Only support GL_FRONT_AND_BACK,GL_LINE
}

void glColor3fv(float In[3]) {}
void glNormal3f(float X, float Y, float Z) {}
void glNormal3fv(float In[3]) {}
void glTexCoord2f(float S, float T) {}
void glTexCoord2fv(float In[2]) {}
