/* ============================================================
   Data Structure & Programming II
   Topic 3: File IO (Input / Output)

   What students learn here:
     1. Why we need files (data must survive after the program ends)
     2. The library <fstream>
            ofstream -> only WRITE
            ifstream -> only READ
            fstream  -> read AND write (choose with a mode)
     3. Opening modes: ios::out, ios::in, ios::app
     4. Always TEST that the file was really opened
     5. Always CLOSE the file
     6. Reading word by word / line by line / character by character
     7. Reading a CSV file with getline + stringstream

   This program creates its own files in the current folder,
   so it can be run directly with no preparation.

   Compile:  g++ L3-FileIO.cpp -o L3
   ============================================================ */

#include <iostream>
#include <fstream>     // ofstream, ifstream, fstream
#include <sstream>     // stringstream (to cut a CSV line)
#include <string>
using namespace std;

int main()
{
    /* ============================================================
       1. WRITING TO A FILE with ofstream
          ios::out -> if the file does not exist, it is created
                      if the file exists, its content is ERASED
       ============================================================ */

    cout << "=== 1. Write to StudentList.txt ===" << endl;

    ofstream fout;                       // "f-out" = file output
    fout.open("StudentList.txt");        // same as: open(..., ios::out)

    if (!fout) {                         // ALWAYS test!
        cout << "Error: cannot create the file." << endl;
        return 1;
    }

    fout << "ID"   << "\t" << "Name"  << "\t" << "Age" << endl;
    fout << "B101" << "\t" << "Sok"   << "\t" << 17    << endl;
    fout << "B102" << "\t" << "Sao"   << "\t" << 20    << endl;
    fout << "B109" << "\t" << "Dara"  << "\t" << 18    << endl;
    fout << "B110" << "\t" << "Seyha" << "\t" << 22    << endl;

    fout.close();                        // ALWAYS close!
    cout << "File written." << endl;

    /* Notice: writing to a file is exactly like using cout,
       we only replace "cout" by the name of our file variable. */

    /* ============================================================
       2. READING A FILE WORD BY WORD with ifstream
          >>  reads one "word": it stops at a space, a tab
              or a new line.
       ============================================================ */

    cout << "\n=== 2. Read word by word ===" << endl;

    ifstream fin;                        // "f-in" = file input
    fin.open("StudentList.txt");

    if (!fin) {
        cout << "Error opening file OR file does not exist" << endl;
        return 1;
    }

    string word;
    while (fin >> word) {                // stops when there is nothing left
        cout << "[" << word << "] ";
    }
    cout << endl;
    fin.close();

    /* ============================================================
       3. READING LINE BY LINE with getline()
       ============================================================ */

    cout << "\n=== 3. Read line by line ===" << endl;

    fin.open("StudentList.txt");
    string line;
    int lineNo = 0;

    while (getline(fin, line)) {
        lineNo++;
        cout << lineNo << ": " << line << endl;
    }
    fin.close();
    cout << "The file has " << lineNo << " line(s)." << endl;

    /* ============================================================
       4. READING FIELD BY FIELD (we know the format of the file)
       ============================================================ */

    cout << "\n=== 4. Read the data as real fields ===" << endl;

    fin.open("StudentList.txt");

    string id, name, header1, header2, header3;
    int age, count = 0, totalAge = 0;

    fin >> header1 >> header2 >> header3;    // skip the title line

    while (fin >> id >> name >> age) {
        cout << "  " << id << " -> " << name
             << " (" << age << " years old)" << endl;
        count++;
        totalAge += age;
    }
    fin.close();

    if (count > 0)
        cout << "Average age of " << count << " students: "
             << (float)totalAge / count << endl;

    /* ============================================================
       5. ADDING DATA AT THE END with ios::app (append)
          ios::out would erase everything, ios::app adds at the end.
       ============================================================ */

    cout << "\n=== 5. Append a new student ===" << endl;

    fstream file;
    file.open("StudentList.txt", ios::app);

    string newId, newName;
    int    newAge;

    cout << "New student ID  : ";  cin >> newId;
    cout << "New student name: ";  cin >> newName;
    cout << "New student age : ";  cin >> newAge;

    file << newId << "\t" << newName << "\t" << newAge << endl;
    file.close();

    cout << "Added. The file now contains:" << endl;
    fin.open("StudentList.txt");
    while (getline(fin, line))
        cout << "  " << line << endl;
    fin.close();

    /* ============================================================
       6. READING CHARACTER BY CHARACTER with get()
          Useful to count letters, spaces, lines ...
       ============================================================ */

    cout << "\n=== 6. Read character by character ===" << endl;

    fin.open("StudentList.txt");
    char ch;
    int nbChar = 0, nbTab = 0;

    while (fin.get(ch)) {
        nbChar++;
        if (ch == '\t') nbTab++;
    }
    fin.close();
    cout << nbChar << " characters, " << nbTab << " tabulations." << endl;

    /* ============================================================
       7. A CSV FILE (comma separated values)
          Each line looks like:   B101,Sok,17,3.5
          We read the LINE with getline, then we cut it with
          a stringstream and getline(..., ',').
       ============================================================ */

    cout << "\n=== 7. Read a CSV file ===" << endl;

    // first we create the CSV file
    ofstream csvOut("MyData.csv");
    csvOut << "B101,Sok,17,3.50" << endl;
    csvOut << "B102,Sao,20,3.75" << endl;
    csvOut << "B109,Dara,18,2.90" << endl;
    csvOut.close();

    ifstream csvIn("MyData.csv");
    string field;

    cout << "ID\tName\tAge\tGPA" << endl;
    while (getline(csvIn, line)) {

        stringstream ss(line);       // put the line inside a "mini cin"

        string sId, sName, sAge, sGpa;
        getline(ss, sId,   ',');     // read until the next comma
        getline(ss, sName, ',');
        getline(ss, sAge,  ',');
        getline(ss, sGpa,  ',');

        cout << sId << "\t" << sName << "\t" << sAge << "\t" << sGpa << endl;
    }
    csvIn.close();

    cout << "\nLook in the folder of this program: the files "
         << "StudentList.txt and MyData.csv were created." << endl;

    return 0;
}

/* ============================================================
   SUMMARY

     ofstream f("name.txt");            open for writing (erases)
     ifstream f("name.txt");            open for reading
     fstream  f("name.txt", ios::app);  open to add at the end

     f << data;                         write
     f >> word;                         read one word
     getline(f, line);                  read one line
     f.get(ch);                         read one character
     f.eof()                            true when the end is reached
     f.close();                         close

   PRACTICE

   1. Write a program that asks the user for 5 students
      (name, age) and saves them in a file "class.txt".
   2. Read "class.txt" and display only the students older than 18.
   3. Count how many lines and how many words a file contains.
   4. Read a file of numbers (one per line) and compute their
      sum, their average and their maximum.
   5. Copy the content of one file into another file.
   6. Save the result of the "grade of a score" program of
      Topic 3 (C) into a file "grades.csv".
   ============================================================ */
