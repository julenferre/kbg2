#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h> /* cos eta sin */


//Traslazio matrizeak
GLdouble  * trasX;
GLdouble  * trasY;
GLdouble  * trasZ;
GLdouble  * trasXn;
GLdouble  * trasYn;
GLdouble  * trasZn;

//Biraketa matrizeak
GLdouble  * biraX;
GLdouble  * biraY;
GLdouble  * biraZ;    
GLdouble  * biraXn;
GLdouble  * biraYn;    
GLdouble  * biraZn;    

GLdouble *result; 
GLdouble *resultv; 

    
    
    
    

void init_matrizeak(){

trasX = malloc ( sizeof ( GLdouble )*16);
trasY = malloc ( sizeof ( GLdouble )*16);
trasZ = malloc ( sizeof ( GLdouble )*16);
trasXn = malloc ( sizeof ( GLdouble )*16);
trasYn = malloc ( sizeof ( GLdouble )*16);
trasZn = malloc ( sizeof ( GLdouble )*16);
biraX = malloc ( sizeof ( GLdouble )*16);
biraY = malloc ( sizeof ( GLdouble )*16);
biraZ = malloc ( sizeof ( GLdouble )*16);    
biraXn = malloc ( sizeof ( GLdouble )*16);
biraYn = malloc ( sizeof ( GLdouble )*16);    
biraZn = malloc ( sizeof ( GLdouble )*16);


	trasX[0]=1; trasX[4]=0; trasX[8] =0; trasX[12]=KG_KAM_ABIAD_TRASL;
    trasX[1]=0; trasX[5]=1; trasX[9] =0; trasX[13]=0;
    trasX[2]=0; trasX[6]=0; trasX[10]=1; trasX[14]=0;
    trasX[3]=0; trasX[7]=0; trasX[11]=0; trasX[15]=1;

    
    trasY[0]=1; trasY[4]=0; trasY[8] =0; trasY[12]=0;
    trasY[1]=0; trasY[5]=1; trasY[9] =0; trasY[13]=KG_KAM_ABIAD_TRASL;
    trasY[2]=0; trasY[6]=0; trasY[10]=1; trasY[14]=0;
    trasY[3]=0; trasY[7]=0; trasY[11]=0; trasY[15]=1;

    
    trasZ[0]=1; trasZ[4]=0; trasZ[8] =0; trasZ[12]=0;
    trasZ[1]=0; trasZ[5]=1; trasZ[9] =0; trasZ[13]=0;
    trasZ[2]=0; trasZ[6]=0; trasZ[10]=1; trasZ[14]=KG_KAM_ABIAD_TRASL;
    trasZ[3]=0; trasZ[7]=0; trasZ[11]=0; trasZ[15]=1;

    
    trasXn[0]=1; trasXn[4]=0; trasXn[8] =0; trasXn[12]=-KG_KAM_ABIAD_TRASL;
    trasXn[1]=0; trasXn[5]=1; trasXn[9] =0; trasXn[13]=0;
    trasXn[2]=0; trasXn[6]=0; trasXn[10]=1; trasXn[14]=0;
    trasXn[3]=0; trasXn[7]=0; trasXn[11]=0; trasXn[15]=1;

    
    trasYn[0]=1; trasYn[4]=0; trasYn[8] =0; trasYn[12]=0;
    trasYn[1]=0; trasYn[5]=1; trasYn[9] =0; trasYn[13]=-KG_KAM_ABIAD_TRASL;
    trasYn[2]=0; trasYn[6]=0; trasYn[10]=1; trasYn[14]=0;
    trasYn[3]=0; trasYn[7]=0; trasYn[11]=0; trasYn[15]=1;

    
    trasZn[0]=1; trasZn[4]=0; trasZn[8] =0; trasZn[12]=0;
    trasZn[1]=0; trasZn[5]=1; trasZn[9] =0; trasZn[13]=0;
    trasZn[2]=0; trasZn[6]=0; trasZn[10]=1; trasZn[14]=-KG_KAM_ABIAD_TRASL;
    trasZn[3]=0; trasZn[7]=0; trasZn[11]=0; trasZn[15]=1;

    biraX [0]=1;  biraX [4]=0;                   biraX [8] =0;                    biraX [12]=0;
    biraX [1]=0;  biraX [5]=cos(KG_KAM_ABIAD_BIRAK); biraX [9] =-sin(KG_KAM_ABIAD_BIRAK); biraX [13]=0;
    biraX [2]=0;  biraX [6]=sin(KG_KAM_ABIAD_BIRAK); biraX [10]=cos(KG_KAM_ABIAD_BIRAK);  biraX [14]=0;
    biraX [3]=0;  biraX [7]=0;                   biraX [11]=0;                    biraX [15]=1;

    biraY [0]=cos(KG_KAM_ABIAD_BIRAK);  biraY [4]=0;  biraY [8] =sin(KG_KAM_ABIAD_BIRAK); biraY [12]=0;
    biraY [1]=0;                    biraY [5]=1;  biraY [9]=0;                    biraY [13]=0;
    biraY [2]=-sin(KG_KAM_ABIAD_BIRAK); biraY [6]=0;  biraY [10]=cos(KG_KAM_ABIAD_BIRAK); biraY [14]=0;
    biraY [3]=0;                    biraY [7]=0;  biraY [11]=0;                   biraY [15]=1;

    biraZ [0]=cos(KG_KAM_ABIAD_BIRAK); biraZ [4]=-sin(KG_KAM_ABIAD_BIRAK); biraZ [8] =0;  biraZ [12]=0;
    biraZ [1]=sin(KG_KAM_ABIAD_BIRAK); biraZ [5]=cos(KG_KAM_ABIAD_BIRAK);  biraZ [9] =0;  biraZ [13]=0;
    biraZ [2]=0;                   biraZ [6]=0;                    biraZ [10]=1;  biraZ [14]=0;
    biraZ [3]=0;                   biraZ [7]=0;                        biraZ [11]=0;  biraZ [15]=1;

    biraXn [0]=1;  biraXn [4]=0;                   biraXn [8] =0;                        biraXn [12]=0;
    biraXn [1]=0;  biraXn [5]=cos(KG_KAM_ABIAD_BIRAK); biraXn [9] =sin(KG_KAM_ABIAD_BIRAK); biraXn [13]=0;
    biraXn [2]=0;  biraXn [6]=-sin(KG_KAM_ABIAD_BIRAK); biraXn [10]=cos(KG_KAM_ABIAD_BIRAK);      biraXn [14]=0;
    biraXn [3]=0;  biraXn [7]=0;                   biraXn [11]=0;                        biraXn [15]=1;

    biraYn [0]=cos(KG_KAM_ABIAD_BIRAK);      biraYn [4]=0;  biraYn [8] =-sin(KG_KAM_ABIAD_BIRAK); biraYn [12]=0;
    biraYn [1]=0;                        biraYn [5]=1;  biraYn [9]=0;                    biraYn [13]=0;
    biraYn [2]=sin(KG_KAM_ABIAD_BIRAK); biraYn [6]=0;  biraYn [10]=cos(KG_KAM_ABIAD_BIRAK); biraYn [14]=0;
    biraYn [3]=0;                        biraYn [7]=0;  biraYn [11]=0;                   biraYn [15]=1;

    biraZn [0]=cos(KG_KAM_ABIAD_BIRAK); biraZn [4]=sin(KG_KAM_ABIAD_BIRAK); biraZn [8] =0;  biraZn [12]=0;
    biraZn [1]=-sin(KG_KAM_ABIAD_BIRAK); biraZn [5]=cos(KG_KAM_ABIAD_BIRAK);      biraZn [9] =0;  biraZn [13]=0;
    biraZn [2]=0;                   biraZn [6]=0;                        biraZn [10]=1;  biraZn [14]=0;
    biraZn [3]=0;                   biraZn [7]=0;                        biraZn [11]=0;  biraZn [15]=1;
}

GLdouble *mult_vec(GLdouble *m, GLdouble *v){

    resultv = (GLdouble*)malloc(sizeof(GLdouble)*4);

    result[0] = m[0]*v[0] + m[4]*v[1] + m[8] *v[2] + m[12]*v[3];
    result[1] = m[1]*v[0] + m[5]*v[1] + m[9] *v[2] + m[13]*v[3];
    result[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3];
    result[3] = m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3];

    return resultv;
}

/**
 * @brief Matrizeak biderkatzeko metodoa
 * @param m1 Biderkadurako ezkerreko matrizea
 * @param m2 Biderkadurako eskuineko matrizea
 * @return GLdouble motako matrizea, m1Xm2-ren emaitza
 */
GLdouble *mult(GLdouble *m1, GLdouble *m2) {
    result = malloc(sizeof(GLdouble) * 4 * 4);
    // @formatter:off
    result[0 + 4* 0] = m1[0 + 4* 0] * m2[0 + 4* 0] + m1[0 + 4* 1] * m2[1 + 4* 0] + m1[0 + 4* 2] * m2[2 + 4* 0] + m1[0 + 4* 3] * m2[3 + 4* 0];
    result[1 + 4* 0] = m1[1 + 4* 0] * m2[0 + 4* 0] + m1[1 + 4* 1] * m2[1 + 4* 0] + m1[1 + 4* 2] * m2[2 + 4* 0] + m1[1 + 4* 3] * m2[3 + 4* 0];
    result[2 + 4* 0] = m1[2 + 4* 0] * m2[0 + 4* 0] + m1[2 + 4* 1] * m2[1 + 4* 0] + m1[2 + 4* 2] * m2[2 + 4* 0] + m1[2 + 4* 3] * m2[3 + 4* 0];
    result[3 + 4* 0] = m1[3 + 4* 0] * m2[0 + 4* 0] + m1[3 + 4* 1] * m2[1 + 4* 0] + m1[3 + 4* 2] * m2[2 + 4* 0] + m1[3 + 4* 3] * m2[3 + 4* 0];

    result[0 + 4* 1] = m1[0 + 4* 0] * m2[0 + 4* 1] + m1[0 + 4* 1] * m2[1 + 4* 1] + m1[0 + 4* 2] * m2[2 + 4* 1] + m1[0 + 4* 3] * m2[3 + 4* 1];
    result[1 + 4* 1] = m1[1 + 4* 0] * m2[0 + 4* 1] + m1[1 + 4* 1] * m2[1 + 4* 1] + m1[1 + 4* 2] * m2[2 + 4* 1] + m1[1 + 4* 3] * m2[3 + 4* 1];
    result[2 + 4* 1] = m1[2 + 4* 0] * m2[0 + 4* 1] + m1[2 + 4* 1] * m2[1 + 4* 1] + m1[2 + 4* 2] * m2[2 + 4* 1] + m1[2 + 4* 3] * m2[3 + 4* 1];
    result[3 + 4* 1] = m1[3 + 4* 0] * m2[0 + 4* 1] + m1[3 + 4* 1] * m2[1 + 4* 1] + m1[3 + 4* 2] * m2[2 + 4* 1] + m1[3 + 4* 3] * m2[3 + 4* 1];

    result[0 + 4* 2] = m1[0 + 4* 0] * m2[0 + 4* 2] + m1[0 + 4* 1] * m2[1 + 4* 2] + m1[0 + 4* 2] * m2[2 + 4* 2] + m1[0 + 4* 3] * m2[3 + 4* 2];
    result[1 + 4* 2] = m1[1 + 4* 0] * m2[0 + 4* 2] + m1[1 + 4* 1] * m2[1 + 4* 2] + m1[1 + 4* 2] * m2[2 + 4* 2] + m1[1 + 4* 3] * m2[3 + 4* 2];
    result[2 + 4* 2] = m1[2 + 4* 0] * m2[0 + 4* 2] + m1[2 + 4* 1] * m2[1 + 4* 2] + m1[2 + 4* 2] * m2[2 + 4* 2] + m1[2 + 4* 3] * m2[3 + 4* 2];
    result[3 + 4* 2] = m1[3 + 4* 0] * m2[0 + 4* 2] + m1[3 + 4* 1] * m2[1 + 4* 2] + m1[3 + 4* 2] * m2[2 + 4* 2] + m1[3 + 4* 3] * m2[3 + 4* 2];

    result[0 + 4* 3] = m1[0 + 4* 0] * m2[0 + 4* 3] + m1[0 + 4* 1] * m2[1 + 4* 3] + m1[0 + 4* 2] * m2[2 + 4* 3] + m1[0 + 4* 3] * m2[3 + 4* 3];
    result[1 + 4* 3] = m1[1 + 4* 0] * m2[0 + 4* 3] + m1[1 + 4* 1] * m2[1 + 4* 3] + m1[1 + 4* 2] * m2[2 + 4* 3] + m1[1 + 4* 3] * m2[3 + 4* 3];
    result[2 + 4* 3] = m1[2 + 4* 0] * m2[0 + 4* 3] + m1[2 + 4* 1] * m2[1 + 4* 3] + m1[2 + 4* 2] * m2[2 + 4* 3] + m1[2 + 4* 3] * m2[3 + 4* 3];
    result[3 + 4* 3] = m1[3 + 4* 0] * m2[0 + 4* 3] + m1[3 + 4* 1] * m2[1 + 4* 3] + m1[3 + 4* 2] * m2[2 + 4* 3] + m1[3 + 4* 3] * m2[3 + 4* 3];
    // @formatter:on
    return result;
}

void free_matrizeak(){

free(trasX);
free(trasY);
free(trasZ);
free(trasXn);
free(trasYn);
free(trasZn);
free(biraX);
free(biraY);
free(biraZ);
free(biraXn);
free(biraYn);
free(biraZn);
free(result);
free(resultv);  

}