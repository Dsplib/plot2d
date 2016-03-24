#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "plot2d.h"


void plotInit (plot_t *pd,  RECT rect)
{
	
	pd->axis.minXData = pd->axis.minYData = 0.0;
	pd->axis.maxXData = pd->axis.maxYData = 1.0;
	pd->axis.minX = pd->axis.minY = 0.0;
	pd->axis.maxX = pd->axis.maxY = 1.0;
	pd->axis.margin.top = 10;
	pd->axis.margin.left = 60;
	pd->axis.margin.right = 10;
	pd->axis.margin.bottom = 40;
	pd->axis.bgColor     = 0x00FFFFFF;
	pd->axis.borderColor = 0x000000FF;
	pd->axis.borderWidth = 1;
	
}




void plotPaint(plot_t *pd,  RECT rect)
{
	//int k;
	HBRUSH hBrush = CreateSolidBrush((COLORREF)pd->axis.bgColor);
	HPEN hPen = CreatePen(PS_SOLID, 1, (COLORREF) pd->axis.borderColor);
	


	SelectObject(pd->hDC, hBrush);
	FillRect(pd->hDC, &rect, hBrush);
	
	SelectObject(pd->hDC, hPen);

	MoveToEx(pd->hDC, pd->axis.margin.left, pd->axis.margin.top, NULL);
	LineTo(pd->hDC, rect.right, rect.bottom);

	DeleteObject(hPen);
	DeleteObject(hBrush);
	
	
}