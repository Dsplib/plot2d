#ifndef PLOT2D_H
#define PLOT2D_H
#include <windows.h>


//***********************************************************************
// CURVE STRUCTURE
typedef struct
{
	double 		*pX;	// x vector pointer
	double 		*pY;	// y vector pointer
	int 		n;		// x and y vectors length
	DWORD 		lc;		// curve color
	int	     	lw;		// curve width
	int		 	lt;		// curve type
} curve_t;





//***********************************************************************
// AXIS STRUCTURE
typedef struct
{
	// axis	
	double	  	minX;		// minimum x axis value for current plot
	double	  	maxX;		// maximum x axis value for current plot
	double	  	minY;		// minimum y axis value for current plot
	double	  	maxY;		// maximum y axis value for current plot	

	double	  	minXData;	// Global minimum x axis value for current plot
	double	  	maxXData;	// Global maximum x axis value for current plot
	double	  	minYData;	// Global minimum y axis value for current plot
	double	  	maxYData;	// Global maximum y axis value for current plot	
	
	double		kX;			// x axis scale
	double		kY;			// y axis scale

	// Grid description
	double	   *pGridX;		// x grid values vector pointer 
	int			nGridX; 	// x grid count
	double	   *pGridY;		// y grid values vector pointer
	int			nGridY;		// y grid count
	int 		nSubGrid;
	DWORD		gridColor;
	DWORD		subGridColor;
	
	// border margins in pixels
	RECT 		margin;	// border top margin

	// plot color
	DWORD		bgColor;
	DWORD		borderColor;
	int			borderWidth;

} axis_t;





//*******************************************************************************************
// PLOTDATA STRUCTURE
typedef struct
{
	// curves description
	curve_t 	*pCurve;		// curves array
	int      	nCurve;			// curve count
	
	axis_t		axis;
	
	HDC		    hDC;			// compatible DC
	HBITMAP     hBMP;			// compatible BMP				
	//LOGFONT     lf;
	//HFONT       hf;
} plot_t;



//*******************************************************************************************
// PAINT PLOT
void plotInit (plot_t *pd,  RECT rect);
void plotPaint(plot_t *pd,  RECT rect);

#endif