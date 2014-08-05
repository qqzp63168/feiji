// leidian0_1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "leidian0_1.h"
#include "GShape.h"
#include"GWorld.h"
#include"GObject.h"
#include"RealObject.h"
#include<vector>
#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND  hwnd;
GWorld *gameworld;//


// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

  
HDC mdc;// ���ڱ���λͼ���ڴ�DC  

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;
	gameworld=NULL;
	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LEIDIAN0_1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LEIDIAN0_1));
	
	// ����Ϣѭ��:
	
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//����
void restart(HWND hWnd)
{
	delete gameworld;
	gameworld=new GWorld();
	Space sp;
   sp.ltx=200;
   sp.lty=200;
   sp.rdx=1000;
   sp.rdy=800;
	gameworld->setGWorld(sp,0,hWnd);//��ʼ��gameworld
	gameworld->m_iControl.douwn=0;
	gameworld->m_iControl.up=0;
	gameworld->m_iControl.left=0;
	gameworld->m_iControl.right=0;
	gameworld->m_iControl.ctrl=11;
	string s;
	GObject* p_OB=NULL;

	//����
    s="Pic\\xxxx.bmp";//BMP·��
    GShape sBackGround(800,600,800,600,0,0,s);//������״
	p_OB=new BackGround(hwnd,sBackGround,0,0,0,0);//��ʼ������
    gameworld->addObject(p_OB);
    //����
    s="Pic\\BONUS.BMP";//BMP·��
    GShape sBONUS0(200,300,100,100,0,0,s);//������״BOUNS0
    p_OB=new BONUS(hwnd,sBONUS0,0,1,0,0);//��ʼ������
    
	//�һ�
	s="Pic\\CENTER.BMP";
	GShape sPlane(50,60,50,60,0,0,s);//������״plane
	p_OB=new ourPlane(hwnd,sPlane,0,0,350,500);//��ʼ��feiji
	p_OB->setboom("Pic\\EXPLODE.BMP");
	p_OB->classnum=1;
	gameworld->addObject(p_OB);
	gameworld->setplanenum(p_OB->m_iNum);
	
	//�ӵ�
	s="Pic\\BULLET.BMP";
	GShape sBullet(80,20,8,8,18,3,s);//������״plane
	p_OB=new Bullet(hwnd,sBullet,0,0,50,150);//��ʼ��feiji
	
	//�л�
	s="Pic\\ENEMY.BMP";
	GShape sePlane(230,130,50,60,0,0,s);//������״plane
	p_OB=new ePlane(hwnd,sePlane,0,2,300,0);//��ʼ��feiji
	p_OB->setboom("Pic\\EXPLODE.BMP");
	p_OB->classnum=2;
	gameworld->addObject(p_OB);

	

}


//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
	SetTimer(hWnd, 1, 20, NULL);//��Ϸ����ʱ��
    SetTimer(hWnd, 2, 1250, NULL);//�ͼ����ּ��
	SetTimer(hWnd, 3, 10, NULL);//��ͼ���

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
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
            // Update and flip surfaces//***********************************ѭ��
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

// �����ڡ������Ϣ�������
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
