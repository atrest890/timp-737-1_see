#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

typedef struct tree {
    node *root;
    unsigned int size;
} tree;


void init(tree *t) {
    t->root = NULL;
    t->size = 0;
}

node* clear_impl(node *n) {
    if (n != NULL) {
        clear_impl(n->left);
        clear_impl(n->right);
        n = NULL;
        return n;
    }

    return NULL;
}

void clear(tree *t) {
    clear_impl(t->root);
}

int insert(tree *t, int value) {
    node *n = malloc(sizeof(node));
    n->value = value;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;

    node *p = t->root;
    node *tmp = NULL;

    if (t->root == NULL) {
        t->root = n;
    }

    else {
        while (p != NULL) {
            tmp = p;
            if (value < p->value) {
                p = p->left;

            }
            else if (value > p->value) {
                p = p->right;
            }
            else if (value == p->value) {
                return 1;
            }
        }

        n->parent = tmp;

        if (value < tmp->value) {
            tmp->left = n;
        }
        else if (value > tmp->value) {
            tmp->right = n;
        }
    }

    t->size++;

    return 0;

}

void inorderTraversal(node *n) {
    if (n == NULL) {
        return;
    }

    inorderTraversal(n->left);
    //printf("%d ", n->value);
    inorderTraversal(n->right);
    printf("%d", n->value);
    if (n->parent != NULL) {
        printf(" ");
    }
}

int main() {
    tree *t = malloc(sizeof(tree));
    init(t);
    int n = 7;
    int a;

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a);
        insert(t, a);
    }

    inorderTraversal(t->root);
    printf("%c", '\n');
    clear(t);

    return 0;
}
