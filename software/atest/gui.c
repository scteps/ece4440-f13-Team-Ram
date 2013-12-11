#include "terasic_includes.h"
#include "gui.h"
#include "vip_fr.h"
#include "multi_touch.h"
#include "simple_graphics.h"
#include "geometry.h"
#include "gesture.h"
#include "sensor.h"

extern const struct bmp_struct gesture_bmp;

#define ENALBE_TOUCH_FILTER
//#define DUAL_FRAME_BUFFER


#define FRAME_WIDTH  800
#define FRAME_HEIGHT 480
#define DOT_SIZE    6

#define FR_FRAME_0  (SDRAM_BASE)
#define FR_FRAME_1  (SDRAM_BASE + FRAME_WIDTH*FRAME_HEIGHT*4)


// Since we are only using FR_FRAME_1, can use the space from frame0.
#define DATA_START 	(SDRAM_BASE)

// Overall background color
#define BG_COLOR                       0x474747

// Title Bar Placement
#define VERT_LENGTH_TITLE_BAR          51
#define BG_COLOR_TITLE_BAR             0xFFFFFF
#define COLOR_TITLE_TEXT               0xa7a7a7
#define OFFSET_VERT_TITLE_TEXT         10
#define OFFSET_HORIZ_TITLE_TEXT        250
                                       
// Button Placement                    
#define BTN_OFFSET_VERT_OPTIONS        440
#define BTN_OFFSET_HORIZ_OPTIONS       0
#define BTN_VERT_LENGTH_OPTIONS        20
#define BTN_HORIZ_LENGTH_OPTIONS       40
#define BTN_BG_COLOR_OPTIONS           0xa7a7a7
#define BTN_TEXT_COLOR_OPTIONS         0xFFFFFF
#define BTN_OFFSET_VERT_TEXT_OPTIONS   450
#define BTN_OFFSET_HORIZ_TEXT_OPTIONS  10 

// Graph Placement
#define AXIS_COLOR                     0xa7a7a7
#define PLOT_COLOR                     0x2c64c8
#define GRAPH_BOT_VERT_OFFSET          300
#define GRAPH_BOT_HORIZ_OFFSET         20
#define GRAPH_VERT_LENGTH              150
#define GRAPH_HORIZ_LENGTH             200

// Info placement
#define LABEL_OFFSET_VERT              150
#define LABEL_OFFSET_HORIZ             450
#define STAT_OFFSET_VERT               150
#define STAT_OFFSET_HORIZ              700
#define VERT_SPACING_INFO              40
#define COLOR_INFO_TEXT                0xa7a7a7

// Option Menu Layout
#define OFFSET_VERT_MENU_OPTION        150
#define OFFSET_HORIZ_MENU_OPTION       250
#define VERT_LENGTH_MENU_OPTION        270
#define HORIZ_LENGTH_MENU_OPTION       250
#define TEXT_COLOR_OPTION              0xa7a7a7
#define BG_COLOR_MENU_OPTION           0x000000
#define NUM_OPTIONS                    5
#define REL_HORIZ_OFFSET_OPTION_HEADER 20
#define REL_VERT_OFFSET_OPTION_HEADER  20
// Note, these offsets will be from the SW corner of the option menu.
#define REL_HORIZ_OFFSET_BUTTON_OK     10
#define REL_VERT_OFFSET_BUTTON_OK     -25
#define BTN_BG_COLOR_OK                0xa7a7a7
#define BTN_TEXT_COLOR_OK              0xFFFFFF
#define BTN_VERT_LENGTH_OK             20
#define BTN_HORIZ_LENGTH_OK            40
#define BTN_OFFSET_VERT_TEXT_OK        -25
#define BTN_OFFSET_HORIZ_TEXT_OK       10

// Test values for the graph
const int arr_lengths = 9;
const int xdata[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
const int ydata[] = {10, 80, 160, 50, 90, 120, 33, 55, 300};
int res_opts_count = 3;
int wind_opts_count = 3;
#define MAX_VALUE					   20
unsigned int data[MAX_VALUE];


int get_max(const int* arr, int arr_length)
{
  int i;
  int max = arr[0];
  for(i = 1; i < arr_length; ++i)
  {
    if(arr[i] >= max)
    {
      max = arr[i];
    }
  }
  return max;
}

float get_scale_factor(int abs_dim, int max_val)
{
  return abs_dim / (float)max_val;
}

void plot(int x_offset, const int* x_data, float scale_factor_x, int y_offset,
    const int* y_data, float scale_factor_y, int values, int color,  alt_video_display* display  )
{
  int i;
  // Plot the points
  for(i = 1; i < values; ++i)
  {
//    point(x_offset + x_data[i] * scale_factor_x,
//        y_offset + y_data[i] * scale_factor_y);
    vid_draw_line(x_offset + (int)(x_data[i-1] * scale_factor_x),
        y_offset - (int)(y_data[i-1] * scale_factor_y),
        x_offset + (int)(x_data[i] * scale_factor_x),
        y_offset - (int)(y_data[i] * scale_factor_y),
        1,
        color,
        display);
  }
}

// Values is the max of the array

void sliding_plot(int x_offset, const int* x_data, float scale_factor_x, int y_offset,
    const int* y_data, float scale_factor_y, int values, int color,  alt_video_display* display) {
	int i;
//	int samples = samples_in_graph;
//	int start = some_offset;
//	for(i = 0; i < samples; ++i) {
//		int curr_index;
//		int curr_index_prev;
//		vid_draw_line(x_offset + (int)(x_data[curr_index_prev] * scale_factor_x),
//		        y_offset - (int)(y_data[curr_index_prev] * scale_factor_y),
//		        x_offset + (int)(x_data[curr_index] * scale_factor_x),
//		        y_offset - (int)(y_data[curr_index] * scale_factor_y),
//		        1,
//		        color,
//		        display);
//	}

}

void draw_options(VIP_FRAME_READER *pReader, RECT* ok_button, RECT * res_opt_buttons, RECT * wind_opt_buttons) {
	vid_draw_box(OFFSET_HORIZ_MENU_OPTION,
			OFFSET_VERT_MENU_OPTION,
			OFFSET_HORIZ_MENU_OPTION + HORIZ_LENGTH_MENU_OPTION,
			OFFSET_VERT_MENU_OPTION + VERT_LENGTH_MENU_OPTION,
			BG_COLOR_MENU_OPTION, 1, pReader);

	vid_print_string_alpha(OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_OPTION_HEADER,
			OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER,
			TEXT_COLOR_OPTION,
			BG_COLOR_MENU_OPTION,
			tahomabold_20, pReader, "Options");

	// Format will be:

	// TODO Make sure the max array size does not overflow to FRAME

	// Resolution:
	// 0.5, 1, 5

	// Window Time:
	// 10, 60, 300

	int resolution_header_vert_offset = 20;
	// Draw resolution header
	vid_print_string_alpha(OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_OPTION_HEADER,
				OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + resolution_header_vert_offset,
				TEXT_COLOR_OPTION,
				BG_COLOR_MENU_OPTION,
				tahomabold_20, pReader, "Resolution Options");

	// Draw res options
	int resolution_options_vert_offset = 40;
	int resolution_options_horiz_offsets = 10;
	const int res_opts[] = {500, 1000, 5000};
	int i;
	char float_digits[] = "1.0";
	for(i = 0; i < res_opts_count; ++i) {
		sprintf(float_digits, "%f", res_opts[i]/1000.0);
		vid_print_string_alpha(OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_OPTION_HEADER + i * resolution_options_horiz_offsets,
						OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + resolution_options_vert_offset,
						TEXT_COLOR_OPTION,
						BG_COLOR_MENU_OPTION,
						tahomabold_20, pReader, float_digits);

		// Set res options hit area
		// Using VERT length of OK Button for now.
		RectSet(&(res_opt_buttons[i]),
			    		OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_BUTTON_OK + i * BTN_HORIZ_LENGTH_OK,
			    		OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_BUTTON_OK + i * BTN_HORIZ_LENGTH_OK + BTN_HORIZ_LENGTH_OK,
			    		OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + resolution_options_vert_offset,
			    		OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + resolution_options_vert_offset + BTN_VERT_LENGTH_OK);

	}
	// Draw Window Header
	int window_header_vert_offset = 60;
	int window_opts_vert_offset = 80;
	vid_print_string_alpha(OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_OPTION_HEADER,
					OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + window_header_vert_offset,
					TEXT_COLOR_OPTION,
					BG_COLOR_MENU_OPTION,
					tahomabold_20, pReader, "Window Options");
	// Use the same vert and horiz offsets as from resolution
	const int * wind_opts = {10, 60, 300};
	char digits[] = "100";
	for(i = 0; i < wind_opts_count; ++i) {
		sprintf(digits, "%d", wind_opts[i]);
		vid_print_string_alpha(OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_OPTION_HEADER + i * resolution_options_horiz_offsets,
								OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + window_opts_vert_offset,
								TEXT_COLOR_OPTION,
								BG_COLOR_MENU_OPTION,
								tahomabold_20, pReader, digits);

		RectSet(&(wind_opt_buttons[i]),
					    		OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_BUTTON_OK + i * BTN_HORIZ_LENGTH_OK,
					    		OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_BUTTON_OK + i * BTN_HORIZ_LENGTH_OK + BTN_HORIZ_LENGTH_OK,
					    		OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + window_opts_vert_offset,
					    		OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_OPTION_HEADER + window_opts_vert_offset + BTN_VERT_LENGTH_OK);

	}


	// Set button hit area
	RectSet(ok_button,
	    		OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_BUTTON_OK,
	    		OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_BUTTON_OK + BTN_HORIZ_LENGTH_OK,
	    		OFFSET_VERT_MENU_OPTION + VERT_LENGTH_MENU_OPTION + REL_VERT_OFFSET_BUTTON_OK,
	    		OFFSET_VERT_MENU_OPTION + VERT_LENGTH_MENU_OPTION + REL_VERT_OFFSET_BUTTON_OK + BTN_VERT_LENGTH_OK);

    // Draw the button
    vid_draw_box(OFFSET_HORIZ_MENU_OPTION + REL_HORIZ_OFFSET_BUTTON_OK,
    		OFFSET_VERT_MENU_OPTION + REL_VERT_OFFSET_BUTTON_OK,
    		BTN_HORIZ_LENGTH_OK,
    		BTN_VERT_LENGTH_OK,
    		BTN_BG_COLOR_OK,
    		1, pReader);

    vid_print_string_alpha(OFFSET_HORIZ_MENU_OPTION + BTN_OFFSET_HORIZ_TEXT_OK,
    		OFFSET_VERT_MENU_OPTION + VERT_LENGTH_MENU_OPTION + BTN_OFFSET_VERT_TEXT_OK,
    		BTN_TEXT_COLOR_OK,
    		BTN_BG_COLOR_OK,
    		tahomabold_20, pReader, "OK");

}


int GUI_CheckButton(POINT *pt, RECT * rc_button){

    if(IsPtInRect(pt, rc_button))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



void GUI_DeskDraw(VIP_FRAME_READER *pReader, RECT* rc_button){
    RECT rc;

    const char * OPTIONS[NUM_OPTIONS];
       OPTIONS[0] = "Battery Level";
       OPTIONS[1] = "Power from Battery";
       OPTIONS[2] = "Panel Voltage";
       OPTIONS[3] = "Charge State";
       OPTIONS[4] = "Battery Time Left";

       const int * STATS[NUM_OPTIONS];
       STATS[0] = 1;
       STATS[1] = 33;
       STATS[2] = 2;
       STATS[3] = 54;
       STATS[4] = 100;
    

    // Draw the background
    vid_draw_box(0, 0, FRAME_WIDTH, FRAME_HEIGHT, BG_COLOR, 1, pReader);

    // Draw the Title Bar
    vid_draw_box(0, 0, FRAME_WIDTH, VERT_LENGTH_TITLE_BAR, BG_COLOR_TITLE_BAR, 1, pReader);
    vid_print_string_alpha(OFFSET_HORIZ_TITLE_TEXT,
    		OFFSET_VERT_TITLE_TEXT,
    		COLOR_TITLE_TEXT,
    		BG_COLOR_TITLE_BAR,
    		tahomabold_20, pReader, "Solar Car Status Screen");
    
    // Draw the button
    vid_draw_box(BTN_OFFSET_HORIZ_OPTIONS,
    		BTN_OFFSET_VERT_OPTIONS,
    		BTN_HORIZ_LENGTH_OPTIONS,
    		BTN_VERT_LENGTH_OPTIONS,
    		BTN_BG_COLOR_OPTIONS,
    		1, pReader);

    vid_print_string_alpha(BTN_OFFSET_HORIZ_TEXT_OPTIONS,
    		BTN_OFFSET_VERT_TEXT_OPTIONS,
    		BTN_TEXT_COLOR_OPTIONS,
    		BTN_BG_COLOR_OPTIONS,
    		tahomabold_20, pReader, "Options");
    

    
    // Draw the info
    int i;
    for(i = 0; i < NUM_OPTIONS; ++i)
    {
        vid_print_string_alpha(LABEL_OFFSET_HORIZ,
        		LABEL_OFFSET_VERT + (i * VERT_SPACING_INFO),
        		COLOR_INFO_TEXT, BG_COLOR, tahomabold_20, pReader, OPTIONS[i]);
    }

    // Draw the stats
    // TODO Have to cast the int into a string correctly
    char digits[] = "00";

    for(i = 0; i < NUM_OPTIONS; ++i)
    {
        sprintf(digits, "%d", STATS[i]);
        vid_print_string_alpha(STAT_OFFSET_HORIZ,
        		STAT_OFFSET_VERT + (i * VERT_SPACING_INFO),
        		COLOR_INFO_TEXT, BG_COLOR, tahomabold_20, pReader, digits);
    }

    // Set button rect dims

    RectSet(rc_button,
    		BTN_OFFSET_HORIZ_OPTIONS,
    		BTN_OFFSET_HORIZ_OPTIONS + BTN_HORIZ_LENGTH_OPTIONS,
    		BTN_OFFSET_VERT_OPTIONS,
    		BTN_OFFSET_VERT_OPTIONS + BTN_VERT_LENGTH_OPTIONS);

    // Draw the axes
    // X-AXIS
    vid_draw_line(GRAPH_BOT_HORIZ_OFFSET,
    		GRAPH_BOT_VERT_OFFSET,
    		GRAPH_BOT_HORIZ_OFFSET + GRAPH_HORIZ_LENGTH,
    		GRAPH_BOT_VERT_OFFSET, 1, AXIS_COLOR, pReader);
    // Y-AXIS
    vid_draw_line(GRAPH_BOT_HORIZ_OFFSET,
    		GRAPH_BOT_VERT_OFFSET,
    		GRAPH_BOT_HORIZ_OFFSET,
    		GRAPH_BOT_VERT_OFFSET - GRAPH_VERT_LENGTH,
    		1, AXIS_COLOR, pReader);


    // Draw the graph
	int max_x = get_max(xdata, arr_lengths);
	int max_y = get_max(ydata, arr_lengths);
	float scale_factor_x = get_scale_factor(GRAPH_HORIZ_LENGTH, max_x);
	float scale_factor_y = get_scale_factor(GRAPH_VERT_LENGTH, max_y);

	plot(GRAPH_BOT_HORIZ_OFFSET, xdata, scale_factor_x,
			GRAPH_BOT_VERT_OFFSET, ydata, scale_factor_y,
			arr_lengths, PLOT_COLOR, pReader);

}

bool IsContinuedPoint(POINT *ptPre, POINT *ptNew){
    bool bYes = TRUE;
    const int nMax = 50;
    if (abs(ptPre->x - ptNew->x) > nMax)
        bYes = FALSE;
    else if (abs(ptPre->y - ptNew->y) > nMax)
        bYes = FALSE;
        
    return bYes;        
        
}

void GUI_ShowGesture(VIP_FRAME_READER *pReader, POINT *ptDraw, alt_u8 GestureId ){
    // show bitmap
    int nIndex = -1, x, y;
    const int BmpW = 60;
    const int BmpH = 60;
    alt_u8 *pDes, *pSrc, *pDesStart;
    
    // find gesture bitmap id
    switch(GestureId){
        case MTC_ST_NORTH:  nIndex = 0; break;
        case MTC_ST_SOUTH:  nIndex = 1; break;
        case MTC_ST_EAST:   nIndex = 2; break;
        case MTC_ST_WEST:   nIndex = 3; break;
        case MTC_ST_N_WEST: nIndex = 4; break;
        case MTC_ST_N_EAST: nIndex = 5; break;
        case MTC_ST_S_WEST: nIndex = 6; break;
        case MTC_ST_S_EAST: nIndex = 7; break;
        
        case MTC_ST_CLICK:       nIndex = 8; break;
        case MTC_ST_DOUBLECLICK: nIndex = 9; break;
     
        case MTC_1_POINT:        nIndex = 10; break;
     
        case MTC_MT_NORTH:        nIndex = 11; break;
        case MTC_MT_SOUTH:        nIndex = 12; break;
        case MTC_MT_EAST:         nIndex = 13; break;
        case MTC_MT_WEST:         nIndex = 14; break;
        case MTC_MT_S_WEST:       nIndex = 17; break;
        case MTC_MT_N_EAST:       nIndex = 16; break;
        case MTC_MT_N_WEST:       nIndex = 15; break;
        case MTC_MT_S_EAST:       nIndex = 18; break;
        
        case MTC_MT_CLICK:        nIndex = 19; break;
        case MTC_2_POINT:         nIndex = 21; break;

        case MTC_ST_ROTATE_CW:    nIndex = 22; break;
        case MTC_ST_ROTATE_CCW:   nIndex = 23; break;

        
        case MTC_ZOOM_IN:         nIndex = 24; break;
        case MTC_ZOOM_OUT:        nIndex = 25; break;
    }
    
    if (nIndex  == -1)
        return;
    
    pSrc = (alt_u8 *)gesture_bmp.pixel_data + nIndex * BmpW * BmpH * 3;
    
    pDesStart = (alt_u8 *)VIPFR_GetDrawFrame(pReader) + (ptDraw->y*pReader->width*pReader->bytes_per_pixel) + (ptDraw->x*pReader->bytes_per_pixel);
    
    for(y=0;y<BmpH;y++){
        pDes = pDesStart; 
        for(x=0;x<BmpW;x++){
            memcpy(pDes, pSrc, 3);
            pDes += 4;
            pSrc += 3;
        }
        pDesStart += pReader->width*pReader->bytes_per_pixel; 
    }
} 

void GUI_TraceGesture(VIP_FRAME_READER *pReader, POINT *ptDraw, alt_u8 GestureId ){
    if (GestureId == MTC_2_POINT)
        return;
    if (GestureId == MTC_1_POINT)
        return;
    GUI_ShowGesture(pReader, ptDraw, GestureId);
}

//void GUI_ClearPaintArea(VIP_FRAME_READER *pReader, DESK_INFO *pDeskInfo){
//    RECT rc;
//
//    return;
//}

void GUI(MTC_INFO *pTouch){
    // video
//    DESK_INFO DeskInfo;
	int option_selected = 0;
    VIP_FRAME_READER *pReader;
    int X1, Y1, X2, Y2;
    POINT Pt1, Pt2, ptGesture;
    alt_u8 Event, TouchNum, LedMask = 0x01;
    const int nDotSize = DOT_SIZE;
    RECT rcTouch;
    // Set the rectangle for the button
    RECT rc_button;
    RECT ok_button;
    RECT * res_opt_buttons;
    RECT * wind_opt_buttons;
    int ColorPen0, ColorPen1, ButtonId, ButtonId2;
    bool UpdatePalette;
    int * data = (int *) DATA_START;
    int curr_res_opt_selected = -1;
    int curr_wind_opt_selected = -1;
#ifdef ENALBE_TOUCH_FILTER    
    POINT LastPt1, LastPt2;
    alt_u32 LastTimePt1=0,LastTimePt2=0; 
    const alt_u32 ContinuedTime = alt_ticks_per_second()/50;
#endif    
    
    /////////////////////////////////////////////
    // frame reader
#ifdef DUAL_FRAME_BUFFER
    pReader =  VIPFR_Init(ALT_VIP_VFR_0_BASE, (void *)FR_FRAME_0, (void *)FR_FRAME_1, FRAME_WIDTH, FRAME_HEIGHT);
#else    
    pReader =  VIPFR_Init(ALT_VIP_VFR_0_BASE, (void *)FR_FRAME_1, (void *)FR_FRAME_1, FRAME_WIDTH, FRAME_HEIGHT);
#endif // DUAL_FRAME_BUFFER    
    VIPFR_Go(pReader, TRUE);
    
    
    // clean screen
    vid_clean_screen(pReader, BLACK_24);
    
   
    //GUI_DeskInit(pReader, &DeskInfo);
    GUI_DeskDraw(pReader, &rc_button);
    
    VIPFR_ActiveDrawFrame(pReader);
    
//    RectCopy(&rcTouch, &DeskInfo.rcPaint);
//    RectInflate(&rcTouch, -nDotSize-2, -nDotSize-2);

    
    while(1){
		// touch
		if (MTC_GetStatus(pTouch, &Event, &TouchNum, &X1, &Y1, &X2, &Y2)){
			PtSet(&Pt1, X1, Y1);
			if(!option_selected) {
				if(TouchNum == 1 && GUI_CheckButton(&Pt1, &rc_button)) {
					printf("Options.");
					option_selected = 1;
					draw_options(pReader, &ok_button, res_opt_buttons, wind_opt_buttons);
				}
			}
			else {

				// Check and set the resolution and window options
				int i;
				for(i = 0; i < res_opts_count; ++i) {
					if(TouchNum == 1 && GUI_CheckButton(&Pt1, &(res_opt_buttons[i]))){
						curr_res_opt_selected = i;
					}
				}

				for(i = 0; i < wind_opts_count; ++i) {
					if(TouchNum == 1 && GUI_CheckButton(&Pt1, &(wind_opt_buttons[i]))){
						curr_wind_opt_selected = i;
					}
				}


				// Check for the OK button
				if(TouchNum == 1 && GUI_CheckButton(&Pt1, &ok_button)) {
					printf("OK.");
					option_selected = 0;
					printf("RES SELECTED: %d, WIND SELECTED: %d.",
							curr_res_opt_selected, curr_wind_opt_selected);
					// Change the color.
					// Reset selected options?
					GUI_DeskDraw(pReader, &rc_button);
				}
			}
    	}
    }
}


