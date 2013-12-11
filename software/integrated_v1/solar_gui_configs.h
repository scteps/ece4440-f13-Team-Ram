#ifndef SOLAR_GUI_CONFIGS_H_
#define SOLAR_GUI_CONFIGS_H_

// Overall background color
#define BG_COLOR                       0x474747

// Title Bar Placement
#define VERT_LENGTH_TITLE_BAR          51
#define BG_COLOR_TITLE_BAR             0x000000
#define COLOR_TITLE_TEXT               0xa7a7a7
#define OFFSET_VERT_TITLE_TEXT         10
#define OFFSET_HORIZ_TITLE_TEXT        270

// Button Placement
#define BTN_OFFSET_VERT_OPTIONS        440
#define BTN_OFFSET_HORIZ_OPTIONS       0
#define BTN_VERT_LENGTH_OPTIONS        40
#define BTN_HORIZ_LENGTH_OPTIONS       80
#define BTN_BG_COLOR_OPTIONS           0xa7a7a7
#define BTN_TEXT_COLOR_OPTIONS         0xFFFFFF
#define BTN_OFFSET_VERT_TEXT_OPTIONS   450
#define BTN_OFFSET_HORIZ_TEXT_OPTIONS  10

// Graph Placement
#define AXIS_COLOR                     0xa7a7a7
#define PLOT_COLOR                     0x2c64c8
#define GRAPH_BOT_VERT_OFFSET          300
#define GRAPH_BOT_HORIZ_OFFSET         50
#define GRAPH_VERT_LENGTH              150
#define GRAPH_HORIZ_LENGTH             200

// Graph text Placement
#define OFFSET_VERT_GRAPH_TITLE        100
#define OFFSET_HORIZ_GRAPH_TITLE       70
#define OFFSET_VERT_GRAPH_INFO         330
#define OFFSET_HORIZ_GRAPH_INFO        70

// Info placement
#define LABEL_OFFSET_VERT              150
#define LABEL_OFFSET_HORIZ             400
#define STAT_OFFSET_VERT               150
#define STAT_OFFSET_HORIZ              650
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
#define REL_VERT_OFFSET_OPTION_HEADER  10
// Note, these offsets will be from the SW corner of the option menu.
#define REL_HORIZ_OFFSET_BUTTON_OK     10
#define REL_VERT_OFFSET_BUTTON_OK     -25
#define BTN_BG_COLOR_OK                0xa7a7a7
#define BTN_TEXT_COLOR_OK              0xFFFFFF
#define BTN_VERT_LENGTH_OK             20
#define BTN_HORIZ_LENGTH_OK            40
#define BTN_OFFSET_VERT_TEXT_OK        -25
#define BTN_OFFSET_HORIZ_TEXT_OK       10

// Selected option
#define TEXT_COLOR_SELECTED            0xFFB366

// Resolution offsets
#define resolution_options_vert_offset   70
#define resolution_options_horiz_offsets 50
#define res_opt_horiz_length             50
#define res_opt_vert_length              20

// Window offsets
#define window_header_vert_offset        120
#define window_opts_vert_offset          40
#define wind_opt_horiz_length            40

// Graph options
const int wind_opts[] = {5, 10, 60};
const float res_opts[] = {0.5, 1.0, 5.0};
const char * char_res_opts[] = {"0.5", "1.0", "5.0"};
const char * char_wind_opts[] = {"05", "10", "60"};

#endif /* SOLAR_GUI_CONFIGS_H_ */
