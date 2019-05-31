#ifndef COMMAND_H
#define COMMAND_H
#include "common/Common.h"
/******************************************************************************/
/* Offset in command and response array */
enum offset {
    OFFSET_HEADER = 0,
    OFFSET_LEN_LO = 1,
    OFFSET_LEN_HI = 2,
    OFFSET_CMD_TYPE = 3,
    OFFSET_CMD_CODE = 4,
    OFFSET_CMD_DATA = 5,
};

enum offsetRX {
    OFFSET_CMD_TYPE_RX = 3,
    OFFSET_CMD_CODE_RX = 4,
    OFFSET_CMD_DATA_RX = 5,
};

/* Command type */
enum cmdType {
    CMD_TYPE_NONE = 0,
    CMD_TYPE_APP = 0XFE,
    CMD_TYPE_BL = 0xFF,
};

/* Command code */
enum cmdCode {
    CMD_CODE_STATUS = 0X00,
    APP_CLEAR_RECORD= 0x78,
    APP_SEEK_RECORD,
    APP_RECORD_COUNT,
};

#endif // COMMAND_H
