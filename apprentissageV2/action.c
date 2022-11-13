#include <stdio.h>


void manger(float * barreD, float * barreM,float * barreJ,int currentRoom,float drain){
    printf("Tama mange.\n");
    if(currentRoom == 0){
        *barreD -= drain;
        *barreJ -= drain;
        *barreM = 1.0;
    }
}

void dormir(float * barreD, float * barreM,float * barreJ,int currentRoom,float drain){
    printf("Tama dort.\n");
    if(currentRoom == 2){
        *barreM -= drain;
        *barreJ -= drain;
        *barreD = 1.0;
    }
} 
void jouer(float * barreD, float * barreM,float * barreJ,int currentRoom,float drain){
    printf("Tama joue.\n");
    if(currentRoom == 4){
        *barreM -= drain;
        *barreD -= drain;
        *barreJ = 1.0;
    }
}

void deplaceDroite(float * barreD, float * barreM,float * barreJ,int * currentRoom,float drain){
    *currentRoom=(*currentRoom+1+7)%7;
    *barreM -= drain;
    *barreD -= drain;
    *barreJ -= drain;
}

void deplaceGauche(float * barreD, float * barreM,float * barreJ,int * currentRoom,float drain){
    *currentRoom=(*currentRoom-1+7)%7;
    *barreM -= drain;
    *barreD -= drain;
    *barreJ -= drain;
}