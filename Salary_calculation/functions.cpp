#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include "functions.h"

Job::Job()
{
	string path_parameters = "F:\\My programs in C++\\Salary_calculation\\Parameters.txt";
	/*cin >> path_parameters;*/ // Тут можна зробити щоб користувач вводив файл параметрів
	ifstream fin_parameters;
	fin_parameters.open(path_parameters);
	if (!fin_parameters.is_open())
	{
		throw runtime_error("File not found");
	}

	fin_parameters >> parameters_in_file.hourly_wage >> parameters_in_file.supplement_in_evening >> parameters_in_file.supplement_in_weekend >> parameters_in_file.tax;
	if (fin_parameters.fail()) {
		throw runtime_error("Error reading parameters");
	}

	/*cout << "parameters_in_file.hourly_wage = " << parameters_in_file.hourly_wage << endl;
	cout << "parameters_in_file.supplement_in_evening = " << parameters_in_file.supplement_in_evening << endl;
	cout << "parameters_in_file.supplement_in_weekend = " << parameters_in_file.supplement_in_weekend << endl;
	cout << "tax = " << parameters_in_file.tax << endl;*/

	fin_parameters.close();

	string path_work = "F:\\My programs in C++\\Salary_calculation\\Work.txt";
	/*cin >> path_work;*/ // Тут можна зробити щоб користувач вводив файл роботи
	ifstream fin_work;
	fin_work.open(path_work);
	string job = "F:\\My programs in C++\\Salary_calculation\\Work.txt";
	if (!fin_work.is_open()) {
		/* Функція */
		ofstream out_file_out(job);
		cout << "The file doesn't exist, but we created it!\n";
		out_file_out.close();
	}
	else
	{
		Day day_temp;
		string line;
		while (getline(fin_work, line))
		{
			istringstream iss(line); // istringstream дозволяє інтерпретувати рядок як потік вводу, щоб можна було легко розбити рядок на окремі значення, як це робиться з файлом чи консоллю.
			if (!(iss >> day_temp.date >> day_temp.start_work >> day_temp.end_work >> day_temp.number_hours_at_work >> day_temp.earned_in_day))
			{
				throw runtime_error("Error reading work");
			}
			array_day.push_back(day_temp);
		}
	}

	/*for (int i = 0; i < array_day.size(); i++)
	{
		cout << array_day[i].date << ' ' << array_day[i].start_work << ' ' << array_day[i].end_work << ' ' << array_day[i].number_hours_at_work << ' ' << array_day[i].earned_in_day << endl;
	}*/
}

void Job::Show_Parameters()
{
	cout << "parameters_in_file.hourly_wage = " << parameters_in_file.hourly_wage << endl;
	cout << "parameters_in_file.supplement_in_evening = " << parameters_in_file.supplement_in_evening << endl;
	cout << "parameters_in_file.supplement_in_weekend = " << parameters_in_file.supplement_in_weekend << endl;
	cout << "tax = " << parameters_in_file.tax << endl;
}

void Job::Show_Job()
{
	for (int i = 0; i < array_day.size(); i++)
	{
		cout << array_day[i].date << ' ' << array_day[i].start_work << ' ' << array_day[i].end_work << ' ' << array_day[i].number_hours_at_work << ' ' << array_day[i].earned_in_day << endl;
	}
}