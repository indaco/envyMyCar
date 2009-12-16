#include "myfunctions.h"



// LOAD A TEXTURE UTILIZZANDO SDL (LA TEXTURE DEVE ESSERE IN FORMATO BITMAP)
//
// SI SUPPONE CHE id SIA L'HANDLE DELLA TEXTURE PRECEDENTEMENTE GENERATA CON glGenTextures(..)

GLuint loadBMPTexture(const char * filename, GLuint texture, int wrap) {
    SDL_Surface *surface;
    if ((surface = SDL_LoadBMP(filename))) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        // ALLOCA LA TEXTURE
        glGenTextures(1, &texture);
        // BINDA LA TEXTURE
        glBindTexture(GL_TEXTURE_2D, texture);
        // MINIFICATION
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        // MAGNIFICATION
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // GL_REPEAT => RIPETIZIONE DELLA TEXTURE
        // GL_CLAMP  => ADEGUA LA TEXTURE ALLA SUPERFCIE SU CUI LA DEVE ATTACCARE
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);
        // CARICA LA TEXTURE
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, surface->w, surface->h, GL_BGR_EXT, GL_UNSIGNED_BYTE, surface->pixels);

    } else {
        printf("SDL could not load image.bmp: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    if (surface) {
        SDL_FreeSurface(surface);
    }
    return texture;
}

void loadTexture(const char* fname, int id) {
    SDL_Surface *s = SDL_LoadBMP(fname);

    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // UV MODE (REPEAT/CLAMP) SETTINGS	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // MINIFICATION-MAGNIFICATION SETTINGS
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // MIPMAPPING
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, s->w, s->h, GL_BGR, GL_UNSIGNED_BYTE, s->pixels);

    SDL_FreeSurface(s);
}

void logVideoInfo(const SDL_VideoInfo * vInfo, LogFile *log) {
    log->writeLog(LOG_PLAINTEXT, "*** Getting SDL Video Informations ***");
    log->writeLog(LOG_SUCCESS, "hw_available?  %d ", vInfo->hw_available);
    log->writeLog(LOG_SUCCESS, "wm_available? %d", vInfo->wm_available);
    log->writeLog(LOG_SUCCESS, "blit_hw?  %d", vInfo->blit_hw);
    log->writeLog(LOG_SUCCESS, "blit_hw_CC? %d ", vInfo->blit_hw_CC);
    log->writeLog(LOG_SUCCESS, "blit_hw_a?  %d", vInfo->blit_hw_A);
    log->writeLog(LOG_SUCCESS, "blit_sw?  %d", vInfo->blit_sw);
    log->writeLog(LOG_SUCCESS, "blit_sw_CC? %d ", vInfo->blit_sw_CC);
    log->writeLog(LOG_SUCCESS, "blit_sw_A? %d ", vInfo->blit_sw_A);
    log->writeLog(LOG_SUCCESS, "video memory(in Kb)? %d ", (int) vInfo->video_mem);
    log->writeLog(LOG_SUCCESS, "bits per pixel? %d ", (int) vInfo->vfmt->BitsPerPixel);
    log->writeLog(LOG_PLAINTEXT, "*** End of SDL Video Informations ***");
}
