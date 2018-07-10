/*****************************************************************   
  **   ������:DBGridToExcel   
  **   ��   ��:TDBGrid   *,AnsiString   *   
  **   TDBGrid   *:������Դ��
*****************************************************************/   

  //---------------------------------------------------------------------------
  #include      "ComObj.hpp"
  #include      "DataExport.h"
  #define       PG       OlePropertyGet   
  #define       PS       OlePropertySet   
  #define       FN       OleFunction   
  #define       PR       OleProcedure   
  //----------------------------
  //void  DBGridToExcel(TDBGrid   *DBGrid,AnsiString   strPath)
void  DBGridToExcel(TDBGrid *dbg)
{
        String strXlsFile;

        if(!dbg->DataSource->DataSet->Active) // ���ݼ�û�д򿪾ͷ���
                return;
        if(!GetDestFilePath(strXlsFile))
                return;
        Variant vExcelApp, vSheet;
        try
        {
                vExcelApp = Variant::CreateObject("Excel.Application");
        }
        catch(...)
        {
                MessageBox(0, "���� Excel ����, ������û�а�װExcel.","DBGrid2Excel", MB_OK | MB_ICONERROR);
                return;
        }
        // ����Excel����
        vExcelApp.OlePropertySet("Visible", true);
        // �½�һ��������
        vExcelApp.OlePropertyGet("Workbooks").OleFunction("Add", 1); // ������
        // �������������
        vSheet = vExcelApp.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);
        // ����Excel�ĵ�������
        vSheet.OleProcedure("Select"); 
        vSheet.OlePropertyGet("Cells").OleProcedure("Select");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Size", dbg->Font->Size);
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Name",dbg->Font->Name.c_str());
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("FontStyle", "����");
        vSheet.OlePropertyGet("Cells", 1, 1).OleProcedure("Select");
        // ��������
        int nRowCount(dbg->DataSource->DataSet->RecordCount + 1);
        nRowCount = nRowCount < 2? 2: nRowCount;
        // ��������
        int nColCount(dbg->Columns->Count);
        nColCount = nColCount < 1? 1: nColCount;
        // ���õ�Ԫ��Ŀ��
        for(int i=0; i<nColCount; i++)
        {
                int nColWidth = dbg->Columns->Items[i]->Width;
                vExcelApp.OlePropertyGet("Columns", i + 1).OlePropertySet("ColumnWidth", nColWidth / 7);
        }
        // �Ƚ�����д��Excel���
        for(int j=0; j<dbg->Columns->Count; j++)
        {
        // �����е��и�
                vExcelApp.OlePropertyGet("Rows", 1).OlePropertySet("RowHeight", 20);
                vSheet.OlePropertyGet("Cells", 1, j + 1).OlePropertySet("Value", dbg->Columns->Items[j]->Title->Caption.c_str());
        // ����������Ԫ��ı���ɫ
                Variant vInter = vSheet.OlePropertyGet( "Cells", 1, j + 1).OlePropertyGet("Interior");
                vInter.OlePropertySet("ColorIndex", 15); // ��ɫ
                vInter.OlePropertySet("Pattern", 1); // xlSolid
                vInter.OlePropertySet("PatternColorIndex", -4105); // xlAutomatic
         }
        // ��DBGrid�е�����д��Excel���
        dbg->DataSource->DataSet->First();
        for(int i=0; i<nRowCount-1; i++)
        {
        // ��ͨ�����е��и�16
                vExcelApp.OlePropertyGet("Rows", i + 2).OlePropertySet("RowHeight", 16);
                // 63 63 72 75 6E 2E 63 6F 6D
                for(int j=0; j<dbg->Columns->Count; j++)
                {
                        vSheet.OlePropertyGet("Cells", i + 2, j + 1).OlePropertySet("Value",dbg->DataSource->DataSet->FieldByName(dbg->Columns->Items[j]->FieldName)->AsString.c_str());
                }
                dbg->DataSource->DataSet->Next();
        }
        // ����Excel�ĵ����˳�
        vExcelApp.OlePropertyGet("ActiveWorkbook").OleFunction("SaveAs", strXlsFile.c_str());
        vExcelApp.OleFunction("Quit");
        vSheet = Unassigned;
        vExcelApp = Unassigned;
        // ��������
        MessageBox(0, "���ݵ������!","DBGrid2Excel", MB_OK | MB_ICONINFORMATION);
}
void     ListViewToExcel(TListView *dbg,AnsiString UnitName,AnsiString WorkerName)

{
        String strXlsFile;
        AnsiString      DateStr;
        TDateTime       DTTemp=Now();
        DateStr=DTTemp.DateString();
        if(!dbg->Items->Count>0)
                return;
        if(!GetDestFilePath(strXlsFile))
                return;
        Variant vExcelApp, vSheet;
        try
        {
                vExcelApp = Variant::CreateObject("Excel.Application");
        }
        catch(...)
        {
                MessageBox(0, "���� Excel ����, ������û�а�װExcel.","DBGrid2Excel", MB_OK | MB_ICONERROR);
                return;
        }
        // ����Excel����
        vExcelApp.OlePropertySet("Visible", true);
        // �½�һ��������
        vExcelApp.OlePropertyGet("Workbooks").OleFunction("Add", 1); // ������
        // �������������
        vSheet = vExcelApp.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);
        // ����Excel�ĵ�������
        vSheet.OleProcedure("Select");
        vSheet.OlePropertyGet("Cells").OleProcedure("Select");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Size", 18);
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Name","����");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("FontStyle", "����");
        vSheet.OlePropertyGet("Cells", 1, 1).OleProcedure("Select");
        // ��������
        int nRowCount(dbg->Items->Count+1);
        nRowCount = nRowCount < 2? 2: nRowCount;
        // ��������
        int nColCount(dbg->Columns->Count);
        nColCount = nColCount < 1? 1: nColCount;
        // ���õ�Ԫ��Ŀ��
        for(int i=0; i<nColCount; i++)
        {
                int nColWidth = dbg->Columns->Items[i]->Width;

                if(i<1)
                        vExcelApp.OlePropertyGet("Columns", i + 1).OlePropertySet("ColumnWidth", (nColWidth / 7)-3);
                else    if(i==1)
                        vExcelApp.OlePropertyGet("Columns", i + 1).OlePropertySet("ColumnWidth", nColWidth / 7);
                else
                        vExcelApp.OlePropertyGet("Columns", i + 1).OlePropertySet("ColumnWidth", nColWidth / 7-1);
        }
        // �Ƚ�����д��Excel���

        vExcelApp.OlePropertyGet("Rows", 1).OlePropertySet("RowHeight", 40);
        vSheet.OlePropertyGet("Range","A1:K1").OleFunction("Merge",false);
        vSheet.PG("Cells", 1, 1).PG("Font").PS("Name", "����"); //����
        vSheet.PG("Cells", 1, 1).PG("Font").PS("size", 28);     //��С
        vSheet.OlePropertyGet("Cells", 1, 1).OlePropertySet("Value", "                ����ͳ�Ʊ�");

        // ����Excel�ĵ�������
        /*
        vSheet.OleProcedure("Select");
        vSheet.OlePropertyGet("Cells").OleProcedure("Select");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Size", dbg->Font->Size);
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Name",dbg->Font->Name.c_str());
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("FontStyle", "����");
        vSheet.OlePropertyGet("Cells", 1, 1).OleProcedure("Select");
        */
        vExcelApp.OlePropertyGet("Rows", 2).OlePropertySet("RowHeight", 20);
        vSheet.PG("Cells", 2, 2).PG("Font").PS("Name", "����"); //����
        vSheet.PG("Cells", 2, 2).PG("Font").PS("size", 12);     //��С
        vSheet.OlePropertyGet("Cells", 2, 2).OlePropertySet("Value", "���λ��");

        vSheet.PG("Cells", 2, 3).PG("Font").PS("Name", "����"); //����
        vSheet.PG("Cells", 2, 3).PG("Font").PS("size", 12);     //��С
        vSheet.OlePropertyGet("Cells", 2, 3).OlePropertySet("Value", UnitName.c_str());

        vSheet.PG("Cells", 2, 6).PG("Font").PS("Name", "����"); //����
        vSheet.PG("Cells", 2, 6).PG("Font").PS("size", 12);     //��С
        vSheet.OlePropertyGet("Cells", 2, 6).OlePropertySet("Value", "��ˣ�");


        vSheet.PG("Cells", 2, 7).PG("Font").PS("Name", "����"); //����
        vSheet.PG("Cells", 2, 7).PG("Font").PS("size", 12);     //��С
        vSheet.OlePropertyGet("Cells", 2, 7).OlePropertySet("Value", WorkerName.c_str());

        vSheet.PG("Cells", 2, 9).PG("Font").PS("Name", "����"); //����
        vSheet.PG("Cells", 2, 9).PG("Font").PS("size", 12);     //��С
        vSheet.OlePropertyGet("Cells", 2, 9).OlePropertySet("Value", "���ڣ�");

        vSheet.PG("Cells", 2, 10).PG("Font").PS("Name", "����"); //����
        vSheet.PG("Cells", 2, 10).PG("Font").PS("size", 12);     //��С
        vSheet.OlePropertyGet("Cells", 2, 10).OlePropertySet("Value", DateStr.c_str());
        for(int j=0; j<dbg->Columns->Count; j++)
        {
        // �����е��и�
                vSheet.PG("Cells", 3, j + 1).PG("Font").PS("Name", "����"); //����
                vSheet.PG("Cells", 3, j + 1).PG("Font").PS("size", 12);     //��С
                vExcelApp.OlePropertyGet("Rows", 3).OlePropertySet("RowHeight", 20);
                vSheet.OlePropertyGet("Cells", 3, j + 1).OlePropertySet("Value", dbg->Columns->Items[j]->Caption.c_str());
        // ����������Ԫ��ı���ɫ
                Variant vInter = vSheet.OlePropertyGet( "Cells", 3, j + 1).OlePropertyGet("Interior");
                vInter.OlePropertySet("ColorIndex", 15); // ��ɫ
                vInter.OlePropertySet("Pattern", 1); // xlSolid
                vInter.OlePropertySet("PatternColorIndex", -4105); // xlAutomatic
         }
        // ������д��Excel���
        //dbg->DataSource->DataSet->First();
        TListItem       *ItemTemp;
        for(int i=0; i<nRowCount-1; i++)
        {
                // ��ͨ�����е��и�16
                ItemTemp=dbg->Items->Item[i];
                AnsiString      Caption=ItemTemp->Caption;
                AnsiString      Str;
                vExcelApp.OlePropertyGet("Rows", i + 2).OlePropertySet("RowHeight", 16);
                // 63 63 72 75 6E 2E 63 6F 6D
                for(int j=0; j<dbg->Columns->Count; j++)
                {
                        //vSheet.OlePropertyGet("Cells", i + 2, j + 1).OlePropertySet("Value",dbg->DataSource->DataSet->FieldByName(dbg->Columns->Items[j]->FieldName)->AsString.c_str())
                        vSheet.PG("Cells", i + 4, j + 1).PG("Font").PS("Name", "����"); //����
                        vSheet.PG("Cells", i + 4, j + 1).PG("Font").PS("size", 12);     //��С
                        if(j==0)
                                vSheet.OlePropertyGet("Cells", i + 4, j + 1).OlePropertySet("Value",ItemTemp->Caption.c_str());
                        else
                                {
                                        //Str=ItemTemp->SubItems->Strings[j-1].Text;
                                        if(ItemTemp->SubItems->Strings[j-1]!="")
                                             vSheet.OlePropertyGet("Cells", i + 4, j + 1).OlePropertySet("Value",ItemTemp->SubItems->Strings[j-1].c_str());
                                        else
                                             vSheet.OlePropertyGet("Cells", i + 4, j + 1).OlePropertySet("Value","");
                                }

                }

        }
        // ����Excel�ĵ����˳�
        vExcelApp.OlePropertyGet("ActiveWorkbook").OleFunction("SaveAs", strXlsFile.c_str());
        vExcelApp.OleFunction("Quit");
        vSheet = Unassigned;
        vExcelApp = Unassigned;
        // ��������
        MessageBox(0, "���ݵ������!","DBGrid2Excel", MB_OK | MB_ICONINFORMATION);
}
bool GetDestFilePath(AnsiString &FilePath)
{
        TOpenDialog *OpenDialog1;
        AnsiString      DateStr;
        TDateTime       DTTemp=Now();
        DateStr=DTTemp.DateString();
        OpenDialog1=new TOpenDialog(Application);
        if(OpenDialog1!=NULL)
        {
                //OpenDialog1->Files.Add("*xls�ļ�|*.xls");
                OpenDialog1->Filter="Xls�ļ�|*.xls";
                DateStr="����ͳ�Ʊ�"+DateStr;
                OpenDialog1->FileName=DateStr+".xls";
                if(OpenDialog1->Execute())
                {
                        FilePath=OpenDialog1->FileName;
                        delete OpenDialog1;
                        OpenDialog1=NULL;
                        return true;
                }
                else
                {
                        delete OpenDialog1;
                        OpenDialog1=NULL;
                        return false;
                }
        }
}
