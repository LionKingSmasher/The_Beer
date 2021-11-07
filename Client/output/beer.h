#include <arpa/inet.h>
#include <fcntl.h>
#include <beer_sock.h>
#include <beer_zip.h>

#define BeerSuccess(X) if (X == 0)
#define BeerFail(X)    if (X == -1)

class Beer : public BeerSock, BeerZip {
private:
    int fd; // file descriptor
    const char *ip;
public:
    Beer(const char* ip, int port) : BeerSock(ip, port) {};
    virtual ~Beer();
    virtual BeerZipStatus_t compress(const char*);
    virtual BeerZipStatus_t compress(std::string);
    virtual BeerZipStatus_t uncompress(const char*);
    virtual BeerZipStatus_t uncompress(std::string);
};
