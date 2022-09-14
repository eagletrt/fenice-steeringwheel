#ifndef INVLIB_INVERTER_H
#define INVLIB_INVERTER_H

#include <stdio.h>

#include "primary/c/ids.h"
#include "primary/c/network.h"

/* Configuration parameters from NDrive */
#define INV_MAX_RPM    6500                      /*< The "Nmax" parameter - maximum motor speed */

/* Register IDs for which updates will be activated */
#define INV_CMD_TX_REQ    0x3D
#define INV_REG_TORQUECMD 0x90
#define INV_REG_MODE      0x51
#define INV_REG_STATUS    0x40
#define INV_REG_IOINFO    0xD8
#define INV_REG_ERRORS    0x8F
#define INV_REG_SPEED     0xA8
#define INV_REG_MOT_TEMP  0x49
#define INV_REG_INV_TEMP  0x4A
#define INV_REG_I_CMD     0x26
#define INV_REG_I_ACTUAL  0x27

#define INV_IDX_LEFT      0
#define INV_IDX_RIGHT     1
#define INV_STR_SIZE      255

#ifndef INVLIB_PARKING
/* We know it's PACKING but PARKING sounds a bit better ;) */
#if defined(__MINGW32__)
#define INVLIB_PARKING __attribute__((__gcc_struct__, __packed__)) // , __aligned__(1)))
#else
#define INVLIB_PARKING __attribute__((__packed__)) // , __aligned__(1)))
#endif // defined(__MINGW32__)
#endif // INVLIB_PARKING


typedef struct INVLIB_PARKING{
  uint drive_enable:1;
  uint ncr0:1;
  uint limp:1;
  uint limm:1;
  uint drive_ok:1;
  uint icns:1;
  uint t_nlim:1;
  uint p_n:1;
  uint n_i:1;
  uint n0:1;
  uint rsw:1;
  uint cal0:1;
  uint cal:1;
  uint tol:1;
  uint drive_ready:1;
  uint brk:1;
  uint sign_mag:1;
  uint nclip:1;
  uint nclipp:1;
  uint nclipm:1;
  uint ird_dig:1;
  uint iuse_rchd:1;
  uint ird_n:1;
  uint ird_ti:1;
  uint ird_tir:1;
  uint hz10:1;
  uint ird_tm:1;
  uint ird_ana:1;
  uint iwcns:1;
  uint rfe_pulse:1;
  uint md:1;
  uint hnd_whl:1;
}inverter_status_expanded_t;

typedef struct INVLIB_PARKING{
  uint bad_param:1;
  uint hw_fault:1;
  uint safety_fault:1;
  uint can_timeout:1;
  uint encoder_err:1;
  uint no_power_voltage:1;
  uint hi_motor_temp:1;
  uint hi_device_temp:1;
  uint overvoltage:1;
  uint overcurrent:1;
  uint raceaway:1;
  uint user_err:1;
  uint unknown_err_12:1;
  uint unknown_err_13:1;
  uint current_err:1;
  uint ballast_overload:1;
  uint device_id_err:1;
  uint run_sig_fault:1;
  uint unknown_err_19:1;
  uint unknown_err_20:1;
  uint powervoltage_warn:1;
  uint hi_motor_temp_warn:1;
  uint hi_device_temp_warn:1;
  uint vout_limit_warn:1;
  uint overcurrent_warn:1;
  uint raceaway_warn:1;
  uint unknown_err_27:1;
  uint unknown_err_28:1;
  uint unknown_err_29:1;
  uint unknown_err_30:1;
  uint ballast_overload_warn:1;
} inverter_errors_expanded_t;

typedef struct INVLIB_PARKING{
  uint lmt1:1;
  uint lmt2:1;
  uint in2:1;
  uint in1:1;
  uint frg:1;
  uint rfe:1;
  uint unk6:1;
  uint unk7:1;
  uint out1:1;
  uint out2:1;
  uint btb:1;
  uint go:1;
  uint out3:1;
  uint out4:1;
  uint g_off:1;
  uint brk1:1;
}inverter_io_info_expanded_t;

typedef struct CANLIB_PARKING{
    primary_uint8 reg_id;
    primary_uint8 data_0;
    primary_uint8 data_1;
    primary_uint8 data_2;
    primary_uint8 data_3;
    primary_uint8 data_4;
    primary_uint8 data_5;
    primary_uint8 data_6;
#ifdef CANLIB_TIMESTAMP
    primary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
}inverter_message_INV_RESPONSE;
static_assert(sizeof(inverter_message_INV_RESPONSE) == sizeof(primary_message_INV_L_RESPONSE), "invlib l response message size != primary l response message size");
static_assert(sizeof(inverter_message_INV_RESPONSE) == sizeof(primary_message_INV_R_RESPONSE), "invlib r response message size != primary r response message size");

typedef struct {
    uint16_t io_info;
#ifdef CANLIB_TIMESTAMP
    uint64_t _timestamp;
#endif // CANLIB_TIMESTAMP
} inverter_io_info_t;

typedef struct {
    uint32_t status;
#ifdef CANLIB_TIMESTAMP
    uint64_t _timestamp;
#endif // CANLIB_TIMESTAMP
} inverter_status_t;

typedef struct {
    uint32_t errors;
#ifdef CANLIB_TIMESTAMP
    uint64_t _timestamp;
#endif // CANLIB_TIMESTAMP
} inverter_errors_t;

typedef struct {
    float temp;
#ifdef CANLIB_TIMESTAMP
    uint64_t _timestamp;
#endif // CANLIB_TIMESTAMP
} inverter_temp_t;

typedef struct {
    float motor_temp;
#ifdef CANLIB_TIMESTAMP
    uint64_t _timestamp;
#endif // CANLIB_TIMESTAMP
} inverter_motor_temp_t;

typedef struct {
    float speed;
#ifdef CANLIB_TIMESTAMP
    uint64_t _timestamp;
#endif // CANLIB_TIMESTAMP
} inverter_speed_t;

typedef struct {
    inverter_temp_t inverter_temp;
    inverter_speed_t inverter_speed;
    inverter_motor_temp_t inverter_motor_temp;
    inverter_status_t inverter_status;
    inverter_errors_t inverter_errors;
    inverter_io_info_t inverter_io_info;
} inverter_data_t;

typedef struct {
    FILE* inverter_temp;
    FILE* inverter_motor_temp;
    FILE* inverter_speed;
    FILE* inverter_status;
    FILE* inverter_errors;
    FILE* inverter_io_info;
} inverter_files_t;

void set_max_rpm(int16_t value);
int32_t inline inverter_get_errors(inverter_message_INV_RESPONSE *data);
int32_t inline inverter_get_status(inverter_message_INV_RESPONSE *data);
int16_t inline inverter_get_io_info(inverter_message_INV_RESPONSE *data);
float inline inverter_get_motor_temp(inverter_message_INV_RESPONSE *data);
float inline inverter_get_inverter_temp(inverter_message_INV_RESPONSE *data);
int16_t inline inverter_get_speed(inverter_message_INV_RESPONSE *data);
void inline inverter_get_status_expanded(const inverter_status_t* status, inverter_status_expanded_t* status_expanded);
void inline inverter_get_errors_expanded(const inverter_errors_t* errors, inverter_errors_expanded_t* errors_expanded);
void inline inverter_get_io_info_expanded(const inverter_io_info_t* io_info, inverter_io_info_expanded_t* io_info_expanded);

bool parse_inverter(inverter_message_INV_RESPONSE *data, int id, inverter_data_t inverters_data[2]);

const char* inverter_filename(int reg_id);
int inverter_fields(FILE *buffer, int reg_id);
void inverter_close_files(inverter_files_t* inverters_files);
void inverter_open_files(const char* folder, inverter_files_t* inverters_files);
bool inverter_to_file(inverter_message_INV_RESPONSE *data, int id, inverter_files_t files[2], inverter_data_t inverters_data[2]);

static int16_t max_rpm = INV_MAX_RPM;

#ifdef INVLIB_IMPLEMENTATION
#include <math.h>

void set_max_rpm(float value){
  max_rpm = value;
}

int32_t inline inverter_get_errors(inverter_message_INV_RESPONSE *data){
  return ((uint32_t)data->data_3 << 24) | (data->data_2 << 16) | (data->data_1 << 8) | data->data_0;
}

int32_t inline inverter_get_status(inverter_message_INV_RESPONSE *data){
  return ((uint32_t)data->data_3 << 24) | (data->data_2 << 16) | (data->data_1 << 8) | data->data_0;
}

int16_t inline inverter_get_io_info(inverter_message_INV_RESPONSE *data){
  return (data->data_1 << 8) | data->data_0;
}

float inline inverter_get_motor_temp(inverter_message_INV_RESPONSE *data) {
  int16_t m_temp = ((data->data_1 << 8) | data->data_0);
  return (m_temp - 9393.9f) / 55.1f;
}

float inline inverter_get_inverter_temp(inverter_message_INV_RESPONSE *data) {
  uint16_t i_temp = ((data->data_1 << 8) | data->data_0);
  return -43.23745 + 0.01073427*i_temp - 5.523417e-7*pow(i_temp, 2) + 1.330787e-11*pow(i_temp, 3);
}

int16_t inline inverter_get_speed(inverter_message_INV_RESPONSE *data) {
  return max_rpm * (int16_t)((data->data_1 << 8) | data->data_0) / 32767;
}

float inline rpm_to_rads(int16_t rpm) {
  return rpm * 2 * M_PI / 60;
}

void inline inverter_get_status_expanded(const inverter_status_t* status, inverter_status_expanded_t* status_expanded){
  memcpy(status_expanded, &(status->status), sizeof(inverter_status_expanded_t));
}

void inline inverter_get_errors_expanded(const inverter_errors_t* errors, inverter_errors_expanded_t* errors_expanded){
  memcpy(errors_expanded, &(errors->errors), sizeof(inverter_errors_expanded_t));
}

void inline inverter_get_io_info_expanded(const inverter_io_info_t* io_info, inverter_io_info_expanded_t* io_info_expanded){
  memcpy(io_info_expanded, &(io_info->io_info), sizeof(inverter_io_info_expanded_t));
}

FILE* inverter_open_file(const char* path, int reg_id, int inv_index){
  FILE* out = NULL;
  char buff[400];
  strcpy(buff, path);
  strcat(buff, inverter_filename(reg_id));
  if(inv_index == INV_IDX_LEFT)
    strcat(buff, "_L.csv");
  else if(inv_index == INV_IDX_RIGHT)
    strcat(buff, "_R.csv");

  out = fopen(buff, "w");
  inverter_fields(out, reg_id);
  fflush(out);
  return out;
}

void inverter_open_files(const char* folder, inverter_files_t* inverters_files){
  inverters_files[INV_IDX_LEFT].inverter_temp       = inverter_open_file(folder, INV_REG_INV_TEMP, INV_IDX_LEFT);
  inverters_files[INV_IDX_LEFT].inverter_motor_temp = inverter_open_file(folder, INV_REG_MOT_TEMP, INV_IDX_LEFT);
  inverters_files[INV_IDX_LEFT].inverter_speed      = inverter_open_file(folder, INV_REG_SPEED,    INV_IDX_LEFT);
  inverters_files[INV_IDX_LEFT].inverter_status     = inverter_open_file(folder, INV_REG_STATUS,   INV_IDX_LEFT);
  inverters_files[INV_IDX_LEFT].inverter_errors     = inverter_open_file(folder, INV_REG_ERRORS,   INV_IDX_LEFT);
  inverters_files[INV_IDX_LEFT].inverter_io_info    = inverter_open_file(folder, INV_REG_IOINFO,   INV_IDX_LEFT);

  inverters_files[INV_IDX_RIGHT].inverter_temp       = inverter_open_file(folder, INV_REG_INV_TEMP, INV_IDX_RIGHT);
  inverters_files[INV_IDX_RIGHT].inverter_motor_temp = inverter_open_file(folder, INV_REG_MOT_TEMP, INV_IDX_RIGHT);
  inverters_files[INV_IDX_RIGHT].inverter_speed      = inverter_open_file(folder, INV_REG_SPEED,    INV_IDX_RIGHT);
  inverters_files[INV_IDX_RIGHT].inverter_status     = inverter_open_file(folder, INV_REG_STATUS,   INV_IDX_RIGHT);
  inverters_files[INV_IDX_RIGHT].inverter_errors     = inverter_open_file(folder, INV_REG_ERRORS,   INV_IDX_RIGHT);
  inverters_files[INV_IDX_RIGHT].inverter_io_info    = inverter_open_file(folder, INV_REG_IOINFO,   INV_IDX_RIGHT);

}

void inverter_close_files(inverter_files_t* inverters_files){
  fflush(inverters_files[INV_IDX_LEFT].inverter_temp);
  fflush(inverters_files[INV_IDX_LEFT].inverter_motor_temp);
  fflush(inverters_files[INV_IDX_LEFT].inverter_speed);
  fflush(inverters_files[INV_IDX_LEFT].inverter_status);
  fflush(inverters_files[INV_IDX_LEFT].inverter_errors);
  fflush(inverters_files[INV_IDX_LEFT].inverter_io_info);
  fclose(inverters_files[INV_IDX_LEFT].inverter_temp);
  fclose(inverters_files[INV_IDX_LEFT].inverter_motor_temp);
  fclose(inverters_files[INV_IDX_LEFT].inverter_speed);
  fclose(inverters_files[INV_IDX_LEFT].inverter_status);
  fclose(inverters_files[INV_IDX_LEFT].inverter_errors);
  fclose(inverters_files[INV_IDX_LEFT].inverter_io_info);

  fflush(inverters_files[INV_IDX_RIGHT].inverter_temp);
  fflush(inverters_files[INV_IDX_RIGHT].inverter_motor_temp);
  fflush(inverters_files[INV_IDX_RIGHT].inverter_speed);
  fflush(inverters_files[INV_IDX_RIGHT].inverter_status);
  fflush(inverters_files[INV_IDX_RIGHT].inverter_errors);
  fflush(inverters_files[INV_IDX_RIGHT].inverter_io_info);
  fclose(inverters_files[INV_IDX_RIGHT].inverter_temp);
  fclose(inverters_files[INV_IDX_RIGHT].inverter_motor_temp);
  fclose(inverters_files[INV_IDX_RIGHT].inverter_speed);
  fclose(inverters_files[INV_IDX_RIGHT].inverter_status);
  fclose(inverters_files[INV_IDX_RIGHT].inverter_errors);
  fclose(inverters_files[INV_IDX_RIGHT].inverter_io_info);
}

const char* inverter_filename(int reg_id){
  switch (reg_id) {
    case INV_REG_INV_TEMP:
      return "INVERTER_TEMP";
    case INV_REG_MOT_TEMP:
      return "INVERTER_MOTOR_TEMP";
    case INV_REG_SPEED:
      return "INVERTER_SPEED";
    case INV_REG_STATUS:
      return "INVERTER_STATUS";
    case INV_REG_ERRORS:
      return "INVERTER_ERRORS";
    case INV_REG_IOINFO:
      return "INVERTER_IOINFO";
  }
  return "";
}

int inverter_fields(FILE *buffer, int reg_id) {
  switch (reg_id) {
    case INV_REG_INV_TEMP:
      return fprintf(buffer, "_timestamp,inverter_temp\n");
    break;
    case INV_REG_MOT_TEMP:
      return fprintf(buffer, "_timestamp,motor_temp\n");
    break;
    case INV_REG_SPEED:
      return fprintf(buffer, "_timestamp,speed\n");
    break;
    case INV_REG_STATUS:
      return fprintf(buffer, "_timestamp,status,status_str\n");
    break;
    case INV_REG_ERRORS:
      return fprintf(buffer, "_timestamp,errors,errors_str\n");
    break;
    case INV_REG_IOINFO:
      return fprintf(buffer, "_timestamp,io_info,io_info_str\n");
    break;
  }
  return 0;
}

bool inverter_to_file(inverter_message_INV_RESPONSE *data, int id, inverter_files_t* inverters_files, inverter_data_t inverters_data[2]) {
  inverter_data_t& inv = id == primary_ID_INV_L_RESPONSE ? inverters_data[INV_IDX_LEFT] : inverters_data[INV_IDX_RIGHT];
  inverter_files_t& file = id == primary_ID_INV_L_RESPONSE ? inverters_files[INV_IDX_LEFT] : inverters_files[INV_IDX_RIGHT];
  const uint str_buffer_size = 255;
  static char str_buffer[str_buffer_size];
  switch (data->reg_id) {
    case INV_REG_MOT_TEMP:
      if(file.inverter_motor_temp == NULL) return false;
      fprintf(file.inverter_motor_temp, "%" PRIu64 ",%f", inv.inverter_motor_temp._timestamp,
                    inv.inverter_motor_temp.motor_temp);
      fprintf(file.inverter_motor_temp, "\n");
      fflush(file.inverter_motor_temp);
      break;
    case INV_REG_INV_TEMP:
      if(file.inverter_temp == NULL) return false;
      fprintf(file.inverter_temp, "%" PRIu64 ",%f", inv.inverter_temp._timestamp,
                    inv.inverter_temp.temp);
      fprintf(file.inverter_temp, "\n");
      fflush(file.inverter_temp);
      break;
    case INV_REG_SPEED:
      if(file.inverter_speed == NULL) return false;
      fprintf(file.inverter_speed, "%" PRIu64 ",%f", inv.inverter_speed._timestamp,
                    inv.inverter_speed.speed);
      fprintf(file.inverter_speed, "\n");
      fflush(file.inverter_speed);
      break;
    case INV_REG_STATUS:
      if(file.inverter_status == NULL) return false;
      memset(str_buffer, 0, str_buffer_size);
      primary_to_string_InvStatus((primary_InvStatus)inv.inverter_status.status, str_buffer);
      fprintf(file.inverter_status, "%" PRIu64 ",%" PRIu32 ",\"%s\"", inv.inverter_status._timestamp,
                    inv.inverter_status.status, str_buffer);
      fprintf(file.inverter_status, "\n");
      fflush(file.inverter_status);
      break;
    case INV_REG_ERRORS:
      if(file.inverter_errors == NULL) return false;
      memset(str_buffer, 0, str_buffer_size);
      primary_to_string_InvErrors((primary_InvErrors)inv.inverter_errors.errors, str_buffer);
      fprintf(file.inverter_errors, "%" PRIu64 ",%" PRIu32 ",\"%s\"", inv.inverter_errors._timestamp,
                    inv.inverter_errors.errors, str_buffer);
      fprintf(file.inverter_errors, "\n");
      fflush(file.inverter_errors);
      break;
    case INV_REG_IOINFO:
      if(file.inverter_io_info == NULL) return false;
      memset(str_buffer, 0, str_buffer_size);
      primary_to_string_Inv_IOInfo((primary_Inv_IOInfo)inv.inverter_io_info.io_info, str_buffer);
      fprintf(file.inverter_io_info, "%" PRIu64 ",%" PRIu16 ",\"%s\"", inv.inverter_io_info._timestamp,
                    inv.inverter_io_info.io_info, str_buffer);
      fprintf(file.inverter_io_info, "\n");
      fflush(file.inverter_io_info);
      break;
    default:
      return false;
      break;
  }
  return true;
}

bool parse_inverter(inverter_message_INV_RESPONSE *data, int id, inverter_data_t inverters_data[2]){
  inverter_data_t& inv = id == primary_ID_INV_L_RESPONSE ? inverters_data[INV_IDX_LEFT] : inverters_data[INV_IDX_RIGHT];
  switch (data->reg_id) {
    case INV_REG_MOT_TEMP:
      inv.inverter_motor_temp._timestamp = data->_timestamp;
      inv.inverter_motor_temp.motor_temp = inverter_get_motor_temp(data);
      break;
    case INV_REG_INV_TEMP:
      inv.inverter_temp._timestamp = data->_timestamp;
      inv.inverter_temp.temp = inverter_get_inverter_temp(data);
      break;
    case INV_REG_SPEED:
      inv.inverter_speed._timestamp = data->_timestamp;
      inv.inverter_speed.speed = rpm_to_rads(inverter_get_speed(data));
      break;
    case INV_REG_STATUS:
      inv.inverter_status._timestamp = data->_timestamp;
      inv.inverter_status.status = inverter_get_status(data);
      break;
    case INV_REG_ERRORS:
      inv.inverter_errors._timestamp = data->_timestamp;
      inv.inverter_errors.errors = inverter_get_errors(data);
      break;
    case INV_REG_IOINFO:
      inv.inverter_io_info._timestamp = data->_timestamp;
      inv.inverter_io_info.io_info = inverter_get_io_info(data);
      break;
    default:
      return false;
      break;
  }
  return true;
}

#endif // INVLIB_IMPLEMENTATION
#endif