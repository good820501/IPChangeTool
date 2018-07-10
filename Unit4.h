//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label2;
        TEdit *Edit2;
        TLabel *Label3;
        TEdit *Edit3;
        TEdit *Edit5;
        TLabel *Label5;
        TEdit *Edit4;
        TLabel *Label4;
        TCheckBox *CheckBox1;
        TLabel *Label6;
        TEdit *Edit6;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
        int     EndRows;
public:		// User declarations
        BOOL    StoreFlag;      //是否保存；1：保存；0：不保存；
        __fastcall TForm4(TComponent* Owner);
        void __fastcall InitInputWnd();
        void __fastcall InitTableHead();
        void __fastcall InitColHead();
        BOOL __fastcall CheckDataError();
        void __fastcall UpdateSaleRecord(AnsiString KindName, AnsiString SaleCount, AnsiString SaleMoney);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
