#pragma once

#define LEFT_FIRST_UNDERGLOW 0
#define LEFT_LAST_UNDERGLOW 5
#define LEFT_FIRST_RGB 6
#define LEFT_LAST_RGB 26

#define RIGHT_FIRST_UNDERGLOW 27
#define RIGHT_LAST_UNDERGLOW 32
#define RIGHT_FIRST_RGB 33
#define RIGHT_LAST_RGB 53

#define INDIGN 255
#define INDOFF 0

// clang-format off
const uint8_t PROGMEM hue_indicators[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_split_3x6_3(
    INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,                         INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,
    INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,                         INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,
    INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,                         INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,
                                    INDIGN, INDIGN, INDIGN,         INDIGN, INDIGN, INDIGN
),

[_COLEMAK] = LAYOUT_split_3x6_3(
    INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,                         INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,
    INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,                         INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,
    INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,                         INDIGN, INDIGN, INDIGN, INDIGN, INDIGN, INDIGN,
                                    INDIGN, INDIGN, INDIGN,         INDIGN, INDIGN, INDIGN
),

[_GAMING] = LAYOUT_split_3x6_3(
    INDOFF, INDOFF, INDIGN, INDOFF, INDOFF, INDOFF,                         INDOFF, INDOFF, INDOFF, INDOFF, INDOFF, INDOFF,
    INDOFF, INDIGN, INDIGN, INDIGN, INDOFF, INDOFF,                         INDOFF, INDOFF, INDOFF, INDOFF, INDOFF, INDIGN,
    INDOFF, INDOFF, INDOFF, INDOFF, INDOFF, INDOFF,                         INDOFF, INDOFF, INDOFF, INDOFF, INDOFF, INDIGN,
                                    INDOFF, INDOFF, INDOFF,         INDOFF, INDOFF, INDOFF
),

[_LOWER] = LAYOUT_split_3x6_3(
    INDOFF, 21    , 21    , 21    , 21    , 21    ,                         1     , 1     , 1     , 1     , 1     , INDOFF,
    INDOFF, 21    , 21    , 21    , 21    , 21    ,                         1     , 1     , 1     , 1     , 1     , 180   ,
    INDOFF, INDOFF, INDOFF, INDOFF, INDOFF, INDOFF,                         1     , 1     , 85    , 43    , 201   , INDOFF,
                                    INDOFF, INDOFF, INDOFF,         INDOFF, INDOFF, INDOFF
),

[_RAISE] = LAYOUT_split_3x6_3(
    INDOFF, 1     , 169   , 85    , 180   , INDOFF,                         148   , INDOFF, INDOFF, 106   , INDOFF, INDOFF,
    INDOFF, 169   , 169   , 169   , INDOFF, INDOFF,                         148   , INDOFF, 106   , 106   , 106   , 180   ,
    INDOFF, INDOFF, INDOFF, INDOFF, INDOFF, INDOFF,                         148   , INDOFF, 85    , 43    , 201   , INDOFF,
                                    INDOFF, INDOFF, INDOFF,         106   , INDOFF, 106
),

[_ADJUST] = LAYOUT_split_3x6_3(
    1     , 21    , INDOFF, INDOFF, INDOFF, 201   ,                         INDOFF, INDOFF, INDIGN, INDIGN, INDIGN, INDIGN,
    INDOFF, 1     , 201   , 148   , 106   , 169   ,                         169   , INDOFF, INDIGN, INDIGN, INDIGN, INDIGN,
    INDIGN, 1     , 201   , 148   , 106   , 1     ,                         1     , INDOFF, INDIGN, INDIGN, INDIGN, INDIGN,
                                    INDOFF, INDOFF, INDOFF,         INDOFF, INDOFF, INDOFF
)
};
// clang-format on
