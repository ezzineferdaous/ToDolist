#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter une tâche
typedef struct Tache {
    char nom[100];
    char description[100];
    int priorite;
    int terminee;
} Tache;

// Fonction pour ajouter une tâche
void ajouterTache(Tache **taches, int *nb_taches) {
    (*nb_taches)++;
    *taches = (Tache *)realloc(*taches, (*nb_taches) * sizeof(Tache));
    if (*taches == NULL) {
        printf("Erreur : échec d'allocation mémoire !\n");
        exit(1);
    }

    Tache nouvelle_tache;
    printf("Entrez le nom de la tâche : ");
    scanf("%s", nouvelle_tache.nom);
    printf("Entrez la description de la tâche : ");
    scanf("%s", nouvelle_tache.description);
    printf("Entrez la priorité de la tâche (1-5) : ");
    scanf("%d", &nouvelle_tache.priorite);
    nouvelle_tache.terminee = 0;

    (*taches)[*nb_taches - 1] = nouvelle_tache;

    printf("Tâche ajoutée avec succès !\n");
}

// Fonction pour mettre à jour une tâche
void modifierTache(Tache *taches, int nb_taches) {
    int index;
    printf("Entrez l'indice de la tâche à mettre à jour : ");
    scanf("%d", &index);

    if (index < 1 || index > nb_taches) {
        printf("Erreur : indice de tâche invalide !\n");
        return;
    }

    Tache *tache = &taches[index - 1];
    printf("Entrez le nouveau nom de la tâche : ");
    scanf("%s", tache->nom);
    printf("Entrez la nouvelle description de la tâche : ");
    scanf("%s", tache->description);
    printf("Entrez la nouvelle priorité de la tâche (1-5) : ");
    scanf("%d", &tache->priorite);

    printf("Tâche mise à jour avec succès !\n");
}

// Fonction pour supprimer une tâche
void supprimerTache(Tache **taches, int *nb_taches) {
    int index;
    printf("Entrez l'indice de la tâche à supprimer : ");
    scanf("%d", &index);

    if (index < 1 || index > *nb_taches) {
        printf("Erreur : indice de tâche invalide !\n");
        return;
    }

    for (int i = index - 1; i < *nb_taches - 1; i++) {
        (*taches)[i] = (*taches)[i + 1];
    }

    (*nb_taches)--;
    *taches = (Tache *)realloc(*taches, (*nb_taches) * sizeof(Tache));

    printf("Tâche supprimée avec succès !\n");
}

// Fonction pour marquer une tâche comme terminée
void marquerTacheCommeTerminee(Tache *taches, int nb_taches) {
    int index;
    printf("Entrez l'indice de la tâche à marquer comme terminée : ");
    scanf("%d", &index);

    if (index < 1 || index > nb_taches) {
        printf("Erreur : indice de tâche invalide !\n");
        return;
    }

    taches[index - 1].terminee = 1;

    printf("Tâche marquée comme terminée !\n");
}

// Fonction pour filtrer les tâches par priorité
void filtrerTachesParPriorite(Tache *taches, int nb_taches, int priorite) {
    printf("Tâches avec priorité %d :\n", priorite);
    for (int i = 0; i < nb_taches; i++) {
        if (taches[i].priorite == priorite) {
            printf("Nom : %s, Description : %s, Priorité : %d\n", taches[i].nom, taches[i].description, taches[i].priorite);
        }
    }
}

// Fonction pour afficher toutes les tâches
void afficherTaches(Tache *taches, int nb_taches) {
    printf("Toutes les tâches :\n");
    for (int i = 0; i < nb_taches; i++) {
        printf("Indice : %d, Nom : %s, Description : %s, Priorité : %d, Terminée : %s\n", i + 1, taches[i].nom, taches[i].description, taches[i].priorite, taches[i].terminee ? "Oui" : "Non");
    }
}

int main() {
    Tache *taches = NULL;
    int nb_taches = 0;
    int choix;

    do {
        printf("\n=== Liste de tâches ===\n");
        printf("1. Ajouter une tâche\n");
        printf("2. Modifier une tâche\n");
        printf("3. Supprimer une tâche\n");
        printf("4. Marquer une tâche comme terminée\n");
        printf("5. Filtrer les tâches par priorité\n");
        printf("6. Afficher toutes les tâches\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterTache(&taches, &nb_taches);
                break;
            case 2:
                modifierTache(taches, nb_taches);
                break;
            case 3:
                supprimerTache(&taches, &nb_taches);
                break;
            case 4:
                marquerTacheCommeTerminee(taches, nb_taches);
                break;
            case 5:
                {
                    int priorite;
                    printf("Entrez la priorité à filtrer : ");
                    scanf("%d", &priorite);
                    filtrerTachesParPriorite(taches, nb_taches, priorite);
                }
                break;
            case 6:
                afficherTaches(taches, nb_taches);
                break;
            case 7:
                printf("Fermeture...\n");
                break;
            default:
                printf("Choix invalide ! Veuillez entrer un nombre entre 1 et 7.\n");
        }
    } while (choix != 7);

    // Libération de la mémoire allouée
    free(taches);

    return 0;
}
