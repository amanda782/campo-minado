# 💣 Campo Minado em C

Um clássico reinventado no terminal! Desenvolvido em linguagem C, este projeto simula o tradicional **Campo Minado** em uma grade 9x9, com 10 bombas escondidas. Um ótimo exercício de lógica, recursividade e manipulação de matrizes.

---

## 🎮 Como jogar

- O campo é uma grade de **9 linhas por 9 colunas**.
- Há exatamente **10 bombas** escondidas em posições aleatórias.
- O jogador deve escolher uma posição digitando a linha e a coluna.
- Se a posição escolhida contiver uma **bomba**, o jogo termina ❌
- Se não, o número exibido indica **quantas bombas existem ao redor**.
- Se a posição for **0**, o jogo revela automaticamente os vizinhos vazios.
- Vence quem **revelar todas as posições seguras** (71 no total).

---

## 🖥️ Execução

Compile com o GCC e execute no terminal:

```bash
gcc campo_minado.c -o campo-minado
./campo-minado