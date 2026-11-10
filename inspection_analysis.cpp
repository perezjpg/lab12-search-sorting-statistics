/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: Johnatanel Perez Lopez
 * Lab: 12 - Search, Sorting and Statistics
 * Description: Searches six safety inspections by ID and by area, copies their
 *              vibration readings into a separate array, sorts the copy with
 *              selection sort, and reports the mean, median and mode.
 * Due Date: November 9, 2026
 */

#include <iostream> // Provides console input and output
#include <iomanip> // Provides table and decimal formatting
#include <string> // Provides string and getline
using namespace std;

struct Inspection {
    int id = 0;
    string area;
    double vibration = 0.0;
    bool isEmpty = true;
};

int findInspectionById(const Inspection inspections[], int capacity, int targetId);
int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea);
int copyVibrations(const Inspection inspections[], int capacity, double values[]);
void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);
void displayInspection(Inspection inspection);

int main() {
    const int CAPACITY = 6;
    Inspection inspections[CAPACITY] = {
        {101, "Assembly", 0.30, false},
        {104, "Power", 0.15, false},
        {109, "Assembly", 0.30, false},
        {115, "Thermal", 0.45, false},
        {118, "Power", 0.10, false},
        {123, "Assembly", 0.15, false}
    };
    double sortedVibrations[CAPACITY] = {};
    int menuChoice = 0;

    cout << fixed << setprecision(2);
    do {
        cout << "\nInspection Analysis\n";
        cout << "1. Find inspection by ID\n";
        cout << "2. List inspections by area\n";
        cout << "3. Analyze vibration readings\n";
        cout << "4. Exit\n";
        cout << "Enter option number: ";
        cin >> menuChoice;

        if (menuChoice == 1) {
            int targetId = 0;
            cout << "Enter inspection ID: ";
            cin >> targetId;
            int foundIndex = findInspectionById(inspections, CAPACITY, targetId);
            if (foundIndex == -1) {
                cout << "Inspection not found." << endl;
            } else {
                displayInspection(inspections[foundIndex]);
            }
        } else if (menuChoice == 2) {
            string targetArea;
            cout << "Enter area: ";
            getline(cin >> ws, targetArea);
            int matchCount = displayInspectionsByArea(inspections, CAPACITY, targetArea);
            cout << "Matches: " << matchCount << endl;
        } else if (menuChoice == 3) {
            int valueCount = copyVibrations(inspections, CAPACITY, sortedVibrations);
            if (valueCount == 0) {
                cout << "No readings available for statistics." << endl;
            } else {
                selectionSort(sortedVibrations, valueCount);
                cout << "Values used: " << valueCount << endl;
                cout << "Mean: " << calculateMean(sortedVibrations, valueCount) << endl;
                cout << "Median: " << calculateMedian(sortedVibrations, valueCount) << endl;
                cout << "Mode: ";
                displayModes(sortedVibrations, valueCount);
            }
        } else if (menuChoice != 4) {
            cout << "Invalid option." << endl;
        }
    } while (menuChoice != 4);

    return 0;
}

void displayInspection(Inspection inspection) {
    cout << "ID: " << inspection.id
         << " | Area: " << inspection.area
         << " | Vibration: " << inspection.vibration << endl;
}

int findInspectionById(const Inspection inspections[], int capacity, int targetId) {
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty && inspections[index].id == targetId) {
            return index; // Stops because an ID identifies one inspection
        }
    }
    return -1; // Reports that no occupied position holds the ID
}

int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea) {
    int matchCount = 0;
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty && inspections[index].area == targetArea) {
            displayInspection(inspections[index]);
            matchCount++; // Counts every matching inspection
        }
    }
    return matchCount;
}

int copyVibrations(const Inspection inspections[], int capacity, double values[]) {
    int valueCount = 0;
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty) {
            values[valueCount] = inspections[index].vibration; // Fills the next free position of the copy
            valueCount++;
        }
    }
    return valueCount; // Number of values copied, not the capacity
}

void selectionSort(double values[], int count) {
    for (int start = 0; start < count - 1; start++) {
        int minIndex = start;
        for (int index = start + 1; index < count; index++) {
            if (values[index] < values[minIndex]) {
                minIndex = index; // Remembers the smallest value in the unsorted part
            }
        }
        double temp = values[start];
        values[start] = values[minIndex];
        values[minIndex] = temp; // Moves the smallest value into its final position
    }
}

double calculateMean(const double values[], int count) {
    double total = 0.0;
    for (int index = 0; index < count; index++) {
        total += values[index];
    }
    return total / count;
}

double calculateMedian(const double sortedValues[], int count) {
    int middle = count / 2;
    if (count % 2 == 1) {
        return sortedValues[middle]; // Odd count: one middle value
    }
    return (sortedValues[middle - 1] + sortedValues[middle]) / 2.0; // Even count: average of the two middle values
}

void displayModes(const double sortedValues[], int count) {
    int maxFrequency = 1;
    int runLength = 1;
    for (int index = 1; index < count; index++) {
        if (sortedValues[index] == sortedValues[index - 1]) {
            runLength++; // Equal values are next to each other in a sorted array
        } else {
            runLength = 1;
        }
        if (runLength > maxFrequency) {
            maxFrequency = runLength;
        }
    }

    if (maxFrequency == 1) {
        cout << "N/A" << endl; // No value repeats
        return;
    }

    runLength = 1;
    for (int index = 1; index <= count; index++) {
        if (index < count && sortedValues[index] == sortedValues[index - 1]) {
            runLength++;
        } else {
            if (runLength == maxFrequency) {
                cout << sortedValues[index - 1] << " "; // Displays every value tied at the top frequency
            }
            runLength = 1;
        }
    }
    cout << endl;
}

/*
 * Test Cases:
 * 1. Inputs: option 1, ID 109
 *    Expected: Displays the Assembly inspection with vibration 0.30.
 *    Observed: ID: 109 | Area: Assembly | Vibration: 0.30
 * 2. Inputs: option 1, ID 999
 *    Expected: Displays "Inspection not found."
 *    Observed: Inspection not found.
 * 3. Inputs: option 2, area Assembly; then option 2, area Optics
 *    Expected: Assembly shows three inspections and Matches: 3; Optics shows
 *              no rows and Matches: 0.
 *    Observed: Assembly listed IDs 101, 109 and 123 and printed Matches: 3.
 *              Optics printed no rows and Matches: 0.
 * 4. Inputs: option 3
 *    Expected: Values used: 6, mean 0.24, median 0.23, modes 0.15 and 0.30.
 *    Observed: Values used: 6, Mean: 0.24, Median: 0.22, Mode: 0.15 0.30.
 *              The median is mathematically 0.225, but (0.15 + 0.30) / 2 is
 *              stored in binary as 0.2249999..., so setprecision(2) rounds it
 *              down to 0.22. The two middle values are correct.
 * 5. Inputs: option 8, then option 1 with ID 109
 *    Expected: Reports that the option is not valid and keeps the data.
 *    Observed: Invalid option. The next search still found ID 109 in
 *              Assembly with vibration 0.30, so the records were unchanged.
 */

/*
 * Analysis:
 * 1. findInspectionById returns an index because the caller already knows the
 *    ID it typed. The index is what lets main reach the whole record (area and
 *    vibration) in the array, and -1 can never be a valid index, so it clearly
 *    means "not found".
 * 2. An area is shared by several inspections, unlike an ID. Stopping after the
 *    first match would hide the other Assembly inspections, so the function
 *    must check every position to display and count all of them.
 * 3. index walks through every position of inspections, including empty ones.
 *    valueCount only advances when a reading is copied, so the copied values
 *    stay packed at the start of values with no gaps, and the function can
 *    return how many readings were actually copied instead of the capacity.
 * 4. Sorting inspections would rearrange the original records and change the
 *    order the queries show. Sorting only the separate copy, sortedVibrations,
 *    gives the median and mode the ordered values they need while the IDs,
 *    areas and readings in inspections stay exactly as they were registered.
 * 5. With six sorted readings (0.10 0.15 0.15 0.30 0.30 0.45), the median is
 *    the average of the two middle values at indexes 2 and 3: 0.15 and 0.30.
 */
