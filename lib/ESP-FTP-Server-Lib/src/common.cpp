#include "common.h"

/*
template <typename T>
T Split(String str, char parser)
{
	T str_array;
	int last_idx = 0;
	int next_idx = str.indexOf(parser, last_idx);
	do
	{
		str_array.push_back(str.substring(last_idx, next_idx));
		last_idx = next_idx + 1;
		next_idx = str.indexOf(parser, last_idx);
		if(next_idx == -1 && last_idx != 0)
		{
			str_array.push_back(str.substring(last_idx, str.length()));
		}
	} while (next_idx != -1);
	return str_array;
}
*/
