/*******************************************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 122, Fall 2024; Lab Section 4
* Programming Assignment: PA2
* Date: September 6, 2024
* Description: This DMM program which allows user to select from a main menu.
*******************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H

typedef struct Duration {
    int minutes;
    int seconds;
} Duration;

typedef struct Record {
    char artist[50];
    char albumTitle[50];
    char songTitle[50];
    char genre[50];
    Duration songLength;
    int timesPlayed;
    int rating;
} Record;

typedef struct Node {
    Record data;
    struct Node* next;
    struct Node* prev;
} Node;

/*********************************************************************
* Function: makeNode                                                *
* Description: Creates a new node for a doubly linked list with      *
*              the provided data.                                  *
* Input parameters: data - Record data to be stored in the node     *
* Returns: Pointer to the newly created node                        *
* Preconditions: None                                               *
* Postconditions: A new node is allocated and initialized            *
*********************************************************************/
Node* makeNode(Record data);

/*********************************************************************
* Function: insertFront                                             *
* Description: Inserts a new node at the front of the doubly linked  *
*              list.                                                *
* Input parameters: head - Pointer to the head of the list           *
*                   data - Record data to be inserted                *
* Returns: None                                                     *
* Preconditions: None                                               *
* Postconditions: A new node is added to the front of the list        *
*********************************************************************/
void insertFront(Node** head, Record data);

/*********************************************************************
* Function: printList                                               *
* Description: Prints all records in the doubly linked list.         *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Records are printed to the standard output         *
*********************************************************************/
void printList(Node* head);

/*********************************************************************
* Function: load                                                    *
* Description: Loads data from a CSV file into a doubly linked list. *
* Input parameters: head - Pointer to the head of the list           *
*                   filename - Name of the CSV file to be loaded     *
* Returns: None                                                     *
* Preconditions: File must be in CSV format and accessible           *
* Postconditions: List is populated with data from the file          *
*********************************************************************/
void load(Node** head, const char* filename);

/*********************************************************************
* Function: store                                                   *
* Description: Stores data from the doubly linked list back into a   *
*              CSV file.                                             *
* Input parameters: head - Pointer to the head of the list           *
*                   filename - Name of the CSV file to be written to *
* Returns: None                                                     *
* Preconditions: File should be writable                            *
* Postconditions: Data from the list is written to the file          *
*********************************************************************/
void store(Node* head, const char* filename);

/*********************************************************************
* Function: display                                                 *
* Description: Displays records from the list based on user choice.  *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Records are printed based on user choice           *
*********************************************************************/
void display(Node* head);

/*********************************************************************
* Function: edit                                                    *
* Description: Allows editing of a specific record in the list.      *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Record specified by song title is edited           *
*********************************************************************/
void edit(Node* head);

/*********************************************************************
* Function: rate                                                    *
* Description: Allows rating a specific song in the list.            *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Rating of the specified song is updated            *
*********************************************************************/
void rate(Node* head);

/*********************************************************************
* Function: play                                                    *
* Description: Plays all songs starting from a specific song in the  *
*              list.                                                 *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Songs are played starting from the specified song  *
*********************************************************************/
void play(Node* head);

/*********************************************************************
* Function: deleteNode                                              *
* Description: Deletes a node from the doubly linked list based on   *
*              the song title.                                       *
* Input parameters: head - Pointer to the head of the list           *
*                   songTitle - Title of the song to be deleted      *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Node with the specified song title is removed      *
*********************************************************************/
void deleteNode(Node** head, const char* songTitle);

/*********************************************************************
* Function: sortByArtist                                            *
* Description: Sorts the doubly linked list by artist name.          *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on artist name                *
*********************************************************************/
void sortByArtist(Node** head);

/*********************************************************************
* Function: sortByAlbum                                             *
* Description: Sorts the doubly linked list by album title.          *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on album title                *
*********************************************************************/
void sortByAlbum(Node** head);

/*********************************************************************
* Function: sortByRating                                            *
* Description: Sorts the doubly linked list by rating (1-5).         *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on rating                     *
*********************************************************************/
void sortByRating(Node** head);

/*********************************************************************
* Function: sortByTimesPlayed                                       *
* Description: Sorts the doubly linked list by times played          *
*              (largest to smallest).                               *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on times played               *
*********************************************************************/
void sortByTimesPlayed(Node** head);

/*********************************************************************
* Function: freeList                                                *
* Description: Frees all nodes in the doubly linked list.            *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: All nodes are deallocated and list is emptied      *
*********************************************************************/
void freeList(Node* head);
/*******************************************************************************************
 * Function: handleInsert
 * Description: Prompts the user for song details and inserts a new record at the front of the list.
 * Input parameters:
 *    - Node** head: Pointer to the head of the linked list
 * Returns: None
 *******************************************************************************************/
void handleInsert(Node** head);
/*********************************************************************
* Function: shuffle                                                 *
* Description: Shuffles the records in a random order without        *
*              modifying the links of the doubly linked list.        *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: The records are shuffled in a random order         *
*********************************************************************/
/*******************************************************************************************
 * Function: handleDelete
 * Description: Prompts the user for a song title and deletes the corresponding node from the list.
 * Input parameters:
 *    - Node** head: Pointer to the head of the linked list
 * Returns: None
 *******************************************************************************************/
void handleDelete(Node** head);
void shuffle(Node* head);

#endif
