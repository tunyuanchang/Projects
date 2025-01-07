#include<bits/stdc++.h>
using namespace std;

void merge(vector<int> &vec, int left, int mid, int right) {
	vector<int> L(vec.begin() + left, vec.begin() + mid + 1);
	vector<int> R(vec.begin() + mid + 1, vec.begin() + right + 1);
	
	int idx_L = 0, idx_R = 0;
	
	L.insert(L.end(), 1e9 + 1);
	R.insert(R.end(), 1e9 + 1);
	
	for(int i = left ; i <= right; i++)
        vec[i] = (L[idx_L] < R[idx_R]) ?L[idx_L++] :R[idx_R++];
}
void mergeSort(vector<int> &vec, int left, int right) {
	if(left < right){
        int mid = (left + right) / 2;
	    mergeSort(vec, left, mid);
	    mergeSort(vec, mid + 1, right);
	    merge(vec, left, mid, right);
    }
}

int main(){
    int N, M, S, E;
    cin >> N >> M;

    vector<int> start(1, 0), end(1, M); 
    unsigned long long ans = 0;

    for(int i = 0 ; i < N ; i++){
        cin >> S >> E;
        start.push_back(S);
        end.push_back(E);
        ans += abs(S - E);
    }
    mergeSort(start, 0, N - 1);
    mergeSort(end, 0, N - 1);

    for(int i = 0 ; i <= N ; i++){
        cout << start[i] << ' ' << end[i] << '\n';
        ans += abs(start[i] - end[i]);
    }
    
    cout << ans << endl;
}
