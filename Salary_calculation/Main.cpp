#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
	try
	{
		Job my_job;
		int user_input;
		bool flag = true;
		do
		{
			cout << "Enter what you want to know:\n1 - Show parameters\n2 - Show job\n3 - Add day\n4 - Show salary\n5 - Save in file\n0 - to stop\n";
			cin >> user_input;
			switch (user_input)
			{
			case 0:
				flag = false;
				cout << "Good luck!\n";
				break;
			case 1:
				my_job.Show_Parameters();
				break;
			case 2:
				my_job.Show_Job();
				break;
			case 3:
				my_job.Add_Day();
				break;
			case 4:
				my_job.Show_Salary();
				break;
			case 5:
				my_job.Save_in_File();
				break;
			default:
				break;
			}
		} while (flag);
	}
	catch (const std::exception& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	
	return 0;
}