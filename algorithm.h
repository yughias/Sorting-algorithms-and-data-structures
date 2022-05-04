#include <iostream>
#include "BinarySearchTree.h"
#include "Heap.h"
#include "List.h"

using namespace std;

//=> UTILITY FUNCTIONS

template<class T>
void swap(int a, int b, T* array){
    T tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

template<class T>
printArray(T* array, int len){
    for(int i = 0; i < len; i++)
        cout << array[i] << " ";
    cout << endl;
}

//=> SELECTION SORT

template<class T>
void selectionSort(T* array, int len){
    for(int i = 0; i < len-1; i++){
        int min = i;
        for(int j = i; j < len; j++){
            if(array[j] < array[i])
                min = j;
        }
        swap(i, min, array);
    }
}

//=> BUBBLE SORT

template<class T>
void bubbleSort(T* array, int len){
    for(int i = len-1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(array[j] > array[j+1])
                swap(j, j+1, array);
        }
    }
}

//=> INSERTION SORT

template<class T>
void insertionSort(T* array, int len){
    for(int i = 0; i < len; i++){
        for(int j = i; j > 0 && array[j] < array[j-1]; j--)
            swap(j, j-1, array);
    }
}

//=> QUICK SORT

template<class T>
void quickSort(T* arr, int iStart, int iEnd){
	T vMid = arr[(iStart+iEnd)/2];
	int iLeft = iStart;
	int iRight = iEnd;
	while(iLeft < iRight){
		while(arr[iLeft] < vMid)
			iLeft++;
		while(arr[iRight] > vMid)
			iRight--;
		if(iLeft > iRight)
			break;
		swap(arr[iLeft], arr[iRight]);
		iLeft++;
		iRight--;
	}
	if(iStart < iRight)
		quickSort(arr, iStart, iRight);
	if(iLeft < iEnd)
		quickSort(arr, iLeft, iEnd);
}

//=> MERGE SORT

template<class T>
void merge(T* arr, int start, int mid, int end){
    int iSx = start;
    int iDx = mid;
    int size = end-start;
    T tmp[size];
    int index = 0;
    while(iSx != mid || iDx != end){
        if(iSx == mid)
            tmp[index] = arr[iDx++];
        else if(iDx == end)
            tmp[index] = arr[iSx++];
        else if(arr[iSx] < arr[iDx])
            tmp[index] = arr[iSx++];
        else
            tmp[index] = arr[iDx++];
        index++;
    }
    for(int i = 0; i < size; ++i)
        arr[start+i] = tmp[i];
}

template<class T>
void mergeSort(T* arr, int start, int end){
    if(start < end){
        int mid = (start+end)/2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid+1, end);
        merge(arr, start, mid+1, end+1);
    }
}

//=> COUNTING SORT

void countingSort(int* arr, int len){
    int max = arr[0];
    int min = arr[0];
    for(int i = 1; i < len; ++i)
        if(arr[i] > max)
            max = arr[i];
        else if(arr[i] < min)
            min = arr[i];

    int tmp[max-min+1] = {0};
    for(int i = 0; i < len; ++i)
        tmp[arr[i]-min]++;
    
    int k = 0;
    for(int i = 0; i < max-min+1; ++i){
        while(tmp[i] > 0){
            arr[k] = i + min;
            k++;
            tmp[i]--;
        }
    }
}

//=> BUCKET SORT

void bucketSort(int* arr, int len){
    int max = arr[0];
    int min = arr[0];
    for(int i = 0; i < len; i++){
        if(arr[i] > max)
            max = arr[i];
        if(arr[i] < min)
            min = arr[i];
    }

    List<int>* bucket[max-min+1];
    for(int i = 0; i < max-min+1; i++)
        bucket[i] = new List<int>;

    for(int i = 0; i < len; i++){
        bucket[arr[i]-min]->append(arr[i]);
    }

    int position = 0;
    for(int i = 0; i < max-min+1; i++){
        while(!bucket[i]->empty()){
            int val = bucket[i]->pop_front();
            arr[position] = val;
            position++;
        }
    }
    
    //delete list
    for(int i = 0; i < max+min-1; i++){
        delete bucket[i];
    }
}

//=> RADIX SORT

int calculateDigits(int value){
    int out = 1;
    for(int exponent = 10; value / exponent != 0; exponent*= 10)
        out++;
  
    return out;
}

int maxDigit(int* arr, int len){
    int out = 0;
    for(int i = 0; i < len; i++){
        int digits = calculateDigits(arr[i]);
        if(digits > out)
            out = digits;
    }
    return out;
}

void bucketSort(int* arr, int len, int exp){
    List<int>* bucket[10];
    for(int i = 0; i < 10; i++)
        bucket[i] = new List<int>;

    for(int i = 0; i < len; i++){
        bucket[(arr[i] % exp) / (exp/10)]->append(arr[i]);
    }
    
    int position = 0;
    for(int i = 0; i < 10; i++){
        while(!bucket[i]->empty()){
            int val = bucket[i]->pop_front();
            arr[position] = val;
            position++;
        }
    }
    //delete list
    for(int i = 0; i < 10; i++){
        delete bucket[i];
    }
}

void radixSort(int* arr, int len){
    int nDigits = maxDigit(arr, len);
    int exponent = 1;
    for(int i = 0; i < nDigits; i++){
        exponent *= 10;
        bucketSort(arr, len, exponent);
    }
}

//=> TREE SORT

template<class T>
void treeSort(T* arr, int len) {
    BinarySearchTree<T> tree(arr, len);
    tree.copy(arr);
}

//=> HEAP SORT

template<class T>
void heapSort(T* arr, int len){
    Heap<T> heap(arr, len);
    for(int i = len-1; i >= 0; i--){
        T val = heap.extract();
        arr[i] = val;
    }
}