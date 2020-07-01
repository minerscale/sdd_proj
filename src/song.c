#include "song.h"
unsigned char sound_data[] = {
  0x00, 0x03, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x0c, 0x00, 0x00, 0x00, 0x3f, 0x01, 0x0d, 0x00, 0x00, 0x60, 0x40,
  0x01, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x40,
  0x03, 0x03, 0x00, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00, 0x00, 0x80, 0x3d,
  0x01, 0x04, 0x00, 0x00, 0x00, 0x3d, 0x02, 0x04, 0x00, 0x00, 0x00, 0x3d,
  0x03, 0x04, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x05, 0x00, 0x00, 0x00, 0x40,
  0x00, 0x08, 0x00, 0x00, 0x16, 0x43, 0x00, 0x01, 0x00, 0x00, 0x80, 0x3f,
  0x01, 0x01, 0x00, 0x00, 0x20, 0x40, 0x02, 0x01, 0x00, 0x00, 0xc0, 0x40,
  0x03, 0x01, 0x00, 0x00, 0x80, 0x40, 0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x40,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0x40, 0x40,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40,
  0x02, 0x01, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x09, 0x00, 0x00, 0x90, 0x3f,
  0x00, 0x01, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x01, 0x00, 0x00, 0x20, 0x40,
  0x02, 0x01, 0x00, 0x00, 0xc0, 0x40, 0x03, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x40, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40, 0x01, 0x01, 0xab, 0xaa, 0x2a, 0x40,
  0x02, 0x01, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x09, 0x9a, 0x99, 0x19, 0x3f,
  0x00, 0x01, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x01, 0x00, 0x00, 0xa0, 0x40,
  0x02, 0x01, 0x00, 0x00, 0xc0, 0x40, 0x03, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x40, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40, 0x01, 0x01, 0x00, 0x00, 0xc0, 0x40,
  0x02, 0x01, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x09, 0x00, 0x00, 0xc0, 0x3f,
  0x00, 0x01, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x02, 0x01, 0x00, 0x00, 0xa0, 0x40, 0x03, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x40, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40, 0x01, 0x01, 0x00, 0x00, 0x40, 0x40,
  0x02, 0x01, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x01, 0x00, 0x00, 0x80, 0x3f,
  0x01, 0x01, 0x00, 0x00, 0x20, 0x40, 0x02, 0x01, 0x00, 0x00, 0xc0, 0x40,
  0x03, 0x01, 0x00, 0x00, 0x80, 0x40, 0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x40,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0x40, 0x40,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40,
  0x02, 0x01, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x09, 0x00, 0x00, 0x90, 0x3f,
  0x00, 0x01, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x01, 0x00, 0x00, 0x20, 0x40,
  0x02, 0x01, 0x00, 0x00, 0xc0, 0x40, 0x03, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x40, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40, 0x01, 0x01, 0xab, 0xaa, 0x2a, 0x40,
  0x02, 0x01, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x09, 0x9a, 0x99, 0x19, 0x3f,
  0x00, 0x01, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x01, 0x00, 0x00, 0xa0, 0x40,
  0x02, 0x01, 0x00, 0x00, 0xc0, 0x40, 0x03, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x40, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40, 0x01, 0x01, 0x00, 0x00, 0xc0, 0x40,
  0x02, 0x01, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x09, 0x00, 0x00, 0xc0, 0x3f,
  0x00, 0x01, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x02, 0x01, 0x00, 0x00, 0xa0, 0x40, 0x03, 0x01, 0x00, 0x00, 0x80, 0x40,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x40, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x80, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xa0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0xe0, 0x40, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3f,
  0x00, 0x0b, 0x00, 0x00, 0x00, 0x41, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x0a, 0x00, 0x00, 0x50, 0x41,
  0x00, 0x07, 0x00, 0x00, 0x00, 0x00
};
unsigned int sound_data_len = 1206;