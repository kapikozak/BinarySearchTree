#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
    int klucz;
    int dana;
    struct vertex* left, *right;
} vertex, *pvertex;

pvertex root;

void InitBST() {
    root = NULL;
}

pvertex BSTNewLeaf(int klucz, int dana) {
    pvertex p = malloc(sizeof(struct vertex));
    if (!p) {
        perror("Nie udalo sie przydzielic pamieci");
        exit(EXIT_FAILURE);
    }
    p->klucz = klucz;
    p->dana = dana;
    p->left = p->right = NULL;
    return p;
}

void BSTInsert(int klucz, int dana) {
    pvertex* p = &root;
    while (*p) {
        if ((*p)->klucz == klucz) return;
        else if ((*p)->klucz > klucz) {
            p = &(*p)->left;
        } else {
            p = &(*p)->right;
        }
    }
    *p = BSTNewLeaf(klucz, dana);
}

char BSTFind(int klucz, int* dana) {
    pvertex p = root;
    while (p) {
        if (p->klucz == klucz) {
            *dana = p->dana;
            return 1;
        } else if (p->klucz > klucz) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    return 0;
}

void BSTDestroy(pvertex* tree) {
    if (*tree) {
        BSTDestroy(&(*tree)->left);
        BSTDestroy(&(*tree)->right);
        free(*tree);
        *tree = NULL;
    }
}

pvertex BSTExtractMin(pvertex* tree) {
    if(!tree) return NULL;
    pvertex p;
    while((*tree)->left) {
        tree = &(*tree)->left;
    }
    p = *tree;
    *tree = p->right;
    return p;
}

void BSTDelete(int klucz) {
    pvertex p, q, *r = &root;
    while (*r) {
        p = *r;
        if (klucz < p->klucz) {
            r = &p->left;
        } else if (klucz > p->klucz) {
            r = &p->right;
        } else {
            if (!p->left) *r = p->right;
            else if (!p->right) *r = p->left;
            else {
                q = BSTExtractMin(&p->right);
                q->left = p->left;
                q->right = p->right;
                *r = q;
            }
            free(p);
            return;
        }
    }
}


void BSTPrintInOrder(pvertex tree) {
    if (tree) {
        BSTPrintInOrder(tree->left);
        printf("(%d, %d)\n", tree->klucz, tree->dana);
        BSTPrintInOrder(tree->right);
    }
}

int main() {
    InitBST();

    BSTInsert(10, 100);
    BSTInsert(5, 50);
    BSTInsert(15, 150);
    BSTInsert(7, 70);

    printf("Drzewo BST w kolejnosci rosnacych klucz (klucz, dana):\n");
    BSTPrintInOrder(root);

    int dana;
    if (BSTFind(7, &dana)) {
        printf("Znaleziono klucz 7 z dana: %d\n", dana);
    } else {
        printf("Klucz 7 nie zostal znaleziony\n");
    }

    printf("Usuwanie klucza 5\n");
    BSTDelete(5);

    printf("Drzewo BST po usunieciu klucza 5:\n");
    BSTPrintInOrder(root);

    BSTDestroy(&root);
    printf("Drzewo BST zostalo zniszczone\n");

    return 0;
}
