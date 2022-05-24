#pragma once
class Cond
{
public:
	Cond() : m_data(0) {}

	bool never(int arg1,int arg2);
	bool equal(int arg1, int arg2);
	bool less(int arg1, int arg2);
	bool lessOrEqual(int arg1, int arg2);
	bool always(int arg1, int arg2);
	bool notEqual(int arg1, int arg2);
	bool bigOrEqual(int arg1, int arg2);
	bool big(int arg1, int arg2);

private:
	int m_data;
};

