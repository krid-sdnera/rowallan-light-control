#include <Arduino.h>
#include <EthernetServer.h>

#ifndef RestServer_H
#define RestServer_H

#define MAX_REQUEST_SIZE 80
#define MAX_URI_SIZE 20

class RestServer
{
private:
    EthernetServer *server;

    void sendHeader(EthernetClient *client);
    void send404(EthernetClient *client);
    bool handleIndexApi(EthernetClient *client);
    bool handleCircuitApi(char *id, char *action, EthernetClient *client);

public:
    RestServer(EthernetServer *_server);

    void begin(byte mac[8], byte ip[4]);
    void serve();
};
#endif
