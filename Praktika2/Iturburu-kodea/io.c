#include "definitions.h"
#include "load_obj.h"
#include "display.h"
#include <GL/glut.h>
#include <stdio.h>
#include "multiMatrix.h"

extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;


extern char transf_helburua;
extern char transf_mota;
extern char transf_ardatza;
extern char transf_norabidea;

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");

    printf("Egilea: Borja Calvo (borja.calvo@ehu.es) \n");
    printf("Data: Irailak, 2014 \n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<M>\t\t Traslazioa aktibatu\n");
    printf("<B>\t\t Biraketa aktibatu\n");
    printf("<T>\t\t Tamaina aldaketa aktibatu\n");
    printf("<G>\t\t Aldaketak munduaren erreferentzi sisteman eragin (aldaketa globalak)\n");
    printf("<L>\t\t Aldaketak objektuaren (edo kameraren, edo argiaren) erreferentzi sisteman eragin (aldaketa lokalak)\n");
    printf("<O>\t\t Aldaketak hautaturik dagoen objektuari eragin\n");
    printf("<GORA>\t\t Mugitu +Y; Txikitu Y; Biratu +X\n");
    printf("<BEHERA>\t\t Mugitu -Y; Handitu Y; Biratu -X\n");
    printf("<ESKUINA>\t\t Mugitu +X; Txikitu X; Biratu +Y\n");
    printf("<EZKERRA>\t\t Mugitu -X; Handitu X; Biratu -Y\n");
    printf("<AVPAG>\t\t Mugitu +Z; Txikitu Z; Biratu +Z\n");
    printf("<REPAG>\t\t Mugitu -Z; Handitu Z; Biratu -Z\n");
    printf("<+>\t\t Ardatz guztietan handitu (Objektuak bakarrik)\n");
    printf("<->\t\t Ardatz guztietan txikitu (Objektuak bakarrik)\n");
    printf("<CTRL + (Z,z)>\t\t Aldaketak desegin\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");

    printf("\n\n");
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {

    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;

    switch (key) {
        case 'f':
        case 'F':
            /*Ask for file*/
            printf("%s", KG_MSSG_SELECT_FILE);
            scanf("%s", fname);
            /*Allocate memory for the structure and read the file*/
            auxiliar_object = (object3d *) malloc(sizeof (object3d));
            read = read_wavefront(fname, auxiliar_object);
            switch (read) {
                /*Errors in the reading*/
                case 1:
                    printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
                    break;
                case 2:
                    printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
                    break;
                case 3:
                    printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
                    break;
                    /*Read OK*/
                case 0:
                    /*Insert the new object in the list*/
                    auxiliar_object->next = _first_object;
                    _first_object = auxiliar_object;
                    _selected_object = _first_object;
                    printf("%s\n",KG_MSSG_FILEREAD);
                    break;
            }
            break;

        case 'm':
        case 'M':
            printf("Traslazioa aktibatuta\n");
            transf_mota = 'm';
            break;

        case 'b':
        case 'B':
            printf("Biraketa aktibatuta\n");
            transf_mota = 'b';
            break;

        case 't':
        case 'T':
            printf("Tamaina aldaketa aktibatuta\n");
            transf_mota = 't';
            break;

        case 'g':
        case 'G':
            printf("Aldaketak munduaren erreferentzi sisteman eragin (aldaketa globalak)\n");
            transf_helburua = 'g';
            break;

        case 'l':
        case 'L':
            printf("Aldaketak objektuaren (edo kameraren, edo argiaren) erreferentzi sisteman eragin (aldaketa lokalak)\n");
            transf_helburua = 'l';
            break;

        case 'o':
        case 'O':
            printf("Aldaketak hautaturik dagoen objektuari eragin\n");
            printf("(Hurrengo praktikan implementatuko da)\n");
            break;

        /*
        case 'z':
        case 'Z':
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
                printf("Aldaketak desegin\n");
                aldaketaDesegin();
            }
            else{
                printf("Z\n");
            }
            break;
        */
        case 26: /* <CTRL + Z*/
            printf("Aldaketak desegin\n");
            aldaketaDesegin();
            break;

        case 9: /* <TAB> */
            if(_selected_object != NULL) {
                _selected_object = _selected_object->next;
                /*The selection is circular, thus if we move out of the list we go back to the first element*/
                if (_selected_object == 0) _selected_object = _first_object;
            }
            break;

        case 127: /* <SUPR> */
            if(_selected_object != NULL){
                /*Erasing an object depends on whether it is the first one or not*/
                if (_selected_object == _first_object)
                {
                    /*To remove the first object we just set the first as the current's next*/
                    _first_object = _first_object->next;
                    /*Once updated the pointer to the first object it is save to free the memory*/
                    free(_selected_object);
                    /*Finally, set the selected to the new first one*/
                    _selected_object = _first_object;
                } else {
                    /*In this case we need to get the previous element to the one we want to erase*/
                    auxiliar_object = _first_object;
                    while (auxiliar_object->next != _selected_object)
                        auxiliar_object = auxiliar_object->next;
                    /*Now we bypass the element to erase*/
                    auxiliar_object->next = _selected_object->next;
                    /*free the memory*/
                    free(_selected_object);
                    /*and update the selection*/
                    _selected_object = auxiliar_object;
                }
            }
            break;

        case '-':
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                /*Increase the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            else
            {
                printf("Ardatz guztietan txikitu (Objektuak bakarrik)\n");
                guztiaTxikitu();
            }
            break;

        case '+':
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                /*Decrease the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            else
            {
                printf("Ardatz guztietan handitu (Objektuak bakarrik)\n");
                guztiaHanditu();
            }
            break;

        case '?':
            print_help();
            break;

        case 27: /* <ESC> */
            exit(0);
            break;

        default:
            transf_ardatza = 's';
            transf_norabidea = 's';
            /*In the default case we just print the code of the key. This is usefull to define new cases*/
            printf("%d %c\n", key, key);
            break;
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}//void keyboard

/**
 * @brief Teklatuko tekla bereziak kontrolatzeko
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboardSpecial(int key, int x, int y) {
    switch (key){
        case GLUT_KEY_LEFT:  /* <LEFT> */
            switch (transf_mota){
                case 'm':
                    transf_ardatza = 'X';
                    transf_norabidea = '-';
                    mugitu();
                    break;
                case 't':
                    transf_ardatza = 'X';
                    transf_norabidea = '-';
                    tAldatu();
                    break;
                case 'b':
                    transf_ardatza = 'Y';
                    transf_norabidea = '-';
                    biratu();
                    break;
            }
            break;

        case GLUT_KEY_UP: /* <UP> */
            switch (transf_mota){
                case 'm':
                    transf_ardatza = 'Y';
                    transf_norabidea = '+';
                    mugitu();
                    break;
                case 't':
                    transf_ardatza = 'Y';
                    transf_norabidea = '+';
                    tAldatu();
                    break;
                case 'b':
                    transf_ardatza = 'X';
                    transf_norabidea = '+';
                    biratu();
                    break;
            }
            break;

        case GLUT_KEY_RIGHT:  /* <RIGHT> */
            switch (transf_mota){
                case 'm':
                    transf_ardatza = 'X';
                    transf_norabidea = '+';
                    mugitu();
                    break;
                case 't':
                    transf_ardatza = 'X';
                    transf_norabidea = '+';
                    tAldatu();
                    break;
                case 'b':
                    transf_ardatza = 'Y';
                    transf_norabidea = '+';
                    biratu();
                    break;
            }
            break;

        case GLUT_KEY_DOWN:  /* <DOWN> */
            switch (transf_mota){
                case 'm':
                    transf_ardatza = 'Y';
                    transf_norabidea = '-';
                    mugitu();
                    break;
                case 't':
                    transf_ardatza = 'Y';
                    transf_norabidea = '-';
                    tAldatu();
                    break;
                case 'b':
                    transf_ardatza = 'X';
                    transf_norabidea = '-';
                    biratu();
                    break;
            }
            break;

        case GLUT_KEY_PAGE_DOWN: /* <AVPAG> */
            switch (transf_mota){
                case 'm':
                    transf_ardatza = 'Z';
                    transf_norabidea = '+';
                    mugitu();
                    break;
                case 't':
                    transf_ardatza = 'Z';
                    transf_norabidea = '-';
                    tAldatu();
                    break;
                case 'b':
                    transf_ardatza = 'Z';
                    transf_norabidea = '+';
                    biratu();
                    break;
            }
            break;

        case GLUT_KEY_PAGE_UP: /* <REPAG> */
            switch (transf_mota){
                case 'm':
                    transf_ardatza = 'Z';
                    transf_norabidea = '-';
                    mugitu();
                    break;
                case 't':
                    transf_ardatza = 'Z';
                    transf_norabidea = '+';
                    tAldatu();
                    break;
                case 'b':
                    transf_ardatza = 'Z';
                    transf_norabidea = '-';
                    biratu();
                    break;
            }
            break;
        default:
            transf_ardatza = 's';
            transf_norabidea = 's';
            break;
    }

    glutPostRedisplay();
}//void keyboardSpecial


