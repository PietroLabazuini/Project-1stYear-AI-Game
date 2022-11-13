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
    positionT.h = windowH*0.3;
    sourceT.x = 0;
    sourceT.y = 0;
    sourceT.h = sourceT.h*0.55;

    SDL_Texture * texture = IMG_LoadTexture(renderer,"./image/eclosion.png");

    SDL_QueryTexture(texture,NULL,NULL,NULL,&source.h);
     int i;
    position.x = windowW/3;
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
    posP.x = 0.4*windowW;
    posP.y = 0.5*windowH;
    posP.w = 0.3*windowH;
    posP.h = 0.45*windowH;


    positionT.h = windowH*0.3+0.55*sourceT.h;;

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

void afficheBarre(SDL_Renderer * renderer,int windowW,int windowH){
    char icones[3][20]={{"./image/manger.png"},{"./image/jouer.png"},{"./image/dormir.png"}};
    SDL_Rect position,source;
    SDL_Texture * texture;
    SDL_SetRenderDrawColor(renderer,grisF.r,grisF.g,grisF.b,grisF.a);
    
    //barre du bas

    texture = IMG_LoadTexture(renderer,"./image/hotbar.png");
    SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
    source.x = 0;
    source.y = 0;
    
    position.y = windowH*0.75;
    position.h = windowH*0.2;
    position.w = windowW*0.3;
    position.x = windowW/2-position.w/2;
    SDL_RenderCopy(renderer,texture,&source,&position);

    //boutons
    
    SDL_Rect icone;
    icone.w=position.w*0.3;
    icone.h=position.h*0.85;

    for (int i = 0; i < 3;i++){

        //icones
        texture = IMG_LoadTexture(renderer,icones[i]);
        source.x=0;
        source.y=0;
        SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);

        icone.x=position.x+0.03*icone.w;
        icone.y=position.y+0.03*icone.h;
        position.x += position.w*0.35;

        SDL_RenderCopy(renderer, texture, &source, &icone);
    }
    SDL_DestroyTexture(texture);
}


void carte(SDL_Renderer * renderer,int currentRoom,int WindowW){
    char map[8][30]={{"./image/mapCuisine.png"},{"./image/mapCouloir1.png"},{"./image/mapChambre.png"},{"./image/mapCouloir2.png"},{"./image/mapSalleJeu.png"},{"./image/mapCouloir3.png"},{"./image/mapCouloir4.png"}};
    SDL_Texture * texture = IMG_LoadTexture(renderer,map[currentRoom]);
    
    SDL_Rect position,source;

    SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
    source.x = 0;
    source.y = 0;

    position.x = 0.75 * WindowW;
    position.y = 0;
    position.w = source.w;
    position.h = source.h;
    SDL_RenderCopy(renderer, texture, &source, &position);
    SDL_DestroyTexture(texture);
}

void initSDL(int currentRoom,float barreM,float barreJ,float barreD,SDL_Renderer * renderer,int windowW,int windowH){
    char salles[8][20]={{"./image/cuisine.png"},{"./image/couloir.png"},{"./image/chambre.jpg"},{"./image/couloir.png"},{"./image/stade.jpg"},{"./image/couloir.png"},{"./image/couloir2.png"}};
    char barre[3][20]={{"./image/barreM.png"},{"./image/barreJ.png"},{"./image/barreD.png"}};
    int barreVal[3]={barreM*10,barreJ*10,barreD*10};
    SDL_Rect position,source;


    //image de fond
    SDL_Texture * texture = IMG_LoadTexture(renderer,salles[currentRoom]);
    SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
    source.x = 0;
    source.y= 0;

    position.x = 0;
    position.y = 0;
    position.w = windowW;
    position.h = windowH;
    SDL_RenderCopy(renderer, texture, &source, &position);

    position.w = windowW/8;
    position.y = 50;
    position.h = windowH/4;
      
    for (int i = 0; i < 3;i++){
        texture = IMG_LoadTexture(renderer,barre[i]);
        SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
        source.w = source.w /11;
        source.x = barreVal[i]*source.w;  
        position.x= i * (position.w + 100)/3;

        SDL_RenderCopy(renderer, texture, &source, &position);
    }
    
    SDL_DestroyTexture(texture);
}

void pause(int etat,SDL_Renderer * renderer,int WindowW,int WindowH){
    SDL_Texture * texture;
    if(etat){
        texture = IMG_LoadTexture(renderer,"./image/pause.png");


        //code qui était en dessous avant

        SDL_Rect position,source;
        source.x=0;
        source.y=0;
        SDL_QueryTexture(texture,NULL,NULL,&source.w,&source.h);
        
        position.h = WindowW*0.25;
        position.w = WindowW*0.25;
        position.x = WindowW/2-position.w/2;
        position.y = WindowH/2-position.h/2;

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
        carte(renderer,currentRoom,WindowW);
        
        //AFFICHAGE TAMAGOCHI

        sprite.x = i*LargeurCase;
        SDL_RenderCopy(renderer, texture, &sprite, &position);
        afficheBarre(renderer,WindowW,WindowH);
        pause(etat,renderer,WindowW,WindowW);
        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }
    
    SDL_DestroyTexture(texture);
}

void animeMort(SDL_Renderer * renderer,int WindowW,int WindowH){
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
    sourceP.y=5*hauteurCase;

    position.x =WindowW/4;
    position.y = WindowH/4;
    position.w = WindowW/2;
    position.h = WindowH/2;


    
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    for (int i =0;i<5;i++){
        source.y=i*hauteurCase;
        for (int j = 0; j < 5 ;j++){
            sourceP.x = j*largeurCase;
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer,pingouinT,&sourceP,&position);
            
            source.x = j*largeurCase;
            SDL_RenderCopy(renderer,texture,&source,&position);
            SDL_RenderPresent(renderer);
            SDL_Delay(200);
        }
    }

    SDL_DestroyTexture(texture);
}