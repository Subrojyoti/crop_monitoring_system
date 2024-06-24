#include <iostream>
#include <fstream>
#include <string>
#include <map>

// Global map to store crop names and their average prices
/*
A map that associates crop names with their average prices. The map is populated from a CSV file.
*/
std::map<std::string, double> price_avg_map;

// Function to load the average prices of crops into the map
/*
Reads data from "price_avg.csv" file and populates the price_avg_map with crop names and their corresponding average prices.
*/
void load_price_avg_map() {
    std::ifstream file("price_avg.csv");
    std::string line, crop, avg;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        size_t comma = line.find(',');
        crop = line.substr(0, comma);
        avg = line.substr(comma + 1);
        price_avg_map[crop] = std::stod(avg);
    }
    file.close();
}
// Main function
/*
Main function takes a crop name as a command-line argument and prints its average price. It loads the crop price data from a CSV file into a map and checks if the crop exists in the map. If the crop is found, its average price is printed; otherwise, an error message is displayed.
*/
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <crop_name>" << std::endl;
        return 1;
    }

    load_price_avg_map();

    std::string crop_name = argv[1];
    if (price_avg_map.find(crop_name) != price_avg_map.end()) {
        std::cout << crop_name << ": " << price_avg_map[crop_name] << std::endl;
    } else {
        std::cerr << "Crop not found: " << crop_name << std::endl;
        return 1;
    }

    return 0;
}