#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char *nome;
    int votos;
    int numero;

}Candidato;

void resetarArquivo(FILE * file){
    int n_candidatos = 3;
    fprintf(file, "%d\n", n_candidatos);

    for(int i = 0; i < n_candidatos; i++){
        fprintf(file, "candidato%d-%d-%d\n", i + 1, i + 12, 0);
    }

}

void passar_candidatos(FILE * file, Candidato * candidato, int n_candidatos){

    char linha[50];
    fgets(linha, 50, file);

    for(int i = 0; i < n_candidatos; i++){

        fgets(linha, 50, file);

        char *nome = strtok(linha, "-");
        char *numero = strtok(NULL, "-");
        char *votos = strtok(NULL, "\n");

        candidato[i].nome = malloc(strlen(nome) * sizeof(char));

        strcpy(candidato[i].nome, nome);
        candidato[i].numero = atoi(numero);
        candidato[i].votos  = atoi(votos);

    }

}

int buscarCandidato(Candidato * candidatos, int n_candidatos, int voto){

    for(int i = 0; i < n_candidatos; i++){
        if(candidatos[i].numero == voto)
            return i;
    }

    return -1;

}


int iniciar_votacao(Candidato *candidatos, int n_candidatos){

    printf("Selecione seu candidato\n");
    for(int i = 0; i < n_candidatos; i++){
        printf("%d - %s\n", candidatos[i].numero, candidatos[i].nome);
    }

    printf(">>>");

    int voto;
    scanf("%d", &voto);

    if(voto == 9999)
        return 0;

    int indice = buscarCandidato(candidatos, n_candidatos, voto);

    while(indice == -1){

        printf("Candidato invalido\n>>>");
        scanf("%d", &voto);
        indice = buscarCandidato(candidatos, n_candidatos, voto);

    }

    printf("Candidato escolhido: %s\n", candidatos[indice].nome);
    candidatos[indice].votos++;

    return 1;

}

void votoImpresso(Candidato * candidatos, int n_candidatos){

    for(int i = 0; i < n_candidatos; i++){
        printf("%s - %d votos\n", candidatos[i].nome, candidatos[i].votos);
    }

}

void atualizarArquivo(FILE *file, Candidato * candidatos, int n_candidatos){


    fprintf(file, "%d\n", n_candidatos);

    for(int i = 0; i < n_candidatos; i++){
        fprintf(file, "%s-%d-%d\n", candidatos[i].nome, candidatos[i].numero, candidatos[i].votos);
    }
}

int main()
{

    FILE *file;
    Candidato * candidatos;

    /*
    file = fopen("candidatos.urna", "w");

    if(file == NULL){
        printf("Erro ao ler arquivo");
        return 0;
    }

    resetarArquivo(file);
    fclose(file);*/

    file = fopen("candidatos.urna", "r");

    if(file == NULL){
        printf("Erro ao ler arquivo");
        return 0;
    }

    int n_candidatos;
    fscanf(file, "%d", &n_candidatos);

    candidatos = (Candidato*) malloc(n_candidatos * sizeof(Candidato));
    passar_candidatos(file, candidatos, n_candidatos);

    fclose(file);

    while(iniciar_votacao(candidatos, n_candidatos)){
        system("pause");
        system("cls");
    }

    system("pause");
    system("cls");

    printf("Atualizando dados...\n");

    votoImpresso(candidatos, n_candidatos);

    file = fopen("candidatos.urna", "w");

    if(file == NULL){
        printf("Erro ao ler arquivo");
        return 0;
    }

    atualizarArquivo(file, candidatos, n_candidatos);
    fclose(file);


    free(candidatos);

    return 0;
}
