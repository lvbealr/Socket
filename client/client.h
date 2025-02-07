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

const size_t MAX_MSG_SIZE = 100;

enum clientError {
    NO_CLIENT_ERROR       = 0,
    NO_SOCKET_INITIALIZED = 1,
    MSG_BUFFER_ERROR      = 2
};

#endif // CLIENT_H_