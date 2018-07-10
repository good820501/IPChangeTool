//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1Click(TObject *Sender)
{
        if(Edit1->Text!="")
        {
             StoreFlag=true;
             Close();
        }
        else
        {
                ShowMessage("请输入物品种类名称,或者点击取消按钮退出！");
                Edit1->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm5::FormShow(TObject *Sender)
{
        StoreFlag=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key==13)
        {
                Button1Click(Sender);
        }
}
//---------------------------------------------------------------------------
