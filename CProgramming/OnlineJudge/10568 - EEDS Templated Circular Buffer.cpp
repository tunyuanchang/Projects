#include<iostream>
#include<deque>
using namespace std;

template <class T>class circular_buffer{
        int capacity;
        deque<T> arr;
    public:
        circular_buffer(int cap){
            capacity = cap;
        }
        void push_back(T data){
            if(arr.size() == capacity) arr.pop_front();
            arr.push_back(data);
        }
        void pop_front(){
            if(!arr.empty()) arr.pop_front();
        }
        int size(){
            return arr.size();
        }
        T& operator[](int i){
            return arr[i];
        }
};
int main(){
    int capacity;
    cin >> capacity;
    circular_buffer<int> cbi(capacity);

    int N;
    cin >> N;
    for(int i=0; i<N; i++){
        string cmd;
        cin >> cmd;
        if(cmd=="push_back"){
            int data;
            cin >> data;
            cbi.push_back(data);
        }else if(cmd=="pop_front"){
            cbi.pop_front();
        }else if(cmd=="print"){
            for(int j=0; j<cbi.size(); j++){
                cout << cbi[j] << endl;
            }
            cout << "----" << endl;
        }
    }
    return 0;
}