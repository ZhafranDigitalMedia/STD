#include "TUBESSTD.h"
#include <fstream>

// Stack untuk undo dan redo
stack<List> undoStack, redoStack;

void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
    L.cursor = nullptr;
}

address alokasi(infotype x) {
    address P = new elmList;
    P->info = x;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void insertChar(List &L, infotype x) {
    saveState(cloneList(L), undoStack);
    while (!redoStack.empty()) redoStack.pop();

    address P = alokasi(x);

    if (L.cursor == nullptr) {
        L.first = L.last = P;
        L.cursor = P;
    } else {
        P->next = L.cursor->next;
        P->prev = L.cursor;
        if (L.cursor->next != nullptr) {
            L.cursor->next->prev = P;
        }
        L.cursor->next = P;
        if (L.cursor == L.last) {
            L.last = P;
        }
        L.cursor = P;
    }
}

void removeChar(List &L) {
    if (L.cursor != nullptr) {
        saveState(cloneList(L), undoStack);
        while (!redoStack.empty()) redoStack.pop();

        address temp = L.cursor;
        if (L.cursor->prev != nullptr) {
            L.cursor->prev->next = L.cursor->next;
        }
        if (L.cursor->next != nullptr) {
            L.cursor->next->prev = L.cursor->prev;
        }
        if (L.cursor == L.first) {
            L.first = L.cursor->next;
        }
        if (L.cursor == L.last) {
            L.last = L.cursor->prev;
        }
        L.cursor = L.cursor->prev;
        delete temp;
    }
}

void insertNewline(List &L) {
    insertChar(L, '\n');
}

void moveCursorLeft(List &L) {
    if (L.cursor != nullptr && L.cursor->prev != nullptr) {
        L.cursor = L.cursor->prev;
    }
}

void moveCursorRight(List &L) {
    if (L.cursor != nullptr && L.cursor->next != nullptr) {
        L.cursor = L.cursor->next;
    }
}

void displayText(List L) {
    address temp = L.first;
    while (temp != nullptr) {
        if (temp == L.cursor) {
            cout << temp->info << "|";
        } else {
            cout << temp->info;
        }
        temp = temp->next;
    }
    cout << endl;
}

void displayFinalText(List L) {
    address temp = L.first;
    while (temp != nullptr) {
        cout << temp->info;
        temp = temp->next;
    }
    cout << endl;
}

int count_words(List L) {
    address head = L.first;
    int word_count = 0;
    bool in_word = false;

    while (head != nullptr) {
        if (head->info == ' ' || head->info == '\t' || head->info == '\n') {
            if (in_word) {
                word_count++;
                in_word = false;
            }
        } else {
            in_word = true;
        }
        head = head->next;
    }

    if (in_word) {
        word_count++;
    }

    return word_count;
}

List cloneList(List L) {
    List clone;
    createList(clone);
    address temp = L.first, prev = nullptr, newNode;

    while (temp != nullptr) {
        newNode = alokasi(temp->info);
        if (prev == nullptr) {
            clone.first = newNode;
        } else {
            prev->next = newNode;
            newNode->prev = prev;
        }

        if (temp == L.cursor) {
            clone.cursor = newNode;
        }

        prev = newNode;
        temp = temp->next;
    }

    clone.last = prev;
    return clone;
}

void saveState(List L, stack<List> &stackToSave) {
    stackToSave.push(cloneList(L));
}

void undo(List &L) {
    if (!undoStack.empty()) {
        saveState(L, redoStack);
        L = undoStack.top();
        undoStack.pop();
    }
}

void redo(List &L) {
    if (!redoStack.empty()) {
        saveState(L, undoStack);
        L = redoStack.top();
        redoStack.pop();
    }
}

void loadFile(List &L, const string &filename) {
    ifstream file(filename);
    char ch;
    if (!file) {
        cout << "File not found!\n";
        return;
    }

    while (file.get(ch)) {
        insertChar(L, ch);
    }
    file.close();
}

void saveFile(List L, const string &filename) {
    ofstream file(filename);
    address temp = L.first;
    while (temp != nullptr) {
        file << temp->info;
        temp = temp->next;
    }
    file.close();
}
