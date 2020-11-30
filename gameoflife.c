#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define HEIGHT 50
#define WIDTH 50

char grid[HEIGHT][WIDTH];

int init_Game(void){
	int choix;
	printf("1 - ### \n");
	printf("2 - U en # \n");
	
	do{
		printf("Entre ton choix : ");
		scanf("%d", &choix);

	}while (choix < 0 || choix > 3);
	return choix;
}
int loadGame(int motif){
	
	int heightmiddle = HEIGHT / 2; /* milieu de la hauteur */
	int widthmiddle = WIDTH / 2;	/* milieu de la largeur */

	for (int i = 0; i < HEIGHT; ++i){
		for (int j = 0; j < WIDTH; ++j)
		{
			grid[i][j] = ' ';
		}
	}
	switch(motif){
	

	
	case 1:
		grid[heightmiddle][widthmiddle + 0] = '#'; /* widthmiddle permet de pas mettre le # sur la meme case */
		grid[heightmiddle][widthmiddle + 1] = '#';
		grid[heightmiddle][widthmiddle + 2] = '#';
		break;
	case 2:
		grid[heightmiddle][widthmiddle + 0] = '#';
		grid[heightmiddle][widthmiddle + 2] = '#';
		grid[heightmiddle + 1][widthmiddle + 0] = '#';
		grid[heightmiddle + 1][widthmiddle + 2] = '#';
		grid[heightmiddle + 2][widthmiddle + 0] = '#';
		grid[heightmiddle + 2][widthmiddle + 1] = '#';
		grid[heightmiddle + 2][widthmiddle + 2] = '#';
		break;
	

	default:
		printf("Motif invalide: %d\n", motif); 
		return 1;	
	}
	return 0;
}

void drawGame(){
	printf("┌"); /* En haut a gauche du tableau */
	for (int i = 0; i < WIDTH; i++){ /* faire toute la largeur du tableau */
		printf("─"); 
	} 
	printf("┐\n"); /* En haut a droite du tableau */
	for (int i = 0; i < HEIGHT; i++)
	{
		printf("│");
		for (int j = 0; j < WIDTH; j++){ /* permet de se decaller a droite pour possitionner la ligne de la case */ 
			printf("%c", grid[i][j]); /*afficher les caractere du tableau*/
		}
		printf("│\n");
	}
	printf("└"); /* En haut a gauche du tableau */
	
	for (int i = 0; i < WIDTH; i++){ /* meme usage que le premier for mais pour le bas du tableau */
		printf("─"); 
	} 
	printf("┘\n");

}

int IsInRange(int ligne, int colonne){
	
	if (ligne >= 0 && colonne >= 0 && ligne < HEIGHT && colonne < WIDTH){ /* condition permettant de savoir si la case appartient a la grille */
		return 1;
	}
	else{
		return 0;
	}
} 



int NbCasesAdj (int ligne, int colonne){
	int total_case_adjacente = 0;
	for (int i = 0; i <= 2; i++){
		for (int j = 0; j <= 2; j++){
			if ((i != 1 || j != 1) && IsInRange(ligne + (i-1), colonne + (j-1))){
				if (grid[ligne + (i-1)][colonne + (j-1)] == '#'){
					total_case_adjacente ++;
				}
				
			}
		}
	} 

	return total_case_adjacente;
}

void UpdateGame(){
	char grilletemp[HEIGHT][WIDTH];
	int nb_case_adjacente;
	for (int i = 0; i < HEIGHT; i++){ /* check toute la colonne */
		for (int j = 0; j < WIDTH; j++){ /* check toute la ligne */
			nb_case_adjacente = NbCasesAdj(i, j);
			if (nb_case_adjacente == 2){
				grilletemp[i][j] = grid[i][j];
			}
			else if (nb_case_adjacente == 3){
				grilletemp[i][j] = '#';
			}
			else{
				grilletemp[i][j] = ' ';
			}
		}
	}
	memcpy(&grid, &grilletemp, sizeof grid); 
	
}

int main(int argc, char *argv[])
{
	
	int motif;
	motif = init_Game();
	loadGame(motif);
	drawGame();
	
	while(getc(stdin) != 's'){
		
		system("clear"); /* equivalent au os.system en python permet de utiliser la commance clear du terminal*/
		drawGame();
		printf("Press s and enter for stop \n");
		printf("Press enter for play \n");
		UpdateGame();
	}
	
	return 0;
}