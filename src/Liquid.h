#pragma once
#include "excel9.h"
#include <map>
#include <vector>

using namespace std;

typedef struct _Liquid
{
public:
	CString m_name;
	double m_density;
	double m_molecularWeight;
	double m_boilingPoint;
} Liquid;

class LiquidDB
{
public:
	static LiquidDB *getInstance();

	bool Load();
	const vector<CString> getLiquidList();
	Liquid getLiquidByName(const CString);

private:
	LiquidDB();
	CString liquidFilePath();
	CString getStrValue(_Worksheet &sheet, Range &range, int row, int colum);
	double getDoubleValue(_Worksheet &sheet, Range &range, int row, int colum);

	std::map<CString, Liquid> m_liqList;

	static LiquidDB * m_instance;
};
