#include <chrono>
#include <random>
#include <ctime>
#include <iostream>

void printArray(int *values, int values_count) {
    for (int i = 0; i < values_count; i++) {
        std::cout << values[i];
        if (i != values_count - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int searchArray(int const *values, int values_count, int value) {
    // Return index in array for found value
    int left = 0;
    int right = values_count - 1;
    while (left < right) {
        int middle = (left + right) / 2;
        if (*(values + middle) < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

int *insertArray(int *values, int *values_count, int value) {
    int *new_array = new int[*values_count + 1];

    // Copy over old array
    for (int i = 0; i < *values_count; i++) {
        new_array[i] = values[i];
    }

    // Look up where to insert value
    int index = searchArray(values, *values_count, value);
    // Values is no longer needed and is copied into new_array
    delete values;

    // Start only from the point where value needs to be inserted
    for (int i = index; i <= *values_count; i++) {

        // Temporarily store value that will be overridden
        int next_value = *(new_array + i);

        // Insert value at new pointer
        *(new_array + i) = value;

        // For next iteration, restore previously temp stored value
        value = next_value;
    }

    *values_count =  *values_count + 1;
    return new_array;
}

int main() {
    int *values = new int[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int values_count = 10;

    // Pointer won't change, but its value will
    int *values_count_ptr = &values_count;

    // Initialize our mersenne twister with a random seed
    std::mt19937 mersenne(static_cast<unsigned int>(std::time(nullptr)));

    // Create a reusable random number generator
    std::uniform_int_distribution<> generator(1, 1000000);

    std::chrono::time_point<std::chrono::system_clock> p1;
    p1 = std::chrono::system_clock::now();

    for(int i = 0; i < 25000; ++i) {
        int value = generator(mersenne);
        values = insertArray(values, values_count_ptr, value);
    }

    std::chrono::time_point<std::chrono::system_clock> p2;

    p2 = std::chrono::system_clock::now();

    std::cout << "Duration: " <<
              std::chrono::duration_cast<std::chrono::milliseconds>(p2 - p1).count()
              << " milliseconds "<< std::endl;

    return 0;
}