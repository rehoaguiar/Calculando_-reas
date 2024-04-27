#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Cria uma struct para os pontos
typedef struct {
    float X;
    float Y;
} Ponto;

// Cria uma struct para os polígonos
typedef struct {
    Ponto *vertices;
    int numVertices;
} Poligono;

// Função para calcular a área do triângulo
float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    return fabs((A.X * (B.Y - C.Y)) + (B.X * (C.Y - A.Y)) + (C.X * (A.Y - B.Y))) / 2.0;
}

// Função para calcular a área total do polígono
float AreaPoligono(Poligono poligono) {
    float areaTotal = 0.0;
    Ponto pontoRef = poligono.vertices[0]; // Ponto de referência para decomposição em triângulos

    for (int i = 1; i < poligono.numVertices - 1; i++) {
        float areaTriangulo = AreaTriangulo(pontoRef, poligono.vertices[i], poligono.vertices[i + 1]);
        areaTotal += areaTriangulo;
    }

    return areaTotal;
}

// Função para ler um polígono de um arquivo
void lerPoligonoArquivo(Poligono *poligono, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo '%s'.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d", &poligono->numVertices);

    // Verifica se é um triângulo/polígono (>3)
    if (poligono->numVertices < 3) {
        printf("O polígono deve ter pelo menos 3 vértices.\n");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    // Alocação de memória
    poligono->vertices = (Ponto *)malloc(poligono->numVertices * sizeof(Ponto));
    if (poligono->vertices == NULL) {
        printf("Erro de alocação de memória.\n");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    // Lê as coordenadas do polígono
    for (int i = 0; i < poligono->numVertices; i++) {
        fscanf(arquivo, "%f %f", &poligono->vertices[i].X, &poligono->vertices[i].Y);
    }

    fclose(arquivo);
}

// Função para ler um polígono
void lerPoligonoTeclado(Poligono *poligono) {
    printf("Digite o número de vértices do polígono: ");
    scanf("%d", &poligono->numVertices);

    // Verifica se é um polígono (>3)
    if (poligono->numVertices < 3) {
        printf("O polígono deve ter pelo menos 3 vértices.\n");
        exit(EXIT_FAILURE);
    }

    // Alocação de memória
    poligono->vertices = (Ponto *)malloc(poligono->numVertices * sizeof(Ponto));
    if (poligono->vertices == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    // Lê as coordenadas do polígono
    for (int i = 0; i < poligono->numVertices; i++) {
        printf("Digite as coordenadas x e y do vértice %d separadas por espaço: ", i + 1);
        scanf("%f %f", &poligono->vertices[i].X, &poligono->vertices[i].Y);
    }
}

// Função para criar um arquivo com as coordenadas do polígono
void criarArquivo(Poligono poligono, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo '%s'.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    fprintf(arquivo, "%d\n", poligono.numVertices);

    for (int i = 0; i < poligono.numVertices; i++) {
        fprintf(arquivo, "%.2f %.2f\n", poligono.vertices[i].X, poligono.vertices[i].Y);
    }

    fclose(arquivo);

    // Calcula a área do polígono
    float area = AreaPoligono(poligono);
    printf("\nA área do polígono é: %.2f\n", area);
}

// Função para liberar a memória alocada
void liberarPoligono(Poligono *poligono) {
    if (poligono->vertices != NULL) {
        free(poligono->vertices);
        poligono->vertices = NULL;
    }
}

int main() {
    Poligono poligono;
    char nomeArquivo[100];
    int resposta;

    // Menu para escolha (Criar um arquivo ou ler um arquivo existente)
    printf("\nDigite 1 para criar um arquivo com as coordenadas do polígono ou 0 para ler um arquivo existente: ");
    scanf("%d", &resposta);

    if (resposta == 1) {
        printf("\nDigite o nome do arquivo a ser criado: ");
        scanf("%s", nomeArquivo);

        lerPoligonoTeclado(&poligono);

        criarArquivo(poligono, nomeArquivo);

        liberarPoligono(&poligono);
    } else if (resposta == 0) {
        printf("Digite o nome do arquivo a ser lido: ");
        scanf("%s", nomeArquivo);

        lerPoligonoArquivo(&poligono, nomeArquivo);

        float area = AreaPoligono(poligono);
        printf("\nA área do polígono é: %.2f\n", area);

        liberarPoligono(&poligono);
    } else {
        printf("Opção inválida.\n");
        return EXIT_FAILURE;
    }

    return 0;
}
