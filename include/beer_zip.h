#define LOOK_BUF 0x04
#define WIN_BUF  0x06

typedef u8 unsigned char;

struct LZ77_t {
	int dist;  // distance
	int len;   // length
	char data; // data
};

struct LZ77_Buffer_t {
	u8 window_buf[WIN_BUF];
	u8 look_buf[LOOK_BUF];
};
