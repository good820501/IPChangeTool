//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TGroupBox *GroupBox1;
        TLabel *Label2;
        TEdit *Edit1;
        TLabel *Label3;
        TEdit *Edit2;
        TLabel *Label4;
        TButton *Button1;
        TGroupBox *GroupBox2;
        TListView *ListView1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TDateTimePicker *DateTimePicker1;
        TButton *Button6;
        TButton *Button5;
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
        void __fastcall ExitSystem();
        void __fastcall MakeReport();
        void __fastcall GetDetailData(AnsiString KindNo,double   * NowCount, double   * NowMoney, double   * MonthCount, double   * MonthMoney, double   * MonthAverage, double   * YearCount, double   * YearMoney, double   * YearAverage);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
