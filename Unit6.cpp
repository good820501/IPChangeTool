//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include"stdio.h"
#include "Unit6.h"
#include "DataCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button3Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button1Click(TObject *Sender)
{
        //清空月数据
        AnsiString      FromData,EndData;
        AnsiString      HindInfo;
        AnsiString      StrTemp;
        TDateTime       NowTime;
        char            DataTmp[32];
        unsigned  short year,month,day;

        
        NowTime=Now();
        NowTime.DecodeDate(&year,&month,&day);
        memset(DataTmp,0x00,sizeof(DataTmp));
        sprintf(DataTmp,"%04d-%02d-%02d",year,month,1);
        FromData=DataTmp;
        memset(DataTmp,0x00,sizeof(DataTmp));
        sprintf(DataTmp,"%04d-%02d-%02d",year,month,31);
        EndData=DataTmp;
        memset(DataTmp,0x00,sizeof(DataTmp));
        sprintf(DataTmp,"%04d年%02d月",year,month);
        HindInfo="即将删除";
        StrTemp=DataTmp;
        StrTemp=StrTemp.Trim();
        HindInfo+=StrTemp;
        HindInfo+="的数据，确定吗？数据删除后不可恢复。";
        //ShowMessage(HindInfo);

        if(MessageBox(Handle,HindInfo.c_str(),"数据删除确认",MB_OKCANCEL)==1)
        {
               ClearData(FromData,EndData);
               ShowMessage("数据删除成功！");
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button2Click(TObject *Sender)
{
         //清空年数据
        AnsiString      FromData,EndData;
        AnsiString      HindInfo;
        AnsiString      StrTemp;
        TDateTime       NowTime;
        char            DataTmp[32];
        unsigned  short year,month,day;

        
        NowTime=Now();
        NowTime.DecodeDate(&year,&month,&day);
        memset(DataTmp,0x00,sizeof(DataTmp));
        sprintf(DataTmp,"%04d-%02d-%02d",year,1,1);
        FromData=DataTmp;
        memset(DataTmp,0x00,sizeof(DataTmp));
        sprintf(DataTmp,"%04d-%02d-%02d",year,12,31);
        EndData=DataTmp;
        memset(DataTmp,0x00,sizeof(DataTmp));
        sprintf(DataTmp,"%04d年",year);
        HindInfo="即将删除'";
        StrTemp=DataTmp;
        HindInfo+=StrTemp;
        HindInfo+="'的数据，确定吗？数据删除后不可恢复。";

        if(MessageBox(Handle,HindInfo.c_str(),"数据删除确认",MB_OKCANCEL)==1)
        {
               ClearData(FromData,EndData);
               ShowMessage("数据删除成功！");
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm6::ClearData(AnsiString FromData, AnsiString EndData)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="delete from Sal_Record where Sal_Date between #"+FromData;
        StrSql+="# and #"+EndData+"#";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
        DataModule1->ADOQuery2->ExecSQL();
}