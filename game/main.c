#include "sceneSDL.h"
#include "action.h"
#include <time.h>

int main(){

    //init sdl
    SDL_Window 
       *window_1 = NULL;

    SDL_DisplayMode current;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
            SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    int ticks = 0;
    SDL_GetCurrentDisplayMode(0, &current);
    int curX,curY;
    int currMood = 0;
    int WindowW = current.h/2;
    int WindowH = 1.3*current.h/2;

    window_1 = SDL_CreateWindow("Tama!Go!CHI!",current.w/2-current.h/4,0,WindowW,WindowH,SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED );
    //fin init


    srand( time( NULL ) );
    
    float barreD = (rand()%6);
    barreD = barreD/10+0.2;
    
    float barreM = (rand()%6);
    barreM = barreM/10+0.2;
    
    float barreJ = (rand()%6);
    barreJ = barreJ/10+0.2;
    
    printf("Etat de départ des barres => Manger : %f, Dormir : %f, Jouer : %f\n", barreM, barreD, barreJ);
    SDL_Event event;


    SDL_Rect position;
    position.x = WindowW*0.1;
    position.y = WindowH*(-0.4);
    position.w = WindowW;
    position.h = WindowH;
    int etatPause = 0;
    int currentRoom = 0;
    int program_on = 1;
    int etat = 1;
    float drain = 0.1;
    int delai = 200;

    //ECRAN DE DEBUT
    eclosion(renderer,WindowW,WindowH);

    //BOUCLE DE JEU
    while(program_on){
            
            while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            currentRoom = (currentRoom-1+3)%3;
                            break;
                        case SDLK_RIGHT:
                            currentRoom = (currentRoom+1+3)%3;
                            break;
                        case SDLK_SPACE:
                            etatPause = (etatPause+1)%2;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    program_on = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    curX=event.motion.x;
                    curY = event.motion.y;
                    ticks =0;

                    //DETERMINATION BOUTON APPUYE
                    if((curY)>=WindowH*0.75 && curY<=WindowH*0.95+50){
                        if(curX >= 50 && curX <=WindowH*0.2+50){
                            manger(&barreD,&barreM,&barreJ,drain);
                            currMood = 1;
                            currentRoom = 1;
                        }
                        else if(curX >= 200 && curX <=WindowH*0.2+200){
                            jouer(&barreD,&barreM,&barreJ,drain);
                            currMood = 2;
                            currentRoom = 2;
                        }
                        else if(curX >= 350 && curX <=WindowH*0.2+350){
                            dormir(&barreD,&barreM,&barreJ,drain);
                            currMood = 3;
                            currentRoom = 0;
                        }
                    }
                default:
                    break;
            }
        }

        while(etatPause){
                pause(etat,renderer,WindowW);
                SDL_RenderPresent(renderer);
                SDL_WaitEvent(&event);
                    switch(event.type){
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                                case SDLK_SPACE:
                                etatPause = (etatPause+1)%2;
                                break;
                            }
                            break;
                        case SDL_QUIT:
                            program_on = 0;
                            etatPause = 0;
                            break;
                    }
                
            }
        
        //ON EVITE LES ERREURS D'AFFICHAGE
        if(barreM<=0.0){
            barreM = 0.0;
        }
        if(barreD<=0.0){
            barreD = 0.0;
        }
        if(barreJ<=0.0){
            barreJ = 0.0;
        }

        if(barreM>=1.0||barreD>=1.0||barreJ>=1.0||barreM<=0.0||barreD<=0.0||barreJ<=0.0){
            program_on = 0;
            animeMort(renderer,WindowW,WindowH,position);
        }
    
        if(program_on){
            afficheTama(renderer,position,currMood,currentRoom,barreM,barreJ,barreD,WindowW,WindowH,etatPause);
        }

        ticks++;
        currMood=0;
        SDL_Delay(delai);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
}