//Windows API
//���� Ű�� ���� ������ �̵� ��Ű��
//    Ű�� ������ �� �߻��ϴ� ������ �޽���? WM_KEYDOWN
//    ȭ���� �ٽ� �׸��� ���� ���� �޽���? WM_PAINT

#include <Windows.h>
#define MY_DEF_STYLE CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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