/*
LORA (1 Watt Module) APRS Tracker
https://github.com/richonguzman/LoRa_1W_APRS_Tracker
written by Ricardo Guzman ( CD2RXU-7 )
based on lots of other Lora APRS Tracker ideas like:
https://github.com/lora-aprs/LoRa_APRS_Tracker
https://github.com/aprs434/lora.tracker
https://github.com/Mane76/lora.tracker
https://github.com/sh123/esp32_loraprs
*/

#include <SPI.h>
#include <TinyGPS++.h>
#include <RadioLib.h>
#include <WiFi.h>
#include <OneButton.h>
#include "pins_config.h"
#include "lora_config.h"
#include "beacon_config.h"

#define VERSION "2023.01.28-2"		// BETA!!!

SX1268				radio = new Module(NSS, DIO1, NRST, BUSY);
HardwareSerial		neo6m_gps(1);
TinyGPSPlus			gps;
OneButton			UserButton1 = OneButton(BUTTON1_PIN, true, true);

String CurrentUser[10];
static bool send_update = true;

String CALLSIGN_CONFIG_1[10] = {User1_Callsign,User1_Symbol,String(User1_SlowRate),String(User1_SlowSpeed),
								String(User1_FastRate),String(User1_FastSpeed),String(User1_MinDistTx),
								String(User1_MinDeltaBcn),String(User1_TurnMin),String(User1_TurnSlope)};

String CALLSIGN_CONFIG_2[10] = {User2_Callsign,User2_Symbol,String(User2_SlowRate),String(User2_SlowSpeed),
								String(User2_FastRate),String(User2_FastSpeed),String(User2_MinDistTx),
								String(User2_MinDeltaBcn),String(User2_TurnMin),String(User2_TurnSlope)};

String CALLSIGN_CONFIG_3[10] = {User3_Callsign,User3_Symbol,String(User3_SlowRate),String(User3_SlowSpeed),
								String(User3_FastRate),String(User3_FastSpeed),String(User3_MinDistTx),
								String(User3_MinDeltaBcn),String(User3_TurnMin),String(User3_TurnSlope)};


void setup_lora_module() {
	int state = radio.begin(LoraFreqTx, LoraBandWidth, LoraSpreadingFactor, LoraCodingRate, LoraSyncWord, LoraOutro, LoraPreampbleLenght);
	radio.setOutputPower(Lora_Power);
	radio.setRfSwitchPins(RXEN, TXEN);
	if (state == RADIOLIB_ERR_NONE) {
		Serial.println(F("LORA (1 Watt) MODULE Ready (Radiolib success!)"));
	} else {
		Serial.println(F("Lora Module Setup failed, code "));
		Serial.println(state);
	}
}

void setup_gps_module() {
	neo6m_gps.begin(9600, SERIAL_8N1, GPS_TXD, GPS_RXD);
}

void setup_first_user() {
	for (int i = 0; i<10; i++ ) {
		CurrentUser[i] = CALLSIGN_CONFIG_1[i];
	}
	Serial.print("Current User --> ");
	Serial.println(CurrentUser[0]);
}

static void ForcedBeaconTx() {
	Serial.println("Forced Beacon Tx");
	send_update = true;
}

static void HandleNextBeacon() {
	if (CurrentUser[0] == CALLSIGN_CONFIG_1[0]){
		Serial.print("Changing CALLSIGN to --> ");
		Serial.println(CALLSIGN_CONFIG_2[0]);
		for (int i = 0; i<10; i++ ) {
			CurrentUser[i] = CALLSIGN_CONFIG_2[i];
		}
	} else if (CurrentUser[0] == CALLSIGN_CONFIG_2[0]){
		Serial.print("Changing CALLSIGN to --> ");
		Serial.println(CALLSIGN_CONFIG_3[0]);
		for (int i = 0; i<10; i++ ) {
			CurrentUser[i] = CALLSIGN_CONFIG_3[i];
		}
	} else if (CurrentUser[0] == CALLSIGN_CONFIG_3[0]){
		Serial.print("Changing CALLSIGN to --> ");
		Serial.println(CALLSIGN_CONFIG_1[0]);
		for (int i = 0; i<10; i++ ) {
			CurrentUser[i] = CALLSIGN_CONFIG_1[i];
		}
	}
}

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	WiFi.mode(WIFI_OFF);
	btStop();
	UserButton1.attachClick(ForcedBeaconTx);
	UserButton1.attachLongPressStart(HandleNextBeacon);
	Serial.println("");
	Serial.println("****** LoRa APRS Tracker ******");
	Serial.println("https://github.com/richonguzman/LoRa_1W_APRS_Tracker");
	Serial.print("Version -------> ");
	Serial.println(VERSION);
	setup_first_user();
	setup_lora_module();
	setup_gps_module();
	Serial.println("---Transmission Start ---");
}

uint8_t  tx_buffer[256];
uint32_t lastTxTime = 0;

char *ax25_base91enc(char *s, uint8_t n, uint32_t v) {
	/* Creates a Base-91 representation of the value in v in the string */
	/* pointed to by s, n-characters long. String length should be n+1. */
	for(s += n, *s = '\0'; n; n--) {
		*(--s) = v % 91 + 33;
    	v /= 91;
  	}
  	return(s);
}

void loop() {
	UserButton1.tick();

	while (neo6m_gps.available() > 0) {
		gps.encode(neo6m_gps.read());
	}
	bool 		gps_loc_update 	= gps.location.isUpdated();
	bool        gps_time_update = gps.time.isUpdated();
	//static time_t nextBeaconTimeStamp = -1;
	static double       currentHeading          = 0;
	static double       previousHeading         = 0;
	//static unsigned int rate_limit_message_text = 0;
	
	static double   lastTxLatitude	= 0.0;
	static double   lastTxLongitude = 0.0;
	static double   lastTxDistance  = 0.0;
	static uint32_t txInterval      = 60000L;
	//static int      speed_zero_sent = 0;


	String mensaje_test = "0";
	if (!send_update && gps_loc_update) {
		uint32_t lastTx 			= millis() - lastTxTime;
		int MinimumDistanceTx 		= CurrentUser[6].toInt();
		int MinimumTimeDeltaBeacon	= CurrentUser[7].toInt();
		int TurnDegrees				= CurrentUser[8].toInt();
		int TurnSlope				= CurrentUser[9].toInt();
		currentHeading  			= gps.course.deg();
		lastTxDistance  			= TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), lastTxLatitude, lastTxLongitude);
		
		if (lastTx >= txInterval) {
			if (lastTxDistance > MinimumDistanceTx) {
				send_update = true;
				mensaje_test = "D:" + String(lastTxDistance) + " I:" + String(txInterval);
			}
		}
		if (!send_update) {
			double headingDelta = abs(previousHeading - currentHeading);
			if (lastTx > MinimumTimeDeltaBeacon * 1000) {
				if (headingDelta > TurnDegrees && lastTxDistance > MinimumDistanceTx) {
					send_update = true;
					mensaje_test = "C:" + String(headingDelta) + " D:" + String(lastTxDistance) + " I:" + String(txInterval);
				}
			}
		}
	}
	
	if (send_update && gps_loc_update) {
		float Tlat, Tlon;
		float Tspeed=0, Tcourse=0;
		Tlat    = gps.location.lat();
		Tlon    = gps.location.lng();
		Tcourse = gps.course.deg();
		Tspeed  = gps.speed.knots();

		uint32_t aprs_lat, aprs_lon;
		aprs_lat = 900000000 - Tlat * 10000000;
		aprs_lat = aprs_lat / 26 - aprs_lat / 2710 + aprs_lat / 15384615;
		aprs_lon = 900000000 + Tlon * 10000000 / 2;
		aprs_lon = aprs_lon / 26 - aprs_lon / 2710 + aprs_lon / 15384615;

		String Ns, Ew, helper;
		if(Tlat < 0) { Ns = "S"; } else { Ns = "N"; }
		if(Tlat < 0) { Tlat= -Tlat; }

		if(Tlon < 0) { Ew = "W"; } else { Ew = "E"; }
		if(Tlon < 0) { Tlon= -Tlon; }

		String AprsPacketMsg = "!";
		AprsPacketMsg += AprsOverlay;	
		char helper_base91[] = {"0000\0"};
		int i;
		ax25_base91enc(helper_base91, 4, aprs_lat);
		for (i=0; i<4; i++) {
			AprsPacketMsg += helper_base91[i];
		}
		ax25_base91enc(helper_base91, 4, aprs_lon);
		for (i=0; i<4; i++) {
			AprsPacketMsg += helper_base91[i];
		}

		AprsPacketMsg += CurrentUser[1];	// Symbol

		if (SendAltitude) {					// Send Altitude or... (APRS calculates Speed also)
			int Alt1, Alt2;
			int Talt;
			Talt = gps.altitude.feet();
			if(Talt>0){
				double ALT=log(Talt)/log(1.002);
				Alt1= int(ALT/91);
				Alt2=(int)ALT%91;
			}else{
				Alt1=0;
				Alt2=0;
			}
			AprsPacketMsg +=char(Alt1+33);
			AprsPacketMsg +=char(Alt2+33);
			AprsPacketMsg +=char(0x30+33);
		} else {							// ... just send Course and Speed
			ax25_base91enc(helper_base91, 1, (uint32_t) Tcourse/4 );
			AprsPacketMsg += helper_base91[0];
			ax25_base91enc(helper_base91, 1, (uint32_t) (log1p(Tspeed)/0.07696));
			AprsPacketMsg += helper_base91[0];
			AprsPacketMsg += "\x47";	
		}

		if (SendComment) {
			//AprsPacketMsg += APRS_COMMENT;
			AprsPacketMsg += mensaje_test;
		}

		Serial.print(F("GPS coordinates: ")); 				// Only for Serial Monitor
		Serial.print(Tlat, 6); 
		Serial.print(F(", ")); 
		Serial.println(Tlon, 6);

		memset(tx_buffer, 0x00, sizeof tx_buffer);
		uint16_t size = 0;

		size = snprintf(reinterpret_cast<char *>(tx_buffer), sizeof tx_buffer, "\x3c\xff\x01%s>%s:%s", CurrentUser[0], AprsPath, AprsPacketMsg.c_str());

		Serial.print(millis()); 							// Only for Serial Monitor
		Serial.print(F(" transmitting: ")); 
		Serial.println(reinterpret_cast<char *>(tx_buffer));

		digitalWrite(LED_BUILTIN, HIGH);
		radio.transmit(tx_buffer, size);
		radio.finishTransmit();
		digitalWrite(LED_BUILTIN, LOW);

		lastTxLatitude	= gps.location.lat();
		lastTxLongitude = gps.location.lng();
		previousHeading = currentHeading;
		lastTxDistance  = 0.0;
		lastTxTime      = millis();
		send_update = false;
	}

	if (gps_time_update) {									// updating txInterval between Slow and FastRate or in between
		int SlowRate 		= CurrentUser[2].toInt();
		int SlowSpeed 		= CurrentUser[3].toInt();
		int FastRate 		= CurrentUser[4].toInt();
		int FastSpeed 		= CurrentUser[5].toInt();

		int curr_speed = (int)gps.speed.kmph();
		if (curr_speed < SlowSpeed) {
			txInterval = SlowRate * 1000;
		} else if (curr_speed > FastSpeed) {
			txInterval = FastRate * 1000;
		} else {
			txInterval = min(SlowRate, (FastSpeed * FastRate / curr_speed)) * 1000;
		}
	}
}