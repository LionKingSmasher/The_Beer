#include <arpa/inet.h>
#include <fcntl.h>
#include <beer_sock.h>
#include <beer_zip.h>

#define BeerSuccess(X) if (X == 0)
#define BeerFail(X)    if (X == -1)

class Beer {
};
