#include <ESP8266WiFi.h>
#include <SoftwareSerial.h> 

SoftwareSerial NodeMCU(D2,D3);
 
const char* ssid = "Anthony's";
const char* password = "Jesus123";
const char* host = "pbas.000webhostapp.com";
int my_attendance[]={2,2,1,2,3,4};
//std::vector<int> my_attendance;
static int ptr=0;
int at=1;
bool send_data= true;
void sending_data_to_database(int myattendance[] );
int count = 1;

void setup() {
  Serial.begin(115200);
  NodeMCU.begin(9600);
  delay(100);
  Serial.println();       
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  
}
void loop(){

sending_data_to_database(my_attendance);

}


/////////////////SEND ARRAY TO DATABASE/////////////////////
void sending_data_to_database(int myattendance[] ){
  
  if (send_data){
  Serial.print("connecting to ");
  Serial.println(host);
  
  int i=2;
  while (send_data){
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  
 while(count<2)
{
  

  String url_1 = "/api/status_insert.php?tid=" + String(myattendance[1]);
  Serial.print("Requesting URL: ");
  Serial.println(url_1);
  client.print(String("GET ") + url_1 + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
               count = 4;
}
  Serial.print("po");
  String url = "/api/insert.php?tid=" + String(myattendance[1]) + "&sid="+ String(myattendance[i]);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");


 while (client.connected() || client.available())
{
  if (client.available())
  {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
}
  Serial.println();
  Serial.println("closing connection");
  i=i+1;
  Serial.println(i);
  if(i==myattendance[0]-1){
     send_data=false;
     break;
    }
  }
 }
 
}


 
