#ifndef PRO_H
#define PRO_H

#include <stdint.h>

enum
{
 PKG_HEADER = 0x54,
 PKG_VER_LEN = 0x2C,
 POINT_PER_PACK = 12,
//POINT_PER_PACK = 360,
};

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint16_t Distance;
    uint8_t Confidence;
}LidarPointStructDef;

typedef struct
{
    uint8_t           Header;
    uint8_t           VerAndLength;
    uint16_t          Speed;
    uint16_t          StartAngle;
    LidarPointStructDef LidarPoint[POINT_PER_PACK];
    uint16_t          EndAngle;
    uint16_t          Timestamp;
    uint8_t           Crc8;
}LiPkgTypeDef;
#pragma pack(pop)

#endif // PRO_H
