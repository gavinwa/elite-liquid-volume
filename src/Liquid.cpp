#include "StdAfx.h"
#include "Liquid.h"
#include "excel9.h"

LiquidDB * LiquidDB::m_instance = NULL;

LiquidDB * LiquidDB::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new LiquidDB();
	}
	return m_instance;
}

LiquidDB::LiquidDB()
{
}

bool LiquidDB::Load()
{
	const CString strfile = liquidFilePath();

	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range;
	Range iCell;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	COleVariant covTrue((short)TRUE);
	COleVariant covFalse((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);    

	//初始化COM的动态连接库
	if(!AfxOleInit())
	{
		return false;
	}

	// 启动Excel
	if(!app.CreateDispatch(_T("Excel.Application"))) 
	{
		return false;
	}

	app.SetVisible(FALSE);          //使Excel可见
	app.SetUserControl(FALSE);      //允许其它用户控制Excel

	books.AttachDispatch(app.GetWorkbooks());
	lpDisp = books.Open(strfile, covFalse, covTrue, covOptional, covOptional, covOptional, covTrue, covOptional,
		covOptional, covFalse, covFalse, covFalse, covFalse);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.GetWorksheets()); 

	//得到当前活跃sheet，如果Cell-edit mode，此操作不能返回，会一直等待
	lpDisp = book.GetActiveSheet();
	sheet.AttachDispatch(lpDisp); 

	int row = 2;
	Liquid oneLi;
	do {
		oneLi.m_name = getStrValue(sheet, range, row, 1);
		oneLi.m_boilingPoint = getDoubleValue(sheet, range, row, 2);
		oneLi.m_density = getDoubleValue(sheet, range, row, 3);
		oneLi.m_purity = getDoubleValue(sheet, range, row, 4);
		oneLi.m_molecularWeight = getDoubleValue(sheet, range, row, 5);
		oneLi.m_velocity = getDoubleValue(sheet, range, row, 6);
		oneLi.m_concentration = getDoubleValue(sheet, range, row, 7);
		if (!oneLi.m_name.IsEmpty())
		{
			m_liqList[oneLi.m_name] = oneLi;
		}
		++row;
	} while (!oneLi.m_name.IsEmpty());
	
	//关闭所有的book，退出Excel 
	book.Close (covFalse, COleVariant(strfile), covOptional);
	books.Close();
	app.Quit();
	return true;
}

const vector<CString> LiquidDB::getLiquidList()
{
	vector<CString> keys;
	for(auto itor = m_liqList.begin(); itor != m_liqList.end(); ++itor )
	{
		keys.push_back(CString(itor->first));
	}
	return keys;
}

Liquid LiquidDB::getLiquidByName(const CString name)
{
	auto itor = m_liqList.find(name);
	if (itor != m_liqList.end())
	{
		return itor->second;
	}
	else
	{
		return Liquid();
	}

}

CString LiquidDB::liquidFilePath()
{
	TCHAR path[256] = {0};
	GetCurrentDirectory(255, path);
	CString filePath(path);
	filePath = filePath.Trim();
	filePath += "\\液体配气参数.xlsx";
	return filePath;
}

double LiquidDB::getDoubleValue(_Worksheet &sheet, Range &range, int row, int colum)
{
	range.AttachDispatch(sheet.GetCells());
	range.AttachDispatch(range.GetItem(COleVariant((long)row), COleVariant((long)colum)).pdispVal);
	COleVariant vResult = range.GetValue();
	CString str;
	if (vResult.vt==VT_R8)     //8字节的数字
	{
		return vResult.dblVal;
	}
	else
	{
		return -1;
	}
}

CString LiquidDB::getStrValue(_Worksheet &sheet, Range &range, int row, int colum)
{
	range.AttachDispatch(sheet.GetCells());
	range.AttachDispatch(range.GetItem (COleVariant((long)row), COleVariant((long)colum)).pdispVal );
	COleVariant vResult = range.GetValue();
	if (vResult.vt == VT_BSTR)       //字符串
	{
		return CString(vResult.bstrVal);
	}
	else
	{
		return NULL;
	}
}

