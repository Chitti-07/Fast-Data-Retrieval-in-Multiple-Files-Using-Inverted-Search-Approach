#ifndef INVERT_H
#define INVERT_H
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define SUCCESS 0
#define FAILURE 1
#define EMPTY_FILE 2
#define LIST_EMPTY 3
#define DUPLICATE_FOUND 4
#define NO_FILE 5
#define SIZE 50

typedef struct invert
{
    char data[20];
    struct invert* link;

}Slist;

typedef struct subNode
{
    int wordCount;
    char file_name[SIZE];
    struct subNode* Slink;
}sub_node;

typedef struct mainNode
{
    int file_count;
    char word[SIZE];
    struct mainNode* Mlink;
    struct subNode* Slink;
}main_node;

typedef struct hash
{
    int key;
    struct mainNode* link;
}Hash;


int validate(int argc, char** argv, Slist** head);
int insert_last(Slist** head, char data[]);
Slist* createNode(char data[]);
FILE* validate_file(char* file);
void print_list(Slist *head);
int find_duplicates(Slist** head, char* argv);
int File_content(FILE* fptr);
int create_DataBase(Slist** head, Hash* hashT, main_node** Main_node, sub_node** Snode);
main_node* createManiNode(main_node** Mnode, int fileCount, char word[], main_node* Mlink, sub_node* Slink);
sub_node* createSubNode(sub_node** Snode, int wordCount, char fileName[], sub_node* Slink);
void display_HT(Hash *arr, int size);
void display_DataBase(Hash* hash);
void search_DataBase(Hash* hashT);
int save_DataBase(Hash* hash);
int update_DataBase(Hash* hash, main_node** Mnode, sub_node** Snode);
FILE* update_file_validation(char file[]);
int find_new_file(Slist *head  , char file[]);
void update_new_files(Hash* hash, Slist** head, Slist** UpdateHead, Slist** NewHead, main_node** mainNode, sub_node** subNode);