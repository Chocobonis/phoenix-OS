#include "broken.c"

GLuint Bon_load_bmp(char *filename, int w, int h){
 std::cout<<"loading texture"<<std::endl;                                       // debug message
 GLuint tmp_txt;
  int comp = 4;
  unsigned char* image = stbi_load(filename, &w, &h, &comp, STBI_rgb_alpha);

  if(image == nullptr){
    glGenTextures(1, &tmp_txt);
    glBindTexture(GL_TEXTURE_2D, tmp_txt);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);                
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);                 // these are the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, brk_tex.bytes_per_pixel, brk_tex.width, brk_tex.height, GL_RGBA, GL_UNSIGNED_BYTE, brk_tex.pixel_data);
  }
  glGenTextures(1, &tmp_txt);
  glBindTexture(GL_TEXTURE_2D, tmp_txt);

 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

 stbi_image_free(image);
 return tmp_txt;
}
/*
=================================================
=  FUNCTION TO CREATE A TEXTURE FROM .C FORMAT  =
=================================================
*/
GLuint Bon_create_texture(int bpp, int w, int h, const void *data){
 GLuint tmp_txt;
 glGenTextures(1, &tmp_txt);                                                  // CREATION OF A NEW TEXTURE
 glBindTexture(GL_TEXTURE_2D, tmp_txt);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);                 // generate the default texture once again
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
 return tmp_txt;
}