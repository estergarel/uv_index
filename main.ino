#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <String.h>

const char* ssid = "ESP33";
const char* password = "";
float values[8];
// Definirea pinilor pentru fiecare segment
const int A = 4;
const int B = 16;
const int C = 17;
const int D = 5;
const int E = 18;
const int F = 19;
const int G = 21;
const int comma = 22;

// Definirea pinilor pentru selectarea cifrei
const int digit1  = 2;
const int digit2 = 15;

// Definirea cifrelor pentru fiecare număr
const byte bytes[12][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1, 0},  // 2
  {1, 1, 1, 1, 0, 0, 1, 0},  // 3
  {0, 1, 1, 0, 0, 1, 1, 0},  // 4
  {1, 0, 1, 1, 0, 1, 1, 0},  // 5
  {1, 0, 1, 1, 1, 1, 1, 0},  // 6
  {1, 1, 1, 0, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1, 0},  // 8
  {1, 1, 1, 1, 0, 1, 1, 0},  // 9
};
//afisare
void printSerial(int i)
{
  if(!i%2)
  {
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(values[i]);
    Serial.print("    ");
    if(i==6)
    Serial.println(" ");
  }
  else
  {
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(values[i]);
    Serial.println(" ");

  }
}
void afisareStinsa()
{
  // Afișăm cifra zecilor pe display
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, LOW);
   digitalWrite(A, 0);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 0);
    digitalWrite(G, 0);
    digitalWrite(comma, 0);
  // Pauză pentru a afișa cifra zecilor
  delay(5);
  // Activăm cifra 2
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);
  // Afișăm cifra unităților pe display
  digitalWrite(A, 0);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 0);
  digitalWrite(E, 0);
  digitalWrite(F, 0);
  digitalWrite(G, 0);
  digitalWrite(comma, 0);

  // Pauză pentru a afișa cifra unităților
  delay(5);

  // Dezactivăm cifra 2
  digitalWrite(digit2, LOW);
}
void afisareNumarFractional(String a) {
  // Extragem zecile și unitățile din număr
    // Șirul de caractere de intrare
  char digit1R = a[0];
  // Primul caracter din șirul de intrare

  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, LOW);

  // Afișăm cifra zecilor pe display
  digitalWrite(A, 0);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 0);
  digitalWrite(E, 0);
  digitalWrite(F, 0);
  digitalWrite(G, 0);
  digitalWrite(comma, 1);

  // Pauză pentru a afișa cifra zecilor
  delay(5);


  // Activăm cifra 2
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);

  // Afișăm cifra unităților pe display
  digitalWrite(A, bytes[String(digit1R).toInt()][0]);
  digitalWrite(B, bytes[String(digit1R).toInt()][1]);
  digitalWrite(C, bytes[String(digit1R).toInt()][2]);
  digitalWrite(D, bytes[String(digit1R).toInt()][3]);
  digitalWrite(E, bytes[String(digit1R).toInt()][4]);
  digitalWrite(F, bytes[String(digit1R).toInt()][5]);
  digitalWrite(G, bytes[String(digit1R).toInt()][6]);
  digitalWrite(comma, bytes[String(digit1R).toInt()][7]);

  // Pauză pentru a afișa cifra unităților
  delay(5);

  // Dezactivăm cifra 2
  digitalWrite(digit2, LOW);
}
void afisareNumarReal(String a) {
  // Extragem zecile și unitățile din număr
  char nr1 = a.charAt(0);  // Primul caracter din șirul de intrare
  char nr2 = a.charAt(1);  // Al doilea caracter din șirul de intrare
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, LOW);

  // Afișăm cifra zecilor pe display
   if(nr1>='0' && nr1<='9')
  {
  digitalWrite(A, bytes[String(nr1).toInt()][0]);
  digitalWrite(B, bytes[String(nr1).toInt()][1]);
  digitalWrite(C, bytes[String(nr1).toInt()][2]);
  digitalWrite(D, bytes[String(nr1).toInt()][3]);
  digitalWrite(E, bytes[String(nr1).toInt()][4]);
  digitalWrite(F, bytes[String(nr1).toInt()][5]);
  digitalWrite(G, bytes[String(nr1).toInt()][6]);
  digitalWrite(comma, bytes[String(nr1).toInt()][7]);
  }
  else if(nr1=='?')
  {
    digitalWrite(A, 0);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 0);
    digitalWrite(G, 0);
    digitalWrite(comma, 0);
  }

  // Pauză pentru a afișa cifra zecilor
  delay(5);

  // Activăm cifra 2
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);

  // Afișăm cifra unităților pe display
  digitalWrite(A, bytes[String(nr2).toInt()][0]);
  digitalWrite(B, bytes[String(nr2).toInt()][1]);
  digitalWrite(C, bytes[String(nr2).toInt()][2]);
  digitalWrite(D, bytes[String(nr2).toInt()][3]);
  digitalWrite(E, bytes[String(nr2).toInt()][4]);
  digitalWrite(F, bytes[String(nr2).toInt()][5]);
  digitalWrite(G, bytes[String(nr2).toInt()][6]);
  digitalWrite(comma, bytes[String(nr2).toInt()][7]);

  // Pauză pentru a afișa cifra unităților
  delay(5);

  // Dezactivăm cifra 2
  digitalWrite(digit2, LOW);
}
void afisareNumar(float nr)
{
  int a,b;
  String strA,strB;
  a = static_cast<int>(nr); // Convertim partea reală în int
  float ok = static_cast<int>(nr * 10) % 10;
  b = int(ok); // Convertim partea fractionala în int
  if(a<=9 && a>=0)
   strA = "?"+String(a);
  else
   strA = String(a); // Convertim partea intreaga in String
   
   strB = String(b); // Convertim partea fractionala in String
 
  unsigned long timpInceput = millis();
  while (millis() - timpInceput < 1000)
  {
    afisareNumarReal(strA);
  }
  timpInceput = millis();
  while (millis() - timpInceput < 1000)
  {
    afisareNumarFractional(strB);
  }
  timpInceput = millis();

  while (millis() - timpInceput < 500)
  {
    afisareStinsa();
  }


}
void ledStins()
{
  digitalWrite(13, LOW);
  digitalWrite(23, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
}
void regulaLed(int i)
{
ledStins();
switch (i)
{
case 0:
digitalWrite(13, HIGH);
break;
case 1:
digitalWrite(23, HIGH);
break;
case 2:
digitalWrite(25, HIGH);
break;
case 3:
digitalWrite(26, HIGH);
break;
case 4:
digitalWrite(27, HIGH);
break;
case 5:
digitalWrite(32, HIGH);
break;
case 6:
digitalWrite(33, HIGH);
break;
default:
break;
}
}

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(comma, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);

  pinMode(13, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  // Conectarea la WiFi
  Serial.begin(115200);
  Serial.println("PIA - Echipa 510");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  Serial.println("");
  Serial.print("numele retelei WiFi: ");
  Serial.println(WiFi.SSID());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

  //obiecte json
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    String url = "https://api.open-meteo.com/v1/forecast?latitude=44.43&longitude=26.14&timezone=auto&current_weather=true&daily=uv_index_max";

    http.begin(url);

    int httpResponseCode = http.GET();
    if (httpResponseCode == 200)
    {
      String payload = http.getString();
      //Serial.println(payload);

      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);

      if (error)
      {
        Serial.println("Eroare (JSON 1)");
      }
      else
      {
        // Aici puteți accesa și procesa valorile JSON în funcție de structura răspunsului API
        JsonArray vectorUV = doc["daily"]["uv_index_max"];
          for (size_t i = 0; i < vectorUV.size(); i++)
          {
           float vectorValori = vectorUV[i].as<float>();
            values[i]=vectorValori;
            if(i<vectorUV.size()-1)
            {
              Serial.print(values[i]);
              Serial.print(",");
            }
            else
            {
              Serial.print(values[i]);
            }

          }
        }
      }
    http.end();
  }
  Serial.println(" ");

  for(int i=0;i<7;i++)
  {
    printSerial(i);
    regulaLed(i);
    afisareNumar(values[i]);

  }
  ledStins();


}
void loop() {

}