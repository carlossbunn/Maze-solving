#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 61  // Tamanho do labirinto

int isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 0);
}

int solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N], int endX, int endY) {
    if (x == endX && y == endY) {
        sol[x][y] = 1;
        return 1; // Solução encontrada
    }

    if (isSafe(maze, x, y)) {
        sol[x][y] = 1;

        if (x + 1 < N && solveMazeUtil(maze, x + 1, y, sol, endX, endY) == 1) return 1;
        if (y + 1 < N && solveMazeUtil(maze, x, y + 1, sol, endX, endY) == 1) return 1;
        if (x - 1 >= 0 && solveMazeUtil(maze, x - 1, y, sol, endX, endY) == 1) return 1;
        if (y - 1 >= 0 && solveMazeUtil(maze, x, y - 1, sol, endX, endY) == 1) return 1;

        sol[x][y] = 0; // Backtrack
    }
    return 0;
}

void printMaze(int sol[N][N]) {
    printf("Solution:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", sol[i][j] ? 'o' : '.');
        }
        printf("\n");
    }
}

void loadMaze(int maze[N][N], char *fname) {
    FILE *f;
    char line[1024];
    int lineN = 0;

    f = fopen(fname, "r");
    if (!f) {
        perror("Unable to open file");
        exit(1);
    }

    while (fgets(line, sizeof(line), f) != NULL && lineN < N) {
        for (int i = 0; i < N && line[i] != '\n'; i++) {
            maze[lineN][i] = line[i] - '0';
        }
        lineN++;
    }
    fclose(f);
    printf("Labirinto carregado com sucesso.\n");
}

int main() {
    int maze[N][N] = {0};
    int sol[N][N] = {0};

    int startX = 0, startY = 0;
    int endX = N-1, endY = N-1;

    loadMaze(maze, "lab.txt");
    printMaze(maze);  // Diagnostic print to see how maze is loaded

    if (solveMazeUtil(maze, startX, startY, sol, endX, endY) == 1) {
        printf("Labirinto resolvido!\n");
        printMaze(sol);
    } else {
        printf("Não há solução para o labirinto.\n");
    }

    return 0;
}
