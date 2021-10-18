#include <vector>
#include <iostream>

// ======================= Beer Zip Macros ==========================
#define LOOK_BUF  0x06
#define WIN_BUF   0x08
#define POINT_BUF WIN_BUF
#define MAX_BUF_SIZE LOOK_BUF + WIN_BUF - 1

#define BEERZIP_FAILURE(X) if (X == BEERZIP_FAIL)
#define BEERZIP_SUCCESS(X) if (X == BEERZIP_SUCCESS)
// ==================================================================

typedef unsigned char u8;

struct LZ77_t {
	int dist;  // distance
	int len;   // length
	u8  data;  // data
};

struct LZ77_Buffer_t {
	u8 buffer[WIN_BUF + LOOK_BUF];
	// 0x00 - WIN_BUF : Window buff
	// (WIN_BUF + 1) - LOOK_BUF : lookahead buff

	struct LZ77_Buffer_t operator<<(unsigned int n) {
		struct LZ77_Buffer_t lz_buffer;
		lz_buffer = *this;
		for(int i = n; i < WIN_BUF + LOOK_BUF; i++)
			lz_buffer.buffer[i-n] = lz_buffer.buffer[i];
		return lz_buffer;
	}

	struct LZ77_Buffer_t operator<<=(unsigned int n){
		*this = *this << n;
		return *this;
	}

	struct LZ77_Buffer_t operator>>(unsigned int n){
		struct LZ77_Buffer_t lz_buffer;
		lz_buffer = *this;
		for(int i = MAX_BUF_SIZE - 1; i > n; i--)
			lz_buffer.buffer[i+n] = lz_buffer.buffer[i];
		return lz_buffer;
	}
};

enum BeerZipStatus_t {
	BEERZIP_FAIL = -1,
	BEERZIP_SUCCESS
};

BeerZipStatus_t beerSockZip(const char*, std::vector<struct LZ77_t>&);

class BeerZip{
protected:
	std::vector<struct LZ77_t> lz77_buffer;
public:
	BeerZip();
	virtual ~BeerZip();
	virtual BeerZipStatus_t compress(const char*);
	virtual BeerZipStatus_t compress(std::string);
	virtual BeerZipStatus_t uncompress(const char*);
	virtual BeerZipStatus_t uncompress(std::string);
};