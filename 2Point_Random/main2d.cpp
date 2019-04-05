/* Window with two points randowly on the screen */
#include"Point2D.h"
#include<Windows.h>

bool Running = true;

LRESULT CALLBACK Win32CallBack(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;

    switch (Message)
    {
    case WM_SIZE:
    {

    }break;
    case WM_CLOSE:
    {
        Running = false;

    }break;
    case WM_PAINT:
    {

        PAINTSTRUCT Paint;
        HDC DeviceContext = BeginPaint(Window, &Paint);
        int X = Paint.rcPaint.left;
        int Y = Paint.rcPaint.top;
        int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        int Width = Paint.rcPaint.right - Paint.rcPaint.left;
        static DWORD Operation = WHITENESS;

        PatBlt(DeviceContext, X, Y, Height, Width, Operation);

        if (Operation == WHITENESS)
        {
            Operation = BLACKNESS;
        }
        else
        {
            Operation = WHITENESS;
        }
        EndPaint(Window, &Paint);

    }break;

    default:
    {
        Result = DefWindowProc(Window, Message, WParam, LParam);
    }break;

    }

    return(Result);
}

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPTSTR CmdLine, int CmdShow) //Entry Point WinApi
{
    // Register the window class.
    WNDCLASS WindowClass = {};

    WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WindowClass.lpfnWndProc = Win32CallBack;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "2Point Random";


    if (RegisterClass(&WindowClass)) //window class for subsequent use in calls Create Window
    {
        HWND Window = CreateWindowEx(
            0,                              // Optional window styles.
            WindowClass.lpszClassName,      // Window class
            "2 Point Random",               // Window text
            WS_OVERLAPPEDWINDOW,            // Window style
            CW_USEDEFAULT,                  // Size and position
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,                           // Parent window    
            NULL,                           // Menu
            Instance,                       // Instance handle
            NULL                            // Additional application data
        );

        if (Window)
        {
            HDC DeviceContext = GetDC(Window);

            while (Running) //will receive thousands of messages while it runs
            {

                MSG Message;
                while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))  //PeekMessage Dispatches incoming sent messages, checks the thread message queue for a posted message, and retrieves the message (if any exist).
                {
                    if (Message.message == WM_QUIT)
                    {
                        Running = false;
                    }
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }


            }
        }
    }


    return 0;

}