#define Logo_width 128
#define Logo_height 32
const uint8_t Logo_bits[] PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0xff,0xff,0x7f,0xfe,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xff,0xff,0x1f,0xfc,0xff,0xff,0xff,0xff,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xdf,0xf9,
 0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0xff,0xff,0xdf,0x79,0xbf,0x9b,0xff,0xff,0xfc,0xff,0xff,0x00,
 0x00,0x00,0x00,0x00,0xff,0xff,0xdf,0x9c,0xce,0x81,0xff,0xff,
 0xfc,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x1f,0xcc,
 0x26,0xf3,0xff,0xff,0xfc,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
 0xff,0xff,0x3f,0x19,0x26,0xf7,0xff,0xff,0xf8,0xff,0x7f,0x00,
 0x00,0x00,0x00,0x00,0xff,0xff,0xdf,0x8b,0xc7,0xf7,0xff,0xff,
 0xe0,0xff,0x3f,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xdf,0x93,
 0xc7,0xf7,0xff,0xff,0x00,0x80,0x1f,0x00,0x00,0x00,0x00,0x00,
 0xff,0xff,0xff,0x3d,0x0c,0xf2,0xff,0xff,0x00,0xc0,0x0f,0xf0,
 0xff,0x01,0xff,0x0f,0xff,0xff,0x3f,0x7c,0x7c,0xf7,0xff,0xff,
 0x00,0xe0,0x07,0xf8,0xff,0x83,0xff,0x1f,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0x00,0xf0,0x03,0xfc,0xff,0xc7,0xff,0x1f,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xf8,0x01,0xfc,
 0xff,0xc7,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0x00,0xfc,0x00,0x7e,0x80,0xef,0x03,0x7e,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0x00,0x7e,0x00,0x1e,0x00,0xef,0x01,0x78,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0x00,0x0e,
 0x00,0xef,0x00,0x70,0xff,0xff,0xdf,0xff,0x3f,0xff,0xff,0xff,
 0x80,0x1f,0x00,0x0e,0x00,0xef,0x00,0x70,0xff,0xff,0xda,0xff,
 0x9f,0xff,0xff,0xff,0xc0,0x0f,0x00,0x0e,0x00,0xef,0x00,0x70,
 0xff,0x7f,0xc8,0xff,0xbf,0xf3,0xff,0xff,0xe0,0x07,0x00,0x1e,
 0x00,0xef,0x00,0x70,0xff,0x3f,0xcf,0xff,0x3f,0xf7,0xff,0xff,
 0xf0,0xff,0x7f,0xfe,0x7f,0xef,0x00,0x70,0xff,0x7f,0xdf,0xff,
 0x9f,0xff,0xfe,0xff,0xf8,0xff,0xff,0xfc,0x7f,0xef,0x00,0x70,
 0xff,0x7f,0x0e,0xbb,0x03,0x77,0xf0,0xff,0xfc,0xff,0xff,0xf8,
 0x7f,0xef,0x00,0x70,0xff,0xff,0xac,0x99,0xbb,0x73,0xe7,0xff,
 0xfc,0xff,0xff,0xf8,0x7f,0xee,0x00,0x70,0xff,0xff,0xe9,0x99,
 0x3d,0x3b,0xcf,0xff,0xf8,0xff,0xff,0xf0,0x7f,0xcc,0x00,0x30,
 0xff,0xff,0xeb,0xd9,0x3d,0x7b,0xef,0xff,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xff,0xff,0xcb,0x9d,0x49,0x32,0xf7,0xff,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x18,0x03,
 0x61,0x46,0xf0,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0xff,0xff,0x9c,0x97,0xff,0xe7,0xfa,0xff,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
  };


#define beer_width  32
#define beer_height 32
//static unsigned char beer_bits[] = {
//  0x00,0x1c,0x60,0x33,0xd0,0x40,0x90,0x60,0x30,0x3f,0xe0,0x3f,
// 0xfc,0x3f,0xf6,0x35,0x26,0x35,0x26,0x35,0x26,0x35,0x26,0x35,
// 0xe6,0x3f,0xfc,0x3f,0xe0,0x3f,0xe0,0x1f};
static unsigned char beer_bits[] = {
   0x00,0x00,0xf0,0x03,0x00,0x00,0xf0,0x03,0x00,0x3c,0x0f,0x0f,
 0x00,0x3c,0x0f,0x0f,0x00,0xf3,0x00,0x30,0x00,0xf3,0x00,0x30,
 0x00,0xc3,0x00,0x30,0x00,0xc3,0x00,0x30,0x00,0x0f,0xff,0x0f,
 0x00,0x0f,0xff,0x0f,0x00,0xfc,0x03,0x0c,0x00,0xfc,0x03,0x0c,
 0xf0,0x0f,0x00,0x0c,0xf0,0x0f,0x00,0x0c,0x3c,0x0f,0x33,0x0c,
 0x3c,0x0f,0x33,0x0c,0x0c,0x0c,0x33,0x0c,0x0c,0x0c,0x33,0x0c,
 0x0c,0x0c,0x33,0x0c,0x0c,0x0c,0x33,0x0c,0x0c,0x0c,0x33,0x0c,
 0x0c,0x0c,0x33,0x0c,0x0c,0x0c,0x33,0x0c,0x0c,0x0c,0x33,0x0c,
 0x3c,0x0c,0x33,0x0c,0x3c,0x0c,0x33,0x0c,0xf0,0x0f,0x00,0x0c,
 0xf0,0x0f,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,
 0x00,0xfc,0xff,0x03,0x00,0xfc,0xff,0x03};
