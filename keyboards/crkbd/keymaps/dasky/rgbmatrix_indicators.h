#define LEFT_FIRST_UNDERGLOW 0
#define LEFT_LAST_UNDERGLOW 5
#define LEFT_FIRST_RGB 6
#define LEFT_LAST_RGB 26

#define RIGHT_FIRST_UNDERGLOW 27
#define RIGHT_LAST_UNDERGLOW 32
#define RIGHT_FIRST_RGB 33
#define RIGHT_LAST_RGB 53

const uint8_t PROGMEM gaming_left[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0};

const uint8_t PROGMEM gaming_right[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255};

const uint8_t PROGMEM lower_left[] = {0, 0, 44, 44, 44, 44, 0, 0, 0, 0, 44, 44, 44, 44, 0, 0, 44, 44, 0, 0, 0};

const uint8_t PROGMEM lower_right[] = {0, 1, 1, 1, 1, 1, 1, 0, 0, 85, 1, 1, 1, 1, 43, 201, 1, 1, 0, 180, 0};

const uint8_t PROGMEM raise_left[] = {0, 0, 0, 0, 180, 0, 0, 0, 0, 0, 169, 85, 169, 169, 0, 0, 169, 1, 0, 0, 0};

const uint8_t PROGMEM raise_right[] = {169, 127, 127, 127, 0, 0, 0, 0, 169, 85, 169, 0, 169, 169, 43, 201, 169, 0, 0, 180, 0};

// 19,18,13,12, 5, 4           4, 5,12,13,18,19
// 20,17,14,11, 6, 3           3, 6,11,14,17,20
// 21,16,15,10, 7, 2           2, 7,10,15,16,21
//             9, 8, 1     1, 8, 9

_Static_assert(sizeof(gaming_left) == 21, "gaming_left wrong size");
_Static_assert(sizeof(gaming_right) == 21, "gaming_right wrong size");
_Static_assert(sizeof(lower_left) == 21, "lower_left wrong size");
_Static_assert(sizeof(lower_right) == 21, "lower_right wrong size");
_Static_assert(sizeof(raise_left) == 21, "raise_left wrong size");
_Static_assert(sizeof(raise_right) == 21, "raise_right wrong size");
