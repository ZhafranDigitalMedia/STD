#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <stack>

using namespace std;

typedef char infotype;
typedef struct elmList *address;

struct elmList {
    infotype info;
    address next;
    address prev;
};

struct List {
    address first;
    address last;
    address cursor;
};

// Fungsi List
void createList(List &L);
address alokasi(infotype x);
void insertChar(List &L, infotype x);
void removeChar(List &L);
void insertNewline(List &L);
void moveCursorLeft(List &L);
void moveCursorRight(List &L);
void displayText(List L);
void displayFinalText(List L);
int count_words(List L);
List cloneList(List L);
void saveState(List L, stack<List> &stackToSave);
void undo(List &L);
void redo(List &L);

// Fungsi File
void loadFile(List &L, const string &filename);
void saveFile(List L, const string &filename);

#endif // HEADER_H_INCLUDED
