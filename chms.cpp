#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>

// CropHealthMonitoringSystem class definition
/*
The CropHealthMonitoringSystem class simulates a monitoring system for crop health.
It tracks soil moisture levels and pH levels, and can control an irrigation system and fertilizer application based on 
these levels. The class also logs sensor data to CSV and JSON files.
*/
class CropHealthMonitoringSystem {

public:
    CropHealthMonitoringSystem() : soilMoistureLevel(100.0), phLevel(12.0), irrigationSystem(false) {
        std::ofstream file("sensor_data.csv", std::ios::app);
        file << "soil_moisture_level,ph_level\n";
        file.close();
    }

    // Method to update crop parameters
    /*
    Updates the soil moisture and pH levels, logging the changes every second. It decreases soil moisture by 5% every second and pH level by 1 every 3 seconds. Updates the JSON data after each change.
    */

    void updateCropParameters() {
        writeDataToFile(soilMoistureLevel, phLevel);
        auto startTime = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(1)) {
            // Wait for 1 second
        }

        // Drop soil moisture level by 5% every 1 second
        soilMoistureLevel -= 5.0;
        if (soilMoistureLevel < 0.0) {
            soilMoistureLevel = 0.0;
        }

        // Drop pH level by 1 every 3 seconds
        if (std::chrono::steady_clock::now() - lastPhUpdate >= std::chrono::seconds(3)) {
            lastPhUpdate = std::chrono::steady_clock::now();
            phLevel -= 1.0;
            if (phLevel < 0.0) {
                phLevel = 0.0;
            }
        }

        // Update JSON data
        updateJsonData();
    }

    // Method to check crop health
    /*
    Checks the current soil moisture and pH levels, and triggers alerts if levels drop below thresholds (30% for soil moisture and 4 for pH). It starts the irrigation system or applies fertilizers if necessary. Logs data and updates JSON after each check.
    */

    void checkCropHealth() {
        std::cout << "Soil Moisture Level: " << soilMoistureLevel << std::endl;
        std::cout << "pH Level: " << phLevel << std::endl;
        writeDataToFile(soilMoistureLevel, phLevel);
        auto startTime = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(1)) {
            // Wait for 1 second
        }

        if (soilMoistureLevel < 30.0) {
            std::cout << "Alert: Soil moisture level is below threshold!" << std::endl;
            Beep(2500, 1000);
            // PlaySound(TEXT("soilMoisture.mp3"), NULL, SND_SYNC);
            startIrrigationSystem();
        }
        if (phLevel < 4.0) {
            std::cout << "Alert: pH level is below threshold!" << std::endl;
            Beep(2500, 1000);
            // PlaySound(TEXT("phLevel.mp3"), NULL, SND_SYNC);
            giveFertilizers();
        }

        // Update JSON data
        updateJsonData();
    }


    // Method to start the irrigation system
    /*
    Activates the irrigation system for 3 seconds, replenishing soil moisture to 100%. Logs the action and updates JSON data.
    */

    void startIrrigationSystem() {
        std::cout << "Irrigation system started!" << std::endl;

        auto startTime = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(3)) {
            // Wait for 3 seconds
        }

        soilMoistureLevel = 100.0;
        std::cout << "Irrigation system stopped!" << std::endl;

        // Update JSON data
        updateJsonData();
    }

    // Method to apply fertilizers
    /*
    Sprays fertilizers for 5 seconds, resetting pH levels to 12. Logs the action and updates JSON data.
    */
    void giveFertilizers() {
        std::cout << "Sprinking Fertilizers!" << std::endl;
        auto startTime = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(5)) {
            // Wait for 5 seconds
        }
        phLevel = 12.0;
        std::cout << "Fertilizers stopped!" << std::endl;

        // Update JSON data
        updateJsonData();
    }

private:
    double soilMoistureLevel;                               // stores current soil moisture level
    double phLevel;                                         // stores current pH level
    bool irrigationSystem;                                  // State of the irrigation system
    std::chrono::steady_clock::time_point lastPhUpdate;     // Time point for last pH level update

    // Method to update JSON data
    /*
    Writes the current soil moisture and pH levels to a JSON file.
    */
    void updateJsonData() {
        std::ofstream outFile("data.json");
        outFile << "{\n";
        outFile << "  \"soil_moisture_level\": " << soilMoistureLevel << ",\n";
        outFile << "  \"ph_level\": " << phLevel << "\n";
        outFile << "}\n";
    }

    // Method to write data to CSV file
    /*
    Logs the current soil moisture and pH levels to a CSV file.
    */
    void writeDataToFile(float soilMoistureLevel, float phLevel){
        std::ofstream file("sensor_data.csv", std::ios::app);
        file << soilMoistureLevel << "," << phLevel << "\n";
        file.close();
    }
};

// Main function
/*
Initializes the CropHealthMonitoringSystem and continuously updates crop parameters and checks crop health in an
infinite loop.
*/
int main() {
    CropHealthMonitoringSystem system;

    while (true) {
        system.updateCropParameters();
        system.checkCropHealth();
    }

    return 0;
}
