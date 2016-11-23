#include "WiFiEsp.h" //Libreria para comunicarse facilmente con el modulo ESP01
#include "SoftwareSerial.h" //Libreria para poder emular un puerto serial
SoftwareSerial Serial1(3, 2); // RX, TX  
char ssid[] = "mi_ssid";            // SSID (Nombre de la red WiFi)
char pass[] = "mi_contraseña_ssid";        // Contraseña
int status = WL_IDLE_STATUS;     // Estado del ESP. No tocar
 
char server[] = "api.openweathermap.org"; //Servidor al que nos conectaremos
char key[] = "api key";    //key
 
WiFiEspClient client;  //Iniciar el objeto para cliente 
 
void setup()
{
  Serial.begin(9600); //Monitor serial
  Serial1.begin(9600); //ESP01
  WiFi.init(&Serial1);
 
  //intentar iniciar el modulo ESP
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Modulo no presente. Reinicie el Arduino y el ESP01 (Quite el cable que va de CH_PD a 3.3V y vuelvalo a colocar)");
    //Loop infinito
    while (true);
  }
 
  //Intentar conectar a la red wifi
  while ( status != WL_CONNECTED) {
    Serial.print("Intentando conectar a la red WiFi: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
 
  Serial.println();
}
 
void loop()
{
  Serial.println("Iniciando conexion..."); // Intentar la conexion al servidor dado
  if (client.connect(server, 80)) {
    Serial.println("Conectado al servidor");
    // Request TCP
    client.print("GET /data/2.5/weather?id=3703443&APPID=");
    client.print(key);
    client.println(" HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  }
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  
  }
 
  //Desconexion
  if (!client.connected()) {
    Serial.println();
    Serial.println("Desconectando del servidor...");
    client.stop();
  }
    // Reintentar
    Serial.println();
    Serial.println("Reintentar? <y>/<n>");
    boolean y=false;
    while(y==false)
    {
      String x = Serial.readString();
      x.trim();
      y=(x=="y" ? true : false);
    }
    
  }

