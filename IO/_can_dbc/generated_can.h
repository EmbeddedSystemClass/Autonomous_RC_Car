/// DBC file: C:/SJSU_Dev/projects/spartan_and_furious/snf.dbc    Self node: 'IO'  (ALL = 0)
/// This file can be included by a source file, for example: #include "generated.h"
#ifndef __GENEARTED_DBC_PARSER
#define __GENERATED_DBC_PARSER
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/// Extern function needed for dbc_encode_and_send()
extern bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);

/// Missing in Action structure
typedef struct {
    uint32_t is_mia : 1;          ///< Missing in action flag
    uint32_t mia_counter_ms : 31; ///< Missing in action counter
} dbc_mia_info_t;

/// CAN message header structure
typedef struct { 
    uint32_t mid; ///< Message ID of the message
    uint8_t  dlc; ///< Data length of the message
} dbc_msg_hdr_t; 

// static const dbc_msg_hdr_t BLE_COMM_CMD_HDR =                     {  010, 1 };
static const dbc_msg_hdr_t SYSTEM_CMD_HDR =                       {  100, 1 };
// static const dbc_msg_hdr_t MASTER_HEARTBEAT_HDR =                 {  134, 4 };
static const dbc_msg_hdr_t MOTOR_CMD_HDR =                        {  151, 3 };
static const dbc_msg_hdr_t SYSTEM_STATUS_HDR =                    {  162, 2 };
// static const dbc_msg_hdr_t SENSOR_ULTRASONIC_HDR =                {  211, 7 };
static const dbc_msg_hdr_t SENSOR_SPEED_HDR =                     {  212, 1 };
static const dbc_msg_hdr_t SENSOR_BATT_HDR =                      {  213, 1 };
// static const dbc_msg_hdr_t SENSOR_HEARTBEAT_HDR =                 {  214, 4 };
// static const dbc_msg_hdr_t BLE_CHCK_PT_HDR =                      {  311, 4 };
static const dbc_msg_hdr_t BLE_DEST_RCHD_HDR =                    {  312, 1 };
// static const dbc_msg_hdr_t BLE_HEARTBEAT_HDR =                    {  314, 4 };
static const dbc_msg_hdr_t BLE_MAP_DATA_HDR =                     {  361, 8 };
// static const dbc_msg_hdr_t GEO_DIRECTION_HDR =                    {  411, 1 };
// static const dbc_msg_hdr_t GEO_ACCELEROMETER_HDR =                {  412, 1 };
// static const dbc_msg_hdr_t GEO_HEARTBEAT_HDR =                    {  414, 4 };
static const dbc_msg_hdr_t GEO_LOCATION_HDR =                     {  421, 5 };
// static const dbc_msg_hdr_t MOTOR_HEARTBEAT_HDR =                  {  514, 4 };
static const dbc_msg_hdr_t IO_HEARTBEAT_HDR =                     {  614, 4 };

/// Enumeration(s) for Message: 'SYSTEM_CMD' from 'MASTER'
typedef enum {
    SYSTEM_START = 1,
    SYSTEM_RESET = 2,
    SYSTEM_STOP = 0,
} SYSTEM_CMD_enum_E ;

/// Enumeration(s) for Message: 'MOTOR_CMD' from 'MASTER'
typedef enum {
    STEER_HALF_LEFT = 1,
    STEER_FORWARD = 4,
    STEER_HALF_RIGHT = 3,
    STEER_LEFT = 0,
    STEER_RIGHT = 2,
    STEER_REVERSE = 5,
} MOTOR_CMD_steer_E ;

typedef enum {
    BRAKE = 2,
    RESUME = 3,
    STOP = 0,
    START = 1,
} MOTOR_CMD_drive_E ;




/// Message: SYSTEM_CMD from 'MASTER', DLC: 1 byte(s), MID: 100
typedef struct {
    SYSTEM_CMD_enum_E SYSTEM_CMD_enum;        ///< B7:0   Destination: BLE,GEO,IO,MOTOR,SENSOR

    dbc_mia_info_t mia_info;
} SYSTEM_CMD_t;


/// Message: MOTOR_CMD from 'MASTER', DLC: 3 byte(s), MID: 151
typedef struct {
    uint8_t MOTOR_CMD_speed;                  ///< B4:0  Min: 10 Max: 20   Destination: MOTOR,IO
    MOTOR_CMD_steer_E MOTOR_CMD_steer;        ///< B15:8   Destination: MOTOR,IO
    MOTOR_CMD_drive_E MOTOR_CMD_drive;        ///< B23:16   Destination: MOTOR,IO

    dbc_mia_info_t mia_info;
} MOTOR_CMD_t;


/// Message: SYSTEM_STATUS from 'MASTER', DLC: 2 byte(s), MID: 162
typedef struct {
    uint8_t SYSTEM_STATUS_ble : 1;            ///< B0:0   Destination: BLE,IO
    uint8_t SYSTEM_STATUS_geo : 1;            ///< B1:1   Destination: BLE,IO
    uint8_t SYSTEM_STATUS_io : 1;             ///< B2:2   Destination: BLE,IO
    uint8_t SYSTEM_STATUS_master : 1;         ///< B3:3   Destination: BLE,IO
    uint8_t SYSTEM_STATUS_motor : 1;          ///< B4:4   Destination: BLE,IO
    uint8_t SYSTEM_STATUS_sensor : 1;         ///< B5:5   Destination: BLE,IO
    uint8_t SYSTEM_STATUS_util;               ///< B15:8  Min: 0 Max: 100   Destination: BLE,IO

    dbc_mia_info_t mia_info;
} SYSTEM_STATUS_t;


/// Message: SENSOR_SPEED from 'SENSOR', DLC: 1 byte(s), MID: 212
typedef struct {
    uint8_t SENSOR_SPEED_data;                ///< B7:0   Destination: MASTER,IO,BLE

    dbc_mia_info_t mia_info;
} SENSOR_SPEED_t;


/// Message: SENSOR_BATT from 'SENSOR', DLC: 1 byte(s), MID: 213
typedef struct {
    uint8_t SENSOR_BATT_stat;                 ///< B6:0  Min: 0 Max: 100   Destination: MASTER,IO,BLE

    dbc_mia_info_t mia_info;
} SENSOR_BATT_t;


/// Message: BLE_DEST_RCHD from 'BLE', DLC: 1 byte(s), MID: 312
typedef struct {
    uint8_t BLE_DEST_RCHD_stat : 1;           ///< B0:0  Min: 0 Max: 1   Destination: MASTER,IO

    dbc_mia_info_t mia_info;
} BLE_DEST_RCHD_t;


/// Message: BLE_MAP_DATA from 'BLE', DLC: 8 byte(s), MID: 361
typedef struct {
    uint16_t BLE_MAP_DATA_start_lat;          ///< B15:0   Destination: IO
    uint16_t BLE_MAP_DATA_start_long;         ///< B31:16   Destination: IO
    uint16_t BLE_MAP_DATA_dest_lat;           ///< B47:32   Destination: IO
    uint16_t BLE_MAP_DATA_dest_long;          ///< B63:48   Destination: IO

    dbc_mia_info_t mia_info;
} BLE_MAP_DATA_t;


/// Message: GEO_LOCATION from 'GEO', DLC: 5 byte(s), MID: 421
typedef struct {
    uint16_t GEO_LOCATION_lat;                ///< B15:0   Destination: BLE,IO
    uint16_t GEO_LOCATION_long;               ///< B31:16   Destination: BLE,IO
    uint8_t GEO_COMPASS_mag;                  ///< B39:32   Destination: BLE,IO

    dbc_mia_info_t mia_info;
} GEO_LOCATION_t;


/// Message: IO_HEARTBEAT from 'IO', DLC: 4 byte(s), MID: 614
typedef struct {
    uint16_t IO_HEARTBEAT_rx_bytes;           ///< B15:0   Destination: MASTER
    uint16_t IO_HEARTBEAT_tx_bytes;           ///< B31:16   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} IO_HEARTBEAT_t;


/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t                             SYSTEM_CMD__MIA_MS;
extern const SYSTEM_CMD_t                         SYSTEM_CMD__MIA_MSG;
extern const uint32_t                             MOTOR_CMD__MIA_MS;
extern const MOTOR_CMD_t                          MOTOR_CMD__MIA_MSG;
extern const uint32_t                             SYSTEM_STATUS__MIA_MS;
extern const SYSTEM_STATUS_t                      SYSTEM_STATUS__MIA_MSG;
extern const uint32_t                             SENSOR_SPEED__MIA_MS;
extern const SENSOR_SPEED_t                       SENSOR_SPEED__MIA_MSG;
extern const uint32_t                             SENSOR_BATT__MIA_MS;
extern const SENSOR_BATT_t                        SENSOR_BATT__MIA_MSG;
extern const uint32_t                             BLE_DEST_RCHD__MIA_MS;
extern const BLE_DEST_RCHD_t                      BLE_DEST_RCHD__MIA_MSG;
extern const uint32_t                             BLE_MAP_DATA__MIA_MS;
extern const BLE_MAP_DATA_t                       BLE_MAP_DATA__MIA_MSG;
extern const uint32_t                             GEO_LOCATION__MIA_MS;
extern const GEO_LOCATION_t                       GEO_LOCATION__MIA_MSG;
/// @}


/// Not generating code for dbc_encode_BLE_COMM_CMD() since the sender is BLE and we are IO

/// Not generating code for dbc_encode_SYSTEM_CMD() since the sender is MASTER and we are IO

/// Not generating code for dbc_encode_MASTER_HEARTBEAT() since the sender is MASTER and we are IO

/// Not generating code for dbc_encode_MOTOR_CMD() since the sender is MASTER and we are IO

/// Not generating code for dbc_encode_SYSTEM_STATUS() since the sender is MASTER and we are IO

/// Not generating code for dbc_encode_SENSOR_ULTRASONIC() since the sender is SENSOR and we are IO

/// Not generating code for dbc_encode_SENSOR_SPEED() since the sender is SENSOR and we are IO

/// Not generating code for dbc_encode_SENSOR_BATT() since the sender is SENSOR and we are IO

/// Not generating code for dbc_encode_SENSOR_HEARTBEAT() since the sender is SENSOR and we are IO

/// Not generating code for dbc_encode_BLE_CHCK_PT() since the sender is BLE and we are IO

/// Not generating code for dbc_encode_BLE_DEST_RCHD() since the sender is BLE and we are IO

/// Not generating code for dbc_encode_BLE_HEARTBEAT() since the sender is BLE and we are IO

/// Not generating code for dbc_encode_BLE_MAP_DATA() since the sender is BLE and we are IO

/// Not generating code for dbc_encode_GEO_DIRECTION() since the sender is GEO and we are IO

/// Not generating code for dbc_encode_GEO_ACCELEROMETER() since the sender is GEO and we are IO

/// Not generating code for dbc_encode_GEO_HEARTBEAT() since the sender is GEO and we are IO

/// Not generating code for dbc_encode_GEO_LOCATION() since the sender is GEO and we are IO

/// Not generating code for dbc_encode_MOTOR_HEARTBEAT() since the sender is MOTOR and we are IO

/// Encode IO's 'IO_HEARTBEAT' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_IO_HEARTBEAT(uint8_t bytes[8], IO_HEARTBEAT_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->IO_HEARTBEAT_rx_bytes)))) & 0xffff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0xff)); ///< 8 bit(s) starting from B8

    raw = ((uint32_t)(((from->IO_HEARTBEAT_tx_bytes)))) & 0xffff;
    bytes[2] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B16
    bytes[3] |= (((uint8_t)(raw >> 8) & 0xff)); ///< 8 bit(s) starting from B24

    return IO_HEARTBEAT_HDR;
}

/// Encode and send for dbc_encode_IO_HEARTBEAT() message
static inline bool dbc_encode_and_send_IO_HEARTBEAT(IO_HEARTBEAT_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_IO_HEARTBEAT(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_decode_BLE_COMM_CMD() since 'IO' is not the recipient of any of the signals

/// Decode MASTER's 'SYSTEM_CMD' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_SYSTEM_CMD(SYSTEM_CMD_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != SYSTEM_CMD_HDR.dlc || hdr->mid != SYSTEM_CMD_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    to->SYSTEM_CMD_enum = (SYSTEM_CMD_enum_E)((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_MASTER_HEARTBEAT() since 'IO' is not the recipient of any of the signals

/// Decode MASTER's 'MOTOR_CMD' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_CMD(MOTOR_CMD_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != MOTOR_CMD_HDR.dlc || hdr->mid != MOTOR_CMD_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]) & 0x1f)); ///< 5 bit(s) from B0
    to->MOTOR_CMD_speed = ((raw));
    raw  = ((uint32_t)((bytes[1]))); ///< 8 bit(s) from B8
    to->MOTOR_CMD_steer = (MOTOR_CMD_steer_E)((raw));
    raw  = ((uint32_t)((bytes[2]))); ///< 8 bit(s) from B16
    to->MOTOR_CMD_drive = (MOTOR_CMD_drive_E)((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Decode MASTER's 'SYSTEM_STATUS' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_SYSTEM_STATUS(SYSTEM_STATUS_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != SYSTEM_STATUS_HDR.dlc || hdr->mid != SYSTEM_STATUS_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]) & 0x01)); ///< 1 bit(s) from B0
    to->SYSTEM_STATUS_ble = ((raw));
    raw  = ((uint32_t)((bytes[0] >> 1) & 0x01)); ///< 1 bit(s) from B1
    to->SYSTEM_STATUS_geo = ((raw));
    raw  = ((uint32_t)((bytes[0] >> 2) & 0x01)); ///< 1 bit(s) from B2
    to->SYSTEM_STATUS_io = ((raw));
    raw  = ((uint32_t)((bytes[0] >> 3) & 0x01)); ///< 1 bit(s) from B3
    to->SYSTEM_STATUS_master = ((raw));
    raw  = ((uint32_t)((bytes[0] >> 4) & 0x01)); ///< 1 bit(s) from B4
    to->SYSTEM_STATUS_motor = ((raw));
    raw  = ((uint32_t)((bytes[0] >> 5) & 0x01)); ///< 1 bit(s) from B5
    to->SYSTEM_STATUS_sensor = ((raw));
    raw  = ((uint32_t)((bytes[1]))); ///< 8 bit(s) from B8
    to->SYSTEM_STATUS_util = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_SENSOR_ULTRASONIC() since 'IO' is not the recipient of any of the signals

/// Decode SENSOR's 'SENSOR_SPEED' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_SENSOR_SPEED(SENSOR_SPEED_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != SENSOR_SPEED_HDR.dlc || hdr->mid != SENSOR_SPEED_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    to->SENSOR_SPEED_data = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Decode SENSOR's 'SENSOR_BATT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_SENSOR_BATT(SENSOR_BATT_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != SENSOR_BATT_HDR.dlc || hdr->mid != SENSOR_BATT_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]) & 0x7f)); ///< 7 bit(s) from B0
    to->SENSOR_BATT_stat = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_SENSOR_HEARTBEAT() since 'IO' is not the recipient of any of the signals

/// Not generating code for dbc_decode_BLE_CHCK_PT() since 'IO' is not the recipient of any of the signals

/// Decode BLE's 'BLE_DEST_RCHD' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_BLE_DEST_RCHD(BLE_DEST_RCHD_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != BLE_DEST_RCHD_HDR.dlc || hdr->mid != BLE_DEST_RCHD_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]) & 0x01)); ///< 1 bit(s) from B0
    to->BLE_DEST_RCHD_stat = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_BLE_HEARTBEAT() since 'IO' is not the recipient of any of the signals

/// Decode BLE's 'BLE_MAP_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_BLE_MAP_DATA(BLE_MAP_DATA_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != BLE_MAP_DATA_HDR.dlc || hdr->mid != BLE_MAP_DATA_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    raw |= ((uint32_t)((bytes[1]))) << 8; ///< 8 bit(s) from B8
    to->BLE_MAP_DATA_start_lat = ((raw));
    raw  = ((uint32_t)((bytes[2]))); ///< 8 bit(s) from B16
    raw |= ((uint32_t)((bytes[3]))) << 8; ///< 8 bit(s) from B24
    to->BLE_MAP_DATA_start_long = ((raw));
    raw  = ((uint32_t)((bytes[4]))); ///< 8 bit(s) from B32
    raw |= ((uint32_t)((bytes[5]))) << 8; ///< 8 bit(s) from B40
    to->BLE_MAP_DATA_dest_lat = ((raw));
    raw  = ((uint32_t)((bytes[6]))); ///< 8 bit(s) from B48
    raw |= ((uint32_t)((bytes[7]))) << 8; ///< 8 bit(s) from B56
    to->BLE_MAP_DATA_dest_long = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_GEO_DIRECTION() since 'IO' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GEO_ACCELEROMETER() since 'IO' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GEO_HEARTBEAT() since 'IO' is not the recipient of any of the signals

/// Decode GEO's 'GEO_LOCATION' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GEO_LOCATION(GEO_LOCATION_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != GEO_LOCATION_HDR.dlc || hdr->mid != GEO_LOCATION_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    raw |= ((uint32_t)((bytes[1]))) << 8; ///< 8 bit(s) from B8
    to->GEO_LOCATION_lat = ((raw));
    raw  = ((uint32_t)((bytes[2]))); ///< 8 bit(s) from B16
    raw |= ((uint32_t)((bytes[3]))) << 8; ///< 8 bit(s) from B24
    to->GEO_LOCATION_long = ((raw));
    raw  = ((uint32_t)((bytes[4]))); ///< 8 bit(s) from B32
    to->GEO_COMPASS_mag = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_MOTOR_HEARTBEAT() since 'IO' is not the recipient of any of the signals

/// Not generating code for dbc_decode_IO_HEARTBEAT() since 'IO' is not the recipient of any of the signals

/// Handle the MIA for MASTER's SYSTEM_CMD message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_SYSTEM_CMD(SYSTEM_CMD_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= SYSTEM_CMD__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = SYSTEM_CMD__MIA_MSG;
        msg->mia_info.mia_counter_ms = SYSTEM_CMD__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for MASTER's MOTOR_CMD message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_CMD(MOTOR_CMD_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_CMD__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = MOTOR_CMD__MIA_MSG;
        msg->mia_info.mia_counter_ms = MOTOR_CMD__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for MASTER's SYSTEM_STATUS message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_SYSTEM_STATUS(SYSTEM_STATUS_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= SYSTEM_STATUS__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = SYSTEM_STATUS__MIA_MSG;
        msg->mia_info.mia_counter_ms = SYSTEM_STATUS__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for SENSOR's SENSOR_SPEED message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_SENSOR_SPEED(SENSOR_SPEED_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= SENSOR_SPEED__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = SENSOR_SPEED__MIA_MSG;
        msg->mia_info.mia_counter_ms = SENSOR_SPEED__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for SENSOR's SENSOR_BATT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_SENSOR_BATT(SENSOR_BATT_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= SENSOR_BATT__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = SENSOR_BATT__MIA_MSG;
        msg->mia_info.mia_counter_ms = SENSOR_BATT__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for BLE's BLE_DEST_RCHD message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_BLE_DEST_RCHD(BLE_DEST_RCHD_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= BLE_DEST_RCHD__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = BLE_DEST_RCHD__MIA_MSG;
        msg->mia_info.mia_counter_ms = BLE_DEST_RCHD__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for BLE's BLE_MAP_DATA message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_BLE_MAP_DATA(BLE_MAP_DATA_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= BLE_MAP_DATA__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = BLE_MAP_DATA__MIA_MSG;
        msg->mia_info.mia_counter_ms = BLE_MAP_DATA__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for GEO's GEO_LOCATION message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GEO_LOCATION(GEO_LOCATION_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GEO_LOCATION__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = GEO_LOCATION__MIA_MSG;
        msg->mia_info.mia_counter_ms = GEO_LOCATION__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

#endif