#include <iostream>
#include <vector>
#include <string>
#include <optional> 
#include <numeric> 
#include <fstream>
using namespace std;
namespace dz
{
	class FullName
	{
	public:
		FullName() {};
		void setName(string _name) { name = _name; }
		void setSurname(string _surname) { surname = _surname; }
		void setPatronym(string _patronym) { patronym = _patronym; }
		friend class StudentsGroup;
	private:
		string name;
		string surname;
		optional <string> patronym;
	};

	class Student
	{
	public:
		Student() {};
		Student(string _name, string _surname, string _patronym)
		{
			fullname.setName(_name);
			fullname.setSurname(_surname);
			fullname.setPatronym(_patronym);
		};
		Student(string _name, string _surname)
		{
			fullname.setName(_name);
			fullname.setSurname(_surname);
		};
		void addGrade(int addGrade)
		{
			grades.push_back(addGrade);
			sGrade = accumulate(grades.begin(), grades.end(), 0) / grades.size();
		}
		friend class StudentsGroup;
	private:
		FullName fullname;
		vector<int> grades;
		int sGrade = 0;
	};

	class StudentsGroup
	{
	public:
		StudentsGroup() {};
		void addStudent(const Student& _name) { students.push_back(_name); };
		void Save(string _filename)
		{
			ofstream SV(_filename, ios::binary);
			for (auto it : students)
			{
				char* F = (char*)&it.fullname;
				SV.write(F, sizeof(FullName));
				char* S = (char*)&it.sGrade;
				SV.write(S, sizeof(int));
			}
			SV.close();
		};
		void Open(string _file)
		{
			ifstream MK(_file, ios::binary);
			while (MK)
			{
				if (MK.peek() != -1)
				{
					Student* ptrS = new Student;
					MK.read(reinterpret_cast<char*>(&ptrS->fullname), sizeof(FullName));
					MK.read(reinterpret_cast<char*>(&ptrS->sGrade), sizeof(int));
					students.push_back(*ptrS);
				}
			}
			MK.close();
		};
		double GetAverageScore(const Student& _name) { return _name.sGrade; };
		string GetAllInfo(const Student& _name)
		{
			string info = "";
			info = _name.fullname.name + " " + _name.fullname.surname;
			if (_name.fullname.patronym)
			{
				info = info + " " + _name.fullname.patronym.value();
			}
			info = info + ",Average grade is: " + to_string(_name.sGrade) + "\n";
			return info;
		};
		string GetAllInfo()
		{
			string info = "";
			for (auto it : students)
			{
				info = info + it.fullname.name + " " + it.fullname.surname;
				if (it.fullname.patronym)
				{
					info = info + " " + it.fullname.patronym.value();
				}
				info = info + ",Average grade is: " + to_string(it.sGrade) +"\n";
			}
			return info;
		};
	private:
		vector<Student> students;
	};

}
int main()
{
	using namespace dz;
	string filename = "save.bin";
	Student st1("Petr", "Artemovich", "Ilin");
	Student st2("Zakhar", "Zaitsev");
	Student st3("Aleksei", "Dubinin", "Mikhailovich");
	st1.addGrade(3);
	st2.addGrade(5);
	st3.addGrade(4);


	StudentsGroup group;
	group.addStudent(st1);
	group.addStudent(st2);
	group.addStudent(st3);
	cout << group.GetAllInfo();
	group.Save(filename);

	StudentsGroup* groupCopy = new StudentsGroup;
	groupCopy->Open(filename);
	cout << endl << endl << groupCopy->GetAllInfo();
	return 0;
}