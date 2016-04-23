#include <OneWire.h> // Inclusion de la librairie OneWire
 
#define DS18B20 0x28     // Adresse 1-Wire du DS18B20
#define BROCHE_ONEWIRE 7 // Broche utilisée pour le bus 1-Wire
 
OneWire OneWire_dev(BROCHE_ONEWIRE); // Création de l'objet OneWire ds
 
// Fonction récupérant la température depuis le DS18B20
// Retourne true si tout va bien, ou false en cas d'erreur
boolean getTemperature(float *temp){ 
  uint8_t data[9], addr[8];
  
  // Search an attached OneWire device
  if(!OneWire_dev.search(addr)) {
    /* If device is found reset OneWire communication
     * and return error
     */
    Serial.print("TEMP : No OneWire found on pin ");
    Serial.println(BROCHE_ONEWIRE);
    OneWire_dev.reset_search();
    return (false);
  }

  // Check the crc
  if (OneWire::crc8 (addr, 7) != addr[7]) {
    // If the crc fails return error
    Serial.println("TEMP : CRC error");
    return (false);
  }

  // Check the OneWire device address
  if (addr[0] != DS18B20) {
    // If the address does not match the expected device address return error
    Serial.print("TEMP : The address of the device is not ");
    Serial.print(DS18B20);
    Serial.print("but ");
    Serial.println(addr[0]);
    return (false);
  }

  // Reset the bus
  OneWire_dev.reset(); 
  // Select the device
  OneWire_dev.select(addr);
  
  // Start a temperature measure
  OneWire_dev.write(0x44, 1);
  // Wait the end of the measure
  delay(800);
   
  // Reset the bus
  OneWire_dev.reset(); 
  // Select the device
  OneWire_dev.select(addr);
  // Get the scratchpad
  OneWire_dev.write(0xBE);    

  // Read the scratchpad and save the data
  for (byte i = 0; i < 9; i++) {
    data[i] = OneWire_dev.read();     
  }

  // Compute the temperature value
  *temp = ((data[1] << 8) | data[0]) * 0.0625; 

  // No error return true
  return(true);
}
 
// setup()
void setup() {
  Serial.begin(9600); // Initialisation du port série
}
 
// loop()
void loop() {
  float temp;
   
  // Lit la température ambiante à ~1Hz
  if(getTemperature(&temp)) {
     
    // Affiche la température
    Serial.print("Temperature : ");
    Serial.print(temp);
    Serial.write(176); // caractère °
    Serial.write('C');
    Serial.println();
  } else {
    Serial.println("Moi pas pouvoir lire");
  }
}
