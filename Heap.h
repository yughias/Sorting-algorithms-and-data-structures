#ifndef HEAP
#define HEAP

#include <vector>

template<class T>
class Heap{
private:
    vector<T> vec;

    void swap(int a, int b){
        T tmp = vec[a];
        vec[a] = vec[b];
        vec[b] = tmp;
    }

    void up(int index){
        int father = (index-1)/2;
        if(father > 0){
            if(vec[index] > vec[father]){
                swap(index, father);
                up(father);
            }
        }
    }

    void down(int index){
        int son = 2*index+1;
        if(son == vec.size()-1){
            if(vec[son] > vec[index])
                swap(index, son);
        }
        else if(son < vec.size()-1){
            if(vec[son] < vec[son+1]) son++;
            if(vec[son] > vec[index]){
                swap(index, son);
                down(son);
            }
        }
    }

public:
    Heap() {}
    Heap(T* arr, int len) {
        for(int i = 0; i < len; i++)
            vec.push_back(arr[i]);

        for(int i = (vec.size()-1)/2; i >= 0; i--)
            down(i);
    }

    T extract(){
        T out = vec[0];
        vec[0] = vec[vec.size()-1];
        vec.pop_back();
        if(vec.size() != 0)
            down(0);
        return out;
    }

    void insert(T x){
        vec.push_back(x);
        up(vec.size()-1);
    }

    friend ostream& operator<<(ostream& os, Heap<T>& h){
        for(int i = 0; i < h.vec.size(); i++)
            os << h.vec[i] << " ";
        os << endl;
        return os;
    }
};

#endif