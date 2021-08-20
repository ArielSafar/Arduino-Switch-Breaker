#include <Arduino.h>
#include <A4988.h>
#include <BasicStepperDriver.h>
#include <MultiDriver.h>
#include <SyncDriver.h>

#include <SPI.h>
#include <Ethernet.h>

#include <math.h>

#define MOTOR_STEPS 200 // using a 200-step motor (most common)
// configure the pins connected

#define DIR 5
#define STEP 6
#define MS1 7
#define MS2 8
#define MS3 9
#define MICROSTEPS 16
#define RPM 120

A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

long revolutions = 0;
short direction = 1;

byte mac_address[] = {0xDE, 0xA0, 0xB3, 0x5F, 0xFE, 0xED};
EthernetServer server(80); // Using port 80

void setup()
{
    Serial.begin(9600);
    stepper.begin(RPM, MICROSTEPS);
    Serial.println("Start 1:16");

    Ethernet.begin(mac_address);
    server.begin();
    Serial.println(Ethernet.localIP());
}

void loop()
{

    EthernetClient client = server.available();
    if (client)
    {
        boolean currentLineIsBlank = true;
        String buffer = "";
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read(); // Read from the Ethernet shield
                buffer += c;            // Add character to string buffer
                // Client sent request, now waiting for response
                if (c == '\n' && currentLineIsBlank)
                {
                    client.println("HTTP/1.1 200 OK"); // HTTP response
                    client.println("Content-Type: text/html");
                    client.println(); // HTML code
                    client.print("<center><br><h1>Stepper Motor</h1><br><br><br><FORM>");
                    client.print("<P> <INPUT type=\"submit\" name=\"direction\" value=\"CW\">");
                    client.print("<P> <INPUT type=\"submit\" name=\"direction\" value=\"CCW\">");
                    client.print("</FORM>");
                    client.print("<p>" + String(round(revolutions)) + "</p></center>");
                    break;
                }
                if (c == '\n')
                {
                    currentLineIsBlank = true;
                    buffer = "";
                }
                else if (c == '\r')
                { // Command from webpage
                    if (buffer.indexOf("GET /?direction=CW") >= 0)
                        direction = 1;
                    if (buffer.indexOf("GET /?direction=CCW") >= 0)
                        direction = -1;
                }
                else
                {
                    currentLineIsBlank = false;
                }
            }
        }
        client.stop(); // End server
    }

    revolutions += 0.5;
    stepper.rotate(direction * 1 * 180); // in microsteps
    Serial.println(revolutions);
}
