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

#include <string.h>
#include <beer_zip.h>

static void init_lz77_buffer(const char * str, struct LZ77_Buffer_t* lz77_buffer){
	for(short i = 0; i < WIN_BUF; i++)
		lz77_buffer->buffer[i + WIN_BUF] = str[i];
}

BeerZipStatus_t beerSockZip(const char* str, std::vector<struct LZ77_t>& lz77_vector){
	struct LZ77_Buffer_t __buffer;
	init_lz77_buffer(str, &__buffer);
	for(int i = 0; i < strlen(str); i ++){
		
	}
	return BEERZIP_SUCCESS;
}
