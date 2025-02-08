#include "client.h"

#define INITIALIZE_SOCKET_INFO_(socketInfoPtr, sunFamily) do {                \
    if (argc == 1) {                                                          \
        initializeSocketInfo(socketInfoPtr, sunFamily, "./socket");           \
    }                                                                         \
                                                                              \
    else {                                                                    \
        initializeSocketInfo(socketInfoPtr, sunFamily, argv[--argc]);         \
    }                                                                         \
} while (0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    /* Socket Initializing*/
    SOCKET clientDescr = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);

    /* Connecting */
    sockaddr_un socketInfo = {};
    INITIALIZE_SOCKET_INFO_(&socketInfo, AF_UNIX);

    clientError connectionStatus  = setConnection(clientDescr, (sockaddr *) &socketInfo, sizeof(socketInfo));

    /* Interaction */
    clientError interactionStatus = socketInteractor(clientDescr, STDIN_FILENO);

    return interactionStatus;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* ======================================== FUNCTIONS DEFINITIONS  ============================================= */
/* SOCKET      initializeSocket(int domain, int type, int protocol) ============================================ */
/* clientError initializeSocketInfo(sockaddr_un *socketInfo, unsigned short sunFamily, const char *sunPath) ==== */
/* clientError setConnection(int clientDescr, sockaddr *socketInfo, size_t size) =============================== */
/* clientError socketInteractor(int clientDescr, int inputStream) ============================================== */
/* ============================================================================================================= */

SOCKET initializeSocket(int domain, int type, int protocol) {
    SOCKET clientDescr = socket(domain, type, protocol);
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    customAssert(clientDescr != ERROR, NO_SOCKET_INITIALIZED);

    ON_DEBUG(customPrint(green, underlined, bgDefault,
                         "SOCKET INITIALIZED: [%d] (descr)\n", clientDescr);)

    return clientDescr;
}

clientError initializeSocketInfo(sockaddr_un *socketInfo, unsigned short sunFamily, const char *sunPath) {
    customAssert(socketInfo != NULL, SOCKET_INFO_NULL_PTR);
    customAssert(sunPath    != NULL, SUN_PATH_NULL_PTR);

    socketInfo->sun_family = sunFamily;

    strncpy(socketInfo->sun_path, sunPath, strlen(sunPath));

    ON_DEBUG(customPrint(yellow, normal, bgDefault,
                         "sockaddr_un.sun_family = [%d]\nsockaddr_un.sun_path = [%s]\n",
                         socketInfo->sun_family, socketInfo->sun_path);)

    return NO_CLIENT_ERROR;
}

clientError setConnection(int clientDescr, sockaddr *socketInfo, size_t size) {
    customPrint(lightblue, bold, bgDefault,
                "Attempting to connect...\n");

    STATUS connectionStatus = connect(clientDescr, socketInfo, size);

    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "CONNECTION STATUS: [%d]\n", connectionStatus));

    customAssert(connectionStatus == CONNECTION_SUCCEED, CONNECTION_ERROR);

    customPrint(green, bold, bgDefault,
                "Connected!\n\n");

    return NO_CLIENT_ERROR;
}

clientError socketInteractor(int clientDescr, int inputStream) {
    char *msgBuffer = (char *)calloc(MAX_MSG_SIZE, sizeof(char));
    customAssert(msgBuffer != NULL, MSG_BUFFER_ERROR);

    while (strcmp((const char *) msgBuffer, "END")) {
        memset(msgBuffer, 0, MAX_MSG_SIZE);

        /* Read Message */
        customPrint(purple, bold, bgDefault, ">> ");

        ssize_t readSTDIN = read(inputStream, msgBuffer, MAX_MSG_SIZE);
        ON_DEBUG(customPrint(red, bold, bgDefault,
                             "errno status: [%d] on line %d\n", errno, __LINE__));
        ON_DEBUG(customPrint(green, bold, bgDefault,
                             "READ MESSAGE STATUS: [%d]\n", inputStream));

        /* Send Message */
        STATUS sendStatus = send(clientDescr, (const char *) msgBuffer, MAX_MSG_SIZE, 0);
        ON_DEBUG(customPrint(red, bold, bgDefault,
                             "errno status: [%d] on line %d\n", errno, __LINE__));
        ON_DEBUG(customPrint(green, bold, bgDefault,
                             "SEND MESSAGE STATUS: [%d]\n", sendStatus));

        msgBuffer[strlen(msgBuffer) - 1] = '\0';
    }

    return NO_CLIENT_ERROR;
}