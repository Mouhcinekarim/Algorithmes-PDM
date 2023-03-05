#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define N_STATES 10 // Nombre d'états
#define N_ACTIONS 2 // Nombre d'actions
#define EPSILON 0.01 // Seuil de convergence
#define ALPHA 0.1 // Facteur d'apprentissage
#define GAMMA 1.0 // Facteur d'actualisation
#define MAX 100

double P[MAX][MAX][MAX];
double R[MAX][MAX];
// Fonction pour initialiser les valeurs de chaque état
void init_values(double *values) {
	int i,a,j;
    for (i = 0; i < N_STATES; i++) {
        values[i] = 0.0;
    }
    
    for (i=0;i<N_STATES;i++){
    	for(a=0 ;a<N_ACTIONS;a++){
    		for(j=0;j<N_STATES;j++){
    			printf("donner la prob de etat %d a etat %d et faire action %d\n",i+1,j+1,a+1);
    			scanf("%lf",P[i,a,j]);
			}
		}
	}
	
	for(i=0;i<N_STATES;i++){
		for(a=0;a<N_ACTIONS;a++){
			printf("donner le recomposion de etat %d et l'action %d \n",i,a);
			scanf("%lf",R[i][a]);
		}
	}
}


  
  
  

// Fonction pour choisir l'action maximisant la valeur d'un état
//int max_action(double *values, int state) {
//	int a;
//    int action = 0;
//    double max_value = -INFINITY;
//    for (a = 0; a < N_ACTIONS; a++) {
//        double value = R(state, a) + GAMMA * P(state, a, 1) * values[1];
//        if (value > max_value) {
//            max_value = value;
//            action = a;
//        }
//    }
//    return action;
//}

// Fonction principale d'itération de la valeur
void value_iteration(double *values, int *policy) {
    double old_values[N_STATES];
    int i,a,j;
    bool converged = false;
    int n = 0;
    
    while (!converged) {
        n++;
        // Sauvegarder les anciennes valeurs
        for ( i = 0; i < N_STATES; i++) {
            old_values[i] = values[i];
        }
        
        // Mettre à jour les valeurs de chaque état
        for (i = 0; i < N_STATES; i++) {
            double max_value = -INFINITY;
            int action = 0;
            for (a = 0; a < N_ACTIONS; a++) {
               
                double somme=0;
                for (j=0;j<N_STATES;j++){
                	somme+=old_values[j]*P[i][a][j];
				}
				 double value = R[i][a] + ALPHA * somme;
                if (value > max_value) {
                    max_value = value;
                    action=a;
                }
            }
            values[i] = max_value;
            policy[i]=action;
        }
        
        // Mettre à jour la politique optimale
//        for (i = 0; i < N_STATES; i++) {
//            policy[i] = max_action(values, i);
//        }
        
        // Tester la convergence
        double max_diff = 0.0;
        for (i = 0; i < N_STATES; i++) {
            double diff = fabs(values[i] - old_values[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
        if (max_diff < EPSILON) {
            converged = true;
        }
    }
    
    printf("Nombre d'itérations : %d\n", n);
}

int main() {
	int i;
    double values[N_STATES];
    
    int policy[N_STATES];
    init_values(values);
    value_iteration(values, policy);
    
    // Afficher la politique optimale et les valeurs de chaque état
    printf("Politique optimale :\n");
    for (i = 0; i < N_STATES; i++) {
        printf("Etat %d : action %d\n", i, policy[i]);
    }
}
