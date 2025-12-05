#pragma once
#include <list>

template <typename T>
class Topic
{
public:
	Topic(int size):size(size){};
	~Topic() { clear(); };

	void send(T value)
	{
		values.push_back(value);
		if (values.size() > size && size > 0)
			values.pop_front();
	}

	bool read(T& t)
	{
		if (size <= 0)
		{
			if (values.empty())
			{
				return false;
			}
			else
			{
				t = values.front();
				values.pop_front();
				return true;
			}
		}

		if (values.empty())
		{
			return false;
		}
		else
		{
			t = values.back();
			return true;
		}
	}

	void clear()
	{
		values.clear();
	}
private:
	const int size;
	std::list<T> values;
};