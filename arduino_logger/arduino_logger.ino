#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219_A;
Adafruit_INA219 ina219_B(0x41);

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219_A.begin();
  ina219_B.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (highina219_A.begin();er precision on volts and amps):
  ina219_A.setCalibration_16V_400mA();
  ina219_B.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  float solar_voltage = 0;
  float solar_current = 0;
  float battery_voltage = 0;
  float battery_current = 0;
  
  solar_voltage = ina219_A.getShuntVoltage_mV();
  solar_voltage += ina219_A.getBusVoltage_V();
  solar_current = ina219_A.getCurrent_mA();
 
  battery_voltage = ina219_B.getShuntVoltage_mV();
  battery_voltage += ina219_B.getBusVoltage_V();
  battery_current = ina219_B.getCurrent_mA();

  Serial.print("Solar Voltage:   "); Serial.print(solar_voltage); Serial.println(" V");
  Serial.print("Solar Current:       "); Serial.print(solar_current); Serial.println(" mA");
  Serial.print("Battery Voltage:   "); Serial.print(battery_voltage); Serial.println(" V");
  Serial.print("Battery Current:       "); Serial.print(battery_current); Serial.println(" mA");
  Serial.println("");

  delay(2000);
}
