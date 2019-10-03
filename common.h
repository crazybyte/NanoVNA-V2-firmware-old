#pragma once

// constants and data types used by all modules.
// DO NOT DECLARE EXTERNAL FUNCTIONS HERE!!!

#define TRACES_MAX 4
#define FFT_SIZE 256



#define CAL_LOAD 0
#define CAL_OPEN 1
#define CAL_SHORT 2
#define CAL_THRU 3
#define CAL_ISOLN 4

#define CALSTAT_LOAD (1<<0)
#define CALSTAT_OPEN (1<<1)
#define CALSTAT_SHORT (1<<2)
#define CALSTAT_THRU (1<<3)
#define CALSTAT_ISOLN (1<<4)
#define CALSTAT_ES (1<<5)
#define CALSTAT_ER (1<<6)
#define CALSTAT_ET (1<<7)
#define CALSTAT_ED CALSTAT_LOAD
#define CALSTAT_EX CALSTAT_ISOLN
#define CALSTAT_APPLY (1<<8)
#define CALSTAT_INTERPOLATED (1<<9)

#define ETERM_ED 0 /* error term directivity */
#define ETERM_ES 1 /* error term source match */
#define ETERM_ER 2 /* error term refrection tracking */
#define ETERM_ET 3 /* error term transmission tracking */
#define ETERM_EX 4 /* error term isolation */

#define DOMAIN_MODE (1<<0)
#define DOMAIN_FREQ (0<<0)
#define DOMAIN_TIME (1<<0)
#define TD_FUNC (0b11<<1)
#define TD_FUNC_BANDPASS (0b00<<1)
#define TD_FUNC_LOWPASS_IMPULSE (0b01<<1)
#define TD_FUNC_LOWPASS_STEP    (0b10<<1)
#define TD_WINDOW (0b11<<3)
#define TD_WINDOW_NORMAL (0b00<<3)
#define TD_WINDOW_MINIMUM (0b01<<3)
#define TD_WINDOW_MAXIMUM (0b10<<3)


enum {
  TRC_LOGMAG, TRC_PHASE, TRC_DELAY, TRC_SMITH, TRC_POLAR, TRC_LINEAR, TRC_SWR, TRC_REAL, TRC_IMAG, TRC_R, TRC_X, TRC_OFF
};

enum {
  ST_START, ST_STOP, ST_CENTER, ST_SPAN, ST_CW
};

typedef struct {
  uint8_t enabled;
  uint8_t type;
  uint8_t channel;
  uint8_t polar;
  float scale;
  float refpos;
} trace_t;

typedef struct {
  int8_t enabled;
  int16_t index;
  uint32_t frequency;
} marker_t;

typedef struct {
  int32_t magic;
  int32_t _frequency0; // start or center
  int32_t _frequency1; // stop or span
  int16_t _sweep_points;
  uint16_t _cal_status;

  uint32_t _frequencies[101];
  float _cal_data[5][101][2];
  float _electrical_delay; // picoseconds
  
  trace_t _trace[TRACES_MAX];
  marker_t _markers[4];
  int _active_marker;
  uint8_t _domain_mode; /* 0bxxxxxffm : where ff: TD_FUNC m: DOMAIN_MODE */
  uint8_t _velocity_factor; // %

  int32_t checksum;
} properties_t;


typedef struct {
  int32_t magic;
  uint16_t dac_value;
  uint16_t grid_color;
  uint16_t menu_normal_color;
  uint16_t menu_active_color;
  uint16_t trace_color[TRACES_MAX];
  int16_t touch_cal[4];
  int8_t default_loadcal;
  int32_t checksum;
} config_t;


#define CONFIG_MAGIC 0x434f4e45 /* 'CONF' */



// convert vbat [mV] to battery indicator
static inline uint8_t vbat2bati(int16_t vbat)
{
	if (vbat < 3200) return 0;
	if (vbat < 3450) return 25;
	if (vbat < 3700) return 50;
	if (vbat < 4100) return 75;
	return 100;
}



static const struct {
  const char *name;
  uint16_t refpos;
  float scale_unit;
} trace_info[] = {
  { "LOGMAG", 7, 10 },
  { "PHASE",  4, 90 },
  { "DELAY",  4,  1 },
  { "SMITH",  0,  1 },
  { "POLAR",  0,  1 },
  { "LINEAR", 0,  0.125 },
  { "SWR",    0,  1 },
  { "REAL",   4,  0.25 },
  { "IMAG",   4,  0.25 },
  { "R",      0, 100 },
  { "X",      4, 100 }
};

static const char * const trc_channel_name[] = {
  "CH0", "CH1"
};


