#include "invert.h"

/* Function to search a word in database */
void search_DataBase(Hash* hashT) {
    /* Check if the database is empty or not */
    int i;
    for (i = 0; i < 28; i++) {
        if (hashT[i].link != NULL) {
            break;
        }
    }
    /* If it is not empty, Then search for the word */
    if (i < 28) {
        /* Reading the word from user */
        char word[SIZE];
        printf("Enter the word to search: ");
        scanf("%s", word);
        /* Finding the index */
        int index;
        /* If the word entered is number, then index is 26 */
        if (isdigit(word[0])) {
            index = 26;
        /* If the word entered is special character, then index is 27 */
        }else if (ispunct(word[0])) {
            index = 27;
        /* If the word is alphabetical word, Then find the index */
        }else {
            index = (tolower(word[0]) % 97);
        }
        /* If the index link is null, Then there is no word present in database */
        if (hashT[index].link == NULL) {
            printf("%s is not found in dataBase\n", word);
            return;
        /* If the index link is not null, Then search for that word */
        }else {
            /* Create a main node and point it to index link */
            main_node* tempMainNode = hashT[index].link;
            /* Find the main link where the word matches */
            while (tempMainNode != NULL && strcasecmp(tempMainNode->word, word) != 0) {
                tempMainNode = tempMainNode->Mlink;
            }
            /* If the word is found, then print the information */
            if (tempMainNode != NULL) {
                printf("FileCount %d ", tempMainNode->file_count);
                sub_node* subTemp = tempMainNode->Slink;
                /* Iterate through file count times */
                for (int i = 0; i < tempMainNode->file_count; i++) {
                    printf("FileName %s WordCount %d ", subTemp->file_name, subTemp->wordCount);
                    subTemp = subTemp->Slink;
                }
                printf("\n");
            }else {
                printf("%s is not found in data base\n", word);
                return;
            }
        }
    /* If the database is empty, print the below */
    }else {
        printf("DataBase is empty\n");
        return;
    }
}