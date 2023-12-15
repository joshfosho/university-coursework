/* list.c */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

Node *new_node(const char *value) {
    Node *myNode = (Node *) malloc(sizeof(Node));

    if (myNode == NULL) {
        return NULL;
    }

    // Get length of the value string
    int length = 0;
    while (value[length] != '\0') {
        length++;
    }

    // Allocate memory and copy the string
    myNode->value = (char *) malloc((length + 1) * sizeof(char));

    // Verify memory allocation
    if (myNode->value == NULL) {
        free(myNode);
        return NULL;
    }

    // Copy the characters
    for (int i = 0; i <= length; i++) {
        myNode->value[i] = value[i];
    }

    myNode->next = NULL;

    return myNode;
}

void delete_node(Node *node) {

    // Free memory for string and node
    if (node != NULL) {
        free(node->value);
        free(node);

        // Set node to NULL as per criteria
        node = NULL;
    }
}

void push(List list, const char *value) {

    // Point to Node
    Node *current = *list;

    // Find element at end of list
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }

    // Set new Node to end of list
    Node *newNode = new_node(value);
    if (newNode != NULL) {
        if (current == NULL) {

            // Must update pointer
            *list = newNode;
        } else {
            current->next = newNode;
        }
    }
}

List new_list(void) {

    // Make list in memory
    List newList = (List) malloc(sizeof(Node *));

    // If succesfull set to NULL
    if (newList != NULL) {
        *newList = NULL;
    }
    return newList;
}

char *pop(List list) {

    // If List empty, nothing to return
    if (*list == NULL) {
        return NULL;
    }

    // Point to Node
    Node *current = *list;
    Node *previous = NULL;

    // Loop to get to last node
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    // Get value
    char *value = (char *) malloc(strlen(current->value) + 1);

    // Copy string over
    if (value != NULL) {
        for (size_t i = 0; current->value[i] != 0; i++) {
            value[i] = current->value[i];
        }
        // Remember null terminator
        value[strlen(current->value)] = '\0';
    }

    // Remove last node
    if (previous != NULL) {
        previous->next = NULL;
    } else {
        *list = NULL;  // The list had only one element
    }

    // Delete last node
    delete_node(current);

    return value;
}

void print_list(List list) {

    // Print opening bracket regardless
    printf("[");

    // Point to Node
    Node *current = *list;

    while (current != NULL) {
        // Print value REMEMBER QUOTES
        printf("\"%s\"", current->value);

        // Remember to print comma
        if (current->next != NULL) {
            printf(", ");
        }

        current = current->next;
    }

    // Add close bracket
    printf("]\n");
}

char *peek(List list) {

    // If List is empty, nothing to peek
    if (*list == NULL) {
        return NULL;
    }

    // Point to Node
    Node *current = *list;

    // Loop for last node
    while (current->next != NULL) {
        current = current->next;
    }

    // Get value
    char *value = (char *) malloc(strlen(current->value) + 1);

    // Copy the string over
    if (value != NULL) {
        for (size_t i = 0; current->value[i] != '\0'; i++) {
            value[i] = current->value[i];
        }
        value[strlen(current->value)] = '\0';
    }

    return value;
}

void add(List list, const char *value) {

    Node *newNode = new_node(value);
    if (newNode != NULL) {
        newNode->next = *list;
        *list = newNode;
    }
}

char *rem(List list) {

    // If list empty, nothing to remove
    if (*list == NULL) {
        return NULL;
    }

    // Point to Node
    Node *current = *list;
    *list = current->next;

    // Get value
    char *value = (char *) malloc(strlen(current->value) + 1);

    if (value != NULL) {
        // Copy the string over
        for (size_t i = 0; current->value[i] != '\0'; i++) {
            value[i] = current->value[i];
        }
        value[strlen(current->value)] = '\0';
    }

    // Delete last node
    delete_node(current);

    return value;
}

int size(List list) {

    // Initiate length
    int length = 0;

    // Point to node
    Node *current = *list;

    // Loop for counting elements
    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

int is_empty(List list) {

    // If size is 0, return 1 as its empty
    return (size(list) == 0) ? 1 : 0;
}

void clear(List list) {

    // Point to node
    Node *current = *list;
    Node *next;

    // Loop over to delete elements
    while (current != NULL) {
        next = current->next;
        delete_node(current);
        current = next;
    }

    *list = NULL;
}

int index_of(List list, const char *value) {

    int index = 0;

    // Point to node
    Node *current = *list;

    // Loop to get to element
    while (current != NULL) {

        // Use string compare function to compare values and return
        if (strcmp(current->value, value) == 0) {
            return index;
        }

        // Add and move over
        index++;
        current = current->next;
    }

    return -1;
}

int contains(List list, const char *value) {

    // Uses index function to check value
    return (index_of(list, value) != -1) ? 1 : 0;
}

char *get_at(List list, int index) {

    // Initiliase int
    int new_index = 0;

    // Point to node
    Node *current = *list;

    // Get element at index needed
    while (current != NULL && new_index < index) {
        new_index++;
        current = current->next;
    }

    // Make sure index will work
    if (new_index == index && current != NULL) {

        // Return current element
        return current->value;
    } else {
        return NULL;
    }
}

int replace_at(List list, int index, const char *new_value) {
    int current_index = 0;
    Node *current = *list;

    // Traverse the list to find the node at the specified index
    while (current != NULL && current_index < index) {
        current_index++;
        current = current->next;
    }

    // Check if the index is valid
    if (current_index == index && current != NULL) {
        // Allocate memory for the new value and copy it
        char *new_value_copy = strdup(new_value);
        if (new_value_copy == NULL) {
            return 0;  // Memory allocation failed
        }

        // Free the old value and replace it with the new value
        free(current->value);
        current->value = new_value_copy;

        return 1;  // Successful replacement
    } else {
        return 0;  // Index out of bounds or list is empty
    }
}
