//Windows API
//ù ��° ����
//int main() �ܼ� ���� ������ �Լ�
#include <Windows.h>//Windows API ���� ���İ� ����� ����
//WinMain - Windows ���� ������ �Լ�
INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
    MessageBox(0, TEXT("ABC"), TEXT("BCD"), MB_OKCANCEL);
    return 0;
}
