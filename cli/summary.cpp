#include "summary.hpp"
#include "cli/cli.hpp"
#include "core/entry.hpp"
#include "core/topic.hpp"
#include "core/categories.hpp"
#include "core/xml_parser.hpp"
#include "core/filesystem.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "boost/filesystem.hpp"

using namespace std;

namespace scilog_cli
{
	void command_summary_month(const string& x,const string& directory_path)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (!boost::filesystem::exists(filepath))
		{
			print_non_exist_message(filepath);
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
		print_summary(entries);
	}

	void command_summary_month_by_topics(const string& x,const string& directory_path)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		if (!boost::filesystem::exists(filepath))
		{
			print_non_exist_message(filepath);
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
		print_topics(entries);
	}

	void command_summary_month_by_sciences(const string& x,const string& directory_path)
	{
		string filename = scilog_cli::get_filename_from_month_number(x);
		string filepath = directory_path + "/" + filename;
		string topicspath = directory_path + "/topics.scilog_topics";
		if (!boost::filesystem::exists(filepath))
		{
			print_non_exist_message(filepath);
			return;
		}
		if (!boost::filesystem::exists(topicspath))
		{
			print_non_exist_message(topicspath);
			return;
		}
		vector<shared_ptr<entry>> entries = create_entries_from_scilog_file(filepath);
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(topicspath);
		print_sciences(entries,topics);
	}

	void command_summary_year(const string& directory_path)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(directory_path);
		print_summary(entries);
	}

	void command_summary_year_by_topics(const string& directory_path)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(directory_path);
		print_topics(entries);
	}

	void command_summary_year_by_sciences(const string& directory_path)
	{
		vector<shared_ptr<entry>> entries = get_year_entries(directory_path);
		string topicspath = directory_path + "/topics.scilog_topics";
		if (!boost::filesystem::exists(topicspath))
		{
			print_non_exist_message(topicspath);
			return;
		}
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(topicspath);
		print_sciences(entries,topics);
	}

	void command_summary_all_years(const string& directory_path)
	{
		vector<string> paths = get_years_path(directory_path);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		print_summary(entries);
	}

	void command_summary_all_years_by_topics(const string& directory_path)
	{
		vector<string> paths = get_years_path(directory_path);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		print_topics(entries);
	}

	void command_summary_all_years_by_sciences(const string& directory_path)
	{
		vector<string> paths = get_years_path(directory_path);
		vector<shared_ptr<entry>> entries = get_all_years_entries(paths);
		string topicspath = directory_path + "/topics.scilog_topics";
		if (!boost::filesystem::exists(topicspath))
		{
			print_non_exist_message(topicspath);
			return;
		}
		vector<shared_ptr<topic>> topics = create_topics_from_scilog_file(topicspath);
		print_sciences(entries,topics);
	}

	void print_summary(const vector<shared_ptr<entry>>& entries)
	{
		int total_learn_entries = 0;
		int total_project_entries = 0;

		int total_learn_book_entries = 0;
		int total_learn_documentation_entries = 0;
		int total_learn_planification_entries = 0;

		int total_project_theory_entries = 0;
		int total_project_design_entries = 0;
		int total_project_programming_entries = 0;
		int total_project_planification_entries = 0;

		for (const shared_ptr<entry>& entry : entries)
		{
			if (entry->get_type() == "learn")
			{
				total_learn_entries++;
				if (entry->get_subtype() == "book")
				{
					total_learn_book_entries++;
				}
				else if (entry->get_subtype() == "documentation")
				{
					total_learn_documentation_entries++;
				}
				else if (entry->get_subtype() == "planification")
				{
					total_learn_planification_entries++;
				}
			}
			else if (entry->get_type() == "project")
			{
				total_project_entries++;
				if (entry->get_subtype() == "theory")
				{
					total_project_theory_entries++;
				}
				else if (entry->get_subtype() == "design")
				{
					total_project_design_entries++;
				}
				else if (entry->get_subtype() == "programming")
				{
					total_project_programming_entries++;
				}
				else if (entry->get_subtype() == "planification")
				{
					total_project_planification_entries++;
				}
			}
		}
		cout << scilog_cli::white_text << "total entries: " << scilog_cli::green_text << entries.size() << endl;

		cout << scilog_cli::white_text << "total learn entries: " << scilog_cli::green_text << total_learn_entries << "    " << (100 * total_learn_entries / entries.size()) << " %" << endl;
		cout << scilog_cli::white_text << "total project entries: " << scilog_cli::green_text << total_project_entries << "    " << (100 * total_project_entries / entries.size()) << " %" << endl << endl;

		cout << scilog_cli::white_text << "learn book entries: " << scilog_cli::green_text << total_learn_book_entries << "    " << (100 * total_learn_book_entries / total_learn_entries) << " %" << endl;
		cout << scilog_cli::white_text << "learn documentation entries: " << scilog_cli::green_text << total_learn_documentation_entries << "    " << (100 * total_learn_documentation_entries / total_learn_entries) << " %" << endl;
		cout << scilog_cli::white_text << "learn planification entries: " << scilog_cli::green_text << total_learn_planification_entries << "    " << (100 * total_learn_planification_entries / total_learn_entries) << " %" << endl << endl;

		cout << scilog_cli::white_text << "project theory entries: " << scilog_cli::green_text << total_project_theory_entries << "    " << (100 * total_project_theory_entries / total_project_entries) << " %" << endl;
		cout << scilog_cli::white_text << "project design entries: " << scilog_cli::green_text << total_project_design_entries << "    " << (100 * total_project_design_entries / total_project_entries) << " %" << endl;
		cout << scilog_cli::white_text << "project programming entries: " << scilog_cli::green_text << total_project_programming_entries << "    " << (100 * total_project_programming_entries / total_project_entries) << " %" << endl;
		cout << scilog_cli::white_text << "project planification entries: " << scilog_cli::green_text << total_project_planification_entries << "    " << (100 * total_project_planification_entries / total_project_entries) << " %" << endl;
	}

	void print_topics(const vector<shared_ptr<entry>>& entries)
	{
		map<string,int> learn_topics_count = map<string,int>();
		map<string,int> project_topics_count = map<string,int>();
		for (const shared_ptr<entry>& entry : entries)
		{
			if (entry->get_topic() != "")
			{
				if (entry->get_type() == "learn")
				{
					if (learn_topics_count.count(entry->get_topic()) == 0)
					{
						learn_topics_count[entry->get_topic()] = 0;
					}
					learn_topics_count[entry->get_topic()]++;
				}
				else if (entry->get_type() == "project")
				{
					if (project_topics_count.count(entry->get_topic()) == 0)
					{
						project_topics_count[entry->get_topic()] = 0;
					}
					project_topics_count[entry->get_topic()]++;
				}
			}
		}
		cout << scilog_cli::white_text << "total entries: " << scilog_cli::green_text << entries.size() << endl << endl;
		for (auto learn_topic_count : learn_topics_count)
		{
			cout << scilog_cli::white_text << "learn " << scilog_cli::green_text << learn_topic_count.first << ": " << learn_topic_count.second << endl;
		}
		cout << endl;
		for (auto project_topic_count : project_topics_count)
		{
			cout << scilog_cli::white_text << "project " << scilog_cli::green_text << project_topic_count.first << ": " << project_topic_count.second << endl;
		}
	}

	void print_sciences(const vector<shared_ptr<entry>>& entries,vector<shared_ptr<topic>>& topics)
	{
		map<string,int> learn_sciences_count = map<string,int>();
		map<string,int> project_sciences_count = map<string,int>();
		bool learn_entry;
		map<string,category> categories = get_all_categories_map();
		for (const shared_ptr<entry>& log_entry : entries)
		{
			if (log_entry->get_type() == "learn")
			{
				learn_entry = true;
			}
			else
			{
				learn_entry = false;
			}
			vector<shared_ptr<topic>>::iterator actual_topic = find_if(topics.begin(),topics.end(),[log_entry](const shared_ptr<topic>& x) -> bool { return x->get_name() == log_entry->get_topic(); });
			if (actual_topic == topics.end())
			{
				continue;
			}
			if (learn_entry)
			{
				if (learn_sciences_count[(*actual_topic)->get_category()] == 0)
				{
					learn_sciences_count[(*actual_topic)->get_category()] = 0;
				}
				learn_sciences_count[(*actual_topic)->get_category()]++;
			}
			else
			{
				if (project_sciences_count[(*actual_topic)->get_category()] == 0)
				{
					project_sciences_count[(*actual_topic)->get_category()] = 0;
				}
				project_sciences_count[(*actual_topic)->get_category()]++;
			}
			if ((*actual_topic)->get_category() != "")
			{
				category& actual_category = categories[(*actual_topic)->get_category()];
				while (true)
				{
					if (actual_category.get_name() == "")
					{
						break;
					}
					if (learn_entry)
					{
						if (learn_sciences_count[actual_category.get_name()] == 0)
						{
							learn_sciences_count[actual_category.get_name()] = 0;
						}
						learn_sciences_count[actual_category.get_name()]++;
					}
					else
					{
						if (project_sciences_count[actual_category.get_name()] == 0)
						{
							project_sciences_count[actual_category.get_name()] = 0;
						}
						project_sciences_count[actual_category.get_name()]++;
					}
					actual_category = categories[actual_category.get_parent_category()];
					if (actual_category.get_parent_category() == "")
					{
						break;
					}
				}
			}
		}
		cout << scilog_cli::white_text << "total of topics to learn: " << scilog_cli::green_text << learn_sciences_count.size() << endl;
		for (const auto& learn_science_count : learn_sciences_count)
		{
			cout << scilog_cli::white_text << "learn " << learn_science_count.first << ": " << scilog_cli::green_text << learn_science_count.second << endl;
		}
		cout << endl;
		cout << scilog_cli::white_text << "total of projects: " << scilog_cli::green_text << project_sciences_count.size() << endl;
		for (const auto& project_science_count : project_sciences_count)
		{
			cout << scilog_cli::white_text << "project " << project_science_count.first << ": " << scilog_cli::green_text << project_science_count.second << endl;
		}
	}
}
