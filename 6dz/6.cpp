#include <iostream>
#include <string>
#include <mutex>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
//=====Task1==========================================================================
class pcout : public ostringstream
{
public:
	pcout() = default;
	~pcout()
	{
		lock_guard<mutex> guard(m_lock);
		cout << this->str();
	}
private:
	static mutex m_lock;
};
mutex pcout::m_lock;

void func(int a)
{
	pcout() << "demonstration: " << a << endl;
	pcout() << "demonstration: " << a << endl;
}
void task1()
{
	thread th1(func, 1);
	thread th2(func, 2);
	thread th3(func, 3);
	th1.join();
	th2.join();
	th3.join();
}
//=====Task2==========================================================================
bool isPrime(uint32_t number) 
{
	if (number < 2)
		return false;

	bool answer = true;
	for (uint32_t i = 2; i <= sqrt(number); i++) 
	{
		if (number % i == 0) 
		{
			answer = false;
			break;
		}
	}
	return answer;
}
uint32_t findPrime(uint32_t n)
{
	uint32_t count = 1;
	uint32_t number = 2;
	while (count != n)
	{
		++number;
		if (isPrime(number))
		{
			++count;
			cout << "Progress: " << (static_cast<double>(count) / n) * 100. << "%" << endl;
		}
	}
	return number;
}
void task2()
{
	thread thr([](){cout << findPrime(1000000) << endl; });
	thr.join();
}
//=====Task3==========================================================================
mutex m;
void Owner(vector<int>& add)
{
	lock_guard f(m);
	srand(time(NULL));
	this_thread::sleep_for(1000ms);
	int x = rand() % 50;
	add.push_back(x);
	cout << "brought a thing: " << x << endl;
}

void Thief(vector<int>& del)
{
	lock_guard f(m);
	this_thread::sleep_for(500ms);
	auto it = max_element(del.begin(), del.end());
	cout << "stole a thing: " << *it << endl;
	del.erase(it);
}

void task3()
{
	vector<int> things = { 12, 9, 16, 77, 54, 34, 87, 71, 33, 56 };
	for (size_t i = 0; i < 30; i++)
	{
		thread owner([&]() {Owner(things); });
		thread thief([&]() {Thief(things); });
		owner.join();
		thief.join();
	}
}

int main()
{
	//task1();
	task2();
	//task3();
	return 0;
}