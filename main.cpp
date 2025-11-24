/*
2020 - 2025 Cap Software INC.
ALL RIGHTS RESERVED
*/

#include <sleeper_cap.h>
#include <samples_mun.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
#include <string>
#include <vector>

using namespace std;

bool file_is_empty(std::fstream& pFile)
{
    return pFile.tellg() == 0 && pFile.peek() == std::ifstream::traits_type::eof();
}

array<string, 2> committeeDefine()
{
    array<string, 2> meinStrings;
    fstream infoFile("committee_info.txt");
    string comNameIn, conNameIn;
    if(file_is_empty(infoFile))
    {
        cout << "Enter conference name: "; getline(cin, conNameIn);
        cout << "Enter committee name: "; getline(cin, comNameIn);
        infoFile << conNameIn << "\n" << comNameIn;
        infoFile.close();
    }
    else
    {
        getline(infoFile, conNameIn);
        getline(infoFile, comNameIn);
    }
    meinStrings[0] = conNameIn; meinStrings[1] = comNameIn;
    cout << "\n";
    return meinStrings;
}

void mainEvent(string conName, string comName, std::vector<pair<string, string>> mtrx)
{
    vector<bool> present(mtrx.size(), false);

    cout << conName << " - " << comName << "\n----------------------\n";

    for (size_t i = 0; i < mtrx.size(); i++)
    {
        string response;
        while (true)
        {
            cout << mtrx[i].first << " (" << mtrx[i].second << ") - present(p)/absent(a): ";
            getline(cin, response);

            for (auto &c : response) c = tolower(c);

            if (response == "p") {
                present[i] = true;
                break;
            }
            else if (response == "a") {
                present[i] = false;
                break;
            }
            else {
                cout << "Invalid input. Please type 'p' for present or 'a' for absent.\n";
            }
        }
    }

    cout << "\nRollcall complete!\n\n";
    for (size_t i = 0; i < mtrx.size(); i++) {
        cout << mtrx[i].first << " (" << mtrx[i].second << "): "
             << (present[i] ? "Present" : "Absent") << "\n";
    }
    cin.get();
}

int main()
{
    array<string, 2> myStrings = committeeDefine();
    string conNameOut = myStrings[0];
    string comNameOut = myStrings[1];
    string opName;
    std::vector <pair<string, string>> matrix;
    std::cout << "-----MUN MANAGER SOFTWARE-----\n--2020-2025 CAP SOFTWARE INC--\n-----©ALL RIGHTS RESERVED-----\n\n> "; getline(std::cin, opName);
    while(true)
    {

        if(opName == "load matrix")
        {
            ifstream matrixFile("matrix.txt");
            if (!matrixFile) {
                cout << "No saved matrix found.\n";
            } else {
                matrix.clear(); // clear previous matrix
                string line;
                while (getline(matrixFile, line))
                {
                    size_t sep = line.find('|');
                    if (sep != string::npos)
                    {
                        string country = line.substr(0, sep);
                        string code = line.substr(sep + 1);
                        matrix.push_back({country, code});
                    }
                }
                cout << "Matrix loaded successfully (" << matrix.size() << " entries).\n";
            }
            printCAP(); getline(cin, opName);
        }

        else if (opName == "save matrix")
        {
            string name, code;
            cout << "Press enter to start typing countries/characters.";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true)
            {
                cout << "Enter country name (or 'exit' to stop): ";
                getline(cin, name);

                if (name == "exit") break;

                cout << "Enter country code: ";
                getline(cin, code);

                matrix.push_back({name, code});
            }

            ofstream outFile("matrix.txt");
            for (auto &c : matrix)
                outFile << c.first << "|" << c.second << "\n";

            cout << "Matrix saved successfully.\n";
            printCAP(); getline(cin, opName);
        }


        else if(opName == "rollcall"){mainEvent(conNameOut, comNameOut, matrix);}

        else if(opName == "exit") {cout << "\nPress enter to exit the program.";return 0;}

        else if(opName == "help")
        {
            printCAP();
            cout << setw(15) << "EXIT" << " || Closes the program." << endl;
            cout << setw(15) << "HELP" << " || Shows this help menu." << endl;
            cout << setw(15) << "LOAD MATRIX" << " || Loads country matrix from save." << endl;
            cout << setw(15) << "ROLLCALL" << " || Starts rollcall with current matrix and goes on with standart GA prosedures." << endl;
            cout << setw(15) << "SAVE MATRIX" << " || Saves a new matrix " << endl;
            cout << "\n> ";
            getline(cin, opName);
        }

        else{
            printCAP();
            cout << "Unknown command. Please try again.\n> "; getline(std::cin, opName);
        }

    }
}
