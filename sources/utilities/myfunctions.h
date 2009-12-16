#ifndef _FUNCTIONS_H
#define	_FUNCTIONS_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "LogFile.h"


GLuint loadBMPTexture(const char * filename, GLuint texture, int wrap);
void logVideoInfo(const SDL_VideoInfo * vInfo, LogFile *log);


#endif	/* _FUNCTIONS_H */

