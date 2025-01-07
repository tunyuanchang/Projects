#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, a;
    long long sum, ans;
    stack< tuple<int, int, long long> > M;
    cin >> n >> a;
    M.push(make_tuple(a, 1, a));
    ans = a;
    for(int i = 2 ; i <= n ; i++){
        cin >> a;
        for(int j = M.size() - 1 ; j >= 0 ; j--){
            if(get<0>(M.top()) > a){
                sum = get<2>(M.top()) + (long long)a * (i - get<1>(M.top()));
                break;
            }else M.pop();
        }
        if(M.empty()) sum = (long long)a * i;
        
        M.push(make_tuple(a, i, sum));
        ans += sum;
    }
    cout << ans << '\n';
}
