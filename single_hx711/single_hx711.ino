#include <HX711.h>

HX711 scale(6, 5); //HX711 scale(6, 5);

float calibration_factor = -434;
float units; // weight in grams
float volume; // volume in cubic meters
float cost; // cost in IDR
const float price_per_m3 = 10000; // price per cubic meter in IDR

void setup()
{
  Serial.begin(9600);
  Serial.println("HX711 weighing");
  scale.set_scale(calibration_factor);
  scale.tare();
  Serial.println("Readings:");
}

void loop()
{
  Serial.print("Reading:");
  units = scale.get_units(),10;
  if (units < 0)
  {
    units = 0.00;
  }

  // Convert grams to cubic meters
  volume = units / 1000000.0;

  // Calculate cost
  cost = volume * price_per_m3;

  Serial.print(" Weight: ");
  Serial.print(units);
  Serial.print(" grams");

  Serial.print(" Volume: ");
  Serial.print(volume, 6); // Print volume in cubic meters with 6 decimal places

  Serial.print(" m³");

  Serial.print(" Cost: IDR ");
  Serial.println(cost, 2); // Print cost with 2 decimal places

  delay(500);
}
