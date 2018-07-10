//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit4.h"
#include "DataCtrl.h"
#include "stdio.h"
#include      "DataExport.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm2::ExitSystem()
{
       
        
}
void __fastcall TForm2::Button5Click(TObject *Sender)
{
        if(Form1!=NULL)
        {
             Form1->ShowCaEditWnd();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button4Click(TObject *Sender)
{
        if(Form4!=NULL)
                Form4->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
        DateTimePicker1->Date=Now();        
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
        MakeReport();
}
//---------------------------------------------------------------------------

//生成统计报表
void __fastcall TForm2::MakeReport()
{
        //TODO: Add your source code here
        int             GridRows=1;
        int             ID;
        AnsiString      StrSql="select * from CoalKinds";
        AnsiString      KindName;
        TListItem       *ItemTemp;
        double          NowCount,NowMoney,MonthCount,MonthMoney,MonthAverage,YearCount,YearMoney,YearAverage;
        double          TotalNowCoun=0.0,TotalNowMoney=0.0,TotalMonthCount=0.0,TotalMonthMoney=0.0,TotalMonthAverage=0.0,TotalYearCount=0.0,TotalYearMoney=0.0,TotalYearAverage=0.0;
        ListView1->Items->Clear();
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        while(!DataModule1->ADOQuery1->Eof)
        {
                if(!DataModule1->ADOQuery1->FieldByName("Sale_Name")->Value.IsNull())
                {
                       KindName=DataModule1->ADOQuery1->FieldByName("Sale_Name")->Value;
                       KindName= KindName.Trim();
                }
                ID=DataModule1->ADOQuery1->FieldByName("ID")->Value;
                ItemTemp=ListView1->Items->Add();
                ItemTemp->Caption=IntToStr(GridRows);
                ItemTemp->SubItems->Add(KindName);

                GetDetailData(IntToStr(ID),&NowCount,&NowMoney,&MonthCount,&MonthMoney,&MonthAverage,&YearCount,&YearMoney,&YearAverage);
                ItemTemp->SubItems->Add(FormatFloat("0.00",NowCount));
                TotalNowCoun+=NowCount;
                ItemTemp->SubItems->Add(FormatFloat("0.00",NowMoney));
                TotalNowMoney+=NowMoney;
                ItemTemp->SubItems->Add(FormatFloat("0.00",MonthCount));
                TotalMonthCount+=MonthCount;
                ItemTemp->SubItems->Add(FormatFloat("0.00",MonthMoney));
                TotalMonthMoney+=MonthMoney;
                ItemTemp->SubItems->Add(FormatFloat("0.00",MonthAverage));
                TotalMonthAverage+=MonthAverage;
                ItemTemp->SubItems->Add(FormatFloat("0.00",YearCount));
                TotalYearCount+=YearCount;
                ItemTemp->SubItems->Add(FormatFloat("0.00",YearMoney));
                TotalYearMoney+=YearMoney;
                ItemTemp->SubItems->Add(FormatFloat("0.00",YearAverage));
                TotalYearAverage+=YearAverage;
                GridRows++;
                DataModule1->ADOQuery1->Next();
        }
        ItemTemp=ListView1->Items->Add();
        ItemTemp->Caption=IntToStr(GridRows);
        ItemTemp->SubItems->Add("合计");
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalNowCoun));
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalNowMoney));
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalMonthCount));
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalMonthMoney));
        if(TotalMonthCount!=0.0)
                TotalMonthAverage=TotalMonthMoney/TotalMonthCount;
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalMonthAverage));
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalYearCount));
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalYearMoney));
        if(TotalYearCount!=0.0)
                TotalYearAverage=TotalYearMoney/TotalYearCount;
        ItemTemp->SubItems->Add(FormatFloat("0.00",TotalYearAverage));
}
//枚举详细数据
void __fastcall TForm2::GetDetailData(AnsiString KindNo, double   * NowCount, double   * NowMoney, double   * MonthCount, double   * MonthMoney, double   * MonthAverage, double   * YearCount, double   * YearMoney, double   * YearAverage)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      DataStr;
        double          DataCount;
        TDateTime       DTNow;
        AnsiString      DateStr;
        AnsiString      MonthStr;
        unsigned  short year,month,day;
        char            MonthComposite[32];
        DTNow =Now();
        DateStr = DTNow.DateString();
        DTNow.DecodeDate(&year,&month,&day);


        StrSql="select * from Sal_Record where Sal_No='"+KindNo+"' and Sal_Date=#"+DateStr+"#";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
        DataModule1->ADOQuery2->Open();
        if(DataModule1->ADOQuery2->RecordCount>0)
        {
                //if(!DataModule1->ADOQuery2->FieldByName("Sal_Num")->Value.IsNull())
                *NowCount=DataModule1->ADOQuery2->FieldByName("Sal_Num")->Value;
                *NowMoney=DataModule1->ADOQuery2->FieldByName("Sal_Money")->Value;
        }
        //止月结果
        memset(MonthComposite,0x00,sizeof(MonthComposite));
        sprintf(MonthComposite,"%4d-%02d-%02d",year,month,1);
        MonthStr =MonthComposite;
        StrSql="select * from Sal_Record where Sal_No='"+KindNo+"' and (Sal_Date between #"+DateStr+"# and #"+MonthStr+"#)";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
        DataModule1->ADOQuery2->Open();
        *MonthCount =0.0;
        *MonthMoney =0.0;
        *MonthAverage=0.0;
        while(!DataModule1->ADOQuery2->Eof)
        {
              DataCount=DataModule1->ADOQuery2->FieldByName("Sal_Num")->Value;
              *MonthCount+=DataCount;
              DataCount=DataModule1->ADOQuery2->FieldByName("Sal_Money")->Value;
              *MonthMoney+=DataCount;
              DataModule1->ADOQuery2->Next();
        }
        if(*MonthCount>0.0)
        {
                *MonthAverage=(*MonthMoney)/(*MonthCount);
        }
        //止年结果 YearCount, double   * YearMoney, double   * YearAverage
        memset(MonthComposite,0x00,sizeof(MonthComposite));
        sprintf(MonthComposite,"%4d-%02d-%02d",year,1,1);
        MonthStr =MonthComposite;
        StrSql="select * from Sal_Record where Sal_No='"+KindNo+"' and (Sal_Date between #"+DateStr+"# and #"+MonthStr+"#)";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
        DataModule1->ADOQuery2->Open();
        *YearCount =0.0;
        *YearMoney =0.0;
        *YearAverage=0.0;
        while(!DataModule1->ADOQuery2->Eof)
        {
              DataCount=DataModule1->ADOQuery2->FieldByName("Sal_Num")->Value;
              *YearCount+=DataCount;
              DataCount=DataModule1->ADOQuery2->FieldByName("Sal_Money")->Value;
              *YearMoney+=DataCount;
              DataModule1->ADOQuery2->Next();
        }
        if(*YearCount>0.0)
        {
                *YearAverage=(*YearMoney)/(*YearCount);
        }

}
void __fastcall TForm2::Button2Click(TObject *Sender)
{
        ListViewToExcel(ListView1,Edit1->Text,Edit2->Text);        
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button6Click(TObject *Sender)
{
        if(Form6!=NULL)
        {
                Form6->ShowModal();
        }
}
//---------------------------------------------------------------------------

