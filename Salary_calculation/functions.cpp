#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string.h>
#include "functions.h"

Job::Job()
{
	string path_parameters = "F:\\My programs in C++\\Salary_calculation\\Parameters.txt";
	/*cout << "Enter the path where you save the settings:\n";*/
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
	//cout << "Enter the path where you save the work file:\n";
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
	/*for (int i = 0; i < array_day.size(); i++)
	{
		cout << array_day[i].date << ' ' << array_day[i].start_work << ' ' << array_day[i].end_work << ' ' << array_day[i].number_hours_at_work << ' ' << array_day[i].earned_in_day << endl;
	}*/
	for (const auto& element : array_day)
	{
		cout << element.date << ' ' << element.start_work << ' ' << element.end_work << ' ' << element.number_hours_at_work << ' ' << element.earned_in_day << '\n';
	}
}

bool Job::is_Weekend(const string &date)
{
	int day, month, year;
	char dot;

	istringstream iss(date);
	if (!(iss >> day >> dot >> month >> dot >> year)) {
		throw runtime_error("Invalid date format");
	}

	tm time_in = { 0,0,0,day,month - 1, year - 1900 }; // Створюється структура tm, яка представляє собою часову структуру.
	// Полям tm присвоюються значення : 0, 0, 0 - секунди, хвилини, години, day(день місяця), month - 1 (місяць - 1, тому що місяці у структурі tm індексуються з 0), year - 1900 (рік змінюється на рік з початку 1900 року).

	time_t time_temp = mktime(&time_in); // Функція mktime приймає покажчик на структуру tm (&time_in) і перетворює його у часову мітку (типу time_t), яка представляє час, який пройшов з 1 січня 1970 року до вказаного часу в time_in.

	// Перевіряємо, чи вдалося створити тимчасову мітку
	if (time_temp == -1) {
		throw runtime_error("Invalid date values");
	}

	const tm* time_out = localtime(&time_temp); // Функція localtime приймає часову мітку time_temp і перетворює її на місцевий час, представлений в структурі tm.
												 // Результат зберігається в time_out, яке є вказівником на структуру tm.
	// Перевіряємо, чи вдалося отримати місцевий час
	if (time_out == nullptr) {
		throw runtime_error("Failed to convert time");
	}

	int w_day = time_out->tm_wday; // З поля tm_wday структури tm, яка представляє день тижня(0 для неділі, 1 для понеділка, ..., 6 для суботи), отримується день тижня.

	return (w_day == 0 || w_day == 6);
}


void Job::Add_Day()
{
	do
	{
		string user_date;
		while (true)
		{
			cout << "Enter date:\n";
			cin >> user_date;
			if (user_date.size() != 10)
			{
				cout << "Error date!\nTry again!\n";
				continue;
			}
			else
			{
				break;
			}
		}

		double user_start_work;
		while (true)
		{
			cout << "Enter start work:\n";
			cin >> user_start_work;
			if (user_start_work < 00.00 || user_start_work>23.59)
			{
				cout << "Error start work!\nTry again!\n";
				continue;
			}
			else
			{
				break;
			}
		}
		double user_end_work;
		while (true)
		{
			cout << "Enter end work:\n";
			cin >> user_end_work;
			if (user_end_work < 00.00 || user_end_work>23.59)
			{
				cout << "Error end work!\nTry again!\n";
				continue;
			}
			else
			{
				break;
			}
		}

		double user_number_hours_at_work_minutes_start = (user_start_work - floor(user_start_work)) / 0.6;
		double user_number_hours_at_work_start_together = floor(user_start_work) + user_number_hours_at_work_minutes_start;

		double user_number_hours_at_work_minutes_end = (user_end_work - floor(user_end_work)) / 0.6;
		double user_number_hours_at_work_end_together = floor(user_end_work) + user_number_hours_at_work_minutes_end;

		double user_number_hours_at_work = user_number_hours_at_work_end_together - user_number_hours_at_work_start_together;

		if (user_start_work > user_end_work)
		{
			cout << "Error!\nTry again!\n";
			continue;
		}

		double local_hourly_wage = parameters_in_file.hourly_wage;
		if (is_Weekend(user_date))
		{
			local_hourly_wage += parameters_in_file.supplement_in_weekend;
		}
		if (user_start_work > 17)
		{
			local_hourly_wage += parameters_in_file.supplement_in_evening;
		}

		Day day_temp;
		day_temp.date = user_date;
		day_temp.start_work = user_start_work;
		day_temp.end_work = user_end_work;
		day_temp.number_hours_at_work = user_number_hours_at_work;
		day_temp.earned_in_day = user_number_hours_at_work * local_hourly_wage;

		array_day.push_back(day_temp);
		
		char flag;
		cout << "Do you want to continue?(y - yes, n - no)\n";
		cin >> flag;

		flag = tolower(flag);

		if (flag != 'y' && flag!='n')
		{
			throw runtime_error("Invalid input");
		}

		if (flag=='y')
		{
			continue;
		}
		else
		{
			break;
		}

	} while (true);
}

void Job::Save_in_File()
{
	string path_out = "F:\\My programs in C++\\Salary_calculation\\Work.txt";
	/*cout << "Enter the path where you want to save the file:\n";
	cin >> path_out;*/

	ofstream fout(path_out);

	if (!fout)
	{
		throw runtime_error("Error opening file for writing");
	}

	for (const auto& element : array_day)
	{
		fout << element.date << ' ' << element.start_work << ' ' << element.end_work << ' ' << element.number_hours_at_work << ' ' << element.earned_in_day << '\n';
	}

	fout.close();
}
