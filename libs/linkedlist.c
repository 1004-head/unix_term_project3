#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

static Node* _head = NULL;
static Node* _tail = NULL;
static Node* _cur_node = NULL;

static size_t _size = 0; 

bool empty(){
    if (size() == 0){
        return true;
    }
    return false;
}

size_t size(){
    return _size;
}

void print(){
    printf("[%s] is now playing!\n", _cur_node->data);
}

void print_all(){
    Node* now = first_node();

    printf("LinkedList [ ");
    for (size_t i = 0; i < size(); i++){
        printf("%s ", now->data);
        now = now->next;
    }
    printf("]\n"); 
}

void print_file(FILE* stream)
{	
	Node* now = last_node();
	char my_string[51];

	sprintf(my_string, "%zd\n", size());
	fputs(my_string, stream);

    for (size_t i = 0; i < size(); i++){
		fputs(now->data, stream);
		fputs("\n", stream);
		now = now->prev;
    }
}

// free 아직 안넣음
void clear(){
    Node* now = _head->next;
    Node* next;

    while (size() > 0){
        next = now->next;
        free(delete_node(now));
        now = next;
    }

    printf("LinkedList is cleared!\n");
}

Node* append_left(size_t n, char new_data[]){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = (char*)malloc(sizeof(char)*n);
    strcpy(new_node->data, new_data);

    new_node->next = _head->next;
    _head->next->prev = new_node;

    _head->next = new_node;
    new_node->prev = _head;

    if (empty()){
        _cur_node = new_node;
    }

    _size++;
    _cur_node = new_node;

    return new_node;
}

// move
Node* insert_after(Node* cur_node, Node* new_node){
    new_node->prev->next = new_node->next;
    new_node->next->prev = new_node->prev;

    new_node->next = cur_node->next;
    cur_node->next->prev = new_node;

    cur_node->next = new_node;
    new_node->prev = cur_node;

    return new_node;
}

Node* append(size_t n, char new_data[]){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = (char*)malloc(sizeof(char)*n);
    strcpy(new_node->data, new_data);

    new_node->next = _tail;
    _tail->prev->next = new_node;

    new_node->prev = _tail->prev;
    _tail->prev = new_node;

    if (empty()){
        _cur_node = new_node;
    }

    _size++;
    _cur_node = new_node;

    return new_node;
}

// 노드 삭제 시, cur_node를 우선적으로 뒤로 이동함.
// 만약 불가능(NULL)할 시, 앞으로 이동함.
// size가 0이면, NULL
Node* delete_node(Node* cur_node){
    // 여기에 들어오면 무조건 매칭되는 값이 있다는 의미
    // 따라서 그 검사는 하지 않겠음.
    // 테스트 케이스 보고 참고
    _size--;
    if (_cur_node == cur_node)
        if (cur_node -> next == NULL){
            _cur_node = _cur_node->next;
        }
        else{
            _cur_node = _cur_node->prev;
        }

    cur_node->prev->next = cur_node->next;
    cur_node->next->prev = cur_node->prev;

    return cur_node;
}

Node* delete_by_data(char* data){
    Node* now = first_node();

    for (size_t i = 0; i < size(); i++){
        if (strcmp(data, now->data) == 0){
            return delete_node(now);
        }
        now = now->next;
    }

    return NULL;
}

Node* get_node(size_t index){
    Node* now = _head;
    size_t cnt_max = (index <= size())? index : size();

    for (size_t cnt = 0; cnt < cnt_max; cnt++){
        now = now->next;
    }

    return now;
}

Node* first_node(){
    if (empty()) return NULL;
    return _head->next;
}

Node* last_node(){
    if (empty()) return NULL;
    return _tail->prev;
}

Node* next(){
    if (empty())
        _cur_node = NULL;
    else if (_cur_node->next != _tail)
        _cur_node = _cur_node->next;
    return _cur_node;
}

Node* prev(){
    if (empty())
        _cur_node = NULL;
    else if (_cur_node->prev != _head)
        _cur_node = _cur_node->prev;
    return _cur_node;
}


// 추가 함수
// 실행 전에, 반드시 call 해주세요.
void init_state(){
    _head = (Node*)malloc(sizeof(Node));
    _tail = (Node*)malloc(sizeof(Node));

    _head->prev = NULL;
    _head->next = _tail;
    
    _tail->prev = _head;
    _tail->next = NULL;
    
    _cur_node = NULL; 
}