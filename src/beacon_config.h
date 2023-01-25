#ifndef BEACON_CONFIG_H_
#define BEACON_CONFIG_H_

#define SlowRate                120     // Seg
#define SlowSpeed               10      // Km/h (3 Runner , 5 Bike, 10 Car)
#define FastRate                60      // Seg
#define FastSpeed               20      // Km/h (20 Runner y Bike, 70 Car)
#define TurnDegrees             20      // Degrees before Forced Beacon Tx (20 Car , 15 Bike/Runner)
#define MinimumDistanceTx       30      // Mts (20 Runner, 100 Car/Bike)
#define MinimumTimeDeltaBeacon  5       // Seg between Tx

#define SendAltitude true               // "true" adds Altitude to the APRS packet/message, "false" add Course+Speed
#define SendComment false               // "true" adds comment to the APRS packet/message

#endif