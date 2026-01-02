#define RXD2 16
#define TXD2 17
#define FRAME_PROVISION 0x01
#define FRAME_COMMAND 0x03 
#define FRAME_CONFIG 0x05
#define MAX_FRAME_SIZE 64 
 // safety limit 
// Create frame into array and return length 
uint8_t createFrame(uint8_t frameType, const char *payload, uint8_t *frame) 
{    uint8_t index = 0; 
    // 1. Frame type
     frame[index++] = frameType;
      // 2. Payload (variable length) 
       while (*payload && index < (MAX_FRAME_SIZE - 2))
       { 
         frame[index++] = (uint8_t)(*payload++);
       } 
        // 3. EOF
         frame[index++] = 0xEE;
          frame[index++] = 0xEE; 

          return index; 
          // total frame length
} 
// Send frame array 
void sendFrame(uint8_t *frame, uint8_t length) 
{
     Serial2.write(frame, length); 
} 
void setup() 
{     
    Serial.begin(115200); 
    delay(2000); 
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    Serial.println("ESP32 Array-Based Variable Frame Sender"); 
    uint8_t frame[MAX_FRAME_SIZE];
    uint8_t frameLen; 
  // Provision frame 
    frameLen = createFrame(FRAME_PROVISION, "PROVISION1", frame); 
    sendFrame(frame, frameLen); Serial.println("Sent Provision Frame");
    delay(500); 
   // Command frame 
   frameLen = createFrame(FRAME_COMMAND, "LED_ON", frame); 
   sendFrame(frame, frameLen); Serial.println("Sent Command Frame"); 
   delay(500);

   // Config frame 
  // frameLen = createFrame(FRAME_CONFIG, "WIFI_OK", frame); 
   // sendFrame(frame, frameLen); // Serial.println("Sent Config Frame");
    } 
 void loop() 
{

}
