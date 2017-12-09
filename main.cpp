#include "main.hpp"

#include "cli/help.hpp"
#include "cli/list.hpp"
#include "cli/summary.hpp"
#include "cli/version.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return 0;
	}
	if (string(argv[1]) == "--help" or string(argv[1]) == "-h")
	{
		scilog_cli::help_command();
		return 0;
	}
	else if (string(argv[1]) == "--version" or string(argv[1]) == "-v")
	{
		scilog_cli::version_command();
		return 0;
	}
	else if (string(argv[1]) == "list")
	{
		scilog_cli::list_type selected_type = scilog_cli::list_type::all;
		if (argc > 3)
		{
			for (unsigned int i = 3; i < argc; i++)
			{
				if (string(argv[i]) == "--type=learn")
				{
					selected_type = scilog_cli::list_type::learn;
				}
				else if (string(argv[i]) == "--type=project")
				{
					selected_type = scilog_cli::list_type::project;
				}
			}
		}
		scilog_cli::list_command(string(argv[2]),selected_type);
		return 0;
	}
	else if (string(argv[2]) == "summary-month")
	{
		if (argc == 3)
		{
			scilog_cli::command_summary_month(string(argv[1]));
		}
		else
		{
			bool topics = false;
			for (unsigned int i = 3; i < argc; i++)
			{
				if (string(argv[i]) == "--topics")
				{
					topics = true;
				}
			}
			if (topics)
			{
				scilog_cli::command_summary_month_by_topics(string(argv[1]));
			}
		}
		return 0;
	}
	return 0;
}
