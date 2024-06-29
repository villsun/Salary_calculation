#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
	try
	{
		Job my_job;
		my_job.Show_Parameters();
		my_job.Show_Job();
		my_job.Add_Day();
		my_job.Show_Job();
		my_job.Show_Salary();
		my_job.Save_in_File();
	}
	catch (const std::exception& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	
	return 0;
}