//
// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: Andrew Lau
// Student Number: 1004022336
// March 16,2018

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

// Declarations of linked list functions
bool isEmpty(Node *head);
Node* isDuplicate(char name[],Node*head);
Node* insertNode(char name[],char artist[],char genre[],Node*head);
void addNode(Node *node1,Node *node2);
void printAllNodes(Node *head);
void printOneNode(Node *print);
Node* removeAllNodes(Node *head);
Node* removeNode(Node *head, Node *delete);


// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH = 1024;

int main( void ) {
    // Declare the head of the linked list.
    Node*head = NULL;
 
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" ) ;
    
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
        
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH );

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        
        response = toupper( input[0] );
    
        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            
            char *promptName = "Song name" ;
            char *promptArtist =  "Artist" ;
            char *promptGenre = "Genre" ;
            char inputName[ MAX_LENGTH + 1 ];
            char inputArtist[ MAX_LENGTH + 1 ];
            char inputGenre[ MAX_LENGTH + 1 ];

            inputStringFromUser(promptName, inputName, MAX_LENGTH);
            inputStringFromUser(promptArtist, inputArtist, MAX_LENGTH);
            inputStringFromUser(promptGenre, inputGenre, MAX_LENGTH);

            if(isDuplicate(inputName,head)==NULL)
                head=insertNode(inputName,inputArtist,inputGenre,head);
            else
                songNameDuplicate(inputName);
                
        } else if( response == 'D' ) { // Delete a song from the list.
        
            char *prompt = "\nEnter the name of the song to be deleted" ;
            char deleteName[ MAX_LENGTH + 1 ];
            
            //determines node where song exists
            inputStringFromUser(prompt,deleteName, MAX_LENGTH);
            Node *findNode = isDuplicate(deleteName,head);
            
            //if song DNE, display message
            if(findNode==NULL)
                songNameNotFound(deleteName);
            else
                head=removeNode(head,findNode);
                       
        } else if( response == 'S' ) { // Search for a song by its name.
        
            char *prompt = "\nEnter the name of the song to search for" ;
            char searchName[ MAX_LENGTH + 1 ];
            inputStringFromUser(prompt,searchName, MAX_LENGTH);
            
            //finds node with same name if possible
            //displays messages accordingly and prints song if found
            Node *searchNode = isDuplicate(searchName,head);
            if(searchNode==NULL){
                songNameNotFound(searchName); 
            } else {
                songNameFound(searchName);
                printOneNode(searchNode);
            }
            
        } else if( response == 'P' ) { // Print the music library.
        
            //check if list is filled, if yes print list
            if(isEmpty(head)){
                printMusicLibraryEmpty();
            } else {
                printMusicLibraryTitle();
                printAllNodes(head);
            }
            
        } else if( response == 'Q' ) { // do nothing, we'll catch this below
            ; 
        } else { // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ; 
    
    // Delete the entire linked list.
    head=removeAllNodes(head);

    // Print the linked list to confirm deletion.
    printAllNodes(head);
    if(isEmpty(head))
        printMusicLibraryEmpty();
    else
        printMusicLibraryTitle();
        
    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}
// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf("\nThe song name '%s' was found in the music library.\n",songName );
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf("\nThe song name '%s' was not found in the music library.\n",songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf("\nDeleting a song with name '%s' from the music library.\n",songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}

//determines if list is empty, true for empty
bool isEmpty(Node *head){
    if (head==NULL)
        return true;
    else
        return false;
}

//returns node with name searched, if not found returns null
Node* isDuplicate(char name[],Node*head){
    Node *current=head;
    while (current!=NULL){
        if(strcmp(current->songName,name)==0){
            return current;
        }
        current=current->nextNode;
    }
    return NULL;
}

//returns start of list after adding elements
Node* insertNode(char name[],char artist[],char genre[],Node*head){
    Node*current=head,*nextCurrent=NULL;
    Node*newNode=(Node*)malloc(sizeof(Node));

    bool inserted=false,putAtBack=false;
    
    //make a new node with elements inputted by user
    newNode->songName=malloc(sizeof(name));
    newNode->artist=malloc(sizeof(artist));
    newNode->genre= malloc(sizeof(genre));
    strcpy(newNode->songName,name);
    strcpy(newNode->artist,artist);
    strcpy(newNode->genre,genre);

    while(current!=NULL && !inserted){
        //checks if song would go between current node and next node
        //if yes, new node is placed between        
        if(strcmp(current->songName,newNode->songName)<0){
            putAtBack=true;
            nextCurrent=current->nextNode;
            if(nextCurrent==NULL || strcmp(nextCurrent->songName,newNode->songName)>0){
                addNode(current,newNode); //put newNode after current
                inserted=true;
            }        
        } else { //name goes before current node
            break;
        }
        current=current->nextNode;
    }
    
    if(!inserted){ //new node not inserted
        if(!putAtBack){ //place at start of list
            if(head!=NULL)
                newNode->nextNode=head->nextNode;
            addNode(newNode,head);
            head=newNode; //set new head
        } else { //place at end of list
            addNode(current,newNode);
        }
    }
    
    return head;
}

//places node1 directly before node2 in list
void addNode(Node *node1,Node *node2){
    if(node2!=NULL){
        node2->nextNode=(Node*)malloc(sizeof(Node));
        node2->nextNode = node1->nextNode;
    }
    node1->nextNode=node2;
}

//traverses from head to end to call for print of all song nodes
void printAllNodes(Node *head){
    Node *current = head;
    while(current!=NULL){
        printOneNode(current);
        current=current->nextNode;
    }
}

//prints all information to do with song node received
void printOneNode(Node *print){
    printf("\n");
    printf("%s\n",print->songName);
    printf("%s\n",print->artist);
    printf("%s\n",print->genre);
}

//traverses from head to end to call for removal of all nodes
//returns new head after removing all elements
Node* removeAllNodes(Node *head){
    Node *current = head;
    while(current!=NULL){
        head=removeNode(current,current);
        current=current->nextNode;
    }
    return head;
}

//removes delete from list
//the node before delete points to node after delete
Node* removeNode(Node *head, Node *delete){
    Node *current = head;
    if(current==delete){
        head = delete->nextNode;
    } else {
        while(current->nextNode!=delete)
            current=current->nextNode;
        current->nextNode=delete->nextNode;
    }
    
    //removed node element memory is freed
    songNameDeleted(delete->songName);
    free(delete->songName);
    free(delete->artist);
    free(delete->genre);
    free(delete);
    
    return head;
}