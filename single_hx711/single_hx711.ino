#include <HX711.h>

HX711 scale(6, 5); //HX711 scale(6, 5);

float calibration_factor = -434;
float initial_units; // initial weight in grams
float current_units; // current weight in grams
float previous_units; // previous weight in grams
float used_volume; // used volume in cubic meters
float total_cost; // total cost in IDR
float cost; // cost in IDR
const float price_per_m3 = 10000; // price per cubic meter in IDR

void setup()
{
  Serial.begin(9600);
  Serial.println("HX711 Weighing System Initialized");
  scale.set_scale(calibration_factor);
  scale.tare();
  delay(1000); // Wait for the scale to stabilize

  // Measure and store initial weight
  initial_units = scale.get_units(10);
  if (initial_units < 0)
  {
    initial_units = 0.00;
  }

  previous_units = initial_units;
  used_volume = 0.0;
  cost = 0.0;
  total_cost = 0.0;

  // Display initial state
  Serial.println("\nInitial State:");
  Serial.print("  Initial Weight: ");
  Serial.print(initial_units);
  Serial.println(" grams");

  Serial.print("  Initial Volume: ");
  Serial.print(initial_units / 1000000.0, 6);
  Serial.println(" m³");

  Serial.print("  Initial Cost: IDR ");
  Serial.println(total_cost, 2);
  Serial.println("------------------------------");
}

void loop()
{
  Serial.print("Reading: ");
  current_units = scale.get_units(10);
  if (current_units < 0)
  {
    current_units = 0.00;
  }

  if (current_units < previous_units) {
    // Water used
    float volume_used = (previous_units - current_units) / 1000000.0;
    total_cost += volume_used * price_per_m3;
    used_volume += volume_used;

    Serial.println("\nWater Usage Detected:");
    Serial.print("  Water Used: ");
    Serial.print(volume_used, 6); // Print used volume in cubic meters with 6 decimal places
    Serial.println(" m³");

    cost = volume_used * price_per_m3;
    Serial.print("  Cost for This Usage: IDR ");
    Serial.println(cost, 2); // Print cost with 2 decimal places
  }

  Serial.println("\nCurrent State:");
  Serial.print("  Current Weight: ");
  Serial.print(current_units);
  Serial.println(" grams");

  Serial.print("  Current Volume: ");
  Serial.print(current_units / 1000000.0, 6); // Print volume in cubic meters with 6 decimal places
  Serial.println(" m³");

  Serial.print("  Total Cost: IDR ");
  Serial.println(total_cost, 2); // Print total cost with 2 decimal places
  Serial.println("------------------------------");

  previous_units = current_units;
  delay(5000);
}
