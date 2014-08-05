// leidian0_1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "leidian0_1.h"
#include "GShape.h"
#include"GWorld.h"
#include"GObject.h"
#include"RealObject.h"
#include<vector>
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND  hwnd;
GWorld *gameworld;//


// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

  
HDC mdc;// 用于保存位图的内存DC  

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;
	gameworld=NULL;
	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LEIDIAN0_1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LEIDIAN0_1));
	
	// 主消息循环:
	
		while (GetMessage(&msg, NULL, 0, 0))
		{
			
			
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	
	

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE("pic\\icon1.ico"));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE("pic\\icon1.ico");
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
//重启
void restart(HWND hWnd)
{
	delete gameworld;
	gameworld=new GWorld();
	Space sp;
   sp.ltx=200;
   sp.lty=200;
   sp.rdx=1000;
   sp.rdy=800;
	gameworld->setGWorld(sp,0,hWnd);//初始化gameworld
	gameworld->m_iControl.douwn=0;
	gameworld->m_iControl.up=0;
	gameworld->m_iControl.left=0;
	gameworld->m_iControl.right=0;
	gameworld->m_iControl.ctrl=11;
	string s;
	GObject* p_OB=NULL;

	//背景
    s="Pic\\xxxx.bmp";//BMP路径
    GShape sBackGround(800,600,800,600,0,0,s);//建立形状
	p_OB=new BackGround(hwnd,sBackGround,0,0,0,0);//初始化背景
    gameworld->addObject(p_OB);
    //补给
    s="Pic\\BONUS.BMP";//BMP路径
    GShape sBONUS0(200,300,100,100,0,0,s);//建立形状BOUNS0
    p_OB=new BONUS(hwnd,sBONUS0,0,1,0,0);//初始化背景
    
	//我机
	s="Pic\\CENTER.BMP";
	GShape sPlane(50,60,50,60,0,0,s);//建立形状plane
	p_OB=new ourPlane(hwnd,sPlane,0,0,350,500);//初始化feiji
	p_OB->setboom("Pic\\EXPLODE.BMP");
	p_OB->classnum=1;
	gameworld->addObject(p_OB);
	gameworld->setplanenum(p_OB->m_iNum);
	
	//子弹
	s="Pic\\BULLET.BMP";
	GShape sBullet(80,20,8,8,18,3,s);//建立形状plane
	p_OB=new Bullet(hwnd,sBullet,0,0,50,150);//初始化feiji
	
	//敌机
	s="Pic\\ENEMY.BMP";
	GShape sePlane(230,130,50,60,0,0,s);//建立形状plane
	p_OB=new ePlane(hwnd,sePlane,0,2,300,0);//初始化feiji
	p_OB->setboom("Pic\\EXPLODE.BMP");
	p_OB->classnum=2;
	gameworld->addObject(p_OB);

	

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
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   Space sp;
   sp.ltx=200;
   sp.lty=200;
   sp.rdx=1000;
   sp.rdy=800;
   
  
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, sp.rdx-sp.ltx, sp.rdy-sp.lty, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
	
   	
  restart(hWnd);
	SetTimer(hWnd, 1, 20, NULL);//游戏世界时间
    SetTimer(hWnd, 2, 1250, NULL);//低级出现间隔
	SetTimer(hWnd, 3, 10, NULL);//绘图间隔

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		if(NULL!=gameworld)
		{
			gameworld->show();
		}
		//UpdateWindow(hWnd);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	

	case WM_KEYDOWN:
            // Handle any non-accelerated key commands
		gameworld->getControl(wParam);
            switch (wParam)
            {
				case VK_RETURN : restart(hWnd);break;//enter
                case VK_ESCAPE:
                case VK_F12:
				
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    return 0L;
            }
            break;
	case WM_KEYUP:
            // Handle any non-accelerated key commands

			gameworld->getDownControl(wParam);
            
            break;
	case WM_TIMER:
            // Update and flip surfaces//***********************************循环
            if (1== wParam)
            {
				gameworld->run();
				
            }
			if (2== wParam)
            {
				gameworld->addenemy();
            }
			if (3== wParam)
            {
				gameworld->show();
				UpdateWindow(hWnd);
            }
            break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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
