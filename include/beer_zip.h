#include <vector>

// ======================= Beer Zip Macros ==========================
#define LOOK_BUF 0x04
#define WIN_BUF  0x06

#define BEERZIP_FAILURE(X) if (X == BEERZIP_FAIL)
// ==================================================================

typedef u8 unsigned char;

struct LZ77_t {
	int dist;  // distance
	int len;   // length
	char data; // data
};

struct LZ77_Buffer_t {
	u8 buffer[WIN_BUF + LOOK_BUFF];
	// 0x00 - 0x05 : Window buff
	// 0x06 - 0x09 : lookahead buff

	struct LZ77_Buffer_t operator<<(unsigned int n) {
		struct LZ77_Buffer_t lz_buffer;
		lz_buffer = *this;
		for(int i = n; i < WIN_BUF + LOOK_BUF; i++)
			lz_buffer[i-n] = lz_buffer[i];
		return lz_buffer;
	}
};

enum BeerZipStatus_t {
	BEERZIP_FAIL = -1,
	BEERZIP_SUCCESS
};

BeerZipStatus_t beerSockZip(const char*, std::vector<struct LZ77_Buffer_t>&);
