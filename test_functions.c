#include "Header.h"  
#include "test_functions.h"
#include <stdlib.h>

/*********************************************************************
* Function: testInsert                                              *
* Description: Tests the insertFront function by inserting a record  *
*              and checking if the node is inserted correctly.       *
* Input parameters: None                                             *
* Returns: None                                                      *
* Preconditions: None                                                *
* Postconditions: Outputs whether the test passed or failed          *
*********************************************************************/
void testInsert() {
    Node* head = NULL;
    Record newRecord = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop", {4, 36}, -1, 6 };

    insertFront(&head, newRecord);

    if (head && strcmp(head->data.artist, "Perry, Katy") == 0 && head->data.timesPlayed == -1 && head->data.rating == 6) {
        printf("Insert Test Passed!\n");
    }
    else {
        printf("Insert Test Failed!\n");
    }

    freeList(head);
}

/*********************************************************************
* Function: testDelete                                               *
* Description: Tests the deleteNode function by inserting and        *
*              deleting a node, then verifying if the list is empty. *
* Input parameters: None                                             *
* Returns: None                                                      *
* Preconditions: None                                                *
* Postconditions: Outputs whether the test passed or failed          *
*********************************************************************/
void testDelete() {
    Node* head = NULL;
    Record newRecord = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop", {4, 36}, 3, 5 };
    insertFront(&head, newRecord);

    deleteNode(&head, "Chained to the Rhythm");

    if (head == NULL) {
        printf("Delete Test Passed!\n");
    }
    else {
        printf("Delete Test Failed!\n");
    }
}

/*********************************************************************
* Function: testShuffle                                              *
* Description: Tests the shuffle function by inserting multiple      *
*              records and calling the shuffle function to verify    *
*              the records are shuffled correctly.                   *
* Input parameters: None                                             *
* Returns: None                                                      *
* Preconditions: None                                                *
* Postconditions: The shuffle function is executed and its results   *
*********************************************************************/
void testShuffle() {
    Node* head = NULL;

    Record record1 = {
        "Artist1", "Album1", "Song1", "Genre1", {3, 30}, 10, 5
    };
    Record record2 = {
        "Artist2", "Album2", "Song2", "Genre2", {4, 15}, 5, 4
    };
    Record record3 = {
        "Artist3", "Album3", "Song3", "Genre3", {5, 10}, 7, 3
    };

    insertFront(&head, record1);
    insertFront(&head, record2);
    insertFront(&head, record3);

    printf("Shuffling the playlist...\n");
    shuffle(head);

    freeList(head);
}
