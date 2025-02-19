#ifndef CLIENT_H_
#define CLIENT_H_

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "customWarning.h"
#include "colorPrint.h"

#ifndef NDEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...)
#endif

const size_t MAX_MSG_SIZE       = 100;

const int    DEFAULT_PROTOCOL   = 0;

const int    ERROR              = -1;
const int    CONNECTION_SUCCEED = 0;

enum clientError {
    NO_CLIENT_ERROR       = 0,
    NO_SOCKET_INITIALIZED = 1,
    MSG_BUFFER_ERROR      = 2,
    CONNECTION_ERROR      = 3,
    SOCKET_INFO_NULL_PTR  = 4,
    SUN_PATH_NULL_PTR     = 5,
};

typedef int STATUS;
typedef int SOCKET;

// FUNCTION PROTOTYPES //
SOCKET      initializeSocket    (int          domain,      int            type,             int    protocol);
clientError initializeSocketInfo(sockaddr_un *socketInfo,  unsigned short sunFamily,  const char  *sunPath);
clientError setConnection       (int          clientDescr, sockaddr      *socketInfo,       size_t size);
clientError interactBySocket    (int          clientDescr, int            inputStream);
// FUNCTION PROTOTYPES //

#endif // CLIENT_H_