//3dSoftRenderer.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "3dSoftRenderer.h"
#include<Windows.h>
#include<windowsx.h>
#include<mmsystem.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#include<string.h>
#include<stdarg.h>
#include<stdio.h>
#include<math.h>
#include<io.h>
#include<fcntl.h>

#define WIN32_LEAN_AND_MEAN
#define WINDOW_CLASS_NAME "WIN3DCLASS"
#define WINDOW_TITLE "T3D Graphics Console Alpha 1.0"
#define MAX_LOADSTRING 100
#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// 全局变量: 
HWND main_window_handle = NULL;
HINSTANCE main_instance = NULL;
char buffer[256];
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名


												// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int Game_Init(void *parms = NULL);
int Game_Shutdown(void *parms = NULL);
int Game_Main(void *parms = NULL);



int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       nCmdShow)
{
	//UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。

	//windows 窗口模板
	WNDCLASS winclass;
	HWND hwnd;		//窗口句柄
	MSG msg;		//消息
	HDC hdc;		//设置场境
	PAINTSTRUCT ps;	//paintstruct

					//winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	//事件处理函数, WinProc是回调函数
	winclass.lpfnWndProc = WndProc;
	winclass.cbClsExtra = 0; //额外的类信息空间
	winclass.cbWndExtra = 0; //额外的窗口信息空间
	winclass.hInstance = hInstance;
	//图标句柄
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//光标句柄
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//绘制窗口的画刷句柄
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//菜单字段
	winclass.lpszMenuName = NULL;
	//Windows序号跟踪识别每个windows类，可以用类名来引用新的windows类。
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	//winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//定义窗口类后需要进行注册
	if (!RegisterClass(&winclass))
		return(0);

	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,
		0, 0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL))) {
		return(0);
	}
	main_window_handle = hwnd;
	main_instance = hInstance;

	ShowWindow(hwnd, nCmdShow);

	Game_Init();

	/*
	//UpdateWindow(hwnd);
	// 初始化全局字符串
	//szTitle[MAX_LOADSTRING] = L"";
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY3DSOFTRENDERER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
	return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DSOFTRENDERER));

	MSG msg;


	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
	}

	return (int) msg.wParam;
	*/

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//是否为退出消息
			if (msg.message == WM_QUIT) {
				break;
			}
			//转换加速键
			TranslateMessage(&msg);
			//将消息发送给wndProc
			DispatchMessage(&msg);
		}
		Game_Main();
	}

	Game_Shutdown();

	return(msg.wParam);
}

//T3DII game program console function
//游戏初始化工作
int Game_Init(void *parms) {
	return(1);
}

//关闭释放分配的资源
int Game_Shutdown(void *parms) {
	return(1);
}

//实时调用
int Game_Main(void *parms) {
	if (KEY_DOWN(VK_ESCAPE)) {
		PostMessage(main_window_handle, WM_DESTROY, 0, 0);
	}
	return(1);
}


/*
//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
WNDCLASSEXW wcex;

wcex.cbSize = sizeof(WNDCLASSEX);

wcex.style          = CS_DBLCLKS| CS_OWNDC| CS_HREDRAW | CS_VREDRAW;
wcex.lpfnWndProc    = WndProc;
wcex.cbClsExtra     = 0;
wcex.cbWndExtra     = 0;
wcex.hInstance      = hInstance;
wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
wcex.lpszMenuName   = NULL;
wcex.lpszClassName  = szWindowClass;
//wcex.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
hInst = hInstance; // 将实例句柄存储在全局变量中

//HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
//   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
0, 0, 400, 400, NULL, NULL, hInstance, NULL);

if (!hWnd)
{
return FALSE;
}

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);

return TRUE;
}
*/

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;		//设置场境句柄

	switch (message)
	{
	case WM_CREATE:
	{
		return (0);
	}
	break;
	/*
	case WM_COMMAND:
	{
	int wmId = LOWORD(wParam);
	// 分析菜单选择:
	switch (wmId)
	{
	case IDM_ABOUT:
	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
	break;
	case IDM_EXIT:
	DestroyWindow(hWnd);
	break;
	default:
	return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	break;
	*/
	case WM_PAINT:
	{
		//PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd, &ps);
		return(0);
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return(0);
	}
	break;
	default:break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
	//return 0;
}


/*
// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
UNREFERENCED_PARAMETER(lParam);
switch (message)
{
case WM_INITDIALOG:
return (INT_PTR)TRUE;

case WM_COMMAND:
if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
{
EndDialog(hDlg, LOWORD(wParam));
return (INT_PTR)TRUE;
}
break;
}
return (INT_PTR)FALSE;
}
*/