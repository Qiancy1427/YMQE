#ifndef YMQEmain_thr
#define YMQEmain_thr

#include"YMQEhead_func.h"
#include"YMQEinput_thr.h"
#include"YMQEgraphic_thr.h"
#include"YMQEsound_thr.h"


void init(){
	
	//设置整个窗口的矩形 
	rectt.top=0;
	rectt.bottom=windowheight;
	rectt.left=0;
	rectt.right=windowwidth;
	
	//创建并填写位图信息 
	ZeroMemory(&bmpinfo,sizeof(BITMAPINFO));
	bmpinfo.bmiHeader.biBitCount=24;      //每个像素多少位，也可直接写24(RGB)或者32(RGBA)
	bmpinfo.bmiHeader.biCompression=0;
	bmpinfo.bmiHeader.biHeight=windowheight;
	bmpinfo.bmiHeader.biPlanes=1;
	bmpinfo.bmiHeader.biSizeImage=0;
	bmpinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth=windowwidth;
	
	HANDLE hThreadinput = CreateThread(NULL, 0, inputLoop, NULL, 0, NULL);//将inputloop塞进线程并推入cpu栈 
    CloseHandle(hThreadinput);//释放线程
    HANDLE hThreadgraphic = CreateThread(NULL, 0, graphicLoop, NULL, 0, NULL);//将graphicloop塞进线程并推入cpu栈 
    CloseHandle(hThreadgraphic);//释放线程 
    HANDLE hThreadsound = CreateThread(NULL, 0, soundLoop, NULL, 0, NULL);//将soundloop塞进线程并推入cpu栈 
    CloseHandle(hThreadsound);//释放线程
	
	return;
}

void instances_manage(){
	
	
	return;
} 

//entries begin

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//傀儡callback 
{	
    switch (uMsg)
    {
    case WM_DESTROY:
    	
        PostQuitMessage(0);//窗口还是得能关上的，windows api官方的东西就只能干这种杂鱼事了 .
    case WM_PAINT:
        {
            //啥都没有，byd windows api 我才不在这写东西   		
        }
        return 0;

    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)//傀儡winapi 
{
	
    // Register the window class
    const wchar_t CLASS_NAME[]  = L"YMQEwindow";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        L"YMQE",    					// Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        0, 0, windowwidth, windowheight+39,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }
    main_hwnd=hwnd;//设置唯一指定窗口 
    
    init();//初始化 
    
    

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    // Run你妈啊 

    MSG msg = { };
    while(1){
    	instances_manage();
    	
    	if(GetMessage(&msg, NULL, 0, 0) > 0){
			TranslateMessage(&msg);
		    DispatchMessage(&msg);
		    //也是啥都没有，只是为了让这个线程能活着关掉窗口 
		}else{
			break;
		}
	}
    
    return 0;
}



#endif
