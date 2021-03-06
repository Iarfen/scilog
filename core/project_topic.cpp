#include "project_topic.hpp"

using namespace std;

namespace scilog_cli
{
	project_topic::project_topic() : topic()
	{
	}

	project_topic::project_topic(const string& new_category,const string& new_name,const string& new_start_date,const string& new_end_date,const string& new_description,const string& new_parent_topic,bool new_finished) : topic(new_category,new_name,new_start_date,new_end_date,new_description,new_parent_topic,new_finished)
	{
	}

	topic_kind project_topic::get_kind() const
	{
		return topic_kind::project;
	}
}
