/**
 * @file main.cpp
 * @author Carlos David Amezcua Canales A01641742
 * @author Juan Daniel Muñoz Dueñas A01641792
 * @author Diego Curiel Castellanos A01640372
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
    return 0;
}

