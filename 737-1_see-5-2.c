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
} tree;



typedef struct stack_node {
    node *data;
    struct stack_node *next;
} stack_node;

typedef struct stack {
    stack_node *head;
} stack;


//stack functions
void init_stack(stack *s) {
    s->head = NULL;
}

int push(stack *s, node *n) {
    stack_node *snode = malloc(sizeof(stack_node));
    snode->data = n;
    snode->next = s->head;
    s->head = snode;
    return 0;
}

node* pop(stack *s) {
    stack_node *snode = s->head;
    node *n = s->head->data;
    s->head = s->head->next;
    free(snode);
    return n;
}

void clear_stack(stack *s) {
    stack_node *sn = s->head;

    while (sn != NULL) {
        stack_node *temp = sn->next;
        free(sn);
        sn = temp;
    }
    s->head = NULL;
}



//tree functions
void init(tree *t) {
    t->root = NULL;
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

    return 0;

}

void preorderTraversal(node *n) {
    if (n == NULL) {
        return;
    }

    stack *s = malloc(sizeof(stack));
    init_stack(s);
    push(s, n);

    while (s->head != NULL) {
        n = pop(s);
        printf("%d ", n->value);

        if (n->right != NULL) {
            push(s, n->right);
        }
        if (n->left != NULL) {
            push(s, n->left);
        }
        
        if (s->head != NULL) {
            printf(" ");
        }
    }
    printf("%c", '\n');
    clear_stack(s);
}

int main()
{
    tree *t = malloc(sizeof(tree));
    init(t);
    int n = 7;
    int a;

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a);
        insert(t, a);
    }

    preorderTraversal(t->root);
    clear(t);

    return 0;
}
