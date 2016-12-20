#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h> /* cos eta sin */
#include "multiMatrix.h"

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

/** GLOBAL VARIABLES **/

extern object3d * trans_obj;                    /*Transformazioa jasango duen objektua*/

char kamera_mota = 'o';							//Orto,objektu-kamera,ibiltaria
char kamera_tmota= '\0';						//Biratu edo mugitu
char kamera_tardatza = '\0';					//X,Y,Z
char kamera_tnorabidea = '\0';					//+,-
extern char transf_helburua;

extern kamera * kamera1;

GLdouble *mult_vec(GLdouble *m, GLdouble *v){

    GLdouble *result = (GLdouble*)malloc(sizeof(GLdouble)*4);

    result[0] = m[0]*v[0] + m[4]*v[1] + m[8] *v[2] + m[12]*v[3];
    result[1] = m[1]*v[0] + m[5]*v[1] + m[9] *v[2] + m[13]*v[3];
    result[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3];
    result[3] = m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3];

    return result;
}

/**
 * @brief Kamera baten aldaketa pilan aldaketa egin ondoren lortu den matrizea gordetzeko metodoa
 * @param matrix_aux aldeketa egin ondoren lortutako matrizea
 */
void pilanGehituK(GLdouble *matrix_aux){
    pila *pila_aux = (pila *) malloc(sizeof(pila));
    pila_aux->matrix= matrix_aux;
    pila_aux->next = kamera1->aldaketaPila;
    kamera1->aldaketaPila = pila_aux;
    kamera1->num_aldaketak+=1;
}

/**
 * @brief Objetu baten aldaketak desegiteko metodoa
 */
void kamAldaketaDesegin(){
    if(kamera1->num_aldaketak>0){
        pila *first_matrix;
        first_matrix = kamera1->aldaketaPila->next;
        kamera1->aldaketaPila = 0;
        kamera1->aldaketaPila = first_matrix;
        kamera1->aldaketaPila->matrix = first_matrix->matrix;
        kamera1->num_aldaketak-=1;
        printf("Kameraren aldaketak desegin dira\n");}
    else{
        printf("Ezin dira aldaketa gehiagorik desegin\n");}
}//aldaketaDesegin

void kamera_mota_aldatu(){
	if(kamera_mota == 'o') kamera_mota='k';
	else if(kamera_mota == 'k') kamera_mota='i';
	else if(kamera_mota == 'i') kamera_mota='o';

	printf("Kamera mota: %c (o: ortografikoa, k: objektu-kamera, i: ibiltaria)\n",kamera_mota);
}

void kam_mugitu(){
    GLdouble  * trasX = malloc ( sizeof ( GLdouble )*16);
    trasX[0]=1; trasX[4]=0; trasX[8] =0; trasX[12]=KG_KAM_ABIAD_TRASL;
    trasX[1]=0; trasX[5]=1; trasX[9] =0; trasX[13]=0;
    trasX[2]=0; trasX[6]=0; trasX[10]=1; trasX[14]=0;
    trasX[3]=0; trasX[7]=0; trasX[11]=0; trasX[15]=1;

    GLdouble  * trasY = malloc ( sizeof ( GLdouble )*16);
    trasY[0]=1; trasY[4]=0; trasY[8] =0; trasY[12]=0;
    trasY[1]=0; trasY[5]=1; trasY[9] =0; trasY[13]=KG_KAM_ABIAD_TRASL;
    trasY[2]=0; trasY[6]=0; trasY[10]=1; trasY[14]=0;
    trasY[3]=0; trasY[7]=0; trasY[11]=0; trasY[15]=1;

    GLdouble  * trasZ = malloc ( sizeof ( GLdouble )*16);
    trasZ[0]=1; trasZ[4]=0; trasZ[8] =0; trasZ[12]=0;
    trasZ[1]=0; trasZ[5]=1; trasZ[9] =0; trasZ[13]=0;
    trasZ[2]=0; trasZ[6]=0; trasZ[10]=1; trasZ[14]=KG_KAM_ABIAD_TRASL;
    trasZ[3]=0; trasZ[7]=0; trasZ[11]=0; trasZ[15]=1;

    GLdouble  * trasXn = malloc ( sizeof ( GLdouble )*16);
    trasXn[0]=1; trasXn[4]=0; trasXn[8] =0; trasXn[12]=-KG_KAM_ABIAD_TRASL;
    trasXn[1]=0; trasXn[5]=1; trasXn[9] =0; trasXn[13]=0;
    trasXn[2]=0; trasXn[6]=0; trasXn[10]=1; trasXn[14]=0;
    trasXn[3]=0; trasXn[7]=0; trasXn[11]=0; trasXn[15]=1;

    GLdouble  * trasYn = malloc ( sizeof ( GLdouble )*16);
    trasYn[0]=1; trasYn[4]=0; trasYn[8] =0; trasYn[12]=0;
    trasYn[1]=0; trasYn[5]=1; trasYn[9] =0; trasYn[13]=-KG_KAM_ABIAD_TRASL;
    trasYn[2]=0; trasYn[6]=0; trasYn[10]=1; trasYn[14]=0;
    trasYn[3]=0; trasYn[7]=0; trasYn[11]=0; trasYn[15]=1;

    GLdouble  * trasZn = malloc ( sizeof ( GLdouble )*16);
    trasZn[0]=1; trasZn[4]=0; trasZn[8] =0; trasZn[12]=0;
    trasZn[1]=0; trasZn[5]=1; trasZn[9] =0; trasZn[13]=0;
    trasZn[2]=0; trasZn[6]=0; trasZn[10]=1; trasZn[14]=-KG_KAM_ABIAD_TRASL;
    trasZn[3]=0; trasZn[7]=0; trasZn[11]=0; trasZn[15]=1;

    for(int i = 0; i < 16; i++){
        printf("%f ",kamera1->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");

    GLdouble *matBerria;

    switch (kamera_tardatza){
        case 'X':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +X\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,trasX);
                else if(transf_helburua=='g')
                    matBerria = mult(trasX, kamera1->aldaketaPila->matrix);
            }
            else{
                printf("Kamera traslazioa: -X\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,trasXn);
                else if(transf_helburua=='g')
                    matBerria = mult(trasXn,kamera1->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Y':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +Y\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,trasY);
                else if(transf_helburua=='g')
                    matBerria = mult(trasY,kamera1->aldaketaPila->matrix);
            }
            else{
                printf("Kamera traslazioa: -Y\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,trasYn);
                else if(transf_helburua=='g')
                    matBerria = mult(trasYn,kamera1->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Z':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +Z\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,trasZ);
                else if(transf_helburua=='g')
                    matBerria = mult(trasZ,kamera1->aldaketaPila->matrix);
            }
            else{
                printf("Kamera traslazioa: -Z\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,trasZn);
                else if(transf_helburua=='g')
                    matBerria = mult(trasZn,kamera1->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;
    }
}//kam_mugitu

void kam_biratu(){
    GLdouble  * biraX = malloc ( sizeof ( GLdouble )*16);
    biraX [0]=1;  biraX [4]=0;                   biraX [8] =0;                    biraX [12]=0;
    biraX [1]=0;  biraX [5]=cos(KG_KAM_ABIAD_BIRAK); biraX [9] =-sin(KG_KAM_ABIAD_BIRAK); biraX [13]=0;
    biraX [2]=0;  biraX [6]=sin(KG_KAM_ABIAD_BIRAK); biraX [10]=cos(KG_KAM_ABIAD_BIRAK);  biraX [14]=0;
    biraX [3]=0;  biraX [7]=0;                   biraX [11]=0;                    biraX [15]=1;

    GLdouble  * biraY = malloc ( sizeof ( GLdouble )*16);
    biraY [0]=cos(KG_KAM_ABIAD_BIRAK);  biraY [4]=0;  biraY [8] =sin(KG_KAM_ABIAD_BIRAK); biraY [12]=0;
    biraY [1]=0;                    biraY [5]=1;  biraY [9]=0;                    biraY [13]=0;
    biraY [2]=-sin(KG_KAM_ABIAD_BIRAK); biraY [6]=0;  biraY [10]=cos(KG_KAM_ABIAD_BIRAK); biraY [14]=0;
    biraY [3]=0;                    biraY [7]=0;  biraY [11]=0;                   biraY [15]=1;

    GLdouble  * biraZ = malloc ( sizeof ( GLdouble )*16);
    biraZ [0]=cos(KG_KAM_ABIAD_BIRAK); biraZ [4]=-sin(KG_KAM_ABIAD_BIRAK); biraZ [8] =0;  biraZ [12]=0;
    biraZ [1]=sin(KG_KAM_ABIAD_BIRAK); biraZ [5]=cos(KG_KAM_ABIAD_BIRAK);  biraZ [9] =0;  biraZ [13]=0;
    biraZ [2]=0;                   biraZ [6]=0;                    biraZ [10]=1;  biraZ [14]=0;
    biraZ [3]=0;                   biraZ [7]=0;                        biraZ [11]=0;  biraZ [15]=1;

    GLdouble  * biraXn = malloc ( sizeof ( GLdouble )*16);
    biraXn [0]=1;  biraXn [4]=0;                   biraXn [8] =0;                        biraXn [12]=0;
    biraXn [1]=0;  biraXn [5]=cos(KG_KAM_ABIAD_BIRAK); biraXn [9] =sin(KG_KAM_ABIAD_BIRAK); biraXn [13]=0;
    biraXn [2]=0;  biraXn [6]=-sin(KG_KAM_ABIAD_BIRAK); biraXn [10]=cos(KG_KAM_ABIAD_BIRAK);      biraXn [14]=0;
    biraXn [3]=0;  biraXn [7]=0;                   biraXn [11]=0;                        biraXn [15]=1;

    GLdouble  * biraYn = malloc ( sizeof ( GLdouble )*16);
    biraYn [0]=cos(KG_KAM_ABIAD_BIRAK);      biraYn [4]=0;  biraYn [8] =-sin(KG_KAM_ABIAD_BIRAK); biraYn [12]=0;
    biraYn [1]=0;                        biraYn [5]=1;  biraYn [9]=0;                    biraYn [13]=0;
    biraYn [2]=sin(KG_KAM_ABIAD_BIRAK); biraYn [6]=0;  biraYn [10]=cos(KG_KAM_ABIAD_BIRAK); biraYn [14]=0;
    biraYn [3]=0;                        biraYn [7]=0;  biraYn [11]=0;                   biraYn [15]=1;

    GLdouble  * biraZn = malloc ( sizeof ( GLdouble )*16);
    biraZn [0]=cos(KG_KAM_ABIAD_BIRAK); biraZn [4]=sin(KG_KAM_ABIAD_BIRAK); biraZn [8] =0;  biraZn [12]=0;
    biraZn [1]=-sin(KG_KAM_ABIAD_BIRAK); biraZn [5]=cos(KG_KAM_ABIAD_BIRAK);      biraZn [9] =0;  biraZn [13]=0;
    biraZn [2]=0;                   biraZn [6]=0;                        biraZn [10]=1;  biraZn [14]=0;
    biraZn [3]=0;                   biraZn [7]=0;                        biraZn [11]=0;  biraZn [15]=1;

    for(int i = 0; i < 16; i++){
        printf("%f ",kamera1->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");

    GLdouble *matBerria;

    switch (kamera_tardatza){
        case 'X':
            if(kamera_tnorabidea=='+'){
                printf("Kamera biraketa: +X\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,biraX);
                else if(transf_helburua=='g')
                    matBerria = mult(biraX, kamera1->aldaketaPila->matrix);
            }
            else{
                printf("Kamera biraketa: -X\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,biraXn);
                else if(transf_helburua=='g')
                    matBerria = mult(biraXn,kamera1->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Y':
            if(kamera_tnorabidea=='+'){
                printf("Kamera biraketa: +Y\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,biraY);
                else if(transf_helburua=='g')
                    matBerria = mult(biraY,kamera1->aldaketaPila->matrix);
            }
            else{
                printf("Kamera biraketa: -Y\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,biraYn);
                else if(transf_helburua=='g')
                    matBerria = mult(biraYn,kamera1->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Z':
            if(kamera_tnorabidea=='+'){
                printf("Kamera biraketa: +Z\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,biraZ);
                else if(transf_helburua=='g')
                    matBerria = mult(biraZ,kamera1->aldaketaPila->matrix);
            }
            else{
                printf("Kamera biraketa: -Z\n");
                if(transf_helburua=='l')
                    matBerria = mult(kamera1->aldaketaPila->matrix,biraZn);
                else if(transf_helburua=='g')
                    matBerria = mult(biraZn,kamera1->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;
    }
}//kam_biratu
