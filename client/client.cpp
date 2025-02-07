#include "client.h"

typedef int CLIENT_ERROR;

CLIENT_ERROR main() {
    /*  ======================================= INITIALIZE SOCKET ================================================== */
    CLIENT_ERROR clientDescr = socket(AF_UNIX, SOCK_STREAM, 0); // (AF_UNIX = use UNIX I/O)
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    customAssert(clientDescr != -1, NO_SOCKET_INITIALIZED);

    ON_DEBUG(customPrint(green, underlined, bgDefault,
                         "SOCKET INITIALIZED: [%d] (descr)\n", clientDescr);)
    /*  ============================================================================================================ */

    /*  ===================================== CONNECTING TO SERVER ================================================= */
    sockaddr_un socketInfo = {};

    socketInfo.sun_family = AF_UNIX;
    strncpy(socketInfo.sun_path, "../server/socketHere", 108); // TODO

    // struct sockaddr_un {
    //    sa_family_t sun_family;               /* AF_UNIX */              /* sa_family_t = unsigned short int */
    //    char        sun_path[108];            /* имя пути */
    // };

    ON_DEBUG(customPrint(yellow, normal, bgDefault,
                         "sockaddr_un.sun_family = [%d]\nsockaddr_un.sun_path = [%s]\n",
                         socketInfo.sun_family, socketInfo.sun_path);)

    int connectingStatus = connect(clientDescr, (sockaddr *) &socketInfo, sizeof(socketInfo));
    ON_DEBUG(customPrint(red, bold, bgDefault,
                         "errno status: [%d] on line %d\n", errno, __LINE__));
    ON_DEBUG(customPrint(green, bold, bgDefault,
                         "CONNECTING STATUS: [%d]\n", connectingStatus));
    /*  ============================================================================================================ */

    char *msgBuffer = (char *)calloc(MAX_MSG_SIZE, sizeof(char));
    customAssert(msgBuffer != NULL, MSG_BUFFER_ERROR);

    while (strcmp((const char *) msgBuffer, "END")) {
        memset(msgBuffer, 0, MAX_MSG_SIZE);

        ssize_t readSTDIN = read(STDIN_FILENO, msgBuffer, MAX_MSG_SIZE);
        ON_DEBUG(customPrint(red, bold, bgDefault,
                             "errno status: [%d] on line %d\n", errno, __LINE__));
        ON_DEBUG(customPrint(green, bold, bgDefault,
                             "READ MESSAGE STATUS: [%d]\n", readSTDIN));

        /*  ========================================= SEND MESSAGE ===================================================== */
        CLIENT_ERROR sendStatus = send(clientDescr, (const char *) msgBuffer, MAX_MSG_SIZE, 0);
        ON_DEBUG(customPrint(red, bold, bgDefault,
                             "errno status: [%d] on line %d\n", errno, __LINE__));
        ON_DEBUG(customPrint(green, bold, bgDefault,
                             "SEND MESSAGE STATUS: [%d]\n", sendStatus));
        // TODO

        /*  ============================================================================================================ */
    }

    return NO_CLIENT_ERROR;
}