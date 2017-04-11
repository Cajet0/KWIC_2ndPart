/*
*   Created by: ProArquis
*
*   Modified by: Los Sobrinos del Dr. Lavariega
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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

vector<string> glbVecSInputStrings;
vector<string> glbVecSCircularIt;
vector<string> glbVecSStopWords;


string transLowerC(string sLine) {
    for (int iI = 0; iI < sLine.size(); iI++) {
        sLine[iI] = tolower(sLine[iI]);
    }
    return sLine;
}

// Compara cadena recibida con la lista de palabras STOP para tomarla en cuenta o no
bool removeWord(string sWord) {
    for (int iIt = 0; iIt < glbVecSStopWords.size(); iIt++) {
        if (strcmp(sWord.c_str(), glbVecSStopWords[iIt].c_str()) == 0)
            return true;
    }

    return false;
}

// Recibe un vector para imprimir su contenido de manera enumerada
void printWithID(vector<string> listaTexto) {
    for (int iIte = 0; iIte < listaTexto.size(); iIte++) {
        cout << iIte << " - " << listaTexto[iIte] << endl;
    }
}

string cricularShift(string sLine) {
    int iFindSpace = sLine.find(' ');
    if(iFindSpace != -1){
        sLine = sLine.substr(iFindSpace + 1) + " " + sLine.substr(0, iFindSpace);
    }
    return sLine;
}

// Funcion que elimina espacios en blanco innecesarios que separe a las palabras
string removeExtraSpaces(string sLine) {
    string sFormatLine = "";

    while (sLine != "") {
        if (sLine.find(" ") == -1) {
            //Ya no se encontraro espacios en blanco
            sFormatLine.append(sLine);
            break;
        }
        else {
            // Se identifica una palabra en la linea de texto
            string sWord = sLine.substr(0, sLine.find(" ") + 1);
            // Con esto se eliminan espacios en blanco que sobraran entre la separacion de palabras y se descartan palabras STOP
            if (sWord != " " && !removeWord(sWord.substr(0, sWord.length() - 1))) {
                    sFormatLine.append(sWord);
            }
            sLine.erase(0, sLine.find(" ") + 1);
        }
    }

    return sFormatLine;
}

void getInput() {
    cout << "Ingresa cada una de las palabras STOP (Una palabra por renglon)" << endl;
    cout << "Finaliza la accion ingresando una cadena vacia" << endl;
    string sLine;
    getline(cin, sLine);
    sLine = transLowerC(sLine);

    // el input termina cuando escriba ya no ingrese texto
    while(sLine!="") {
        sLine = removeExtraSpaces(sLine);
        glbVecSStopWords.push_back(sLine);

        getline(cin, sLine);
        sLine = transLowerC(sLine);
    }

    cout << endl << "Ingresa lineas de texto a solucionar. Ingrese 'end' para finalizar la entrada." << endl;
    getline(cin, sLine);
    sLine = transLowerC(sLine);
    // el input termina cuando escriba "end"
    while(sLine!="end") {
        if (sLine != "") {
            sLine = removeExtraSpaces(sLine);
            glbVecSInputStrings.push_back(sLine);
        }

        getline(cin, sLine);
        sLine = transLowerC(sLine);
    }
}

void deleteInputLines() {
    int iPosRenglon = -10;

    while (iPosRenglon != -1) {
        cout << endl << "Lineas de entrada ingresada por usuario: " << endl;
        printWithID(glbVecSInputStrings);

        cout << "Ingrese numero de renglon si desea eliminarlo como entrada" << endl;
        cout << "Ingrese -1 para proseguir" << endl;
        cin >> iPosRenglon;

        if (iPosRenglon > -1 && iPosRenglon < glbVecSInputStrings.size()) {
            glbVecSInputStrings.erase(glbVecSInputStrings.begin() + iPosRenglon);
        }
    }
}

void getShifts() {
    for (int iItVect = 0; iItVect < glbVecSInputStrings.size(); iItVect++) {
        int iContWords = 0;
        string sLine = glbVecSInputStrings[iItVect];
        for (int iI = 0; iI < sLine.size(); iI++) {
            if (sLine[iI] == ' ')
                iContWords++;
        }
        iContWords++;

        for (int iI = 0; iI < iContWords; iI ++) {
            glbVecSCircularIt.push_back(sLine);
            sLine = cricularShift(sLine);
        }
    }
}

void sortData() {
    int iRespuesta;
    cout << "Ingrese numero de tipo de orden deseado: " << endl;
    cout << "1) Ascendente  -  2) Descendente" << endl;
    cin >> iRespuesta;

    sort(glbVecSCircularIt.begin(), glbVecSCircularIt.end());

    if (iRespuesta == 2)
        reverse(glbVecSCircularIt.begin(), glbVecSCircularIt.end());
}

void deleteOutputLines() {
    int iPosRenglon = -10;

    while (iPosRenglon != -1) {
        cout << endl << "Lineas de salida generadas: " << endl;
        printWithID(glbVecSCircularIt);

        cout << "Ingrese numero de renglon si desea eliminar alguna salida" << endl;
        cout << "Ingrese -1 para proseguir" << endl;
        cin >> iPosRenglon;

        if (iPosRenglon > -1 && iPosRenglon < glbVecSCircularIt.size()) {
            glbVecSCircularIt.erase(glbVecSCircularIt.begin() + iPosRenglon);
        }
    }
}

void printOutput() {
    cout << endl << "Ordenamientos resultantes: " << endl;
    for (int iI = 0; iI < glbVecSCircularIt.size(); iI++){
        cout<<glbVecSCircularIt[iI]<<endl;
    }
}


int main() {
    getInput();
    deleteInputLines();
    getShifts();
    sortData();
    deleteOutputLines();
    printOutput();

    return 0;
}
