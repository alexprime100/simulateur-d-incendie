#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct _cellule
{
    int type;    //de nombreux problemes ont ete rencontres avec le type char (voir rapport)
    int degre;
    int etat;
};
typedef struct _cellule cellule;

struct _matrice
{
	int longueur;
	int largeur;
	cellule** contenu;
}; // ne pas oublier le ; ici

typedef  struct _matrice  matrice;

int generation_alea_int(int valeur_max)
{
    int alea = 0;

    do
    {
        alea = 1 + rand()/(RAND_MAX/valeur_max);
    }
    while(alea > valeur_max);

    return alea;
}

matrice* creation_foret(int longueur, int largeur);

cellule* choix_alea(cellule* case_foret);

matrice* remplissage_aleatoire_foret(matrice* foret, int longueur, int largeur);

matrice* remplissage_manuel_foret(matrice* foret, int longueur, int largeur);

matrice* initialise_feu(matrice* foret, int longueur, int largeur);

matrice* initialise_feu_manuel(matrice* foret, int longueur, int largeur);

matrice* liberation_foret(matrice* foret, int longueur, int largeur);

void afficher_foret(matrice* foret, int longeur, int largeur);

int nb_voisins_feu(matrice* foret, int longueur, int largeur, int indl, int indc);

matrice* tour_suivant(matrice* foret, int longueur, int largeur, int tour);

matrice* modification_case(matrice* foret, int longueur, int largeur);

int modulo(int entier1, int entier2);

int stabilite(matrice* foret, matrice* foret_temp, int longueur, int largeur);

void simulation();


int main()
{
    srand(time(NULL));
    simulation();
}

matrice* creation_foret(int longueur, int largeur)
{
    //cette fonction crée une foret sous forme de matrice de cellule (structure definie plus haut), et la stocke en memoire.
	matrice* foret = (matrice*) malloc(sizeof(matrice));
	foret->longueur = longueur;
	foret->largeur = largeur;
	foret->contenu = (cellule**) malloc(longueur * sizeof(cellule*));
	for (int i = 0; i < longueur; i++)
    {
        foret->contenu[i] = (cellule*) malloc(largeur * sizeof(cellule));
    }
	return foret;
}

cellule* choix_alea(cellule* case_foret)
{
    //cette fonction permet de generer une cellule dont le type est choisi aleatoirement.
    const int valeur_max = 6;
    int a = generation_alea_int(valeur_max); //la première execution de cette fonction renvoie toujours le même nombre, et ensuite elle fonctionne normalement.

    a = generation_alea_int(valeur_max);
    case_foret->type = a;

    case_foret->etat = 0;
    //chaque type possede un degre initial predefini qui est affecte automatiquement

    if (case_foret->type == 1)   //herbe
    {
        case_foret->degre = 3;
    }

    if (case_foret->type == 2)    //arbre
    {
        case_foret->degre = 4;//
    }

    if (case_foret->type == 3)    //terrain
    {
        case_foret->degre = 0;
    }

    if (case_foret->type == 4)    //feuille
    {
        case_foret->degre = 2;
    }

    if (case_foret->type == 5)    //eau
    {
        case_foret->degre = 0;
    }

    if (case_foret->type == 6)    //rocher
    {
        case_foret->degre = 5;
    }
    return case_foret;
}

matrice* remplissage_aleatoire_foret(matrice* foret, int longueur, int largeur)
{
    //cette fonction remplit une matrice aleatoirement

    //on parcourt chaque case de la foret
    for (int ligne = 0; ligne < longueur; ligne++)
    {
        for (int colonne = 0; colonne < largeur; colonne++)
        {
             cellule* case_foret;
            generation_alea_int(6); //la première execution de cette fonction renvoie toujours le même nombre, et ensuite elle fonctionne normalement.
            int a = generation_alea_int(6);
            case_foret->type = a ;
            case_foret->etat = 0;

            if (case_foret->type == 1)   //herbe.
            {
                case_foret->degre = 3;
            }

            if (case_foret->type == 2)    //arbre
            {
                case_foret->degre = 4;//
            }

            if (case_foret->type == 3)    //terrain
            {
                case_foret->degre = 0;
            }

            if (case_foret->type == 4)    //feuille
            {
                case_foret->degre = 2;
            }

            if (case_foret->type == 5)    //eau
            {
                case_foret->degre = 0;
            }

            if (case_foret->type == 6)    //rocher
            {
                case_foret->degre = 5;
            }
            foret->contenu[ligne][colonne].type = case_foret->type;
            foret->contenu[ligne][colonne].degre = case_foret->degre;
            foret->contenu[ligne][colonne].etat = case_foret->etat;
        }
    }
    return foret;
}

matrice* remplissage_manuel_foret(matrice* foret, int longueur, int largeur)
{
    //cette fonction permet de remplir une matrice manuellement

    //on parcourt chaque case de la matrice
    for (int ligne = 0; ligne < longueur; ligne++)
    {
        for (int colonne = 0; colonne < largeur; colonne++)
        {
            printf("saisissez le type de la case \n");
            printf("saisissez 1 pour une case d'herbe\n");
            printf("2 pour un arbre\n");
            printf("3 pour un terrain\n");
            printf("4 pour une feuille\n");
            printf("5 pour de l'eau\n");
            printf("6 pour un rocher\n");
            int type;
            scanf("%d", &type);

            while (type < 1 || type > 6)       //le numero saisi doit obligatoirement etre un entier compris entre 1 et 6
            {
                printf("le type doit etre compris entre 1 et 8, ressaisissez-le\n");
                scanf("%d", &type);
            }

            foret->contenu[ligne][colonne].type = type;
            foret->contenu[ligne][colonne].etat = 0;

            if (type == 1)   //herbe
            {
                foret->contenu[ligne][colonne].degre = 3;
            }

            if (type == 2)    //arbre
            {
                foret->contenu[ligne][colonne].degre = 4;
            }

            if (type == 3)    //terrain
            {
                foret->contenu[ligne][colonne].degre = 0;
            }

            if (type == 4)    //feuille
            {
                foret->contenu[ligne][colonne].degre = 2;
            }

            if (type == 5)    //eau
            {
                foret->contenu[ligne][colonne].degre = 0;
            }

            if (type == 6)    //rocher
            {
                foret->contenu[ligne][colonne].degre = 5;
            }
        }
    }
    return foret;
}

matrice* initialise_feu(matrice* foret, int longueur, int largeur)
{
    //cette fonction permet d'initialiser l'incendie

    //choix aleatoire de la cellule d'origine de l'incendie
    int ligne = generation_alea_int(longueur - 1);
    ligne = generation_alea_int(longueur - 1);
    int colonne = generation_alea_int(largeur - 1);

    while (foret->contenu[ligne][colonne].type == 3 || foret->contenu[ligne][colonne].type == 5 )   //tant que la cellule est un terrain, ou de l'eau, on initialise à nouveau l'incendie
    {
        ligne = generation_alea_int(longueur - 1);
        colonne = generation_alea_int(largeur - 1);
    }
    foret->contenu[ligne][colonne].etat = 1;
    return foret;
}

void afficher_foret(matrice* foret, int longeur, int largeur)
{
    //cette fonction affiche la foret dans ses formes
    //l'ordre d'affichage est le suivant : type, etat, degre
    for (int ligne = 0; ligne < longeur; ligne++)
    {
        for (int colonne = 0; colonne < largeur; colonne++)    //affichage des types de la ligne i
        {
            printf("%d ", foret->contenu[ligne][colonne].type);
        }
        printf("           ");
        for (int colonne = 0; colonne < largeur; colonne++)    //affichage des etats de la ligne i
        {
            printf("%d ", foret->contenu[ligne][colonne].etat);
        }
        printf("           ");
        for (int colonne = 0; colonne < largeur; colonne++)   //affichage des degres de la ligne i
        {
            printf("%d ", foret->contenu[ligne][colonne].degre);
        }
        printf("\n");
    }
    printf("\n");
}

int nb_voisins_feu(matrice* foret, int longueur, int largeur, int indl, int indc)
{   //cette fonction permet de compter le nombre de voisins en feu d'une case donnee
    //le modele de matrice circulaire est adoptee, donc chaque case possede toujours 8 voisins
    int compteur = 0;
    int ligne = 0;
    int colonne = 0;

    for (ligne = indl - 1; ligne <= indl + 1; ligne++)
    {
        for (colonne = indc - 1; colonne <= indc + 1; colonne++)
        {
            if (foret->contenu[modulo(ligne,longueur)][modulo(colonne,largeur)].etat == 1)   //l'utilisation du modulo permet de gerer une matrice circulaire
            {
                compteur++;
            }
        }
    }

    if (foret->contenu[indl][indc].etat == 1)   //la cellule [indl, indc] a ete incluse dans le comptage, donc si elle est en feu, il faut l'exclure en diminuant de 1 la valeur finale du comptage
    {
         compteur--;
    }
    return compteur;
}

matrice* liberation_foret(matrice* foret, int longueur, int largeur)
{
    //cette fonction permet de libérer la mémoire utilisée pour stocker la matrice
    for (int i = 0; i < longueur; i++)
    {
        free(foret->contenu[i]);   //on libère d'abord la memoire utilisee par chaque ligne
    }
    free(foret);   //enfin on libere l'espace de la matrice
    return foret;
}

matrice* tour_suivant(matrice* foret, int longueur, int largeur, int tour)
{
    //cette fonction permet d'enregistrer toutes les modifications de la foret dans une matrice temporaire pour pouvoir passer au tour suivant
    //creation de la matrice temporaire dans laquelle les modifications seront enregistrees
    matrice* foret_temp = creation_foret(longueur, largeur);
    int voisins_feu;

    for (int ligne = 0; ligne < longueur; ligne++)
    {
        for (int colonne = 0; colonne < largeur; colonne++)
        {
            //on parcourt chaque case de la foret et on applique les 5 regles
            voisins_feu = nb_voisins_feu(foret, longueur, largeur, ligne, colonne);

            if (foret->contenu[ligne][colonne].etat == 1 && (foret->contenu[ligne][colonne].degre == 2 || foret->contenu[ligne][colonne].degre == 1))    //si la case est en feu et de degre 1 ou 2. la regle a du etre modifie (la raison est expliquee dans le rapport)
            {
                foret_temp->contenu[ligne][colonne].type = 7;   //la case se transforme en cendre
                foret_temp->contenu[ligne][colonne].degre = 1;   //le degré est donc à 1
                foret_temp->contenu[ligne][colonne].etat = 1;    //la case reste en feu
            }

            if (foret->contenu[ligne][colonne].type == 7)    //si la case est en cendres
            {
                foret_temp->contenu[ligne][colonne].type = 8;   //la case devient une cendre eteinte
                foret_temp->contenu[ligne][colonne].degre = 0;   //le degré est donc nul
                foret_temp->contenu[ligne][colonne].etat = 1;    //la case reste en feu
            }

            if ((foret->contenu[ligne][colonne].type == 1 || foret->contenu[ligne][colonne].type == 2 || foret->contenu[ligne][colonne].type == 4 || foret->contenu[ligne][colonne].type == 6) && voisins_feu >= 1 && foret->contenu[ligne][colonne].etat == 0)
            {   //si la case est herbe, ou arbre, ou une feuille ou rocher, et a au moins un voisin en feu, et n'est pas en feu
                foret_temp->contenu[ligne][colonne].etat = 1;                                             //la case prend feu
                foret_temp->contenu[ligne][colonne].degre = foret->contenu[ligne][colonne].degre - 1;     //et son degre diminue de 1
                foret_temp->contenu[ligne][colonne].type = foret->contenu[ligne][colonne].type;           //son type est inchangé
            }

            if (foret->contenu[ligne][colonne].etat == 1  && foret->contenu[ligne][colonne].degre > 2)
            {   //si la case est en feu et de degre superieur a 2
                foret_temp->contenu[ligne][colonne].degre = foret->contenu[ligne][colonne].degre - 1;   //le degre diminue
                foret_temp->contenu[ligne][colonne].type = foret->contenu[ligne][colonne].type;         //le type est inchangé
                foret_temp->contenu[ligne][colonne].etat = 1;                                           //la case reste en feu
            }

            if (foret->contenu[ligne][colonne].type == 3 || foret->contenu[ligne][colonne].type == 5)
            {   //si la case possède de l'eau ou un terrain, rien ne change
                foret_temp->contenu[ligne][colonne].type = foret->contenu[ligne][colonne].type;
                foret_temp->contenu[ligne][colonne].etat = 0;
                foret_temp->contenu[ligne][colonne].degre = 0;
            }

            if (voisins_feu == 0 && foret->contenu[ligne][colonne].etat == 0)   //si la case n'est pas en feu, et n'a pas de voisins en feu, rien ne change
            {
                foret_temp->contenu[ligne][colonne].etat = 0;
                foret_temp->contenu[ligne][colonne].type = foret->contenu[ligne][colonne].type;
                foret_temp->contenu[ligne][colonne].degre = foret->contenu[ligne][colonne].degre;
            }

            if (foret->contenu[ligne][colonne].type == 8)    //si la case est en cendres eteintes, rien ne change
            {
                foret_temp->contenu[ligne][colonne].etat = 1;
                foret_temp->contenu[ligne][colonne].type = 8;
                foret_temp->contenu[ligne][colonne].degre = 0;
            }
        }
    }
    printf("tour %d\n",tour);
    return foret_temp;
}

matrice* initialise_feu_manuel(matrice* foret, int longueur, int largeur)
{
    //cette fonction permet d'initialiser manuellement l'incendie
    //si les indices saisis ne sont incompatibles avec les dimensions de la matrice, ou qu'ils correspondent a une case d'eau ou de terrain, le programme demande a l'utilisateur de ressaisir les indices
    printf("saisissez l'indice de la ligne puis de la colonne de la case ou vous souhaitez initialiser l'incendie\n");
    int ligne;
    int colonne;
    scanf("%d", &ligne);
    scanf("%d", &colonne);
    int indices_valides;
    if (ligne < 0 || ligne >= longueur || colonne < 0 || colonne >= largeur)   //si les indices sont trop grands ou trop petits
    {
        indices_valides = 0;    //la saisie sera redemandee
    }
    else
    {
        if (foret->contenu[ligne][colonne].type == 3 || foret->contenu[ligne][colonne].type == 5) //si les indices ont la bonne taille mais correpondent a une case d'eau ou de terrain
        {
            indices_valides = 0;    //la saisie sera redemandee
        }
        else
        {
            indices_valides = 1;    //sinon le programme continue
        }
    }

    while (indices_valides == 0)  //la ressaisie est demandee
    {
        printf("l'indice ligne doit etre compris entre 0 et %d\n",longueur-1);
        printf("l'indice colonne doit etre compris entre 0 et %d\n",largeur-1);
        printf("vous ne pouvez pas initialiser un incendie sur une case d'eau ou de terrain\n");
        scanf("%d", &ligne);
        scanf("%d", &colonne);
        if (ligne >= 0 && ligne < longueur && colonne >= 0 && colonne < largeur)
        {
            if (foret->contenu[ligne][colonne].type != 3 && foret->contenu[ligne][colonne].type != 5)
            {
                indices_valides = 1;
            }
        }
    }
    foret->contenu[ligne][colonne].etat = 1;

    return foret;
}

matrice* modification_case(matrice* foret, int longueur, int largeur)
{
    //cette fonction permet a l'utilisateur de modifier n'importe quelle case de la foret entre 2 tours
    //l'utilisateur commence par choisir la case a modifier
    printf("saisissez l'indice de la ligne puis de la colonne de la case a modifier\n");
    int indl;
    int indc;
    scanf("%d", &indl);
    while (indl < 0 || indl >= longueur)
    {
        printf("indice ligne invalide, ressaisissez-le\n");
        scanf("%d", &indl);
    }

    scanf("%d", &indc);
    while (indc < 0 || indc >= largeur)
    {
        printf("indice colonne invalide, ressaisissez-le\n");
        scanf("%d", &indc);
    }
    //il faut maintenant choisir le nouveau type de la case
    printf("saisissez le nouveau type de la case\n");
    printf("saisissez 1 pour une case d'herbe\n");
    printf("2 pour un arbre\n");
    printf("3 pour un terrain\n");
    printf("4 pour une feuille\n");
    printf("5 pour de l'eau\n");
    printf("6 pour un rocher\n");
    printf("7 pour des cendres\n");
    printf("8 pour des cendres eteintes\n");

    int type;
    scanf("%d", &type);

    while (type < 1 || type > 8)
    {
        printf("le type doit etre compris entre 1 et 8, ressaisissez-le\n");
        scanf("%d", &type);
    }
    foret->contenu[indl][indc].type = type;
    //pour les cendres (eteintes ou non), les terrains et l'eau, le degre et l'etat sont modifies automatiquement
    if (type == 7)
    {
        foret->contenu[indl][indc].degre = 1;
        foret->contenu[indl][indc].etat = 1;
    }

    if (type == 3 || type == 5 || type == 8)
    {
        foret->contenu[indl][indc].degre = 0;
        foret->contenu[indl][indc].etat = 0;
    }
    else   //sinon l'utilisateur a le choix de les modifier ou pas
    {
        printf("souhaitez-vous modifier le degre de la case ? repondez 1 pour modifier la case, ou un autre chiffre pour continuer\n");
        int reponse;
        scanf("%d", &reponse);

        if (reponse == 1)
        {
            printf("entrez le nouveau degre\n");
            int degre;
            scanf("%d", &degre);
            foret->contenu[indl][indc].degre = degre;
        }

        printf("souhaitez-vous modifier l'etat de la case ? repondez 1 pour modifier la case, ou un autre chiffre pour continuer\n");
        int reponse2;
        scanf("%d", &reponse2);

        if (reponse2 == 1)
        {
            printf("entrez le nouveau etat\n");
            int etat;
            scanf("%d", &etat);
            foret->contenu[indl][indc].etat = etat;
        }
    }
    return foret;
}

int modulo(int entier1, int entier2)
{
    //cette fonction permet de calculer le modulo mathematique (qui est toujours positif). plus d'informations dans le rapport
    if (entier1 % entier2 >= 0)
    {
        return entier1 % entier2;
    }
    else
    {
        return entier2 + (entier1 % entier2);
    }
}

int stabilite(matrice* foret, matrice* foret_temp, int longueur, int largeur)
{
    //cette fonction permet de detecter un etat stable
    //si toutes les cases de la foret restent identiques entre 2 tours, alors l'incendie ne se propage plus, sinon il continue
    for (int ligne = 0; ligne < longueur; ligne++)
    {
        for (int colonne = 0; colonne < largeur; colonne++)
        {
            if (foret->contenu[ligne][colonne].type != foret_temp->contenu[ligne][colonne].type || foret->contenu[ligne][colonne].etat != foret_temp->contenu[ligne][colonne].etat || foret->contenu[ligne][colonne].degre != foret_temp->contenu[ligne][colonne].degre)
            {
                return 0;
            }
        }
    }
    return 1;
}

void simulation()
{
    //il s'agit du programme qui execute le simulateur d'incendie
    printf("saisissez la longueur puis la largeur de la foret en nombre de cases\n");
    int longueur;
    int largeur;
    scanf("%d", &longueur);
    scanf("%d", &largeur);

    //création de la foret en memoire
    matrice* foret = creation_foret(longueur, largeur);
    matrice* foret_temp;

    //remplissage de la foret en memoire, et choix d'un remplissage aléatoire ou manuel
    printf("souhaitez-vous remplir la matrice de facon aleatoire ou manuelle ? repondez 1 pour un remplissage aleatoire, ou un autre chiffre pour un remplissage manuel\n");

    int generation_aleatoire;
    scanf("%d", &generation_aleatoire);

    if (generation_aleatoire == 1)
    {
        printf("la foret va etre remplie aleatoirement\n");
        foret = remplissage_aleatoire_foret(foret, longueur, largeur);
    }

    else
    {
        foret = remplissage_manuel_foret(foret, longueur, largeur);
    }

    //initialisation aléatoire ou manuelle de l'incendie
    printf("souhaitez-vous initialiser l'incendie de maniere aleatoire ou manuelle ? repondez 1 pour une initialisation aleatoire, ou un autre chiffre pour une initialisation manuelle\n");
    int initialisation_aleatoire_incendie;
    scanf("%d", &initialisation_aleatoire_incendie);

    if (initialisation_aleatoire_incendie == 1)
    {
        foret = initialise_feu(foret, longueur, largeur);
    }

    else
    {
        foret = initialise_feu_manuel(foret, longueur, largeur);
    }
    //affichage de la foret a partir du debut de l'incendie
    afficher_foret(foret, longueur, largeur);

    //choix du nombre de tours
    printf("combien d'autres tours voulez-vous afficher ?\n");
    int nb_tours;
    scanf("%d", &nb_tours);
    int tour = 2;

    //execution de la propagation de l'incendie
    while (nb_tours > 0 )
    {
        //passage au tour suivant
        printf("souhaitez-vous modifier manuellement une case ? repondez 1 pour modifier une case ou un autre chiffre pour continuer\n");
        int reponse;
        scanf("%d", &reponse);

        if (reponse == 1)
        {
            foret = modification_case(foret, longueur, largeur);
        }

        //creation d'une foret temporaire
        foret_temp = creation_foret(longueur, largeur);

        //enregistrement des informations du tour suivant dans la foret temporaire
        foret_temp = tour_suivant(foret, longueur, largeur, tour);

        //detection ou non d'un etat stable
        if (stabilite(foret, foret_temp, longueur, largeur) == 0)  //si l'incendie continue de se propager
        {
            //on recree la matrice foret
            foret = liberation_foret(foret, longueur, largeur);

            foret = creation_foret(longueur, largeur);

            for (int ligne = 0; ligne < longueur; ligne++)
            {
                for (int colonne = 0; colonne < largeur; colonne++)
                {
                    foret->contenu[ligne][colonne].type = foret_temp->contenu[ligne][colonne].type;
                    foret->contenu[ligne][colonne].etat = foret_temp->contenu[ligne][colonne].etat;
                    foret->contenu[ligne][colonne].degre = foret_temp->contenu[ligne][colonne].degre;
                }
            }
            afficher_foret(foret, longueur, largeur);
            //on actualise le numero du tour, ainsi que le nombre de tours restants
            nb_tours--;
            tour++;
        }
        else  //si l'incendie ne se propage plus, le programme s'arrete
        {
            printf("l'incendie ne se propage plus");
            nb_tours = 0;
        }
    }
}






