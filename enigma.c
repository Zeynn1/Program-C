#include <stdio.h>

char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
char connexion[26] = "abcdefghijklmnopqrstuvwxyz";
char textrotor[3][26] = {"ekmflgdqvzntowyhxuspaibrcj", "ajdksiruxblhwtmcqgznpyfvoe","bdfhjlcprtxvznyeiwgakmusqo"};
char textReflector[26] = "ejmzalyxvbwfcrquontspikhgd";
int reflector[26];
int shift[3] = {0,0,0};
int rotor[3][26];
int invrotor[3][26];
int posrotor[3];
int lenstring(char full_len[]){
	
	int compteur = 0;
	for(int i=0; full_len[i]; i++){
		compteur ++;
	}
	return compteur;
}

void Chooserotor(){

	char shiftletter[3];
	printf("Entrer les 3 cran des rotor : \n ex:abc\n");
	scanf("%3s",shiftletter);

	for(int i = 0; i<3 ; i++){
		shift[i] = shiftletter[i] - 'a';
	}
	/*for(int i = 0; i<3 ; i++){
		printf("%d",shift[i]);
	}*/
}


void GenerateInvPerm(){
    for(int i = 0; i<3 ; i++){
        for(int j = 0; j<26; j++){
            for(int h = 0; h<26 ; h++){
                if (textrotor[i][h] == ('a' + j)){
                    /*printf("%d - %d\n", i, j);*/
                    invrotor[i][j] = h;    
                }    
            }    
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int j=0; j < 26; j++) {
            printf("%c", ('a' + invrotor[i][j]));
        }
        printf("\n");
    }
}

void Text2Value(void){
	for (int i = 0; i<3 ; i++){
		for (int j = 0; j<26; j++){
			rotor[i][j] = textrotor[i][j]-'a';
		}
	}
	for (int i = 0; i<26 ; i++){
		reflector[i] = textReflector[i]-'a';
    	}
}

int passagerotor(int lettre, int shift, int n){

	lettre = (lettre - shift + 26)%26;
	lettre = rotor[n][lettre];
	lettre = (lettre + shift)%26;
	return lettre;

}

int inverserotor(int lettre, int shift, int rotor_choisi){
	
	lettre = (lettre - shift + 26)%26;
	lettre = invrotor[rotor_choisi][lettre];
  	lettre = (lettre + shift)%26;
  	return lettre;
}

int passagereflecteur(int lettre){
	
	lettre = reflector[lettre];
	return lettre;
}

int connect(int lettre){
	
 	lettre = connexion[lettre];
 	lettre = lettre -'a';
 	return lettre;
}

int encrypt(char lettre){
	
	lettre = lettre-'a';
	lettre = connect(lettre);
	lettre = passagerotor(lettre, shift[0],0);
	lettre = passagerotor(lettre, shift[1],1);
	lettre = passagerotor(lettre, shift[2],2);
	lettre = passagereflecteur(lettre);
	lettre = inverserotor(lettre, shift[2],2);
	lettre = inverserotor(lettre, shift[1],1);
	lettre = inverserotor(lettre, shift[0],0);
	lettre = connect(lettre);
	
	shift[0]++;             
	if( shift[0] == 26){
		shift[1]++;
		shift[0] = 0;
	}
	if(shift[1] == 26){
		shift[2]++;
		shift[1] = 0;
	}
	if(shift[2] == 26)
		shift[2] = 0;
	lettre = lettre + 'a';
	return lettre;
}
void ConnectCables(void){
	char test[12] = "";
	int diff = 0;
	do{
		diff = 0;
		printf("Entrer les 12 cables à inversés : \n ex:abcdefghijkl\n");
		scanf("%12s",test);
		for(int i=0;i<12;i++){
			for(int j=0;j<12;j++){
				if (test[i] == test[j] && i!=j){
					printf("! deux caractères sont identiques\n");
					diff ++;
				}
			}
		}
	}while (diff != 0);
	for(int i = 0; i<12;i=i+2){
		connexion[test[i]-'a'] = test[i+1];
		connexion[test[i+1]-'a'] = test[i];
	}
}
	
void loop_encrypt(char mot[], int len_characher){ /*fonction qui chiffre chaque lettre */
	char lettre; 
	
	for(int i=0; i< len_characher;i++){
		lettre = encrypt(mot[i]);
		printf("%c",lettre);

	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	
	if (argc == 2){
		GenerateInvPerm(); 
		ConnectCables();
		Chooserotor();
		Text2Value();
		loop_encrypt(argv[1],lenstring(argv[1])); 
		/*printf("%s\n", argv[1]);*/
		
	} else{
		fprintf(stderr, "Usage: %s <word encrypt> \n",argv[0] ); /* si pas de mot a cypher renvoyer une erreur */
		return 1;

	}	
	return 0;
}