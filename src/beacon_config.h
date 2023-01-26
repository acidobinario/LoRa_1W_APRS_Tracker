#ifndef BEACON_CONFIG_H_
#define BEACON_CONFIG_H_

// Settings for Car Tracker (for now)
#define SlowRate                300     // Seg (300 = 5min)
#define SlowSpeed               10      // Km/h (3 Runner , 5 Bike, 10 Car)
#define FastRate                30      // Seg
#define FastSpeed               100     // Km/h (20 Runner y Bike, 100 Car)
#define TurnDegrees             20      // Degrees before Forced Beacon Tx (20 Car , 15 Bike/Runner)
#define MinimumDistanceTx       100     // Mts (20 Runner, 100 Car/Bike)
#define MinimumTimeDeltaBeacon  5       // Seg between Tx

#define SendAltitude true               // "true" adds Altitude to the APRS packet/message, "false" add Course+Speed
#define SendComment true                // "true" adds comment to the APRS packet/message

#endif