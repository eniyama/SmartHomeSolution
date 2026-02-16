#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <stdint.h>

/* ================= USER CONFIG ================= */

/* ================= UART PINS ================= */
#define RXD2 16
#define TXD2 17

/* ================= FRAME DEFINITIONS ================= */
#define eFrame_Type_Command   0x03

#define CMD_RELAY_ON          0x01
#define CMD_RELAY_OFF         0x02

// WiFi
#define WIFI_SSID       "ACT-ai_102776212086"
#define WIFI_PASSWORD   "80340576"

// AWS IoT endpoint
#define AWS_IOT_ENDPOINT "a19csj95tolf69-ats.iot.ap-south-1.amazonaws.com"

// Topic to subscribe
#define SUB_TOPIC "home/device/control"



/* ================= CERTIFICATES ================= */

// Amazon Root CA 1
const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
const char AWS_CERT_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUT3+4OSXDfMAS2VeUIiWLx04BCwcwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDEwNzA1MTAx
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJ46hIaahUdwNct5bMMu
RKWf5gLg1i84PKJ7Ri9fa3FhG5/qj5ERcXRi2dCTw2ZMkNfyw1Rpq09NeXtbDhjh
OkAn2Mb8nWPNu0QEAeOY7fZ5YJzhUDpbLZbxq6MgqLa645QMAQC0pjIjHPwq3RZT
r3RPZQWA8KOKt7p1uwhngsZMwy1YOVdcPC1dWw5KShAO9t33HJozMFpcM4im0Z5k
GuMg9+uShZymCsHEM6Pyb7ijt4PxYbi9KpZCbFLvbHYAwQtg+LwjhipxAKuP+Ht7
7dFj5MEx+KSQGu/TuWE/hK7HbtYndzDh5B/zNJORTMZd51WDsK4YwR8lro9zAk2Y
h9cCAwEAAaNgMF4wHwYDVR0jBBgwFoAUip2lD7DXg2qbivo9isKd/iGROuEwHQYD
VR0OBBYEFLm8T/ZrzLE+HHR/g4EvlqPKqtF1MAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBvg1Ug30QkIbvpTjZWFx1j7O5x
6DdWCga8wpmc3m9z6YpowseHHD+kwZ1aoITrQYltrkdQFS05kBXbCWCGqo2blexk
3BndaM74XGT5WX4fcgXbEt4Z497/3FCOLp2KULwVywxJzSQ9lHs6TPC9Hzw9DJvs
BXmqy5OdmYRMLaobBdaEc3cvVF6C2UjgnyQXBoZdyqBBI/tJ/lj7IG47bzhzw05u
OOQMwOvqFcuKdeNUq/jjVyjiYFp9pmxQbx+2Z0ganzKgnvOWANyWVisXYniJ36IZ
mGogFyh478SaiKuF8ckDmDbPGBCJD/5nIilN2rfP/0PqtNE5bBc5Yy2dfEKZ
-----END CERTIFICATE-----
)EOF";

// Device Private Key
const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAnjqEhpqFR3A1y3lswy5EpZ/mAuDWLzg8ontGL19rcWEbn+qP
kRFxdGLZ0JPDZkyQ1/LDVGmrT015e1sOGOE6QCfYxvydY827RAQB45jt9nlgnOFQ
OlstlvGroyCotrrjlAwBALSmMiMc/CrdFlOvdE9lBYDwo4q3unW7CGeCxkzDLVg5
V1w8LV1bDkpKEA723fccmjMwWlwziKbRnmQa4yD365KFnKYKwcQzo/JvuKO3g/Fh
uL0qlkJsUu9sdgDBC2D4vCOGKnEAq4/4e3vt0WPkwTH4pJAa79O5YT+Ersdu1id3
MOHkH/M0k5FMxl3nVYOwrhjBHyWuj3MCTZiH1wIDAQABAoIBAQCd62eTdCsrJpn6
L4FWuBn5d8I4AzChxi32OLTO2RxB95p7m76YGeGzOGmOG7v8oNQ7Q2aiHCjHKFrj
u/gw6rGZkGtyBnQLRSzu8FT2VA7EXVYInXPWGmRA74jPcewRHCvA+c4SZzosdhEa
uKkZ/IHzwr3fpVYG048VwSTfeXfy8t4CP+5NUL5EMNJJ/IB1O+cXoq6GE2fXPA5s
SS97LI3XxafkovjLDlnWvPRsKvuxLb933fLAW/cWyHVRE6I9ErEoPIUaYEHwbySU
tAMp0Mo4+eGvpe62CjWxk2upXtvEL/Fx+6+103Me29y1ZzNoEf7JSfo8TPOWRRKc
BxKKt00JAoGBANJfNx/zmpMefNK+L8xncrMR6YEh3TZaV4ZUgi5eVSMD/RWXzwz6
26nIVh6TMmFMBGOIsWHv6javPqPxy134MW7cG0XP5kxAZAQn8AzDa+Hu2wjwdY+P
+F1eBlsqt64udw6VyylfrJi4PtBYM/szLG3ExIpcxUT0O6y5bMcWzJXVAoGBAMCM
EmOKS7v5U8D+aiy+u+EnlD0ZwyE713Uc+YkZueqpQqftf9+q4L4sk6mMSe/3WbXM
KTjd1ajMAdZQhNwzJ1qgiDWUKSumSEjqrnQP36fXIxmr5IOdyOE2sw7sZ4tX+6iX
UlAq3Jx2m813TiU87UbgUNwUN/ui7eLhkUafqyD7AoGAX3H/qql1iiYc7+iF+zE8
Iu6PiJz6pnxalYGmBq+Z5OccXj2gHP17yA4ytHCIPQimPRp5kDuvgdwEiZFceWfv
1aJbZVMr45CbUB9mlAPd4IXkLqwaSmZBgurz60z4RTijn6RqpnzX6/o71X8PJntT
PwI1QalRfzVoFbeTGMjJTXkCgYApRp22ivH7RNKIf8GBAA5EkPh9NKWY3Twt1d1E
X6h0Pn6UgxwzdW0iN2ocIX/EGlE34KFBmIRx3/HQ4IfqsGiSS/GHEtDUk5vRTcXC
CZkXYM4cdbXR5SQn61LtMw5rV5wSIwY5O0b5n498t0OgRfRTikirNQZfQikext4e
tqG3uwKBgFxsXynOt1ZVCGkGMQ++cmQt6jHPDii/b34bPHWdanthDFlzEQvR3zUD
PnsYkMalVrww84pfI5mWbljRD5RoUHwCyHxAsaiET5ZCVOZSkxiEFqRAK0CdxFda
MA32UwhiXw4KIBO0H/CQQcQNSQHG+rJ40l6qOFxQE/pCpFE1d7z5
-----END RSA PRIVATE KEY-----
)EOF";

/* ================= GLOBAL OBJECTS ================= */

WiFiClientSecure net;
PubSubClient client(net);

/* ================= FUNCTIONS ================= */

void connectWiFi()
{
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
}
void sendCommandToSTM32(uint8_t relay_cmd)
{
  Serial.println("down");
    uint8_t txBuf[66];   // 4(header) + 60(payload) + 2(EE EE)
    uint16_t idx = 0;

    /* ================= HEADER ================= */
    txBuf[idx++] = 1;                    // version
    txBuf[idx++] = eFrame_Type_Command;  // frame type
    txBuf[idx++] = 3;                    // device_id
    txBuf[idx++] = 0;                    // reserved

    /* ================= PAYLOAD ================= */
    txBuf[idx++] = relay_cmd;  // relay ON / OFF

    txBuf[idx++] = 12;  // fan_default_speed
    txBuf[idx++] = 30;  // ac_default_temp
    txBuf[idx++] = 34;  // drapes_state
    txBuf[idx++] = 14;  // air_purifier_state

    /* Padding to make payload = 60 bytes */
    while (idx < (4 + 60))
    {
        txBuf[idx++] = 0x00;
    }

    /* ================= EOF ================= */
    txBuf[idx++] = 0xEE;
    txBuf[idx++] = 0xEE;

    /* ================= SEND ================= */
    Serial2.write(txBuf, idx);

    Serial.println("UART: Command frame sent to STM32");
}
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("\nMessage received from AWS");
  Serial.print("\nTopic: ");
  Serial.println(topic);

  String message = "";

    for (unsigned int i = 0; i < length; i++)
        message += (char)payload[i];

    Serial.println(message);

    if (message == "LED_ON")
    {
        Serial.println("up");
        sendCommandToSTM32(CMD_RELAY_ON);
        
    }
    else if (message == "LED_OFF")
    {
        sendCommandToSTM32(CMD_RELAY_OFF);
    }
}

void connectAWS()
{
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageHandler);

  Serial.print("Connecting to AWS IoT");

  while (!client.connect("ESP32_01"))
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected to AWS IoT");

  client.subscribe(SUB_TOPIC);
  Serial.print("Subscribed to topic: ");
  Serial.println(SUB_TOPIC);
}

/* ================= SETUP ================= */

void setup()
{
  Serial.println("updown");
  Serial.begin(115200);
  delay(2000);

  Serial.println("updown");
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    Serial.println("below_uart");
    
  connectWiFi();
  connectAWS();
}

/* ================= LOOP ================= */

void loop()
{
  if (!client.connected())
  {
    connectAWS();
  }

  client.loop();   // VERY IMPORTANT
}
