#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

extern char transf_helburua;
extern char transf_mota;
extern char transf_ardatza;
extern char transf_norabidea;

/**
 * @brief Matrizeak biderkatzeko metodoa
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
 * @brief Objektua mugitzeko metodoa
 * @param transf_ardatza Transformazioaren ardatza
 * @param transf_norabidea transformazioaren norabidea
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
            break;
    }
}//void traslazioa()

/**
 * @brief Objektuaren tamaina aldatzeko metodoa
 * @param transf_ardatza Transformazioaren ardatza
 * @param transf_norabidea transformazioaren norabidea
 */
void tamainaAldaketa(){
    GLdouble  * tamaX = malloc ( sizeof ( GLdouble )*16);
    tamaX [0]=KG_ABIAD_TAMAN;  tamaX [4]=0; tamaX [8] =0; tamaX [12]=0;
    tamaX [1]=0;               tamaX [5]=1; tamaX [9] =0; tamaX [13]=0;
    tamaX [2]=0;               tamaX [6]=0; tamaX [10]=1; tamaX [14]=0;
    tamaX [3]=0;               tamaX [7]=0; tamaX [11]=0; tamaX [15]=1;

    GLdouble  * tamaY = malloc ( sizeof ( GLdouble )*16);
    tamaY [0]=1; tamaY [4]=0;               tamaY [8] =0; tamaY [12]=0;
    tamaY [1]=0; tamaY [5]=KG_ABIAD_TAMAN;  tamaY [9] =0; tamaY [13]=0;
    tamaY [2]=0; tamaY [6]=0;               tamaY [10]=1; tamaY [14]=0;
    tamaY [3]=0; tamaY [7]=0;               tamaY [11]=0; tamaY [15]=1;

    GLdouble  * tamaZ = malloc ( sizeof ( GLdouble )*16);
    tamaZ [0]=1; tamaZ [4]=0; tamaZ [8] =0;               tamaZ [12]=0;
    tamaZ [1]=0; tamaZ [5]=1; tamaZ [9] =0;               tamaZ [13]=0;
    tamaZ [2]=0; tamaZ [6]=0; tamaZ [10]=KG_ABIAD_TAMAN;  tamaZ [14]=0;
    tamaZ [3]=0; tamaZ [7]=0; tamaZ [11]=0;               tamaZ [15]=1;

    GLdouble  * tamaXn = malloc ( sizeof ( GLdouble )*16);
    tamaXn [0]=KG_ABIAD_TAMAN*(-1);  tamaXn [4]=0; tamaXn [8] =0; tamaXn [12]=0;
    tamaXn [1]=0;               tamaXn [5]=1; tamaXn [9] =0; tamaXn [13]=0;
    tamaXn [2]=0;               tamaXn [6]=0; tamaXn [10]=1; tamaXn [14]=0;
    tamaXn [3]=0;               tamaXn [7]=0; tamaXn [11]=0; tamaXn [15]=1;

    GLdouble  * tamaYn = malloc ( sizeof ( GLdouble )*16);
    tamaYn [0]=1; tamaYn [4]=0;               tamaYn [8] =0; tamaYn [12]=0;
    tamaYn [1]=0; tamaYn [5]=KG_ABIAD_TAMAN*(-1);  tamaYn [9] =0; tamaYn [13]=0;
    tamaYn [2]=0; tamaYn [6]=0;               tamaYn [10]=1; tamaYn [14]=0;
    tamaYn [3]=0; tamaYn [7]=0;               tamaYn [11]=0; tamaYn [15]=1;

    GLdouble  * tamaZn = malloc ( sizeof ( GLdouble )*16);
    tamaZn [0]=1; tamaZn [4]=0; tamaZn [8] =0;               tamaZn [12]=0;
    tamaZn [1]=0; tamaZn [5]=1; tamaZn [9] =0;               tamaZn [13]=0;
    tamaZn [2]=0; tamaZn [6]=0; tamaZn [10]=KG_ABIAD_TAMAN*(-1);  tamaZn [14]=0;
    tamaZn [3]=0; tamaZn [7]=0; tamaZn [11]=0;               tamaZn [15]=1;

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
            break;
    }
}//void tamainaAldaketa()

/**
 * @brief Objektua biratzeko metodoa
 * @param transf_ardatza Transformazioaren ardatza
 * @param transf_norabidea transformazioaren norabidea
 */
void biraketa(){
    switch (transf_ardatza){
        case 'X':
            if(transf_norabidea=='+'){
                printf("Biraketa: +X\n");
            }
            else{
                printf("Biraketa: -X\n");
            }
            break;

        case 'Y':
            if(transf_norabidea=='+'){
                printf("Biraketa: +Y\n");
            }
            else{
                printf("Biraketa: -Y\n");
            }
            break;

        case 'Z':
            if(transf_norabidea=='+'){
                printf("Biraketa: +Z\n");
            }
            else{
                printf("Biraketa: -Z\n");
            }
            break;
    }
}//void biraketa()

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(KG_MAX_DOUBLE,0,0);
    glVertex3d(-1*KG_MAX_DOUBLE,0,0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,KG_MAX_DOUBLE,0);
    glVertex3d(0,-1*KG_MAX_DOUBLE,0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,0,KG_MAX_DOUBLE);
    glVertex3d(0,0,-1*KG_MAX_DOUBLE);
    glEnd();
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    /*VIEWPORT nagusia*/
    glViewport(0, 0, width, height);

    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}

/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;
    object3d *trans_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*When the window is wider than our original projection plane we extend the plane in the X axis*/
    if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
        /* New width */
        GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;
        /* Midpoint in the X axis */
        GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
        /*Definition of the projection*/
        glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
    } else {/* In the opposite situation we extend the Y axis */
        /* New height */
        GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
        /* Midpoint in the Y axis */
        GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
        /*Definition of the projection*/
        glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
    }

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*First, we draw the axes*/
    draw_axes();

    switch(transf_mota){
        case 'b':
            if(transf_helburua=='l'){
                biraketa();
            }
            else{
                while (trans_obj != 0){
                    biraketa();
                    trans_obj = trans_obj->next;
                }
            }
            break;
        case 'm':
            if(transf_helburua=='l'){
                traslazioa();
            }
            else{
                while (trans_obj != 0){
                    traslazioa();
                    trans_obj = trans_obj->next;
                }
            }
            break;
        case 't':
            if(transf_helburua=='l'){
                tamainaAldaketa();
            }
            else{
                while (trans_obj != 0){
                    tamainaAldaketa();
                    trans_obj = trans_obj->next;
                }
            }
            break;
        default:
            transf_ardatza = 's';
            transf_norabidea = 's';
            break;
    }

    /*Now each of the objects in the list*/
    while (aux_obj != 0) {

        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }

        /* Draw the object; for each face create a new polygon with the corresponding vertices */
        glLoadIdentity();

        glMultMatrixd(aux_obj->matrix);

        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);
            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                v_index = aux_obj->face_table[f].vertex_table[v];
                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                        aux_obj->vertex_table[v_index].coord.y,
                        aux_obj->vertex_table[v_index].coord.z);

            }
            glEnd();
        }
        aux_obj = aux_obj->next;
    }
    /*Do the actual drawing*/
    glFlush();
}
