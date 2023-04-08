class Processo:
    def __init__(self, pid, tempo_chegada, tempo_execucao):
        self.pid = pid
        self.tempo_chegada = tempo_chegada
        self.tempo_execucao = tempo_execucao
        self.tempo_restante = tempo_execucao

def main():
    numProcessos = int(input("Digite o número de processos: "))
    processos = []
    for i in range(numProcessos):
        tempo_chegada, tempo_execucao = map(int, input(f"Digite o tempo de chegada e de execução para o processo {i+1}: ").split())
        processos.append(Processo(i+1, tempo_chegada, tempo_execucao))
    quantum = int(input("Digite o quantum: "))
    tempo_atual = 0
    tempo_total_espera = 0
    tempo_total_retorno = 0
    concluidos = 0
    while concluidos < numProcessos:
        for p in processos:
            if p.tempo_restante > 0:
                if p.tempo_chegada <= tempo_atual:
                    if p.tempo_restante > quantum:
                        tempo_atual += quantum
                        p.tempo_restante -= quantum
                    else:
                        tempo_atual += p.tempo_restante
                        tempo_total_espera += tempo_atual - p.tempo_chegada - p.tempo_execucao
                        tempo_total_retorno += tempo_atual - p.tempo_chegada
                        p.tempo_restante = 0
                        concluidos += 1
    print(f"Tempo médio de espera: {tempo_total_espera/numProcessos}")
    print(f"Tempo médio de retorno: {tempo_total_retorno/numProcessos}")

if __name__ == '__main__':
    main()
