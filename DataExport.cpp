/*****************************************************************   
  **   函数名:DBGridToExcel   
  **   输   入:TDBGrid   *,AnsiString   *   
  **   TDBGrid   *:数据来源。
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

        if(!dbg->DataSource->DataSet->Active) // 数据集没有打开就返回
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
                MessageBox(0, "启动 Excel 出错, 可能是没有安装Excel.","DBGrid2Excel", MB_OK | MB_ICONERROR);
                return;
        }
        // 隐藏Excel界面
        vExcelApp.OlePropertySet("Visible", true);
        // 新建一个工作表
        vExcelApp.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 工作表
        // 操作这个工作表
        vSheet = vExcelApp.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);
        // 设置Excel文档的字体
        vSheet.OleProcedure("Select"); 
        vSheet.OlePropertyGet("Cells").OleProcedure("Select");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Size", dbg->Font->Size);
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Name",dbg->Font->Name.c_str());
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("FontStyle", "常规");
        vSheet.OlePropertyGet("Cells", 1, 1).OleProcedure("Select");
        // 表格的行数
        int nRowCount(dbg->DataSource->DataSet->RecordCount + 1);
        nRowCount = nRowCount < 2? 2: nRowCount;
        // 表格的列数
        int nColCount(dbg->Columns->Count);
        nColCount = nColCount < 1? 1: nColCount;
        // 设置单元格的宽度
        for(int i=0; i<nColCount; i++)
        {
                int nColWidth = dbg->Columns->Items[i]->Width;
                vExcelApp.OlePropertyGet("Columns", i + 1).OlePropertySet("ColumnWidth", nColWidth / 7);
        }
        // 先将列名写入Excel表格
        for(int j=0; j<dbg->Columns->Count; j++)
        {
        // 标题行的行高
                vExcelApp.OlePropertyGet("Rows", 1).OlePropertySet("RowHeight", 20);
                vSheet.OlePropertyGet("Cells", 1, j + 1).OlePropertySet("Value", dbg->Columns->Items[j]->Title->Caption.c_str());
        // 设置列名单元格的背景色
                Variant vInter = vSheet.OlePropertyGet( "Cells", 1, j + 1).OlePropertyGet("Interior");
                vInter.OlePropertySet("ColorIndex", 15); // 灰色
                vInter.OlePropertySet("Pattern", 1); // xlSolid
                vInter.OlePropertySet("PatternColorIndex", -4105); // xlAutomatic
         }
        // 将DBGrid中的数据写入Excel表格
        dbg->DataSource->DataSet->First();
        for(int i=0; i<nRowCount-1; i++)
        {
        // 普通数据行的行高16
                vExcelApp.OlePropertyGet("Rows", i + 2).OlePropertySet("RowHeight", 16);
                // 63 63 72 75 6E 2E 63 6F 6D
                for(int j=0; j<dbg->Columns->Count; j++)
                {
                        vSheet.OlePropertyGet("Cells", i + 2, j + 1).OlePropertySet("Value",dbg->DataSource->DataSet->FieldByName(dbg->Columns->Items[j]->FieldName)->AsString.c_str());
                }
                dbg->DataSource->DataSet->Next();
        }
        // 保存Excel文档并退出
        vExcelApp.OlePropertyGet("ActiveWorkbook").OleFunction("SaveAs", strXlsFile.c_str());
        vExcelApp.OleFunction("Quit");
        vSheet = Unassigned;
        vExcelApp = Unassigned;
        // 工作结束
        MessageBox(0, "数据导出完毕!","DBGrid2Excel", MB_OK | MB_ICONINFORMATION);
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
                MessageBox(0, "启动 Excel 出错, 可能是没有安装Excel.","DBGrid2Excel", MB_OK | MB_ICONERROR);
                return;
        }
        // 隐藏Excel界面
        vExcelApp.OlePropertySet("Visible", true);
        // 新建一个工作表
        vExcelApp.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 工作表
        // 操作这个工作表
        vSheet = vExcelApp.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);
        // 设置Excel文档的字体
        vSheet.OleProcedure("Select");
        vSheet.OlePropertyGet("Cells").OleProcedure("Select");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Size", 18);
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Name","黑体");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("FontStyle", "常规");
        vSheet.OlePropertyGet("Cells", 1, 1).OleProcedure("Select");
        // 表格的行数
        int nRowCount(dbg->Items->Count+1);
        nRowCount = nRowCount < 2? 2: nRowCount;
        // 表格的列数
        int nColCount(dbg->Columns->Count);
        nColCount = nColCount < 1? 1: nColCount;
        // 设置单元格的宽度
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
        // 先将列名写入Excel表格

        vExcelApp.OlePropertyGet("Rows", 1).OlePropertySet("RowHeight", 40);
        vSheet.OlePropertyGet("Range","A1:K1").OleFunction("Merge",false);
        vSheet.PG("Cells", 1, 1).PG("Font").PS("Name", "宋体"); //字体
        vSheet.PG("Cells", 1, 1).PG("Font").PS("size", 28);     //大小
        vSheet.OlePropertyGet("Cells", 1, 1).OlePropertySet("Value", "                销售统计表");

        // 设置Excel文档的字体
        /*
        vSheet.OleProcedure("Select");
        vSheet.OlePropertyGet("Cells").OleProcedure("Select");
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Size", dbg->Font->Size);
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("Name",dbg->Font->Name.c_str());
        vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font").OlePropertySet("FontStyle", "常规");
        vSheet.OlePropertyGet("Cells", 1, 1).OleProcedure("Select");
        */
        vExcelApp.OlePropertyGet("Rows", 2).OlePropertySet("RowHeight", 20);
        vSheet.PG("Cells", 2, 2).PG("Font").PS("Name", "黑体"); //字体
        vSheet.PG("Cells", 2, 2).PG("Font").PS("size", 12);     //大小
        vSheet.OlePropertyGet("Cells", 2, 2).OlePropertySet("Value", "填报单位：");

        vSheet.PG("Cells", 2, 3).PG("Font").PS("Name", "黑体"); //字体
        vSheet.PG("Cells", 2, 3).PG("Font").PS("size", 12);     //大小
        vSheet.OlePropertyGet("Cells", 2, 3).OlePropertySet("Value", UnitName.c_str());

        vSheet.PG("Cells", 2, 6).PG("Font").PS("Name", "黑体"); //字体
        vSheet.PG("Cells", 2, 6).PG("Font").PS("size", 12);     //大小
        vSheet.OlePropertyGet("Cells", 2, 6).OlePropertySet("Value", "填报人：");


        vSheet.PG("Cells", 2, 7).PG("Font").PS("Name", "黑体"); //字体
        vSheet.PG("Cells", 2, 7).PG("Font").PS("size", 12);     //大小
        vSheet.OlePropertyGet("Cells", 2, 7).OlePropertySet("Value", WorkerName.c_str());

        vSheet.PG("Cells", 2, 9).PG("Font").PS("Name", "黑体"); //字体
        vSheet.PG("Cells", 2, 9).PG("Font").PS("size", 12);     //大小
        vSheet.OlePropertyGet("Cells", 2, 9).OlePropertySet("Value", "日期：");

        vSheet.PG("Cells", 2, 10).PG("Font").PS("Name", "黑体"); //字体
        vSheet.PG("Cells", 2, 10).PG("Font").PS("size", 12);     //大小
        vSheet.OlePropertyGet("Cells", 2, 10).OlePropertySet("Value", DateStr.c_str());
        for(int j=0; j<dbg->Columns->Count; j++)
        {
        // 标题行的行高
                vSheet.PG("Cells", 3, j + 1).PG("Font").PS("Name", "宋体"); //字体
                vSheet.PG("Cells", 3, j + 1).PG("Font").PS("size", 12);     //大小
                vExcelApp.OlePropertyGet("Rows", 3).OlePropertySet("RowHeight", 20);
                vSheet.OlePropertyGet("Cells", 3, j + 1).OlePropertySet("Value", dbg->Columns->Items[j]->Caption.c_str());
        // 设置列名单元格的背景色
                Variant vInter = vSheet.OlePropertyGet( "Cells", 3, j + 1).OlePropertyGet("Interior");
                vInter.OlePropertySet("ColorIndex", 15); // 灰色
                vInter.OlePropertySet("Pattern", 1); // xlSolid
                vInter.OlePropertySet("PatternColorIndex", -4105); // xlAutomatic
         }
        // 将数据写入Excel表格
        //dbg->DataSource->DataSet->First();
        TListItem       *ItemTemp;
        for(int i=0; i<nRowCount-1; i++)
        {
                // 普通数据行的行高16
                ItemTemp=dbg->Items->Item[i];
                AnsiString      Caption=ItemTemp->Caption;
                AnsiString      Str;
                vExcelApp.OlePropertyGet("Rows", i + 2).OlePropertySet("RowHeight", 16);
                // 63 63 72 75 6E 2E 63 6F 6D
                for(int j=0; j<dbg->Columns->Count; j++)
                {
                        //vSheet.OlePropertyGet("Cells", i + 2, j + 1).OlePropertySet("Value",dbg->DataSource->DataSet->FieldByName(dbg->Columns->Items[j]->FieldName)->AsString.c_str())
                        vSheet.PG("Cells", i + 4, j + 1).PG("Font").PS("Name", "宋体"); //字体
                        vSheet.PG("Cells", i + 4, j + 1).PG("Font").PS("size", 12);     //大小
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
        // 保存Excel文档并退出
        vExcelApp.OlePropertyGet("ActiveWorkbook").OleFunction("SaveAs", strXlsFile.c_str());
        vExcelApp.OleFunction("Quit");
        vSheet = Unassigned;
        vExcelApp = Unassigned;
        // 工作结束
        MessageBox(0, "数据导出完毕!","DBGrid2Excel", MB_OK | MB_ICONINFORMATION);
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
                //OpenDialog1->Files.Add("*xls文件|*.xls");
                OpenDialog1->Filter="Xls文件|*.xls";
                DateStr="销售统计表"+DateStr;
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
