#include<iostream>
#include<iomanip>

using namespace std;

const int LOWER_LIMIT = 0;
const int UPPER_LIMIT = 12;

int RaiseIntToPower(int n, int k){
    int result = 1;
    for(int i = 0; i < k; i++){
        result *= n;
    }
    return result;
}

int main()
{
    cout << "   |   2|    N|" << endl;
    cout << "  N|  N |   2 |" << endl;
    cout << "---+----+------------" << endl;
    for(int n = LOWER_LIMIT; n <= UPPER_LIMIT; n++){
        cout << setw(3) << n << "|";
        cout << setw(4) << RaiseIntToPower(n, 2) << "|";
        cout << setw(5) << RaiseIntToPower(2, n) << "|" << endl;
    }

    return 0;
}