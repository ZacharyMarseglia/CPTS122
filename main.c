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
#include <time.h>

int main() {
    Node* head = NULL;
    int choice;
    char filename[] = "musicPlayList.csv";

    load(&head, filename);

    do {
        printf("\nMain Menu:\n");
        printf("1. Load\n");
        printf("2. Store\n");
        printf("3. Display\n");
        printf("4. Insert\n");
        printf("5. Delete\n");
        printf("6. Edit\n");
        printf("7. Sort by artist\n");
        printf("8. Rate\n");
        printf("9. Play\n");
        printf("10. Shuffle\n");
        printf("11. Sort by album\n");
        printf("12. Sort by rating\n");
        printf("13. Sort by times played\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
        case 1:
            load(&head, filename);
            break;
        case 2:
            store(head, filename);
            break;
        case 3:
            display(head);
            break;
        case 4:
            handleInsert(&head);
            break;
        case 5:
            handleDelete(&head);
            break;
        case 6:
            edit(head);
            break;
        case 7:
            sortByArtist(&head);
            break;
        case 8:
            rate(head);
            break;
        case 9:
            play(head);
            break;
        case 10:
            shuffle(head);
            break;
        case 11:
            sortByAlbum(&head);
            break;
        case 12:
            sortByRating(&head);
            break;
        case 13:
            sortByTimesPlayed(&head);
            break;
        case 14:
            store(head, filename);
            freeList(head);
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 14);

    return 0;
}
