#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
//=======Task1============================================================================
template<typename T>
void insert_sorted(T& arr, int input) 
{
    arr.insert(upper_bound(arr.begin(), arr.end(), input), input);
}
void task1()
{
    vector<int> arr = {4, 3, 1, 2, 5};
    cout << "Your arr: "; for (const auto n : arr) cout << n << " ";
    cout << endl;
    sort(arr.begin(), arr.end());
    cout << "Sorted arr: ";
    for (const auto n : arr) cout << n << " ";
    cout << endl;
    insert_sorted(arr, 2);
    cout << "adding a number in arr: ";
    for (const auto n : arr) cout << n << " ";
}
//=======Task2============================================================================
void task2()
{
    int e = 100;
    float err = 0;
    vector<double> a(e);
    vector<int> b;
    generate(a.begin(), a.end(), []() {return static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 100.0)); });
    cout << endl << "Vector a:" << endl;
    for (const auto n : a) cout << n << " ";
    copy(a.begin(), a.end(), back_inserter(b));
    cout << endl;
    cout << endl << "Vector b:" << endl;
    for (const auto n : b) cout << n << " ";
    err = accumulate(a.begin(), a.end(), 0.0, [](double x, double y) {return x + pow(y - static_cast<int>(y), 2); });
    cout << endl;
    cout << endl << "Digital signal error: " << err << endl;
}
int main()
{
    //task1();
    task2();
    return 0;
}