//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "DataCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormShow(TObject *Sender)
{
        StoreFlag=false;
        InitInputWnd();
}
//---------------------------------------------------------------------------

//初始化出入窗口
void __fastcall TForm4::InitInputWnd()
{
        //TODO: Add your source code here
        InitTableHead();
        InitColHead();
}
//初始化表头
void __fastcall TForm4::InitTableHead()
{
        //TODO: Add your source code here


}
//初始化列号
void __fastcall TForm4::InitColHead()
{

}

//检验数据输入的合法性，合法返回true；否则返回false；
BOOL __fastcall TForm4::CheckDataError()
{
        //TODO: Add your source code here

        return  true;
}

//将销售记录更新到表中
void __fastcall TForm4::UpdateSaleRecord(AnsiString KindName, AnsiString SaleCount, AnsiString SaleMoney)
{
        
}
void __fastcall TForm4::Button2Click(TObject *Sender)
{
        StoreFlag=true;
        Close();        
}
//---------------------------------------------------------------------------
