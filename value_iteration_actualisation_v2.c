#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Les variables globale

#define NUM_STATES 2 // nombre d'états dans le problème
#define NUM_ACTIONS 2 // nombre d'actions possibles dans chaque état
#define ALPHA 0.5 // facteur d'actualisation
#define EPSILON 0.1 // seuil de convergence

float V[NUM_STATES]; // Le vecteur gain optimal
int strategie[NUM_STATES]; // les stratégies



// définir les probabilités de transition et les récompenses pour chaque couple état-action
float T[NUM_STATES][NUM_ACTIONS][NUM_STATES] = {
        {{0.3333, 0.6666}, {0.5, 0.5}},
        {{0.25, 0.75}, {0, 1}}
};
float R[NUM_STATES][NUM_ACTIONS] = {{1, 0},
                                    {3, 2}
};


// fonction pour calculer la valeur de chaque état à l'aide de l'équation de Bellman
void valueIteration(float V[NUM_STATES], int policy[NUM_STATES])
{
    int i, j, a;
    float maxVal, newVal, newVoldV, temp;
    float oldV[NUM_STATES];

    do {
        for (i = 0; i < NUM_STATES; i++) {
            oldV[i] = V[i];
        }

        maxVal = -INFINITY;
        for (i = 0; i < NUM_STATES; i++) {
            for (a = 0; a < NUM_ACTIONS; a++) {
                newVal = R[i][a];
                for (j = 0; j < NUM_STATES; j++) {
                    newVal += ALPHA * T[i][a][j] * V[j];
                }
                if (newVal > maxVal) {
                    maxVal = newVal;
                    policy[i] = a;
                }
            }
            V[i] = maxVal;
            maxVal = -INFINITY;
        }

        newVoldV = -INFINITY;

        for (i = 0; i < NUM_STATES; i++) {
            temp = V[i] - oldV[i];
            if (temp < 0) temp = -temp;
            if (temp > newVoldV) newVoldV = temp;
        }

    } while (newVoldV > EPSILON);
}

int main()
{
    int i;

    // initialiser toutes les valeurs d'état à 0
    for (i = 0; i < NUM_STATES; i++) {
        V[i] = 0.0;
    }

    // initialiser toutes les stratégies à la première action
    for (i = 0; i < NUM_STATES; i++) {
        strategie[i] = 0;
    }

    valueIteration(V, strategie);

    printf("La stratégie optimale:\n");
    for (i = 0; i < NUM_STATES; i++) {
        printf("Etat : %d -- Action : %d\n", i, strategie[i]);
    }
    printf("\nLe vecteur gain optimal: \n");
    for (i = 0; i < NUM_STATES; i++) {
        printf("V[%d] = %.2f\n",i ,V[i]);
    }
// Affichage des valeurs des variables
printf("Les valeurs des variables sont :\n");
for (i = 0; i < n; i++) {
    printf("x%d = %f\n", i+1, x[i]);
}

// Lib�ration de la m�moire allou�e
free(x);
    return 0;
}
