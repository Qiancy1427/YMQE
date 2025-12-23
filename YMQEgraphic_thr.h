#ifndef YMQEgraphic_thr
#define YMQEgraphic_thr

#include"YMQEhead_func.h"


//windows api setting
#define windowwidth 1900
#define windowheight 1000
HWND main_hwnd;//唯一指定的窗口句柄 
RECT rectt;//整个窗口的矩形 
BYTE *pBuf=new BYTE[windowwidth*windowheight*3];
PAINTSTRUCT ps;
HDC hdc,renderDC;//双缓冲DC 
HBITMAP renderBmp;
BITMAPINFO bmpinfo;//位图信息


void setpixel(int x, int y,BYTE r,BYTE g,BYTE b){
	if(x<0) return;
	if(x>=windowwidth) return;
	if(y<0) return;
	if(y>=windowheight) return;
	
	
	int k=(y*windowwidth+x)*3;
	pBuf[k++]=b;
	pBuf[k++]=g;
	pBuf[k++]=r;
	
	return;
}

void render(){
	//窗口DC声明 
	InvalidateRect(main_hwnd,&rectt,true);//将整个窗口添加到更新区域 
    hdc = BeginPaint(main_hwnd, &ps);//开始绘制，并调用更新区句柄
    //双缓冲DC声明
	renderDC=CreateCompatibleDC(hdc);
    renderBmp = CreateCompatibleBitmap(hdc, windowwidth, windowheight);
    SelectObject(renderDC, renderBmp);
	
	// All painting occurs here, between BeginPaint and EndPaint.
	//beginpaint
	
//	for(int i = 0; i < 10000; i++){	//fps:我感觉要出逝 
//		settri_quick(pBuf, Vector{100.0, 100.0, 0.0, 0.0}, Vector{100.0, 200.0, 0.0, 0.0}, Vector{200.0, 100.0, 0.0, 0.0}, 255, 255, 255);
//	}

	/*for(int i=0;i<windowwidth*windowheight*3;i++){
		pBuf[i]=0;
	}*/
	
	
	for(int i=0;i<windowwidth;i++){
		setpixel(i,0,255,255,255);
		
		
	} 
	
	
	//EndPaint
	
	//全图处理完毕读出到renderDC
	SetDIBits(renderDC,renderBmp,0,bmpinfo.bmiHeader.biHeight,pBuf,(BITMAPINFO*)&bmpinfo,0);
	BitBlt(hdc, 0, 0, windowwidth, windowheight, renderDC, 0, 0, SRCCOPY);//缓冲区显示
    EndPaint(main_hwnd, &ps);//结束绘制，释放更新区句柄
    DeleteDC(renderDC);//shel漏抄释放内存当了一年傻逼2025.12.22才发现 
    DeleteObject(renderBmp);
    
	return;
}


DWORD WINAPI graphicLoop(LPVOID lpParamter){//渲染主循环
    while(1){
		render();//渲染
		
	}
    return 0L;
}


#endif
