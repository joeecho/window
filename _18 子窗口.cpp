// _18 子窗口.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

HINSTANCE g_hinsatance;
#define EDIT_INDETIFIER 0x1001
#define BUTTON1_INDETIFED 0x1002
#define BUTTON2_INDETIFED 0x1003
LRESULT CALLBACK WindowProc(
							HWND hwnd,      // handle to window
							UINT uMsg,      // message identifier
							WPARAM wParam,  // first message parameter
							LPARAM lParam   // second message parameter
							);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	g_hinsatance = hInstance;
	//定义窗口
	TCHAR classname[] = TEXT("test message window");
	WNDCLASS wndclass = {0};
	wndclass.hbrBackground = (HBRUSH)COLOR_INACTIVECAPTION;
	wndclass.lpszClassName = classname;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	RegisterClass( &wndclass );
	
	//创建并显示窗口
	HWND hwnd = CreateWindow(
		classname,
		TEXT("message test app"),
		WS_OVERLAPPEDWINDOW,
		10,
		10,
		600,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	
	ShowWindow( hwnd, SW_SHOW );
	
	//接收消息并处理
	MSG msg;
	BOOL bret;
	TCHAR szoutbuff[80];
	while( (bret = GetMessage( &msg, NULL, 0, 0 )) != NULL){
		if(bret == -1){
			sprintf(szoutbuff,"Error: %d",GetLastError());
			OutputDebugString(szoutbuff);	//handle the error and possibly exit
		}
		else{
			//转换消息
			TranslateMessage( &msg );
			//分发消息
			DispatchMessage( &msg );
		}
	};
	return 0;
}

LRESULT CALLBACK WindowProc(
							HWND hwnd,      // handle to window
							UINT uMsg,      // message identifier
							WPARAM wParam,  // first message parameter
							LPARAM lParam   // second message parameter
							){
	//显示消息
	TCHAR szoutbuff1[80];
	/*	sprintf( szoutbuff1,"消息: %x   %x\n", uMsg, wParam);
	OutputDebugString( szoutbuff1 );*/
	switch(uMsg){
	case WM_DESTROY:{//窗口销毁,非常重要，否则关闭窗口，但程序仍然在运行
		PostQuitMessage(0);
		return 0;
					}
	case WM_CREATE:{
		//创建文本框
		CreateWindow(
			"EDIT",
			"",
			WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_MULTILINE,
			0,
			0,
			500,
			360,
			hwnd,
			(HMENU)EDIT_INDETIFIER,
			g_hinsatance,
			NULL
			);
		//创建按钮1
		CreateWindow(
			"BUTTON",
			"写入",
			WS_CHILD|WS_VISIBLE,
			520,
			200,
			60,
			30,
			hwnd,
			(HMENU)BUTTON1_INDETIFED,
			g_hinsatance,
			NULL
			);
		//创建按钮2
		CreateWindow(
			"BUTTON",
			"读取",
			WS_CHILD|WS_VISIBLE,
			520,
			250,
			60,
			30,
			hwnd,
			(HMENU)BUTTON2_INDETIFED,
			g_hinsatance,
			NULL
			);
		return 0;
				   }
	case WM_COMMAND:{
		//MessageBox( 0, 0, 0, 0 );
		switch( LOWORD(wParam) ){
		case BUTTON1_INDETIFED:{
			SetDlgItemText( hwnd, EDIT_INDETIFIER, "写入");
			//MessageBox( hwnd, "写入", "写入", MB_OK );
			break;
							   }
		case BUTTON2_INDETIFED:{
			GetDlgItemText( hwnd, EDIT_INDETIFIER, szoutbuff1, 79 );
			OutputDebugString( szoutbuff1 );	
			//MessageBox( hwnd, "获取", "获取", MB_OK );
			break;
							   }
		}
					}
		
	}
	return DefWindowProc( hwnd, uMsg, wParam, lParam );
};