#include <beer.h>
#include <time.h>
#include <string.h>

#define STB_HEADER_MAGIC_NUMBER 0x13631AD2U

typedef unsigned long  u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

#define COMPRESS_TYPE_STB 0x01

typedef struct {
    u32 magicNumber;  // magic
    u32 file_size;    // file size
    u8 compress_type; // compress_type
} TB_Header_t;

static void print_all_vector(std::vector<struct LZ77_t> __a){
    for(LZ77_t i : __a){
        printf("Data: ");
    }
}

static u8* stb_vector_to_string(std::vector<struct LZ77_t> vector, int fd){
    u32 offset = 0;
    u8* result = (u8*)malloc(sizeof(u8) * 3);
    for(LZ77_t i : vector){
        printf("%d %d %d\n", i.dist, i.len, i.data);
        result[0] = i.dist;
        result[1] = i.len;
        result[2] = i.data;
        write(fd, result, 3);
    }
    return result;
}

static inline struct LZ77_t stb_string_to_vector(u8* buffer){
    struct LZ77_t __lz77;
    __lz77.dist = buffer[0];
    __lz77.len  = buffer[1];
    __lz77.data = buffer[2];
    return __lz77;
}

Beer::~Beer(){

}

BeerZipStatus_t Beer::compress(const char* str){
    TB_Header_t stb_header;
    std::vector<struct LZ77_t> lz77_vector;
    u8 buffer[513];
    ssize_t size;
    u32 file_size = 0;
    int read_fd = open(str, O_RDONLY);
    int fd = open("lz77_result.stb", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while((size = read(read_fd, buffer, 513)) != 0){
        BEERZIP_FAILURE(beerSockZip(buffer, lz77_vector, size)){
            return BEERZIP_FAIL;
        }
        file_size += (u32)size;
        printf("Do...! %d\n", file_size);
    }
    stb_header.magicNumber = STB_HEADER_MAGIC_NUMBER;
    stb_header.file_size = file_size;
    stb_header.compress_type = COMPRESS_TYPE_STB;
    write(fd, (TB_Header_t*)&stb_header, sizeof(stb_header));
    stb_vector_to_string(lz77_vector, fd);
    // write(fd, stb_header.file, lz77_vector.size() * 3);
    close(fd);
    close(read_fd);
    return BEERZIP_SUCCESS;
}

BeerZipStatus_t Beer::compress(std::string str){
    return compress(str.c_str());
}

BeerZipStatus_t Beer::uncompress(const char* str){
    TB_Header_t stb_header;
    std::vector<struct LZ77_t> lz77_vector;
    u8 buffer[3];
    u8 write_buffer[513];
    ssize_t size;
    u32 file_size = 0;
    u32 cnt = 0;
    u64 offset = 0;
    int read_fd = open(str, O_RDONLY);
    int fd = open("lz77_decompress.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    read(read_fd, (TB_Header_t*)&stb_header, sizeof(stb_header));
    if(stb_header.magicNumber != STB_HEADER_MAGIC_NUMBER)
        return BEERZIP_FAIL;
    while((size = read(read_fd, buffer, 3)) != 0)
        lz77_vector.push_back(stb_string_to_vector(buffer));

    for(LZ77_t i : lz77_vector)
        printf("%d %d %c\n", i.dist, i.len, i.data);
    
    for(int i = 0; cnt > 0 || i == 0;){
        cnt = beerSockUnZip(write_buffer, lz77_vector, i, &offset);
        // printf("Chk: %d %d...\n", i, lz77_vector.size());
        write(fd, write_buffer, offset);
        memset(write_buffer, 0, 513);
        i+=cnt;
    }
    return BEERZIP_SUCCESS;
}

BeerZipStatus_t Beer::uncompress(std::string str){
    return uncompress(str.c_str());
}