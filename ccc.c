#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Treenode {
   struct Treenode* left_child, *right_child;
   struct Treenode *parent;
   int key, height;
}treeNode;

void swap(int *p, int *q){
   int tmp;
   tmp = *p;
   *p = *q;
   *q = tmp;
}

int main(){

   int n;
   int *p = (int *)calloc(sizeof(int), 5);
   int *q = (int *)malloc(sizeof(int) * 5);

   for (int i = 0;i < sizeof(p); i++)
}