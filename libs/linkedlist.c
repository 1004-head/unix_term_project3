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
    printf("%s is now playing!\n", _cur_node->data);
}

void print_file(FILE* stream);

// free 아직 안넣음
void clear(){
    if (!empty()){
        Node* now = _head->next;
        Node* next;
        while (now != NULL){
            next = now->next;
            delete_node(now);
            now = next;
        }
    }
    printf("LinkedList is cleared!\n");
}

Node* append_left(size_t n, char new_data[n]){
    Node* new = (Node*)malloc(sizeof(Node));
    strcpy(new->data, new_data);

    new->next = _head->next;
    _head->next->prev = new;

    _head->next = new;
    new->prev = _head;

    if (empty()){
        _cur_node = new;
    }
    _size++;

    return new;
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

Node* append(size_t n, char new_data[n]){
    Node* new = (Node*)malloc(sizeof(Node));
    strcpy(new->data, new_data);

    new->next = _tail;
    _tail->prev->next = new;

    new->prev = _tail->prev;
    _tail->prev = new;

    if (empty()){
        _cur_node = new;
    }
    _size++;

    return new;
}

// 노드 삭제 시, cur_node를 우선적으로 앞으로 이동함.
// 만약 불가능(NULL)할 시, 뒤로 이동함.
// size가 0이면, NULL
Node* delete_node(Node* cur_node){
    // 여기에 들어오면 무조건 매칭되는 값이 있다는 의미
    // 따라서 그 검사는 하지 않겠음.
    _size--;
    if(empty()){
        _cur_node = NULL;
    } 
    else if (_cur_node -> prev == NULL){
        _cur_node = _cur_node->next;
    }
    else{
        _cur_node = _cur_node->prev;
    }

    _cur_node->prev->next = _cur_node->next;
    _cur_node->next->prev = _cur_node->prev;

    return _cur_node;
}

Node* delete(char* data){
    Node* now = _head;
    while (now != NULL){
        if (strcmp(data, now->data) == 0){
            return delete_node(now);
        }
        now = now->next;
    }

    return NULL;
}

Node* get_node(size_t index){
    Node* now = _head;
    size_t cnt_max = (index <= _size)? index : _size;

    for (size_t cnt = 0; cnt < cnt_max; cnt++){
        now = now->next;
    }

    return now;
}

Node* first(){
    return _head->next;
}

Node* last(){
    return _tail->prev;
}

Node* next(){
    if (empty())
        _cur_node = NULL;
    else if (_cur_node->next)
        _cur_node = _cur_node->next;
    return _cur_node;
}

Node* prev(){
    if (empty())
        _cur_node = NULL;
    else if (_cur_node->prev)
        _cur_node = _cur_node->prev;
    return _cur_node;
}


// 추가 함수
void init_state(){
    _head = (Node*)malloc(sizeof(Node));
    _tail = (Node*)malloc(sizeof(Node));

    _head->prev = NULL;
    _head->next = _tail;
    
    _tail->prev = _head;
    _tail->next = NULL;
    
    _cur_node = NULL; 
}