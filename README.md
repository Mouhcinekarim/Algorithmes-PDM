# Algorithmes MDP — politique et valeur optimales

Schéma d’architecture logicielle : **`ARCHITECTURE.md`**.

Implémentations en C pour la **planification** (policy iteration, value iteration) sur des processus de décision markoviens.

## Prérequis

- Compilateur C (GCC ou Clang)
- `make` (optionnel)

## Compiler

```bash
make
```

Ou manuellement :

```bash
gcc -std=c11 -Wall -Wextra -O2 -o policy_iteration policy_iteration_actualisation.c -lm
gcc -std=c11 -Wall -Wextra -O2 -o value_iteration value_iteration_actualisation.c -lm
gcc -std=c11 -Wall -Wextra -O2 -o value_iteration_v2 value_iteration_actualisation_v2.c -lm
```

## Exécuter

- `./policy_iteration` — itération sur la politique (saisie interactive des paramètres selon le programme).
- `./value_iteration` — itération sur la valeur (matrices de transition et récompenses saisies au clavier).
- `./value_iteration_v2` — exemple à petit nombre d’états avec données codées en dur.

## Nettoyer

```bash
make clean
```
