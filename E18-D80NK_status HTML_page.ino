/* ESP8266 - Status Leitura sensor reflexivo em página HTML
 */

#include <ESP8266WiFi.h>

char ssid [] = "peixeiro 2.4";
char senha[] = "Ab034033";

WiFiServer server(80);

void setup() {
  pinMode(D0, INPUT);
  
  Serial.begin(115200);
  delay(10);
  
  conectaWiFi(ssid,senha);

  server.begin();
  Serial.println("Servidor iniciou");
  
}

void loop() {
  // Para ver a leitura no Serial
  Serial.println(digitalRead(D0));


  WiFiClient client = server.available();
  if(!client)
    return;
 
  while(!client.available())
    delay(1);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv='refresh' content='2'; charset=utf-8>");
  client.println("<h1>Status Sensor Reflexivo no ESP8266 em página HTML</h1>");
  client.println("<h2>STATUS:</h2>");

  if(!digitalRead(D0) == 1){
   client.print("<p>Há obstáculo a frente</p>");
   client.println(!digitalRead(D0));
  }
  else{
    client.println("<p>Nenhum obstáculo</p>");
    client.println(!digitalRead(D0));
  }
  client.println("</html>");
   
}

void conectaWiFi(char SSID[],char SENHA[]){

  Serial.print("Conectando a rede ");
  Serial.println(SSID);

  WiFi.begin(SSID,SENHA);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println("WiFi Conectado Com Sucesso!");
  Serial.println("Endereço de IP: ");
  Serial.print(WiFi.localIP());
  Serial.println();
}
