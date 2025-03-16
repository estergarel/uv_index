# ESP32 UV Index Display

This project uses an **ESP32** board to display the **UV index** on a **dual 7-segment display** and indicate daily values using a **bar graph with LEDs**.

## Features
- Displays the UV index for 7 days.
- Uses a dual 7-segment display to present UV values in the format "xy.z".
- Controls a bar graph with LEDs, each LED representing a day.
- Displays data in the serial monitor.
- Connects to **WiFi** and retrieves data from an online API.

## Components Used
- **ESP32**
- **Dual 7-segment display**
- **LED bar graph**
- **WiFi connection for data retrieval**

## Arduino Principles Applied

### 1. **WiFi Connectivity**
ESP32 connects to the WiFi network using the `WiFi.h` library:
```cpp
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
}
```
Once connected, the network name and signal strength (RSSI) are displayed in the **serial monitor**.

### 2. **Fetching and Processing Data**
Data is retrieved from the Open-Meteo API using `HTTPClient.h` and `ArduinoJson.h`:
```cpp
HTTPClient http;
http.begin(url);
int httpResponseCode = http.GET();
String payload = http.getString();
DynamicJsonDocument doc(1024);
deserializeJson(doc, payload);
JsonArray vectorUV = doc["daily"]["uv_index_max"];
```
The UV values for 7 days are obtained and stored in a `values[8]` array.

### 3. **Displaying on 7-Segment Display**
Values are displayed sequentially, for **2.5 seconds per value**, splitting the integer and decimal parts:
```cpp
void afisareNumar(float nr) {
    int a = static_cast<int>(nr);
    int b = int(nr * 10) % 10;
    afisareNumarReal(String(a));
    delay(1000);
    afisareNumarFractional(String(b));
    delay(1000);
    afisareStinsa();
    delay(500);
}
```
### 4. **LED Bar Graph Control**
Each LED lights up corresponding to the currently displayed day:
```cpp
void regulaLed(int i) {
    ledStins();
    digitalWrite(ledPins[i], HIGH);
}
```

## Installation and Running
1. **Download** and upload the code to the ESP32.
2. **Configure** `ssid` and `password` for WiFi.
3. **Monitor** the values in the serial monitor.
