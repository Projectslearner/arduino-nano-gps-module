/*
    Project name : GPS Sensor
    Modified Date: 10-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-nano-gps-module
*/

#include <SoftwareSerial.h>

// Create a SoftwareSerial object for communication with the GPS module
SoftwareSerial gpsSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600); // Initialize serial communication with the PC
  gpsSerial.begin(9600); // Initialize serial communication with the GPS module
}

void loop() {
  if (gpsSerial.available()) { // If data is available from the GPS module
    String gpsData = gpsSerial.readStringUntil('\n'); // Read a line from the GPS module
    if (gpsData.startsWith("$GPRMC")) { // Check if the line is a GPRMC sentence
      // Split the comma-separated values into an array
      String values[13];
      int pos = 0;
      while (gpsData.indexOf(',') > -1) {
        int index = gpsData.indexOf(',');
        values[pos++] = gpsData.substring(0, index);
        gpsData = gpsData.substring(index + 1);
      }
      values[pos] = gpsData; // Last value after the last comma

      // Extract latitude and longitude from the GPRMC sentence
      if (values[2] == "A") { // Check if GPS fix is available
        float latitude = values[3].toFloat() / 100;
        float longitude = values[5].toFloat() / 100;
        char latDir = values[4].charAt(0);
        char lonDir = values[6].charAt(0);

        // Print latitude and longitude to the serial monitor
        Serial.print("Latitude: ");
        Serial.print(latitude, 6);
        Serial.print(" ");
        Serial.print(latDir);
        Serial.print(" Longitude: ");
        Serial.print(longitude, 6);
        Serial.print(" ");
        Serial.println(lonDir);
      }
    }
  }
}
