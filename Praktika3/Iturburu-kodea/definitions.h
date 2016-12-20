#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/gl.h>

/** DEFINITIONS **/


#define KG_WINDOW_TITLE                     "KbG Praktika"
#define KG_WINDOW_WIDTH                     860
#define KG_WINDOW_HEIGHT                    600
#define KG_WINDOW_X                         50
#define KG_WINDOW_Y                         50

#define KG_MSSG_SELECT_FILE                 "Idatz ezazu fitxategiaren path-a: "
#define KG_MSSG_FILENOTFOUND                "Fitxategi hori ez da existitzen!!"
#define KG_MSSG_INVALIDFILE                 "Arazoren bat egon da fitxategiarekin ..."
#define KG_MSSG_EMPTYFILE                   "Fitxategia hutsik dago"
#define KG_MSSG_FILEREAD                    "Fitxategiaren irakurketa buruta"

#define KG_STEP_MOVE                        5.0f
#define KG_STEP_ROTATE                      10.0f
#define KG_STEP_ZOOM                        0.75
#define KG_STEP_CAMERA_ANGLE                5.0f

#define KG_ORTHO_X_MIN_INIT                -5
#define KG_ORTHO_X_MAX_INIT                 5
#define KG_ORTHO_Y_MIN_INIT                -5
#define KG_ORTHO_Y_MAX_INIT                 5
#define KG_ORTHO_Z_MIN_INIT                -100
#define KG_ORTHO_Z_MAX_INIT                 10000

#define KG_COL_BACK_R                       0.70f
#define KG_COL_BACK_G                       0.70f
#define KG_COL_BACK_B                       1.00f
#define KG_COL_BACK_A                       1.00f

#define KG_COL_SELECTED_R                   1.00f
#define KG_COL_SELECTED_G                   1.00f
#define KG_COL_SELECTED_B                   1.00f

#define KG_COL_NONSELECTED_R                1.00f
#define KG_COL_NONSELECTED_G                0.75f
#define KG_COL_NONSELECTED_B                0.00f

#define KG_COL_X_AXIS_R                     1.0f
#define KG_COL_X_AXIS_G                     0.0f
#define KG_COL_X_AXIS_B                     0.0f

#define KG_COL_Y_AXIS_R                     0.0f
#define KG_COL_Y_AXIS_G                     1.0f
#define KG_COL_Y_AXIS_B                     0.0f

#define KG_COL_Z_AXIS_R                     0.0f
#define KG_COL_Z_AXIS_G                     0.0f
#define KG_COL_Z_AXIS_B                     1.0f

#define KG_COL_P_AXIS_R                     0.0f
#define KG_COL_P_AXIS_G                     0.0f
#define KG_COL_P_AXIS_B                     0.0f

#define KG_MAX_DOUBLE                       100025

#define KG_ABIAD_TAMAN                      0.1f
#define KG_ABIAD_BIRAK                      3.14159265359f/8
#define KG_ABIAD_TRASL                      0.1f

#define KG_KAM_ABIAD_BIRAK                  3.14159265359f/128
#define KG_KAM_ABIAD_TRASL                  0.1f;

/** STRUCTURES **/

/****************************
 * Structure to store the   *
 * coordinates of 3D points *
 ****************************/
typedef struct {
    GLdouble x, y, z;
} point3;

/*****************************
 * Structure to store the    *
 * coordinates of 3D vectors *
 *****************************/
typedef struct {
    GLdouble x, y, z;
} vector3;

/****************************
 * Structure to store the   *
 * colors in RGB mode       *
 ****************************/
typedef struct {
    GLfloat r, g, b;
} color3;

/****************************
 * Structure to store       *
 * objects' vertices         *
 ****************************/
typedef struct {
    point3 coord;                       /* coordinates,x, y, z */
    GLint num_faces;                    /* number of faces that share this vertex */
} vertex;

/****************************
 * Structure to store       *
 * objects' faces or        *
 * polygons                 *
 ****************************/
typedef struct {
    GLint num_vertices;                 /* number of vertices in the face */
    GLint *vertex_table;                /* table with the index of each vertex */
} face;


struct aldaketaPila{
    GLdouble * matrix;
    struct aldaketaPila *next;
};
typedef struct aldaketaPila pila;

/****************************
 * Structure to store a     *
 * pile of 3D objects       *
 ****************************/
struct object3d{
    GLint num_vertices;                 /* number of vertices in the object*/
    vertex *vertex_table;               /* table of vertices */
    GLint num_faces;                    /* number of faces in the object */
    face *face_table;                   /* table of faces */
    point3 min;                         /* coordinates' lower bounds */
    point3 max;                         /* coordinates' bigger bounds */
    struct object3d *next;              /* next element in the pile of objects */
    GLdouble * matrix;
    pila * aldaketaPila;
    GLint num_aldaketak;
};

typedef struct object3d object3d;

/*****************************
 * Structure to store a      *
 * camera position and angle *
 *****************************/
struct kamera{
    GLdouble * eye;
    GLdouble * center;
    GLdouble * up;
    GLfloat n;
    GLfloat f;
    GLfloat angeluaXZ; /*Kamera ibiltariarako, eskuin-ezkerrerako angelua gordetzea beharrezkoa da*/
    GLfloat angeluaY; /*Kamera ibiltariarako, gora-beherako angelua gordetzea beharrezkoa da*/
    pila * aldaketaPila;
    GLint num_aldaketak;
};

typedef struct kamera kamera;


#endif // DEFINITIONS_H
