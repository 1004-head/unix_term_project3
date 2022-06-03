#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linkedlist.h"
#include "textfilewriter.h"

enum Command{
    add,
    del,
    list,
    next,
    prev,
    move,
    play,
    clear,
    quit,
    load,
    save
};

void checkCommand(char** command){
    switch (command[0]) {
        case add:
            char *title = malloc(sizeof(command[1]));
            title = command[1];
            append_left(sizeof(title), title);
            break;
        case del:
            char *title = malloc(sizeof(command[1]));
            title = command[1];
            delete(title);
            break;
        case list:
            print_all();
            break;
        case next:
            next();
            break;
        case prev:
            prev();
            break;
        case move:
            int moveNum = command[1]-0x30;
            Node *new_node = get_node(moveNum);
            //insert_after(??,new_node); 좀 더 알아보고 추가 구현
            break;
        case play:
            print();
            break;
        case clear:
            clear();
            break;
        case quit:
            clear();
            printf("quit!");
            exit(0);
            break;
        case load:
            char *fileName = command[1];
            read_file(fileName);
            break;
        case save:
            char *fileName = command[1];
            write_file(fileName);
            break;
        default:
            printf("Invalid Command\n");
            break;
    }
}

char** splitCommandArgument(char* cmdArg){
    char *ptr = strtok(cmdArg, " ");

    int argc = 1;
    char* command = "";
    char* argument = "";
    while (ptr != NULL)
    {
        if(argc == 1) { command = ptr; }
        if(argc == 2) { argument = ptr; }
        ptr = strtok(NULL, " ");
    }
    printf("%s %s\n", command, argument);
    char** comandAndArgument = {command, argument};

    return comandAndArgument;
}

int main(){
    int musicNum = 0;
    scanf("%d", &musicNum);

    for(int i=0; i<musicNum; i++){
        char *title;
        fgets(title, MAX_TITLE_SIZE);

    }

    int commandNum = 0;
    scanf("%d", &commandNum);

    for(int i = 0; i < commandNum; i++){
        char *command;
        scanf("%s", command);

        char** commandAndArgument = splitCommandArgument(command);
        checkCommand(commandAndArgument);
    }
}
