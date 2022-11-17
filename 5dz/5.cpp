#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
//======Task1============================================================================
template <typename T, typename T1>
void uniqueElements(T1 begin, T1 end)
{
    set<T> temp;
    T1 m = begin;
    while (m != end)
    {
        temp.insert(*m);
        m = next(m);
    }
    for (auto& i : temp)
    {
        cout << i << ",";
    }
    cout << endl << endl;
}
void task1()
{
	vector<string> myString = { "one", "two", "two", "one", "three", "two", "four" };
	cout << "vector" << endl;
	uniqueElements<string>(myString.begin(), myString.end());
	cout << "list" << endl;
	list<string> secondString = { "two", "three", "two", "one", "three", "two", "four" };
	uniqueElements<string>(secondString.begin(), secondString.end());
}
//======Task2============================================================================
void task2()
{
	string myString;
	string temp;
	cout << "Enter some text: " << endl;
	getline(cin, myString);
	multimap<int, string>m;
	int n = 0;
	int begin = 0;
	int end = 0;
	for (auto i : myString)
	{
		end++;
		if (i == '.' || i == '!' || i == '?' || i + 1 == string::npos)
		{
			temp.clear();
			copy(myString.begin() + begin, myString.begin() + end, back_inserter(temp));
			n = count_if(myString.begin() + begin, myString.begin() + end, [](char f) { return (f == ' '); });
			m.insert({ ++n,temp });
			begin = end + 1;
		}
	}
	cout << endl;
	for (auto i : m)
	{
		cout << "word count: " << i.first << "  " << i.second << endl;
	}
}
int main()
{
	//task1();
	task2();
    return 0;
};