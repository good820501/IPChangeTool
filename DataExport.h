//---------------------------------------------------------------------------

#ifndef DataExportH
#define DataExportH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
void     DBGridToExcel(TDBGrid   *DBGrid);
void     ListViewToExcel(TListView *dbg,AnsiString UnitName,AnsiString WorkerName);
bool     GetDestFilePath(AnsiString &FilePath);
//---------------------------------------------------------------------------
#endif
