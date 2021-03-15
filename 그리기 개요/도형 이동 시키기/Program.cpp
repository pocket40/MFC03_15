//Windows API
//방향 키에 따라 도형을 이동 시키기
//    키를 눌렀을 때 발생하는 윈도우 메시지? WM_KEYDOWN
//    화면을 다시 그리기 위한 윈우 메시지? WM_PAINT

#include <Windows.h>
#define MY_DEF_STYLE CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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
int x = 0, y = 0;
void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    Rectangle(ps.hdc, x, y, x + 20, y + 20);
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
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_KEYDOWN: OnKeyDown(hWnd, LOWORD(wParam)); return 0;
    case WM_PAINT: OnPaint(hWnd); return 0;
    case WM_DESTROY: OnDestroy(hWnd); return 0;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}