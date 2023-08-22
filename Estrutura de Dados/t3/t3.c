#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Estrutura para representar um nó no grafo
struct Node {
    int data;
    struct Node* next;
};

// Estrutura para representar o grafo
struct Graph {
    int numNodes;
    struct Node* adjList[MAX_NODES];
};

// Inicializa o grafo
void initGraph(struct Graph* g, int numNodes) {
    g->numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
        g->adjList[i] = NULL;
    }
}

// Adiciona uma aresta entre dois nós
void addEdge(struct Graph* g, int src, int dest) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = dest;
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
}

// Percorre o grafo em largura a partir de um nó inicial
void BFS(struct Graph* g, int startNode) {
    int visited[MAX_NODES] = {0};
    struct Node* queue[MAX_NODES];
    int front = 0, rear = 0;

    visited[startNode] = 1;
    printf("%d ", startNode);

    queue[rear] = g->adjList[startNode];
    rear++;

    while (front < rear) {
        struct Node* current = queue[front];
        front++;

        while (current != NULL) {
            int adjNode = current->data;
            if (!visited[adjNode]) {
                visited[adjNode] = 1;
                printf("%d ", adjNode);
                queue[rear] = g->adjList[adjNode];
                rear++;
            }
            current = current->next;
        }
    }
    printf("\n");
}

// Percorre o grafo em profundidade a partir de um nó inicial
void DFS(struct Graph* g, int startNode, int visited[]) {
    visited[startNode] = 1;
    printf("%d ", startNode);

    struct Node* current = g->adjList[startNode];
    while (current != NULL) {
        int adjNode = current->data;
        if (!visited[adjNode]) {
            DFS(g, adjNode, visited);
        }
        current = current->next;
    }
}

void DFS_post_order(struct Graph* g, int startNode, int visited[]) {
    visited[startNode] = 1;

    struct Node* current = g->adjList[startNode];
    while (current != NULL) {
        int adjNode = current->data;
        if (!visited[adjNode]) {
            DFS_post_order(g, adjNode, visited);
        }
        current = current->next;
    }
    visited[startNode] = 1;
    printf("%d ", startNode);
}

// Printa a lista de adjacência
void printAdjList(struct Graph* g) {
    for (int i = 0; i < g->numNodes; i++) {
        printf("Adjacency list of node %d: ", i);
        struct Node* current = g->adjList[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    // Exemplo de uso
    struct Graph g;
    initGraph(&g, 5);
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 0);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 3);

    printAdjList(&g);

    printf("Percurso em largura a partir do nó 2:\n");
    BFS(&g, 2);

    int visited[MAX_NODES] = {0};
    printf("Percurso em profundidade pré-ordem a partir do nó 2:\n");
    DFS(&g, 2, visited);
    printf("\n");

    printf("Percurso em profundidade pós-ordem a partir do nó 2:\n");
    for (int i = 0; i < g.numNodes; i++) {
        visited[i] = 1;
    }

    for (int i = 0; i < g.numNodes; i++) {
        if (visited[i]) {
            DFS_post_order(&g, i, visited);
        }
    }
    printf("\n");

    return 0;
}
