#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{

    vector<string> piante = {"Geranio", "Papavero", "Altrofiore", "Ancorafiore", "Girasole", "Non me lo ricordo"};
    for (string piant : piante)
        cout << piant << endl;

    vector<int> numeri = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int num : numeri)
        cout << num << endl;

    ifstream miofile("Nome.txt");
    ofstream os;
    string str((istreambuf_iterator<char>(miofile)), istreambuf_iterator<char>());
    stringstream flusso(str);
    string token, nome;
    while (flusso >> token)
    {
        nome = token;
        cout << token << endl;
    }

    cout << "token= " << nome << endl;
    cout << str << endl;
    miofile.close();
}