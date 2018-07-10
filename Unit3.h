//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TListBox *ListBox1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall ListBox1DblClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
        void __fastcall LoadTradeList();
        void __fastcall AddKindName(AnsiString KindName);
        bool __fastcall GudgeTradeName(AnsiString TradeName);
        void __fastcall ModifyKindName(AnsiString OldName, AnsiString NewName);
        void __fastcall DelKindName(AnsiString KindName);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
