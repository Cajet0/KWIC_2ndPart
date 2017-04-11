/*
*   Created by: ProArquis
*   Martha Benavides A01280115
*   Melissa Figueroa A01280388
*   Pedro Esparza A01280126
*   César de la Barreda A01195359
*
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

/*
Ejemplo:

Entrada:
Clouds are white
Pittsburgh is beautiful
END

Salida:
are white clouds
beautiful pittsburgh is
clouds are white
is beautiful pittsburgh
pittsburgh is beautiful
white clouds are
*/

vector<string> glbVecSCircularIt;


string transLowerC(string sLine) {
    for (int iI = 0; iI < sLine.size(); iI++) {
        sLine[iI] = tolower(sLine[iI]);
    }
    return sLine;
}

string cricularShift(string sLine) {
    int iFindSpace = sLine.find(' ');
    if(iFindSpace != -1){
        sLine = sLine.substr(iFindSpace + 1) + " " + sLine.substr(0, iFindSpace);
    }
    return sLine;
}


void getInput() {
    string sLine;
    getline(cin, sLine);
    sLine = transLowerC(sLine);
    // el input termina cuando escriba "end"
    while(sLine!="end") {
        int iContWords = 0;
        for (int iI = 0; iI < sLine.size(); iI++) {
            if (sLine[iI] == ' ')
                iContWords++;
        }
        sLine = transLowerC(sLine);
        iContWords++;
        for (int iI = 0; iI < iContWords; iI ++) {
            glbVecSCircularIt.push_back(sLine);
            sLine = cricularShift(sLine);
        }
        getline(cin, sLine);
        sLine = transLowerC(sLine);
    }
}

void sortData() {
    sort(glbVecSCircularIt.begin(), glbVecSCircularIt.end());
}


void printOutput() {
    for (int iI = 0; iI < glbVecSCircularIt.size(); iI++){
        cout<<glbVecSCircularIt[iI]<<endl;
    }
}


int main() {
    getInput();
    sortData();
    printOutput();

    return 0;
}
