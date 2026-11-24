#include "pemesanan.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// --- UTILITAS TAMPILAN ---

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    cout << "\n(Ketik huruf/angka apapun lalu Enter untuk lanjut): ";
    string dummy;
    cin >> dummy;
}

static string potongTeks(const string &teks, size_t maks) {
    if (teks.length() <= maks) {
        return teks;
    }
    return teks.substr(0, maks - 3) + "...";
}

// --- BASIC OPERATIONS ---

void createListPesanan(ListPesanan &L) {
    L.first = NULL;
    L.last = NULL;
}

bool isEmptyPesanan(ListPesanan L) {
    return (L.first == NULL);
}

bool isEmptyItem(adrPesanan p) {
    return (p == NULL || p->firstItem == NULL);
}

adrPesanan createElementPesanan(string kode, string namaPelanggan, int nomorMeja, string status) {
    adrPesanan p = new elemenPesanan;
    p->info.kodePesanan = kode;
    p->info.namaPelanggan = namaPelanggan;
    p->info.nomorMeja = nomorMeja;
    p->info.status = status;
    p->next = NULL;
    p->prev = NULL;
    p->firstItem = NULL;
    return p;
}

adrItem createElementItem(string namaMenu, string kategori, int hargaSatuan, int jumlahPorsi) {
    adrItem p = new elemenItem;
    p->info.namaMenu = namaMenu;
    p->info.kategori = kategori;
    p->info.hargaSatuan = hargaSatuan;
    p->info.jumlahPorsi = jumlahPorsi;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

// --- ADD ---

void addPesanan(ListPesanan &L, adrPesanan p) {
    if (p == NULL || searchPesanan(L, p->info.kodePesanan) != NULL) {
        delete p;
        return;
    }

    if (isEmptyPesanan(L)) {
        L.first = p;
        L.last = p;
    } else {
        // Insert Sorted berdasarkan kodePesanan (A-Z)
        if (p->info.kodePesanan < L.first->info.kodePesanan) {
            p->next = L.first;
            L.first->prev = p;
            L.first = p;
        } else if (p->info.kodePesanan > L.last->info.kodePesanan) {
            p->prev = L.last;
            L.last->next = p;
            L.last = p;
        } else {
            adrPesanan q = L.first;
            bool inserted = false;
            while (q != NULL && !inserted) {
                if (p->info.kodePesanan < q->info.kodePesanan) {
                    p->next = q;
                    p->prev = q->prev;
                    q->prev->next = p;
                    q->prev = p;
                    inserted = true;
                }
                q = q->next;
            }
        }
    }
}

void addItemMenu(adrPesanan p, adrItem pItem) {
    if (p == NULL || pItem == NULL) {
        return;
    }

    // Jika menu yang sama sudah ada di pesanan ini, gabungkan jumlah porsinya
    adrItem existing = searchItemMenu(p, pItem->info.namaMenu);
    if (existing != NULL) {
        existing->info.jumlahPorsi += pItem->info.jumlahPorsi;
        delete pItem;
        return;
    }

    if (p->firstItem == NULL) {
        p->firstItem = pItem;
    } else {
        adrItem q = p->firstItem;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = pItem;
        pItem->prev = q;
    }
}

// --- SEARCH ---

adrPesanan searchPesanan(ListPesanan L, string kodePesanan) {
    adrPesanan p = L.first;
    while (p != NULL) {
        if (p->info.kodePesanan == kodePesanan) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

adrItem searchItemMenu(adrPesanan p, string namaMenu) {
    if (p == NULL) {
        return NULL;
    }
    adrItem q = p->firstItem;
    while (q != NULL) {
        if (q->info.namaMenu == namaMenu) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

bool searchMenuDiSemuaPesanan(ListPesanan L, string namaMenu) {
    adrPesanan p = L.first;
    bool found = false;

    cout << "\n============================================================" << endl;
    cout << "HASIL PENCARIAN MENU: '" << namaMenu << "'" << endl;
    cout << "============================================================" << endl;

    while (p != NULL) {
        adrItem q = p->firstItem;
        while (q != NULL) {
            if (q->info.namaMenu == namaMenu) {
                int subtotal = q->info.hargaSatuan * q->info.jumlahPorsi;
                cout << "- [" << p->info.kodePesanan << "] " << p->info.namaPelanggan
                     << " (Meja " << p->info.nomorMeja << ") | "
                     << q->info.jumlahPorsi << "x @ Rp" << q->info.hargaSatuan
                     << " = Rp" << subtotal << endl;
                found = true;
            }
            q = q->next;
        }
        p = p->next;
    }

    if (found) {
        cout << "============================================================" << endl;
    }
    return found;
}

// --- UPDATE ---

void updatePesanan(adrPesanan p, string namaBaru, int mejaBaru, string statusBaru) {
    if (p != NULL) {
        p->info.namaPelanggan = namaBaru;
        p->info.nomorMeja = mejaBaru;
        p->info.status = statusBaru;
    }
}

void updateItemMenu(adrItem pItem, string namaBaru, string kategoriBaru, int hargaBaru, int jumlahBaru) {
    if (pItem != NULL) {
        pItem->info.namaMenu = namaBaru;
        pItem->info.kategori = kategoriBaru;
        pItem->info.hargaSatuan = hargaBaru;
        pItem->info.jumlahPorsi = jumlahBaru;
    }
}

// --- DELETE ---

void deletePesanan(ListPesanan &L, string kodePesanan) {
    adrPesanan p = searchPesanan(L, kodePesanan);
    if (p != NULL) {
        // 1. Bebaskan memori seluruh child (item menu) terlebih dahulu
        adrItem q = p->firstItem;
        while (q != NULL) {
            adrItem hapus = q;
            q = q->next;
            delete hapus;
        }
        p->firstItem = NULL;

        // 2. Lepas node parent dari Doubly Linked List
        if (p == L.first && p == L.last) {
            L.first = NULL;
            L.last = NULL;
        } else if (p == L.first) {
            L.first = p->next;
            L.first->prev = NULL;
        } else if (p == L.last) {
            L.last = p->prev;
            L.last->next = NULL;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }

        // 3. Bebaskan memori node parent
        delete p;
    }
}

void deleteItemMenu(adrPesanan p, string namaMenu) {
    if (p != NULL && !isEmptyItem(p)) {
        adrItem q = searchItemMenu(p, namaMenu);
        if (q != NULL) {
            if (q == p->firstItem) {
                p->firstItem = q->next;
                if (p->firstItem != NULL) {
                    p->firstItem->prev = NULL;
                }
            } else {
                q->prev->next = q->next;
                if (q->next != NULL) {
                    q->next->prev = q->prev;
                }
            }
            delete q;
        }
    }
}

void clearAllPesanan(ListPesanan &L) {
    while (L.first != NULL) {
        deletePesanan(L, L.first->info.kodePesanan);
    }
}

// --- HELPER & HITUNGAN ---

int countPesanan(ListPesanan L) {
    int hasil = 0;
    adrPesanan q = L.first;
    while (q != NULL) {
        hasil++;
        q = q->next;
    }
    return hasil;
}

int countTotalPorsi(adrPesanan p) {
    if (p == NULL) return 0;
    int hasil = 0;
    adrItem q = p->firstItem;
    while (q != NULL) {
        hasil += q->info.jumlahPorsi;
        q = q->next;
    }
    return hasil;
}

int countPorsiByCategory(adrPesanan p, string kategori) {
    if (p == NULL) return 0;
    int hasil = 0;
    adrItem q = p->firstItem;
    while (q != NULL) {
        if (q->info.kategori == kategori) {
            hasil += q->info.jumlahPorsi;
        }
        q = q->next;
    }
    return hasil;
}

int calculateTotalBayar(adrPesanan p) {
    if (p == NULL) return 0;
    int total = 0;
    adrItem q = p->firstItem;
    while (q != NULL) {
        total += (q->info.hargaSatuan * q->info.jumlahPorsi);
        q = q->next;
    }
    return total;
}

// --- SORTING ---

void selectionSortPesanan(adrPesanan* arrayPesanan, int n, int mode) {
    for (int i = 0; i < n - 1; i++) {
        int indexTerpilih = i;

        for (int j = i + 1; j < n; j++) {
            bool harusTukar = false;
            adrPesanan pesananA = arrayPesanan[j];
            adrPesanan pesananB = arrayPesanan[indexTerpilih];

            if (mode == 1) {
                if (pesananA->info.kodePesanan < pesananB->info.kodePesanan) harusTukar = true;
            } else if (mode == 2) {
                if (calculateTotalBayar(pesananA) > calculateTotalBayar(pesananB)) harusTukar = true;
            } else if (mode == 3) {
                if (calculateTotalBayar(pesananA) < calculateTotalBayar(pesananB)) harusTukar = true;
            } else if (mode == 4) {
                if (countTotalPorsi(pesananA) > countTotalPorsi(pesananB)) harusTukar = true;
            } else if (mode == 5) {
                if (countPorsiByCategory(pesananA, "Makanan") > countPorsiByCategory(pesananB, "Makanan")) harusTukar = true;
            } else if (mode == 6) {
                if (countPorsiByCategory(pesananA, "Minuman") > countPorsiByCategory(pesananB, "Minuman")) harusTukar = true;
            }

            if (harusTukar) {
                indexTerpilih = j;
            }
        }

        adrPesanan temp = arrayPesanan[i];
        arrayPesanan[i] = arrayPesanan[indexTerpilih];
        arrayPesanan[indexTerpilih] = temp;
    }
}

// --- DISPLAY ---

void displayTable(ListPesanan L, int mode) {
    const string garis(91, '=');

    if (isEmptyPesanan(L)) {
        cout << "\nDAFTAR PESANAN RESTORAN (KOSONG)" << endl;
        cout << garis << endl;
        cout << "| " << left << setw(10) << "KODE"
             << " | " << setw(20) << "PELANGGAN"
             << " | " << setw(6)  << "MEJA"
             << " | " << setw(12) << "STATUS"
             << " | " << setw(8)  << "PORSI"
             << " | " << setw(16) << "TOTAL BAYAR" << " |" << endl;
        cout << garis << endl;
        cout << "| " << left << setw(10) << "-"
             << " | " << setw(20) << "-"
             << " | " << setw(6)  << "-"
             << " | " << setw(12) << "-"
             << " | " << setw(8)  << "-"
             << " | " << setw(16) << "-" << " |" << endl;
        cout << garis << endl;
        return;
    }

    int n = countPesanan(L);
    adrPesanan* arrayPesanan = new adrPesanan[n];
    adrPesanan q = L.first;
    int idx = 0;
    while (q != NULL) {
        arrayPesanan[idx++] = q;
        q = q->next;
    }

    selectionSortPesanan(arrayPesanan, n, mode);

    cout << "\nDAFTAR PESANAN RESTORAN (Mode Urut: " << mode << ")" << endl;
    cout << garis << endl;
    cout << "| " << left << setw(10) << "KODE"
         << " | " << setw(20) << "PELANGGAN"
         << " | " << setw(6)  << "MEJA"
         << " | " << setw(12) << "STATUS"
         << " | " << setw(8)  << "PORSI"
         << " | " << setw(16) << "TOTAL BAYAR" << " |" << endl;
    cout << garis << endl;

    for (int k = 0; k < n; k++) {
        adrPesanan cur = arrayPesanan[k];
        string totalStr = "Rp " + to_string(calculateTotalBayar(cur));

        cout << "| " << left << setw(10) << potongTeks(cur->info.kodePesanan, 10)
             << " | " << setw(20) << potongTeks(cur->info.namaPelanggan, 20)
             << " | " << setw(6)  << cur->info.nomorMeja
             << " | " << setw(12) << potongTeks(cur->info.status, 12)
             << " | " << setw(8)  << countTotalPorsi(cur)
             << " | " << setw(16) << totalStr << " |" << endl;
    }
    cout << garis << endl;

    // Bebaskan memori array sementara
    delete[] arrayPesanan;
}

void showPesananDetails(adrPesanan p) {
    if (p != NULL) {
        cout << "\n====================================================" << endl;
        cout << "                STRUK DETAIL PESANAN                " << endl;
        cout << "====================================================" << endl;
        cout << "Kode Pesanan   : " << p->info.kodePesanan << endl;
        cout << "Nama Pelanggan : " << p->info.namaPelanggan << endl;
        cout << "Nomor Meja     : " << p->info.nomorMeja << endl;
        cout << "Status         : " << p->info.status << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "DAFTAR ITEM MENU:" << endl;

        adrItem q = p->firstItem;
        if (q == NULL) {
            cout << "(Belum ada menu yang dipesan)" << endl;
        } else {
            int no = 1;
            while (q != NULL) {
                int subtotal = q->info.hargaSatuan * q->info.jumlahPorsi;
                cout << no++ << ". " << q->info.namaMenu
                     << " [" << q->info.kategori << "]" << endl;
                cout << "   " << q->info.jumlahPorsi << " x Rp " << q->info.hargaSatuan
                     << " = Rp " << subtotal << endl;
                q = q->next;
            }
        }
        cout << "----------------------------------------------------" << endl;
        cout << "TOTAL PORSI    : " << countTotalPorsi(p) << " item" << endl;
        cout << "TOTAL BAYAR    : Rp " << calculateTotalBayar(p) << endl;
        cout << "====================================================" << endl;
    }
}
