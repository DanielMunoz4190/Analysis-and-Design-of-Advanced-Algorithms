/**
 * @file main.cpp
 * @author Carlos David Amezcua Canales A01641742
 * @author Juan Daniel Muñoz Dueñas A01641792
 * @brief  
 * @version 0.1
 * @date 09-09-2023
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <sstream>

using namespace std;

const int NUMBER_OF_TRANSMISSIONS = 2;
const int NUMBER_OF_MALICIOUS_CODES = 3;

string readFile(const string &fileName) {
    ifstream archivo(fileName);

    if (!archivo.is_open()) 
        throw runtime_error("Error opening file " + fileName);

    stringstream buffer;
    buffer << archivo.rdbuf(); 
    archivo.close(); 

    return buffer.str();
}

int main()
{
    vector<string> transmissions(NUMBER_OF_TRANSMISSIONS), maliciousCodes(NUMBER_OF_MALICIOUS_CODES);
    for (int i = 0; i < NUMBER_OF_TRANSMISSIONS; ++i)
    {
        transmissions[i] = readFile("transmission" + to_string(i + 1) + ".txt");
    }
    for (int i = 0; i < NUMBER_OF_MALICIOUS_CODES; ++i)
    {
        maliciousCodes[i] = readFile("mcode" + to_string(i + 1) + ".txt");
    }


    return 0;
}

