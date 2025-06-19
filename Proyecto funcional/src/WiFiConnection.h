#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

class WiFiConnection {
public:
    void begin(const char* ssid, const char* password);
    bool isConnected();
};

#endif
