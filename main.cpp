#include "pemesanan.h"
#include <iomanip>

// ============================================================================
// FUNGSI PEMBANTU INPUT & TAMPILAN MENU (TANPA VARIABEL GLOBAL)
// ============================================================================

// I.S. prompt bertipe string terdefinisi.
// F.S. Mengembalikan bilangan bulat valid dari input pengguna (atau 0 jika EOF tercapai).
int inputInt(string prompt) {
    int nilai = 0;
    bool selesai = false;
    while (!selesai) {
        cout << prompt;
        if (cin >> nilai) {
            selesai = true;
            cin.ignore(10000, '\n');
        } else if (cin.eof()) {
            nilai = 0;
            selesai = true;
        } else {
            cout << "Input tidak valid! Harap masukkan angka bulat." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    return nilai;
}

// I.S. prompt bertipe string terdefinisi.
// F.S. Mengembalikan satu baris teks (termasuk spasi) yang dimasukkan pengguna.
string inputLine(string prompt) {
    string teks = "";
    cout << prompt;
    getline(cin, teks);
    return teks;
}

// I.S. judul bertipe string terdefinisi.
// F.S. Menampilkan header tabel standar untuk hasil traversal BST ke layar.
void cetakHeaderTabelBST(string judul) {
    cout << "\n================ " << judul << " ================" << endl;
    cout << left << setw(10) << "NO ORDER"
         << setw(16) << "ID PELANGGAN"
         << setw(14) << "WAKTU PESAN"
         << setw(16) << "STATUS" << endl;
    cout << "--------------------------------------------------------" << endl;
}

// I.S. Sembarang.
// F.S. Menampilkan daftar menu utama aplikasi ke layar.
void tampilkanMenuUtama() {
    cout << "\n================================================================" << endl;
    cout << "     SISTEM PEMESANAN MENU RESTORAN (ONLINE) - MLL-02 & BST     " << endl;
    cout << "================================================================" << endl;
    cout << "--- MANAJEMEN MLL-02 (ORDER, MENU & RELASI) ---" << endl;
    cout << " [1]  Tambah Order Baru (Parent - Insert Last + Sync BST)" << endl;
    cout << " [2]  Tambah Menu Baru (Child - Insert First)" << endl;
    cout << " [3]  Tambah Item Pesanan / Relasi (Insert First)" << endl;
    cout << " [4]  Update Status Pesanan (Sinkron MLL & BST)" << endl;
    cout << " [5]  Hapus Order beserta Relasinya" << endl;
    cout << " [6]  Hapus Menu beserta Relasinya" << endl;
    cout << " [7]  Hapus Relasi Tertentu (Hapus Item dari Order)" << endl;
    cout << " [8]  Pencarian MLL (Cari Order / Cari Menu / Cek Relasi)" << endl;
    cout << " [9]  Tampilkan Data MLL (Order, Menu, Order->Menu, Menu->Order)" << endl;
    cout << " [10] Hitung Relasi (Jumlah Menu per Order & Order per Menu)" << endl;
    cout << "--- MANAJEMEN BST RIWAYAT TRANSAKSI (KEY: NOMOR ORDER) ---" << endl;
    cout << " [11] Insert Node Riwayat Order ke BST" << endl;
    cout << " [12] Cari Riwayat & Status Transaksi di BST" << endl;
    cout << " [13] Hapus Node dari BST (Kasus Daun, 1 Anak, 2 Anak)" << endl;
    cout << " [14] Traversal BST (In-Order, Pre-Order, Post-Order)" << endl;
    cout << " [15] Statistik BST (Min, Max, Tinggi Pohon, Jumlah Node)" << endl;
    cout << "--- FUNGSIONALITAS KHUSUS (TOPIK 13) ---" << endl;
    cout << " [16] Total Porsi per Menu & Menu Paling Diminati" << endl;
    cout << " [17] Menu Sering Dipesan Bersamaan dalam Satu Order" << endl;
    cout << " [18] Total Pendapatan per Menu" << endl;
    cout << " [19] Analisis Waktu Favorit Pemesanan Menu" << endl;
    cout << " [0]  Keluar Program" << endl;
    cout << "================================================================" << endl;
}

// ============================================================================
// SUBPROGRAM HANDLER MENU (BERPARAMETER, LENGKAP I.S. & F.S.)
// ============================================================================

// I.S. ListOrder LO dan BST root terdefinisi.
// F.S. Menambahkan Order baru ke akhir LO (Insert Last) dan menyisipkannya ke BST jika nomorOrder belum ada.
void menuTambahOrder(ListOrder &LO, adrBST &root) {
    cout << "\n--- [1] TAMBAH ORDER BARU (INSERT LAST) ---" << endl;
    infotypeOrder data;
    data.nomorOrder = inputInt("Nomor Order (Angka Unik, misal 101) : ");

    if (findOrder(LO, data.nomorOrder) != NULL) {
        cout << "Gagal: Order #" << data.nomorOrder << " sudah terdaftar di MLL." << endl;
    } else {
        data.idPelanggan = inputLine("ID Pelanggan (misal CUST01)         : ");
        data.waktuPesan = inputLine("Waktu Pesan (HH:MM, misal 12:30)    : ");
        data.statusPesanan = inputLine("Status (Diproses/Selesai/Dibayar)   : ");

        adrOrder P = allocateOrder(data);
        insertLastOrder(LO, P);

        if (searchBST(root, data.nomorOrder) == NULL) {
            insertBST(root, data);
        }
        cout << "Berhasil: Order #" << data.nomorOrder << " ditambahkan ke MLL dan BST." << endl;
    }
}

// I.S. ListMenu LM terdefinisi.
// F.S. Menambahkan Menu baru ke awal LM (Insert First) jika idMenu belum terdaftar.
void menuTambahMenu(ListMenu &LM) {
    cout << "\n--- [2] TAMBAH MENU BARU (INSERT FIRST) ---" << endl;
    infotypeMenu data;
    data.idMenu = inputLine("ID Menu (Unik, misal MN01)          : ");

    if (findMenu(LM, data.idMenu) != NULL) {
        cout << "Gagal: Menu dengan ID '" << data.idMenu << "' sudah terdaftar." << endl;
    } else {
        data.namaMenu = inputLine("Nama Menu                           : ");
        data.kategori = inputLine("Kategori (Makanan/Minuman/Snack)    : ");
        data.hargaSatuan = inputInt("Harga Satuan (Rp)                   : ");

        adrMenu C = allocateMenu(data);
        insertFirstMenu(LM, C);
        cout << "Berhasil: Menu [" << data.idMenu << "] " << data.namaMenu << " ditambahkan." << endl;
    }
}

// I.S. ListOrder LO, ListMenu LM, dan ListRelasi LR terdefinisi.
// F.S. Menambahkan relasi baru di awal LR (Insert First), atau menambah porsi jika relasi sudah ada.
void menuTambahRelasi(ListOrder LO, ListMenu LM, ListRelasi &LR) {
    cout << "\n--- [3] TAMBAH ITEM PESANAN / RELASI (INSERT FIRST) ---" << endl;
    if (isEmptyOrder(LO) || isEmptyMenu(LM)) {
        cout << "Gagal: Pastikan minimal sudah ada 1 Order dan 1 Menu." << endl;
    } else {
        int noOrder = inputInt("Nomor Order Tujuan                  : ");
        adrOrder P = findOrder(LO, noOrder);
        if (P == NULL) {
            cout << "Gagal: Order #" << noOrder << " tidak ditemukan." << endl;
        } else {
            string idMenu = inputLine("ID Menu yang Dipesan                : ");
            adrMenu C = findMenu(LM, idMenu);
            if (C == NULL) {
                cout << "Gagal: Menu '" << idMenu << "' tidak ditemukan." << endl;
            } else {
                int porsi = inputInt("Jumlah Porsi                        : ");
                string catatan = inputLine("Catatan (isi '-' jika normal)       : ");

                if (porsi <= 0) {
                    cout << "Gagal: Jumlah porsi harus lebih dari 0." << endl;
                } else {
                    adrRelasi existing = findRelasi(LR, noOrder, C->info.idMenu);
                    if (existing != NULL) {
                        existing->info.jumlahPorsi += porsi;
                        if (catatan != "-" && catatan != "") {
                            if (existing->info.catatan == "-" || existing->info.catatan == "") {
                                existing->info.catatan = catatan;
                            } else {
                                existing->info.catatan = existing->info.catatan + "; " + catatan;
                            }
                        }
                        cout << "Menu sudah ada di Order #" << noOrder
                             << ". Jumlah porsi diakumulasi menjadi "
                             << existing->info.jumlahPorsi << "." << endl;
                    } else {
                        infotypeRelasi dataRel;
                        dataRel.nomorOrder = P->info.nomorOrder;
                        dataRel.jumlahPorsi = porsi;
                        dataRel.hargaSaatPesan = C->info.hargaSatuan;
                        dataRel.catatan = catatan;

                        adrRelasi R = allocateRelasi(P, C, dataRel);
                        insertFirstRelasi(LR, R);
                        cout << "Berhasil: [" << C->info.idMenu << "] " << C->info.namaMenu
                             << " (" << porsi << " porsi @ Rp " << dataRel.hargaSaatPesan
                             << ") ditambahkan ke Order #" << noOrder << "." << endl;
                    }
                }
            }
        }
    }
}

// I.S. ListOrder LO, ListMenu LM, dan ListRelasi LR terdefinisi.
// F.S. Menjalankan sub-opsi pencarian Order, pencarian Menu, atau pengecekan relasi antara keduanya.
void menuPencarianMLL(ListOrder LO, ListMenu LM, ListRelasi LR) {
    cout << "\n--- [8] PENCARIAN MLL ---" << endl;
    cout << " [1] Cari Order (Parent)" << endl;
    cout << " [2] Cari Menu (Child)" << endl;
    cout << " [3] Cek Apakah Order dan Menu Saling Berelasi" << endl;
    int sub = inputInt("Pilih sub-menu (1-3): ");

    if (sub == 1) {
        int noOrder = inputInt("Masukkan Nomor Order: ");
        adrOrder P = findOrder(LO, noOrder);
        if (P == NULL) {
            cout << "Order #" << noOrder << " tidak ditemukan." << endl;
        } else {
            cout << "Order Ditemukan -> #" << P->info.nomorOrder
                 << " | Pelanggan: " << P->info.idPelanggan
                 << " | Waktu: " << P->info.waktuPesan
                 << " | Status: " << P->info.statusPesanan
                 << " | Total Bayar: Rp " << calculateTotalBayarOrder(LR, noOrder) << endl;
        }
    } else if (sub == 2) {
        string idMenu = inputLine("Masukkan ID Menu: ");
        adrMenu C = findMenu(LM, idMenu);
        if (C == NULL) {
            cout << "Menu '" << idMenu << "' tidak ditemukan." << endl;
        } else {
            cout << "Menu Ditemukan -> [" << C->info.idMenu << "] " << C->info.namaMenu
                 << " | Kategori: " << C->info.kategori
                 << " | Harga: Rp " << C->info.hargaSatuan << endl;
        }
    } else if (sub == 3) {
        int noOrder = inputInt("Masukkan Nomor Order: ");
        string idMenu = inputLine("Masukkan ID Menu    : ");
        if (isRelated(LR, noOrder, idMenu)) {
            adrRelasi R = findRelasi(LR, noOrder, idMenu);
            cout << "BERELASI: Order #" << noOrder << " memesan ["
                 << R->child->info.idMenu << "] " << R->child->info.namaMenu
                 << " sebanyak " << R->info.jumlahPorsi << " porsi"
                 << " (Catatan: " << R->info.catatan << ")." << endl;
        } else {
            cout << "TIDAK BERELASI: Order #" << noOrder
                 << " tidak memesan Menu '" << idMenu << "'." << endl;
        }
    } else {
        cout << "Pilihan sub-menu tidak valid." << endl;
    }
}

// I.S. ListOrder LO, ListMenu LM, dan ListRelasi LR terdefinisi.
// F.S. Menampilkan data MLL sesuai sub-opsi yang dipilih pengguna.
void menuTampilkanMLL(ListOrder LO, ListMenu LM, ListRelasi LR) {
    cout << "\n--- [9] TAMPILKAN DATA MLL ---" << endl;
    cout << " [1] Tampilkan Semua Order (Parent)" << endl;
    cout << " [2] Tampilkan Semua Menu (Child)" << endl;
    cout << " [3] Tampilkan Semua Order beserta Menu-nya (Parent -> Child)" << endl;
    cout << " [4] Tampilkan Semua Menu beserta Order-nya (Child -> Parent)" << endl;
    int sub = inputInt("Pilih sub-menu (1-4): ");

    if (sub == 1) {
        showAllOrder(LO);
    } else if (sub == 2) {
        showAllMenu(LM);
    } else if (sub == 3) {
        showAllOrderWithMenu(LO, LR);
    } else if (sub == 4) {
        showAllMenuWithOrder(LM, LR);
    } else {
        cout << "Pilihan sub-menu tidak valid." << endl;
    }
}

// I.S. ListOrder LO, ListMenu LM, dan ListRelasi LR terdefinisi.
// F.S. Menampilkan jumlah child dari parent tertentu atau jumlah parent dari child tertentu.
void menuHitungRelasi(ListOrder LO, ListMenu LM, ListRelasi LR) {
    cout << "\n--- [10] HITUNG JUMLAH RELASI ---" << endl;
    cout << " [1] Hitung Jumlah Jenis Menu (Child) dari Order Tertentu" << endl;
    cout << " [2] Hitung Jumlah Order (Parent) dari Menu Tertentu" << endl;
    int sub = inputInt("Pilih sub-menu (1-2): ");

    if (sub == 1) {
        int noOrder = inputInt("Masukkan Nomor Order: ");
        adrOrder P = findOrder(LO, noOrder);
        if (P == NULL) {
            cout << "Order #" << noOrder << " tidak ditemukan." << endl;
        } else {
            cout << "Order #" << noOrder << " memiliki "
                 << countMenuByOrder(LR, noOrder) << " jenis menu (child)." << endl;
        }
    } else if (sub == 2) {
        string idMenu = inputLine("Masukkan ID Menu: ");
        adrMenu C = findMenu(LM, idMenu);
        if (C == NULL) {
            cout << "Menu '" << idMenu << "' tidak ditemukan." << endl;
        } else {
            cout << "Menu [" << C->info.idMenu << "] " << C->info.namaMenu
                 << " dipesan pada " << countOrderByMenu(LR, C->info.idMenu)
                 << " transaksi order (parent)." << endl;
        }
    } else {
        cout << "Pilihan sub-menu tidak valid." << endl;
    }
}

// I.S. BST root terdefinisi.
// F.S. Menyisipkan node riwayat order baru secara langsung ke dalam BST jika nomorOrder belum ada.
void menuInsertBST(adrBST &root) {
    cout << "\n--- [11] INSERT NODE RIWAYAT ORDER KE BST ---" << endl;
    infotypeOrder data;
    data.nomorOrder = inputInt("Nomor Order (Key BST)               : ");

    if (searchBST(root, data.nomorOrder) != NULL) {
        cout << "Gagal: Node dengan Nomor Order #" << data.nomorOrder << " sudah ada di BST." << endl;
    } else {
        data.idPelanggan = inputLine("ID Pelanggan                        : ");
        data.waktuPesan = inputLine("Waktu Pesan (HH:MM)                 : ");
        data.statusPesanan = inputLine("Status Pesanan                      : ");
        insertBST(root, data);
        cout << "Berhasil: Node Order #" << data.nomorOrder << " disisipkan ke BST." << endl;
    }
}

// I.S. BST root dan ListRelasi LR terdefinisi.
// F.S. Mencari node berdasarkan nomorOrder pada BST dan menampilkan detail riwayat serta statusnya.
void menuCariBST(adrBST root, ListRelasi LR) {
    cout << "\n--- [12] CARI RIWAYAT & STATUS TRANSAKSI DI BST ---" << endl;
    int noOrder = inputInt("Masukkan Nomor Order yang Dicari: ");
    adrBST hasil = searchBST(root, noOrder);

    if (hasil == NULL) {
        cout << "Riwayat Order #" << noOrder << " tidak ditemukan pada BST." << endl;
    } else {
        cout << "Riwayat Ditemukan pada BST:" << endl;
        cout << " * Nomor Order   : #" << hasil->info.nomorOrder << endl;
        cout << " * ID Pelanggan  : " << hasil->info.idPelanggan << endl;
        cout << " * Waktu Pesan   : " << hasil->info.waktuPesan
             << " (" << getSlotWaktu(hasil->info.waktuPesan) << ")" << endl;
        cout << " * Status Pesanan: " << hasil->info.statusPesanan << endl;
        int totalBayar = calculateTotalBayarOrder(LR, noOrder);
        if (totalBayar > 0) {
            cout << " * Total Tagihan : Rp " << totalBayar << endl;
        }
    }
}

// I.S. BST root terdefinisi.
// F.S. Menghapus node berdasarkan nomorOrder dari BST jika ditemukan dan menampilkan konfirmasi.
void menuHapusBST(adrBST &root) {
    cout << "\n--- [13] HAPUS NODE DARI BST ---" << endl;
    if (root == NULL) {
        cout << "BST masih kosong." << endl;
    } else {
        int noOrder = inputInt("Masukkan Nomor Order yang akan dihapus dari BST: ");
        if (searchBST(root, noOrder) == NULL) {
            cout << "Node Order #" << noOrder << " tidak ditemukan pada BST." << endl;
        } else {
            deleteBST(root, noOrder);
            cout << "Node Order #" << noOrder << " berhasil dihapus dari BST." << endl;
        }
    }
}

// I.S. BST root terdefinisi.
// F.S. Menampilkan hasil traversal In-Order, Pre-Order, dan/atau Post-Order pada BST.
void menuTraversalBST(adrBST root) {
    cout << "\n--- [14] TRAVERSAL BST ---" << endl;
    if (root == NULL) {
        cout << "BST masih kosong." << endl;
    } else {
        cout << " [1] In-Order   (Terurut Menanjak)" << endl;
        cout << " [2] Pre-Order  (Root -> Left -> Right)" << endl;
        cout << " [3] Post-Order (Left -> Right -> Root)" << endl;
        cout << " [4] Tampilkan Ketiganya" << endl;
        int sub = inputInt("Pilih jenis traversal (1-4): ");

        if (sub == 1 || sub == 4) {
            cetakHeaderTabelBST("BST IN-ORDER");
            inOrderBST(root);
        }
        if (sub == 2 || sub == 4) {
            cetakHeaderTabelBST("BST PRE-ORDER");
            preOrderBST(root);
        }
        if (sub == 3 || sub == 4) {
            cetakHeaderTabelBST("BST POST-ORDER");
            postOrderBST(root);
        }
        if (sub < 1 || sub > 4) {
            cout << "Pilihan traversal tidak valid." << endl;
        }
    }
}

// ============================================================================
// PROGRAM UTAMA
// ============================================================================

int main() {
    ListOrder LO;
    ListMenu LM;
    ListRelasi LR;
    adrBST rootBST;

    createListOrder(LO);
    createListMenu(LM);
    createListRelasi(LR);
    createBST(rootBST);

    int pilihan = -1;

    while (pilihan != 0) {
        tampilkanMenuUtama();
        pilihan = inputInt("Pilih menu (0-19): ");

        if (pilihan == 1) {
            menuTambahOrder(LO, rootBST);
        } else if (pilihan == 2) {
            menuTambahMenu(LM);
        } else if (pilihan == 3) {
            menuTambahRelasi(LO, LM, LR);
        } else if (pilihan == 4) {
            cout << "\n--- [4] UPDATE STATUS PESANAN ---" << endl;
            int noOrder = inputInt("Nomor Order                         : ");
            string statusBaru = inputLine("Status Baru (Diproses/Selesai/Dibayar/Dibatalkan): ");
            updateStatusOrder(LO, rootBST, noOrder, statusBaru);
        } else if (pilihan == 5) {
            cout << "\n--- [5] HAPUS ORDER BESERTA RELASINYA ---" << endl;
            int noOrder = inputInt("Masukkan Nomor Order yang dihapus: ");
            deleteOrderByNomor(LO, LR, noOrder);
        } else if (pilihan == 6) {
            cout << "\n--- [6] HAPUS MENU BESERTA RELASINYA ---" << endl;
            string idMenu = inputLine("Masukkan ID Menu yang dihapus: ");
            deleteMenuByID(LM, LR, idMenu);
        } else if (pilihan == 7) {
            cout << "\n--- [7] HAPUS RELASI TERTENTU ---" << endl;
            int noOrder = inputInt("Masukkan Nomor Order: ");
            string idMenu = inputLine("Masukkan ID Menu    : ");
            deleteRelasiTertentu(LR, noOrder, idMenu);
        } else if (pilihan == 8) {
            menuPencarianMLL(LO, LM, LR);
        } else if (pilihan == 9) {
            menuTampilkanMLL(LO, LM, LR);
        } else if (pilihan == 10) {
            menuHitungRelasi(LO, LM, LR);
        } else if (pilihan == 11) {
            menuInsertBST(rootBST);
        } else if (pilihan == 12) {
            menuCariBST(rootBST, LR);
        } else if (pilihan == 13) {
            menuHapusBST(rootBST);
        } else if (pilihan == 14) {
            menuTraversalBST(rootBST);
        } else if (pilihan == 15) {
            showStatistikBST(rootBST);
        } else if (pilihan == 16) {
            hitungTotalPorsiPerMenu(LM, LR);
        } else if (pilihan == 17) {
            analisisMenuBersamaan(LO, LM, LR);
        } else if (pilihan == 18) {
            hitungPendapatanPerMenu(LM, LR);
        } else if (pilihan == 19) {
            cout << "\n--- [19] ANALISIS WAKTU FAVORIT MENU ---" << endl;
            string idMenu = inputLine("Masukkan ID Menu yang dianalisis: ");
            analisisWaktuFavoritMenu(LM, LR, idMenu);
        } else if (pilihan == 0) {
            dealokasiSemua(LO, LM, LR, rootBST);
            cout << "\nSeluruh memori MLL-02 dan BST telah dibersihkan. Program selesai." << endl;
        } else {
            cout << "\nPilihan tidak valid! Silakan masukkan angka 0 sampai 19." << endl;
        }
    }

    return 0;
}
