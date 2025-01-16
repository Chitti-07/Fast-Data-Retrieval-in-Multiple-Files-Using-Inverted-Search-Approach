#include "invert.h"

int main(int argc, char** argv) {

    /* Creating Single linked list to store the file names */
    Slist* head = NULL;
    /* Validating thr files */
    if (validate(argc, argv, &head) == SUCCESS) {
        printf("Validation is Successful\n");
        /* Initializing the hash table ( [0-25] indexes -> for alphabets, 26th index for numbers, 27th index for special characters)*/
        Hash hash[28];
        for (int i = 0; i < 28; i++) {
            hash[i].key = i;
            hash[i].link = NULL;
        }
        print_list(head);
        /* Creating main node and sub node for creating database in hash table*/
        main_node* mainNode;
        sub_node* subNode;
        int option;
        
        /* Flags to avoid creating and updating database accordingly */
        int create_database = 0;
        int update_database = 0;

        /* Displaying menu for user */
        do {
            printf("1. Create DataBase\n2. Display DataBase\n3. Search word\n4. Save DataBase\n5. Update dataBase\n6. Exit\nEnter your choice: ");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                
                /* if database is not created and not updated, then create database */
                if(create_database == 0 && update_database == 0) {
                    if (create_DataBase(&head, hash, &mainNode, &subNode) == SUCCESS) {
                        create_database = 1;
                        printf("Create DataBase is successfully completed\n");
                    }else {
                        printf("Create DataBase is Failed\n");
                    }
                /* If the update is done and create of database is not done, Then create database for new files */
                }else if (update_database != 0 && create_database == 0){
                    Slist* UpdateHead = NULL;
                    Slist* NewHead = NULL;
                    /* Getting the new files for creating the database */
                    update_new_files(hash, &head, &UpdateHead, &NewHead, &mainNode, &subNode);
                    create_DataBase(&NewHead, hash, &mainNode, &subNode);
                    create_database = 1;
                    printf("Create data base is successfull for new files\n");
                }else {
                    printf("DataBase is already created\n");
                }
                break;
            /* Displaying the DataBase */
            case 2:
                display_DataBase(hash);
                break;
            /* Search a word in database */
            case 3:
                search_DataBase(hash);
                break;
            case 4:
                if(save_DataBase(hash) == SUCCESS) {
                    printf("Data is saved to DataBase\n");
                }
                break;
            case 5:
                if (update_database == 0) {
                    if(update_DataBase(hash, &mainNode, &subNode) == SUCCESS) {
                        printf("Data base is updated successfully\n");
                        update_database = 1;
                    }else {
                        printf("Updation of data base is failed\n");
                    }
                }else {
                    printf("DataBase is already updates\n");
                }
                break;
            default:
                printf("Enter valid option\n");
                break;
            }
        }while(option != 6);

    }else {
        printf("Validation is failed\n");
    }

}

/* Function to validate */
int validate(int argc, char** argv, Slist** head) {
    /* If there are no files available, Then we cannot do invert search */
    if (argc < 2) {
        return FAILURE;
    }
    /* validating rach file */
    char* fileExtn;
    for (int i = 1; i < argc; i++) {

        /* Check if the file present have the extension of ".txt" */
        if ((fileExtn = strcasestr(argv[i], ".txt")) && (strcasecmp(fileExtn, ".txt") == 0)) {

            /* Open the files with extension of ".txt" */
            FILE* fptr = validate_file(argv[i]);
            if (fptr != NULL) {

                /* Check if the file is empty */
                if (File_content(fptr) != EMPTY_FILE) {

                    /* Check if the file is already present or not (duplicate) */
                    if (find_duplicates(head, argv[i]) != DUPLICATE_FOUND) {

                        /* Insert to the list */
                        insert_last(head, argv[i]);
                        printf("%s file is added successfully\n", argv[i]);
                    }else {
                        printf("%s file is already present\n", argv[i]);
                    }
                }else {
                    printf("%s file have no content available\n", argv[i]);
                }
            }else {
                printf("%s file is failed to open\n", argv[i]);
            }
        }else {
            printf("%s File should be \".txt\" extension\n", argv[i]);
        }
    }
    return SUCCESS;
}

/* Function to validate the file */
FILE* validate_file(char* file) {
    FILE* fptr = fopen(file, "r");
    if (fptr == NULL) {
        return NULL;
    }
    return fptr;
}

/* Function to check file is empty or not */
int File_content(FILE* fptr) {
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0) {
        return EMPTY_FILE;
    }
    return SUCCESS;
}

/* Function to find duplicate files */
int find_duplicates(Slist** head, char data[]) {
    if (head == NULL) {
        return LIST_EMPTY;
    }
    Slist *t1 = *head;
    while (t1 != NULL) {
        if (strcasecmp(t1->data, data) == 0) {
            return DUPLICATE_FOUND;
        }
        t1 = t1->link;
    }
    return SUCCESS;
}

/* Function to check updated file is present in user given file */
int find_new_file(Slist *head  , char file[]) {
    while (head != NULL) {
        if (strcasecmp(head->data, file) == 0) {
            return SUCCESS;
        }
        head = head->link;
    }
    return FAILURE;
}

/* Function to update the new files, after updating the database and creating the database for new files */
void update_new_files(Hash* hash, Slist** head, Slist** UpdateHead, Slist** NewHead, main_node** mainNode, sub_node** subNode) {
    for (int i = 0; i < 28; i++) {
        if (hash[i].link == NULL) {
            continue;
        }
        main_node* Main = hash[i].link;
        while (Main != NULL) {
            sub_node* Sub = Main->Slink;
            while (Sub != NULL) {
                insert_last(UpdateHead, Sub->file_name);
                Sub = Sub->Slink;
            }
            Main = Main->Mlink;
        }
    }
    Slist* tempHead = *head;
    while (tempHead != NULL) {
        if (find_new_file(*UpdateHead, tempHead->data) == FAILURE) {
            insert_last(NewHead, tempHead->data);
        }
        tempHead = tempHead->link;
    }
}
