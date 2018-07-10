//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        BOOL    StoreFlag;     //是否保存的标志1：保存；0：不保存；
        __fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
