// HomeWork3P1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


//****************
class Student
{

private:
	int grade;
	string fname, lname;

public:
	Student(const string& name, const string& last, int g) : fname(name), lname(last), grade(g) {}

	int checkGrade() const
	{
		return grade;
	}

	void displayStudents() const
	{
		cout << fname << " " << lname << " " << grade << '\n';
	}

	bool operator>(const Student& other) const
	{
		return grade > other.grade;
	}

};
//****************







//****************
int main()
{
	int grade;
	string fname, lname;
	
	ifstream myfile("test.txt");

	

	if (myfile.is_open())
	{
		vector<Student> students;
		string fname, lname;
		int grade;

		while (myfile >> fname >> lname >> grade)
		{
			Student student(fname, lname, grade);
			students.push_back(student);

		}
		
		sort(students.begin(), students.end(), greater<Student>());

		for (const Student& student : students)
		{
			student.displayStudents();
		}
		
	}


	else
	{
		cout << "Error loading test.txt file " << endl;
	}
	


	return 0;

}
