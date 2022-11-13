#include "action.h"

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