#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

/*
    Allocates memory and sets value, initially points next to NULL.
*/
node_t* create_node(int value)
{
    node_t *new_node = NULL;

    // NO ERROR CHECK
    new_node = (node_t*) malloc(sizeof(node_t));

    fprintf(stdout, "will create node with value %d\n", value);

    new_node->value = value;
    new_node->next = NULL;

    return (new_node);
}

/*
    Adds a node to the linked list.

    If position is 0 node will be added as the first node, returning the new first node.
    If position is -1 node will be added at the end of the linked list.
*/
node_t* add_node_to_list(int position, int value, node_t* list_entry)
{
    node_t* current_node = list_entry;
    node_t* new_node = NULL;
    int i = 0;

    fprintf(stdout, "will add node with value %d at position %d\n", value, position);
    new_node = create_node(value);

    // There is no node in the list yet.
    if (list_entry == NULL) {
        return (new_node);
    }

    // Create new entry node
    if (position == 0) {
        if (list_entry != NULL) {
            new_node->next = list_entry;
        }

        return (new_node);
    }

    while (current_node != NULL) {
        if (i == (position - 1)) {
            new_node->next = current_node->next;
            current_node->next = new_node;
        }

        if (position == -1 && current_node->next == NULL) {
            current_node->next = new_node;
            break;
        }
        // fprintf(stdout, "[%p] [%d: %d]\n", current_node, i, current_node->value);

        current_node = current_node->next;
        i++;
    }

    return (NULL);
}

/*
    Removes a node from the linked list.

    If position is 0 the first node will be removed and the new first node will be returned.
*/
node_t* remove_node_from_list(int position, node_t* list_entry)
{
    node_t* current_node = list_entry;
    node_t* hold_node = NULL;
    int i = 0;

    fprintf(stdout, "will remove node at position %d\n", position);

    if (position == 0) {
        list_entry = current_node->next;
        return (list_entry);
    }

    while (current_node != NULL) {
        if (i == (position - 1)) {
            hold_node = current_node;
        }

        if (i == position) {
            hold_node->next = current_node->next;
            free(current_node);
            break;
        }

        current_node = current_node->next;
        i++;
    }

    return (NULL);
}

/*
    Returns the number of elements from the linked list, first element will be 0.
*/
int list_length(node_t* list_entry)
{
    node_t* current_node = list_entry;
    int i = 0;

    while (current_node->next != NULL) {
        current_node = current_node->next;
        i++;
    }
    return(i);
}

/*
    Prints the address, the index and the value of every nodes and returns the
    number of elements from the linked list, first element will be 0.
*/
int traverse_list(node_t* list_entry)
{
    node_t* current_node = list_entry;
    int i = 0;

    while (current_node != NULL) {
        fprintf(stdout, "[%p] [%d: %d]\n", current_node, i, current_node->value);
        current_node = current_node->next;
        i++;
    }
    return(i);
}

int main()
{
    node_t *new_node = NULL;
    node_t *entry_node = NULL;

    fprintf(stdout, "\nsize of list node: %d\n\n", sizeof(node_t));

    new_node = add_node_to_list(-1, 15, entry_node);
    if (new_node != NULL) {
        entry_node = new_node;
    }
    // fprintf(stdout, "current new entry_node: %p\n", entry_node);

    new_node = add_node_to_list(1, 7, entry_node);
    if (new_node != NULL) {
        entry_node = new_node;
    }
    // fprintf(stdout, "current new entry_node: %p\n", entry_node);

    new_node = add_node_to_list(0, 9, entry_node);
    if (new_node != NULL) {
        entry_node = new_node;
    }

    fprintf(stdout, "--- LIST CONTENTS\n");
    traverse_list(entry_node);
    fprintf(stdout, "--- LIST CONTENTS\n");

    fprintf(stdout, "list length: %d\n", list_length(entry_node)+1);

    new_node = remove_node_from_list(1, entry_node);
    if (new_node != NULL) {
        entry_node = new_node;
    }

    new_node = add_node_to_list(-1, 18, entry_node);
    if (new_node != NULL) {
        entry_node = new_node;
    }

    fprintf(stdout, "--- LIST CONTENTS\n");
    traverse_list(entry_node);
    fprintf(stdout, "--- LIST CONTENTS\n");

    new_node = add_node_to_list(-1, 3, entry_node);
    if (new_node != NULL) {
        entry_node = new_node;
    }

    fprintf(stdout, "--- LIST CONTENTS\n");
    traverse_list(entry_node);
    fprintf(stdout, "--- LIST CONTENTS\n");

    fprintf(stdout, "list length: %d\n", list_length(entry_node)+1);

    exit(0);
}