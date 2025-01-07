#include <iostream>
#include <fstream>
#include "function.h"

using namespace std;

int main(int argc, char *argv[]) {
    int X, Y, Z; //Number of wolves, goats and cabbages
    cin >> X >> Y >> Z;
    Crossing p({X, Y, Z});
    p.solve();
    p.show_solutions();
}
