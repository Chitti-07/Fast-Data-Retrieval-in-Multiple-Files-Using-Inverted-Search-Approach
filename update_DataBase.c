#include "invert.h"

/* Function to update database */
int update_DataBase(Hash* hash, main_node** Mnode, sub_node** Snode) {
    /* Reading file from user */
    char file[SIZE];
    printf("Enter the backup file: ");
    scanf("%s", file);

    /* Validating and opening the file */
    FILE* fptr = update_file_validation(file);
    if (fptr == NULL) {
        return FAILURE;
    }

    /* Buffer to store each line from the file */
    char wordLine[SIZE];
    fseek(fptr, 0, SEEK_SET);
    
    /* Iterating untill end of the file */
    while(fscanf(fptr, "%s", wordLine) != EOF) {

        /* Getting the index to store the word */
        int index = atoi(strtok(wordLine, ";#"));

        /* Getting the word */
        char *Word = strtok(NULL, ";#");

        /* Getting the file count */
        int fileCount = atoi(strtok(NULL, ";#"));

        /* Getting and storing each file name and word count in array*/
        char *file_Names[fileCount];
        int word_count[fileCount];
        for (int i = 0; i < fileCount; i++) {
            file_Names[i] = strtok(NULL, ";#");
            word_count[i] = atoi(strtok(NULL, ";#"));
        }

        /* Creating subnode for file count times */
        sub_node* SubNode = NULL;
        for (int i = fileCount-1; i>= 0; i--) {
            SubNode = createSubNode(Snode, word_count[i], file_Names[i], SubNode);
        }

        /* Creating and Updating the main node */
        main_node* MainNode = createManiNode(Mnode, fileCount, Word, NULL, SubNode);
        main_node* temp = hash[index].link;
        main_node* prev = NULL;

        /* If the main node is null, just update the hash index link */
        if (temp == NULL) {
            hash[index].link = MainNode;
        /* If not iterate through last main node and update the last node */
        }else {
            while (temp != NULL) {
                prev = temp;
                temp = temp->Mlink;
            }
            prev->Mlink = MainNode;
        }
    }
    return SUCCESS;

}

/* Function to validate the files given by user */
FILE* update_file_validation(char file[]) {

    /*Check if the file contains ".txt" */
    char* fileExtn = strcasestr(file, ".txt");
    if ((strcasecmp(fileExtn, ".txt") == 0)) {
        /* Opening the file */
        FILE* fptr = fopen(file, "r");
        if (fptr != NULL) {

            /* Storing each line in a buffer */
            char checkLine[SIZE];
            fscanf(fptr, "%s", checkLine);

            /* Check if the line starts and ends with '#' and contains ';' */
            if ((checkLine[0] == '#') && (checkLine[strlen(checkLine) - 1] == '#') && strcasestr(checkLine, ";")) {
                return fptr;
            } else {
                printf("%s is not a valid backup file\n", file);
                return NULL;
            }
        }else {
            printf("%s is not present\n", file);
            return NULL;
        }
    }else {
        printf("%s should be \".txt\" extension\n", file);
        return NULL;
    }
}