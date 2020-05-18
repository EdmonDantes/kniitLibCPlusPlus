#include <iostream>
//#include <windows.h>
//#include "../window/win_app.h"
//
//using namespace std;
//using KNIIT_LIB_NAMESPACE;
//
////////////////////////////////////////////////////////////////////////////
//// функция обработки сообщений
//LRESULT CALLBACK WndProc(
//        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    // выборка и обработка сообщений
//    switch (message)
//    {
//        case WM_LBUTTONUP:
//            // реакция на сообщение
//            MessageBox(hWnd, TEXT("Вы кликнули!"), TEXT("событие"), 0);
//            break;
//        case WM_DESTROY:
//            PostQuitMessage(0);  // реакция на сообщение
//            break;
//        default:
//            // все сообщения не обработанные Вами обработает сама Windows
//            return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
////////////////////////////////////////////////////////////////////////////
//// функция регистрации класса окон
//ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
//{
//    WNDCLASS wcWindowClass = {0};
//    // адрес ф-ции обработки сообщений
//    wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
//    // стиль окна
//    wcWindowClass.style = CS_HREDRAW|CS_VREDRAW;
//    // дискриптор экземпляра приложения
//    wcWindowClass.hInstance = hInst;
//    // название класса
//    wcWindowClass.lpszClassName = lpzClassName;
//    // загрузка курсора
//    wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//    // загрузка цвета окон
//    wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
//    return RegisterClass(&wcWindowClass); // регистрация класса
//}
//
//int main() {
//
//    HINSTANCE hInstance = getApplicationInstance();
//    hideConsole();
//
//    // имя будущего класса
//    LPCTSTR lpzClass = TEXT("My Window Class!");
//
//// регистрация класса
//    if (!RegMyWindowClass(hInstance, lpzClass))
//        return 1;
//
//// вычисление координат центра экрана
//    RECT screen_rect;
//    GetWindowRect(GetDesktopWindow(),&screen_rect); // разрешение экрана
//    int x = screen_rect.right / 2 - 150;
//    int y = screen_rect.bottom / 2 - 75;
//
//// создание диалогового окна
//    HWND hWnd = CreateWindow(lpzClass, TEXT("Dialog Window"),
//                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, 300, 150, NULL, NULL,
//                             hInstance, NULL);
//
//// если окно не создано, описатель будет равен 0
//    if(!hWnd) return 2;
//
//// цикл сообщений приложения
//    MSG msg = {0};    // структура сообщения
//    int iGetOk = 0;   // переменная состояния
//    while ((iGetOk = GetMessage(&msg, NULL, 0, 0 )) != 0) // цикл сообщений
//    {
//        if (iGetOk == -1) return 3;  // если GetMessage вернул ошибку - выход
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return msg.wParam;  // возвращаем код завершения программы
//}

#include "../core/string.h"
#include "../core/codecs.h"
#include <fstream>

using KNIIT_LIB_NAMESPACE;

int main() {

    setlocale(0, "Russian");

    String str(L"Hello my dear friend. Привет мой дорогой друг");
    str += Number(0x1F701);

    List<uint8_t> array = str.to(Codecs::UTF_8, true, BIG_ENDIAN);

    std::ofstream out("output.txt");
    out << array.toArray();
    out.flush();
    out.close();

    return 0;


}