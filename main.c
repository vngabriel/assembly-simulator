#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

char *pega_codigo(char *instrucao_entrada){
    char *codigo;
    int i;
    codigo = (char*)malloc(sizeof(char) * 4);

    // pega apenas os caracteres até o terceiro caractere que diz respeito ao código da instrução
    for(i = 0; i < 3; i++){
        codigo[i] = instrucao_entrada[i];
    }
    codigo[i] = '\0';

    return codigo;
}

int acha_virgula(char *instrucao_entrada){
    // inicializo a posicao_virgula com -1 
    // pois se a instrução não tiver vírgula eu saberei pois irá retornar -1
    int i = 0, posicao_virgula = -1;
    while(instrucao_entrada[i] != '\0'){
        if(instrucao_entrada[i] == ','){
            posicao_virgula = i;
        }
        i++;
    }
    return posicao_virgula;
}

char *pega_parametro1(char *instrucao_entrada, int posicao_virgula){
    char *parametro1;
    int i, j;
    parametro1 = (char*)malloc(sizeof(char) * 10);

    // começa no quarto caractere que é o caractere depois do espaço entre o código e os parâmetros
    // e vai até a posição da vírgula que é onde acaba o primeiro parâmetro
    for(i = 4, j = 0; i < posicao_virgula; i++, j++){
        parametro1[j] = instrucao_entrada[i];
    }
    parametro1[j] = '\0';

    return parametro1;
}

char *pega_parametro2(char *instrucao_entrada, int posicao_virgula){
    char *parametro2;
    int i, j;
    parametro2 = (char*)malloc(sizeof(char) * 10);

    // checo se depois da vírgula tem um espaço então desconsidero ele na criação da string parâmetro2
    if(instrucao_entrada[posicao_virgula + 1] == ' '){
        for(i = posicao_virgula + 2, j = 0; i < strlen(instrucao_entrada); i++, j++){
            parametro2[j] = instrucao_entrada[i];
        }
        parametro2[j] = '\0';

    } else{
        // começa no índice da vírgula + 1 e vai até o final da string para pegar o segundo parâmetro
        for(i = posicao_virgula + 1, j = 0; i < strlen(instrucao_entrada); i++, j++){
            parametro2[j] = instrucao_entrada[i];
        }
        parametro2[j] = '\0';
    }

    return parametro2;
}

int pega_endereco_memoria(char *parametro){
    int i, j, endereco_memoria;
    char *endereco_memoria_string;

    endereco_memoria_string = (char*)malloc(sizeof(char) * strlen(parametro));

    // criando uma nova string que representa o endereço de memória sem os colchetes
    for(i = 1, j = 0; i < strlen(parametro) - 1; i++, j++){
        endereco_memoria_string[j] = parametro[i];
    }
    endereco_memoria_string[j] = '\0';
    // transfromando a string que contém o endereço de memória em inteiro
    endereco_memoria = atoi(endereco_memoria_string);

    return endereco_memoria;
}

void mov_reg_cte(char *parametro1, int constante, int *registradores){

    // checagem de qual registrador o usuário escolheu para colocar o valor da constante nele
    if(parametro1[0] == 'A'){
        registradores[0] = constante;
    } else if(parametro1[0] == 'B'){
        registradores[1] = constante;
    } else if(parametro1[0] == 'C'){
        registradores[2] = constante;
    } else if(parametro1[0] == 'D'){
        registradores[3] = constante;
    }
}

void mov_reg_memoria(char *parametro1, int *registradores, int *memoria_dados, int endero_memoria){

    // checagem de qual registrador o usuário escolheu para colocar o valor do endereço de memória nele
    if(parametro1[0] == 'A'){
        registradores[0] = memoria_dados[endero_memoria - 1];
    } else if(parametro1[0] == 'B'){
        registradores[1] = memoria_dados[endero_memoria - 1];
    } else if(parametro1[0] == 'C'){
        registradores[2] = memoria_dados[endero_memoria - 1];
    } else if(parametro1[0] == 'D'){
        registradores[3] = memoria_dados[endero_memoria - 1];
    }
}

void mov_memoria_cte(int *memoria_dados, int endereco_memoria, int constante){
    
    // colocando uma constante no endereço de memória que o usuário digitou
    memoria_dados[endereco_memoria - 1] = constante;
}

void mov_memoria_reg(int *memoria_dados, int endereco_memoria, int *registradores, char *parametro2){

    // checando qual o registrador o usuário escolheu para colocar o valor do registrador na memória
    if(parametro2[0] == 'A'){
        memoria_dados[endereco_memoria - 1] = registradores[0];
    } else if(parametro2[0] == 'B'){
        memoria_dados[endereco_memoria - 1] = registradores[1];
    } else if(parametro2[0] == 'C'){
        memoria_dados[endereco_memoria - 1] = registradores[2];
    } else if(parametro2[0] == 'D'){
        memoria_dados[endereco_memoria - 1] = registradores[3];
    }
}

void processa_mov(char *parametro1, char *parametro2, int *registradores, int *memoria_dados){
    int constante, endereco_memoria; 

    // primeiro eu checo se o usuário digitou um resgistrador no primeiro parâmetro
    if(parametro1[0] == 'A' || parametro1[0] == 'B' || parametro1[0] == 'C' || parametro1[0] == 'D'){

        // aqui eu checo se o usuário digiou uma constante no segundo parâmetro
        if(parametro2[0] >= '0' && parametro2[0] <= '9'){

            // atoi é a função que transforma string para inteiro
            constante = atoi(parametro2);
            mov_reg_cte(parametro1, constante, registradores);

        // aqui eu checo se o usuário digitou um endereço de memória no segundo parâmetro
        } else if(parametro2[0] == '[' && parametro2[strlen(parametro2) - 1] == ']'){   

            endereco_memoria = pega_endereco_memoria(parametro2);
            mov_reg_memoria(parametro1, registradores, memoria_dados, endereco_memoria);

        } else{
            printf(ANSI_COLOR_RED "*erro!\n" ANSI_COLOR_RESET);
        }

    // checando se o primeiro parâmetro é um endereço de memória
    } else if(parametro1[0] == '[' && parametro1[strlen(parametro1) - 1] == ']'){
        
        endereco_memoria = pega_endereco_memoria(parametro1);

        if(parametro2[0] >= '0' && parametro2[0] <= '9'){
            
            constante = atoi(parametro2);
            mov_memoria_cte(memoria_dados, endereco_memoria, constante);

        } else if(parametro2[0] == 'A' || parametro2[0] == 'B' || parametro2[0] == 'C' || parametro2[0] == 'D'){

            mov_memoria_reg(memoria_dados, endereco_memoria, registradores, parametro2);

        } else{
            printf(ANSI_COLOR_RED "*erro!\n" ANSI_COLOR_RESET);
        }

    } else{
        printf(ANSI_COLOR_RED "*erro!\n" ANSI_COLOR_RESET);
    }
}

void add_reg_reg(char *parametro1, char *parametro2, int *registradores){

    // descobrindo qual registrador o usuário digitou nos dois parâmetros 
    // para somar o valor deles e armazenar no registrador do parâmetro 1
    if(parametro1[0] == 'A'){
        if(parametro2[0] == 'A'){
            registradores[0] = registradores[0] + registradores[0];
        } else if(parametro2[0] == 'B'){
            registradores[0] = registradores[0] + registradores[1];
        } else if(parametro2[0] == 'C'){
            registradores[0] = registradores[0] + registradores[2];
        } else if(parametro2[0] == 'D'){
            registradores[0] = registradores[0] + registradores[3];
        }
    } else if(parametro1[0] == 'B'){
        if(parametro2[0] == 'A'){
            registradores[1] = registradores[1] + registradores[0];
        } else if(parametro2[0] == 'B'){
            registradores[1] = registradores[1] + registradores[1];
        } else if(parametro2[0] == 'C'){
            registradores[1] = registradores[1] + registradores[2];
        } else if(parametro2[0] == 'D'){
            registradores[1] = registradores[1] + registradores[3];
        }
    } else if(parametro1[0] == 'C'){
        if(parametro2[0] == 'A'){
            registradores[2] = registradores[2] + registradores[0];
        } else if(parametro2[0] == 'B'){
            registradores[2] = registradores[2] + registradores[1];
        } else if(parametro2[0] == 'C'){
            registradores[2] = registradores[2] + registradores[2];
        } else if(parametro2[0] == 'D'){
            registradores[2] = registradores[2] + registradores[3];
        }
    } else if(parametro1[0] == 'D'){
        if(parametro2[0] == 'A'){
            registradores[3] = registradores[3] + registradores[0];
        } else if(parametro2[0] == 'B'){
            registradores[3] = registradores[3] + registradores[1];
        } else if(parametro2[0] == 'C'){
            registradores[3] = registradores[3] + registradores[2];
        } else if(parametro2[0] == 'D'){
            registradores[3] = registradores[3] + registradores[3];
        }
    }
}

void add_reg_cte(char *parametro1, int constante, int *registradores){

    // descobrindo qual registrador o usuário escolheu 
    // para somar o valor do reg com a constante e armazenar no próprio reg
    if(parametro1[0] == 'A'){
        registradores[0] = registradores[0] + constante;
    } else if(parametro1[0] == 'B'){
        registradores[1] = registradores[1] + constante;
    } else if(parametro1[0] == 'C'){
        registradores[2] = registradores[2] + constante;
    } else if(parametro1[0] == 'D'){
        registradores[3] = registradores[3] + constante;
    }
}

void processa_add(char *parametro1, char *parametro2, int *registradores){
    int constante;

    // checando se o usuário digitou um registrador no primeiro parâmetro
    if(parametro1[0] == 'A' || parametro1[0] == 'B' || parametro1[0] == 'C' || parametro1[0] == 'D'){

        // checando se o usuário digitou um registrador no segundo parâmetro
        if(parametro2[0] == 'A' || parametro2[0] == 'B' || parametro2[0] == 'C' || parametro2[0] == 'D'){
            add_reg_reg(parametro1, parametro2, registradores);

        // checando se o usuário digitou uma constante no segundo parâmetro
        } else if(parametro2[0] >= '0' && parametro2[0] <= '9'){
            constante = atoi(parametro2);
            add_reg_cte(parametro1, constante, registradores);
        } else{
            printf(ANSI_COLOR_RED "*erro!\n" ANSI_COLOR_RESET);
        }

    } else{
        printf(ANSI_COLOR_RED "*erro!\n" ANSI_COLOR_RESET);
    }
}

void impressao(int *registradores, int *memoria_dados){
    int i;

    printf("\nBanco de registradores: A:%d B:%d C:%d D:%d\n\n", registradores[0], registradores[1], registradores[2], registradores[3]);
    printf("Memória de dados:");
    for(i = 0; i < 15; i++){
        printf(" %3d", memoria_dados[i]);
    }
    printf("\n");
    printf("                 ");
    for(i = 15; i < 30; i++){
        printf(" %3d", memoria_dados[i]);
    }
    printf("\n");
    printf("                 ");
    for(i = 30; i < 45; i++){
        printf(" %3d", memoria_dados[i]);
    }
    printf("\n");
    printf("                 ");
    for(i = 45; i < 50; i++){
        printf(" %3d", memoria_dados[i]);
    }
    printf("\n");
}

int main(){
    // declaração de variáveis
    int *registradores, *memoria_dados;
    char *instrucao_entrada, *codigo, *parametro1, *parametro2;
    int i, j, posicao_virgula, flag_parada = 1;
    int cont_codigo;

    // alocação da memória para os ponteiros
    registradores = (int*)malloc(sizeof(int) * 4);
    memoria_dados = (int*)malloc(sizeof(int) * 50);
    instrucao_entrada = (char*)malloc(sizeof(char) * 20);
    codigo = (char*)malloc(sizeof(char) * 4);
    parametro1 = (char*)malloc(sizeof(char) * 10);
    parametro2 = (char*)malloc(sizeof(char) * 10);

    // deixando os registradores e a memória com valor 0 para aparecer no primeiro print
    for(i = 0; i < 4; i++){
        registradores[i] = 0;
    }
    for(i = 0; i < 50; i++){
        memoria_dados[i] = 0;
    }

    printf("\n=== Bem vindo ao Simulador Assembly em Linguagem C ===\n");
    while(flag_parada == 1){

        // impressão
        impressao(registradores, memoria_dados);

        // lendo a instrução
        printf("> ");
        gets(instrucao_entrada);

        // pegando o código da instrução
        codigo = pega_codigo(instrucao_entrada);

        // processando a instrução de entrada
        if(strcmp(codigo, "HLT") == 0){
            flag_parada = 0;

        } else{

            posicao_virgula = acha_virgula(instrucao_entrada);

            // verifico se a vírgula não foi encontrada
            // pois se ela não foi encontrada a sintaxe está errada
            if(posicao_virgula == -1){
                printf(ANSI_COLOR_RED "*erro!\n" ANSI_COLOR_RESET);

            // se existe vírgula então segue o código
            } else{
                parametro1 = pega_parametro1(instrucao_entrada, posicao_virgula);
                parametro2 = pega_parametro2(instrucao_entrada, posicao_virgula);

                if(strcmp(codigo, "MOV") == 0){
                    processa_mov(parametro1, parametro2, registradores, memoria_dados);
                } else if(strcmp(codigo, "ADD") == 0){
                    processa_add(parametro1, parametro2, registradores);
                
                // se o código não é MOV nem ADD então é um código inválido, logo escreve a mensagem de erro
                } else{
                    printf(ANSI_COLOR_RED "*erro!\n" ANSI_COLOR_RESET);
                }
            }
        }
    }

    return 0;
}