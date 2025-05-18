#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct
{
  int sudo[9][9];
} Node;

Node *createNode()
{
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n)
{
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name)
{
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n)
{
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n)
{
  int i, j, k;

  // Validar filas
  for (i = 0; i < 9; i++)
  {
    int seen[10] = {0}; // Arreglo para marcar números
    for (j = 0; j < 9; j++)
    {
      int num = n->sudo[i][j];
      if (num != 0)
      { // Ignorar celdas vacías
        if (seen[num])
          return 0;    // Número repetido
        seen[num] = 1; // Marcar número
      }
    }
  }

  // Validar columnas
  for (j = 0; j < 9; j++)
  {
    int seen[10] = {0}; // Arreglo para marcar números
    for (i = 0; i < 9; i++)
    {
      int num = n->sudo[i][j];
      if (num != 0)
      { // Ignorar celdas vacías
        if (seen[num])
          return 0;    // Número repetido
        seen[num] = 1; // Marcar número
      }
    }
  }

  // Validar submatrices de 3x3
  for (k = 0; k < 9; k++)
  {
    int seen[10] = {0}; // Arreglo para marcar números
    for (int p = 0; p < 9; p++)
    {
      int i = 3 * (k / 3) + (p / 3);
      int j = 3 * (k % 3) + (p % 3);
      int num = n->sudo[i][j];
      if (num != 0)
      { // Ignorar celdas vacías
        if (seen[num])
          return 0;    // Número repetido
        seen[num] = 1; // Marcar número
      }
    }
  }

  return 1; // Si pasa todas las validaciones, es válido
}

List *get_adj_nodes(Node *n)
{
  List *list = createList();
  return list;
}

int is_final(Node *n)
{
  return 0;
}

Node *DFS(Node *initial, int *cont)
{
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/