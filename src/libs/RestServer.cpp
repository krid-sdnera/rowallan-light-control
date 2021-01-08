#include <EthernetServer.h>
#include "RestServer.h"

RestServer::RestServer(EthernetServer *_server) : server(_server) {}

void RestServer::begin(byte mac[8], byte ip[4])
{
    Ethernet.begin(mac, ip);
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("Ethernet cable is not connected.");
    }

    // start the server
    server->begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
}

void RestServer::serve()
{

    // listen for incoming clients
    EthernetClient client = server->available();
    if (client)
    {
        Serial.println("new client");

        char firstLine[MAX_REQUEST_SIZE];
        unsigned short writepos = 0;
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();

                firstLine[writepos] = c;
                writepos++;

                // Only keep first line of the request.
                if (c == '\r')
                {
                    break;
                }
            }
        }

        firstLine[writepos - 1] = '\0'; // Finish string.

        // Separate first line into it's components.
        char *method = strtok(firstLine, " ");
        char *uri = strtok(NULL, " ");
        char *version = strtok(NULL, " ");

        // Separate uri into path components.
        char *controller = strtok(uri, "/"); // The leading `/` will be excluded.
        char *id = strtok(NULL, "/");
        char *action = strtok(NULL, "/");

        sendHeader(&client);

        bool handled = false;
        if (controller == nullptr)
        {
            handled = handleIndexApi(&client);
        }
        else if (strcmp(controller, "circuit") == 0)
        {
            handled = handleCircuitApi(id, action, &client);
        }
        else if (strcmp(controller, "somethingelse") == 0)
        {
        }

        if (!handled)
        {
            send404(&client);
        }

        Serial.print(F("API:"));
        Serial.print(method);
        Serial.print(F(" con="));
        Serial.print(controller);
        Serial.print(F(",id="));
        Serial.print(id);
        Serial.print(F(",action="));
        Serial.print(action);
        Serial.print(F(",version="));
        Serial.print(version);
        Serial.print(F(",routematched="));
        Serial.print(handled);
        Serial.println();

        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
        Serial.println("client disconnected");
    }
}

void RestServer::sendHeader(EthernetClient *client)
{
    client->println(F("HTTP/1.1 200 OK"));
    client->println(F("Content-Type: application/json"));
    client->println(F("Access-Control-Allow-Origin: *"));
    client->println(F("Connection: close"));
    client->println(F(""));
}

void RestServer::send404(EthernetClient *client)
{
    client->println(F("{\"message\":\"Route not found\",\"error\":{\"status\":404}}"));
}

bool RestServer::handleIndexApi(EthernetClient *client)
{
    client->println(F("{\"paths\":[\"/circuit[/_id_[/(on|off)]]\"]}"));
    return true;
}

bool RestServer::handleCircuitApi(char *id, char *action, EthernetClient *client)
{
    if (id == nullptr)
    {
        client->println(F("{\"paths\":[\"/circuit[/_id_[/(on|off)]]\"],\"circuits\":[1,2,3,4,5,6,7,8]}"));
        return true;
    }
    else if (strcmp(id, "1") == 0)
    {
        // return circuitTest.handleApi(action, client);
    }
    else if (strcmp(id, "2") == 0)
    {
        // return circuitTest.handleApi(action, client);
    }
    return false;
}
