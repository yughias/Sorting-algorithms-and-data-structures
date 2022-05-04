#ifndef LIST
#define LIST

template<class T>
class List{
private:
    struct block{
        T val;
        block* next;
    };

    block* list;

    void append(block*& pointer, T val){
        if(!pointer){
            pointer = new block;
            pointer->val = val;
            pointer->next = nullptr;
        } else append(pointer->next, val);
    }

public:
    List(){ list = nullptr; }
    
    void append(T val){ append(list, val); }
    int pop_front(){
        if(!list){
            return -1;
        }
        block* tmp = list->next;
        T out = list->val;
        delete list;
        list = tmp;
        return out;
    }

    bool empty() { return !list; }

    ~List(){
        while(list != nullptr){
            block* tmp = list;
            list = list->next;
            delete list;
        }
    }
};

#endif