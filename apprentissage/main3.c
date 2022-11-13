#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#define nbIte 1000
#define learnRate 0.9
#define discount 0.5
#define TAILLE 1000

#define NB_ITER 200
#define NB_ACTION 3

typedef struct lineTab {
	int x ;
    int y;
    int z;
    int a;
} lineTab_t ;

typedef struct pile
{
    int nbElts;
    int position;
    lineTab_t * tab ; 
}pile_t;

pile_t * init_pile(int taille)
{
    pile_t * nouv = NULL;
    nouv = malloc(sizeof(pile_t));
    nouv->nbElts = taille;
    nouv->tab = malloc(sizeof(lineTab_t) * taille);
    nouv->position = -1;
    return nouv;
}


int EstVidePile(pile_t *p)
{
    return (p->position == -1);
}


pile_t *  empiler(pile_t * p, lineTab_t data)
{
    if (p->position < p->nbElts)
    {
        p->position += 1;
        p->tab[p->position] = data;
    }
    return p ;
}

pile_t* depiler(pile_t * p, lineTab_t * result)
{
    if (! (EstVidePile(p)))
    {
        *result = p->tab[p->position];
        p->position -= 1;
        
    } 
    return p ;
}

void libererPile(pile_t * p)
{
    if (p != NULL)
    {
        free(p->tab);
        p->tab=NULL;
        free(p);
        p=NULL;
    } 
}

void afficherPile(pile_t * p)
{
    if (p != NULL)
    {
        for (int i = p->position; i>-1; i--)
        {
            printf("%d %d %d %d",p->tab[i].x,p->tab[i].y,p->tab[i].z,p->tab[i].a);

            printf("\n");
        }
    } 
    else{
        printf("pile vide");
    } 
}

void sauvTable(float Qtable[11][11][11][3]){
    int i,j,k,a;
    FILE *fichier = fopen ("Qtable.txt", "w" );
    if (fichier == NULL){
        printf("erreur lors de l'ouverture du fichier");
        }
    else{
        for(i = 0; i<11; i++){
                for(j = 0; j<11; j++){
                    for(k = 0; k<11; k++){
                        fprintf (fichier, "%d %d %d",i, j, k);
                        for(a = 0; a<3; a++){
                            fprintf (fichier, " %f", Qtable[i][j][k][a]);
                            Qtable[i][j][k][a] = 0; 
                        }
                        fprintf (fichier, "\n" );
                    } 
                } 
            } 
        }
    fclose(fichier);
}

lineTab_t etatSuivant(lineTab_t ligne, int drain){
    if(ligne.a==0){
        ligne.x += drain * 2;
        if(ligne.x >10){
            ligne.x = 10;
        }
    }
    else if (ligne.a==1){ 
            ligne.y += drain * 2;
            if(ligne.y >10){
            ligne.y = 10;
        }
    }
    else{
        ligne.z += drain *2;
        if(ligne.z >10){
            ligne.z = 10;
        }
    }
    ligne.x-=drain;
    ligne.y-=drain;
    ligne.z-=drain;
    return ligne;
}

int main(){
    srand(time(NULL));
    float Qtable[11][11][11][3];
    int i,j,k,a ;
    for(i = 0; i<11; i++){
        for(j = 0; j<11; j++){
            for(k = 0; k<11; k++){
                for(a = 0; a<3; a++){
                    Qtable[i][j][k][a] = 0; 
                } 
            } 
        } 
    }
    //sauvTable(Qtable);
    int ite;
    lineTab_t ligne;
    pile_t * p;
    

    float barreM,barreD,barreJ;

    
    int drain = 1;
    int greedy = 0,alea;
    int program_on = 1;
    float q1,q2,q3;
    lineTab_t prec,curr;
    int ChoixMax;
    float Qmax;
    int CompteurIterationProgramme;
    p = init_pile(TAILLE);

    for(CompteurIterationProgramme = 0 ; CompteurIterationProgramme < 100000000 ; CompteurIterationProgramme ++){ 
    //BOUCLE DE REMPLISSAGE DE LA PILE
    program_on = 1;
    //il faudrait peut etre envisage les situation initiales 0.1 et 0.9
    barreM=(rand()%7)+2;
    barreJ=(rand()%7)+2;
    barreD=(rand()%7)+2;
    ligne.x=barreM;
    ligne.y=barreJ;
    ligne.z=barreD;
    ite = 0;
    while(ite<nbIte&&program_on){
        alea = rand() % NB_ITER ;
		if (greedy < alea) { 
			// choix d'une action aleatoire
			ligne.a = rand() % NB_ACTION ;
		}
		else {
            q1 = Qtable[ligne.x][ligne.y][ligne.z][0];
            q2 = Qtable[ligne.x][ligne.y][ligne.z][1];
            q3 = Qtable[ligne.x][ligne.y][ligne.z][2];
            if (q1 > q2) {
				if (q1 > q3) {
					ligne.a = 0 ;
				}
				else {
					ligne.a = 2 ;
				}
			}
			else {
				if (q2 > q3) {
					ligne.a = 1 ;
				}
				else {
					ligne.a = 2 ;
				}
			}
        }
        
        
        if(ligne.x>=10||ligne.y>=10||ligne.z>=10||ligne.x<=0||ligne.y<=0||ligne.z<=0){
            program_on = 0;
        }
        //printf("%d : (%d %d %d %d)\n",ite,ligne.x,ligne.y,ligne.z,ligne.a);
        empiler(p,ligne);
        
        
        ligne = etatSuivant(ligne,drain);
        ite ++;
        //greedy++;
        
    }
    
    //afficherPile(p);
    float r = 1/(1+exp(-ite));
    //UPDATE QTABLE
    depiler(p,&prec);
    Qtable[prec.x][prec.y][prec.z][prec.a] += learnRate * (r - Qtable[prec.x][prec.y][prec.z][prec.a]);
    while(!EstVidePile(p)){

        depiler(p,&curr);
        ite--;
        r = 1/(1+exp(-ite));

        Qmax = Qtable[prec.x][prec.y][prec.z][0];
        for(ChoixMax = 1; ChoixMax < 3; ChoixMax++){
            if (Qtable[prec.x][prec.y][prec.z][ChoixMax] > Qmax){
                Qmax = Qtable[prec.x][prec.y][prec.z][ChoixMax];
            } 
        } 
        
        Qtable[curr.x][curr.y][curr.z][curr.a] += learnRate * (r + discount*Qmax - Qtable[curr.x][curr.y][curr.z][curr.a]);
        if(Qtable[curr.x][curr.y][curr.z][curr.a]>2){
            printf("COUCOU %f\n",Qtable[curr.x][curr.y][curr.z][curr.a]);
        }
        prec = curr;
    }
    
        
    printf("iteration numero : %d \n ",CompteurIterationProgramme);
    
    }
    sauvTable(Qtable);
    libererPile(p);
    
    return 0;
}