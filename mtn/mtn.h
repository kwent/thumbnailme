#ifndef MTN_H
#define MTN_H

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

#define NO_OLDNAMES

#include "fake_tchar.h"
#include "gd.h"
#include "libswscale/swscale.h"

#define UTF8_FILENAME_SIZE (FILENAME_MAX*4)

// newline character for info file
#ifdef WIN32
    #define NEWLINE "\r\n"
#else
    #define NEWLINE "\n"
#endif

#define EDGE_PARTS 6 // # of parts used in edge detection
#define EDGE_FOUND 0.001f // edge is considered found

typedef struct rgb_color
{   // GD uses int, so we'll use int too
    int r; // red
    int g; // green
    int b; // blue
} rgb_color;

typedef char color_str[7]; // "RRGGBB" (in hex)

#define COLOR_BLACK (rgb_color){0, 0, 0}
#define COLOR_GREY (rgb_color){128, 128, 128}
#define COLOR_WHITE (rgb_color){255, 255, 255}
#define COLOR_INFO (rgb_color){85, 85, 85}

typedef struct shot
{
    gdImagePtr ip;
    int64_t eff_target;
    int64_t found_pts;
    double blank; // blank detection
    float edge[EDGE_PARTS]; // edge detection
} shot; // shot

typedef struct thumbnail
{
    gdImagePtr out_ip;
    char out_filename[UTF8_FILENAME_SIZE];
    char info_filename[UTF8_FILENAME_SIZE];
    int out_saved; // 1 = out file is successfully saved
    int width, height;
    int txt_height;
    int column, row;
    int step;
    int shot_width, shot_height;
    int center_gap; // horizontal gap to center the shots
    int idx; // index of the last shot; -1 = no shot

    // dynamic
    int64_t *ppts; // array of pts value of each shot
} thumbnail; // thumbnail data & info

/* LIBAVUTIL_VERSION_INT is too low for VERBOSE & INFO, so we'll define our own */
#define LOG_INFO 0

/* command line options & default values */
#define GB_A_RATIO (AVRational){0, 1}
#define GB_B_BLANK 0.8
#define GB_B_BEGIN 0.0
#define GB_C_COLUMN 3
#define GB_C_CUT -1
#define GB_D_EDGE 12
#define GB_E_EXT NULL
#define GB_E_END 0.0
#define GB_F_FONTNAME "tahomabd.ttf"
#define GB_G_GAP 0
#define GB_H_HEIGHT 150
#define GB_I_INFO 1
#define GB_I_INDIVIDUAL 0
#define GB_J_QUALITY 90
#define GB_K_BCOLOR COLOR_WHITE
#define GB_L_INFO_LOCATION 4
#define GB_L_TIME_LOCATION 1
#define GB_N_NORMAL 0
#define GB_N_SUFFIX NULL
#define GB_O_SUFFIX_USE_FULL 0
#define GB_O_SUFFIX "_s.jpg"
#define GB_O_OUTDIR NULL
#define GB_Q_QUIET 0
#define GB_R_ROW 0
#define GB_S_STEP 120
#define GB_T_TIME 1
#define GB_T_TEXT NULL
#define GB_V_VERBOSE 0
#define GB_W_WIDTH 1024
#define GB_Z_SEEK 0
#define GB_Z_NONSEEK 0

typedef struct params
{
  char *gb_argv0;
  AVRational gb_a_ratio;
  double gb_b_blank;
  double gb_B_begin; // skip this seconds from the beginning
  int gb_c_column;
  double gb_C_cut; // cut movie; <=0 off
  int gb_D_edge; // edge detection; 0 off; >0 on
  char *gb_e_ext;
  double gb_E_end; // skip this seconds at the end
  char *gb_f_fontname;
  rgb_color gb_F_info_color; // info color
  double gb_F_info_font_size; // info font size
  char *gb_F_ts_fontname; // time stamp fontname
  rgb_color gb_F_ts_color; // time stamp color
  rgb_color gb_F_ts_shadow; // time stamp shadow color
  double gb_F_ts_font_size; // time stamp font size
  int gb_g_gap;
  int gb_h_height; // mininum height of each shot; will reduce # of column to meet this height
  int gb_i_info; // 1 on; 0 off
  int gb_I_individual; // 1 on; 0 off
  int gb_j_quality;
  rgb_color gb_k_bcolor; // background color
  int gb_L_info_location;
  int gb_L_time_location;
  int gb_n_normal; // normal priority; 1 normal; 0 lower
  char *gb_N_suffix; // info text file suffix
  char *gb_o_suffix;
  char *gb_O_outdir;
  int gb_q_quiet; // 1 on; 0 off
  int gb_r_row; // 0 = as many rows as needed
  int gb_s_step; // less than 0 = every frame; 0 = step evenly to get column x row
  int gb_t_timestamp; // 1 on; 0 off
  char *gb_T_text;
  int gb_v_verbose; // 1 on; 0 off
  int gb_V; // 1 on; 0 off
  int gb_w_width; // 0 = column * movie width
  int gb_z_seek; // always use seek mode; 1 on; 0 off
  int gb_Z_nonseek; // always use non-seek mode; 1 on; 0 off

} params; // params data & info

#endif // MTN_H
