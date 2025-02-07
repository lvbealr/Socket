#ifndef SERVER_H_
#define SERVER_H_

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "customWarning.h"
#include "colorPrint.h"

#ifndef NDEBUG
    #define ON_DEBUG(...) __VA_ARGS__
#else
    #define ON_DEBUG(...)
#endif

#define FREE_(ptr) do { \
    free(ptr);          \
    ptr = NULL;         \
} while (0)

const size_t MAX_MSG_SIZE  = 100;
const char  *TERMINAL_MSG  = "END";

enum serverError {
    NO_SERVER_ERROR       = 0,
    NO_SOCKET_INITIALIZED = 1,
    FAILED_TO_BIND        = 2,
    FAILED_TO_LISTEN      = 3,
    FAILED_TO_ACCEPT      = 4,
    MSG_BUFFER_ERROR      = 5,
    TERMINATE             = 6,
    SOCKET_INFO_NULL_PTR  = 7,
    SUN_PATH_NULL_PTR     = 8
};

typedef int STATUS;
typedef int SOCKET;

// FUNCTION PROTOTYPES //
SOCKET      initializeSocket    (int          domain,     int            type,            int   protocol);
serverError initializeSocketInfo(sockaddr_un *socketInfo, unsigned short sunFamily, const char *sunPath);

serverError bindSocket          (int serverDescr, sockaddr *myAddr,  size_t        addrLen);
serverError listenServer        (int serverDescr, int       backLog);
SOCKET      acceptClient        (int serverDescr, sockaddr *myAddr,  unsigned int *addrLen);
serverError receiveMessage      (int clientDescr, char    **buffer,  size_t        bufferSize, int flags);

serverError socketInteractor    (int serverDescr, sockaddr *myAddr,  unsigned int *addrLen,    int flags, sockaddr_un *socketInfo);
// FUNCTION PROTOTYPES //

#endif // SERVER_H_