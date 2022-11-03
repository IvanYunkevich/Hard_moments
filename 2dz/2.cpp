#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;

//======Task1============================================================================
template <typename T>
void Swap(T* firstPtr, T* secondPtr)
{
    T temp = move(*firstPtr);
    *firstPtr = move(*secondPtr);
    *secondPtr = move(temp);
}
//======Task2============================================================================
template <typename T1>
void SortPointers(vector <T1*>& v)
{
    sort(v.begin(), v.end(), [](T1* first, T1* second)
        {
            return *first < *second;
        });
}

class Timer
{
private:
    using clock_t = chrono::high_resolution_clock;
    using second_t = chrono::duration<double, ratio<1>>;
    string _name;
    chrono::time_point<clock_t> _begin;
    double elapsed() const
    {
        return chrono::duration_cast<second_t>(clock_t::now() - _begin).count();
    }
public:
    Timer() : _begin(clock_t::now()) {}
    Timer(string name)
        : _name(name), _begin(clock_t::now()) {}
    void start(string name)
    {
        _name = name;
        _begin = clock_t::now();
    }
    void print() const
    {
        cout << _name << " " << elapsed() * 1000 << "ms" << ' ';
    }
};

void task1()
{
    char First = 'M';
    char Second = 'K';
    char* fPtr = &First;
    char* sPtr = &Second;
    cout << "First: " << *fPtr << ", Second: " << *sPtr << endl;
    cout << "Swapping" << endl;
    Swap<char>(fPtr, sPtr);
    cout << "First: " << *fPtr << ", Second: " << *sPtr << endl;
}
void task2()
{
    int a = 22, b = 13, c = 2, d = 66, e = 11;
    vector<int*> MVector = { &a,&b,&c,&d,&e };
    for (int i = 0; i < MVector.size(); i++)
    {
        cout << *MVector.at(i) << " ";
    }
    cout << endl;
    cout << "sorting" << endl;
    SortPointers(MVector);
    for (int i = 0; i < MVector.size(); i++)
    {
        cout << *MVector.at(i) << " ";
    }
    cout << endl;
}
////======Task3============================================================================
void task3()
{
    ifstream file("War_and_peace.txt");
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0);
    string s(size, ' ');
    file.read(&s[0], size);
    string lettters = "АЕЁИОУЫЭЮЯаеёиоуэюя";

    int count = 0;
    Timer timer("count_if && find");
    count = count_if(s.begin(), s.end(), [&lettters](char& c)
        {
            return lettters.find(c) != string::npos;
        });
    timer.print();
    cout << count << endl;

    count = 0;
    timer.start("count_if && for");
    count = count_if(s.begin(), s.end(), [&lettters](char& c)
        {
            for (size_t i = 0; i < lettters.size(); ++i)
            {
                if (lettters[i] == c) return true;
            } return false;
        });
    timer.print();
    cout << count << endl;

    count = 0;
    timer.start("for && find");
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (lettters.find(s[i]) != string::npos) count++;
    }
    timer.print();
    cout << count << endl;

    count = 0;
    timer.start("for && for");
    for (size_t i = 0; i < s.size(); ++i) 
    {
        for (size_t j = 0; j < lettters.size(); ++j)
        {
            if (s[i] == lettters[j])
            {
                count++;
                break;
            }
        }
    }
    timer.print();
    cout << count << endl;
}
int main()
{
    cout << "====1 Task====" << endl;
    task1();
    cout << "====2 Task====" << endl;
    task2();
    cout << "====3 Task====" << endl;
    task3();
    return 0;
}