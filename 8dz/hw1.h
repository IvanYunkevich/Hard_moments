#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <optional>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
//======Task1============================================================================
struct Person
{
    string surname;
    string name;
    optional <string> patronymic;

    Person(string _surname, string _name, optional <string> _patronymic) : surname(_surname), name(_name), patronymic(_patronymic) {};

    friend bool operator< (const Person& t1, const Person& t2);
    friend bool operator== (const Person& t1, const Person& t2);
};
inline ostream& operator << (ostream& out, const Person& person)
{
    out << setw(13) << person.surname << setw(13) << person.name << setw(16) << person.patronymic.value_or("");
    return out;
}
bool operator< (const Person& p1, const Person& p2)
{
    return tie(p1.name, p1.surname, p1.patronymic) < tie(p2.name, p2.surname, p2.patronymic);
}
bool operator== (const Person& p1, const Person& p2)
{
    return tie(p1.name, p1.surname, p1.patronymic) == tie(p2.name, p2.surname, p2.patronymic);
}
//======Task2============================================================================
struct PhoneNumber
{
    int countryCode;
    int cityCode;
    string Number;
    optional <string> addNumber;

    PhoneNumber(int _countryCode, int _cityCode, string _Number, optional <string> _addNumber) : countryCode(_countryCode), cityCode(_cityCode), Number(_Number), addNumber(_addNumber) {};

    friend ostream& operator<< (ostream& out, const PhoneNumber& point);
    friend bool operator< (const PhoneNumber& t1, const PhoneNumber& t2);
    friend bool operator== (const PhoneNumber& t1, const PhoneNumber& t2);
};
inline ostream& operator<< (ostream& out, const PhoneNumber& phonenumber)
{
    out << "+" << phonenumber.countryCode << "(" << phonenumber.cityCode << ")" << phonenumber.Number << " " << phonenumber.addNumber.value_or("") << endl;
    return out;
}
bool operator<(const PhoneNumber& p1, const PhoneNumber& p2)
{
    return tie(p1.countryCode, p1.cityCode, p1.Number, p1.addNumber) < tie(p2.countryCode, p2.cityCode, p2.Number, p2.addNumber);
}
bool operator==(const PhoneNumber& p1, const PhoneNumber& p2)
{
    return tie(p1.countryCode, p1.cityCode, p1.Number, p1.addNumber) == tie(p2.countryCode, p2.cityCode, p2.Number, p2.addNumber);
}
//======Task3============================================================================
class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> ManNumber;
public:
    PhoneBook(ifstream& inFile)
    {
        if (inFile.is_open())
        {
            string surname;
            string name;
            string parent;

            int countryCode;
            int cityCode;
            string number;
            string addNumber;

            while (!inFile.eof())
            {
                inFile >> surname >> name >> parent >> countryCode >> cityCode >> number >> addNumber;
                ManNumber.push_back(make_pair(Person(surname, name, parent), PhoneNumber(countryCode, cityCode, number, addNumber)));
            }
        }
    }
    struct sortBySurname
    {
        bool operator()(const pair<Person, PhoneNumber>& left, const pair<Person, PhoneNumber>& right)
        {
            return left.first.surname < right.first.surname;
        }
    };
    void SortByName()
    {
        sort(ManNumber.begin(), ManNumber.end(), sortBySurname());
    };
    //Сортировка по телефону
    struct sort_second
    {
        bool operator()(const pair<Person, PhoneNumber>& left, const pair<Person, PhoneNumber>& right)
        {
            return left.second < right.second;
        }
    };
    void SortByPhone()
    {
        sort(ManNumber.begin(), ManNumber.end(), sort_second());
    };
    //Проверка наличия Фамилии
    tuple<string, PhoneNumber> GetPhoneNumber(const string& _surname)
    {
        auto defaultElement{ PhoneNumber{0, 0, "0", {}} };
        size_t count{ 0 };
        pair<Person, PhoneNumber> retElement = make_pair(Person{ "", "", "" }, PhoneNumber{ 0,0,"", nullopt });
        for_each(ManNumber.begin(), ManNumber.end(),
            [&_surname, &count, &retElement](const pair<Person, PhoneNumber>& element)
            {
                if (element.first.surname == _surname)
                {
                    count++;
                    retElement = element;
                }
            }
        );
        if (count > 1)
            return make_tuple("", retElement.second);
        else if (count == 0)
            return make_tuple("not found", defaultElement);

        return make_tuple("found more than one", defaultElement);
    }
    //Замена номера
    void ChangePhoneNumber(const Person& _person, const int& countryCode, const int& cityCode, const string& number, const optional <string>& addNumber)
    {
        size_t count{ 0 };
        for_each(ManNumber.begin(), ManNumber.end(),
            [&_person, &countryCode, &cityCode, &number, &addNumber, &count](pair<Person, PhoneNumber>& element)
            {
                if (element.first == _person)
                {
                    count++;
                    element.second.countryCode = countryCode;
                    element.second.cityCode = cityCode;
                    element.second.Number = number;
                    element.second.addNumber = addNumber;
                }
            }
        );
        if (count > 1)
        {
            cout << "found more than one man, error" << endl;
            return;
        }
        else if (count == 0)
        {
            cout << "not found a man with this name" << endl;
            return;
        }
        else if (count == 1)
        {
            cout << "The number of man has changed" << endl;
            return;
        }
    }
    friend ostream& operator << (ostream& out, const PhoneBook& phonebook);
    friend bool operator== (const PhoneNumber& t1, const PhoneNumber& t2);
};
inline ostream& operator << (ostream& out, const PhoneBook& phonebook)
{
    for (int i = 0; i < phonebook.ManNumber.size(); i++)
        out << phonebook.ManNumber[i].first << '\t' << phonebook.ManNumber[i].second;
    return out;
}