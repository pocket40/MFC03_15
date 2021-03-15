//Windows API
/*
* WM_PAINT���� �׸���� �ٸ� ������ �׸����� ������
* 1. WM_PAINT�� ��ȿȭ ������ ���ܼ� �ٽ� �׷��� �� �� �߻�
*      BeginPaint�� DC �߱� EndPaint�� DC����
* 2. �� ��
*      GetDC�� �߱� ReleaseDC�� ����
* �ǽ� �ó�����
* ���콺 ���� Ŭ���ϴ� ������ ���� ���� �׸��ÿ�.
* (â�� �ּ�ȭ���״ٰ� �ٽ� �ִ�ȭ�Ͽ��� �׷ȴ� ������ �����ϰ� �Ϸ���?)
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
    //������ Ŭ���� �Ӽ� ����
    WNDCLASS wndclass = { 0 };
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hInstance = hIns;//GetModuleHandle(0);
    wndclass.hIcon = LoadIcon(0, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(0, IDC_ARROW);
    wndclass.lpfnWndProc = MyWndProc;
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = TEXT("mywindow");
    wndclass.style = MY_DEF_STYLE;
    //������ Ŭ���� ���
    RegisterClass(&wndclass);

    //������ ��ü ����
    HWND hWnd = CreateWindow(TEXT("mywindow"),//Ŭ���� �̸�
        TEXT("Ÿ��Ʋ"),//Ÿ��Ʋ ��
        WS_OVERLAPPEDWINDOW,//������ ��Ÿ��
        100, 30, 700, 600,//Left, Top, Width, Height
        0, //�θ� ������ �ڵ�
        0,//�޴�
        hIns,//��� �ڵ�
        0 //WM_CREATE�� ������ ����       
    );
    //������ ��ü �ð�ȭ
    ShowWindow(hWnd, SW_SHOW);
    //�޽��� ����
    MSG Message;
    while (GetMessage(&Message, 0, 0, 0))//���� ť���� �޽����� ��������
    {
        DispatchMessage(&Message);//�޽��� ����(�ݹ� ����)
    }
}
void OnDestroy(HWND hWnd)
{
    PostQuitMessage(0);//WM_QUIT �޽����� �߱��� �ּ���.
    //GetMessage �Լ��� ���� �޽����� WM_QUIT�̸� FALSE ��ȯ
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