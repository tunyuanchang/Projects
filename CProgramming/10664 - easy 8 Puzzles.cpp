#include<bits/stdc++.h>
using namespace std;
using State = vector<int>;

int main(){
    State arr = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    set<pair<State, int>> ans;  //array step
    
    queue<tuple<State, int, int>> extend;  //array start steps
    set<State> explored;  //board
    
    explored.insert(arr);
    ans.insert(make_pair(arr, 0));
    extend.push(make_tuple(arr, 8, 1));

    while(!extend.empty()){
        auto [array, start, steps] = extend.front();
        extend.pop();

        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        for(int i = 0 ; i < 4 ; i++){
            int x = start % 3 + dx[i];
            int y = start / 3 + dy[i];
            if(x < 3 && x >= 0 && y < 3 && y >= 0){
                State new_array = array;
                new_array[start] = array[y * 3 + x];
                new_array[y * 3 + x] = array[start];
                
                if(explored.find(new_array) == explored.end() && steps <= 14){
                    explored.insert(new_array);
                    ans.insert(make_pair(new_array, steps));
                    extend.push(make_tuple(new_array, y * 3 + x, steps + 1));
                }
            }
        }
    }
    int n;
    cin >> n;
    while(n--){
        State board(9);
        for(int i = 0 ; i < 9 ; i++) cin >> board[i];
        for(auto PAIR : ans){
            if(board == PAIR.first){
                cout << "You can solve it within " << PAIR.second << " steps." << endl;
                break;
            }
            if(PAIR == *ans.rbegin()){
                cout << "You'd better skip this game." << endl;
            }
        }
    }
}