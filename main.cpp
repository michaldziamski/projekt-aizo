#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>
#include "SortAlgorithm.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "BubbleSort.h"
#include "BinaryInsertionSort.h"

enum class DataType { INT, FLOAT, DOUBLE, CHAR };

template <typename T>
void displayArray(T* array, int size) {
    std::cout << "\nArray:\n";
    const int elementsPerLine = 10;  // Ile elementów wyświetlić w jednym wierszu
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
        if ((i + 1) % elementsPerLine == 0) {
            std::cout << "\n";  // Dodaj nową linię po wyświetleniu określonej liczby elementów
        }
    }
    std::cout << "\n";
}

template <typename T>
SortAlgorithm<T>* getSortAlgorithm(int choice) {
    switch(choice) {
        case 1: return new InsertionSort<T>();
        case 2: return new HeapSort<T>();
        case 3: return new QuickSort<T>();
        case 4: return new MergeSort<T>();
        case 5: return new BubbleSort<T>();
        case 6: return new BinaryInsertionSort<T>();
        default: return nullptr;

    }
}

template <typename T>
double measureSortingTime(SortAlgorithm<T>& sortAlgorithm, T* array, int size) {
    auto start = std::chrono::high_resolution_clock::now(); //zmienna - początek zegara

    T* tempArray = new T[size];
    std::copy(array, array + size, tempArray);
    sortAlgorithm.sort(tempArray, size);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start; //zmienna - koniec zegara
    delete[] tempArray;
    return elapsed.count();
}


template <typename T>
bool isValidSizeInput(const std::string& input) {
    return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}

void printDataType() {
    std::cout << "Choose data type:\n";
    std::cout << "1. int\n";
    std::cout << "2. float\n";
    std::cout << "3. double\n";
    std::cout << "4. char\n";
    std::cout << "Enter your choice: ";

}

template <typename T>
void performSortingAndMeasureTime(T* array, int size) {
    int sortChoice;
    std::cout << "\nChoose sorting algorithm:\n";
    std::cout << "1. Insertion Sort\n";
    std::cout << "2. Heap Sort\n";
    std::cout << "3. Quick Sort\n";
    std::cout << "4. Merge Sort\n";
    std::cout << "5. Bubble Sort\n";
    std::cout << "6. Binary Insertion Sort\n";
    std::cout << "Enter your choice: ";

    std::string input;
    std::getline(std::cin, input);
    std::stringstream stream(input);
    if (!(stream >> sortChoice) || sortChoice < 1 || sortChoice > 5) {
        std::cerr << "Invalid input for sorting algorithm. Please enter a number between 1 and 5.\n";
        return;
    }

    SortAlgorithm<T>* sortAlgorithm = getSortAlgorithm<T>(sortChoice);
    if (sortAlgorithm) {
        double sortingTime = measureSortingTime(*sortAlgorithm, array, size);
        std::cout << "\nSorting time: " << sortingTime << " milliseconds\n";

        delete sortAlgorithm; // Free memory
    } else {
        std::cerr << "Invalid choice for sorting algorithm.\n";
    }
}


template <typename T>
T* loadDataFromFile(int& size, const std::string& filename) {

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << filename; //sprawdzenie czy otwarty
        return nullptr;
    }

    std::string line;
    if (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        if (!(ss >> size) || size <= 0) {
            std::cerr << "Invalid data in the file.\n"; // << sprawdzenie poprawności rozmiaru
            inputFile.close();
            return nullptr;
        }
        T* array = new T[size];

        for (int i = 0; i < size; ++i) {
            if (std::getline(inputFile, line)) { //jeśli można pobrac linie z pliku do zmiennej line
                std::stringstream data_ss(line);
                T value;
                if (!(data_ss >> value)) {
                    std::cerr << "Invalid data format in the file.\n" ;//<< std::endl;
                    delete[] array;
                    inputFile.close();
                    return nullptr;
                }
                array[i] = value;
            } else {
                std::cerr << "Insufficient data in the file.\n"; //<< std::endl;
                delete[] array;
                inputFile.close();
                return nullptr;
            }
        }

        std::cout << "Data loaded successfully from file.\n";

        return array;
    } else {
        std::cerr << "Empty file.\n"; //<< std::endl;
    }
    inputFile.close();
    return nullptr;
}

template <typename T>
T* createSorted(int size, DataType dataType, bool sortingType){ //funkcja tworząca tablice całkowicie posortowane malejąco bądź rosnąco
    T* newArray = new T[size]; //dynamiczne alokowanie pamięci dla tablicy typu T i zapisuje wskaźnik do nowej tablicy
    std::random_device rd;
    std::mt19937 gen(rd());

    switch(dataType) {
        case DataType::INT: {
            int help = 0;
            int targetValue = 200000;
            int averageValue = targetValue/size;
            int delta = 5;
            std::uniform_int_distribution<> dis(averageValue-delta, averageValue+delta);
            if(sortingType){
                for (int i = 0; i<size; i++){
                    help = help + dis(gen);
                    if(help>=targetValue){
                        help=targetValue;
                    }
                    newArray[i]=help;
                }

            }
            else {
                help = 200000;
                for (int i = 0; i<size; i++){
                    help = help - dis(gen);
                    if(help<=0){
                        help=0;
                    }
                    newArray[i]=help;
                }
            }

            break;
        }
        case DataType::FLOAT: {
            float help = 0.0;
            float targetValue = 100000.0;
            float averageValue = targetValue/size;
            float delta = 5.0;

            std::uniform_real_distribution<float> dis(averageValue-delta, averageValue+delta); //sprobuj dodac tu floaty
            if(sortingType){
                for (int i = 0; i<size; i++){
                    help = help + dis(gen);
                    if(help>=targetValue){
                        help=targetValue;
                    }
                    newArray[i]=help;
                }
            }
            else {
                help = 100000.0;
                for (int i = 0; i<size; i++){
                    help = help - dis(gen);
                    if(help<=0.0){
                        help=0.0;
                    }
                    newArray[i]=help;
                }
            }

            break;
        }
        case DataType::DOUBLE: {
            double help = 0.0;
            double targetValue = 100000.0;
            double averageValue = targetValue/size;
            double delta = 5.0;
            std::uniform_real_distribution<double> dis(averageValue-delta, averageValue+delta);
            if(sortingType){
                for (int i = 0; i<size; i++){
                    help = help + dis(gen);
                    if(help>=targetValue){
                        help=targetValue;
                    }
                    newArray[i]=help;
                }
            }
            else {
                help = 100000.0;
                for (int i = 0; i<size; i++){
                    help = help - dis(gen);
                    if(help<=0.0){
                        help=0.0;
                    }
                    newArray[i]=help;
                }
            }

            break;
        }
        case DataType::CHAR: {
            std::uniform_int_distribution<> dis(1, size/26);

            if(sortingType){
                char currentChar = 'a';
                int random;
                for (int i = 0; i<size; i++){
                    random = dis(gen);
                    if(currentChar=='z') {
                        random=0;
                    }
                    if(random==1){
                        currentChar++;
                    }
                    newArray[i]=currentChar;
                }
            }
            else {
                char currentChar = 'z';
                int random;
                for (int i = 0; i<size; i++){
                    random = dis(gen);
                    if(currentChar=='a') {
                        random=0;
                    }
                    if(random==1){
                        currentChar--;
                    }
                    newArray[i]=currentChar;
                }
            }

            break;
        }
    }

    return newArray;
}



template <typename T>
T* createPartiallySorted(int size, DataType dataType,bool percentage) { //tworzy tablice częściowo posortowane
    double percent;
    if(percentage){
        percent=0.33;
    }
    else{
        percent=0.66;
    }
    T* newArray = new T[size];
    std::random_device rd;
    std::mt19937 gen(rd());
    switch(dataType) {
        case DataType::INT: {
            std::uniform_int_distribution<> dis(1, 100000);
            for(int i = 0; i<percent*size; i++){
                newArray[i]=i;
            }
            for (int i = percent*size; i < size; ++i) {
                newArray[i] = dis(gen);
            }

            break;
        }
        case DataType::FLOAT: {
            std::uniform_real_distribution<float> dis(1.0f, 100000.0f);
            for(int i = 0; i<percent*size; i++){
                newArray[i]=float(i)+0.1;
            }
            for (int i = percent*size; i < size; ++i) {
                newArray[i] = dis(gen);
            }

            break;
        }
        case DataType::DOUBLE: {
            std::uniform_real_distribution<double> dis(1.0, 100000.0);
            for(int i = 0; i<percent*size; i++){
                newArray[i]=double(i)+0.1;
            }
            for (int i = percent*size; i < size; ++i) {
                newArray[i] = dis(gen);
            }

            break;
        }
        case DataType::CHAR: {
            std::uniform_int_distribution<> dis('a', 'z');

            int help=(size*percent)/26 +1;
            //std::cout << help;
            char currentChar = 'a';
            int postion = 0;
            for (int i = 0; i < size*percent; i++){

                for (int j = 0; j < help; j++){
                    newArray[postion]=currentChar;

                    postion++;
                }
                currentChar++;
            }
            for (int i =size*percent; i < size; ++i) {
                newArray[i] = dis(gen);
            }
            break;
        }
    }

    return newArray;
}


template <typename T>
T* createArray(int size, DataType dataType) { //tworzy tablice o loswej zawertości
    T* newArray = new T[size];
    std::random_device rd;
    std::mt19937 gen(rd());
    switch(dataType) {
        case DataType::INT: {
            std::uniform_int_distribution<> dis(1, 100000);
            for (int i = 0; i < size; ++i) {
                newArray[i] = dis(gen);
            }
            break;
        }
        case DataType::FLOAT: {
            std::uniform_real_distribution<float> dis(1.0f, 100000.0f);
            for (int i = 0; i < size; ++i) {
                newArray[i] = dis(gen);
            }
            break;
        }
        case DataType::DOUBLE: {
            std::uniform_real_distribution<double> dis(1.0, 100000.0);
            for (int i = 0; i < size; ++i) {
                newArray[i] = dis(gen);
            }
            break;
        }
        case DataType::CHAR: {
            std::uniform_int_distribution<> dis('a', 'z');
            for (int i = 0; i < size; ++i) {
                newArray[i] = dis(gen);
            }
            break;
        }
    }

    return newArray;
}

template <typename T>
void cleanUp(T*& array) { //funkcja zwalniająca pamięć
    if (array) {
        delete[] array;
        array = nullptr;
    }
}


int main() {
    int* intArray = nullptr;
    float* floatArray = nullptr;
    double* doubleArray = nullptr;
    char* charArray = nullptr;

    DataType dataTypeChoice;
    int size = 0;
    int choice = 0;
    std::string filename;


    while (true) {

        /* tu byl algorytm liczący dane do sprawozdania
        float czas = 0.0;
        float czas1;
        size=2500;
        for (int i = 0; i < 100; i++) {
            charArray= createPartiallySorted<char>(size, DataType::DOUBLE,false);
            //displayArray(intArray,2500);
            QuickSort<char> QuickSort;  // Utwórz instancję InsertionSort dla typu int
            czas1 = measureSortingTime(QuickSort, charArray,size);
            std::cout<<i<<".czas pojedynczy: "<<czas1<<"\n";
            czas = czas + czas1; // Wywołaj sortowanie dla danego typu

        }
        float srednia = czas / 100;
        std::cout << "srednia: " << srednia <<"\n" ;
        */


        std::string input;

        std::cout << "\nMenu:\n";
        std::cout << "1. Load array from file\n";
        std::cout << "2. Generate random array\n";
        std::cout << "3. Display array\n";
        std::cout << "4. Sort array and measure time\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";


        std::getline(std::cin, input);
        std::stringstream stream(input);






        if (!(stream >> choice) || choice < 1 || choice > 5) {
            std::cerr << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }
        switch (choice) {
            case 1: {
                std::cout << "Enter filename: ";
                std::getline(std::cin, filename);

                int help;
                printDataType();
                std::cin >> help;

                switch (help) { //w zaleznosci od typu danych wczytujemy dane z pliku do tablicy
                    case 1:
                        dataTypeChoice = DataType::INT;
                        intArray = loadDataFromFile<int>(size, filename);
                        break;
                    case 2:
                        dataTypeChoice = DataType::FLOAT;
                        floatArray = loadDataFromFile<float>(size, filename);
                        break;
                    case 3:
                        dataTypeChoice = DataType::DOUBLE;
                        doubleArray = loadDataFromFile<double>(size, filename);
                        break;
                    case 4:
                        dataTypeChoice = DataType::CHAR;
                        charArray = loadDataFromFile<char>(size, filename);
                        break;
                    default:
                        std::cerr << "Invalid data type choice.\n";
                        break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //ta linia usuwa zbędne znaki nowej linii
                break;
            }

            case 2: {
                int dataType;
                printDataType();

                std::string dataTypeInput;
                std::getline(std::cin, dataTypeInput);
                std::stringstream dataTypeStream(dataTypeInput);
                if (!(dataTypeStream >> dataType) || dataType < 1 || dataType > 4) {
                    std::cerr << "Invalid input for data type. Please enter a number between 1 and 4.\n";
                    break;
                }

                std::string sizeInput;
                std::cout << "Enter array size: ";
                std::getline(std::cin, sizeInput);
                if (!isValidSizeInput<int>(sizeInput)) {
                    std::cerr << "Invalid array size input. Please enter a valid integer.\n";
                    break;
                }
                size = std::stoi(sizeInput);
                if (size <= 0) {
                    std::cerr << "Invalid array size.\n";
                    break;
                }

                switch (dataType) { // w zaleznosci od typu danych generujemy tablice
                    case 1: {
                        dataTypeChoice = DataType::INT;
                        intArray = createArray<int>(size, dataTypeChoice);
                        break;
                    }
                    case 2: {
                        dataTypeChoice = DataType::FLOAT;
                        floatArray = createArray<float>(size, dataTypeChoice);
                        break;
                    }
                    case 3: {
                        dataTypeChoice = DataType::DOUBLE;
                        doubleArray = createArray<double>(size, dataTypeChoice);
                        break;
                    }
                    case 4: {
                        dataTypeChoice = DataType::CHAR;
                        charArray = createArray<char>(size, dataTypeChoice);
                        break;
                    }
                    default:
                        std::cerr << "Invalid data type choice.\n";
                        break;
                }
                break;
            }
            case 3: { // w zaleznosci od typu danych wyświetlamy tablicę

                switch(dataTypeChoice) {
                    case DataType::INT: {
                        displayArray(intArray,size);
                        break;
                    }
                    case DataType::FLOAT: {
                        displayArray(floatArray,size);
                        break;
                    }
                    case DataType::DOUBLE: {
                        displayArray(doubleArray,size);
                        break;
                    }
                    case DataType::CHAR: {
                        displayArray(charArray,size);
                        break;
                    }
                    default: std::cout << "Array is empty.\n"; break;
                }
                break;

            }
            case 4: {
                // Kod sortowania i mierzenia czasu
                switch (dataTypeChoice) {
                    case DataType::INT: {
                        if (intArray) {
                            performSortingAndMeasureTime(intArray, size);
                        } else {
                            std::cout << "Array is empty. Load or generate array first.\n";
                        }
                        break;
                    }
                    case DataType::FLOAT: {
                        if (floatArray) {
                            performSortingAndMeasureTime(floatArray, size);
                        } else {
                            std::cout << "Array is empty. Load or generate array first.\n";
                        }
                        break;
                    }
                    case DataType::DOUBLE: {
                        if (doubleArray) {
                            performSortingAndMeasureTime(doubleArray, size);
                        } else {
                            std::cout << "Array is empty. Load or generate array first.\n";
                        }
                        break;
                    }
                    case DataType::CHAR: {
                        if (charArray) {
                            performSortingAndMeasureTime(charArray, size);
                        } else {
                            std::cout << "Array is empty. Load or generate array first.\n";
                        }
                        break;
                    }
                    default: std::cout << "Array is empty.\n";
                        break;
                }
                break;
            }
            case 5: {
                // Kod czyszczenia pamięci i zakończenia programu
                cleanUp(intArray);
                cleanUp(floatArray);
                cleanUp(doubleArray);
                cleanUp(charArray);
                std::cout << "Exiting program.\n";
                return 0;
            }
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    }
    return 0;
}