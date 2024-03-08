// MouseExample.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MouseExample.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MOUSEEXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSEEXAMPLE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOUSEEXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass,TEXT("Nguyễn Quỳnh Chi_211201577"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT pt[1000], point[4];
    static int count = 0, m = 50, s = 0;
    HDC hdc;
    static TCHAR timeLeft[16];
    static int x, y,hinh,xLeft,yTop, xRight, yBottom;
    static HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

    switch (message)
    {
    case WM_SIZE:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        break;
    case WM_CLOSE:
        if (MessageBox(hWnd, TEXT("Bạn có muốn thoát không ?"), TEXT("Yes or No"), MB_YESNO) == IDYES) {
            PostQuitMessage(0);
        }
        break;
    case WM_LBUTTONDOWN:
        xLeft = LOWORD(lParam); 
        yTop = HIWORD(lParam); 
       /* pt[count].x = LOWORD(lParam); 
        pt[count].y = HIWORD(lParam);
        hdc = GetDC(hWnd); 
        SetPixel(hdc, pt[count].x, pt[count].y, 0); 
        ReleaseDC(hWnd, hdc); 
        count++; */
        break;
    case WM_LBUTTONUP:
        xRight = LOWORD(lParam);
        yBottom = HIWORD(lParam);

        //Vẽ hình
        hdc = GetDC(hWnd); 
        SelectObject(hdc, hpen); 

        if (hinh == ID_H_TGV) {
            point[0].x = xLeft;
            point[0].y = yTop;
            point[1].x = xLeft;
            point[1].y = yBottom;
            point[2].x = xRight; 
            point[2].y = yBottom;

            Polygon(hdc, point, 3);
        }
        ReleaseDC(hWnd, hdc); 
        break;
    case WM_CREATE:
        //Tạo Timer
        SetTimer(hWnd, 1, 1000, NULL);
        break;
    case WM_TIMER:
        // Sau 1000ms sẽ tính lại thời gian
        if (s > 0 && s <= 59) {
            s = s - 1;
        }
        else {
            if (s == 0 && m > 0) {
                m = m - 1;
                s = 59;
            }
            if (s == 0 && m == 0) {
                KillTimer(hWnd, 1);
            }
        }
        //Hàm tạo chuỗi
        wsprintfW(timeLeft, L"Time Left: %d:%d", m, s);
        hdc = GetDC(hWnd);
        TextOut(hdc, x + 800, y - 30, timeLeft, 16);
        ReleaseDC(hWnd, hdc);
        break;
    case WM_RBUTTONDOWN:
        hdc = GetDC(hWnd);
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count;j++) {
                MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
                LineTo(hdc, pt[j].x, pt[j].y);
            }
        }
        break;
    case WM_LBUTTONDBLCLK:
        InvalidateRect(hWnd, NULL, true);
        count = 0;
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_H_HCN:
            case ID_H_TGV:
                hinh = wmId;
                break;
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
