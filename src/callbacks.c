#include <windows.h>
#include "callbacks.h"
#include "resource.h"
#include "plot2d.h"


// Window procedure for our main window.
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	RECT rect;
	HDC hDC;	
	PAINTSTRUCT ps;
	plot_t *pd = NULL;
	GetClientRect(hWnd, &rect);
	
	switch (msg)
	{
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
			
			pd = (plot_t*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(plot_t));
			
			plotInit (pd,   rect);
			//pd->hf = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	        //
			//GetObject(pd->hf, 1, &(pd->lf));
	        //
			//pd->lf.lfHeight = 13;
			//pd->hf = CreateFontIndirect(&(pd->lf));
	
			hDC = GetDC(hWnd);
	
			pd->hDC  = CreateCompatibleDC(hDC);
			pd->hBMP = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);			
			SelectObject(pd->hDC, pd->hBMP);
			
			//SelectObject(pd->hDC, pd->hf);
	
			
	
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)pd);
			//plotPaint(pd, rect);
	
			DeleteDC(hDC);
			
			SendMessage(hWnd, WM_PLOT, 0, 0);
	
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case ID_HELP_ABOUT:
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTDIALOG), hWnd, &AboutDialogProc);
					return 0;
			
				case ID_FILE_EXIT:
					DestroyWindow(hWnd);
					return 0;
			}
			break;
			
		case WM_ERASEBKGND:
			return 1;

	
		case WM_PAINT:
			pd = (plot_t*)GetWindowLong(hWnd, GWL_USERDATA);
			hDC = BeginPaint(hWnd, &ps);
			BitBlt(hDC, 0, 0, rect.right, rect.bottom, pd->hDC, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
			break;
			
			
		case WM_SIZE:
			pd = (plot_t*)GetWindowLong(hWnd, GWL_USERDATA);
			hDC = GetDC(hWnd);

			DeleteDC(pd->hDC);
			DeleteObject(pd->hBMP);

			pd->hDC = CreateCompatibleDC(hDC);
			pd->hBMP = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);

			SelectObject(pd->hDC, pd->hBMP);
			//SelectObject(pd->hDC, pd->hf);

			//psdWndGridCalc(pd, rect, GRID_MIN_DISTANCE);

			SetWindowLong(hWnd, GWL_USERDATA, (LONG)pd);

			DeleteDC(hDC);
			SendMessage(hWnd, WM_PLOT, 0, 0);

			break;


		case WM_SYSCOMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_HELP_ABOUT:
			{
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTDIALOG), hWnd, &AboutDialogProc);
				return 0;
			}
			}
			break;
		}	
	
		/* USER MSG */
		case WM_PLOT:
			pd = (plot_t*)GetWindowLong(hWnd, GWL_USERDATA);
			plotPaint(pd, rect);
			InvalidateRect(hWnd, &rect, 1);
		break;				
	}	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}





// Dialog procedure for our "about" dialog.
INT_PTR CALLBACK AboutDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				case IDCANCEL:
					EndDialog(hwndDlg, (INT_PTR) LOWORD(wParam));
					return (INT_PTR) TRUE;
			}
			break;
		}
		
		case WM_INITDIALOG:
			return (INT_PTR) TRUE;
	}
	
	return (INT_PTR) FALSE;
}
