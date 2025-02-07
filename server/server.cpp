#include "server.h"

#define INITIALIZE_SOCKET_INFO_(socketInfoPtr, sunFamily) {           \
    if (argc == 1) {                                                  \
        initializeSocketInfo(socketInfoPtr, sunFamily, "./socket");   \
    }                                                                 \
                                                                      \
    else {                                                            \
        initializeSocketInfo(socketInfoPtr, sunFamily, argv[--argc]); \
    }                                                                 \
}

int main(int argc, char *argv[]) {
    /* Socket Initializing */
    SOCKET serverDescr = socket(AF_UNIX, SOCK_STREAM, 0);

    /* Socket Binding */
    sockaddr_un socketInfo = {};
    INITIALIZE_SOCKET_INFO_(&socketInfo, AF_UNIX);

    STATUS bindingStatus = bindSocket(serverDescr, (sockaddr *) &socketInfo, (int) sizeof(socketInfo));

    /* Listening */
    STATUS listenStatus = listenServer(serverDescr, 1); // TODO 1?

    /* Interaction */
    STATUS interactStatus = socketInteractor(serverDescr, NULL, NULL, 0, &socketInfo);

    return 0;
}

/* ======================================== FUNCTIONS DEFINITIONS  ======================================================================== */
/* SOCKET      initializeSocket(int domain, int type, int protocol) ======================================================================= */
/* serverError initializeSocketInfo(sockaddr_un *socketInfo, unsigned short sunFamily, const char *sunPath) =============================== */
/* serverError bindSocket(int serverDescr, sockaddr *myAddr, size_t addrLen) ============================================================== */
/* serverError listenServer(int serverDescr, int backLog) ================================================================================= */
/* SOCKET      acceptClient(int serverDescr, sockaddr *myAddr, unsigned int *addrLen) ===================================================== */
/* serverError receiveMessage(int clientDescr, char **msgBuffer, size_t bufferSize, int flags) ============================================ */
/* serverError socketInteractor(int serverDescr, sockaddr *myAddr, unsigned int *addrLen, int flags, sockaddr_un socketInfo) ============== */
/* ======================================================================================================================================== */

SOCKET initializeSocket(int domain, int type, int protocol) {
    SOCKET serverDescr = socket(domain, type, protocol); // (AF_UNIX = use UNIX I/O)
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "Errno status: [%d] on line %d\n", errno, __LINE__));
    customAssert(serverDescr != -1, NO_SOCKET_INITIALIZED);

    ON_DEBUG(customPrint(green, underlined, bgDefault,
                         "SOCKET INITIALIZED: [%d] (descr)\n", serverDescr);)

    return serverDescr;
}

serverError initializeSocketInfo(sockaddr_un *socketInfo, unsigned short sunFamily, const char *sunPath) {
    customAssert(socketInfo != NULL, SOCKET_INFO_NULL_PTR);
    customAssert(sunPath    != NULL, SUN_PATH_NULL_PTR);

    socketInfo->sun_family = sunFamily;

    strncpy(socketInfo->sun_path, sunPath, strlen(sunPath));

    ON_DEBUG(customPrint(yellow, normal, bgDefault,
                         "sockaddr_un.sun_family = [%d]\nsockaddr_un.sun_path = [%s]\n",
                         socketInfo.sun_family, socketInfo.sun_path);)

    return NO_SERVER_ERROR;
}

serverError bindSocket(int serverDescr, sockaddr *myAddr, size_t addrLen) {
    STATUS bindingStatus = bind(serverDescr, myAddr, addrLen);
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "Errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "BINDING STATUS: [%d]\n", bindingStatus));

    customAssert(bindingStatus != -1, FAILED_TO_BIND);

    return NO_SERVER_ERROR;
}
serverError listenServer(int serverDescr, int backLog) {
    STATUS listenStatus = listen(serverDescr, backLog);
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "Errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "LISTEN STATUS: [%d]\n", listenStatus));

    customAssert(listenStatus != -1, FAILED_TO_LISTEN);

    customPrint(lightblue, bold, bgDefault, "Listening...\n");

    return NO_SERVER_ERROR;
}

SOCKET acceptClient(int serverDescr, sockaddr *myAddr, unsigned int *addrLen) {
    SOCKET clientDescr = accept(serverDescr, myAddr, addrLen);
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "CLIENT DESCRIPTOR: [%d]\n", clientDescr));
    customAssert(clientDescr != -1, FAILED_TO_ACCEPT);

    customPrint(green, bold, bgDefault,
                "Connection established!\n\n");

    return clientDescr;
}

serverError receiveMessage(int clientDescr, char **msgBuffer, size_t bufferSize, int flags) {
    STATUS recvStatus = recv(clientDescr, *msgBuffer, MAX_MSG_SIZE, 0);
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "RECEIVING MSG STATUS: [%d]\n", recvStatus));

    customPrint(purple, bold, bgDefault,
                ">> ");
    customPrint(white, bold, bgDefault,
                "%s", *msgBuffer);

    (*msgBuffer)[strlen(*msgBuffer) - 1] = '\0';

    return NO_SERVER_ERROR;
}

serverError socketInteractor(int serverDescr, sockaddr *myAddr, unsigned int *addrLen, int flags, sockaddr_un *socketInfo) {
    customAssert(socketInfo != NULL, SOCKET_INFO_NULL_PTR);

    SOCKET clientDescr = acceptClient(serverDescr, myAddr, addrLen);

    char *msgBuffer = (char *)calloc(MAX_MSG_SIZE, sizeof(char)); // TODO FREE
    customAssert(msgBuffer != NULL, MSG_BUFFER_ERROR);

    while (strcmp(msgBuffer, TERMINAL_MSG)) {
        STATUS recvStatus = receiveMessage(clientDescr, &msgBuffer, MAX_MSG_SIZE, flags);
    }

    customPrint(red, bold, bgDefault,
                "\nConnection lost (terminal message was received)!\n");

    close(serverDescr);
    close(clientDescr);

    sprintf(msgBuffer, "rm %s", socketInfo->sun_path);

    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "%s", socketInfo->sun_path);)

    system(msgBuffer);
    FREE_(msgBuffer);

    return NO_SERVER_ERROR;
}