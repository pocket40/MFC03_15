//Windows API
//첫 번째 응용
//int main() 콘솔 응용 진입점 함수
#include <Windows.h>//Windows API 관련 형식과 기능을 제공
//WinMain - Windows 응용 진입점 함수
INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
    MessageBox(0, TEXT("ABC"), TEXT("BCD"), MB_OKCANCEL);
    return 0;
}
