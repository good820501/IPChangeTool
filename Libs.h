#ifndef FCLIBS_H
#define FCLIBS_H

#include <vcl.h>

//������Ϣ
void GetLastErrMsg(char *buf);
void WriteLastErrMsg(void);

//��ָ��λ����ͼ��ͼ�����ļ�
int StretchPicture(TCanvas * Canvas,TRect DispRect,AnsiString FileName);

#define CONFIGFILE	"./CfgFile.ini"
int  GetCfgInt(char *lpAppName, char *lpKeyName, int nDefault);
int  GetCfgStr(char *lpAppName, char *lpKeyName, char *lpDefault, char *lpvalue, int nSize);
void SetCfgInt(char *lpAppName, char *lpKeyName, int nValue);
void SetCfgStr(char *lpAppName, char *lpKeyName, char	*lpValue);
void ChangeServerIP(char *buf);

//���𡢹ػ�
bool    ChangePrivileges(void);
void    ShutDown(HWND hWnd);
void    Reboot(HWND hWnd);

void SetSystemTime(char *buf);
void GetIniStr(char *req, char *rsp);
void SetIniStr(char *req, char *rsp);
long GetCfgFileData(char *req, char **ppdata);
long GetDBFileData(char *req, char **ppdata);
long GetFileData(char *req, char **ppdata);
long GetFileDataEx(char *req, char **ppdata);
void SaveFileDataBin(char *fileinfo, int nfileinfolen, char *rsp);
void SaveFileDataAsc(char *fileinfo, int nfileinfolen, char *rsp);
int  PathOrFile(char *pathfile);
void GetValue(char *buf, char *value, int *start);
//Զ��������������
void StartupPlug(char *req, char *rsp);
void ClosePlug(void);

// ʱ�亯��
/*
fmt:
$Y year(0000)	$m month(00)	$d day(00)
$H hour(00)	$M minute(00)	$S second(00)
*******************************************************************************/
char *Sstrftime(char *buf, const size_t maxsize, const char *fmt);

// ����
HANDLE GetMutex(LPSTR lpszMutexName, DWORD dwWaitMilliseconds=1000*20);
// ����
void FreeMutex(HANDLE &hMutex);

#endif
