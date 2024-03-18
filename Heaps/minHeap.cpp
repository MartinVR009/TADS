#include <deque>

class MinHeap
{
    private:
        std::deque<int> harr;
        int capacity;
        int heap_size;

    public:
        MinHeap(int cap): capacity(cap) heap_size(0) {}
        int parent(int i){
            return harr[(i-1)/2];
        }
        int left(int i){
            return 0;
        }
        int right(int i){
            return 0;
        }
        int getMin(){
            return 0;
        }   
        int extractMin(){
            return 0;
        }
        void insertKey(int k){
            
        }
        void decreaseKey(int i, int new_val){

        }
        void deleteKey(int i){

        }
        void MinHeapify(int i){

        }
        void linearSearch(int val){

        }
        void printArray(){

        }
        int height(){
            return 0;
        }
};