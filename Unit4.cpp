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

//��ʼ�����봰��
void __fastcall TForm4::InitInputWnd()
{
        //TODO: Add your source code here
        InitTableHead();
        InitColHead();
}
//��ʼ����ͷ
void __fastcall TForm4::InitTableHead()
{
        //TODO: Add your source code here


}
//��ʼ���к�
void __fastcall TForm4::InitColHead()
{

}

//������������ĺϷ��ԣ��Ϸ�����true�����򷵻�false��
BOOL __fastcall TForm4::CheckDataError()
{
        //TODO: Add your source code here

        return  true;
}

//�����ۼ�¼���µ�����
void __fastcall TForm4::UpdateSaleRecord(AnsiString KindName, AnsiString SaleCount, AnsiString SaleMoney)
{
        
}
void __fastcall TForm4::Button2Click(TObject *Sender)
{
        StoreFlag=true;
        Close();        
}
//---------------------------------------------------------------------------
