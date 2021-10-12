/*
 *      The Beer Zip Header
 *
 *
 *  Filename: beer_zip.cc
 *  Author:   Shin Hyun-Kyu
 *  Update:   2021-10-05
 *  Description: It is Beer's zip function file
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <beer_zip.h>

static inline void beerSockErrorMsg(const char *msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
}

static void init_lz77_buffer(const char * str, struct LZ77_Buffer_t* lz77_buffer){
	for(short i = 0; i < WIN_BUF; i++)
		lz77_buffer->buffer[i] = 0;
	for(short i = 0; i < LOOK_BUF; i++)
		lz77_buffer->buffer[i + WIN_BUF] = str[i];
}

static inline void lz77_buffer_push_back(const char * str, struct LZ77_Buffer_t* lz77_buffer, int pos){
	*lz77_buffer <<= 1;
	lz77_buffer->buffer[MAX_BUF_SIZE] = pos < strlen(str) ? str[pos] : 0;
}

static struct LZ77_t lz77_search(struct LZ77_Buffer_t* lz77_buffer){
	int __point = POINT_BUF;
	struct LZ77_t __lz77;
	__lz77 = {
		0,
		0,
		lz77_buffer->buffer[POINT_BUF],
	};
	for(int i = 0; i < WIN_BUF; i++){
		if(lz77_buffer->buffer[POINT_BUF] == lz77_buffer->buffer[i]){
			int j = 0;
			while(lz77_buffer->buffer[POINT_BUF + j] == lz77_buffer->buffer[i + j]) 
				j++;
			if(j < __lz77.len)
				continue;
			__lz77 = {
				POINT_BUF - i,
				(i + j > WIN_BUF || lz77_buffer->buffer[POINT_BUF + j] == 0) ? j - 1 : j,
			};
			__lz77.data = lz77_buffer->buffer[POINT_BUF + __lz77.len];
			i += __lz77.len;
		}
	}
	return __lz77;
}

static BeerZipStatus_t beerZipWrite(int fd){
	return BEERZIP_SUCCESS;
}

BeerZipStatus_t beerSockZip(const char* str, std::vector<struct LZ77_t>& lz77_vector){
	struct LZ77_Buffer_t __buffer;
	init_lz77_buffer(str, &__buffer); // Initialize the buffer
	for(int i = 0; i < strlen(str); i++){
		struct LZ77_t lz77_data;
		lz77_data = lz77_search(&__buffer);
		// printf("data = %c dist = %d len = %d\n", lz77_data.data, lz77_data.dist, lz77_data.len);
		for(int j = i; j <= i + lz77_data.len; j++)
			lz77_buffer_push_back(str, &__buffer, j + LOOK_BUF);
		// printf("Offset: %d\n", i + WIN_BUF);
		i += lz77_data.len;
		lz77_vector.push_back(lz77_data);
	}
	return BEERZIP_SUCCESS;
}

BeerZip::BeerZip(){
}

BeerZip::~BeerZip(){
}

BeerZipStatus_t BeerZip::compress(const char* str){
	BEERZIP_FAILURE(beerSockZip(str, this->lz77_buffer)){
		beerSockErrorMsg("BeerZip Failed");
		return BEERZIP_FAIL;
	}
	return BEERZIP_SUCCESS;
}

BeerZipStatus_t BeerZip::compress(std::string str){
	return compress(str.c_str());
}

BeerZipStatus_t BeerZip::uncompress(const char* str){
	return BEERZIP_SUCCESS;
}

BeerZipStatus_t BeerZip::uncompress(std::string str){
	return uncompress(str.c_str());
}