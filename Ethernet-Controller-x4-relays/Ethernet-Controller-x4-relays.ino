/*
This script doesn't use MySensors library!

It is just a basic example of how to connect an Arduino UNO with an Ethernet Shield to your network.
It creates a simple webserver and hosts a single page of action links accessible via an IP address: 

IPAddress ip(192,168,0,161);

To easily find your IP gateway, open a Command Prompt and type:
  ipconfig /all
and then look for the value for Default Gateway. You can then select a high number like 161 as the last number in your IPAddress.

Sensors/Actuators:
You can output whatever sensor data you want to the webpage, and act on clicks of links. In this example, we control a 4 Channel Relay controlling lights in a room.

Circuit:
   1. Ethernet shield attached to pins 10, 11, 12, 13
   2. plug Ethernet cable to shield and your modem/router.
   3. Plug in your 4 Channel shield to digital pins 6, 7, 8 9

*/

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = {0x90, 0xA4, 0xDA, 0x0D, 0x48, 0xD3 };

// The IP address will be dependent on your local network:
// assign an IP address for the controller:

IPAddress ip(192,168,0,161);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255, 255, 255, 0);

// Initialize the Ethernet server library with the port you want to use.
EthernetServer server(80);
String readString;

// Declare Pins
int relay1 = 6; 
int relay2 = 7; 
int relay3 = 8; 
int relay4 = 9;  

void setup()
{
  // Extra Set up code:
  pinMode(relay1, OUTPUT); //pin selected to control
  pinMode(relay2, OUTPUT); //pin selected to control
  pinMode(relay3, OUTPUT); //pin selected to control
  pinMode(relay4, OUTPUT); //pin selected to control

  digitalWrite(relay1, HIGH); 
  digitalWrite(relay2, HIGH); 
  digitalWrite(relay3, HIGH); 
  digitalWrite(relay4, HIGH); 
  
  //enable serial data print
  Serial.begin(9600);

  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)

  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())

      {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100)

        {
          //store characters to string
          readString += c;
          //Serial.print(c);

          Serial.write(c);
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          //if HTTP request has ended
          if (c == '\n') {
            Serial.println(readString); //print to serial monitor for debuging
//--------------------------------------------------------------------------------------------------------
            // Needed to Display Site:
            client.println("HTTP/1.1 200 OK"); //send new page
            client.println("Content-Type: text/html");
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");

//--------------------------------------------------------------------------------------------------------
//-------------------------------------------------

// what is being Displayed :     
        
            client.println("<TITLE>Relay Group 1</TITLE>");
            
            client.println("</HEAD>");
            client.println("<BODY>");
            client.println("<center>");
            client.println("<H1>Relay Group 1</H1>");
            client.println("<hr />");         

            client.println("<a href=\"/?relay1-on\"\">Turn On Relay 1</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?relay1-off\"\">Turn Off Relay 1</a><br />");     
            client.println("<hr />");            

            client.println("<a href=\"/?relay2-on\"\">Turn On Relay 2</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?relay2-off\"\">Turn Off Relay 2</a><br />");     
            client.println("<hr />");           

            client.println("<a href=\"/?relay3-on\"\">Turn On Relay 3</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?relay3-off\"\">Turn Off Relay 3</a><br />");     
            client.println("<hr />");
            
            client.println("<a href=\"/?relay4-on\"\">Turn On Relay 4</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?relay4-off\"\">Turn Off Relay 4</a><br />");     
            client.println("<hr />");
            client.println("</center>");
            client.println("</BODY>");
            client.println("</HTML>");

            delay(1);
            //stopping client
            client.stop();

            //-------------------------------------------------
            // Code which needs to be Implemented:
            if(readString.indexOf("?relay1-on") >0)
            {
              digitalWrite(relay1, LOW);    
              Serial.println("Relay 1 on");
            }
            else if(readString.indexOf("?relay1-off") >0)
            {
                digitalWrite(relay1, HIGH);    
                Serial.println("Relay 1 Off");
            }
            
            if(readString.indexOf("?relay2-on") >0)
            {
              digitalWrite(relay2, LOW);    
              Serial.println("Relay 2 on");
            }
            else if(readString.indexOf("?relay2-off") >0)
            {
                digitalWrite(relay2, HIGH);   
                Serial.println("Relay 2 Off");
            }
            
            if(readString.indexOf("?relay3-on") >0)
            {
              digitalWrite(relay3, LOW);    
              Serial.println("Relay 3 on");
            }
            else if(readString.indexOf("?relay3-off") >0)
            {
                digitalWrite(relay3, HIGH);    
                Serial.println("Relay 3 Off");
            }
            
             if(readString.indexOf("?relay4-on") >0)
            {
              digitalWrite(relay4, LOW);    
              Serial.println("Relay 4 on");
            }
            else if(readString.indexOf("?relay4-off") >0)
            {
                digitalWrite(relay4, HIGH);    
                Serial.println("Relay 4 Off");
            }
            
            //clearing string for next read
            readString="";

            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
            Serial.println("client disconnected");

          }
        }
      }
    }
  }
}
