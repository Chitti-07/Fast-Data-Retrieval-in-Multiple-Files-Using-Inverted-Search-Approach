#include "invert.h"

/* Function to display data base */
void display_DataBase(Hash* hash) {
    /* Check if the hash table is empty */
    int i;
    for (i = 0; i < 28; i++) {

        if (hash[i].link != NULL) {
            break;
        }
    }
    /*If not empty, Then display it */
    if (i < 28) {
        /* Iterate through every index */
        for (i = 0; i < 28; i++) {
            /* If the index link is null, Then continue */
            if (hash[i].link == NULL) {
                continue;
            }
            /* If the index link is not null, Then print the data */
            main_node* temp = hash[i].link;
            /* Iterate through the main link */
            while (temp != NULL) {
                /* Iterate through the sublink, and print the data present in subnode */
                sub_node* subTemp = temp->Slink;
                printf("[%d] ->  word = %s\t%d  ", i, temp->word, temp->file_count);
                while (subTemp != NULL) {
                    printf("%s\t%d times ", subTemp->file_name, subTemp->wordCount);
                    /* Updating the subnode */
                    subTemp = subTemp->Slink;
                }
                printf("\n");
                /* Updating the main node */
                temp = temp->Mlink;
            }
        }
    /* If hash is empty, print the below */  
    }else {
        printf("DataBase is empty\n");
        return;
    }
}