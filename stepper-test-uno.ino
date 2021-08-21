#include <Arduino.h>
#include <A4988.h>
#include <Ethernet.h>
#include <EEPROM.h>

// <!-- Stepper motor stuff -->
#define DIR 5
#define STEP 6
#define MS1 7
#define MS2 8
#define MS3 9
#define MICROSTEPS 16
#define MOTOR_STEPS 200 // using a 200-step motor (most common)

byte RPM = 120;
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);
double cw_revolutions = 0, ccw_revolutions = 0;

enum DIRECTION
{
	CW = 1,
	CCW = -1
};

DIRECTION direction = CW;

// <!-- Network stuff -->
#define PORT 80
EthernetServer server(PORT);
EthernetClient client;
String buffer;
boolean currentLineIsBlank;

// <!-- Storage addresses -->
#define CW_REVS_ADDR 100
#define CCW_REVS_ADDR 110

void setup()
{
	byte mac_address[] = {0xDE, 0xA0, 0xB3, 0x5F, 0xFE, 0xED};
	init_serial(9600);
	init_server(server, mac_address);
	init_stepper(RPM, MICROSTEPS);

	cw_revolutions = get_revolutions_storage(CW_REVS_ADDR);
	ccw_revolutions = get_revolutions_storage(CCW_REVS_ADDR);
}

void loop()
{
	handle_motor();
	handle_network();

	if (direction == CW && (int)cw_revolutions % 20 == 0 && (int)cw_revolutions == cw_revolutions)
		save_revolutions_to_storage(CW_REVS_ADDR, (int)cw_revolutions);

	if (direction == CCW && (int)ccw_revolutions % 20 == 0 && (int)ccw_revolutions == ccw_revolutions)
		save_revolutions_to_storage(CCW_REVS_ADDR, (int)ccw_revolutions);
}

// <!-- EEPROM Memory -->
unsigned int get_revolutions_storage(int addr)
{
	return (EEPROM.read(addr) << 8) + EEPROM.read(addr + 1);
}

void save_revolutions_to_storage(int addr, int revolutions)
{
	writeUnsignedIntIntoEEPROM(addr, revolutions);
}

void writeUnsignedIntIntoEEPROM(int address, unsigned int number)
{
	EEPROM.write(address, number >> 8);
	EEPROM.write(address + 1, number & 0xFF);
}

void clean_memory()
{
	cw_revolutions = 0;
	ccw_revolutions = 0;
	writeUnsignedIntIntoEEPROM(CW_REVS_ADDR, 0);
	writeUnsignedIntIntoEEPROM(CCW_REVS_ADDR, 0);
}

// <!-- Initializers -->
void init_serial(unsigned int data_rate)
{
	Serial.begin(data_rate);
	Serial.println("Serial started successfully with data rate of " + String(data_rate));
}

void init_stepper(unsigned short rpm, unsigned short microsteps)
{
	stepper.begin(rpm, microsteps);
	Serial.println("Stepper motor started successfully, set to " + String(rpm) + " RPM and step ratio to 1:" + String(microsteps));
}

void init_server(EthernetServer server, byte mac_addr[])
{
	Ethernet.begin(mac_addr);
	server.begin();
	Serial.print("Ethernet initialized successfully: ");
	Serial.println(Ethernet.localIP());
}

// <!-- Handle network stuff -->

void send_response(String json, String content_type, String status_code)
{
	client.print("HTTP/1.1 ");
	client.println(status_code);
	client.print("Content-Type: ");
	client.println(content_type);
	client.println();

	client.print(json);
}

String json(const char *key, const char *value)
{
	char buffer[30];
	sprintf(buffer, "{\"%s\":\"%s\"}", key, value);
	return String(buffer);
}

String json(const char *key, const int value)
{
	char buffer[30];
	sprintf(buffer, "{\"%s\":%d}", key, value);
	return String(buffer);
}

void handle_motor()
{
	if (RPM <= 0)
	{
		stepper.setRPM(0);
		return;
	}
	stepper.setRPM(RPM);

	if (direction == 1)
		cw_revolutions += 0.125;
	else
		ccw_revolutions += 0.125;

	stepper.rotate(45 * direction);
}

void handle_network()
{
	client = server.available();
	if (!client)
	{
		return;
	}

	boolean currentLineIsBlank = true;
	buffer = "";

	while (client.connected())
	{
		if (!client.available())
		{
			break;
		}

		char c = client.read(); // Read from the Ethernet shield
		buffer += c;			// Add character to string buffer
		Serial.print(c);
		// Client sent request, now waiting for response
		if (c == '\n' && !currentLineIsBlank)
		{
			Serial.println();
			send_response(handle_response(buffer), "application/json", "200 OK");
			break;
		}
		if (c == '\n')
		{
			currentLineIsBlank = true;
			buffer = "";
		}
		else if (c == '\r')
		{
		}
		else
			currentLineIsBlank = false;
	}
	client.stop(); // End server
}

// This is the place to add more abilities
String handle_response(String buffer)
{
	if (buffer.indexOf("POST /?direction=CW") >= 0)
	{
		direction = CW;
		return json("direction", "CW");
	}
	if (buffer.indexOf("POST /?direction=CCW") >= 0)
	{
		direction = CCW;
		return json("direction", "CCW");
	}

	if (buffer.indexOf("POST /?speed=") >= 0)
	{
		String tmp = buffer.substring(13, 16);
		RPM = tmp.toInt();
		return json("speed", RPM);
	}

	if (buffer.indexOf("DELETE /revolutions") >= 0)
	{
		clean_memory();
		return json("revolutions", 0);
	}

	if (buffer.indexOf("GET /speed") >= 0)
		return json("speed", RPM);
	if (buffer.indexOf("GET /direction") >= 0)
		return json("direction", direction == 1 ? "CW" : "CCW");
	if (buffer.indexOf("GET /revolutions?direction=CW") >= 0)
		return json("cw_revolutions", cw_revolutions);
	if (buffer.indexOf("GET /revolutions?direction=CCW") >= 0)
		return json("ccw_revolutions", ccw_revolutions);
	if (buffer.indexOf("GET /revolutions") >= 0)
		return json("revolutions", cw_revolutions + ccw_revolutions);
}
