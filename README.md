# LORA (1 Watt Module) APRS Tracker

This LORA APRS Tracker will work with very cheep hardware (amazon, ebay or aliexpress):
- ESP32             ( ESP32 Dev Module)
- Ebyte E22 400M30S  (1 Watt (30dB) Lora SPI Module)
- GY-GPSNEO6MV2     (NEO6M GPS Module)

This project uses Enconded APRS GPS packet to extends range by saving bytes (increased battery life, higher chances of good packet reception (increased range), lower probability of packet collisions (more channel capacity) and 1 Watt LoRa Module (over the usual 0.1 Watt in commercial boards like the LILYGO T-Beam V.1).




This Repository is based on lots of other Lora APRS Tracker ideas like:

- https://github.com/lora-aprs/LoRa_APRS_Tracker      (the start with LILYGO T-BEAM v.1)
- https://github.com/aprs434/lora.tracker             (the great encoding position modification)
- https://github.com/Mane76/lora.tracker              (great ideas about changing callsign and other mods)
- https://github.com/sh123/esp32_loraprs              (inspiration for accesing the Lora Module with Radiolib library)




things to do:
- add wiki 
- add status update (on the works)
- add message to another APRS capable Radio (on the works)
- add translation to Spanish (and German?)
- add OLED Screen (allready Bought)
- add schematic for the wiring
- add info of 5V DC stepup and charging battery
- add battery monitoring + charging
- add photos of prototipe
- add PCB (with eagle and gerber)
