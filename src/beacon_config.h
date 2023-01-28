#ifndef BEACON_CONFIG_H_
#define BEACON_CONFIG_H_

//#define SlowRate                120         // Seg
//#define SlowSpeed               10          // Km/h (3 Runner , 5 Bike, 10 Car)
//#define FastRate                60          // Seg
//#define FastSpeed               20          // Km/h (20 Runner y Bike, 70 Car)
//#define TurnDegrees             20          // Degrees before Forced Beacon Tx (20 Car , 15 Bike/Runner)
//#define MinimumDistanceTx       3           // Mts (20 Runner, 100 Car/Bike)
//#define MinimumTimeDeltaBeacon  5           // Seg between Tx

#define SendAltitude            true        // "true" adds Altitude to the APRS packet/message, "false" add Course+Speed
#define SendComment             false       // "true" adds comment to the APRS packet/message

#define APRS_COMMENT    "Lora Tracker 1W"       // if you want to send any comment change the APRS_COMMENT 
                                                // and also beacon_config.h > SendComment = true

#define AprsPath                "AP"        // APRS Destination (could be also "WIDE1-1")
#define AprsOverlay             "/"

#define User1_Callsign          "CD2RXU-7"
#define User1_Symbol            "["         // Runner
#define User1_SlowRate          120
#define User1_SlowSpeed         3
#define User1_FastRate          60
#define User1_FastSpeed         20
#define User1_MinDistTx         50
#define User1_MinDeltaBcn       20
#define User1_TurnMin           8
#define User1_TurnSlope         60

#define User2_Callsign          "CD2RXU-8"
#define User2_Symbol            "b"         // Bike
#define User2_SlowRate          180
#define User2_SlowSpeed         5
#define User2_FastRate          60
#define User2_FastSpeed         40
#define User2_MinDistTx         70
#define User2_MinDeltaBcn       12
#define User2_TurnMin           12
#define User2_TurnSlope         80

#define User3_Callsign          "CD2RXU-9"
#define User3_Symbol            ">"         // Car
#define User3_SlowRate          120
#define User3_SlowSpeed         10
#define User3_FastRate          60
#define User3_FastSpeed         70
#define User3_MinDistTx         100
#define User3_MinDeltaBcn       10
#define User3_TurnMin           15
#define User3_TurnSlope         80


#endif