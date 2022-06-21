#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

struct node_s {
    int value;
    struct node_s *next;
};
typedef struct node_s node_t;

node_t *insertsort(int *numbers, int count);
void delete_nodes(node_t *head);

int main(void)
{
    int *score = NULL;
    node_t *head = NULL, *f = NULL;
    float median;
    int no_students, i;

    cout << "Öðrenci sayýsý: ";
    cin >> no_students;
    score = new int[no_students];

    for (i = 0; i < no_students; i++) {
        cout << i + 1 << ". öðrencinin notu: ";
        cin >> score[i];
    }

    head = insertsort(score, no_students);

    f = head;
    for (i = 0; i < no_students / 2 - 1; i++)
        f = f->next;
    median = (no_students % 2 == 1) ? f->next->value :
                 (f->value + f->next->value) / 2.0;
    cout << "Orta deðer: " << median << endl;

    delete_nodes(head);

    delete score;
    return EXIT_SUCCESS;
}

node_t *insert(node_t *head, int v)
{
    node_t *p = head, *newnode = NULL, *last = NULL;

    newnode = new node_t;
    newnode->value = v;
    while ((p != NULL) && (p->value < v)) {
        last = p;
        p = p->next;
    }
    newnode->next = p;
    if (last == NULL)
        return newnode;
    last->next = newnode;
    return head;
}

node_t *insertsort(int *numbers, int count)
{
    node_t *head = NULL;
    int i;

    for (i = 0; i < count; i++)
        head = insert(head, numbers[i]);
    return head;
}

void delete_nodes(node_t *head)
{
    node_t *p = NULL;

    while (head != NULL) {
        p = head->next;
        delete head;
        head = p;
    }
}
