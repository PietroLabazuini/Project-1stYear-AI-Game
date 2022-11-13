#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sceneSDL.h"

SDL_Color gris = {155,155,155,255};
SDL_Color grisF = {120,120,120,255};
SDL_Color noir = {0,0,0,255};
SDL_Color rouge = {255,0,0,255};
SDL_Color cyan = {0,250,255,255};
SDL_Color vert = {0,255,30,255};

void eclosion(SDL_Renderer * renderer,int windowW,int windowH){
    SDL_Rect source,position;

    //TITRE
    SDL_Texture * textureTitre = IMG_LoadTexture(renderer,"./image/titre.png");
    SDL_Rect positionT,sourceT;
    SDL_QueryTexture(textureTitre,NULL,NULL,&sourceT.w,&sourceT.h);
    positionT.x = 0;
    positionT.y = 0;
    positionT.w = windowW;
    positionT.h = windowH*0.3-sourceT.h*0.2;
    sourceT.x = 0;
    sourceT.y = 0;
    sourceT.h = sourceT.h*0.55;

    SDL_Texture * texture = IMG_LoadTexture(renderer,"./image/eclosion.png");

    SDL_QueryTexture(texture,NULL,NULL,NULL,&source.h);
     int i;
    position.x = windowW/4;
    position.y = windowH*0.4;

    
    //TABLEAU CONTENANT LES COORDONNES DES 6 SPRITES DE L'OEUF
    SDL_Rect spriteOeuf[6];

    for (i = 0;i<6;i++){
        spriteOeuf[i].h = 125;
        spriteOeuf[i].y = 0;
    }

    spriteOeuf[0].x=35;
    spriteOeuf[0].w=117-35;

    spriteOeuf[1].x = 142;
    spriteOeuf[1].w = 223-142;

    spriteOeuf[2].x = 249;
    spriteOeuf[2].w = 330-249;

    spriteOeuf[3].x=356;
    spriteOeuf[3].w=447-356;

    spriteOeuf[4].x=460;
    spriteOeuf[4].w=596-460;

    spriteOeuf[5].x=605;
    spriteOeuf[5].w=763-605;

    //AFFICHAGE OEUFS
    for (i = 0;i<6;i++){
        SDL_RenderCopy(renderer, textureTitre, &sourceT, &positionT);
        position.w = spriteOeuf[i].w*windowH*0.005;
        position.h = windowH/2;
        SDL_RenderCopy(renderer, texture, &spriteOeuf[i], &position);
        SDL_RenderPresent(renderer);
        SDL_Delay(300);
        SDL_RenderClear(renderer);
    }
    SDL_Delay(1500);

    //AFFICHAGE ECRAN DE DEMARAGE
    
    SDL_QueryTexture(textureTitre,NULL,NULL,&sourceT.w,&sourceT.h);
    texture = IMG_LoadTexture(renderer,"./image/pingouinOut.png");

    SDL_Rect flash,pingouin;
    SDL_QueryTexture(texture,NULL,NULL,&flash.w,&flash.h);
    
    SDL_Texture * texturePingouin = IMG_LoadTexture(renderer,"./image/pingouin.png");
    flash.y=0;
    flash.w=flash.w/2;

    position.x=-0.05*windowH;
    position.y = 0.25 * windowH;
    position.w = windowW*1.3;
    position.h = windowH;
    SDL_QueryTexture(texture,NULL,NULL,&pingouin.w,&flash.h);
    pingouin.x = position.x + position.w/2 - pingouin.w/2;
    pingouin.h = windowH*0.2;
    pingouin.y = position.y;
    pingouin.w = position.w;

    SDL_Rect posP;
    posP.x = 0.35*windowW;
    posP.y = 0.6*windowH;
    posP.w = 0.2*windowH;
    posP.h = 0.3*windowH;

    source.x = 0;
    source.y = 0;
    SDL_QueryTexture(texturePingouin,NULL,NULL,&source.w,&source.h);

    for(int i = 0; i < 10;i++){
        flash.x=((i%2)*2*flash.w)/2;
        SDL_RenderCopy(renderer, texture, &flash, &position);
        SDL_RenderCopy(renderer, textureTitre, &sourceT,&positionT);

        SDL_RenderCopy(renderer, texturePingouin, &source, &posP);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texturePingouin);
    SDL_DestroyTexture(textureTitre);
}



void initSDL(int currentRoom,float barreM,float barreJ,float barreD,SDL_Renderer * renderer,int windowW,int windowH){
    char salles[3][20]={{"./image/chambre.jpg"},{"./image/cuisine.png"},{"./image/stade.jpg"}};
    char icones[3][20]={{"./image/manger.png"},{"./image/jouer.png"},{"./image/dormir.png"}};
    SDL_Rect position,position2,source;


    //image de fond
    SDL_Texture * texture = IMG_LoadTexture(renderer,salles[currentRoom]);
    SDL_QueryTexture(texture,NULL,NULL,NULL,&source.h);
    source.x = 0;
    source.y= source.h/4;
    source.w=source.h;

    position.x = 0;
    position.y = 0;
    position.w = windowW;
    position.h = windowH;
    SDL_RenderCopy(renderer, texture, &source, &position);
        
    SDL_Color couleur[3]={rouge,vert,cyan};
    float barres[3] = {barreM,barreJ,barreD};

    //barres de vie
    int ecartBarre = windowW*0.02;

    position.w = windowW/16;
    position.y = ecartBarre;
    position.h = windowH/4;
        
    for (int i = 0; i < 3;i++){
        position.x= i * position.w + ecartBarre *(i+1);
        position2.x = position.x+0.5*ecartBarre;
        position2.w = position.w-ecartBarre;
        position2.h = position.h*barres[i];
        position2.y = (position.h+position.y-(position2.h));
           if(barres[i]!=0){
           position2.h -= 5;
        }
            
        SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
        SDL_RenderFillRect(renderer,&position);
        SDL_SetRenderDrawColor(renderer,couleur[i].r,couleur[i].g,couleur[i].b,couleur[i].a);
        SDL_RenderFillRect(renderer,&position2);
    }

    //barre du bas
    SDL_SetRenderDrawColor(renderer,gris.r,gris.g,gris.b,gris.a);
    position.x = 0;
    position.y = windowH*0.7;
    position.h = windowH*0.3;
    position.w = windowW;
    SDL_RenderFillRect(renderer,&position);

    //boutons
    SDL_SetRenderDrawColor(renderer,grisF.r,grisF.g,grisF.b,grisF.a);
    
    //positions boutons
    int ecartBoutons = windowW*0.05;
    position.y = windowH*0.75;
    position.w = (windowW-4*ecartBoutons)/3;
    position.h = position.w;


    //positions icones relatives aux boutons
    SDL_Rect icone;
    icone.w=position.w*0.85;
    icone.h=position.h*0.85;

    for (int i = 0; i < 3;i++){
        //boutons
        position.x= i * position.w + ecartBoutons *(i+1);
        SDL_SetRenderDrawColor(renderer,couleur[i].r,couleur[i].g,couleur[i].b,couleur[i].a);
        SDL_RenderFillRect(renderer,&position);

        //icones
        texture = IMG_LoadTexture(renderer,icones[i]);
        source.x=0;
        source.y=0;
        SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);

        icone.x=position.x+0.1*icone.w;
        icone.y=position.y+0.1*icone.w;

        SDL_RenderCopy(renderer, texture, &source, &icone);
    }
    SDL_DestroyTexture(texture);
}

void pause(int etat,SDL_Renderer * renderer,int WindowW){
    SDL_Texture * texture;
    if(etat){
        texture = IMG_LoadTexture(renderer,"./image/pause.png");


        //code qui était en dessous avant

        SDL_Rect position,source;
        source.x=0;
        source.y=0;
        SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
        
        position.x = WindowW*0.75;
        position.y = 0;
        position.h = WindowW*0.25;
        position.w = WindowW*0.25;

        SDL_RenderCopy(renderer, texture, &source, &position);
        SDL_DestroyTexture(texture);
    }
}

void afficheTama(SDL_Renderer * renderer,SDL_Rect position,int currMood,int currentRoom,float barreM,float barreJ,float barreD,int WindowW,int WindowH,int etat){
    SDL_Texture * texture = IMG_LoadTexture(renderer,"./image/spriteSheet.png");
    SDL_Rect source,sprite;
    
    SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
    int hauteurCase = source.h/7;
    int LargeurCase = source.w/12;
    sprite.w=LargeurCase;
    sprite.h=hauteurCase;
    
    

    int nbSprite;

    switch(currMood){
        case 0 :
            nbSprite=12;
            sprite.y = 0;
            break;
        case 1 :
            nbSprite = 7;
            sprite.y = hauteurCase;
            break;
        case 2 :
            nbSprite=6;
            sprite.y = 3*hauteurCase;
            break;
        case 3 :
            nbSprite = 9;
            sprite.y = 6*hauteurCase;
            break;
        case 4 :
            break;
    }

    for (int i = 0;i<nbSprite;i++){
        //ON AFFICHE LA SCENE AVANT LE PERSO
        initSDL(currentRoom,barreM,barreJ,barreD,renderer,WindowW,WindowH);
        pause(etat,renderer,WindowW);
        //AFFICHAGE TAMAGOCHI

        sprite.x = i*LargeurCase;
        SDL_RenderCopy(renderer, texture, &sprite, &position);
        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }
    
    SDL_DestroyTexture(texture);
}

void animeMort(SDL_Renderer * renderer,int WindowW,int WindowH,SDL_Rect pingouin){
    SDL_Texture * texture = IMG_LoadTexture(renderer,"./image/explosion.png");
    SDL_Texture * pingouinT = IMG_LoadTexture(renderer,"./image/spriteSheet.png");
    SDL_Rect position,source,sourceP;
    SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
    int hauteurCase = source.h/5;
    int largeurCase = source.w/5;

    source.h=hauteurCase;
    source.w=largeurCase;
    SDL_QueryTexture(pingouinT,NULL,NULL,&sourceP.w,&sourceP.h);
    sourceP.w/=12;
    sourceP.h/=7;
    sourceP.y=5*sourceP.h;

    position.x =WindowW/4;
    position.y = WindowH/4;
    position.w = WindowW/2;
    position.h = WindowH/2;


    
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    for (int i =0;i<5;i++){
        source.y=i*hauteurCase;
        for (int j = 0; j < 4 ;j++){
            sourceP.x = j*sourceP.w;
            SDL_RenderClear(renderer);

            
            
            source.x = j*largeurCase;
            SDL_RenderCopy(renderer,texture,&source,&position);
            SDL_RenderCopy(renderer,pingouinT,&sourceP,&position);
            SDL_RenderPresent(renderer);
            SDL_Delay(200);
        }
    }

    SDL_DestroyTexture(texture);
}