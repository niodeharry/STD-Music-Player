#include <iostream>
#include "list.h"

using namespace std;

int main() {
    //Deklarasi List
    List L;
    
    //Inisialisasi
    createList(L);

    cout << "=== APLIKASI MUSIK ===" << endl;

    //Data Dummy utk Testing
    infotype lagu1 = {1, "Let Down", "Radiohead", "Post-Britpop", 1997};
    infotype lagu2 = {2, "New Dawn Fades", "Joy Division", "Post-Rock", 1979};
    infotype lagu3 = {3, "Terhempas Hilang", "Cherry Bombshell", "Dream Pop", 2000};
    infotype lagu4 = {4, "Good Riddance", "Green Day", "Pop", 2004};

    //Proses Insert (alokasi dulu, lalu insert)
    
    address P;

    P = alokasi(lagu1);
    insertLast(L, P);
    cout << "Input: " << lagu1.judul << " [OK]" << endl;

    P = alokasi(lagu2);
    insertLast(L, P);
    cout << "Input: " << lagu2.judul << " [OK]" << endl;

    P = alokasi(lagu3);
    insertLast(L, P);
    cout << "Input: " << lagu3.judul << " [OK]" << endl;

    P = alokasi(lagu4);
    insertLast(L, P);
    cout << "Input: " << lagu4.judul << " [OK]" << endl;

    // Tampilkan Hasil (DLL + Graph)
    printInfo(L);

    return 0;
}