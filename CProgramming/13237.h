#include <iostream>
#include <vector>
#include <list>
#include <set>

using std::vector;
using std::set;
using std::list;
using std::cout;
using std::endl;

// A state contains seven components:
// The first three components denote the current numbers of
// wolves, goats and cabbages at the left bank of the river.
// The fourth to sixth components denote the current numbers
// of wolves, goats and cabbages at the right bank.
// The seventh component denotes the location of the boat:
// 1 means "left bank" and -1 means "right bank".
using State = vector<int>;
class Crossing
{
private:
    vector<int> _items;     // wolves, goats and cabbages
                           // we use vector<int> as a tuple (int, int, int)
                           // the first integer indicates the number of wolves
                           // the second integer indicates the number of goats
                           // the third integer indicates the number of cabbages.
    set<list<State>> _paths;  // trial paths in progress
    set<State> _explored;     // explored states
    set<list<State>> _solutions;
public:
    // specify the numbers of wolves, goats and cabbages
    Crossing(vector<int> np): _items {np} { }
    // the starting point of your implementation
    void solve();
    // extend to other possible states from a certain state
    set<State> extend(State s);
    // may use s[6] to indicate the direction of move
    State Go(State s, int wolf, int goat, int cabbage);
    // check the validity of a state
    bool valid(State s);
    // check if all people are at the right bank
    bool found(State s);
    void show_solutions() {
        for (auto path : _solutions) {
            for (auto s : path) {
                if (!s.empty()) {
                    cout << "(" << s[0] << ", " << s[1] << ", " << s[2] << ")";
                    cout << "(" << s[3] << ", " << s[4] << ", " << s[5] << ")";
                    if (s[6]==1) cout << " left\n";
                    else cout << " right\n";
                }
            }
            cout << "done" << endl;
        }
    }
};
