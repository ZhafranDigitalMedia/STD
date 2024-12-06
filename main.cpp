#include "TUBESSTD.h"
#include <conio.h>
#include <fstream>

void handleInput(List &L);

int main() {
    List editor;
    createList(editor);

    string filename;
    char choice;

    cout << "1. Open Existing File\n";
    cout << "2. Create New File\n";
    cout << "Enter your choice (1/2): ";
    cin >> choice;
    cin.ignore();

    if (choice == '1') {
        cout << "Enter filename to open: ";
        getline(cin, filename);
        loadFile(editor, filename);
    } else {
        cout << "Enter filename to create: ";
        getline(cin, filename);
        ofstream newFile(filename);
        newFile.close();
    }

    handleInput(editor);

    cout << "\nFinal Text:" << endl;
    displayFinalText(editor);
    saveFile(editor, filename);

    return 0;
}

void handleInput(List &L) {
    char c;
    while (true) {
        if (_kbhit()) {
            c = _getch();

            if (c == 27) break;
            else if (c == -32) {
                c = _getch();
                if (c == 75) moveCursorLeft(L);
                else if (c == 77) moveCursorRight(L);
            } else if (c == 8) removeChar(L);
            else if (c == 13) insertNewline(L);
            else if (c == 26) undo(L);
            else if (c == 25) redo(L);
            else insertChar(L, c);

            system("cls");
            cout << "Text Editor:" << endl;
            displayText(L);
            cout << "Words: " << count_words(L) << endl;
        }
    }
}
