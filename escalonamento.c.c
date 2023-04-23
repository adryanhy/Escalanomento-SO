#include<stdio.h>
#include <locale.h>


struct Processo {
    int id_processo;
    int turn_around;
    int tChegada;
    int tExecucao;
    int tRestante;
};

int main() {
    setlocale(LC_ALL, "Portuguese");
    int num_processo, quantum, tempoMediaEspera = 0, tempoMediaRetorno = 0;
    printf("Informe o numero de processos: ");
    scanf("%d", &num_processo);
    struct Processo processos[num_processo];
    for (int i = 0; i < num_processo; i++) {
        printf("Informe o tempo de chegada e de execução para o processo %d: ", i + 1);
        scanf("%d%d", &processos[i].tChegada, &processos[i].tExecucao);
        processos[i].id_processo = i + 1;
        processos[i].tRestante = processos[i].tExecucao;
        processos[i].turn_around = processos[i].tExecucao;
    }
    printf("Qual será do o valor do quantum? ");
    scanf("%d", &quantum);
    int tempo_atual = 0, processoConcluidos = 0;
    while(processoConcluidos < num_processo) {
        for(int i = 0; i < num_processo; i++) {
            if(processos[i].tRestante > 0) {
                if(processos[i].tChegada <= tempo_atual) {
                    if(processos[i].tRestante > quantum) {
                        tempo_atual += quantum;
                        processos[i].tRestante -= quantum;
                    }
                    else {
                        tempo_atual += processos[i].tRestante;
                        processos[i].tRestante = 0;
                        tempoMediaEspera += tempo_atual - processos[i].tChegada - processos[i].tExecucao;
                        tempoMediaRetorno += tempo_atual - processos[i].tChegada;
                        processoConcluidos++;
                    }
                }
            }
        }
    }
    for (int j = 0; j < num_processo; j++) {
        printf("Tempo total para executar o processo %d é: %d\n", j+1, processos[j].turn_around);
    }
    printf("\n//////////ESCALONAMENTO DE PROCESSOS//////////////\n");
    printf("\tO tempo médio de espera é: %.2f\n", (float) tempoMediaEspera / num_processo);
    printf("\tO tempo médio de retorno é: %.2f\n", (float) tempoMediaRetorno / num_processo);
    printf("Obrigada por utilizar o nosso app de Escalonamento de Processos!!\n");
    return 0;
}
