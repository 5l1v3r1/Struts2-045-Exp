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
	CString httpPost(CString url,CString header,CString postData,DWORD& statusCode,DWORD timeout,DWORD retryTime,DWORD retryDelay); //POST���󣬷�������ҳ����,statusCodeΪ���ص�HTTP״̬��
	CString urlEncode(CString strData,int srcCodepage, int dstCodepage); //URL���� srcCodepageԭ���� dstCodepageת���������
	CString urlEncodeCore(CString strData,int srcCodepage, int dstCodepage); //URL�������ʵ�� srcCodepageԭ���� dstCodepageת���������
	CString writeJspHelperCode; //JSPд�ļ�����
	CString jspHelperFileName; //JSPд�ļ� Ĭ���ļ���
};

