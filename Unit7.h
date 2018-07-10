//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm7 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label2;
        TEdit *Edit2;
        TButton *Button4;
        TButton *Button5;
        TOpenDialog *OpenDialog1;
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm7(TComponent* Owner);
        AnsiString __fastcall GetBakFileName();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
