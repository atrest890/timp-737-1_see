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

typedef struct queue_node {
    node *data;
    struct queue_node *next;
} queue_node;

typedef struct queue {
    queue_node *head;
    queue_node *tail;
} queue;


//queue functions
void init_queue(queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

int enqueue(queue *q, node *n) {
    queue_node *qn = malloc(sizeof(queue_node));
    qn->data = n;
    qn->next = NULL;

    if (q->head == NULL) {
        q->head = qn;
        q->tail = qn;
    }
    else {
        q->tail->next = qn;
        q->tail = qn;
    }

    return 0;
}

node* dequeue(queue *q) {
    queue_node *tmp = q->head;
    node *n = tmp->data;

    if (q->head == NULL) {
        return NULL;
    }

    q->head = tmp->next;
    free(tmp);

    return n;
}

void clear_queue(queue *q) {
    queue_node *qn = q->head;

    while (qn != NULL) {
        queue_node *temp = qn->next;
        free(qn);
        qn = temp;
    }
    q->head = NULL;
    q->tail = NULL;
}



//tree functions
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

void levelOrderTraversal(tree *t) {
    queue *q = malloc(sizeof(queue));
    init_queue(q);
    enqueue(q, t->root);

    while (q->head != NULL) {
        node *n = dequeue(q);
        printf("%d ", n->value);

        if (n->left != NULL) {
            enqueue(q, n->left);
        }
        if (n->right != NULL) {
            enqueue(q, n->right);
        }
        
        
        if (q->head != NULL) {
            printf(" ");
        }
    }
    printf("%c", '\n');
    clear_queue(q);
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

    levelOrderTraversal(t);
    clear(t);

    return 0;
}
