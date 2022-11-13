#include "sceneSDL.h"
#include <time.h>

void manger(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama mange.\n");
    *barreD -= drain;
    *barreJ -= drain;
    *barreM += 2*drain;
    if(*barreM>=1.0){
        *barreM=1.0;
    }
}

void dormir(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama dort.\n");
    *barreM -= drain;
    *barreJ -= drain;
    *barreD += 2*drain;
    if(*barreD>=1.0){
        *barreD=1.0;
    }
}

void jouer(float * barreD, float * barreM,float * barreJ,float drain){
    printf("Tama joue.\n");
    *barreM -= drain;
    *barreD -= drain;
    *barreJ += 2*drain;
    if(*barreJ>=1.0){
        *barreJ=1.0;
    }
}

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

    float probaEtat[3][3] ={{0.1, 0.4, 0.5},
                            {0.4, 0.2, 0.4},
                            {0.5, 0.4, 0.1}};
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
    int probaCumul[3][3];
    int i,j,k,a;
    int delai = 200;
    SDL_bool actionUser = SDL_FALSE;

    // variable pour faire fonctionner l'IA
    float Qmax;
    int ActionMax;

    FILE * fichier = fopen("Qtable.txt","r");      //chargement d'un fichier
    float Qtable[11][11][11][3];
    
    for(i = 0; i < 11; i++){
        for (j = 0; j < 11 ; j++){
            for (k = 0; k < 11 ; k++){
  
                    fscanf(fichier,"%*d %*d %*d %f %f %f", &Qtable[i][j][k][0],&Qtable[i][j][k][1],&Qtable[i][j][k][2]);
                 
            }
        } 
    }
    
    for (i = 0;i<3;i++){
        for (j = 0; j<3;j++){
            probaCumul[i][j]=probaEtat[i][j]*10;
            if(i>0){
                probaCumul[i][j]+=probaCumul[i-1][j];
            }
        }
    }

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
                    actionUser = SDL_TRUE;
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
                        case SDL_MOUSEBUTTONDOWN:
                            curX=event.motion.x;
                            curY = event.motion.y;
                            break;
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

        //BOUCLE DE DETERMINATION DE LA PROCHAINE ACTION (MARKOV)

        /*if(ticks>1){
            ticks = 0;
            outil = rand()%10;
            nextState = 0;
            if(!actionUser){
                while(outil>probaCumul[nextState][etat]){
                    nextState++;
                }
                switch (nextState)
                {
                    case 0:
                        dormir(&barreD,&barreM,&barreJ,drain);
                        currMood = 3;
                        currentRoom = 0;
                        break;
                    case 1:
                        manger(&barreM,&barreM,&barreJ,drain);
                        currMood = 1;
                        currentRoom = 1;
                        break;
                    case 2:
                        jouer(&barreD,&barreM,&barreJ,drain);
                        currMood = 2;
                        currentRoom = 2;
                        break;
                    default:
                        break;
            }
        }
        } */
        //FIN MARKOV

        if(!actionUser){
            Qmax = Qtable[(int)(barreM*10)][(int)(barreD*10)][(int)(barreJ*10)][0];
        ActionMax = 0;
        for(a = 1; a < 3 ; a++){
            if (Qtable[(int)(barreM*10)][(int)(barreD*10)][(int)(barreJ*10)][a] > Qmax){
                Qmax = Qtable[(int)(barreM*10)][(int)(barreD*10)][(int)(barreJ*10)][a];
                ActionMax = a;
            } 
        }


        switch (ActionMax)
                {
                    case 1:
                        dormir(&barreD,&barreM,&barreJ,drain);
                        currMood = 3;
                        currentRoom = 0;
                        break;
                    case 0:
                        manger(&barreD,&barreM,&barreJ,drain);
                        currMood = 1;
                        currentRoom = 1;
                        break;
                    case 2:
                        jouer(&barreD,&barreM,&barreJ,drain);
                        currMood = 2;
                        currentRoom = 2;
                        break;
                    default:
                        break;
            }
        }
        

    
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
        actionUser = SDL_FALSE;
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
}