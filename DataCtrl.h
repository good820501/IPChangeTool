//---------------------------------------------------------------------------

#ifndef DataCtrlH
#define DataCtrlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>

//---------------------------------------------------------------------------
class TDataModule1 : public TDataModule
{
__published:	// IDE-managed Components
        TADOConnection *ADOConnection1;
        TADOQuery *ADOQuery1;
        TADOQuery *ADOQuery2;
private:	// User declarations
public:		// User declarations
        __fastcall TDataModule1(TComponent* Owner);
        void __fastcall GetDBParams(int &DBType,int &HasPass, AnsiString & DBName,AnsiString  &DBServerName, AnsiString & DBPass, AnsiString & User);
        bool __fastcall TestDBConn(int  DBType, int  HasPass,AnsiString DBName, AnsiString  DBServerName, AnsiString  DBPass, AnsiString  User,AnsiString &ErrorInfo);
        void __fastcall SetDBParams(int DBType, int HasPass, AnsiString DBName,AnsiString  DBServerName, AnsiString DBPass, AnsiString User);
        void __fastcall InitAdoQuery(TADOQuery * ADOQuery1, AnsiString StrSql);
        bool __fastcall InitDBLink(AnsiString &ErrorMsg);
        AnsiString __fastcall GetLinkString(int DBType,int HasPass,AnsiString DBName,AnsiString  DBServerName,AnsiString DBPass,AnsiString  UserName);
        void __fastcall InitSQLDBLink(AnsiString & ErrorMsg);
        bool __fastcall InitDBLinkWithoutCfg(AnsiString DBFullName);
        void __fastcall StopDBCon();

protected:
};
//---------------------------------------------------------------------------
extern PACKAGE TDataModule1 *DataModule1;
//---------------------------------------------------------------------------
#endif
