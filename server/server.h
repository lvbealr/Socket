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

const size_t MAX_MSG_SIZE = 100;

enum serverError {
    NO_SERVER_ERROR       = 0,
    NO_SOCKET_INITIALIZED = 1,
    FAILED_TO_BIND        = 2,
    FAILED_TO_LISTEN      = 3,
    FAILED_TO_ACCEPT      = 4,
    MSG_BUFFER_ERROR      = 5,
    TERMINATE             = 6
};

typedef int SERVER_ERROR;
typedef int SOCKET;

// FUNCTION PROTOTYPES //
SERVER_ERROR initializeSocket(int domain,      int       type,    int           protocol);
SERVER_ERROR bindingSocket   (int serverDescr, sockaddr *myAddr,  size_t        addrLen);
SERVER_ERROR listenServer    (int serverDescr, int       backLog);
SERVER_ERROR acceptClient    (int serverDescr, sockaddr *myAddr,  unsigned int *addrLen);
SERVER_ERROR receiveMessage  (int clientDescr, char     **buffer,  size_t        bufferSize, int flags);
// FUNCTION PROTOTYPES //

#endif // SERVER_H_