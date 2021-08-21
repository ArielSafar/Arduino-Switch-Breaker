#include <Arduino.h>
#include <A4988.h>
#include <Ethernet.h>

// <!-- Stepper motor stuff -->
#define DIR 5
#define STEP 6
#define MS1 7
#define MS2 8
#define MS3 9
#define MICROSTEPS 16
#define RPM 120
#define MOTOR_STEPS 200 // using a 200-step motor (most common)

A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

long revolutions = 0;
short direction = 1;

byte mac_address[] = {0xDE, 0xA0, 0xB3, 0x5F, 0xFE, 0xED};
EthernetServer server(80); // Using port 80

void setup()
{
    init_serial(9600);
    init_sdcard();
    init_ethernet(server, mac_address);
    init_stepper(RPM, MICROSTEPS);
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
                    // Todo: read from file
                    html_response(client);

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
    Serial.println("Revolutions: " + String(floor(revolutions)));
}

void init_serial(long data_rate)
{
    Serial.begin(data_rate);
    Serial.println("Serial started successfully with data rate of " + data_rate);
}

void init_stepper(short rpm, short microsteps)
{
    stepper.begin(rpm, microsteps);
    Serial.println("Stepper motor initialized successfully, set to " + String(rpm) + " RPM and step ratio of 1:" + String(microsteps));
}

void init_ethernet(EthernetServer server, byte mac_addr[])
{
    Ethernet.begin(mac_addr);
    server.begin();
    Serial.println("Ethernet initialized successfully " + Ethernet.localIP());
}

void init_sdcard()
{
    bool res = 0;
    do
    {
        res = SD.begin(4);
        if (!res)
            Serial.println("SD Card failed");

    } while (!res);
    Serial.println("SD Card initialized successfully");
}

void html_response(EthernetClient client)
{
    client.println("HTTP/1.1 200 OK"); // HTTP response
    client.println("Content-Type: text/html");
    client.println(); // HTML code

    client.print("<center><br><h1>Stepper Motor</h1><br><br><br><FORM>");
    client.print("<P> <INPUT type=\"submit\" name=\"direction\" value=\"CW\">");
    client.print("<P> <INPUT type=\"submit\" name=\"direction\" value=\"CCW\">");
    client.print("</FORM></center>");
}
