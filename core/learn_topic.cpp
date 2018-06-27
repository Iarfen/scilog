#include "learn_topic.hpp"

using namespace std;

namespace scilog_cli
{
	learn_topic::learn_topic() : topic(),pages()
	{
	}

	learn_topic::learn_topic(const string& new_type,const string& new_category,const string& new_name,const string& new_start_date,const string& new_end_date,const string& new_description,const int& new_pages) : topic(new_type,new_category,new_name,new_start_date,new_end_date,new_description),pages(new_pages)
	{
	}

	topic_kind learn_topic::get_kind() const
	{
		return topic_kind::learn;
	}
}
