# Advance Barricade System with RFID and Ultrasonic Sensors

This project is an Arduino-based Advance Barricade System that utilizes RFID card authentication and ultrasonic sensors to control a servo-based gate mechanism. The system is designed to open the gate for authorized RFID cardholders while keeping the gate closed for unauthenticated individuals.

## Components

- Arduino board (e.g., Arduino Uno)
- Servo motors
- Ultrasonic sensors (2)
- RFID-RC522 module
- LiquidCrystal_I2C display
- Various resistors, wires, and a breadboard

## Functionality

1. **RFID Authentication**: The system uses the RFID-RC522 module to read RFID cards. Authorized RFID cardholders can gain access to the area.

2. **Ultrasonic Sensors**: Two ultrasonic sensors are used to monitor the presence of vehicles or objects on either side of the gate.

3. **Gate Control**: 
   - When an authorized RFID card is detected and there are no obstructions (vehicles) on both sides of the gate (determined by ultrasonic sensors), the gate opens.
   - If an ambulance is detected (based on ultrasonic sensor readings), the gate opens to allow the ambulance to pass.

## Setup

- Connect the components as per the wiring instructions in your Arduino sketch.
- Upload the provided Arduino sketch to your Arduino board.

## Usage

1. Power on the system.
2. Present an authorized RFID card to the RFID-RC522 module.
3. If the card is authorized, the gate opens if there are no obstructions.
4. If an ambulance is detected, the gate opens to allow it to pass.

## Configuration

- You can customize the system's behavior by adjusting the RFID card UID (`UID`), ultrasonic sensor pins, servo positions, and other parameters in the Arduino sketch.

## Dependencies

- This project depends on external libraries including the `Servo`, `LiquidCrystal_I2C`, and `MFRC522` libraries. Ensure you have them installed in your Arduino IDE.

## Authors

- [Your Name]

## License

This project is open-source and available under the [MIT License](LICENSE).
