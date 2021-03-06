#include "help.hpp"

#include <iostream>

using namespace std;

namespace scilog_cli
{
	void command_help()
	{
		cout << "scilog is a command-line utility that tracks the science activity that the user has done during the day, in order to be able to have a summary of the week, of the month, and of the year, among any other useful information." << endl << endl;
		cout << "    scilog <command> <month-number> [year]" << endl << endl;
		cout << "commands:" << endl;
		cout << "    --help,-h                              display this help message" << endl;
		cout << "    --version,-v                           display the version of scilog" << endl << endl;
		cout << "    create-month-file <month-number>       creates the file of the given month" << endl;
		cout << "    create-year-files                      creates all the files of the year" << endl << endl;
		cout << "    list <month-number> [year]             list all the entries of the selected month" << endl;
		cout << "    list --kind=learn|project              list only entries of the selected kind" << endl;
		cout << "    list --kind=learn" << endl
			 << "      --type=<value>                    list only entries of the selected type for learn entries:" << endl;
		cout << "      for learn type: type=book|documentation|planification" << endl;
		cout << "    list --kind=project" << endl
			 << "      --type=<value>                    list only entries of the selected type for project entries:" << endl;
		cout << "      for project type: type=programming|design|theory|planification" << endl;
		cout << "    list --order_by=date|topic             list entries ordered by the value given" << endl << endl;
		cout << "    list-categories                        list all the categories that topics can have" << endl << endl;
		cout << "    list-topics                            list the topics of the year" << endl << endl;
		cout << "    open                                   opens the actual file" << endl;
		cout << "    open <month-number> [year]             opens the selected file" << endl;
		cout << "    open --topics                          opens the file of topics" << endl;
		cout << "    open [year] --topics                   opens the file of topics of the selected year" << endl << endl;
		cout << "    open-dir                               opens the directory of the actual year" << endl;
		cout << "    open-dir [year]                        opens the directory of the selected year" << endl << endl;
		cout << "    summary                                summarizes the work of the year" << endl;
		cout << "    summary <month-number> [year]          summarizes the work of the month or year selected" << endl << endl;
		cout << "    summary-topics                         summarizes the topics worked and learned" << endl;
		cout << "    summary-topics <month-number> [year]   summarizes the topics of the month or year selected" << endl << endl;
		cout << "    summary-sciences                       summarizes the sciences worked on" << endl;
		cout << "    summary-sciences <month-number> [year] summarizes the sciences of the month or year selected" << endl << endl;
		cout << "    validate                               validates all the files of the folder (both months and topics files)" << endl;
		cout << "    validate <month-number>                validates the file of the given month" << endl;
		cout << "    validate --topics                      validates the topics.scilog_topics file" << endl;
	}
}
