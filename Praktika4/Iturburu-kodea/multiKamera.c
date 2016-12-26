#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h> /* cos eta sin */
#include "multiMatrix.h"
#include "matrizeak.h"
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

extern kamera * kameraO;
extern kamera * kameraI;

int i;
//Translazio matrizeak
extern GLdouble  * trasX;
extern GLdouble  * trasY;
extern GLdouble  * trasZ;
extern GLdouble  * trasXn;
extern GLdouble  * trasYn;
extern GLdouble  * trasZn;

//Biraketa matrizeak
extern GLdouble  * biraX;
extern GLdouble  * biraY;
extern GLdouble  * biraZ;    
extern GLdouble  * biraXn;
extern GLdouble  * biraYn;    
extern GLdouble  * biraZn;    


/**
 * @brief Kamera baten aldaketa pilan aldaketa egin ondoren lortu den matrizea gordetzeko metodoa
 * @param matrix_aux aldeketa egin ondoren lortutako matrizea
 */
void pilanGehituK(GLdouble *matrix_aux){
    pila *pila_aux = (pila *) malloc(sizeof(pila));
    pila_aux->matrix= matrix_aux;
    if(kamera_mota=='o') {
        pila_aux->next = kameraO->aldaketaPila;
        kameraO->aldaketaPila = pila_aux;
        kameraO->num_aldaketak += 1;
    }
    else if(kamera_mota=='i') {
        pila_aux->next = kameraI->aldaketaPila;
        kameraI->aldaketaPila = pila_aux;
        kameraI->num_aldaketak += 1;
    }
}

/**
 * @brief Objetu baten aldaketak desegiteko metodoa
 */
void kamAldaketaDesegin(){
    if(kameraO->num_aldaketak>0){
        pila *first_matrix;
        first_matrix = kameraO->aldaketaPila->next;
        kameraO->aldaketaPila = 0;
        kameraO->aldaketaPila = first_matrix;
        kameraO->aldaketaPila->matrix = first_matrix->matrix;
        kameraO->num_aldaketak-=1;
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


void objektuKameraMugitu(){
    
    for(i = 0; i < 16; i++){
        printf("%f ",kameraO->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");

    GLdouble *matBerria;

    switch (kamera_tardatza) {
        case 'X':
            if (kamera_tnorabidea == '+') {
                printf("Kamera traslazioa: +X\n");
                if (transf_helburua == 'l') {
                    matBerria = mult(kameraO->aldaketaPila->matrix, trasX);
                }
                else if (transf_helburua == 'g'){
                    matBerria = mult(trasX, kameraO->aldaketaPila->matrix);
                }
            } else {
                printf("Kamera traslazioa: -X\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, trasXn);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasXn, kameraO->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Y':
            if (kamera_tnorabidea == '+') {
                printf("Kamera traslazioa: +Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, trasY);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasY, kameraO->aldaketaPila->matrix);
            } else {
                printf("Kamera traslazioa: -Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, trasYn);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasYn, kameraO->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Z':
            if (kamera_tnorabidea == '+') {
                printf("Kamera traslazioa: +Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, trasZ);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasZ, kameraO->aldaketaPila->matrix);
            } else {
                printf("Kamera traslazioa: -Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, trasZn);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasZn, kameraO->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;
    }
}//objektuKameraMugitu

void kamIbiltariaMugitu(){
    double angelua, ardatzaX, ardatzaZ;
    angelua = kameraI->angeluaXZ*3.14159265359f/8;

    GLdouble *matBerria;

    if(kamera_tnorabidea=='+'){
        printf("Kamera aurrera ibiltzen\n");
        ardatzaX = cos(angelua);
        ardatzaZ = -sin(angelua);
    }
    else{
        printf("Kamera atzera ibiltzen\n");
        ardatzaX = -cos(angelua);
        ardatzaZ = sin(angelua);
    }
    GLdouble  * trasY_I = malloc ( sizeof ( GLdouble )*16);
    trasY_I[0]=1; trasY_I[4]=0; trasY_I[8] =0; trasY_I[12]=ardatzaX*KG_KAM_ABIAD_TRASL;
    trasY_I[1]=0; trasY_I[5]=1; trasY_I[9] =0; trasY_I[13]=0;
    trasY_I[2]=0; trasY_I[6]=0; trasY_I[10]=1; trasY_I[14]=ardatzaZ*KG_KAM_ABIAD_TRASL;
    trasY_I[3]=0; trasY_I[7]=0; trasY_I[11]=0; trasY_I[15]=1;

    matBerria = mult(trasY_I, kameraI->aldaketaPila->matrix);
    int i;
    for(i = 0; i < 16; i++){
        printf("%f ",kameraI->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");

    pilanGehituK(matBerria);
}

void objektuKameraBiratu(){
    

    GLdouble *matBerria;

    switch (kamera_tardatza) {
        case 'X':
            if (kamera_tnorabidea == '+') {
                printf("Kamera biraketa: +X\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, biraX);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraX, kameraO->aldaketaPila->matrix);
            } else {
                printf("Kamera biraketa: -X\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, biraXn);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraXn, kameraO->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Y':
            if (kamera_tnorabidea == '+') {
                printf("Kamera biraketa: +Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, biraY);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraY, kameraO->aldaketaPila->matrix);
            } else {
                printf("Kamera biraketa: -Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, biraYn);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraYn, kameraO->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;

        case 'Z':
            if (kamera_tnorabidea == '+') {
                printf("Kamera biraketa: +Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, biraZ);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraZ, kameraO->aldaketaPila->matrix);
            } else {
                printf("Kamera biraketa: -Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(kameraO->aldaketaPila->matrix, biraZn);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraZn, kameraO->aldaketaPila->matrix);
            }
            pilanGehituK(matBerria);
            break;
    }
   
    for(i = 0; i < 16; i++){
        printf("%f ",kameraO->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");
}//objektuKameraBiratu

void kamIbiltariaBiratu(){
    GLdouble *matBerria;

    switch (kamera_tardatza) {
        case 'Y':
            if (kamera_tnorabidea == '+') {
                printf("Kamera eskuinera biratu\n");
                kameraI->angeluaXZ += KG_KAM_ABIAD_BIRAK*8;

                GLdouble  * biraY_I_R = malloc ( sizeof ( GLdouble )*16);
                biraY_I_R [0]=cos(KG_KAM_ABIAD_BIRAK); biraY_I_R [4]=0;  biraY_I_R [8]=-sin(KG_KAM_ABIAD_BIRAK); biraY_I_R [12]=0;
                biraY_I_R [1]=0;                       biraY_I_R [5]=1;  biraY_I_R [9]=0;                    biraY_I_R [13]=0;
                biraY_I_R [2]=sin(KG_KAM_ABIAD_BIRAK); biraY_I_R [6]=0;  biraY_I_R [10]=cos(KG_KAM_ABIAD_BIRAK); biraY_I_R [14]=0;
                biraY_I_R [3]=0;                       biraY_I_R [7]=0;  biraY_I_R [11]=0;                   biraY_I_R [15]=1;

                matBerria = mult(kameraI->aldaketaPila->matrix,biraY_I_R);

            } else {
                printf("Kamera ezkerrera biratu\n");
                kameraI->angeluaXZ -= KG_KAM_ABIAD_BIRAK*8;

                GLdouble  * biraY_I_L = malloc ( sizeof ( GLdouble )*16);
                biraY_I_L [0]=cos(KG_KAM_ABIAD_BIRAK);  biraY_I_L [4]=0;  biraY_I_L [8] =sin(KG_KAM_ABIAD_BIRAK); biraY_I_L [12]=0;
                biraY_I_L [1]=0;                        biraY_I_L [5]=1;  biraY_I_L [9]=0;                        biraY_I_L [13]=0;
                biraY_I_L [2]=-sin(KG_KAM_ABIAD_BIRAK); biraY_I_L [6]=0;  biraY_I_L [10]=cos(KG_KAM_ABIAD_BIRAK); biraY_I_L [14]=0;
                biraY_I_L [3]=0;                        biraY_I_L [7]=0;  biraY_I_L [11]=0;                       biraY_I_L [15]=1;

                matBerria = mult(kameraI->aldaketaPila->matrix,biraY_I_L);
            }
            pilanGehituK(matBerria);
            break;

        case 'Z':
            if (kamera_tnorabidea == '+') {
                printf("Kamera goruntz begira\n");

                GLdouble  * biraX_I_U = malloc ( sizeof ( GLdouble )*16);
                biraX_I_U [0]=1;  biraX_I_U [4]=0;                   biraX_I_U [8] =0;                    biraX_I_U [12]=0;
                biraX_I_U [1]=0;  biraX_I_U [5]=cos(KG_KAM_ABIAD_BIRAK); biraX_I_U [9] =-sin(KG_KAM_ABIAD_BIRAK); biraX_I_U [13]=0;
                biraX_I_U [2]=0;  biraX_I_U [6]=sin(KG_KAM_ABIAD_BIRAK); biraX_I_U [10]=cos(KG_KAM_ABIAD_BIRAK);  biraX_I_U [14]=0;
                biraX_I_U [3]=0;  biraX_I_U [7]=0;                   biraX_I_U [11]=0;                    biraX_I_U [15]=1;

                if(kameraI->angeluaY <= 8){
                    kameraI->angeluaY += 1;
                    matBerria = mult(kameraI->aldaketaPila->matrix,biraX_I_U);
                    pilanGehituK(matBerria);
                }

            } else {
                printf("Kamera beheruntz begira\n");

                GLdouble  * biraX_I_D = malloc ( sizeof ( GLdouble )*16);
                biraX_I_D [0]=1;  biraX_I_D [4]=0;                   biraX_I_D [8] =0;                        biraX_I_D [12]=0;
                biraX_I_D [1]=0;  biraX_I_D [5]=cos(KG_KAM_ABIAD_BIRAK); biraX_I_D [9] =sin(KG_KAM_ABIAD_BIRAK); biraX_I_D [13]=0;
                biraX_I_D [2]=0;  biraX_I_D [6]=-sin(KG_KAM_ABIAD_BIRAK); biraX_I_D [10]=cos(KG_KAM_ABIAD_BIRAK);      biraX_I_D [14]=0;
                biraX_I_D [3]=0;  biraX_I_D [7]=0;                   biraX_I_D [11]=0;                        biraX_I_D [15]=1;

                if(kameraI->angeluaY >= -8){
                    kameraI->angeluaY -= 1;
                    matBerria = mult(kameraI->aldaketaPila->matrix,biraX_I_D);
                    pilanGehituK(matBerria);
                }
            }
            break;
    }
    
    for(i = 0; i < 16; i++){
        printf("%f ",kameraI->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");
}

