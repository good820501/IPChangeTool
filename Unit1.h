//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TGroupBox *GroupBox1;
        TComboBox *ComboBox1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label2;
        TEdit *Edit3;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit4;
        TLabel *Label5;
        TEdit *Edit5;
        TGroupBox *GroupBox3;
        TListView *ListView1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TCheckBox *CheckBox1;
        void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
        void __fastcall E1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall M1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall C1Click(TObject *Sender);
        void __fastcall R1Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall ListView1Change(TObject *Sender, TListItem *Item,
          TItemChange Change);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall ListView1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall TurnPage(AnsiString NodeName);
        void __fastcall ExitSystem();
        void __fastcall FreeReAndExit();
        void __fastcall LinkToDatabase();
        void __fastcall ShowDBError();
        void __fastcall ShowCaEditWnd();
        void __fastcall RightConfirm();
        BOOL __fastcall GetAdapterInfo();
        void __fastcall StoreNetSet(int EnableDHCP,AnsiString CfgName,AnsiString IP, AnsiString SubnetMask, AnsiString Netgate, AnsiString DNS1, AnsiString DNS2);
        void __fastcall LoadNetSets();
        void __fastcall ChangeNetSet(int EnableDHCP, AnsiString CfgName, AnsiString IP, AnsiString SubnetMask, AnsiString Netgate, AnsiString DNS1, AnsiString DNS2,int RecordID);
        void __fastcall DetNetConfig(int SelID);
        bool __fastcall RestartNetCard(AnsiString NetName);
        BOOL __fastcall StopNetCard(AnsiString NetName);
};
typedef struct tagAdapterInfo
{
	AnsiString strName;			// 适配器名称
	AnsiString strDriverDesc;	// 适配器描述
	AnsiString strIP;			// IP地址
	AnsiString strNetMask;		// 子网掩码
	AnsiString strNetGate;		// 网关
        AnsiString DNS1;                //DNS1
        AnsiString DNS2;                //DNS2
        BOOL       EnableDHCP;          //是否开启DHCP
}ADAPTER_INFO;

typedef struct NetCardStruct 
{ 
       DWORD Id; // 网卡设备号 
       AnsiString Name; // 网卡名 
       bool Disabled; // 当前是否禁用 
       bool Changed; // 是否更改过 
} TNetCardStruct; 


//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
