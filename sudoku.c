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
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        for (int k = 1; k <= 9; k++)
        {
          Node *new_node = copy(n);
          new_node->sudo[i][j] = k;
          if (is_valid(new_node))
          {
            pushBack(list, new_node);
          }
        }
        return list;
      }
    }
  }

  return list;
}

int is_final(Node *n)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
        return 0; // Si hay un cero, no es final
    }
  }
  return 1; // Si no hay ceros, es final
}

Node *DFS(Node *initial, int *cont)
{
  Stack *stack = createStack(); // Crea una pila para realizar la búsqueda en profundidad
  push(stack, initial);         // Inserta el nodo inicial en la pila

  while (!is_empty(stack)) // Mientras la pila no esté vacía
  {
    Node *current = top(stack); // Obtiene el nodo en la cima de la pila
    pop(stack);                 // Elimina el nodo de la pila
    (*cont)++;                  // Incrementa el contador de iteraciones

    if (is_final(current)) // Verifica si el nodo actual es una solución
    {
      return current; // Si es solución, retorna el nodo
    }

    // Genera los nodos adyacentes (posibles movimientos válidos)
    List *adj_nodes = get_adj_nodes(current);

    // Recorre todos los nodos adyacentes
    for (Node *node = first(adj_nodes); node != NULL; node = next(adj_nodes))
    {
      push(stack, node); // Inserta cada nodo adyacente en la pila
    }

    clean(adj_nodes); // Libera la memoria de la lista de nodos adyacentes
  }

  return NULL; // Si no se encuentra solución, retorna NULL
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