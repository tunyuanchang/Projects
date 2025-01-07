#include<bits/stdc++.h>
using namespace std;

struct cmp{
    bool operator()(pair<int, int> a, pair<int, int> b){
        if(a.first < b.first) return true;
        if(a.first > b.first) return false;
        if(a.second < b.second) return true;
        return false;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    priority_queue<pair<int, int>, vector< pair<int, int> >, cmp> pq;  //val idx
    int N, L, a;
    cin >> N >> L;
    for(int i = 1 ; i <= N ; i++){
        cin >> a;
        pq.push(make_pair(a, i));
        if(i >= L){
            cout << pq.top().first << " ";
            while(pq.top().second <= i - L + 1) pq.pop();
        }
    }
    cout << "\n";
}