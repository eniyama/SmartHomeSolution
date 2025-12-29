/*
 * strcture.h
 *
 *  Created on: Dec 22, 2025
 *      Author: Dev-Laptop2
 */

#ifndef STRCTURE_H_
#define STRCTURE_H_

#include <stdint.h>

/* ================= FRAME TYPE DEFINITIONS ================= */

typedef enum
{
    eFrame_Type_Provision = 0x01,
    eFrame_Type_Command   = 0x03,
    eFrame_Type_Config    = 0x05
} eFrameType_t;

/* ================= PACKING ================= */

#pragma pack(push, 1)

/* ================= COMMON HEADER STRUCTURE ================= */
/* Total size: 4 bytes */

typedef struct
{
    uint8_t      version;      // Protocol Version
    eFrameType_t frame_type;   // Provision / Command / Config
    uint8_t      device_id;    // Device ID
    uint8_t      reserved;     // Reserved (0x00)
} frame_header_t;

/* ================= COMMON SUB-STRUCTURES ================= */

/* Command / Provision type */
typedef struct
{
    uint8_t command_type;
} command_type_t;

/* Interval Time : Fields 7–10 */
typedef struct
{
    uint32_t interval_time;
} interval_time_t;

/* Sensor Thresholds : Fields 11–12 */
typedef struct
{
    uint16_t temperature_threshold;
    uint16_t humidity_threshold;
} sensor_t;

/* Actuators : Fields 13–16 */
typedef struct
{
    uint8_t fan_default_speed;
    uint8_t ac_default_temp;
    uint8_t drapes_state;
    uint8_t air_purifier_state;
} actuator_t;

/* ================= PAYLOAD STRUCTURES ================= */

/* -------- Provision Payload -------- */
typedef struct
{
    frame_header_t  header;     // 4 bytes
    command_type_t command;     // 1 byte
    interval_time_t interval;   // 4 bytes
    sensor_t        sensor;     // 4 bytes
    actuator_t      actuator;   // 4 bytes
    uint8_t         padding[43]; // To make total payload = 60 bytes
} provision_t;

/* -------- Command Payload -------- */
typedef struct
{
    frame_header_t header;      // 4 bytes
    command_type_t command;     // 1 byte
    actuator_t     actuator;    // 4 bytes
    uint8_t        padding[51]; // Total payload = 60 bytes
} command_t;

/* -------- Config Payload -------- */
typedef struct
{
    frame_header_t  header;     // 4 bytes
    interval_time_t interval;   // 4 bytes
    sensor_t        sensor;     // 4 bytes
    uint8_t         padding[48]; // Total payload = 60 bytes
} config_t;

#pragma pack(pop)

#endif /* INC_STRCTURE_H_ */
