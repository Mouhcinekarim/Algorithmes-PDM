#include <stdio.h>

#define N 3

#define nmax 100

#define namax 100

int ne;			   // Nombre d'états		
float Piaj[nmax][namax][nmax];
//={
//                              {{1,0,0},{0,1,0},{0,0,1}}
//							  ,
//							  {{1,0,0},{0,1,0},{0,0,1}}
//							  ,
//							  {{1,0,0},{0,1,0},{0,0,1}}
//							  }; //Probabilite de transition
float Ria[nmax][namax]={{1,2,3},{6,4,5},{8,9,7}}; //Recompence
int na[nmax]={3,3,3}; //Nombre d'actions de chaque etat
int strategie[nmax]; //Strategie intiale
float IP[nmax][nmax];
float J[nmax];
float U[nmax];
int stop;
void lire_Ria(){
    int i,a;
	           
	for( i=0; i<ne; i++){
		for( a=0; a<na[i]; a++){
			printf("R(%d,%d) ? :", i+1,a+1);
			scanf("%f", &Ria[i][a]);			
		}
	}
}

void lire_nbr_actions(){

    int i;	       
	for( i=0; i<ne; i++){
		printf(" Nbr_actions(%d) ? :", i+1);
		scanf("%d", &na[i]);		
	}	
}

//Lecture des probabilites de transitions
void lire_Piaj( ){
    int i,a,j;	   
	for( i=0; i<ne; i++){
		for( a=0; a<na[i]; a++){
			for( j=0; j<ne; j++){
				printf("P(%d,%d,%d) ? : %lf\n", i+1,a+1,j+1,Piaj[i][a][j]);
 				scanf("%f", &Piaj[i][a][j]);
 			}
		}
	}	
}


//Lecture de la politique iniale
void lire_politiqueA0(){

//strategie[0]=2;strategie[1]=1;strategie[2]=0;
    int i;	       
	for( i=0; i<ne; i++){
		printf(" donneer la strategie initial a l'etat (%d) :", i+1);
		scanf("%d", &strategie[i]);
		strategie[i]--;		
	}	
}
float P(x,y){
	int a;
	float s=0;
	for(a=0;a<na[x];a++){
		if(strategie[x]=a)
		s=s+Piaj[x][a][y]*1;
	}
	return s;
}
float R(x){
	int a;
	float s=0;
	for(a=0;a<na[x];a++){
		if(strategie[x]==a) s=s+1*Ria[x][a];
	}
	return s;
}
void I_alphaP(){
	int I[nmax][nmax],i,j;
	
	for(i=0;i<ne;i++){
		for(j=0;j<ne;j++){
			if(i==j) *(*(I+i)+j)=1;
			else I[i][j]=0;
		}
	}
	for(i=0;i<ne;i++){
		for(j=0;j<ne;j++){
			IP[i][j]=(I[i][j]-P(i,j));
		}
	}
	
}
void affiche_system(){
	float System[ne*3][ne*3+1];
	int i,j;
	
	for(i=0;i<ne*3;i++){
		for (j=0;j<ne*3+1;j++){
			System[i][j]=0;
		}
	}
	//calcule (I-alpha*P)
	I_alphaP();
	//ajuter (I-alpha*P)*J=0;
	for(i=0;i<ne;i++){
		for(j=0;j<ne;j++){
			System[i][j]=IP[i][j];
		}
	}
	//ajouter J+(I-alpha*P)*J=R
	for(i=ne;i<ne*2;i++){
		for(j=0;j<ne*2;j++){
			if(i-ne==j) System[i][j]=1;
			if(j>=ne) System[i][j]=IP[i-ne][j-ne];
		}
	}
	
	for (j=ne;j<ne*2;j++){
		System[j][ne*3]=R(j-ne);
	}
	//ajouter U+(I-alpha*P)*Z=0
	
	for(i=ne*2;i<ne*3;i++){
		for(j=ne;j<ne*3;j++){
//			printf("%d %d\n",i,j);
			if(i==j+ne) System[i][j]=1;
			if(j>=ne*2) System[i][j]=IP[i-ne*2][j-ne*2];
		}
	}
	//affiche le system 
	printf("resoudre le system suivant\n");
	for(i=0;i<ne*3;i++){
		for (j=0;j<ne*3;j++){
		printf("%lf ",System[i][j]);
		}
		printf("| %lf\n",System[i][ne*3]);
	}
	
}
void lireSolution(){
	int i;
	printf("entre les %d premiers solutions de system\n",ne*2);
	for(i=0;i<ne;i++){
		printf("X[%d]=",i+1);
		scanf("%f",&J[i]);	
		printf("%f\n",J[i]);
	}
	for(i=0;i<ne;i++){
		printf("X[%d]=",i+1+ne);
		scanf("%f",&U[i]);
		printf("%lf\n",U[i]);
	
	}
}
int findA() {
    int i,j,a,l;
    int ensembleVide;
    int optimale[ne][namax];

    float test1=0,test2=0;

   
    for (i = 0; i < ne; i++) {
    	printf("\nA(%d)\n",i+1);
        for (a = 0; a < na[i]; a++) {
        	test1=0,test2=0;
            for (j = 0; j < ne; j++) {
                test1 +=Piaj[i][a][j] * J[j];
            }

        if (test1 > J[i]){
        	        printf("a=%d\n",a+1);
					optimale[i][a] = 0;
		}
		
		else{
			 
        	if(test1 == J[i]){
        								                  

        		test2=Ria[i][a];
        		for(l=0;l<ne;l++){
        			test2=test2+Piaj[i][a][l] * U[l];
				}

				if(test2>J[i]+U[i]){
					printf("a=%d\n",a+1);
					optimale[i][a] = 0;
				}
				else optimale[i][a] = 1;
			}
        	else optimale[i][a] = 1;
		} 

        }
    }

    int notOptimale;

    notOptimale = 0;

    for (i = 0; i < ne; i++) {
        ensembleVide = 0;
        for (j = 0; j < na[i]; j++) {
            if (optimale[i][j]) ensembleVide = 1;
            else {
                ensembleVide = 0;
                notOptimale = 1;
                break;
            }
        }

        if (!ensembleVide) {
            for (a = 0; a < na[i]; ++a) {
                if (strategie[a] != strategie[i]) strategie[i] = strategie[a];
            }
        }
    }

    return notOptimale;
}

void policy_iteration_moyenne(){
	stop=1;
	while(stop){
		
	affiche_system();
	printf("\n");
	lireSolution();
	stop=findA();

	}

	
	
	
}
int main(){
	printf("entrer le nombre d'etats :");
	scanf("%d",&ne);

	
	printf("entrer le nombre d'actions par etat :\n");
	lire_nbr_actions();
	
	printf("entrer les recompenses :\n");
	lire_Ria();
	
	printf("entrer les probabilites de transition :\n");
	lire_Piaj();
	
	printf("entrer la politique initiale:\n");
	lire_politiqueA0();
	int i;
	policy_iteration_moyenne();
	for ( i=0; i<ne; i++){
    	printf("A(%d)=%d et PhOpt(%d)=%f--  ",i+1, strategie[i]+1, i+1, J[i]);
    }
}
