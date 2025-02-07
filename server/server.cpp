#include "server.h"

typedef int SERVER_ERROR;

SERVER_ERROR main() {
    /*  ======================================= INITIALIZE SOCKET ================================================== */
    SERVER_ERROR serverDescr = socket(AF_UNIX, SOCK_STREAM, 0); // (AF_UNIX = use UNIX I/O)
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    customAssert(serverDescr != -1, NO_SOCKET_INITIALIZED);

    ON_DEBUG(customPrint(green, underlined, bgDefault,
                         "SOCKET INITIALIZED: [%d] (descr)\n", serverDescr);)
    /*  ============================================================================================================ */

    /*  ========================================= SOCKET BINDING =================================================== */
    sockaddr_un socketInfo = {};

    socketInfo.sun_family = AF_UNIX;
    strncpy(socketInfo.sun_path, "./socketHere", 108); // TODO temp file? by time idk (-__-)

    // struct sockaddr_un {
    //    sa_family_t sun_family;               /* AF_UNIX */              /* sa_family_t = unsigned short int */
    //    char        sun_path[108];            /* имя пути */
    // };

    ON_DEBUG(customPrint(yellow, normal, bgDefault,
                         "sockaddr_un.sun_family = [%d]\nsockaddr_un.sun_path = [%s]\n",
                         socketInfo.sun_family, socketInfo.sun_path);)

    SERVER_ERROR bindingStatus = bind(serverDescr, (sockaddr *) &socketInfo, (int) sizeof(socketInfo));
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "BINDING STATUS: [%d]\n", bindingStatus));

    customAssert(bindingStatus != -1, FAILED_TO_BIND);
    /*  ============================================================================================================ */

    /*  ============================================ LISTENING ===================================================== */
    SERVER_ERROR listenStatus = listen(serverDescr, 1); // TODO 1?
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "LISTEN STATUS: [%d]\n", listenStatus));

    customAssert(listenStatus != -1, FAILED_TO_LISTEN);
    /*  ============================================================================================================ */

    /*  ========================================== ACCEPT CLIENT =================================================== */
    SERVER_ERROR clientDescr = accept(serverDescr, NULL, NULL);
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "Client Descriptor: [%d]\n", clientDescr));
    customAssert(clientDescr != -1, FAILED_TO_ACCEPT);
    /*  ============================================================================================================ */

    /*  ========================================== RECEIVING MSG =================================================== */
    char *msgBuffer = (char *)calloc(MAX_MSG_SIZE, sizeof(char));
    customAssert(msgBuffer != NULL, MSG_BUFFER_ERROR);

    SERVER_ERROR recvStatus = recv(clientDescr, msgBuffer, MAX_MSG_SIZE, 0);
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "RECEIVING MSG STATUS: [%d]\n", recvStatus));

    customPrint(purple, bold, bgDefault,
                "\nMESSAGE: ");
    customPrint(white, bold, bgDefault,
                "%s\n\n", msgBuffer);
    /*  ============================================================================================================ */

    // TODO CLOSE SOCKET

    system("rm -rf socketHere"); // TODO

    return NO_SERVER_ERROR;
}