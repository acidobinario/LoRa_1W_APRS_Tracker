#ifndef BEACON_CONFIG_H_
#define BEACON_CONFIG_H_

#define FirstUser               1           // Select the First User at Tracker Start Up (Example: 1 means User1)
#define AprsPath                "APLT00"    // APRS Destination (could be also "WIDE1-1" or even just "AP")
#define AprsOverlay             "/"
#define SendAltitude            true        // "true" adds Altitude to the APRS packet/message, "false" add Course+Speed
#define SendComment             true        // "true" adds comment to the APRS packet/message
#define APRS_COMMENT            "Lora Tracker 1W"   // To send this comment --> SendComment = true (edit the comment as you like)

#define User1_Callsign          "CD2RXU-7"  // This is my Callsign , so go on and change it to yours!!!
#define User1_Symbol            "["         // Runner
#define User1_SlowRate          120         // seg
#define User1_SlowSpeed         3           // km/h
#define User1_FastRate          60          // seg
#define User1_FastSpeed         15          // km/h
#define User1_MinDistTx         5           // debe ser 100 pero esta 5 por pruebas 
#define User1_MinDeltaBcn       20          // seg between beacon update
#define User1_TurnMinDeg        3           // degrees
#define User1_TurnSlope         40          // constant

#define User2_Callsign          "CD2RXU-8"  // This is my Callsign , so go on and change it to yours!!!
#define User2_Symbol            "b"         // Bicycle
#define User2_SlowRate          120
#define User2_SlowSpeed         5
#define User2_FastRate          60
#define User2_FastSpeed         40
#define User2_MinDistTx         100
#define User2_MinDeltaBcn       12
#define User2_TurnMinDeg        12
#define User2_TurnSlope         60

#define User3_Callsign          "CD2RXU-9"  // This is my Callsign , so go on and change it to yours!!!
#define User3_Symbol            ">"         // Car
#define User3_SlowRate          120
#define User3_SlowSpeed         10
#define User3_FastRate          60
#define User3_FastSpeed         70
#define User3_MinDistTx         100
#define User3_MinDeltaBcn       8
#define User3_TurnMinDeg        10
#define User3_TurnSlope         80

#endif