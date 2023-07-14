#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Car {
    string mark;
    string model;
    string color;
    string max_speed;
    int price;
};

// Function to display car details
void DisplayCars(const vector<Car>& cars) {
    if (cars.empty()) {
        cout << "\nNo cars available.\n";
        return;
    }
    cout << "Car Details:\n";
    cout << "---------------------------------------------\n";
    for (const Car& car1 : cars) {
    
        cout << "\nMark: " << car1.mark << endl;
        cout << "Model: " << car1.model << endl;
        cout << "Color: " << car1.color << endl;
        cout << "Max Speed: " << car1.max_speed << endl;
        cout << "Price: " << car1.price << "K\n" << endl;
        cout << "---------------------------------------------\n" << endl;
    }
    }


void WriteCarsToFile(const vector<Car>& cars) {
    ofstream outputFile("car_final.txt");
    if (outputFile.is_open()) {
        for (const Car& car : cars) {
            if (car.mark.empty()) {
                continue; // Skip deleted cars
            }
            outputFile << car.mark << endl;
            outputFile << car.model << endl;
            outputFile << car.color << endl;
            outputFile << car.max_speed << endl;
            outputFile << car.price << endl;
        }
        outputFile.close();
        cout << "\nCar details written to file successfully!\n";
    } else {
        cout << "\nFailed to open the file for writing.\n";
    }
}

void InsertCar(vector<Car>& cars, unordered_map<string, Car>& carHashTable) {
    Car newCar;
    cout << "\nEnter Car Details:\n";
    cout << "\nMark: ";
    cin.ignore();
    getline(cin, newCar.mark);
    cout << "Model: ";
    getline(cin, newCar.model);
    cout << "Color: ";
    getline(cin, newCar.color);
    cout << "Max Speed: ";
    getline(cin, newCar.max_speed);
    cout << "Price: ";
    cin >> newCar.price;

    cars.push_back(newCar);
    carHashTable[newCar.model] = newCar;
    cout << "\nCar inserted successfully!\n";

    WriteCarsToFile(cars);
}

void DeleteCar(std::vector<Car>& cars, std::unordered_map<std::string, Car>& carHashTable) {
    string model;
    cout << "\nEnter the model of the car to delete: ";
    cin.ignore();
    getline(cin, model);

    auto it = carHashTable.find(model);
    if (it != carHashTable.end()) {
        cars.erase(remove_if(cars.begin(), cars.end(), [&](const Car& car) {
            return car.model == model;
        }), cars.end());

        carHashTable.erase(it);
        cout << "\nCar deleted successfully!\n";
        WriteCarsToFile(cars);
    } else {
        cout << "\nCar not found.\n";
    }
}

void SearchCar(const unordered_map<string, Car>& carHashTable) {
    string model;
    cout << "\nEnter the model of the car to search: ";
    cin.ignore();
    getline(cin, model);

    auto it = carHashTable.find(model);
    if (it != carHashTable.end()) {
        const Car& car = it->second;
        cout << "\nCar Details:\n";
        cout << "---------------------------------------------\n";
        cout << "\nMark: " << car.mark << endl;
        cout << "Model: " << car.model << endl;
        cout << "Color: " << car.color << endl;
        cout << "Max Speed: " << car.max_speed << endl;
        cout << "Price: " << car.price << "K\n" << endl;
        cout << "---------------------------------------------\n" << endl;
    } else {
        cout << "\nCar not found.\n";
    }
}

int main() {
    vector<Car> cars;
    unordered_map<string, Car> carHashTable;

    ifstream inputFile("car_final.txt");
    if (inputFile.is_open()) {
        string mark, model, color, max_speed;
        int price;
        while (getline(inputFile, mark)) {
            getline(inputFile, model);
            getline(inputFile, color);
            getline(inputFile, max_speed);
            inputFile >> price;
            inputFile.ignore(); // Ignore the newline character

            Car newCar;
            newCar.mark = mark;
            newCar.model = model;
            newCar.color = color;
            newCar.max_speed = max_speed;
            newCar.price = price;
            cars.push_back(newCar);
            carHashTable[model] = newCar;
        }
        inputFile.close();
    } else {
        cout << "Failed to open the file.\n";
        return 0;
    }

    int choice;
    do {
        cout << "Car Rental System\n";
        cout << "----------------------\n";
        cout << "1. Display Car Details\n";
        cout << "2. Insert a New Car\n";
        cout << "3. Delete a Car\n";
        cout << "4. Search for a Car\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                DisplayCars(cars);
                break;
            case 2:
                InsertCar(cars, carHashTable);
                break;
            case 3:
                DeleteCar(cars, carHashTable);
                break;
            case 4:
                SearchCar(carHashTable);
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
