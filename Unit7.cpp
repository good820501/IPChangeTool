//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//#include"shlobj.h"
#include "Unit7.h"
#include <FileCtrl.hpp>
#include <io.h>
#include "DataCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button3Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button1Click(TObject *Sender)
{
        //
          const   AnsiString   Caption="选择保存文件的路径";   
          const   WideString   Root="我的电脑";
          AnsiString   Directory;
         if(SelectDirectory(Caption,   Root,Directory))
                  Edit1->Text   =Directory+"\\";

}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button2Click(TObject *Sender)
{
        //
        AnsiString      FullDBName;
        AnsiString      ExeName;
        AnsiString      BakFileName;
        AnsiString      BakDir;
        int             Pos,Len;
        if(Edit1->Text!="")
        {
                if(_access(Edit1->Text.c_str(),0)==0)
                {
                        ExeName=ExtractFilePath(Application->ExeName);
                        ExeName+="DB\\CoalSale.mdb";
                        BakFileName=GetBakFileName();
                        Pos = Edit1->Text.Pos('\\');
                        Len = strlen(Edit1->Text.c_str())-1;
                        if(Pos==0)
                                BakDir=Edit1->Text+"\\";
                        else
                                BakDir=Edit1->Text;
                        BakFileName=BakDir+BakFileName;
                        CopyFile(ExeName.c_str(),BakFileName.c_str(),0);
                        ShowMessage("备份完毕");
                }
                else
                {
                        ShowMessage("选择的目录无效，请重新选择！");
                }
        }
        else
        {
                ShowMessage("请选择备份目录！");
        }

}
//---------------------------------------------------------------------------

//获取备份文件的名称
AnsiString __fastcall TForm7::GetBakFileName()
{
        //TODO: Add your source code here
        AnsiString      RetFileName;
        AnsiString      StrTemp;
        TDateTime       NowTime=Now();
        StrTemp=NowTime.DateString();
        StrTemp+=".bak";
        return StrTemp;
}
void __fastcall TForm7::Button4Click(TObject *Sender)
{
        if(OpenDialog1->Execute())
        {
                Edit2->Text=OpenDialog1->FileName;

        }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button5Click(TObject *Sender)
{
       AnsiString      FullDBName;
       AnsiString      ExeName;

       ExeName=ExtractFilePath(Application->ExeName);
       ExeName+="DB\\CoalSale.mdb";

       if(_access(Edit2->Text.c_str(),0)==0)
       {
                if(MessageBox(Handle,"即将覆盖现有的数据文件，确定吗？","数据覆盖确认",MB_OKCANCEL)==1)
                {
                        DataModule1->StopDBCon();
                        CopyFile(Edit2->Text.c_str(),ExeName.c_str(),0);
                        ShowMessage("恢复完毕");
                }
       }
       else
       {
                ShowMessage("指定的数据文件不存在，请重新选择!");
       }
}
//---------------------------------------------------------------------------
