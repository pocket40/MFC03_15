//Windows API
/*��,��,��,�� Ű�� ���� ������ �̵����Ѷ�.
* ���� ������ �簢���̴�. (���� ����, �귯���� �Ķ�)
* ���� ���콺�� Ŭ���ϸ� ��� �귯���� �ٲ��.(...->��->��->��->��->��->��...)
* ������ ���콺�� Ŭ���ϸ� ������ �ٲ��.(�簢��->��->�簢��->��->...)
������ ������: ��ġ, ����, ��Ÿ��(��,�귯��)
ó���� �޽���: WM_LBUTTONDOWN,
                         WM_RBUTTONDOWN,
                         WM_KEYDOWN,
                         WM_PAINT
*/


#include <Windows.h>
#define MY_DEF_STYLE CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int x = 0, y = 0;
bool isrect = true;
int pb_style = 0;//0(��,��), 1(��,��), 2(��,��)

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