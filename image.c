
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"
//------------------------------------------------------------------------------
// Code source pour du projet 
// description : (les fonctions sont définit dans image.h)
//
// les pointeurs images dans ce code sont de type : struct fichierimage *
//
// fonction struct fichierimage * charger(char *)
// permet de charger une image presente sur le disque en memoire vive, la fonction
// renvoie un pointeur de type : struct fichierimage *
//
// fonction int enregistrer(struct fichierimage *,char *)
// permet d'enregistrer une image sur le disque sous le nom donné en arg2, cette
// image est contenue dans une pointeur de type : struct fichierimage * fournit en arg1
//
// fonction struct fichierimage * nouveau(int,int)
// permet de creer une image en memoire de largeur arg1 et de hauteur arg2, la fonction
// retourne un pointeur de type : struct fichierimage *
//------------------------------------------------------------------------------
void NivGris(struct fichierimage* fichier) {
	int i, j, t = 0;
	char sauvegarder[50];
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	for (i = 0; i < hauteur; i++)
		for (j = 0; j < largeur; j++)
		{
			t = 0;
			t += fichier->image[i][j].r;
			t += fichier->image[i][j].g;
			t += fichier->image[i][j].b;
			t /= 3;
			fichier->image[i][j].r = t;
			fichier->image[i][j].g = t;
			fichier->image[i][j].b = t;
		}
	printf("Entrez  sauvegarde: \n");
	scanf(" %s", sauvegarder);
	enregistrer(sauvegarder, fichier);
	free(fichier);
}

void Miroirimage(struct fichierimage* fichier) {
	int i, j;
	char sauvegarder[50];
	struct fichierimage* fichier1 = nouveau(fichier->entetebmp.largeur, fichier->entetebmp.hauteur);
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	for (i = 0; i < hauteur; i++)
		for (j = 0; j < largeur; j++)
		{
			fichier1->image[i][j].r = fichier->image[i][(largeur - 1) - j].r;
			fichier1->image[i][j].g = fichier->image[i][(largeur - 1) - j].g;
			fichier1->image[i][j].b = fichier->image[i][(largeur - 1) - j].b;
		}
	printf("Entrez votre nom de sauvegarde: \n");
	scanf(" %s", sauvegarder);
	enregistrer(sauvegarder, fichier1);
	free(fichier);
	free(fichier1);
}

void Negatif(struct fichierimage* fichier)
{
	int i, j;
	char sauvegarder[50];
	struct fichierimage* fichier1 = nouveau(fichier->entetebmp.largeur, fichier->entetebmp.hauteur);
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	for (i = 0; i < hauteur; i++)
		for (j = 0; j < largeur; j++)
		{
			fichier1->image[i][j].r = 255 - fichier->image[i][j].r;
			fichier1->image[i][j].g = 255 - fichier->image[i][j].g;
			fichier1->image[i][j].b = 255 - fichier->image[i][j].b;

		}
	printf("Entrez votre nom de sauvegarde: \n");
	scanf(" %s", sauvegarder);
	enregistrer(sauvegarder, fichier1);
	free(fichier);
	free(fichier1);
}

void Pivot(struct fichierimage* fichier)
{
	int i, j, rot;
	printf("Entrez niveau de rotation \n");
	scanf("%d", &rot);
	char sauvegarder[50];
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier1 = NULL;
	while (rot != 0) {
		hauteur = fichier->entetebmp.hauteur;
		largeur = fichier->entetebmp.largeur;
		fichier1 = nouveau(fichier->entetebmp.hauteur, fichier->entetebmp.largeur);
		for (i = 0; i < hauteur; i++)
			for (j = 0; j < largeur; j++)
			{
				fichier1->image[j][hauteur - i - 1].r = fichier->image[i][j].r;
				fichier1->image[j][hauteur - i - 1].g = fichier->image[i][j].g;
				fichier1->image[j][hauteur - i - 1].b = fichier->image[i][j].b;
			}
		fichier = nouveau(fichier1->entetebmp.largeur, fichier1->entetebmp.hauteur);
		hauteur = fichier->entetebmp.hauteur;
		largeur = fichier->entetebmp.largeur;
		for (i = 0; i < hauteur; i++)
			for (j = 0; j < largeur; j++)
			{
				fichier->image[i][j].r = fichier1->image[i][j].r;
				fichier->image[i][j].g = fichier1->image[i][j].g;
				fichier->image[i][j].b = fichier1->image[i][j].b;
			}
		rot--;
	}
	printf("Entrez  sauvegarde: \n");
	scanf(" %s", sauvegarder);
	enregistrer(sauvegarder, fichier1);
	free(fichier1);
}

void Agrandir(struct fichierimage* fichier)
{
	int i, j, k, l, echelle;
	printf("Le degree d'agrandissement desire:\n");
	scanf("%d", &echelle);
	char sauvegarder[50];
	int div = 0;
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier1 = nouveau(largeur * echelle, hauteur * echelle);
	for (i = 1; i <= hauteur; i++)
		for (j = 1; j <= largeur; j++)
		{
			for (k = ((echelle * i) - echelle); k <= ((echelle * i) - 1); k++)
				for (l = ((echelle * j) - echelle); l <= ((echelle * j) - 1); l++)
				{
					fichier1->image[k][l].r = fichier->image[i - 1][j - 1].r;
					fichier1->image[k][l].g = fichier->image[i - 1][j - 1].g;
					fichier1->image[k][l].b = fichier->image[i - 1][j - 1].b;
				}
		}
	printf("Entrez votre nom de sauvegarde: \n");
	scanf(" %s", sauvegarder);
	enregistrer(sauvegarder, fichier1);
	free(fichier1);
	free(fichier);
}
void Reduire(struct fichierimage* fichier)
{
	int i, j, k = 0, l = 0, echelle;
	printf("Le degree de reduction desire:\n");
	scanf("%d", &echelle);
	char sauvegarder[50];
	int div = 0;
	int hauteur = fichier->entetebmp.hauteur;
	int largeur = fichier->entetebmp.largeur;
	struct fichierimage* fichier1 = nouveau(largeur / echelle, hauteur / echelle);
	for (i = 0; i <= hauteur; i += echelle) {
		for (j = 0; j <= largeur; j += echelle)
		{
			fichier1->image[i / echelle][j / echelle].r = fichier->image[i][j].r;
			fichier1->image[i / echelle][j / echelle].g = fichier->image[i][j].g;
			fichier1->image[i / echelle][j / echelle].b = fichier->image[i][j].b;
		}
	}

	printf("Entrez votre nom de sauvegarde: \n");
	scanf(" %s", sauvegarder);
	enregistrer(sauvegarder, fichier1);
	free(fichier1);
	free(fichier);
}

int main()
{
	//parcours image
	int i, j;

	//pointeur image
	struct fichierimage* fichier = NULL;

	char image[50];
	char Action[50];
	printf("Entrez  l'image:\n");
	scanf(" %s", image);
	int e = 0;
	int n1 = 0;
	int continuer = 1;
	int red;
	fichier = charger(image);
	while (continuer == 1) {
		printf("Que voulez vous faire?\na) Negatif\nb) Miroir \nc) Niveaux de Gris\nd)Reduire\ne)Agrandir\nf)Pivot\ng)Quitter\n");
		scanf(" %s", Action);
		if (strcmp(Action, "Miroir") == 0) {
			Miroirimage(fichier);
		}
		if (strcmp(Action, "Niveaux de Gris") == 0) {
			NivGris(fichier);
		}
		if (strcmp(Action, "Quitter") == 0) {
			continuer = 0;
		}
		if (strcmp(Action, "Negatif") == 0) {
			Negatif(fichier);
		}
		if (strcmp(Action, "Pivot") == 0) {
			Pivot(fichier);
		}
		if (strcmp(Action, "Agrandir") == 0) {
			Agrandir(fichier);
		}
		if (strcmp(Action, "Reduire") == 0) {
			Reduire(fichier);
		}
		printf("Entrez le nom de l'image a traiter: \n");
		scanf(" %s", image);
		fichier = charger(image);
	}


}
