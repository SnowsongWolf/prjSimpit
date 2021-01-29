Serial communication protocol:

Byte 0: Command type
Byte 1: Data Type
Byte 2: MSB/Value 1
Byte 3: LSB/Value 2

Command type:
  01: Button Action
      Data Type:
        01: Down
        02: Up
        03: Press
        04: Long Press
      MSB:  Device ID
            01: Joy Left
            02: Joy Right
            03: Throttle
            04: Rudder
            05: Wheel (?)
            06: MFCD Left
            07: MFCD Right
      LSB:  Button Index
  
