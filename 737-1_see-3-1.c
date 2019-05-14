#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct {
    struct node *head;
    struct node *tail;
} list;

void init(list *l) {
    l->head = NULL;
    l->tail = NULL;
}

void clear(list *l) {
    node *n = l->head;

    while (n != NULL) {
        node *temp = n->next;
        free(n);
        n = temp;
    }
    l->head = NULL;
    l->tail = NULL;
}

int isEmpty(list *l) {
    if (l->head == NULL) {
        return 1;
    }
    return 0;
}

node* find(list *l, int value) {
    node *n = l->head;

    while (n != NULL && n->value != value) {
        n = n->next;
    }

    return n;
}

int push_back(list *l, int value) {
    node *n = malloc(sizeof(node));
    n->value = value;
    n->next = NULL;
    node *p = l->tail;

    if ( isEmpty(l) ) {
        l->head = n;
        l->tail = n;
    }
    else {
        p->next = n;
        l->tail = n;
    }

    return 0;
}

int push_front(list *l, int value) {
    node *n = malloc(sizeof(node));
    n->value = value;
    n->next = NULL;

    if ( isEmpty(l) ) {
        l->head = n;
        l->tail = n;
    }
    else {
        n->next = l->head;
        l->head = n;
    }

    return 0;

}

int insertAfter(node *n, int value) {
    node *p = malloc(sizeof(node));
    p->value = value;
    p->next = n->next;
    n->next = p;
    return 0;
}

//функция переименована из-за конфликта имен с функцией из stdio.h
int remove_node(list *l, int value) {
    node *prev = NULL;
    node *curr = l->head;

    while (curr != NULL && curr->value != value) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return -1;
    }

    if (curr == l->head) {
        l->head = curr->next;
    }
    if (curr == l->tail) {
        l->tail = prev;
    }
    if (prev != NULL) {
        prev->next = curr->next;
    }

    free(curr);

    return 0;
}

void print(list *l) {
    node *temp = l->head;

    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("%c", '\n');
}

int main() {
    list *lst = malloc(sizeof(list));
    int n, a;

    // task 1
    scanf("%d\n", &n);
    init(lst);

    //task 2
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a);
        push_back(lst, a);
    }
    //task 3
    print(lst);

    //task 4
    int nodes[3] = {};
    scanf("%d %d %d", &nodes[0], &nodes[1], &nodes[2]);

    for (int i = 0; i < 3; ++i) {
        node *n = find(lst, nodes[i]);

        if (n != NULL) {
            printf("%d", 1);
        }
        else {
            printf("%d", 0);
        }
    }
    printf("%c", '\n');

    //task 5
    int m;
    scanf("%d", &m);
    push_back(lst, m);
    //task 6
    print(lst);

    //task 7
    int t;
    scanf("%d", &t);
    push_front(lst, t);
    //task 8
    print(lst);

    //task 9
    int j, x;
    scanf("%d %d", &j, &x);
    node *p = lst->head;

    for (int i = 1; i < j; ++i) {
        p = p->next;
    }

    insertAfter(p, x);

    //task 10
    print(lst);

    //task 11
    int z;
    scanf("%d", &z);
    remove_node(lst, z);

    //task 12
    print(lst);

    //task 13
    clear(lst);

    return 0;
}
