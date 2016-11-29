/*********************************************
 * File with the functions to make all the   *
 * transformations to the objects 			 *
 * ----------------------------------------- *
 * Authors: 								 *
 *  Robin Espinosa   						 *
 *	Julen Ferrero 							 *
 * Date:  November 2016                      *
 *********************************************/


#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h> /** cos eta sin **/

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

/** GLOBAL VARIABLES **/

object3d * trans_obj =0;                    /*Transformazioa jasango duen objektua*/

char transf_helburua = '\0';				//Transformazio lokala edo globala 
char transf_mota = '\0';					//Biraketa, traslazio edo tamaina aldaketa
char transf_ardatza = '\0';					//X,Y,Z
char transf_norabidea = '\0';				//+,-

/**
 * @brief Matrizeak biderkatzeko metodoa
 * @param m1 Biderkadurako ezkerreko matrizea
 * @param m2 Biderkadurako eskuineko matrizea
 * @return GLdouble motako matrizea, m1Xm2-ren emaitza
 */
GLdouble *mult(GLdouble *m1, GLdouble *m2) {
    GLdouble *result = malloc(sizeof(GLdouble) * 4 * 4);
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
/**
 * @brief Objektu baten aldaketa pilan aldaketa egin ondoren lortu den matrizea gordetzeko metodoa
 * @param matrix_aux aldeketa egin ondoren lortutako matrizea
 */
void pilanGehitu(GLdouble *matrix_aux){
    pila *pila_aux = (pila *) malloc(sizeof(pila));
    pila_aux->matrix= matrix_aux;
    pila_aux->next = _selected_object->aldaketaPila;
    _selected_object->aldaketaPila = pila_aux;
    _selected_object->num_aldaketak+=1;
}

/**
 * @brief Objetu baten aldaketak desegiteko metodoa
 */
void aldaketaDesegin(){
    if(_selected_object->num_aldaketak>0){
        pila *first_matrix;
        first_matrix = _selected_object->aldaketaPila->next;
        _selected_object->aldaketaPila = 0;
        _selected_object->aldaketaPila = first_matrix;
        _selected_object->matrix = first_matrix->matrix;
        _selected_object->num_aldaketak-=1;
        printf("Aldaketak desegin dira\n");}
    else{
        printf("Ezin dira aldaketa gehiagorik desegin\n");}
}//aldaketaDesegin

/**
 * @brief Objektua mugitzeko metodoa
 */
void traslazioa(){
    GLdouble  * trasX = malloc ( sizeof ( GLdouble )*16);
    trasX [0]=1; trasX [4]=0; trasX [8] =0; trasX [12]=KG_ABIAD_TRASL;
    trasX [1]=0; trasX [5]=1; trasX [9] =0; trasX [13]=0;
    trasX [2]=0; trasX [6]=0; trasX [10]=1; trasX [14]=0;
    trasX [3]=0; trasX [7]=0; trasX [11]=0; trasX [15]=1;

    GLdouble  * trasY = malloc ( sizeof ( GLdouble )*16);
    trasY [0]=1; trasY [4]=0; trasY [8] =0; trasY [12]=0;
    trasY [1]=0; trasY [5]=1; trasY [9] =0; trasY [13]=KG_ABIAD_TRASL;
    trasY [2]=0; trasY [6]=0; trasY [10]=1; trasY [14]=0;
    trasY [3]=0; trasY [7]=0; trasY [11]=0; trasY [15]=1;

    GLdouble  * trasZ = malloc ( sizeof ( GLdouble )*16);
    trasZ [0]=1; trasZ [4]=0; trasZ [8] =0; trasZ [12]=0;
    trasZ [1]=0; trasZ [5]=1; trasZ [9] =0; trasZ [13]=0;
    trasZ [2]=0; trasZ [6]=0; trasZ [10]=1; trasZ [14]=KG_ABIAD_TRASL;
    trasZ [3]=0; trasZ [7]=0; trasZ [11]=0; trasZ [15]=1;

    GLdouble  * trasXn = malloc ( sizeof ( GLdouble )*16);
    trasXn [0]=1; trasXn [4]=0; trasXn [8] =0; trasXn [12]=KG_ABIAD_TRASL*(-1);
    trasXn [1]=0; trasXn [5]=1; trasXn [9] =0; trasXn [13]=0;
    trasXn [2]=0; trasXn [6]=0; trasXn [10]=1; trasXn [14]=0;
    trasXn [3]=0; trasXn [7]=0; trasXn [11]=0; trasXn [15]=1;

    GLdouble  * trasYn = malloc ( sizeof ( GLdouble )*16);
    trasYn [0]=1; trasYn [4]=0; trasYn [8] =0; trasYn [12]=0;
    trasYn [1]=0; trasYn [5]=1; trasYn [9] =0; trasYn [13]=KG_ABIAD_TRASL*(-1);
    trasYn [2]=0; trasYn [6]=0; trasYn [10]=1; trasYn [14]=0;
    trasYn [3]=0; trasYn [7]=0; trasYn [11]=0; trasYn [15]=1;

    GLdouble  * trasZn = malloc ( sizeof ( GLdouble )*16);
    trasZn [0]=1; trasZn [4]=0; trasZn [8] =0; trasZn [12]=0;
    trasZn [1]=0; trasZn [5]=1; trasZn [9] =0; trasZn [13]=0;
    trasZn [2]=0; trasZn [6]=0; trasZn [10]=1; trasZn [14]=KG_ABIAD_TRASL*(-1);
    trasZn [3]=0; trasZn [7]=0; trasZn [11]=0; trasZn [15]=1;

    switch (transf_ardatza){
        case 'X':
            if(transf_norabidea=='+'){
                printf("Traslazioa: +X\n");
                _selected_object->matrix=mult(_selected_object->matrix,trasX);
            }
            else{
                printf("Traslazioa: -X\n");
                _selected_object->matrix=mult(_selected_object->matrix,trasXn);
            }
            pilanGehitu(_selected_object->matrix);
            break;

        case 'Y':
            if(transf_norabidea=='+'){
                printf("Traslazioa: +Y\n");
                _selected_object->matrix=mult(_selected_object->matrix,trasY);
            }
            else{
                printf("Traslazioa: -Y\n");
                _selected_object->matrix=mult(_selected_object->matrix,trasYn);
            }
            pilanGehitu(_selected_object->matrix);
            break;

        case 'Z':
            if(transf_norabidea=='+'){
                printf("Traslazioa: +Z\n");
                _selected_object->matrix=mult(_selected_object->matrix,trasZ);
            }
            else{
                printf("Traslazioa: -Z\n");
                _selected_object->matrix=mult(_selected_object->matrix,trasZn);
            }
            pilanGehitu(_selected_object->matrix);
            break;
    }
}//void traslazioa()

/**
 * @brief Objektuaren tamaina aldatzeko metodoa
 */
void tamainaAldaketa(){
    GLdouble  * tamaX = malloc ( sizeof ( GLdouble )*16);
    tamaX [0]=1+KG_ABIAD_TAMAN;  tamaX [4]=0; tamaX [8] =0; tamaX [12]=0;
    tamaX [1]=0;               tamaX [5]=1; tamaX [9] =0; tamaX [13]=0;
    tamaX [2]=0;               tamaX [6]=0; tamaX [10]=1; tamaX [14]=0;
    tamaX [3]=0;               tamaX [7]=0; tamaX [11]=0; tamaX [15]=1;

    GLdouble  * tamaY = malloc ( sizeof ( GLdouble )*16);
    tamaY [0]=1; tamaY [4]=0;               tamaY [8] =0; tamaY [12]=0;
    tamaY [1]=0; tamaY [5]=1+KG_ABIAD_TAMAN;  tamaY [9] =0; tamaY [13]=0;
    tamaY [2]=0; tamaY [6]=0;               tamaY [10]=1; tamaY [14]=0;
    tamaY [3]=0; tamaY [7]=0;               tamaY [11]=0; tamaY [15]=1;

    GLdouble  * tamaZ = malloc ( sizeof ( GLdouble )*16);
    tamaZ [0]=1; tamaZ [4]=0; tamaZ [8] =0;               tamaZ [12]=0;
    tamaZ [1]=0; tamaZ [5]=1; tamaZ [9] =0;               tamaZ [13]=0;
    tamaZ [2]=0; tamaZ [6]=0; tamaZ [10]=1+KG_ABIAD_TAMAN;  tamaZ [14]=0;
    tamaZ [3]=0; tamaZ [7]=0; tamaZ [11]=0;               tamaZ [15]=1;

    GLdouble  * tamaXn = malloc ( sizeof ( GLdouble )*16);
    tamaXn [0]=1-KG_ABIAD_TAMAN;  tamaXn [4]=0; tamaXn [8] =0; tamaXn [12]=0;
    tamaXn [1]=0;                    tamaXn [5]=1; tamaXn [9] =0; tamaXn [13]=0;
    tamaXn [2]=0;                    tamaXn [6]=0; tamaXn [10]=1; tamaXn [14]=0;
    tamaXn [3]=0;                    tamaXn [7]=0; tamaXn [11]=0; tamaXn [15]=1;

    GLdouble  * tamaYn = malloc ( sizeof ( GLdouble )*16);
    tamaYn [0]=1; tamaYn [4]=0;                    tamaYn [8] =0; tamaYn [12]=0;
    tamaYn [1]=0; tamaYn [5]=1-KG_ABIAD_TAMAN;  tamaYn [9] =0; tamaYn [13]=0;
    tamaYn [2]=0; tamaYn [6]=0;                    tamaYn [10]=1; tamaYn [14]=0;
    tamaYn [3]=0; tamaYn [7]=0;                    tamaYn [11]=0; tamaYn [15]=1;

    GLdouble  * tamaZn = malloc ( sizeof ( GLdouble )*16);
    tamaZn [0]=1; tamaZn [4]=0; tamaZn [8] =0;                    tamaZn [12]=0;
    tamaZn [1]=0; tamaZn [5]=1; tamaZn [9] =0;                    tamaZn [13]=0;
    tamaZn [2]=0; tamaZn [6]=0; tamaZn [10]=1-KG_ABIAD_TAMAN;  tamaZn [14]=0;
    tamaZn [3]=0; tamaZn [7]=0; tamaZn [11]=0;                    tamaZn [15]=1;

    switch (transf_ardatza){
        case 'X':
            if(transf_norabidea=='+'){
                printf("Tamaina aldaketa: +X\n");
                _selected_object->matrix=mult(_selected_object->matrix,tamaX);
            }
            else{
                printf("Tamaina aldaketa: -X\n");
                _selected_object->matrix=mult(_selected_object->matrix,tamaXn);
            }
            pilanGehitu(_selected_object->matrix);
            break;

        case 'Y':
            if(transf_norabidea=='+'){
                printf("Tamaina aldaketa: +Y\n");
                _selected_object->matrix=mult(_selected_object->matrix,tamaY);
            }
            else{
                printf("Tamaina aldaketa: -Y\n");
                _selected_object->matrix=mult(_selected_object->matrix,tamaYn);
            }
            pilanGehitu(_selected_object->matrix);
            break;

        case 'Z':
            if(transf_norabidea=='+'){
                printf("Tamaina aldaketa: +Z\n");
                _selected_object->matrix=mult(_selected_object->matrix,tamaZ);
            }
            else{
                printf("Tamaina aldaketa: -Z\n");
                _selected_object->matrix=mult(_selected_object->matrix,tamaZn);
            }
            pilanGehitu(_selected_object->matrix);
            break;
    }
}//void tamainaAldaketa()

/**
 * @brief Objektua biratzeko metodoa
 */
void biraketa(){
    GLdouble  * biraX = malloc ( sizeof ( GLdouble )*16);
    biraX [0]=1;  biraX [4]=0;                   biraX [8] =0;                        biraX [12]=0;
    biraX [1]=0;  biraX [5]=cos(KG_ABIAD_BIRAK); biraX [9] =sin(KG_ABIAD_BIRAK)*(-1); biraX [13]=0;
    biraX [2]=0;  biraX [6]=sin(KG_ABIAD_BIRAK); biraX [10]=cos(KG_ABIAD_BIRAK);      biraX [14]=0;
    biraX [3]=0;  biraX [7]=0;                   biraX [11]=0;                        biraX [15]=1;

    GLdouble  * biraY = malloc ( sizeof ( GLdouble )*16);
    biraY [0]=cos(KG_ABIAD_BIRAK);      biraY [4]=0;  biraY [8] =sin(KG_ABIAD_BIRAK); biraY [12]=0;
    biraY [1]=0;                        biraY [5]=1;  biraY [9]=0;                    biraY [13]=0;
    biraY [2]=sin(KG_ABIAD_BIRAK)*(-1); biraY [6]=0;  biraY [10]=cos(KG_ABIAD_BIRAK); biraY [14]=0;
    biraY [3]=0;                        biraY [7]=0;  biraY [11]=0;                   biraY [15]=1;

    GLdouble  * biraZ = malloc ( sizeof ( GLdouble )*16);
    biraZ [0]=cos(KG_ABIAD_BIRAK); biraZ [4]=sin(KG_ABIAD_BIRAK)*(-1); biraZ [8] =0;  biraZ [12]=0;
    biraZ [1]=sin(KG_ABIAD_BIRAK); biraZ [5]=cos(KG_ABIAD_BIRAK);      biraZ [9] =0;  biraZ [13]=0;
    biraZ [2]=0;                   biraZ [6]=0;                        biraZ [10]=1;  biraZ [14]=0;
    biraZ [3]=0;                   biraZ [7]=0;                        biraZ [11]=0;  biraZ [15]=1;

    GLdouble  * biraXn = malloc ( sizeof ( GLdouble )*16);
    biraXn [0]=1;  biraXn [4]=0;                   biraXn [8] =0;                        biraXn [12]=0;
    biraXn [1]=0;  biraXn [5]=cos(KG_ABIAD_BIRAK); biraXn [9] =sin(KG_ABIAD_BIRAK); biraXn [13]=0;
    biraXn [2]=0;  biraXn [6]=sin(KG_ABIAD_BIRAK)*(-1); biraXn [10]=cos(KG_ABIAD_BIRAK);      biraXn [14]=0;
    biraXn [3]=0;  biraXn [7]=0;                   biraXn [11]=0;                        biraXn [15]=1;

    GLdouble  * biraYn = malloc ( sizeof ( GLdouble )*16);
    biraYn [0]=cos(KG_ABIAD_BIRAK);      biraYn [4]=0;  biraYn [8] =sin(KG_ABIAD_BIRAK)*(-1); biraYn [12]=0;
    biraYn [1]=0;                        biraYn [5]=1;  biraYn [9]=0;                    biraYn [13]=0;
    biraYn [2]=sin(KG_ABIAD_BIRAK); biraYn [6]=0;  biraYn [10]=cos(KG_ABIAD_BIRAK); biraYn [14]=0;
    biraYn [3]=0;                        biraYn [7]=0;  biraYn [11]=0;                   biraYn [15]=1;

    GLdouble  * biraZn = malloc ( sizeof ( GLdouble )*16);
    biraZn [0]=cos(KG_ABIAD_BIRAK); biraZn [4]=sin(KG_ABIAD_BIRAK); biraZn [8] =0;  biraZn [12]=0;
    biraZn [1]=sin(KG_ABIAD_BIRAK)*(-1); biraZn [5]=cos(KG_ABIAD_BIRAK);      biraZn [9] =0;  biraZn [13]=0;
    biraZn [2]=0;                   biraZn [6]=0;                        biraZn [10]=1;  biraZn [14]=0;
    biraZn [3]=0;                   biraZn [7]=0;                        biraZn [11]=0;  biraZn [15]=1;
    switch (transf_ardatza){
        case 'X':
            if(transf_norabidea=='+'){
                printf("Biraketa: +X\n");
                _selected_object->matrix=mult(_selected_object->matrix,biraX);
            }
            else{
                printf("Biraketa: -X\n");
                _selected_object->matrix=mult(_selected_object->matrix,biraXn);
            }
            pilanGehitu(_selected_object->matrix);
            break;

        case 'Y':
            if(transf_norabidea=='+'){
                printf("Biraketa: +Y\n");
                _selected_object->matrix=mult(_selected_object->matrix,biraY);
            }
            else{
                printf("Biraketa: -Y\n");
                _selected_object->matrix=mult(_selected_object->matrix,biraYn);
            }
            pilanGehitu(_selected_object->matrix);
            break;

        case 'Z':
            if(transf_norabidea=='+'){
                printf("Biraketa: +Z\n");
                _selected_object->matrix=mult(_selected_object->matrix,biraZ);
            }
            else{
                printf("Biraketa: -Z\n");
                _selected_object->matrix=mult(_selected_object->matrix,biraZn);
            }
            pilanGehitu(_selected_object->matrix);
            break;
    }
}//void biraketa()

/**
 * @brief Objektuen biraketa lokala (aukeratutako objektua) edo globala (objektu guztiak) egiteko erabiltzen den metodoa
 */
void biratu(){
    if(transf_helburua=='l'){
        biraketa();
    }
    else if(transf_helburua=='g'){
        trans_obj= _first_object;
        while (trans_obj != 0){
            biraketa();
            _selected_object = _selected_object->next;
            trans_obj = trans_obj->next;
            if(_selected_object==0) _selected_object= _first_object;
        }
    }
}//void biratu()

/**
 * @brief Objektuen traslazio lokala (aukeratutako objektua) edo globala (objektu guztiak) egiteko erabiltzen den metodoa
 */
void mugitu(){
    if(transf_helburua=='l'){
        traslazioa();
    }
    else if(transf_helburua=='g'){
        trans_obj = _first_object;
        while (trans_obj != 0){
            traslazioa();
            _selected_object = _selected_object->next;
            trans_obj = trans_obj->next;
            if(_selected_object==0) _selected_object= _first_object;
        }
    }
}//void mugitu()

/**
 * @brief Objektuen tamaina aldaketa lokala (aukeratutako objektua) edo globala (objektu guztiak) egiteko erabiltzen den metodoa
 */
void tAldatu(){
    if(transf_helburua=='l'){
        tamainaAldaketa();
    }
    else if(transf_helburua=='g'){
        trans_obj = _first_object;
        while (trans_obj != 0){
            tamainaAldaketa();
            _selected_object = _selected_object->next;
            trans_obj = trans_obj->next;
            if(_selected_object==0) _selected_object= _first_object;
        }
    }
}//void tAldatu()


/**
 * @brief Objektuen tamaina aldaketa globala (objektu guztiak) egiteko erabiltzen den metodoa, objektu guztiak handitzen ditu.
 */
void guztiaHanditu(){
    GLdouble  * tama = malloc ( sizeof ( GLdouble )*16);
    tama [0]=1+KG_ABIAD_TAMAN;  tama [4]=0;                tama [8] =0;                tama [12]=0;
    tama [1]=0;                 tama [5]=1+KG_ABIAD_TAMAN; tama [9] =0;                tama [13]=0;
    tama [2]=0;                 tama [6]=0;                tama [10]=1+KG_ABIAD_TAMAN; tama [14]=0;
    tama [3]=0;                 tama [7]=0;                tama [11]=0;                tama [15]=1;

    printf("Tamaina aldaketa: handitze orokorra\n");
    _selected_object->matrix=mult(_selected_object->matrix,tama);
    pilanGehitu(_selected_object->matrix);
}

/**
 * @brief Objektuen tamaina aldaketa globala (objektu guztiak) egiteko erabiltzen den metodoa, objektu guztiak txikitzen ditu.
 */
void guztiaTxikitu(){
    GLdouble  * tamaN = malloc ( sizeof ( GLdouble )*16);
    tamaN [0]=1-KG_ABIAD_TAMAN;  tamaN [4]=0;                tamaN [8] =0;                tamaN [12]=0;
    tamaN [1]=0;                 tamaN [5]=1-KG_ABIAD_TAMAN; tamaN [9] =0;                tamaN [13]=0;
    tamaN [2]=0;                 tamaN [6]=0;                tamaN [10]=1-KG_ABIAD_TAMAN; tamaN [14]=0;
    tamaN [3]=0;                 tamaN [7]=0;                tamaN [11]=0;                tamaN [15]=1;

    printf("Tamaina aldaketa: txikitze orokorra\n");
    _selected_object->matrix=mult(_selected_object->matrix,tamaN);
    pilanGehitu(_selected_object->matrix);
}
