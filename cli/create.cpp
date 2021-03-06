#include "create.hpp"
#include "cli/cli.hpp"

#include "core/conf.hpp"
#include "core/filesystem.hpp"
#include "core/sql_parser.hpp"
#include "core/xml_parser.hpp"

#include <iostream>
#include <fstream>

#include "boost/filesystem.hpp"
#include "cafi/cafi.hpp"

using namespace std;

namespace scilog_cli
{
	void command_create_month_file(const string& x)
	{
		string filename = cafi::get_filename_from_month(x);
		ofstream new_file (filename);

		new_file << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
		new_file << "<scilog>" << endl;
		new_file << "</scilog>" << endl;

		new_file.close();
	}

	void command_create_year_files()
	{
		command_create_month_file("1");
		command_create_month_file("2");
		command_create_month_file("3");
		command_create_month_file("4");
		command_create_month_file("5");
		command_create_month_file("6");
		command_create_month_file("7");
		command_create_month_file("8");
		command_create_month_file("9");
		command_create_month_file("10");
		command_create_month_file("11");
		command_create_month_file("12");
	}

	void command_create_sql_dump_month(const string& x,const string& year,const string& table_prefix)
	{
		string filename = cafi::get_filename_from_month(x);
		string filepath = cafi::root_dir + "/" + year + "/" + filename;
		if (boost::filesystem::exists(filepath))
		{
			vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath,x,year);
			vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(cafi::root_dir + "/topics.scilog_topics");
			print_sql_dump(entries,topics,table_prefix);
		}
		else
		{
			print_non_exist_message(filepath);
		}
	}

	void command_create_sql_dump_year(const string& year,const string& table_prefix)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(year);
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(cafi::root_dir + "/" + year + "/topics.scilog_topics");
		print_sql_dump(entries,topics,table_prefix);
	}

	void command_create_sql_dump_all_years(const string& table_prefix)
	{
		vector<string> paths = cafi::get_years_path(cafi::root_dir);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		vector<shared_ptr<topic>> topics = get_all_years_topics(paths);
		print_sql_dump(entries,topics,table_prefix);
	}
}
