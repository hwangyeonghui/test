#include <stdio.h>
#include <stdlib.h>


typedef struct Treenode {
    struct Treenode* left_child,* right_child;
    struct Treenode* parent;
    int key,height;
}treeNode;


int isExternal(treeNode* tree) {
    if (tree->left_child == NULL && tree->right_child == NULL) return 1;
    else return 0;
}

int isInternal(treeNode* tree) {
    if (!isExternal(tree)) return 1;
    else return 0;
}

treeNode* treeSearch(treeNode* tree, int key) {
    if (isExternal(tree)) return tree;
    if (tree->key == key)  return tree;
    else if (tree->key > key && isInternal(tree)) {
        tree = treeSearch(tree->left_child, key);
    }
    else if (tree->key < key && isInternal(tree)) {
        tree = treeSearch(tree->right_child, key);
    }
    return tree;
}

treeNode* expandExternal(treeNode* w) {

    treeNode* l = (treeNode*)malloc(sizeof(treeNode));
    l->left_child = NULL;
    l->right_child = NULL;
    l->parent = w;

    treeNode* r = (treeNode*)malloc(sizeof(treeNode));
    r->left_child = NULL;
    r->right_child = NULL;
    r->parent = w;

    w->left_child = l;
    w->right_child = r;

    return w;
}


void insertItem(treeNode* root, int key) {
    treeNode* w = treeSearch(root, key);
    if (isInternal(w)) return;
    else {
        w->key = key;
        expandExternal(w);
    }
}

treeNode* sibling(treeNode* w) {
    if (w->parent == NULL) return NULL;
    if (w->parent->left_child == w) return w->parent->right_child;
    else return w->parent->left_child;
}

treeNode* inOrderSucc(treeNode* w) {
    w = w->right_child;
    if (isExternal(w)) return NULL;
    while (isInternal(w->left_child)) {
        w = w->left_child;
    }
    return w;
}

void reduceExternal(treeNode** root, treeNode* z) {
    treeNode* w = z->parent, * zs = sibling(z);

    if (w->parent == NULL) {
        *root = zs;
        zs->parent = NULL;
    }
    else {
        treeNode* g = w->parent;
        zs->parent = g;
        if (w == g->left_child) g->left_child = zs;
        if (w == g->right_child) g->right_child = zs;
    }
    free(z);
    free(w);
}


void removeElement(treeNode** tree, int key) {
    treeNode* w = treeSearch(*tree, key);
    if (isExternal(w)) {
        printf("X\n");
        return;
    }
    int delKey = w->key;
    treeNode* z = w->left_child;
    if (!isExternal(z))  z = w->right_child;
    if (isExternal(z)) reduceExternal(tree, z);
    else {
        treeNode* y = inOrderSucc(w);
        z = y->left_child;
        w->key = y->key;
        reduceExternal(tree, z);
    }
    printf("%d\n", delKey);
}

void preOrder(treeNode* root) {
    if (isInternal(root)) {
        printf(" %d", root->key);
        preOrder(root->left_child);
        preOrder(root->right_child);
    }

}

void freeTree(treeNode* root) {
    if (root->left_child != NULL) {
        freeTree(root->left_child);
    }
    if (root->right_child != NULL) {
        freeTree(root->right_child);
    }
    free(root);
}

int main() {
    int input; char srt;
    treeNode* k,* root = (treeNode*)malloc(sizeof(treeNode));
    root->parent = NULL;
    root->right_child = NULL;
    root->left_child = NULL;

    do {
        scanf("%c", &srt);
        switch (srt) {
        case 'i':
            scanf("%d", &input);
            insertItem(root, input);
            break;

        case 's':
            scanf("%d", &input);
            k = treeSearch(root, input);
            if (isExternal(k))
                printf("X\n");
            else
                printf("%d\n", k->key);
            break;

        case 'd':
            scanf("%d", &input);
            removeElement(&root, input);
            break;

        case 'p':
            preOrder(root);
            printf("\n");
            break;

        default: break;
        }
    } while (srt != 'q');

    free(root);
}