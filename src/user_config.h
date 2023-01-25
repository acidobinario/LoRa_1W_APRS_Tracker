#ifndef USER_CONFIG_H_
#define USER_CONFIG_H_

#define SRC_CALLSIGN    "CD2RXU-7"              // Change "CD2RXU-7" to your CALLSIGN-SSID you would use in APRS
#define DST_CALLSIGN    "AP"				    // APRS Destination (could be also "WIDE1-1")
#define SYMBOL          "["				        // APRS Symbol:  "[" Runner, "b" Bike, ">" Auto/Car
#define APRS_COMMENT    "Lora Tracker 1W"       // if you want to send any comment change the APRS_COMMENT 
                                                // and also beacon_config.h > SendComment = true
#endif