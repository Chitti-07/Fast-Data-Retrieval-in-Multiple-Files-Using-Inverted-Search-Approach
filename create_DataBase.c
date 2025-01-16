#include "invert.h"

int create_DataBase(Slist** head, Hash* hashT, main_node** Main_node, sub_node** Sub_node) {
    /* Pointing temp node to head of list */
    Slist* temp = *head;
    /* Iterate through all the files */
    while (temp != NULL) {

        /* Opening each file to read and store each word in hast table */
        FILE* fptr = fopen(temp->data, "r");
        fseek(fptr, 0, SEEK_SET);

        /* Iterate upto end of the file */
        while (!feof(fptr)) {
            /* Buffer to store each word */
            char wordBuff[SIZE];
            fscanf(fptr, "%s", wordBuff);
            /* Finding index of 1st letter in the word */
            int index;
            /* if it is a digit, then store it in 26th index */
            if (isdigit(wordBuff[0])) {
                index = 26;
            /* If it is a special character, store it in 27th index */
            }else if (ispunct(wordBuff[0])) {
                index = 27;
            }else {
            /* store the alphabet corresponding to its index */
                index = (tolower(wordBuff[0]) % 97);
            }
            /* Case: 1 -> If the hash table index part is null */
            if (hashT[index].link == NULL) {
                /* Create main node & sub node and link them */
                sub_node* Snode = createSubNode(Sub_node, 1, temp->data, NULL);
                main_node* Mnode = createManiNode(Main_node, 1, wordBuff, NULL, Snode);
                hashT[index].link = Mnode;
            }
            /* Case: 2 -> If the link is not Null, search for the word */
            else {
                main_node* tempMainNode = hashT[index].link;
                main_node* tempPrev = NULL;
                while (tempMainNode != NULL && strcasecmp(tempMainNode->word, wordBuff) != 0) {
                    tempPrev = tempMainNode;
                    tempMainNode = tempMainNode->Mlink;
                }
                /* If the word found, Search for the file */
                if (tempMainNode != NULL) {
                    sub_node* subNode = tempMainNode->Slink;
                    sub_node* subPrev = NULL;
                    int file_found = 0;
                    /* If the file found, increment the file count */
                    while (subNode != NULL) {
                        if (strcasecmp(subNode->file_name, temp->data) == 0) {
                            (subNode->wordCount)++;
                            file_found = 1;
                            break;
                        }
                        subPrev = subNode;
                        subNode = subNode->Slink;
                    }
                    /* If the file is not found, create a subnode and increment the file count */
                    if (file_found == 0) {
                        sub_node* newSubNode = createSubNode(Sub_node, 1, temp->data, NULL);
                        subPrev->Slink = newSubNode;
                        (tempMainNode->file_count)++;
                    }
                /* if the word is not found, create new main & sub node and update the link part */
                }else {
                    sub_node* Snode = createSubNode(Sub_node, 1, temp->data, NULL);
                    main_node* Mnode = createManiNode(Main_node, 1, wordBuff, NULL, Snode);
                    tempPrev->Mlink = Mnode;
                }

            }

        }
        /* updaing the file */
        temp = temp->link;
    }
    return SUCCESS;
}

/* Function to create main node */
main_node* createManiNode(main_node** Mnode, int fileCount, char word[], main_node* Mlink, sub_node* Slink) {
    main_node* node = malloc(sizeof(main_node));
    if (node == NULL) {
        return NULL;
    }
    node->file_count = fileCount;
    strcpy(node->word, word);
    node->Mlink = Mlink;
    node->Slink = Slink;
    return node;
}

/* Function to crete sub node */
sub_node* createSubNode(sub_node** Snode, int wordCount, char fileName[], sub_node* Slink) {
    sub_node* node = malloc(sizeof(sub_node));
    if (node == NULL) {
        return NULL;
    }
    node->wordCount = wordCount;
    strcpy(node->file_name, fileName);
    node->Slink = Slink;
    return node;
}