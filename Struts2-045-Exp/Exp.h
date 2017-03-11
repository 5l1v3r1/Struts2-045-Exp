#pragma once
class Exp
{
public:
	Exp(void);
	~Exp(void);
	CString executeCommand(CString url,CString command); //ִ���������ִ��������
	CString getRootPath(CString url,DWORD& statusCode); //��ȡվ���Ŀ¼
	CString writeFile(CString url,CString filePath,CString writeData); //д�ļ�
	CString getShell(CString url,CString shellName,CString shellData); //Getshell shell�ڸ�Ŀ¼
private:
	CString httpPost(CString url,CString header,CString postData,DWORD& statusCode,DWORD timeout,DWORD retryTime,DWORD retryDelay); //POST���󣬷�������ҳ����,statusCodeΪ״̬�� -1��ʾURL���� 0��ʾHttp������� ������ʾHTTP״̬��
	bool urlParse(CString url,int&httpType,CString& host,unsigned short int& port,CString& path); //URL������������õ� HTTP����(httpType):0ΪHttp 1ΪHttps  host ������ port�˿ں� path����·�� ����ȷURL����FALSE
	CString urlEncode(CString strData,int srcCodepage, int dstCodepage); //URL���� srcCodepageԭ���� dstCodepageת���������
	CString urlEncodeCore(CString strData,int srcCodepage, int dstCodepage); //URL�������ʵ�� srcCodepageԭ���� dstCodepageת���������
	CString writeJspHelperCode; //JSPд�ļ�����
	CString jspHelperFileName; //JSPд�ļ� Ĭ���ļ���
};

