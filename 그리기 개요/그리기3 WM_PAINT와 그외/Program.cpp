//Windows API
/*
* WM_PAINT에서 그리기와 다른 곳에서 그리기의 차이점
* 1. WM_PAINT는 무효화 영역이 생겨서 다시 그려야 할 때 발생
*      BeginPaint로 DC 발급 EndPaint로 DC해제
* 2. 그 외
*      GetDC로 발급 ReleaseDC로 해제
* 실습 시나리오
* 마우스 왼쪽 클릭하는 지점에 작은 원을 그리시오.
* (창을 최소화시켰다가 다시 최대화하여도 그렸던 내용을 유지하게 하려면?)
*/



#include <Windows.h>
#define MY_DEF_STYLE CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
#include <list>
#include <iterator>
using namespace std;
list<POINT> points;

INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
    //윈도우 클래스 속성 설정
    WNDCLASS wndclass = { 0 };
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hInstance = hIns;//GetModuleHandle(0);
    wndclass.hIcon = LoadIcon(0, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(0, IDC_ARROW);
    wndclass.lpfnWndProc = MyWndProc;
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = TEXT("mywindow");
    wndclass.style = MY_DEF_STYLE;
    //윈도우 클래스 등록
    RegisterClass(&wndclass);

    //윈도우 개체 생성
    HWND hWnd = CreateWindow(TEXT("mywindow"),//클래스 이름
        TEXT("타이틀"),//타이틀 명
        WS_OVERLAPPEDWINDOW,//윈도우 스타일
        100, 30, 700, 600,//Left, Top, Width, Height
        0, //부모 윈도우 핸들
        0,//메뉴
        hIns,//모듈 핸들
        0 //WM_CREATE에 전달할 인자       
    );
    //윈도우 개체 시각화
    ShowWindow(hWnd, SW_SHOW);
    //메시지 루프
    MSG Message;
    while (GetMessage(&Message, 0, 0, 0))//응용 큐에서 메시지를 꺼내오기
    {
        DispatchMessage(&Message);//메시지 수행(콜백 가동)
    }
}
void OnDestroy(HWND hWnd)
{
    PostQuitMessage(0);//WM_QUIT 메시지를 발급해 주세요.
    //GetMessage 함수가 얻어온 메시지가 WM_QUIT이면 FALSE 반환
}

void OnDraw(HWND hWnd, HDC hdc)
{
    list<POINT>::iterator seek = points.begin();
    list<POINT>::iterator end = points.end();
    for (; seek != end; seek++)
    {
        POINT pt = (*seek);
        Ellipse(hdc, pt.x, pt.y, pt.x + 10, pt.y + 10);
    }
}
void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    OnDraw(hWnd, ps.hdc);
    EndPaint(hWnd, &ps);
}

void OnLButtonDown(HWND hWnd, int y, int x)
{
    /*
    HDC hdc = GetDC(hWnd);
    Ellipse(hdc, x, y, x + 10, y + 10);
    ReleaseDC(hWnd, hdc);
    */
    POINT pt;
    pt.x = x;
    pt.y = y;
    points.push_back(pt);
    InvalidateRect(hWnd, 0, TRUE);
}

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_LBUTTONDOWN: OnLButtonDown(hWnd, HIWORD(lParam), LOWORD(lParam)); return 0;
    case WM_PAINT: OnPaint(hWnd); return 0;
    case WM_DESTROY: OnDestroy(hWnd); return 0;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}