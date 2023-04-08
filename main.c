/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
const int tam=10;
struct processos
{
    char nome[3];
    int tempo, te, tr;
};
struct processos prontos[tam];

int fim=0;


void inserir()
{
    if (fim ==tam)
    {
        printf("\nFILA CHEIA");
    }
    else
    {
        printf("\nEntre com o nome do processo: ");
        scanf("%s", &prontos[fim].nome);
        printf("Entre com o tempo de processador: ");
        scanf("%d", &prontos[fim].tempo);
        fim++;
    }
}

void mostrar()
{
    if (fim == 0 )
    {
        printf("\nFILA VAZIA");
    }
    else
    {
        for(int i=0; i<fim; i++)
        {
            printf("\n-----------------------------");
            printf("\nNome do processo: %s", prontos[i].nome);
            printf("\nTempo de processamento: %d", prontos[i].tempo);
            printf("\n-----------------------------");
        }
    }
    getch();
}


void fifo()
{
    int espera=0;
    int resposta=0;
    float tme=0;
    float tmr=0;

    for(int i=0; i<fim;i++)
    {
        prontos[i].te = espera;
        prontos[i].tr = resposta + prontos[i].tempo;
        tme = tme + prontos[i].te;
        tmr = tmr + prontos[i].tr;
        espera = espera + prontos[i].tempo;
        resposta = resposta + prontos[i].tempo;
    }
    for(int i=0; i < fim; i++)
    {
        printf("\nProcesso: %s", prontos[i].nome);
        printf("\nTempo de Espera: %d", prontos[i].te);
        printf("\nTempo de Resposta: %d", prontos[i].tr);

    }
    printf("\nEspera: %f \n Resposta: %f", tme,tmr);
    printf("\nTempo medio espera (tme): %f", (tme/fim));
    printf("\nTempo medio retorno (tmr): %f", (tmr/fim));
    getch();
}
int main()
{
    int op;
    do
    {
        system("CLS");
        printf("\n1 - Inserir");
        printf("\n2 - Mostrar");
        printf("\n3 - FIFO");
        printf("\n4 - Sair");
        printf("\n\nEscolha sua opcao: ");
        scanf("%d",&op);
        switch (op)
        {
            case 1: inserir();break;
            case 2: mostrar();break;
            case 3: fifo();break;
        }
    }while(op<=3);
}
*/

#include<stdio.h>
#include<stdlib.h>

struct processo {
    int pid;
    int tempo_chegada;
    int tempo_execucao;
    int tempo_restante;
};

int main() {
    int numProcesso, quantum, tempo_total_espera = 0, tempo_total_retorno = 0;
    struct processo *processos;
    printf("Digite o número de processos: ");
    scanf("%d", &numProcesso);
    processos = (struct processo*) malloc(numProcesso * sizeof(struct processo));
    for(int i = 0; i < numProcesso; i++) {
        printf("Digite o tempo de chegada e de execução para o processo %d: ", i+1);
        scanf("%d%d", &processos[i].tempo_chegada, &processos[i].tempo_execucao);
        processos[i].pid = i+1;
        processos[i].tempo_restante = processos[i].tempo_execucao;
    }
    printf("Digite o quantum: ");
    scanf("%d", &quantum);
    int tempo_atual = 0, concluidos = 0;
    while(concluidos < numProcesso) {
        for(int i = 0; i < numProcesso; i++) {
            if(processos[i].tempo_restante > 0) {
                if(processos[i].tempo_chegada <= tempo_atual) {
                    if(processos[i].tempo_restante > quantum) {
                        tempo_atual += quantum;
                        processos[i].tempo_restante -= quantum;
                    }
                    else {
                        tempo_atual += processos[i].tempo_restante;
                        processos[i].tempo_restante = 0;
                        tempo_total_espera += tempo_atual - processos[i].tempo_chegada - processos[i].tempo_execucao;
                        tempo_total_retorno += tempo_atual - processos[i].tempo_chegada;
                        concluidos++;
                    }
                }
            }
        }
    }
    printf("Tempo médio de espera: %f\n", (float) tempo_total_espera / numProcesso);
    printf("Tempo médio de retorno: %f\n", (float) tempo_total_retorno / numProcesso);
    free(processos);
    return 0;
}

