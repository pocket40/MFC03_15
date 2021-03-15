//Windows API
/*상,하,좌,우 키에 따라 도형을 이동시켜라.
* 최초 도형은 사각형이다. (펜은 빨강, 브러쉬는 파랑)
* 왼쪽 마우스를 클릭하면 펜과 브러쉬가 바뀐다.(...->빨->녹->파->빨->녹->파...)
* 오른쪽 마우스를 클릭하면 도형이 바뀐다.(사각형->원->사각형->원->...)
관리할 데이터: 위치, 도형, 스타일(펜,브러쉬)
처리할 메시지: WM_LBUTTONDOWN,
                         WM_RBUTTONDOWN,
                         WM_KEYDOWN,
                         WM_PAINT
*/


#include <Windows.h>
#define MY_DEF_STYLE CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int x = 0, y = 0;
bool isrect = true;
int pb_style = 0;//0(빨,파), 1(녹,빨), 2(파,녹)

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

void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    HPEN hpens[3];
    hpens[0] = CreatePen(PS_SOLID, 1, RGB(0xFF, 0, 0));
    hpens[1] = CreatePen(PS_SOLID, 1, RGB(0, 0xFF, 0));
    hpens[2] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0xFF));

    HBRUSH hbrushes[3];
    hbrushes[0] = CreateSolidBrush(RGB(0, 0, 0xFF));
    hbrushes[1] = CreateSolidBrush(RGB(0xFF, 0, 0));
    hbrushes[2] = CreateSolidBrush(RGB(0, 0xFF, 0));

    HDC hdc = ps.hdc;
    HPEN open = (HPEN)SelectObject(hdc, hpens[pb_style]);
    HBRUSH obrush = (HBRUSH)SelectObject(hdc, hbrushes[pb_style]);
    if (isrect)
    {
        Rectangle(hdc, x, y, x + 20, y + 20);
    }
    else
    {
        Ellipse(hdc, x, y, x + 20, y + 20);
    }
    SelectObject(hdc, open);
    SelectObject(hdc, obrush);
    DeleteObject(hpens[0]);
    DeleteObject(hpens[1]);
    DeleteObject(hpens[2]);
    DeleteObject(hbrushes[0]);
    DeleteObject(hbrushes[1]);
    DeleteObject(hbrushes[2]);
    EndPaint(hWnd, &ps);
}

void OnKeyDown(HWND hWnd, int key)
{
    switch (key)
    {
    case VK_LEFT: x--; break;
    case VK_RIGHT: x++; break;
    case VK_UP: y--; break;
    case VK_DOWN: y++; break;
    default: return;
    }
    InvalidateRect(hWnd, 0, TRUE);
}
void OnLButtonDown(HWND hWnd)
{
    isrect ^= true;
    InvalidateRect(hWnd, 0, TRUE);
}
void OnRButtonDown(HWND hWnd)
{
    pb_style = (pb_style + 1) % 3;
    InvalidateRect(hWnd, 0, TRUE);
}
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_KEYDOWN: OnKeyDown(hWnd, LOWORD(wParam)); return 0;
    case WM_LBUTTONDOWN: OnLButtonDown(hWnd); return 0;
    case WM_RBUTTONDOWN: OnRButtonDown(hWnd); return 0;
    case WM_PAINT: OnPaint(hWnd); return 0;
    case WM_DESTROY: OnDestroy(hWnd); return 0;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}