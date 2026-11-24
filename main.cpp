#include <iostream>
#include <string>
#include "pemesanan.h"

using namespace std;

int main() {
    ListPesanan L;
    createListPesanan(L);

    string pilihanMenu;
    string kodePesanan, namaPelanggan, statusPesanan, targetKode;
    string namaMenu, kategoriMenu;
    int nomorMeja, hargaSatuan, jumlahPorsi;
    int modeUrutan = 1;
    adrPesanan p;

    bool berjalan = true;

    while (berjalan) {
        clearScreen();
        displayTable(L, modeUrutan);

        cout << "\n=== SISTEM PEMESANAN MENU RESTORAN ===" << endl;
        cout << "[1] Buat Pesanan Baru (Pelanggan)" << endl;
        cout << "[2] Tambah Menu ke Pesanan" << endl;
        cout << "[3] Lihat Struk / Detail Pesanan" << endl;
        cout << "[4] Update Data Pesanan (Pelanggan/Meja/Status)" << endl;
        cout << "[5] Update Item Menu di Pesanan" << endl;
        cout << "[6] Hapus / Batalkan Pesanan" << endl;
        cout << "[7] Hapus Item Menu dari Pesanan" << endl;
        cout << "[8] Ubah Urutan Tabel Pesanan" << endl;
        cout << "[9] Cari Pesanan Berdasarkan Nama Menu" << endl;
        cout << "[0] Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihanMenu;

        if (pilihanMenu == "1") {
            cout << "\n--- BUAT PESANAN BARU ---" << endl;
            cout << "Ketik 'x' pada Kode Pesanan untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Kode Pesanan (contoh: ORD01): ";
                cin >> kodePesanan;

                if (kodePesanan == "x") {
                    valid = true;
                } else if (searchPesanan(L, kodePesanan) != NULL) {
                    cout << "[!] Error: Kode pesanan sudah dipakai! Input kode lain." << endl;
                } else {
                    valid = true;
                    cout << "Nama Pelanggan: ";
                    getline(cin >> ws, namaPelanggan);
                    cout << "Nomor Meja: ";
                    cin >> nomorMeja;
                    statusPesanan = "Diproses";

                    addPesanan(L, createElementPesanan(kodePesanan, namaPelanggan, nomorMeja, statusPesanan));
                    cout << "[OK] Pesanan " << kodePesanan << " berhasil dibuat." << endl;
                    pauseScreen();
                }
            } while (!valid);

        } else if (pilihanMenu == "2") {
            cout << "\n--- TAMBAH MENU KE PESANAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Kode Pesanan Tujuan: ";
                cin >> targetKode;

                if (targetKode == "x") {
                    valid = true;
                } else {
                    p = searchPesanan(L, targetKode);
                    if (p == NULL) {
                        cout << "[!] Error: Pesanan tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        cout << "Nama Menu: ";
                        getline(cin >> ws, namaMenu);
                        cout << "Kategori (Makanan/Minuman/Snack/Dessert): ";
                        cin >> kategoriMenu;
                        cout << "Harga Satuan (Rp): ";
                        cin >> hargaSatuan;
                        cout << "Jumlah Porsi: ";
                        cin >> jumlahPorsi;

                        if (hargaSatuan < 0 || jumlahPorsi <= 0) {
                            cout << "[!] Gagal: Harga tidak boleh negatif dan jumlah porsi minimal 1." << endl;
                        } else {
                            addItemMenu(p, createElementItem(namaMenu, kategoriMenu, hargaSatuan, jumlahPorsi));
                            cout << "[OK] Menu berhasil ditambahkan ke pesanan " << targetKode << "." << endl;
                        }
                        pauseScreen();
                    }
                }
            } while (!valid);

        } else if (pilihanMenu == "3") {
            cout << "\n--- LIHAT STRUK / DETAIL PESANAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Kode Pesanan: ";
                cin >> targetKode;

                if (targetKode == "x") {
                    valid = true;
                } else {
                    p = searchPesanan(L, targetKode);
                    if (p == NULL) {
                        cout << "[!] Error: Pesanan tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        showPesananDetails(p);
                        pauseScreen();
                    }
                }
            } while (!valid);

        } else if (pilihanMenu == "4") {
            cout << "\n--- UPDATE DATA PESANAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Kode Pesanan yang diupdate: ";
                cin >> targetKode;

                if (targetKode == "x") {
                    valid = true;
                } else {
                    p = searchPesanan(L, targetKode);
                    if (p == NULL) {
                        cout << "[!] Error: Pesanan tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        string namaBaru, statusBaru;
                        int mejaBaru;

                        cout << "Nama Pelanggan Baru: ";
                        getline(cin >> ws, namaBaru);
                        cout << "Nomor Meja Baru: ";
                        cin >> mejaBaru;
                        cout << "Status Baru (Diproses/Selesai/Dibayar): ";
                        cin >> statusBaru;

                        updatePesanan(p, namaBaru, mejaBaru, statusBaru);
                        cout << "[OK] Data pesanan berhasil diperbarui." << endl;
                        pauseScreen();
                    }
                }
            } while (!valid);

        } else if (pilihanMenu == "5") {
            cout << "\n--- UPDATE ITEM MENU DI PESANAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Kode Pesanan: ";
                cin >> targetKode;

                if (targetKode == "x") {
                    valid = true;
                } else {
                    p = searchPesanan(L, targetKode);
                    if (p == NULL) {
                        cout << "[!] Error: Pesanan tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        string nmLama;
                        cout << "Nama Menu Lama: ";
                        getline(cin >> ws, nmLama);

                        adrItem foundItem = searchItemMenu(p, nmLama);
                        if (foundItem != NULL) {
                            string nmBaru, katBaru;
                            int hargaBaru, jmlBaru;

                            cout << "Nama Menu Baru: ";
                            getline(cin >> ws, nmBaru);
                            cout << "Kategori Baru (Makanan/Minuman/Snack/Dessert): ";
                            cin >> katBaru;
                            cout << "Harga Satuan Baru (Rp): ";
                            cin >> hargaBaru;
                            cout << "Jumlah Porsi Baru: ";
                            cin >> jmlBaru;

                            if (hargaBaru < 0 || jmlBaru <= 0) {
                                cout << "[!] Gagal: Harga/jumlah tidak valid." << endl;
                            } else {
                                updateItemMenu(foundItem, nmBaru, katBaru, hargaBaru, jmlBaru);
                                cout << "[OK] Item menu berhasil diperbarui." << endl;
                            }
                        } else {
                            cout << "[!] Item menu tidak ditemukan pada pesanan ini." << endl;
                        }
                        pauseScreen();
                    }
                }
            } while (!valid);

        } else if (pilihanMenu == "6") {
            cout << "\n--- HAPUS / BATALKAN PESANAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Kode Pesanan yang dihapus: ";
                cin >> targetKode;

                if (targetKode == "x") {
                    valid = true;
                } else if (searchPesanan(L, targetKode) == NULL) {
                    cout << "[!] Error: Pesanan tidak ditemukan! Input ulang." << endl;
                } else {
                    deletePesanan(L, targetKode);
                    valid = true;
                    cout << "[OK] Pesanan " << targetKode << " beserta seluruh itemnya berhasil dihapus." << endl;
                    pauseScreen();
                }
            } while (!valid);

        } else if (pilihanMenu == "7") {
            cout << "\n--- HAPUS ITEM MENU DARI PESANAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Kode Pesanan: ";
                cin >> targetKode;

                if (targetKode == "x") {
                    valid = true;
                } else {
                    p = searchPesanan(L, targetKode);
                    if (p == NULL) {
                        cout << "[!] Error: Pesanan tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        cout << "Nama Menu yang dihapus: ";
                        getline(cin >> ws, namaMenu);

                        if (searchItemMenu(p, namaMenu) == NULL) {
                            cout << "[!] Error: Menu tidak ditemukan di pesanan ini." << endl;
                        } else {
                            deleteItemMenu(p, namaMenu);
                            cout << "[OK] Item menu berhasil dihapus." << endl;
                        }
                        pauseScreen();
                    }
                }
            } while (!valid);

        } else if (pilihanMenu == "8") {
            cout << "\n--- PILIH URUTAN TABEL PESANAN ---" << endl;
            cout << "1. Kode Pesanan (A-Z)" << endl;
            cout << "2. Total Bayar Tertinggi" << endl;
            cout << "3. Total Bayar Terendah" << endl;
            cout << "4. Total Porsi Terbanyak" << endl;
            cout << "5. Makanan Terbanyak" << endl;
            cout << "6. Minuman Terbanyak" << endl;
            cout << "Pilih: ";
            int tempMode;
            cin >> tempMode;
            if (tempMode >= 1 && tempMode <= 6) {
                modeUrutan = tempMode;
            }

        } else if (pilihanMenu == "9") {
            cout << "\n--- CARI PESANAN BERDASARKAN MENU ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                string cari;
                cout << "Masukkan nama menu yang dicari: ";
                getline(cin >> ws, cari);

                if (cari == "x") {
                    valid = true;
                } else {
                    bool ketemu = searchMenuDiSemuaPesanan(L, cari);
                    if (!ketemu) {
                        cout << "[!] Belum ada pesanan yang memesan menu tersebut." << endl;
                    } else {
                        valid = true;
                    }
                    pauseScreen();
                }
            } while (!valid);

        } else if (pilihanMenu == "0") {
            berjalan = false;
        }
    }

    // Bebaskan seluruh memori list sebelum program berakhir
    clearAllPesanan(L);
    return 0;
}
