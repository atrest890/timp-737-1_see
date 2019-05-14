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
    int size;
} tree;

void init(tree *t) {
    t->root = NULL;
    t->size = 0;
}

node* clear_impl(node *n) {
    if (n != NULL) {
        clear_impl(n->left);
        clear_impl(n->right);
        free(n);
        return n;
    }
    return NULL;
}

void clear(tree *t) {
    clear_impl(t->root);
    t->root = NULL;
    t->size = 0;
}

int mymax(int a, int b) {
    return a > b ? a : b;
}

int getDeepth_dfs(node* root) {
    if(root == NULL){
        return 0;
    }

    return 1 + mymax(getDeepth_dfs(root->left),
                     getDeepth_dfs(root->right));
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
                free(n);
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

int find(tree *t, int value, node *n) {
    node *p = t->root;

    while (p != NULL && p->value != value) {
        if (value < p->value) {
            p = p->left;
        }
        else if (value > p->value) {
            p = p->right;
        }
    }

    if (p == NULL) {
        return 1;
    }

    if (n != NULL) {
        n->left = p->left;
        n->right = p->right;
        n->parent = p->parent;
        n->value = p->value;
    }
    
//    *n = p;

    return 0;
}

//int remove_element(tree *t, int value) {
//    node *n = t->root; //удаляемый элемент

//    while (n != NULL && n->value != value) {
//        if (value < n->value) {
//            n = n->left;
//        }
//        else if (value > n->value) {
//            n = n->right;
//        }
//    }

//    if (n == NULL) {
//        return 1;
//    }

//    node *p = n->parent;

//    //если удаляемый элемент является листом
//    if (n->left == NULL && n->right == NULL) {
//        if (p->left == n) {
//            p->left = NULL;
//        }

//        if (p->right == n) {
//            p->right = NULL;
//        }

//    }
//    //если удаляемый элемент имеет одного потомка
//    else if (n->left == NULL || n->right == NULL) {
//        if (n->left == NULL) {
//            if (p->left == n) {
//                p->left = n->right;
//            }
//            else {
//                p->right = n->right;
//            }

//            n->right->parent = p;
//        }
//        else {
//            if (p->left == n) {
//                p->left = n->left;
//            }
//            else {
//                p->right = n->left;
//            }

//            n->left->parent = p;
//        }
//    }
//    //если удаляемый элемент имеет двух потомков
//    else {
//        node *x = n->right;

//        if (x->left == NULL) {
//            x->right->parent = p;
//            if (n == p->left) {
//                p->left = x;
//            }
//            else {
//                p->right = x;
//            }

//            x->left = n->left;
//            x->left->parent = x;
//            free(n);
//            return 0;
//        }

//        while (x->left != NULL) {
//            x = x->left;
//        }

//        x->parent->left = x->right;

//        if (x->right != NULL) {
//            x->right->parent = x->parent;
//        }

//        if (n == p->left) {
//            p->left = x;
//        }
//        else {
//            p->right = x;
//        }

//        x->right = n->right;
//        x->left = n->left;
//        x->right->parent = x;
//        x->left->parent = x;
//        x->parent = p;
//    }

//    free(n);
//    return 0;

//}

int remove_element(tree *t, int value) {
    node *n = t->root;

    node **parent_ref = &(t->root);

    while (n != NULL && n->value != value) {
        if (value < n->value) {
            parent_ref = &(n->left);
            n = n->left;
        }
        else if (value > n->value) {
            parent_ref = &(n->right);
            n = n->right;
        }
    }

    if (n == NULL) {
        return 1;
    }

    node *p = n->parent;

    //если удаляемый элемент является листом
    if (n->left == NULL && n->right == NULL) {
        *parent_ref = NULL;
    }
    //если удаляемый элемент имеет одного потомка
    else if (n->left == NULL || n->right == NULL) {
        if (n->left == NULL) {
            *parent_ref = n->right;
            n->right->parent = p;
        }
        else {
            *parent_ref = n->left;
            n->left->parent = p;
        }
    }
    //если удаляемый элемент имеет двух потомков
    else {
        node *x = n->right;

        if (x->left == NULL) {

            *parent_ref = x;

            x->parent = p;
            x->left = n->left;
            x->left->parent = x;

            t->size--;
            free(n);
            return 0;
        }

        while (x->left != NULL) {
            x = x->left;
        }

        x->parent->left = x->right;

        if (x->right != NULL) {
            x->right->parent = x->parent;
        }

        *parent_ref = x;

        x->right = n->right;
        x->left = n->left;
        x->right->parent = x;
        x->left->parent = x;
        x->parent = p;
    }

    free(n);
    t->size--;
    return 0;

}

int removeMin(node *n) {
    node **parent_ref = &(n->parent);
    node *p = n->parent;

    if (n->left == NULL && n->right == NULL) {
        parent_ref = NULL;
    }
    //если удаляемый элемент имеет одного потомка
    else if (n->left == NULL || n->right == NULL) {
        if (n->left == NULL) {
            *parent_ref = n->right;
            n->right->parent = p;
        }
        else {
            *parent_ref = n->left;
            n->left->parent = p;
        }
    }
    //если удаляемый элемент имеет двух потомков
    else {
        node *x = n->right;

        if (x->left == NULL) {
            x->right->parent = p;

            *parent_ref = x;

            x->left = n->left;
            x->left->parent = x;
            free(n);
            return 0;
        }

        while (x->left != NULL) {
            x = x->left;
        }

        x->parent->left = x->right;

        if (x->right != NULL) {
            x->right->parent = x->parent;
        }

        *parent_ref = x;

        x->right = n->right;
        x->left = n->left;
        x->right->parent = x;
        x->left->parent = x;
        x->parent = p;
    }

    free(n);
    return 0;
}

int rotateRight(tree*t, node *n) {
    if (n->left == NULL) {
        return 1;
    }

    node *p = n->parent;
    node *x = n->left;
    n->left = x->right;
    x->right = n;

    if (p != NULL) {
        if (n == p->right) {
            p->right = x;
        }
        else if (n == p->right) {
            p->left = x;
        }
    }

    if(n->left != NULL) {
        n->left->parent = n;
    }

    n->parent = x;
    x->parent = p;

    if(n == t->root) {
        t->root = x;
    }

    return 0;
}

int rotateLeft(tree*t, node *n) {
    if (n->right == NULL) {
        return 1;
    }

    node *p = n->parent;
    node *x = n->right;
    n->right = x->left;
    x->left = n;

    if (p != NULL) {
        if (n == p->left) {
            p->left = x;
        }
        else if (n == p->right) {
            p->right = x;
        }
    }


    if (n->right != NULL) {
        n->right->parent = n;
    }

    n->parent = x;
    x->parent = p;

    if(n == t->root) {
        t->root = x;
    }

    return 0;
}

void print(node *n) {
    if(n == NULL) {
        printf("-\n");
        return;
    }

    int deepth = getDeepth_dfs(n);
    unsigned int maxSizeLevel = 1 << deepth;
    node** arr = (node**)malloc(2 * maxSizeLevel * sizeof(node*));
    node** parent = arr;
    node** child = arr + maxSizeLevel;

    int endIdxParent = 0, endIdxChild = 0;

    parent[endIdxParent++] = n;

    for (int q = 0; q < deepth; ++q) {
        for (int i = 0; i < endIdxParent; ++i) {
            if (parent[i] != NULL) {
                if(i != 0) {
                    printf(" ");
                }
                printf("%d", parent[i]->value);

                child[endIdxChild++] = parent[i]->left;
                child[endIdxChild++] = parent[i]->right;
            }
            else {
                if(i != 0) {
                    printf(" ");
                }
                printf("_");

                child[endIdxChild++] = NULL;
                child[endIdxChild++] = NULL;
            }
            fflush(stdout);
        }
        printf("%c", '\n');

        node** tmpPtr = parent;
        parent = child;
        child = tmpPtr;

        endIdxParent = endIdxChild;
        endIdxChild = 0;
    }

    free(arr);
}

void print_tree(tree *t) {
    if(t->root == NULL) {
        printf("-");
        return;
    }

    print(t->root);
}


int main() {
    tree *t = malloc(sizeof(tree));
    //task 1
    init(t);
    int x;
    for (int i = 0; i < 4; ++i) {
        scanf("%d", &x);
        insert(t, x);
    }
    //task 2
    print_tree(t);

    //task 3
    int a;
    for (int i = 0; i < 3; ++i) {
        scanf("%d", &a);
        insert(t, a);
    }
    //task 4
    print_tree(t);

    //task 5
    int m1;
    scanf("%d", &m1);
    node n;
    //find(t, m1, &n);
    if ( find(t, m1, &n) ) {
        printf("-");
    }
    else {
        if (n.parent != NULL) {
            printf("%d", n.parent->value);
        }
        else {
            printf("%c", '_');
        }
        printf(" ");
        if (n.left != NULL) {
            printf("%d", n.left->value);
        }
        else {
            printf("%c", '_');
        }
        printf(" ");
        if (n.right != NULL) {
            printf("%d", n.right->value);
        }
        else {
            printf("%c", '_');
        }
    }
    printf("\n");

    //task 6
    int m2;
    scanf("%d", &m2);
    if ( find(t, m2, &n) ) {
        printf("-");
    }
    else {
        if (n.parent != NULL) {
            printf("%d", n.parent->value);
        }
        else {
            printf("%c", '_');
        }
        printf(" ");
        if (n.left != NULL) {
            printf("%d", n.left->value);
        }
        else {
            printf("%c", '_');
        }
        printf(" ");
        if (n.right != NULL) {
            printf("%d", n.right->value);
        }
        else {
            printf("%c", '_');
        }
    }
    printf("\n");


    //task 7
    int m3;
    scanf("%d", &m3);
    remove_element(t, m3);

    //task 8
    print_tree(t);

    //task 9
    int res = 0;
    while (res != 1) {
        res = rotateLeft(t, t->root);
    }

    //task 10
    print_tree(t);

    //task11
    res = 0;
    while (res != 1) {
        res = rotateRight(t, t->root);
    }

    //task 12
    print_tree(t);

    //task 13
    printf("%d\n", t->size);

    //task 14
    clear(t);

    //task 15
    print_tree(t);

    free(t);

    return 0;
}
