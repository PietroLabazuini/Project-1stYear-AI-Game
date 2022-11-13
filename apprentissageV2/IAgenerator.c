#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#define nbIte 1000
#define learnRate 0.75
#define discount 0.5
#define TAILLE 1001

#define NB_ITER 200
#define NB_ACTION 5
#define NB_SALLES 7  


typedef struct lineTab {
	int x ;
    int y;
    int z;
    int position;
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
        for (int i = p->position; i>-1;i--)
        {
            printf("%d %d %d %d %d",p->tab[i].x,p->tab[i].y,p->tab[i].z,p->tab[i].position,p->tab[i].a);

            printf("\n");
        }
    } 
    else{
        printf("pile vide");
    } 
}

void sauvTable(float Qtable[11][11][11][7][5]){
    int i,j,k,a,l;
    FILE *fichier = fopen ("Qtable.txt", "w" );
    if (fichier == NULL){
        printf("erreur lors de l'ouverture du fichier");
        }
    else{
        for(i = 0; i<11; i++){
            for(j = 0; j<11; j++){
                for(k = 0; k<11; k++){
                    for(l = 0; l<7; l++){
                        fprintf (fichier, "%d %d %d %d",i, j, k, l);
                        for(a = 0; a < 5; a++){
                            fprintf (fichier, " %f", Qtable[i][j][k][l][a]);
                        }
                        fprintf (fichier, "\n" );
                    } 
                } 
            } 
        }
    fclose(fichier);
    }
} 

lineTab_t etatSuivant(lineTab_t ligne, int drain){
    if(ligne.a==0){     //si je veux manger
        if (ligne.position == 0){   //si je suis dans la cuisine je mange
            ligne.x = 11;
        }
    
        }

    if(ligne.a==1){     //si je veux dormir
        if (ligne.position == 2){   //si je suis dans la chambre je dors
            ligne.y = 11;
        }
       
        }
        
    
    if(ligne.a==2){     //si je veux jouer
        if (ligne.position == 4){   //si je suis dans la sdj je joue
            ligne.z = 11;
        }
    
    }   

    if(ligne.a==3){
        ligne.position = (ligne.position - 1 + NB_SALLES)%NB_SALLES; //deplacement a gauche
    } 
    if(ligne.a==4){
        ligne.position = (ligne.position + 1 + NB_SALLES)%NB_SALLES; //deplacement a droite
    } 
    
    ligne.x-=drain;
    ligne.y-=drain;
    ligne.z-=drain;
    
    return ligne;
}

int main(){
    srand(time(NULL));
    float Qtable[11][11][11][7][5];
    int i,j,k,l,a ;
    for(i = 0; i<11; i++){
        for(j = 0; j<11; j++){
            for(k = 0; k<11; k++){
                for(l = 0; l < 7; l++){
                    for(a = 0; a < 5; a++){
                        Qtable[i][j][k][l][a] = 0; 
                    } 
                } 
            } 
        }
    }
    int ite;
    lineTab_t ligne;
    pile_t * p;
    

    float barreM,barreD,barreJ;



    int drain = 1;
    int greedy = 0,alea;
    int program_on = 1;
    lineTab_t prec,curr;
    int ChoixMax;
    int ActionMax;
    float Qmax;
    int CompteurIterationProgramme;
    p = init_pile(TAILLE);

    for(CompteurIterationProgramme = 0 ; CompteurIterationProgramme < 10000000 ; CompteurIterationProgramme ++){ 
    //BOUCLE DE REMPLISSAGE DE LA PILE
    program_on = 1;
    barreD = barreM = barreJ = 9;
    ligne.x=barreM;
    ligne.y=barreJ;
    ligne.z=barreD;
    ligne.position= 0;
    ite = 0;
    while(ite<nbIte&&program_on){
        alea = rand() % 1000000000 ;
		if (greedy < alea) { 
			if (ligne.position==0||ligne.position==2||ligne.position==4){ 
            // choix d'une action aleatoire
			ligne.a = rand() % NB_ACTION ;
            }
		}
		else {
            Qmax = Qtable[ligne.x][ligne.y][ligne.z][ligne.position][0];

            for(ChoixMax = 1; ChoixMax < 5; ChoixMax++){
            if (Qtable[ligne.x][ligne.y][ligne.z][ligne.position][ChoixMax] > Qmax){
                Qmax = Qtable[ligne.x][ligne.y][ligne.z][ligne.position][ChoixMax];
                ActionMax = ChoixMax;
            } 
            } 
            ligne.a = ActionMax;   
        }
        
        
        if(ligne.x<=0||ligne.y<=0||ligne.z<=0){
            program_on = 0;
        }
        
        empiler(p,ligne);
        
        
        ligne = etatSuivant(ligne,drain);
        ite ++;
        
        
    }
    
    float r = 10/(1+exp(-ite*10+200));

    //UPDATE QTABLE

    depiler(p,&prec);
    Qtable[prec.x][prec.y][prec.z][prec.position][prec.a] += learnRate * (r - Qtable[prec.x][prec.y][prec.z][prec.position][prec.a]);
    while(!EstVidePile(p)){

        depiler(p,&curr);
        ite--;

        Qmax = Qtable[prec.x][prec.y][prec.z][prec.position][0];
        for(ChoixMax = 1; ChoixMax < 5; ChoixMax++){
            if (Qtable[prec.x][prec.y][prec.z][prec.position][ChoixMax] > Qmax){
                Qmax = Qtable[prec.x][prec.y][prec.z][prec.position][ChoixMax];

            } 
        } 
        
        Qtable[curr.x][curr.y][curr.z][curr.position][curr.a] += learnRate * (discount*Qmax - Qtable[curr.x][curr.y][curr.z][curr.position][curr.a]); //enlever r   
        
        prec = curr;
    }
    
    
    }
    sauvTable(Qtable);
    libererPile(p);
    
    return 0;
}