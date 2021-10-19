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
//============ Standard =============
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//============== POSIX ==============
#include <fcntl.h>
#include <unistd.h>
//============= Custom ==============
#include <beer_zip.h>
//===================================

static inline void beerSockErrorMsg(const char *msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
}

static void init_lz77_buffer(const unsigned char * str, struct LZ77_Buffer_t* lz77_buffer){
	for(short i = 0; i < WIN_BUF; i++)
		lz77_buffer->buffer[i] = 0;
	for(short i = 0; i < LOOK_BUF; i++)
		lz77_buffer->buffer[i + WIN_BUF] = str[i];
}

static void clear_lz77_buffer(struct LZ77_Buffer_t* lz77_buffer){
	for(short i = 0; i <= MAX_BUF_SIZE; i++)
		lz77_buffer->buffer[i] = 0;
}

static inline void lz77_buffer_push_back(const unsigned char * str, struct LZ77_Buffer_t* lz77_buffer, int pos, long size){
	*lz77_buffer <<= 1;
	lz77_buffer->buffer[MAX_BUF_SIZE] = pos < size ? str[pos] : 0;
}

static struct LZ77_t lz77_search(struct LZ77_Buffer_t* lz77_buffer){
	int __point = POINT_BUF;
	struct LZ77_t __lz77;
	__lz77 = {
		0,
		0,
		lz77_buffer->buffer[POINT_BUF],
	};
	for(u8 i = 0; i < WIN_BUF; i++){
		if(lz77_buffer->buffer[POINT_BUF] == lz77_buffer->buffer[i]){
			u8 j = 0;
			while(lz77_buffer->buffer[POINT_BUF + j] == lz77_buffer->buffer[i + j]) 
				j++;
			if(j < __lz77.len)
				continue;
			__lz77 = {
				(u8)(POINT_BUF - i),
				(u8)((i + j > WIN_BUF || lz77_buffer->buffer[POINT_BUF + j] == 0) ? j - 1 : j),
			};
			__lz77.data = lz77_buffer->buffer[POINT_BUF + __lz77.len];
			i += __lz77.len;
		}
	}
	__lz77.dist = (__lz77.len == 0) ? 0 : __lz77.dist;
	return __lz77;
}

static BeerZipStatus_t beerZipWrite(int fd){
	return BEERZIP_SUCCESS;
}

static inline void see_all_elements(const unsigned char * arr){
	for(int i = 0; i <= MAX_BUF_SIZE; i++){
		printf("%c ", arr[i]);
	}
	printf("\n");
}

unsigned long beerSockUnZip(unsigned char* str, std::vector<struct LZ77_t>& lz77_vector, long offset, unsigned long* size){
	struct LZ77_Buffer_t __lz77_buffer;
	long string_offset = 0;
	long i = 0;
	clear_lz77_buffer(&__lz77_buffer);
	for(i = offset; string_offset < 513 && i < lz77_vector.size(); i++){
		if(lz77_vector[i].len != 0){
			for(int j = 0; j < lz77_vector[i].len; j++){
				str[string_offset + j] = __lz77_buffer.buffer[POINT_BUF - lz77_vector[i].dist];
				__lz77_buffer.buffer[POINT_BUF] = __lz77_buffer.buffer[POINT_BUF - lz77_vector[i].dist];
				__lz77_buffer <<= 1;
			}
		}
		__lz77_buffer.buffer[POINT_BUF] = lz77_vector[i].data;
		str[string_offset + lz77_vector[i].len] = __lz77_buffer.buffer[POINT_BUF];
		string_offset += lz77_vector[i].len + 1;
		__lz77_buffer <<= 1;
		printf("%d %d\n", i, string_offset);
		// see_all_elements(str);
	}
	*size = string_offset;
	return i - offset;
}

BeerZipStatus_t beerSockZip(const unsigned char* str, std::vector<struct LZ77_t>& lz77_vector, long size){
	struct LZ77_Buffer_t __buffer;
	init_lz77_buffer(str, &__buffer); // Initialize the buffer
	for(int i = 0; i < size; i++){
		struct LZ77_t lz77_data;
		lz77_data = lz77_search(&__buffer);
		// printf("data = %c dist = %d len = %d\n", lz77_data.data, lz77_data.dist, lz77_data.len);
		for(int j = i; j <= i + lz77_data.len; j++)
			lz77_buffer_push_back(str, &__buffer, j + LOOK_BUF, size);
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
	BEERZIP_FAILURE(beerSockZip((unsigned char*)str, this->lz77_buffer, strlen(str))){
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