// Nastia_4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Nastia_4.h"
#include "thread"
#include <windowsx.h>


#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hwnd;
// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.
 
   

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NASTIA4, szWindowClass, MAX_LOADSTRING);

    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NASTIA4));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NASTIA4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, L"triangle", WS_OVERLAPPEDWINDOW,
      100, 100, 700, 739, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
  
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   hwnd = hWnd;
   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//


bool active;
struct point {
    int x, y;
};
#define fract_size 2
enum fract {triangle, carpet};
uint32_t fra=triangle;
int clicks = -1;
point* points = new point[8];

void clear();
void draw3(point* points, HDC hdc);
void draw4(point* points, HDC hdc);
void onClick(int64_t par);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    switch (message)
    {

  


    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            --fra %= fract_size;
            clicks = -1;
           
            clear();
            if (fra == triangle)SetWindowTextA(hwnd, "triangle");
            if (fra == carpet)SetWindowTextA(hwnd, "carpet");
            break;

        case VK_RIGHT:
            ++fra %= fract_size;
            clicks = -1;
          
            clear();
            if (fra == triangle)SetWindowTextA(hwnd, "triangle");
            if (fra == carpet)SetWindowTextA(hwnd, "carpet");
            break;
        case VK_SPACE:
            clicks = -1;
            clear();
            break;

        }



        break;


  
    case WM_LBUTTONDOWN:
    {
        onClick(lParam);
        
       
    }
     
        break;

   

        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
          
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
            
          
          



            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        clear();
      
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void onClick(int64_t par) {
    clicks++;
    
    if (fra == triangle) {
         
        clicks %= 3;
       
            points[clicks] = { GET_X_LPARAM(par), GET_Y_LPARAM(par) };
           
            
            if (clicks == 2 && !active) {
                active = true;
                std::thread t(draw3, points, GetDC(hwnd));
                t.detach();
                
            }

            
    }
    if (fra == carpet) {

        clicks %= 4;
        
       
        points[clicks*2] = { GET_X_LPARAM(par), GET_Y_LPARAM(par) };
        if (clicks > 0) {
            points[clicks * 2 - 1] = { (points[clicks * 2].x + points[clicks * 2 - 2].x) / 2,(points[clicks * 2].y + points[clicks * 2 - 2].y) / 2 };
            points[clicks * 2 + 1] = { (points[clicks * 2].x + points[(clicks * 2 + 2)%8].x) / 2,(points[clicks * 2].y + points[(clicks * 2 + 2)%8].y) / 2 };
        }
        if (clicks == 0 && active) {
            points[1] = { (points[0].x + points[2].x) / 2,(points[0].y + points[2].y) / 2 };
            points[7] = { (points[6].x + points[0].x) / 2,(points[6].y + points[0].y) / 2 };
        }
    

        if (clicks == 3 && !active) {
            
            active = true;
            std::thread t(draw4, points, GetDC(hwnd));
            t.detach();
           
        }
        

    }

    
}



void clear() {
    active = false;
  
    RECT r;
    GetWindowRect(hwnd, &r);
    int h = r.bottom - r.top;
    int w = r.right - r.left;
    Rectangle(GetDC(hwnd), 0, 0, w, h);

}


void draw3(point* points, HDC hdc) {

    point p = points[0];
    int n=0;
   
    while (active) {
        
       
        n = rand() % 3;
        
        

        p = { (int)((p.x + points[n].x) / 2),(int)((p.y + points[n].y) / 2) };
        
        RGB(255, 255, 255);
        SetPixelV(hdc, p.x, p.y, RGB((n==0)*255, (n == 1) * 255, (n == 2) * 255));
     
    }
    
    

}

void draw4(point* points, HDC hdc) {
    point p = points[0];
    int n = 0;
    while (active) {
       

        n = rand() % 8;

        p = { (int)((p.x + 2 * points[n].x) / 3),(int)((p.y + 2 * points[n].y) / 3) };
        SetPixelV(hdc, p.x, p.y, 0x00123456 * n);
     
    }

}