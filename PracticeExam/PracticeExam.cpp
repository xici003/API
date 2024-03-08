// PracticeExam.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PracticeExam.h"

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
    LoadStringW(hInstance, IDC_PRACTICEEXAM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRACTICEEXAM));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRACTICEEXAM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
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

   HWND hWnd = CreateWindowW(szWindowClass, TEXT("Vẽ hình"), WS_OVERLAPPEDWINDOW,
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
    HDC hdc;
    static HPEN hpen;
    static HBRUSH hBrush;
    static COLORREF colorPen, colorBrush = WHITE_BRUSH; 
    static int hinh, xLeft, yTop, xRight, yBottom;
    static int stylePen;
    static POINT pt[4];
 
    switch (message)
    {
    case WM_LBUTTONDOWN:
        xLeft = LOWORD(lParam);
        yTop = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        xRight = LOWORD(lParam);
        yBottom = HIWORD(lParam);

        hpen = CreatePen(stylePen, 1, colorPen);   

        hdc = GetDC(hWnd);  

        SelectObject(hdc, hpen);  
        SelectObject(hdc, hBrush); 

        if (hinh == ID_H_TGV) {
            pt[0].x = xLeft;
            pt[0].y = yTop;
            pt[1].x = xLeft;
            pt[1].y = yBottom; 
            pt[2].x = xRight; 
            pt[2].y = yBottom; 

            Polygon(hdc, pt, 3);
        }
        if (hinh == ID_H_HCN) { 
            Rectangle(hdc, xLeft, yTop, xRight, yBottom); 
        } 
        if (hinh == ID_H_Chord) {
            Chord(hdc, xLeft, yTop, xRight, yBottom, xLeft, yTop, xRight, yBottom);
        }
        if (hinh == ID_H_HinhThoi) {
            pt[0].x = xLeft + ((xRight - xLeft) / 2);
            pt[0].y = yTop;
            pt[1].x = xRight;
            pt[1].y = yTop + (yBottom - yTop) / 2;
            pt[2].x = xLeft + ((xRight - xLeft) / 2); 
            pt[2].y = yBottom;
            pt[3].x = xLeft;
            pt[3].y = yTop + (yBottom - yTop) / 2;

            Polygon(hdc, pt, 4);
        }

        ReleaseDC(hWnd, hdc); 
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_H_TGV:
            case ID_H_HCN:
            case ID_H_Chord:
            case ID_H_HinhThoi:
                hinh = wmId;
                break;
            case ID_H_Exit:
                if (MessageBox(hWnd, TEXT("Bạn có muốn thoát không ?"), TEXT("Yes or No"), MB_YESNO) == IDYES) {
                    PostQuitMessage(0);
                }
                break;
            case ID_MV_xanh: 
                colorPen = RGB(0, 0, 255); 
                break;
            case ID_MV_Tim:
                colorPen = RGB(238, 230, 238); 
                break;
            case ID_MN_Do:
                hBrush = CreateSolidBrush(RGB(255, 0, 0));
                break;
            case ID_MN_Vang:
                hBrush = CreateSolidBrush(RGB(255, 255, 0));
                break;
            case ID_K_Dash:
                stylePen = PS_DASH;
                break;
            case ID_K_Solid:
                stylePen = PS_SOLID;
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
