# Architecture — Algorithmes MDP

## Objectif

Implémentations autonomes en **C** pour résoudre des problèmes de **processus de décision markovien (MDP)** : recherche d’une politique optimale ou d’une fonction valeur optimale.

## Structure logique

| Fichier / binaire | Rôle |
|-------------------|------|
| `policy_iteration_actualisation.c` → `policy_iteration` | Itération sur la politique (actualisation). |
| `value_iteration_actualisation.c` → `value_iteration` | Itération sur la valeur (saisie des probabilités `P` et récompenses `R`). |
| `value_iteration_actualisation_v2.c` → `value_iteration_v2` | Variante compacte (matrices `T`, `R` fixées dans le code). |

## Flux de données

```mermaid
flowchart LR
  stdin[Entrée stdin] --> init[Initialisation matrices]
  init --> loop[Boucle Bellman / convergence]
  loop --> out[Sortie console résultats]
```

## Contraintes de conception

- **Pas de dépendance externe** : uniquement la bibliothèque standard C et `-lm` pour les fonctions mathématiques.
- Chaque programme est **autonome** (pas de bibliothèque partagée entre les trois binaires) pour faciliter la compilation pédagogique.

## Compilation

Voir `Makefile` (cible `all`) et `README.md`.

## Évolutions possibles

- Factoriser les structures `P`/`R` dans un module `.h` commun si les trois variantes doivent partager des utilitaires.
- Ajouter des tests unitaires C (Criterion, Unity) ou des jeux de données fichiers pour automatiser la validation.
