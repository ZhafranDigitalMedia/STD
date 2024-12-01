
#include <iostream>
#include <conio.h>  // Untuk _kbhit() dan _getch() buat display text editornya
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
    address P = alokasi(x);

    // insert first
    if (L.cursor == nullptr) {
        L.first = L.last = P;
        L.cursor = P;
    } else {
        // insert after (insert karakter setelah cursor)
        P->next = L.cursor->next;
        P->prev = L.cursor;

        if (L.cursor->next != nullptr) {
            L.cursor->next->prev = P;
        }
        L.cursor->next = P;

        // insert last (jika kursor berada di elemen terakhir)
        if (L.cursor == L.last) {
            L.last = P;
        }

        L.cursor = P;  // P dijadiin posisi baru dari cursor setelah di-insert
    }
}

void removeChar(List &L) {
    if (L.cursor != nullptr) {
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

int count_char(List L) {
    address head = L.first;
    int count_char = 0;

    while (head != nullptr) {
        head = head->next;
        count_char++;
    }

    return count_char;
}

void displayText(List L) {
    address temp = L.first;

    while (temp != nullptr) {
        if (temp == L.cursor) {
            cout << temp->info << "|";  // Menunjukkan posisi kursor
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
        cout << temp->info;  // Cetak karakter biasa tanpa tanda kursor
        temp = temp->next;
    }
    cout << endl;
}

void moveCursorLeft(List &L) {
    if (L.cursor != nullptr && L.cursor->prev != nullptr) {
        L.cursor = L.cursor->prev;  // Pindah ke elemen sebelumnya
    }
}

void moveCursorRight(List &L) {
    if (L.cursor != nullptr && L.cursor->next != nullptr) {
        L.cursor = L.cursor->next;  // Pindah ke elemen berikutnya
    }
}

void handleInput(List &L) {
    char c;
    cout << "Text Editor Controls:" << endl;
    cout << "[Left Arrow]: Move Cursor Left" << endl;
    cout << "[Right Arrow]: Move Cursor Right" << endl;
    cout << "[Backspace]: Remove Character" << endl;
    cout << "[ESC]: Exit Editor" << endl;
    cout << "Start typing..." << endl;

    while (true) {
        if (_kbhit()) {  // Menangkap input keyboard
            c = _getch();

            // Navigasi kursor
            if (c == 27) {  // ESC key untuk keluar
                break;
            } else if (c == -32) {  // Arrow keys
                c = _getch();
                if (c == 75) {  // Left Arrow
                    moveCursorLeft(L);
                } else if (c == 77) {  // Right Arrow
                    moveCursorRight(L);
                }
            } else if (c == 8) {  // Backspace
                removeChar(L);
            } else {
                insertChar(L, c);  // Memasukkan karakter biasa
            }

            system("cls");  // Membersihkan layar untuk refresh tampilan
            cout << "Text Editor:" << endl;
            displayText(L);

            // Hitung jumlah karakter
            int count = count_char(L);
            cout << "Jumlah karakter dalam teks: " << count << endl;  // Selalu cetak jumlah karakter
        }
    }
}

int main() {
    List editor;
    createList(editor);

    handleInput(editor);

    cout << "\nFinal Text:" << endl;
    displayFinalText(editor);  // Menampilkan teks tanpa kursor

    return 0;
}
