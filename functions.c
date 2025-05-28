/*******************************************************************************************
* Programmer: Zachary Marseglia
* Class: CptS 122, Fall 2024; Lab Section 4
* Programming Assignment: PA2
* Date: September 6, 2024
* Description: This DMM program which allows user to select from a main menu.
*******************************************************************************************/
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024

/*********************************************************************
* Function: makeNode                                                *
* Description: Creates a new node for a doubly linked list with      *
*              the provided data.                                  *
* Input parameters: data - Record data to be stored in the node     *
* Returns: Pointer to the newly created node                        *
* Preconditions: None                                             *
* Postconditions: A new node is allocated and initialized            *
*********************************************************************/
Node* makeNode(Record data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}

/*********************************************************************
* Function: insertFront                                             *
* Description: Inserts a new node at the front of the doubly linked  *
*              list.                                                *
* Input parameters: head - Pointer to the head of the list           *
*                   data - Record data to be inserted                *
* Returns: None                                                     *
* Preconditions: None                                             *
* Postconditions: A new node is added to the front of the list        *
*********************************************************************/
void insertFront(Node** head, Record data) {
    Node* newNode = makeNode(data);
    if (newNode) {
        newNode->next = *head;
        if (*head) {
            (*head)->prev = newNode;
        }
        *head = newNode;
    }
}
/*********************************************************************
* Function: trimQuotes                                              *
* Description: Removes surrounding double quotes from a string. will*
need to be fixed for PA3 causes the duration of songs to be wrong   *
* Input parameters: str - String to be trimmed                      *
* Returns: None                                                     *
* Preconditions: String should be non-null and have surrounding     *
*                quotes                                             *
* Postconditions: The string is modified to remove quotes            *
*********************************************************************/
void trimQuotes(char* str) {
    size_t len = strlen(str);

    if (len > 0 && str[0] == '"') {
        memmove(str, str + 1, len - 1);  //from https://www.tutorialspoint.com/c_standard_library/c_function_memmove.htm
        len--;  
    }

    if (len > 0 && str[len - 1] == '"') {
        str[len - 1] = '\0';  
    }
    else {
        while (len > 0 && str[len - 1] == ' ') {
            str[len - 1] = '\0';
            len--;
        }
    }
}


/*********************************************************************
* Function: parseCSVLine                                            *
* Description: Parses a line of CSV data and fills a Record struct.  *
* Input parameters: line - Line of CSV data                          *
*                   record - Pointer to Record struct to be filled    *
* Returns: 1 if parsing successful, 0 otherwise                       *
* Preconditions: Line must be a valid CSV format                     *
* Postconditions: Record struct is populated with parsed data         *
*********************************************************************/


void removeSurroundingQuotes(char* str) {
    size_t len = strlen(str);

    if (len > 0 && str[0] == '"') {
        memmove(str, str + 1, len - 1);  
        len--;
    }

    if (len > 0 && str[len - 1] == '"') {
        str[len - 1] = '\0';  
    }
}

/*********************************************************************
* Function: parseCSVLine                                            *
* Description: Parses a line of CSV data and fills a Record struct.  *
* Input parameters: line - Line of CSV data record - Pointer to Record *
*  struct to be filled-heavely modified this from PA2                 *
* Returns: 1 if parsing successful, 0 otherwise                       *
* Preconditions: Line must be a valid CSV format                     *
* Postconditions: Record struct is populated with parsed data         *
*********************************************************************/
int parseCSVLine(char* line, Record* record) {
    char buffer[1024];
    int bufferIndex = 0;
    int field = 0;
    bool insideQuotes = false;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"') {
            insideQuotes = !insideQuotes;  
        }
        else if (line[i] == ',' && !insideQuotes) {
            buffer[bufferIndex] = '\0'; 

            switch (field) {
            case 0:
                strncpy(record->artist, buffer, sizeof(record->artist) - 1);
                record->artist[sizeof(record->artist) - 1] = '\0';
                removeSurroundingQuotes(record->artist);  
                break;
            case 1:
                strncpy(record->albumTitle, buffer, sizeof(record->albumTitle) - 1);
                record->albumTitle[sizeof(record->albumTitle) - 1] = '\0';
                break;
            case 2:
                strncpy(record->songTitle, buffer, sizeof(record->songTitle) - 1);
                record->songTitle[sizeof(record->songTitle) - 1] = '\0';
                break;
            case 3:
                strncpy(record->genre, buffer, sizeof(record->genre) - 1);
                record->genre[sizeof(record->genre) - 1] = '\0';
                break;
            case 4: {
                int minutes, seconds;
                sscanf(buffer, "%d:%d", &minutes, &seconds); 
                record->songLength.minutes = minutes;
                record->songLength.seconds = seconds;
                break;
            }
            case 5:
                record->timesPlayed = atoi(buffer);
                break;
            case 6:
                record->rating = atoi(buffer);
                break;
            default:
                break;
            }

            field++;
            bufferIndex = 0; 
        }
        else {
            buffer[bufferIndex++] = line[i];
        }
    }

    buffer[bufferIndex] = '\0'; 
    if (field == 6) {
        record->rating = atoi(buffer);
    }

    return 1;  
}

/*********************************************************************
* Function: printList                                               *
* Description: Prints all records in the doubly linked list.         *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Records are printed to the standard output          *
*********************************************************************/
void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("Artist: %s, Album: %s, Song: %s, Genre: %s, Length: %d:%02d, Played: %d, Rating: %d\n",
            current->data.artist, current->data.albumTitle, current->data.songTitle, current->data.genre,
            current->data.songLength.minutes, current->data.songLength.seconds,
            current->data.timesPlayed, current->data.rating);
        current = current->next;
    }
}

/*********************************************************************
* Function: load                                                     *
* Description: Loads data from a CSV file into a doubly linked list. *
* Input parameters: head - Pointer to the head of the list           *
*                   filename - Name of the CSV file to be loaded      *
* Returns: None                                                     *
* Preconditions: File must be in CSV format and accessible           *
* Postconditions: List is populated with data from the file           *
*********************************************************************/
void load(Node** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char buffer[MAX_LINE_LENGTH];
        while (fgets(buffer, sizeof(buffer), file)) {
            Record record;
            memset(&record, 0, sizeof(record));// from https://www.tutorialspoint.com/c_standard_library/c_function_memset.htm

            if (parseCSVLine(buffer, &record)) {
                insertFront(head, record);
            }
            else {
                printf("Failed to parse record: %s\n", buffer);
            }
        }
        fclose(file);
    }
    else {
        printf("Failed to open file: %s\n", filename);
    }
}

/*********************************************************************
* Function: store                                                    *
* Description: Stores data from the doubly linked list back into a   *
*              CSV file.                                            *
* Input parameters: head - Pointer to the head of the list           *
*                   filename - Name of the CSV file to be written to *
* Returns: None                                                     *
* Preconditions: File should be writable                            *
* Postconditions: Data from the list is written to the file           *
*********************************************************************/
void store(Node* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        Node* current = head;
        while (current) {
            fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d\n",
                current->data.artist, current->data.albumTitle, current->data.songTitle, current->data.genre,
                current->data.songLength.minutes, current->data.songLength.seconds,
                current->data.timesPlayed, current->data.rating);
            current = current->next;
        }
        fclose(file);
    }
    else {
        printf("Failed to open file: %s\n", filename);
    }
}

/*********************************************************************
* Function: display                                                 *
* Description: Displays records from the list based on user choice.  *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Records are printed based on user choice           *
*********************************************************************/
void display(Node* head) {
    int choice;
    char artist[50];

    printf("Choose display option:\n");
    printf("1. Display all records\n");
    printf("2. Display records by artist\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  

    if (choice == 1) {
        Node* temp = head;
        while (temp != NULL) {
            printf("Artist: %s\n", temp->data.artist);
            printf("Album: %s\n", temp->data.albumTitle);
            printf("Song: %s\n", temp->data.songTitle);
            printf("Genre: %s\n", temp->data.genre);
            printf("Duration: %d:%02d\n", temp->data.songLength.minutes, temp->data.songLength.seconds);
            printf("Plays: %d\n", temp->data.timesPlayed);
            printf("Rating: %d\n", temp->data.rating);
            printf("----------------------\n");
            temp = temp->next;
        }
    }
    else if (choice == 2) {
        printf("Enter the artist's name: ");
        fgets(artist, sizeof(artist), stdin);
        artist[strcspn(artist, "\n")] = 0;  

        Node* temp = head;
        int found = 0;
        while (temp != NULL) {
            if (strcmp(temp->data.artist, artist) == 0) {
                printf("Artist: %s\n", temp->data.artist);
                printf("Album: %s\n", temp->data.albumTitle);
                printf("Song: %s\n", temp->data.songTitle);
                printf("Genre: %s\n", temp->data.genre);
                printf("Duration: %d:%02d\n", temp->data.songLength.minutes, temp->data.songLength.seconds);
                printf("Plays: %d\n", temp->data.timesPlayed);
                printf("Rating: %d\n", temp->data.rating);
                printf("----------------------\n");
                found = 1;
            }
            temp = temp->next;
        }
        if (!found) {
            printf("No records found for artist: %s\n", artist);
        }
    }
    else {
        printf("Invalid choice. Returning to main menu.\n");
    }
}

/*********************************************************************
* Function: edit                                                    *
* Description: Allows editing of a specific record in the list.       *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Record specified by song title is edited            *
*********************************************************************/
void edit(Node* head) {
    char songTitle[50];
    printf("Enter the song title to edit: ");
    fgets(songTitle, sizeof(songTitle), stdin);
    songTitle[strcspn(songTitle, "\n")] = 0;  

    Node* temp = head;
    while (temp) {
        if (strcmp(temp->data.songTitle, songTitle) == 0) {
            int choice;
            printf("Editing song: %s\n", songTitle);
            printf("Choose field to edit:\n");
            printf("1. Artist\n2. Album\n3. Song Title\n4. Genre\n5. Length\n6. Times Played\n7. Rating\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();  

            switch (choice) {
            case 1:
                printf("Enter new artist: ");
                fgets(temp->data.artist, sizeof(temp->data.artist), stdin);
                temp->data.artist[strcspn(temp->data.artist, "\n")] = 0;  
                break;
            case 2:
                printf("Enter new album: ");
                fgets(temp->data.albumTitle, sizeof(temp->data.albumTitle), stdin);
                temp->data.albumTitle[strcspn(temp->data.albumTitle, "\n")] = 0;  
                break;
            case 3:
                printf("Enter new song title: ");
                fgets(temp->data.songTitle, sizeof(temp->data.songTitle), stdin);
                temp->data.songTitle[strcspn(temp->data.songTitle, "\n")] = 0;  
                break;
            case 4:
                printf("Enter new genre: ");
                fgets(temp->data.genre, sizeof(temp->data.genre), stdin);
                temp->data.genre[strcspn(temp->data.genre, "\n")] = 0;  
                break;
            case 5:
                printf("Enter new length (minutes seconds): ");
                scanf("%d %d", &temp->data.songLength.minutes, &temp->data.songLength.seconds);
                break;
            case 6:
                printf("Enter new times played: ");
                scanf("%d", &temp->data.timesPlayed);
                break;
            case 7:
                printf("Enter new rating: ");
                scanf("%d", &temp->data.rating);
                break;
            default:
                printf("Invalid choice.\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("Song not found: %s\n", songTitle);
}

/*********************************************************************
* Function: rate                                                     *
* Description: Allows rating a specific song in the list.            *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Rating of the specified song is updated            *
*********************************************************************/
void rate(Node* head) {
    char songTitle[50];
    int newRating;

    printf("Enter the song title to rate: ");
    fgets(songTitle, sizeof(songTitle), stdin);
    songTitle[strcspn(songTitle, "\n")] = 0;  

    Node* temp = head;
    while (temp) {
        if (strcmp(temp->data.songTitle, songTitle) == 0) {
            do {
                printf("Enter the new rating (1-5): ");
                scanf("%d", &newRating);
                if (newRating < 1 || newRating > 5) {
                    printf("Invalid rating! Please enter a value between 1 and 5.\n");
                }
            } while (newRating < 1 || newRating > 5);

            temp->data.rating = newRating;
            printf("Updated rating for song '%s' to %d.\n", songTitle, newRating);
            return;
        }
        temp = temp->next;
    }
    printf("Song not found: %s\n", songTitle);
}

/*********************************************************************
* Function: play                                                     *
* Description: Plays all songs starting from a specific song in the   *
*              list.                                                *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Songs are played starting from the specified song   *
*********************************************************************/
void play(Node* head) {
    char songTitle[50];
    int found = 0;

    printf("Enter the song title to start playing from: ");
    fgets(songTitle, sizeof(songTitle), stdin);
    songTitle[strcspn(songTitle, "\n")] = 0;  

    Node* temp = head;
    while (temp) {
        if (strcmp(temp->data.songTitle, songTitle) == 0) {
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Song not found: %s\n", songTitle);
        return;
    }

    while (temp) {
        printf("Now Playing:\n");
        printf("Artist: %s\n", temp->data.artist);
        printf("Album: %s\n", temp->data.albumTitle);
        printf("Song: %s\n", temp->data.songTitle);
        printf("Genre: %s\n", temp->data.genre);
        printf("Duration: %d:%02d\n", temp->data.songLength.minutes, temp->data.songLength.seconds);
        printf("Plays: %d\n", temp->data.timesPlayed);
        printf("Rating: %d\n", temp->data.rating);
        printf("----------------------\n");
        system("cls");

        temp = temp->next;
    }

    printf("All songs have been played.\n");
}

/*********************************************************************
* Function: deleteNode                                              *
* Description: Deletes a node from the doubly linked list based on   *
*              the song title.                                      *
* Input parameters: head - Pointer to the head of the list           *
*                   songTitle - Title of the song to be deleted       *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: Node with the specified song title is removed from   *
*                the list                                            *
*********************************************************************/
void deleteNode(Node** head, const char* songTitle) {
    Node* temp = *head;
    while (temp) {
        if (strcmp(temp->data.songTitle, songTitle) == 0) {
            if (temp->prev) {
                temp->prev->next = temp->next;
            }
            else {
                *head = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Deleted song: %s\n", songTitle);
            return;
        }
        temp = temp->next;
    }
    printf("Song not found: %s\n", songTitle);
}

/*********************************************************************
* Function: sortByArtist                                            *
* Description: Sorts the doubly linked list by artist name.          *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on artist name                *
*********************************************************************/
void sortByArtist(Node** head) {
    if (*head == NULL) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data.artist, ptr1->next->data.artist) > 0) {
                Record temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
/*********************************************************************
* Function: sortByAlbum                                             *
* Description: Sorts the doubly linked list by album title (A-Z).    *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on album title                *
*********************************************************************/void sortByAlbum(Node** head) {
    if (*head == NULL) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data.albumTitle, ptr1->next->data.albumTitle) > 0) {
                Record temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

/*********************************************************************
* Function: sortByRating                                            *
* Description: Sorts the doubly linked list by rating (1-5).         *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on rating                     *
*********************************************************************/void sortByRating(Node** head) {
    if (*head == NULL) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->data.rating > ptr1->next->data.rating) {
                Record temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

/*********************************************************************
* Function: sortByTimesPlayed                                       *
* Description: Sorts the doubly linked list by times played (largest)*
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: List is sorted based on times played               *
*********************************************************************/
void sortByTimesPlayed(Node** head) {
    if (*head == NULL) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->data.timesPlayed < ptr1->next->data.timesPlayed) {
                Record temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

/*******************************************************************************************
 * Function: handleInsert
 * Description: Prompts the user for song details and inserts a new record at the front of the list.
 * Input parameters:
 *    - Node** head: Pointer to the head of the linked list
 * Returns: None
 *******************************************************************************************/
void handleInsert(Node** head) {
    Record newRecord;

    printf("Enter artist name: ");
    fgets(newRecord.artist, sizeof(newRecord.artist), stdin);
    newRecord.artist[strcspn(newRecord.artist, "\n")] = 0;

    printf("Enter album title: ");
    fgets(newRecord.albumTitle, sizeof(newRecord.albumTitle), stdin);
    newRecord.albumTitle[strcspn(newRecord.albumTitle, "\n")] = 0;

    printf("Enter song title: ");
    fgets(newRecord.songTitle, sizeof(newRecord.songTitle), stdin);
    newRecord.songTitle[strcspn(newRecord.songTitle, "\n")] = 0;

    printf("Enter genre: ");
    fgets(newRecord.genre, sizeof(newRecord.genre), stdin);
    newRecord.genre[strcspn(newRecord.genre, "\n")] = 0;

    printf("Enter song length (minutes seconds): ");
    scanf("%d %d", &newRecord.songLength.minutes, &newRecord.songLength.seconds);
    getchar();  // Clear newline

    printf("Enter number of times played: ");
    scanf("%d", &newRecord.timesPlayed);
    getchar();

    printf("Enter rating (1-5): ");
    scanf("%d", &newRecord.rating);
    getchar();

    insertFront(head, newRecord);
}

/*******************************************************************************************
 * Function: handleDelete
 * Description: Prompts the user for a song title and deletes the corresponding node from the list.
 * Input parameters:
 *    - Node** head: Pointer to the head of the linked list
 * Returns: None
 *******************************************************************************************/
void handleDelete(Node** head) {
    char songTitle[50];
    printf("Enter the song title to delete: ");
    fgets(songTitle, sizeof(songTitle), stdin);
    songTitle[strcspn(songTitle, "\n")] = 0;  // Remove newline character

    deleteNode(head, songTitle);
}

/*********************************************************************
* Function: freeList                                                *
* Description: Frees all nodes in the doubly linked list.            *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: All nodes are deallocated and list is emptied       *
*********************************************************************/
void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*********************************************************************
* Function: shuffle                                                 *
* Description: Shuffles the records in a random order without        *
*              modifying the links of the doubly linked list.        *
* Input parameters: head - Pointer to the head of the list           *
* Returns: None                                                     *
* Preconditions: List should be non-null                            *
* Postconditions: The records are shuffled in a random order          *
*********************************************************************/
void shuffle(Node* head) {
    if (!head) return;

    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    Node** nodeArray = (Node**)malloc(count * sizeof(Node*));
    if (nodeArray == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    temp = head;
    for (int i = 0; i < count; i++) {
        nodeArray[i] = temp;
        temp = temp->next;
    }

    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Node* swap = nodeArray[i];
        nodeArray[i] = nodeArray[j];
        nodeArray[j] = swap;
    }

    printf("Shuffled songs:\n");
    for (int i = 0; i < count; i++) {
        printf("Now Playing: %s - %s\n", nodeArray[i]->data.artist, nodeArray[i]->data.songTitle);
    }

    free(nodeArray);
}
