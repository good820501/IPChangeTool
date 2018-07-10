//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit5.h"
#include "DataCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button4Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

//������Ʒ�����б�
void __fastcall TForm3::LoadTradeList()
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      StrTemp;


        StrSql ="select * from CoalKinds";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        ListBox1->Items->Clear();
        while(!DataModule1->ADOQuery1->Eof)
        {
                if(!DataModule1->ADOQuery1->FieldByName("Sale_Name")->Value.IsNull())
                {
                        StrTemp=DataModule1->ADOQuery1->FieldByName("Sale_Name")->Value;
                        StrTemp=StrTemp.Trim();
                }
                ListBox1->Items->Add(StrTemp);
                DataModule1->ADOQuery1->Next();
        }
}
void __fastcall TForm3::FormShow(TObject *Sender)
{
        LoadTradeList();        
}
//---------------------------------------------------------------------------
void __fastcall TForm3::ListBox1Click(TObject *Sender)
{
        AnsiString      StrSelText;
        int             SelIndex;
        SelIndex =ListBox1->ItemIndex;
        StrSelText=ListBox1->Items->Strings[SelIndex];
        StrSelText=StrSelText.Trim();
        if(StrSelText!="")
        {
                Button3->Enabled=true;
                Button2->Enabled=true;
        }
        else
        {
                 Button3->Enabled=false;
                 Button2->Enabled=false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
        if(Form5!=NULL)
        {
                Form5->Edit1->Text="";
                Form5->ShowModal();
                if(Form5->StoreFlag)
                {
                        AddKindName(Form5->Edit1->Text);
                        LoadTradeList();
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm3::AddKindName(AnsiString KindName)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        if(GudgeTradeName(KindName))
        {
                StrSql="insert into CoalKinds(Sale_Name)Values('";
                StrSql+=KindName;
                StrSql+="')";
                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                DataModule1->ADOQuery1->ExecSQL();
        }
        else
        {
                ShowMessage("��Ʒ���ʧ�ܣ����ݿ���������ͬ���Ƶ���Ʒ��");
        }
}
//�ж����ݿ����Ƿ��Ѿ���ͬ���ļ�¼ ,�еĻ�����false�����򷵻�true��
bool __fastcall TForm3::GudgeTradeName(AnsiString TradeName)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="select * from CoalKinds where Sale_Name='"+TradeName+"'";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        if(DataModule1->ADOQuery1->RecordCount>0)
        {
             DataModule1->ADOQuery1->Close();
             return     false;
        }
        return  true;
}
void __fastcall TForm3::Button2Click(TObject *Sender)
{
        AnsiString      StrSelText;
        int             SelIndex;
        SelIndex =ListBox1->ItemIndex;
        StrSelText=ListBox1->Items->Strings[SelIndex];
        StrSelText=StrSelText.Trim();
        if(StrSelText!="")
        {
                if(Form5!=NULL)
                {
                    Form5->Edit1->Text=StrSelText;
                    Form5->ShowModal();
                    if(Form5->StoreFlag)
                    {
                        if(StrSelText!=Form5->Edit1->Text)
                        {
                                ModifyKindName(StrSelText,Form5->Edit1->Text);
                                LoadTradeList();
                        }
                    }
                }
        }
}
//---------------------------------------------------------------------------

//�޸���Ʒ����
void __fastcall TForm3::ModifyKindName(AnsiString OldName, AnsiString NewName)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="update CoalKinds set Sale_Name='"+NewName+"' where Sale_Name='"+OldName+"'";
        if(GudgeTradeName(NewName))
        {
                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                DataModule1->ADOQuery1->ExecSQL();
        }
        else
        {
                ShowMessage("��Ʒ�޸�ʧ�ܣ����ݿ���������ͬ���Ƶ���Ʒ��");
        }
}
void __fastcall TForm3::ListBox1DblClick(TObject *Sender)
{
        Button2Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button3Click(TObject *Sender)
{
        AnsiString      StrSelText;
        AnsiString      ErrorMsg;
        int             SelIndex;
        SelIndex =ListBox1->ItemIndex;
        StrSelText=ListBox1->Items->Strings[SelIndex];
        StrSelText=StrSelText.Trim();
        if(StrSelText!="")
        {
                 ErrorMsg="��Ҫɾ������Ϊ'"+StrSelText+"'����Ʒ��ȷ����";
                 if(MessageBox(Handle,ErrorMsg.c_str(),"��Ʒɾ��ȷ��",MB_OKCANCEL)==1)
                 {
                        DelKindName(StrSelText);
                        LoadTradeList();
                 }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm3::DelKindName(AnsiString KindName)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="delete  from CoalKinds where Sale_Name='"+KindName+"'";
        if(!GudgeTradeName(KindName))
        {
                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                DataModule1->ADOQuery1->ExecSQL();
        }
}