
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

