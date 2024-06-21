#pragma once
#include <string>
#include <vector>

using namespace std;

struct Parameters
{
	double hourly_wage;
	double supplement_in_weekend;
	double supplement_in_evening;
	double tax;
};

struct Day
{
	string date;
	double start_work;
	double end_work;
	double number_hours_at_work;
	double earned_in_day;
};

class Job
{
private:
	Parameters parameters_in_file;
	vector<Day> array_day;
public:
	Job();
	void Show_Parameters();
	void Show_Job();
};