#include "scilog_file.hpp"

using namespace std;

namespace scilog_cli
{
	string get_filename_from_month_number(const string& x)
	{
		if (x == "1")
		{
			return "01-january.xml";
		}
		else if (x == "2")
		{
			return "02-february.xml";
		}
		else if (x == "3")
		{
			return "03-march.xml";
		}
		else if (x == "4")
		{
			return "04-april.xml";
		}
		else if (x == "5")
		{
			return "05-may.xml";
		}
		else if (x == "6")
		{
			return "06-june.xml";
		}
		else if (x == "7")
		{
			return "07-july.xml";
		}
		else if (x == "8")
		{
			return "08-august.xml";
		}
		else if (x == "9")
		{
			return "09-september.xml";
		}
		else if (x == "10")
		{
			return "10-october.xml";
		}
		else if (x == "11")
		{
			return "11-november.xml";
		}
		else if (x == "12")
		{
			return "12-december.xml";
		}
	}
}