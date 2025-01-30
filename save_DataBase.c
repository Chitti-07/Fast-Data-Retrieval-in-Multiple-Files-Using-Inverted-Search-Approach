#include "invert.h"

/* Function to save the database to a file */
int save_DataBase(Hash* hash) {

    /* Check it the hash/database is empty or not */
    int i;
    for (i = 0; i < 28; i++) {
        if (hash[i].link != NULL) {
            break;
        }
    }


    /* If not empty, Then save the data to a file */
    if (i < 28) {

        /* getting file name from the user */
        char file[SIZE];
        printf("Enter the file name: ");
        scanf("%s", file);

        /* Check whether the emtered file is valid or not */
        char* fileExtn = strcasestr(file, ".txt");
        if (fileExtn == NULL || strcasecmp(fileExtn, ".txt") != 0) {
            printf("Error: %s should have a \".txt\" extension\n", file);
            return FAILURE;
        }

        /* If it is a valid file, open it */
        FILE* fptr = fopen(file, "w");
        if (fptr == NULL) {
            printf("Error: Unable to open file for writing.\n");
            return FAILURE;
        }

        /* Iterate through the hash */
        for (int i = 0; i < 28; i++) {

            /* If the hash link is null, skip it */
            if (hash[i].link == NULL) {
                continue;
            }

            /* If not, Iterate through mainnode */
            main_node* temp = hash[i].link;
            while (temp != NULL) {

                /* Iterate through subnode */
                sub_node* subTemp = temp->Slink;

                /* Write the data to the file */
                fprintf(fptr, "#%d;%s;%d", i, temp->word, temp->file_count);
                while (subTemp != NULL) {
                    fprintf(fptr, ";%s;%d", subTemp->file_name, subTemp->wordCount);
                    /* Update the subnode */
                    subTemp = subTemp->Slink;
                }
               fprintf(fptr, "#\n"); // End marker for main node

                /* Update the main node */
                temp = temp->Mlink;
            }
        }
        fclose(fptr);
        printf("Database successfully saved to %s\n", file);
        return SUCCESS;
        return SUCCESS;
    /* If empty, print the below */
    }else {
        printf("DataBase is empty\n");
        return FAILURE;
    }
}


