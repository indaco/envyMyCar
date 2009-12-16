#include "Application.h"
#include <iostream>
#include <cstdlib>


//singleton pointer
CApplication* CApplication::s_pTheApplication = NULL;

//set singleton pointer

void CApplication::SetApplication(CApplication* pTheApp) {
    //ensure that there is not already an application
    if (s_pTheApplication != NULL) {
        //more than one application!
        std::cerr << "More than one CApplication created!" << std::endl;
        //exit
        exit(1);
    }
    //assign a value to the application
    s_pTheApplication = pTheApp;
}

//constructor

CApplication::CApplication() : CMessageHandler(NULL) {
    //set the application
    SetApplication(this);
    //initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to Init SDL:" << SDL_GetError() << std::endl;
        exit(1);
    }
    //set up SDL_Quit to be called during exit
    atexit(SDL_Quit);
}

//destructor

CApplication::~CApplication() {
}

//initialization

bool CApplication::OnInit(int argc, char* argv[]) {
    //by default, simply return true
    return (true);
}

//event occurrence

void CApplication::OnEvent(SDL_Event* pEvent) {
    //by default, do nothing
}

//idle behavior

void CApplication::OnIdle() {
    //by default, do nothing
}

//cleanup

void CApplication::OnExit() {
    //by default, do nothing
}

//execution of application

int CApplication::Execute(int argc, char* argv[]) {
    //check for an application
    if (GetApplication() == NULL) {
        //no application
        std::cerr << "No application has been instantiated!" << std::endl;
        //return error code
        return (-1);
    }
    //attempt to initialize application
    if (!GetApplication()->OnInit(argc, argv)) {
        //could not initialize
        std::cerr << "Could not initialize application!" << std::endl;
        //return
        return (-1);
    }
    //event structure
    SDL_Event event;
    //forever
    for (;;) {
        //poll for an event
        if (SDL_PollEvent(&event) == 1) {
            //check for a quit event
            if (event.type == SDL_QUIT) {
                exit(0);
                break;
            }
            //event occurred
            GetApplication()->OnEvent(&event);
        } else {
            //no event, so idle
            GetApplication()->OnIdle();
        }
    }
    //clean up
    GetApplication()->OnExit();
    //return
    return (0);
}

//get singleton
CApplication* CApplication::GetApplication() {
    //return static pointer to application
    return (s_pTheApplication);
}
