#include <iostream>
#include <limits>
#include "list.h"

using namespace std;

// Fungsi helper untuk clean buffer
void cleanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // 1. Inisialisasi Struktur Data
    List Library;
    ListPlaylist MyPlaylist;
    Stack History;

    createList(Library);
    createPlaylist(MyPlaylist);
    createStack(History);

    // 2. Deklarasi Variabel
    int pilihan = 0;
    string judulCari, judulHapus;
    address foundSong = nullptr;
    address P = nullptr;

    // 3. Data Dummy (Agar saat run tidak kosong)
    
    P = alokasi({1, "Let Down", "Radiohead", "Post-Britpop", 1997});
    insertLast(Library, P);

    P = alokasi({2, "New Dawn Fades", "Joy Division", "Post-Rock", 1979});
    insertLast(Library, P);

    P = alokasi({3, "Terhempas Hilang", "Cherry Bombshell", "Dream Pop", 2000});
    insertLast(Library, P);

    P = alokasi({4, "Good Riddance", "Green Day", "Pop", 2004});
    insertLast(Library, P);

    // 4. Loop Menu Utama
    while (pilihan != 9) {
        cout << "\n===================================" << endl;
        cout << "      STDIFY MUSIC PLAYER       " << endl;
        cout << "===================================" << endl;
        cout << "1. [Admin] Lihat Library Lagu" << endl;
        cout << "2. [Admin] Tambah Lagu Baru" << endl;
        cout << "3. [Admin] Hapus Lagu (Delete)" << endl;
        cout << "4. [User]  Cari Lagu (Search)" << endl;
        cout << "5. [User]  Tambah ke Playlist" << endl;
        cout << "6. [User]  Lihat Playlist" << endl;
        cout << "7. [Player] Play Lagu (By Judul)" << endl;
        cout << "8. [Player] Back (History Stack)" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                printInfo(Library);
                break;
            
            case 2: {
                cout << "Masukkan Judul: ";
                cleanInput();
                getline(cin, judulCari); 

                // default untuk demo
                P = alokasi({rand() % 100 + 10, judulCari, "Unknown", "Pop", 2024});
                insertLast(Library, P);
                cout << "Lagu berhasil ditambah!" << endl;
                break;
            }

            case 3:
                cout << "Judul lagu yang dihapus: ";
                cleanInput();
                getline(cin, judulHapus);
                deleteSong(Library, judulHapus);
                break;

            case 4:
                cout << "Cari Judul: ";
                cleanInput();
                getline(cin, judulCari);
                foundSong = findSong(Library, judulCari);
                if (foundSong != nullptr) {
                    cout << "DITEMUKAN: " 
                         << foundSong->info.judul << " - "
                         << foundSong->info.artis << endl;
                } else {
                    cout << "Lagu tidak ditemukan." << endl;
                }
                break;

            case 5:
                cout << "Masukkan Judul untuk Playlist: ";
                cleanInput();
                getline(cin, judulCari);
                foundSong = findSong(Library, judulCari);
                if (foundSong != nullptr) {
                    insertPlaylist(MyPlaylist, foundSong);
                } else {
                    cout << "Lagu tidak ada di Library, tidak bisa masuk Playlist." << endl;
                }
                break;

            case 6:
                printPlaylist(MyPlaylist);
                break;

            case 7: {
                cout << "Putar Lagu (Judul): ";
                cleanInput();
                getline(cin, judulCari);
                foundSong = findSong(Library, judulCari);
                if (foundSong != nullptr) {
                    playSong(foundSong, History);
                    
                    // Simulasi Next (Graph Logic)
                    if (foundSong->firstedge != nullptr &&
                        foundSong->firstedge->nodeTuju != nullptr) {
                        cout << "[Smart Next] Rekomendasi selanjutnya: " 
                             << foundSong->firstedge->nodeTuju->info.judul << endl;
                    }
                } else {
                    cout << "Lagu tidak ditemukan." << endl;
                }
                break;
            }

            case 8: {
                // Logic Back (Stack)
                pop(History); // buang lagu sekarang

                address prevSong = pop(History);
                if (prevSong != nullptr) {
                    cout << "Mundur ke lagu: " << prevSong->info.judul << endl;
                    push(History, prevSong); // Masukkan lagi karena sedang main
                } else {
                    cout << "Tidak ada history sebelumnya." << endl;
                }
                printHistory(History);
                break;
            }

            case 9:
                cout << "Terima kasih!" << endl;
                break;
            
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}
