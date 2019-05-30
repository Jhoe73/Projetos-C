#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

#define MAX_PALAVRA 100
#define NIVEL_FACIL 1.5
#define NIVEL_MEDIO 1
#define NIVEL_DIFICIL 0.5
#define MINIMO_TENTATIVAS 7
#define MAXIMO_TENTATIVAS 20

int escolhe_dificuldade() {
  char resp;
  printf("Independente da escolha Tentativas = min(%d) max(%d)\n", MINIMO_TENTATIVAS, MAXIMO_TENTATIVAS);
  printf("1 = (Fácil) Tentativas = 150%% da quantidade de letras\n");
  printf("2 = (Médio) Tentativas = 100%% da quantidade de letras\n");
  printf("3 = (Difícil) Tentativas = 50%% da quantidade de letras \n");
  printf("Escolha... \t");
  fflush(stdin);
  scanf(" %d", &resp);

  return resp;
}

int calcula_tentativas(int dificuldade, int quant_caracteres){
  int resp;
  switch (dificuldade) {
    case 1 :
    resp = quant_caracteres*NIVEL_FACIL;
    break;
    case 2 :
    resp = quant_caracteres*NIVEL_MEDIO;
    break;
    case 3 :
    resp = quant_caracteres*NIVEL_DIFICIL;
    break;
    default :
    resp = quant_caracteres*NIVEL_DIFICIL;
    break;
  }
  if (resp > MAXIMO_TENTATIVAS) {
    resp = MAXIMO_TENTATIVAS;
  } else if ( resp < MINIMO_TENTATIVAS) {
    resp = MINIMO_TENTATIVAS;
  }
  return resp;
}

void desenha_forca(char boneco_enforcado[], int quant_caracteres, int quant_tentativas, char letras_chute[]) {
  printf("\n _________ ");
  printf("\n|/        | ");
  printf("\n|         %c \t  Esta palavra contém %d letras", boneco_enforcado[0], quant_caracteres);
  printf("\n|        %c%c%c \t  Tentativas restantes: %d", boneco_enforcado[1], boneco_enforcado[2], boneco_enforcado[3], quant_tentativas);
  printf("\n|        %c%c%c \t  Letras chutadas: %s", boneco_enforcado[4], boneco_enforcado[5], boneco_enforcado[6], letras_chute);
  printf("\n|\n|\n| ");
}

void desenha_palavra(int quant_caracteres, char letras_acertadas[]) {
  for (size_t i = 0; i < quant_caracteres; i++) {
    printf("%c  ", letras_acertadas[i]);
  }
  printf("\n| ");
  for (size_t i = 0; i < quant_caracteres; i++) {
    printf("_  ");
  }
  printf("\n\n");

}

int verifica_vitoria(char palavra[], char letras_acertadas[]) {
  if (strcmpi(palavra, letras_acertadas) == 0) {
    printf("Parabéns você acertou!!!\n\n");
    return 1;
  } else {
    return 0;
  }
}

char recebe_letra(char letras_chute[]) {

  char letra_chute;
  printf("Chute uma letra... \n");

  do{
    fflush(stdin);
    scanf(" %c", &letra_chute);
  } while(isalpha(letra_chute) == 0);

  letras_chute[strlen(letras_chute)] = letra_chute;

  return letra_chute;
}

int verifica_letra(int quant_caracteres, char palavra[], char letra_chute, char letras_acertadas[]) {
  int acertou_letra = 0;

  for (size_t i = 0; i < quant_caracteres; i++) {
    if (toupper(palavra[i]) == toupper(letra_chute)) {
      acertou_letra = 1;
      if(i == 0){
        letras_acertadas[i] = toupper(letra_chute);
      } else {
        letras_acertadas[i] = tolower(letra_chute);
      }
    }
  }

  return acertou_letra;
}

int main() {

  setlocale(LC_ALL, "Portuguese");

  char letras_chute[MAX_PALAVRA] = " ";
  char letras_acertadas[MAX_PALAVRA] = " ";
  char palavra[MAX_PALAVRA] = "Jhoe";
  char boneco_enforcado[MAX_PALAVRA] = " ";
  char boneco[MAX_PALAVRA] = "O/|\\/ \\";
  int quant_caracteres = strlen(palavra);
  int quant_tentativas;

  int dificuldade = escolhe_dificuldade();
  quant_tentativas = calcula_tentativas(dificuldade, quant_caracteres);

  do{

    system("cls");
    desenha_forca(boneco_enforcado, quant_caracteres, quant_tentativas, letras_chute);
    desenha_palavra(quant_caracteres, letras_acertadas);
    if (verifica_vitoria(palavra, letras_acertadas)) {
      break;
    }

    if (quant_tentativas > 0) {

      char letra_chute = recebe_letra(letras_chute);

      int acertou_letra = verifica_letra(quant_caracteres, palavra, letra_chute, letras_acertadas);

      if (!acertou_letra) {
        if (quant_tentativas < 8) {
          for (size_t i = 8; i >= quant_tentativas; i--) {
            boneco_enforcado[i-1] = boneco[i-1];
          }
        }
        quant_tentativas--;
      }

    } else {
      printf("Game Over\n\n");
      break;
    }

  } while(1);
}
