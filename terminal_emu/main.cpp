#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION"
#include "_Data/stb_image.h"
#include "_Data/wallpaper.h"
#include "_Data/serial.h"

int width, height;
GLuint wallpaper_;

void screen();
void RenderString(float x, float y,const char *str,float r, float g, float b);
void standf();
void glIni();
void resetPrj();
void resz(int,int);
void setOrtho();

int main(int argc, char **argv){
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(300,64);
  glutCreateWindow("PHOENIX - IGNITE TERMINAL");
 glIni();
  glutDisplayFunc(screen);
  glutReshapeFunc(resz);
  glutKeyboardFunc(FIRE_INPUT_KEYBOARD);
  glutIdleFunc(standf);
 glutMainLoop(); 
 return 0;
}

void standf(){
 usleep(33);
 glutPostRedisplay();
}

void setOrtho(){ // INICIAR EL MODO EN 2D DE OPENGL
    glMatrixMode(GL_PROJECTION); // MODO DE PROYECCION DE OPENGL
    glPushMatrix(); // INICIAR MATRIZ (PARA LOS POLIGONOS Y LOS OBJETOS QUE SE DIBUJAN EN GENERAL)
    glLoadIdentity(); // CARGAR TODOS LOS OBJETOS UNA VEZ MAS 
    gluOrtho2D(0, width, 0, height); // DEFINIR EL TIPO DE PROYECCION A ORTHOGONAL PARA 2D SIN PERSPECTIVA
    glScalef(1, -1, 1); // DEFINIR EL TAMAÑO DE LA PROYECCION
    glTranslatef(0, -height, 0); // DEFINIR EL LUGAR PARA LA PROYECCION
    glMatrixMode(GL_MODELVIEW); // VOLVER AL MODO DE MEMORIA EN OPENGL
}

void resz(int xs, int ys){ // FUNCION DE REESCALAMIENTO
    const float ar = (float) xs / (float) ys; // TAMAÑO DEL PIXEL ( ASPECT RATIO )
    width = xs; // DEFINIR EL TAMAÑO NUEVO DE LA PANTALLA
    height = ys; // DEFINIR EL TAMAÑO NUEVO DE LA PANTALLA
    glViewport(0, 0, xs, ys); // GENERAR UN VIEWPORT DE DIBUJO
    glMatrixMode(GL_PROJECTION); // CAMBIAR EL MODO A PROYECCION
    glLoadIdentity(); // CARGAR LOS OBJETOS
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0); // ARREGLAR LA RESOLUCION
    glMatrixMode(GL_MODELVIEW); // CAMBIAR EL MODO OTRA VEZ A MEMORIA
    glLoadIdentity() ; // MOSTRAR LOS OBJETOS
}

void resetPrj(){ // REFRESCAR LA MATRIZ PARA DIBUJAR 
    glMatrixMode(GL_PROJECTION); // ENTRAR AL MODO PROYECCION
    glPopMatrix(); // EMPUJAR AL STACK UNA MATRIZ
    glMatrixMode(GL_MODELVIEW); // VOLVER AL MODO NORMAL
}

void glIni(){
 glEnable(GL_TEXTURE_2D);
 glEnable(GL_BLEND);
 glClearColor(1.0f,1.0f,1.0f,0.0f);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 //_term->fire_confg();
 wallpaper_ = Bon_load_bmp("_Data/wallpaper/wallpaper.bmp",640,480);
}

void RenderString(float x, float y,const char *str,float r, float g, float b){  
 const char *c; // VARIABLE AUXILIAR CON EL CONTENIDO
 glDisable(GL_TEXTURE_2D); // PERMITIR EL USO DE TEXTURAS EN OPENGL
 glColor3f(r, g, b); 
 glRasterPos2f(x, y); // MOVER EL TEXTO A LA LOCALIZACION QUE BUSCAMOS 
 for (c=str; *c != '\0'; c++) { // REPETIR PARA CADA LETRA DEL TEXTO
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c); // MOSTRAR UN CARACTER EN PANTALLA
 }
}

void screen(){
 glClear(GL_COLOR_BUFFER_BIT);
 setOrtho();
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, wallpaper_);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex2f(0, 0);
        glTexCoord2d(1,0);
        glVertex2f(width, 0);
        glTexCoord2d(1,1);
        glVertex2f(width, height);
        glTexCoord2d(0,1);
        glVertex2f(0, height);
    glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glPushMatrix();
   std::string info_data = "IGNITE TERMINAL - 0.11 - By: Pentabonyx";
   RenderString(1,15, info_data.c_str(), 1.0f,1.0f,1.0f);
   RenderString(1,30, "--------------------------------------------", 1.0f,1.0f,1.0f);
   for(int i = 1; i < 28; i++){
    std::string v;
    if(i < 10){v = "0";} else {v = "";}
    std::string output_data = "" + v + std::to_string(i) + " | " + _OUT[i-1];
    RenderString(1,30+(15*i), output_data.c_str(), 1.0f,1.0f,1.0f);
   }
   RenderString(1,height - 30, "--------------------------------------------", 1.0f,1.0f,1.0f);
   std::string _input = "Ignite@Phoenix > " + _my_input;
   RenderString(1,height - 15, _input.c_str(), 1.0f,1.0f,1.0f);
  glPopMatrix();
 glFlush();
 glutSwapBuffers();
}