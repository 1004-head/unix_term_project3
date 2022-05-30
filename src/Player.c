#include "include/linkedlist.h"
#include "include/textfilewriter.h"

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
            break;
        case list:
            printf("LinkedList [ ");
            Node *node;
            for(node=first();node==last();node=next()){
                printf("%s ", node->data);
            }
            printf("%s ]", node->date);
            break;
        case next:
            break;
        case prev:
            break;
        case move:
            break;
        case play:
            break;
        case clear:
            break;
        case quit:
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
