#include <WiFi.h>
#include <PubSubClient.h>

/* ===== UART PINS ===== */
#define RXD2 16
#define TXD2 17

/* ===== WIFI ===== */
const char* ssid     = "ACT-ai_102776212086";
const char* password = "80340576";

/* ===== MQTT ===== */
const char* mqtt_server = "192.168.0.14";

const char* topic_temp = "home/temperature";
const char* topic_hum  = "home/humidity";

WiFiClient espClient;
PubSubClient client(espClient);

/* ===== MQTT CALLBACK (optional) ===== */
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("MQTT RX [");
  Serial.print(topic);
  Serial.print("]: ");

  for (unsigned int i = 0; i < length; i++)
    Serial.print((char)payload[i]);

  Serial.println();
}

/* ===== WIFI CONNECT ===== */
void setup_wifi()
{
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

/* ===== MQTT RECONNECT ===== */
void reconnect()
{
  while (!client.connected()) {
    Serial.print("Connecting to MQTT... ");

    if (client.connect("ESP32_UART_BRIDGE")) {
      Serial.println("OK");
      client.subscribe("home/light/#");
    } else {
      Serial.print("failed rc=");
      Serial.println(client.state());
      delay(1500);
    }
  }
}

/* ===== REMOVE GARBAGE / BINARY BYTES ===== */
String cleanAscii(const String& in)
{
  String out = "";

  for (int i = 0; i < in.length(); i++)
  {
    char c = in[i];
    Serial.print("hello world:");
    Serial.print(c);
    // printable ASCII range only
    if (c >= 32 && c <= 126)
      out += c;
  }

  out.trim();
  return out;
}

/* ===== PARSE "Temperature: 27 C, Humidity: 37 %" ===== */
bool parseTempHumidity(const String& line, float& t, float& h)
{
  int ti = line.indexOf("Temperature:");
  int hi = line.indexOf("Humidity:");

  if (ti == -1 || hi == -1)
    return false;

  // ---- Extract temperature text ----
  String tStr = line.substring(ti + 12, hi);
  tStr.replace("C", "");
  tStr.replace(",", "");
  tStr.trim();

  // ---- Extract humidity text ----
  String hStr = line.substring(hi + 9);
  hStr.replace("%", "");
  hStr.trim();

  t = tStr.toFloat();
  h = hStr.toFloat();

  return !(isnan(t) || isnan(h));
}

/* ===== SETUP ===== */
void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println("ESP32 UART → MQTT Bridge Started");
}

/* ===== LOOP ===== */
void loop()
{
  if (!client.connected())
    reconnect();

  client.loop();

  /* ===== READ UART LINE ===== */
  if (Serial2.available())
  {
    String raw = Serial2.readStringUntil('\n');

    // drop garbage bytes
    String line = cleanAscii(raw);
    if (line.length() == 0)
      return;

    Serial.print("UART CLEAN: ");
    Serial.println(line);

    float temp = NAN;
    float hum  = NAN;

    // parse expected format
    if (parseTempHumidity(line, temp, hum))
    {
      char tBuf[16];
      char hBuf[16];

      snprintf(tBuf, sizeof(tBuf), "%.2f", temp);
      snprintf(hBuf, sizeof(hBuf), "%.2f", hum);

      client.publish(topic_temp, tBuf);
      client.publish(topic_hum,  hBuf);

      Serial.print("MQTT -> Temp: ");
      Serial.print(tBuf);
      Serial.print("  Humidity: ");
      Serial.println(hBuf);
    }
    else
    {
      Serial.println("Ignored (not temperature line)");
    }
  }
}
