#
#include<stdio.h>
#include<stdlib.h>

void headerEscalonamento(){
    printf("-------------ESCALONAMENTO-------------\n");
}

struct processo {
    int pid;
    int tempoChegada;
    int tempoExecucao;
    int tempoRestante;
};
/*ATRIBUIR VALORES NOS PROCESSOS*/
void preencher_processos(struct processo *processos, int numProcesso) {
    for (int i = 0; i < numProcesso; i++) {
        printf("Digite o tempo de chegada e de execucao para o processo %d: ", i + 1);
        scanf("%d%d", &processos[i].tempoChegada, &processos[i].tempoExecucao);
        processos[i].pid = i + 1;
        processos[i].tempoRestante = processos[i].tempoExecucao;
    }
}
int main() {
    int numProcesso, quantum, TME = 0, TMR = 0;
    struct processo *processos;
    printf("Digite o numero de processos: ");
    scanf("%d", &numProcesso);
    processos = (struct processo*) malloc(numProcesso * sizeof(struct processo));
    preencher_processos(processos, numProcesso);
    printf("Digite o quantum: ");
    scanf("%d", &quantum);
    int tempo_atual = 0, processoConcluidos = 0;

    //Logica para validar os processos
    while(processoConcluidos < numProcesso) {
        for(int i = 0; i < numProcesso; i++) {
            if(processos[i].tempoRestante > 0) {
                if(processos[i].tempoChegada <= tempo_atual) {
                    if(processos[i].tempoRestante > quantum) {
                        tempo_atual += quantum;
                        processos[i].tempoRestante -= quantum;
                    }
                    else {
                        tempo_atual += processos[i].tempoRestante;
                        processos[i].tempoRestante = 0;
                        TME += tempo_atual - processos[i].tempoChegada - processos[i].tempoExecucao;
                        TMR += tempo_atual - processos[i].tempoChegada;
                        processoConcluidos++;
                    }
                }
            }
        }
    }

    //O que sera apresentado ao usuario final
    headerEscalonamento();
    printf("Tempo medio de espera: %.2f\n", (float) TME / numProcesso);
    printf("Tempo medio de retorno: %.2f\n", (float) TMR / numProcesso);
    free(processos);
    return 0;
}
