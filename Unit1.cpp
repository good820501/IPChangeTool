//---------------------------------------------------------------------------
#include<windows.h> 
#include <cfgmgr32.h>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit4.h"
#include "stdio.h"
#include "Libs.h"
#include "DataCtrl.h"
#include "WinSock.h"
#include <SetupAPI.h>
 // cfgmgr32.h 在Microsoft Windows 2000 DDK 中.
                                                 // 要用 CM_Get_DevNode_Status(...) 来查询状态.

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TForm *FormTemp=NULL;
ADAPTER_INFO *AdapterInfoVector[8];
int          AdapterNums;
BOOL RegGetIP(ADAPTER_INFO *pAI, LPCTSTR lpszAdapterName, int nIndex =0 );
BOOL SetIP(int EnableDHCP,LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate,LPCTSTR DNS1);
BOOL RegSetIP(int EnableDHCP,LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate,LPCTSTR DNS1);
BOOL NotifyIPChange(LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask);
typedef int (CALLBACK* DHCPNOTIFYPROC)(LPWSTR, LPWSTR, BOOL, DWORD, DWORD, DWORD, int);
typedef TNetCardStruct* PNetCardStruct;
bool __fastcall GetRegistryProperty(HDEVINFO DeviceInfoSet,PSP_DEVINFO_DATA DeviceInfoData, ULONG Property, PVOID Buffer, PULONG Length);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
       AdapterNums=0;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
        if(Node->Text!="销售管理")
                TurnPage(Node->Text);
}
//---------------------------------------------------------------------------

//改变当前页
void __fastcall TForm1::TurnPage(AnsiString NodeName)
{
        
}
void __fastcall TForm1::E1Click(TObject *Sender)
{
       ExitSystem();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ExitSystem()
{
        //TODO: Add your source code here
        if(MessageBox(Handle,"退出煤炭销售管理系统，确定吗？","煤炭销售管理系统",MB_OKCANCEL)==1)
        {
             FreeReAndExit();
        }
}

void __fastcall TForm1::FreeReAndExit()
{
        //TODO: Add your source code here
        if(FormTemp!=NULL)
        {
                FormTemp->Close();
        }
        if(Form2!=NULL)
        {
                delete Form2;
                Form2=NULL;
        }
        Application->Terminate();
}
//连接数据库
void __fastcall TForm1::LinkToDatabase()
{
        AnsiString      FullDBName;
        AnsiString      ExeName;

        ExeName=ExtractFilePath(Application->ExeName);
        ExeName+="DB\\CoalSale.mdb";

        if(!DataModule1->InitDBLinkWithoutCfg(ExeName))
        {
                ShowDBError();
                FreeReAndExit();
        }

}

void __fastcall TForm1::ShowDBError()
{
        //TODO: Add your source code here
        ShowMessage("数据库连接失败，请联系软件供应商解决此问题！");
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        //RightConfirm();
        LinkToDatabase();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::M1Click(TObject *Sender)
{
        ShowCaEditWnd();
}
//---------------------------------------------------------------------------

//显示物品种类编辑窗口
void __fastcall TForm1::ShowCaEditWnd()
{
        //TODO: Add your source code here
        if(Form3!=NULL)
        {
                Form3->ShowModal();
        }
}
void __fastcall TForm1::FormShow(TObject *Sender)
{
        GetAdapterInfo();
        ComboBox1->ItemIndex=0;
        ComboBox1Change(Sender);
        LoadNetSets();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::C1Click(TObject *Sender)
{
        if(Form6!=NULL)
        {
                Form6->ShowModal();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::R1Click(TObject *Sender)
{
        if(Form7!=NULL)
                Form7->ShowModal();        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RightConfirm()
{
        //TODO: Add your source code here
        char            tmp[256];
        char            SecretFile[256];

        AnsiString      Strtemp;
        TDateTime       DTTemp;
        memset(tmp,0x00,sizeof(tmp));
        memset(SecretFile,0x00,sizeof(SecretFile));

        sprintf(SecretFile,"%s","C:\\Program Files\\SysSet.ini");

        GetCfgStr("SysSet","TCtrl","0",tmp,sizeof(tmp));
        Strtemp=tmp;
        if(Strtemp!="1")//未通过注册
        {
                DTTemp =Now();
                if(DTTemp>StrToDate("2008-11-01"))
                {
                        WritePrivateProfileString("SysSet","SecretCfg","1",SecretFile);
                 endTerminate:
                        MessageBox(Handle,"您的软件未经过授权,已超过试用期,请联系软件供应商!","煤炭销售管理系统",MB_OK);
                        Application->Terminate();
                        return;
                }
                memset(tmp,0x00,sizeof(tmp));
                GetPrivateProfileString("SysSet","SecretCfg","0",tmp,sizeof(tmp),SecretFile);
                Strtemp=tmp;
                if(Strtemp==1)
                        goto  endTerminate;

        }
}
//获取适配器信息
BOOL __fastcall TForm1::GetAdapterInfo()
{
        //TODO: Add your source code here
        // 这里的代码适合WINDOWS2000，对于NT需要读取HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\NetworkCards
	HKEY hKey, hSubKey, hNdiIntKey;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				"System\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}",
				0,
				KEY_READ,
				&hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwIndex = 0;
	DWORD dwBufSize = 256;
	DWORD dwDataType;
	char szSubKey[256];
	unsigned char szData[256];

	while(RegEnumKeyEx(hKey, dwIndex++, szSubKey, &dwBufSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
	{
		if(RegOpenKeyEx(hKey, szSubKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
		{		
			if(RegOpenKeyEx(hSubKey, "Ndi\\Interfaces", 0, KEY_READ, &hNdiIntKey) == ERROR_SUCCESS)
			{
				dwBufSize = 256;
				if(RegQueryValueEx(hNdiIntKey, "LowerRange", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
				{
					if(strcmp((char*)szData, "ethernet") == 0)		//	判断是不是以太网卡
					{
						dwBufSize = 256;
						if(RegQueryValueEx(hSubKey, "DriverDesc", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
						{
							ADAPTER_INFO *pAI = new ADAPTER_INFO;
							pAI->strDriverDesc = (LPCTSTR)szData;
							dwBufSize = 256;
							if(RegQueryValueEx(hSubKey, "NetCfgInstanceID", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
							{
								pAI->strName = (LPCTSTR)szData;
								RegGetIP(pAI, (LPCTSTR)szData);
							}
							ComboBox1->Items->Add(pAI->strDriverDesc);	// 加入到容器中
                                                        //AdapterInfoVector
                                                        if(AdapterNums<7)
                                                        AdapterInfoVector[AdapterNums++]=pAI;
						}
					}
				}
				RegCloseKey(hNdiIntKey);
			}
			RegCloseKey(hSubKey);
		}

		dwBufSize = 256;
	}	/* end of while */
		
	RegCloseKey(hKey);
        return TRUE;
}
BOOL RegGetIP(ADAPTER_INFO *pAI, LPCTSTR lpszAdapterName, int nIndex/* =0 */)
{

        //ASSERT(pAI);

	HKEY hKey;
	AnsiString strKeyName = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
	strKeyName += lpszAdapterName;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				strKeyName.c_str(),
				0,
				KEY_READ,
				&hKey) != ERROR_SUCCESS)
		return FALSE;

	unsigned char szData[256];
	DWORD dwDataType, dwBufSize;
        DWORD   Num;   
        DWORD   type=REG_DWORD;
        DWORD   cbB=sizeof(DWORD);

        dwBufSize = 256;
	//if(RegQueryValueEx(hKey, "EnableDHCP", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		//pAI->strIP = (LPCTSTR)szData;
        RegQueryValueEx(hKey,"EnableDHCP",NULL,&type,(LPBYTE)&Num,&cbB);
        if(Num==1)
        {
                pAI->EnableDHCP=true;
	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "DhcpIPAddress", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->strIP = (LPCTSTR)szData;

	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "DhcpSubnetMask", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->strNetMask = (LPCTSTR)szData;

	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "DhcpDefaultGateway", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->strNetGate = (LPCTSTR)szData;
	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "DhcpNameServer", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->DNS1= (LPCTSTR)szData;  
        }
        else    if(Num==0)
        {
                pAI->EnableDHCP=false;
	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "IPAddress", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->strIP = (LPCTSTR)szData;

	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "SubnetMask", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->strNetMask = (LPCTSTR)szData;

	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "DefaultGateway", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->strNetGate = (LPCTSTR)szData;
	        dwBufSize = 256;
	        if(RegQueryValueEx(hKey, "NameServer", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		        pAI->DNS1= (LPCTSTR)szData;
        }
	RegCloseKey(hKey);
	return TRUE;
}


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
        //
        int     nSel= ComboBox1->ItemIndex;
        AnsiString      IP,Mask,NetGate,DNS1,DNS2;
        AnsiString      DNSTotal;

        if(AdapterInfoVector[nSel]->EnableDHCP)
                CheckBox1->Checked=true;
        else
                CheckBox1->Checked=false;
        IP =AdapterInfoVector[nSel]->strIP;
        Mask =AdapterInfoVector[nSel]->strNetMask;
        NetGate=AdapterInfoVector[nSel]->strNetGate;
        Edit1->Text=IP ;
        Edit2->Text=Mask ;
        Edit3->Text=NetGate ;

        DNSTotal=AdapterInfoVector[nSel]->DNS1;
        if(DNSTotal.Pos(",")>0)
        {
             DNS1=DNSTotal.SubString(0,DNSTotal.Pos(",")-1);
             DNS2=DNSTotal.SubString(DNSTotal.Pos(",")+1,strlen(DNSTotal.c_str()));
        }
        else    if(DNSTotal.Pos(" ")>0)
        {
             DNS1=DNSTotal.SubString(0,DNSTotal.Pos(" ")-1);
             DNS2=DNSTotal.SubString(DNSTotal.Pos(" ")+1,strlen(DNSTotal.c_str()));
        }

        Edit4->Text=DNS1;
        Edit5->Text=DNS2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if(Form4!=NULL)
        {
                Form4->Edit1->Text="";
                Form4->Edit2->Text="";
                Form4->Edit3->Text="";
                Form4->Edit4->Text="";
                Form4->Edit5->Text="";
                Form4->ShowModal();
                if(Form4->StoreFlag)
                {                                            
                        StoreNetSet(Form4->CheckBox1->Checked,Form4->Edit6->Text,Form4->Edit1->Text,Form4->Edit2->Text,Form4->Edit3->Text,Form4->Edit4->Text,Form4->Edit5->Text);
                        LoadNetSets();
                }
        }
}
//---------------------------------------------------------------------------

                                                   
void __fastcall TForm1::StoreNetSet(int EnableDHCP,AnsiString CfgName,AnsiString IP, AnsiString SubnetMask, AnsiString Netgate, AnsiString DNS1, AnsiString DNS2)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        char            StrTemp[256];
        if(IP=="")
           IP="0.0.0.0";
        if(SubnetMask=="")
           SubnetMask="0.0.0.0";
        if(Netgate=="")
           Netgate="0.0.0.0";
        if(DNS1=="")
           DNS1="0.0.0.0";
        if(DNS2=="")
           DNS2="0.0.0.0";

        memset(StrTemp,0x00,sizeof(StrTemp));
        sprintf(StrTemp,"insert into Sal_Record(CfgName,IP,SubnetMask,NetGate,DNS1,DNS2,EnableDHCP)Values('%s','%s','%s','%s','%s','%s',%d)",CfgName,IP,SubnetMask,Netgate,DNS1,DNS2,EnableDHCP);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrTemp);
        DataModule1->ADOQuery1->ExecSQL();
}
void __fastcall TForm1::Button5Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

//加载所有的网络配置
void __fastcall TForm1::LoadNetSets()
{
        //TODO: Add your source code here
       AnsiString       StrSql;
       AnsiString       CfgName,IP,  SubnetMask,  Netgate,  DNS1,  DNS2;
       AnsiString       Caption;
       int              ID;
       int              EnableDHCP;
       TListItem        *ItemTemp;
       ListView1->Items->Clear();
       StrSql="select * from Sal_Record";
       DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
       DataModule1->ADOQuery1->Open();
       while(!DataModule1->ADOQuery1->Eof)
       {
                CfgName="";
                if(!DataModule1->ADOQuery1->FieldByName("CfgName")->Value.IsNull())
                CfgName = DataModule1->ADOQuery1->FieldByName("CfgName")->Value;
                CfgName=CfgName.Trim();

                if(!DataModule1->ADOQuery1->FieldByName("IP")->Value.IsNull())
                IP = DataModule1->ADOQuery1->FieldByName("IP")->Value;
                IP=IP.Trim();
                
                if(!DataModule1->ADOQuery1->FieldByName("SubnetMask")->Value.IsNull())
                SubnetMask = DataModule1->ADOQuery1->FieldByName("SubnetMask")->Value;
                SubnetMask=SubnetMask.Trim();
                if(!DataModule1->ADOQuery1->FieldByName("NetGate")->Value.IsNull())
                Netgate = DataModule1->ADOQuery1->FieldByName("NetGate")->Value;
                Netgate=Netgate.Trim();
                if(!DataModule1->ADOQuery1->FieldByName("DNS1")->Value.IsNull())
                DNS1 = DataModule1->ADOQuery1->FieldByName("DNS1")->Value;
                DNS1=DNS1.Trim();
                if(!DataModule1->ADOQuery1->FieldByName("DNS2")->Value.IsNull())
                DNS2= DataModule1->ADOQuery1->FieldByName("DNS2")->Value;
                DNS2=DNS2.Trim();

                if(!DataModule1->ADOQuery1->FieldByName("EnableDHCP")->Value.IsNull())
                EnableDHCP= DataModule1->ADOQuery1->FieldByName("EnableDHCP")->Value;


                ID= DataModule1->ADOQuery1->FieldByName("ID")->Value;
                ItemTemp=ListView1->Items->Add();
                Caption=IntToStr(ID);
                ItemTemp->Caption =Caption;
                ItemTemp->SubItems->Add(CfgName);
                ItemTemp->SubItems->Add(IP);
                
                ItemTemp->SubItems->Add(Netgate);
                ItemTemp->SubItems->Add(SubnetMask);
                ItemTemp->SubItems->Add(DNS1);
                ItemTemp->SubItems->Add(DNS2);
                if(EnableDHCP==1)
                     ItemTemp->SubItems->Add("是");
                else
                     ItemTemp->SubItems->Add("否");
                DataModule1->ADOQuery1->Next();
       }
}
void __fastcall TForm1::Button4Click(TObject *Sender)
{
        //
        TListItem       *ItemSelect;
        AnsiString       IP,  SubnetMask,  Netgate,  DNS1,  DNS2,EnableDHCP;
        int              RecordID;
        int              nSel= ComboBox1->ItemIndex;
        int              DhcpFlag;
        ItemSelect=ListView1->Selected;
        if(ItemSelect!=NULL)
        {
               RecordID=StrToInt(ItemSelect->Caption);
               IP = ItemSelect->SubItems->Strings[1];
               SubnetMask = ItemSelect->SubItems->Strings[2];
               Netgate = ItemSelect->SubItems->Strings[3];
               DNS1 = ItemSelect->SubItems->Strings[4];
               DNS2 = ItemSelect->SubItems->Strings[5];
               EnableDHCP = ItemSelect->SubItems->Strings[6];
               if(EnableDHCP=="是")
                      DhcpFlag =1;
               else
                      DhcpFlag =0;

               if((DNS1!="")&&(DNS2!=""))
               {
                   DNS1 = DNS1+","+DNS2;
               }
               else     if((DNS1=="")&&(DNS2!=""))
               {
                   DNS1 =  DNS2;
               }
               else     if((DNS1!="")&&(DNS2==""))
               {
                   DNS1 =  DNS1;
               }
               //StopNetCard(ComboBox1->Text);
               if(SetIP(DhcpFlag,AdapterInfoVector[nSel]->strName.c_str(), 0, IP.c_str(), SubnetMask.c_str(), Netgate.c_str(),DNS1.c_str()) == TRUE)
		        ;
               else
                        ;
               if(RestartNetCard(ComboBox1->Text))
                        ShowMessage("设置成功");
               else
                        ShowMessage("设置失败");
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView1Change(TObject *Sender, TListItem *Item,
      TItemChange Change)
{
        TListItem       *ItemSelect;
        ItemSelect=ListView1->Selected;
        if(ItemSelect!=NULL)
        {
                Button2->Enabled=true;
                Button3->Enabled=true;
                Button4->Enabled=true;
        }
        else
        {
                Button2->Enabled=false;
                Button3->Enabled=false;
                Button4->Enabled=false;
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        TListItem       *ItemSelect;
        AnsiString       CfgName,IP,  SubnetMask,  Netgate,  DNS1,  DNS2,EnableDHCP;
        int              RecordID;
        ItemSelect=ListView1->Selected;
        if(ItemSelect!=NULL)
        {
               
               RecordID=StrToInt(ItemSelect->Caption);
               CfgName= ItemSelect->SubItems->Strings[0];
               IP = ItemSelect->SubItems->Strings[1];
               SubnetMask = ItemSelect->SubItems->Strings[2];
               Netgate = ItemSelect->SubItems->Strings[3];
               DNS1 = ItemSelect->SubItems->Strings[4];
               DNS2 = ItemSelect->SubItems->Strings[5];
               EnableDHCP = ItemSelect->SubItems->Strings[6];
               if(Form4!=NULL)
               {
                  if(EnableDHCP=="是")
                        Form4->CheckBox1->Checked=true;
                  else
                  {
                        Form4->CheckBox1->Checked=false;
                        Form4->Edit6->Text=CfgName;
                        Form4->Edit1->Text=IP;
                        Form4->Edit2->Text=Netgate;
                        Form4->Edit3->Text=SubnetMask;
                        Form4->Edit4->Text=DNS1;
                        Form4->Edit5->Text=DNS2;
                  }
                  Form4->ShowModal();
                  if(Form4->StoreFlag)
                  {                                           
                        ChangeNetSet(Form4->CheckBox1->Checked,Form4->Edit6->Text,Form4->Edit1->Text,Form4->Edit2->Text,Form4->Edit3->Text,Form4->Edit4->Text,Form4->Edit5->Text,RecordID);
                        LoadNetSets();
                  }
               }
        }
}
//---------------------------------------------------------------------------

//修改网络配置
void __fastcall TForm1::ChangeNetSet(int EnableDHCP, AnsiString CfgName,AnsiString IP, AnsiString SubnetMask, AnsiString Netgate, AnsiString DNS1, AnsiString DNS2,int RecordID)
{
        //TODO: Add your source code here
        char    StrSql[256];

        memset(StrSql,0x00,sizeof(StrSql));
        if(EnableDHCP==1)
        {
                sprintf(StrSql,"update Sal_Record set CfgName='%s',IP='0.0.0.0',SubnetMask='0.0.0.0',NetGate='0.0.0.0',DNS1='0.0.0.0',DNS2='0.0.0.0',EnableDHCP=1 where ID=%d",CfgName,RecordID);
        }
        else
        {
                sprintf(StrSql,"update Sal_Record set CfgName='%s',IP='%s',SubnetMask='%s',NetGate='%s',DNS1='%s',DNS2='%s',EnableDHCP=0 where ID=%d",CfgName,IP,SubnetMask,Netgate,DNS1,DNS2,RecordID);
        }
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->ExecSQL();
}
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        TListItem       *ItemSelect;
        AnsiString       IP,  SubnetMask,  Netgate,  DNS1,  DNS2,EnableDHCP;
        int              RecordID;
        ItemSelect=ListView1->Selected;
        if(ItemSelect!=NULL)
        {
                RecordID=StrToInt(ItemSelect->Caption);
                if(MessageBox(Handle,"删除选定的网络设置，确定吗？","删除确认",MB_OKCANCEL)==1)
                {
                        DetNetConfig(RecordID);
                        LoadNetSets();
                }
        }
}
//---------------------------------------------------------------------------

//删除指定IP配置
void __fastcall TForm1::DetNetConfig(int SelID)
{
        //TODO: Add your source code here
        char    StrSql[256];
        memset(StrSql,0x00,sizeof(StrSql));
        sprintf(StrSql,"delete from Sal_Record where ID=%d",SelID);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->ExecSQL();
}

//-----------------------------------------------------------------
//	设置IP地址
//	如果只绑定一个IP，nIndex = 0，暂时未处理一个网卡绑定多个地址
//-----------------------------------------------------------------

BOOL SetIP(int EnableDHCP,LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate,LPCTSTR DNS1)
{
	if(!RegSetIP(EnableDHCP,lpszAdapterName, nIndex, pIPAddress, pNetMask, pNetGate,DNS1))
		return FALSE;
	if(!NotifyIPChange(lpszAdapterName, nIndex, pIPAddress, pNetMask))
		return FALSE;
	return TRUE;
}

//-----------------------------------------------------------------
//	设置注册表中的IP信息
//-----------------------------------------------------------------

BOOL RegSetIP(int EnableDHCP,LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate,LPCTSTR DNS1)
{
	HKEY    hKey;
        char    mszIPAddress[100];
	char    mszNetMask[100];
	char    mszNetGate[100];
        char    DNS[100];


	AnsiString strKeyName = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
	strKeyName += lpszAdapterName;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,strKeyName.c_str(),0,KEY_WRITE,&hKey) != ERROR_SUCCESS)
		return FALSE;

	
        if(EnableDHCP==1)
        {
               strncpy(mszIPAddress,"", 98);
	       strncpy(mszNetMask, "", 98);
	       strncpy(mszNetGate, "", 98);
               strncpy(DNS, "", 98);
        }
        else
        {
              	strncpy(mszIPAddress, pIPAddress, 98);
	        strncpy(mszNetMask, pNetMask, 98);
	        strncpy(mszNetGate, pNetGate, 98);
                strncpy(DNS, DNS1, 98);
        }
	int nIP, nMask, nGate,nDns;

	nIP = strlen(mszIPAddress);
	nMask = strlen(mszNetMask);
	nGate = strlen(mszNetGate);
        nDns = strlen(DNS);

	*(mszIPAddress + nIP + 1) = 0x00;
	nIP += 2;

	*(mszNetMask + nMask + 1) = 0x00;
	nMask += 2;

	*(mszNetGate + nGate + 1) = 0x00;
	nGate += 2;

        *(DNS + nDns + 1) = 0x00;
	nDns += 2;

        char   cvalue[2]   =   {""};
        BYTE isd[6];
         for(int uu=0; uu<6; uu++)
        {
                isd[uu] = 0;
        }
	if(EnableDHCP==1)
        {
                DWORD isd=1;
                RegSetValueEx(hKey,"EnableDHCP",0,REG_DWORD,(unsigned char*)&isd,   sizeof(DWORD));

                RegDeleteValue(hKey, "DefaultGateway");
                RegDeleteValue(hKey, "NameServer");
                /*
                memset(mszIPAddress,0x00,sizeof(mszIPAddress));
                RegSetValueEx(hKey, "IPAddress", 0, REG_MULTI_SZ, (unsigned char*)mszIPAddress, nIP);

                memset(mszNetMask,0x00,sizeof(mszNetMask));
	        RegSetValueEx(hKey, "SubnetMask", 0, REG_MULTI_SZ, (unsigned char*)mszNetMask, nMask);

                memset(mszNetGate,0x00,sizeof(mszNetGate));
	        RegSetValueEx(hKey, "DefaultGateway", 0, REG_MULTI_SZ, (unsigned char*)mszNetGate, nGate);

                memset(DNS,0x00,sizeof(DNS));
                RegSetValueEx(hKey, "NameServer", 0, REG_SZ, (unsigned char*)DNS, nDns); */
        }
        else
        {
                itoa(0,   cvalue,   10);
                RegSetValueEx(hKey,"EnableDHCP",0,REG_DWORD,(PBYTE)isd,   sizeof(DWORD));
	        RegSetValueEx(hKey, "IPAddress", 0, REG_MULTI_SZ, (unsigned char*)mszIPAddress, nIP);
	        RegSetValueEx(hKey, "SubnetMask", 0, REG_MULTI_SZ, (unsigned char*)mszNetMask, nMask);
	        RegSetValueEx(hKey, "DefaultGateway", 0, REG_MULTI_SZ, (unsigned char*)mszNetGate, nGate);
                RegSetValueEx(hKey, "NameServer", 0, REG_SZ, (unsigned char*)DNS, nDns);
        }
	RegCloseKey(hKey);
	return TRUE;
}
BOOL NotifyIPChange(LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask)
{
	BOOL			bResult = FALSE;
	HINSTANCE		hDhcpDll;
	DHCPNOTIFYPROC	pDhcpNotifyProc;
	WCHAR wcAdapterName[256];
	
	MultiByteToWideChar(CP_ACP, 0, lpszAdapterName, -1, wcAdapterName,256);

	if((hDhcpDll = LoadLibrary("dhcpcsvc")) == NULL)
		return FALSE;

	if((pDhcpNotifyProc = (DHCPNOTIFYPROC)GetProcAddress(hDhcpDll, "DhcpNotifyConfigChange")) != NULL)
		if((pDhcpNotifyProc)(NULL, wcAdapterName, TRUE, nIndex, inet_addr(pIPAddress), inet_addr(pNetMask), 0) == ERROR_SUCCESS)
			bResult = TRUE;

	FreeLibrary(hDhcpDll);
	return bResult;
}
bool __fastcall NetCardStateChange(void * NetCardPoint, bool Enabled)
{ 
       PNetCardStruct NetCard = (PNetCardStruct)NetCardPoint; 
       DWORD DeviceId = NetCard->Id;
       HDEVINFO hDevInfo = 0;
           if (INVALID_HANDLE_VALUE == (hDevInfo = 
                               SetupDiGetClassDevs(NULL,NULL,0,DIGCF_PRESENT |DIGCF_ALLCLASSES))) 
               return false; 
           SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)}; 
       DWORD Status, Problem; 
       if (!SetupDiEnumDeviceInfo(hDevInfo,DeviceId,&DeviceInfoData)) 
               return false; 

       if (CM_Get_DevNode_Status(&Status, &Problem,
                               DeviceInfoData.DevInst,0) != CR_SUCCESS) 
               return false;

       SP_PROPCHANGE_PARAMS PropChangeParams = {sizeof(SP_CLASSINSTALL_HEADER)}; 
       PropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE; 
       PropChangeParams.Scope = DICS_FLAG_GLOBAL; 
       if (Enabled) 
       { 
               if (!((Status & DN_HAS_PROBLEM) && (CM_PROB_DISABLED == Problem))) 
               { 
                       NetCard->Disabled = false; 
                       return false; 
               } 
               PropChangeParams.StateChange = DICS_ENABLE; 
       } 
       else 
       { 
               if ((Status & DN_HAS_PROBLEM) && (CM_PROB_DISABLED == Problem)) 
               { 
                       NetCard->Disabled = true; 
                       return false; 
               } 
               if (!((Status & DN_DISABLEABLE) && (CM_PROB_HARDWARE_DISABLED != Problem))) 
                       return false; 
               PropChangeParams.StateChange = DICS_DISABLE; 
       } 

       if (!SetupDiSetClassInstallParams(hDevInfo, &DeviceInfoData, 
               (SP_CLASSINSTALL_HEADER *)&PropChangeParams, sizeof(PropChangeParams))) 
               return false; 
       if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &DeviceInfoData)) 
               return false; 
       if (CM_Get_DevNode_Status(&Status, &Problem, 
                               DeviceInfoData.DevInst,0) == CR_SUCCESS) 
               NetCard->Disabled = (Status & DN_HAS_PROBLEM) && (CM_PROB_DISABLED == Problem); 
       return true; 
} 
 //---------------------------------------------------------------------------       
  //             EnumNetCards     枚举出网卡       
  //---------------------------------------------------------------------------
void     __fastcall     EnumNetCards(TList     *NetDeviceList)
{
       AnsiString DevValue;
       PNetCardStruct NetCard; 
       DWORD Status, Problem; 
       LPTSTR Buffer = NULL; 
       DWORD BufSize = 0; 
       HDEVINFO hDevInfo = 0; 
           if (INVALID_HANDLE_VALUE == (hDevInfo = 
                               SetupDiGetClassDevs(NULL,NULL,0,DIGCF_PRESENT |DIGCF_ALLCLASSES))) 
               return; 
       SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)}; 
           HKEY hKeyClass; 
           char DeviceName[200]; 
           for (DWORD DeviceId=0; 
                       SetupDiEnumDeviceInfo(hDevInfo,DeviceId,&DeviceInfoData); DeviceId++)
       { 
               if (CM_Get_DevNode_Status(&Status, &Problem, 
                                       DeviceInfoData.DevInst,0) != CR_SUCCESS) 
                     continue; 

               DevValue.SetLength(0); 
               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_CLASS , &Buffer, (PULONG)&BufSize))
                       DevValue = Buffer; 
               if (DevValue == "Net") 
               {
                       DevValue.SetLength(0); 
                       if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_ENUMERATOR_NAME , &Buffer, (PULONG)&BufSize)) 
                               DevValue = Buffer; 
                       if (DevValue != "ROOT") 
                       { 
                               NetCard = new TNetCardStruct; 
                               NetCard->Id = DeviceId; 
                               NetCard->Name = "<Unknown Device>";
                               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER , &Buffer, (PULONG)&BufSize))
                               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC , &Buffer, (PULONG)&BufSize)) 
                                       NetCard->Name = Buffer;
                               NetCard->Disabled = (Status & DN_HAS_PROBLEM) && (CM_PROB_DISABLED == Problem);
                               NetCard->Changed = false;
                               NetDeviceList->Add(NetCard); 
                       } 
               } 
       }

  }       
  //---------------------------------------------------------------------------
  //--------------------------------------------------------------------------- 
bool __fastcall GetRegistryProperty(HDEVINFO DeviceInfoSet,
                         PSP_DEVINFO_DATA DeviceInfoData, ULONG Property, PVOID Buffer, PULONG Length)
{ 
           while (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, 
               DeviceInfoData, Property, NULL, (BYTE *)*(TCHAR **)Buffer, *Length, Length)) 
       { 
               if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) 
               { 
                       if (*(LPTSTR *)Buffer) LocalFree(*(LPTSTR *)Buffer); 
                       *(LPTSTR *)Buffer = (PCHAR)LocalAlloc(LPTR,*Length); 
               } 
               else return false; 
       } 
       return (*(LPTSTR *)Buffer)[0]; 
} 

void __fastcall TForm1::Button6Click(TObject *Sender)
{
        TList *NetDeviceList=new  TList;
        EnumNetCards(NetDeviceList);
}

//---------------------------------------------------------------------------
//重启NetName指定的网卡
bool __fastcall TForm1::RestartNetCard(AnsiString NetName)
{
        //TODO: Add your source code here
       AnsiString DevValue;
       PNetCardStruct NetCard;
       DWORD Status, Problem;
       LPTSTR Buffer = NULL;
       DWORD BufSize = 0;
       HDEVINFO hDevInfo = 0;
           if (INVALID_HANDLE_VALUE == (hDevInfo =SetupDiGetClassDevs(NULL,NULL,0,DIGCF_PRESENT |DIGCF_ALLCLASSES)))
               return false;
       SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)};
       HKEY hKeyClass;
       char DeviceName[200];
       for (DWORD DeviceId=0; SetupDiEnumDeviceInfo(hDevInfo,DeviceId,&DeviceInfoData); DeviceId++)
       {
               if (CM_Get_DevNode_Status(&Status, &Problem,
                        DeviceInfoData.DevInst,0) != CR_SUCCESS)
                     continue;

               DevValue.SetLength(0);
               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_CLASS , &Buffer, (PULONG)&BufSize))
                       DevValue = Buffer;
               if (DevValue == "Net")
               {
                       DevValue.SetLength(0);
                       if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_ENUMERATOR_NAME , &Buffer, (PULONG)&BufSize))
                               DevValue = Buffer;
                       if (DevValue != "ROOT")
                       {
                               NetCard = new TNetCardStruct;
                               NetCard->Id = DeviceId;
                               NetCard->Name = "<Unknown Device>";
                               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER , &Buffer, (PULONG)&BufSize))
                               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC , &Buffer, (PULONG)&BufSize))
                                       NetCard->Name = Buffer;
                               if(NetCard->Name==NetName)
                               {
                                        NetCardStateChange(NetCard,false);
                                        NetCardStateChange(NetCard,true);
                                        return  true;
                               }
                       }
               }
       }
       return  false;
}

BOOL __fastcall TForm1::StopNetCard(AnsiString NetName)
{
        //TODO: Add your source code here
        AnsiString DevValue;
       PNetCardStruct NetCard;
       DWORD Status, Problem;
       LPTSTR Buffer = NULL;
       DWORD BufSize = 0;
       HDEVINFO hDevInfo = 0;
           if (INVALID_HANDLE_VALUE == (hDevInfo =SetupDiGetClassDevs(NULL,NULL,0,DIGCF_PRESENT |DIGCF_ALLCLASSES)))
               return false;
       SP_DEVINFO_DATA DeviceInfoData = {sizeof(SP_DEVINFO_DATA)};
       HKEY hKeyClass;
       char DeviceName[200];
       for (DWORD DeviceId=0; SetupDiEnumDeviceInfo(hDevInfo,DeviceId,&DeviceInfoData); DeviceId++)
       {
               if (CM_Get_DevNode_Status(&Status, &Problem,
                        DeviceInfoData.DevInst,0) != CR_SUCCESS)
                     continue;

               DevValue.SetLength(0);
               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_CLASS , &Buffer, (PULONG)&BufSize))
                       DevValue = Buffer;
               if (DevValue == "Net")
               {
                       DevValue.SetLength(0);
                       if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_ENUMERATOR_NAME , &Buffer, (PULONG)&BufSize))
                               DevValue = Buffer;
                       if (DevValue != "ROOT")
                       {
                               NetCard = new TNetCardStruct;
                               NetCard->Id = DeviceId;
                               NetCard->Name = "<Unknown Device>";
                               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER , &Buffer, (PULONG)&BufSize))
                               if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC , &Buffer, (PULONG)&BufSize))
                                       NetCard->Name = Buffer;
                               if(NetCard->Name==NetName)
                               {
                                        NetCardStateChange(NetCard,false);
                                        //NetCardStateChange(NetCard,true);
                                        return  true;
                               }
                       }
               }
       }
       return  false;
}
void __fastcall TForm1::ListView1DblClick(TObject *Sender)
{
        Button4Click(Sender);
}
//---------------------------------------------------------------------------

