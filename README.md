# 🍽️ Sistem Pemesanan Menu Restoran Online (C++)

Aplikasi manajemen pemesanan menu restoran berbasis *console* (CLI) yang dibangun menggunakan bahasa **C++** dengan pendekatan **Abstract Data Type (ADT)** terpisah. Proyek ini disusun untuk memenuhi **Topik 13 — Pemesanan Menu Restoran (Online)** dengan mengimplementasikan dua struktur data utama: **Multi-Linked List Model 02 (MLL-02)** dan **Binary Search Tree (BST)**.

---

## 🏗️ Arsitektur Struktur Data

### 1. Multi-Linked List Model 02 (`MLL-02` / N-to-M)
Satu transaksi pesanan dapat memuat banyak menu berbeda, dan satu jenis menu dapat dipesan pada banyak transaksi berbeda. Relasi disimpan dalam **list relasi terpisah** di luar list parent maupun child.

| Komponen | Nama List | Tipe List Dasar | Metode Insert | Atribut Data (`infotype`) |
| :--- | :--- | :--- | :--- | :--- |
| **Parent (Order)** | `ListOrder` | Doubly Linked List (`first`, `last`) | **Insert Last** | `nomorOrder`, `idPelanggan`, `waktuPesan`, `statusPesanan` |
| **Child (Menu)** | `ListMenu` | Doubly Linked List (`first`, `last`) | **Insert First** | `idMenu`, `namaMenu`, `kategori`, `hargaSatuan` |
| **Relasi (Item Pesanan)** | `ListRelasi` | Singly Linked List (`first`) | **Insert First** | `nomorOrder`, `jumlahPorsi`, `hargaSaatPesan`, `catatan`, pointer `parent` & `child` |

### 2. Binary Search Tree (`BST`)
Digunakan untuk pencarian cepat riwayat dan status transaksi dengan **key `nomorOrder` (`int`)**. Setiap node (`NodeBST`) menyimpan `infotypeOrder`, pointer `left`, dan pointer `right`.

---

## ✨ Fitur Program

### Fungsionalitas Umum MLL-02
* **Penambahan Elemen:** Tambah Order (*Insert Last* + sinkronisasi otomatis ke BST), tambah Menu (*Insert First*), dan tambah Relasi Item Pesanan (*Insert First*).
* **Penghapusan Elemen:** Hapus Order beserta seluruh relasinya (*cascade delete*), hapus Menu beserta seluruh relasinya, serta hapus satu relasi tertentu.
* **Pencarian & Pengecekan Relasi:** Cari Order, cari Menu, dan cek apakah Order & Menu saling berelasi.
* **Tampilan Data:** Tampilkan daftar Order, daftar Menu, seluruh Order beserta Menu-nya (`Parent -> Child`), serta seluruh Menu beserta Order-nya (`Child -> Parent`).
* **Perhitungan Relasi:** Hitung jumlah jenis Menu (child) pada Order tertentu dan jumlah Order (parent) yang memesan Menu tertentu.
* **Pembaruan Status:** Update `statusPesanan` secara tersinkronisasi antara MLL dan BST.

### Fungsionalitas Umum BST
* **Insert Node:** Menyisipkan riwayat order berdasarkan key `nomorOrder`.
* **Search Node:** Mencari riwayat dan status transaksi berdasarkan `nomorOrder`.
* **Delete Node:** Menghapus node dengan penanganan lengkap kasus **daun (0 anak)**, **1 anak**, dan **2 anak** (*in-order successor*).
* **Traversal:** Menampilkan data dengan urutan **In-Order**, **Pre-Order**, dan **Post-Order**.
* **Statistik Pohon:** Menampilkan nilai minimum, maksimum, tinggi pohon (*height*), dan jumlah total node.

### Fungsionalitas Khusus (Topik 13)
1. **Total Porsi per Menu:** Menghitung total `jumlahPorsi` per `idMenu` dan menampilkan menu paling banyak diminati pelanggan.
2. **Analisis Menu Dipesan Bersamaan:** Melihat pasangan menu yang sering dipesan bersamaan dalam satu transaksi `nomorOrder`.
3. **Total Pendapatan per Menu:** Menghitung total pendapatan per menu (`jumlahPorsi * hargaSaatPesan`) beserta total keseluruhan.
4. **Analisis Waktu Favorit Menu:** Menggabungkan `waktuPesan` dengan `idMenu` untuk mengetahui distribusi slot waktu (*Pagi / Siang / Sore / Malam*) serta waktu favorit pelanggan memesan menu tertentu.

---

## ✅ Kepatuhan Ketentuan Teknis
* ADT dasar `Doubly Linked List` dan `Singly Linked List` digunakan sesuai standar tanpa modifikasi struktural.
* Variasi metode penambahan antar-list terpenuhi (1 *Insert Last* dan 2 *Insert First*).
* Pemisahan file header (`pemesanan.h`), implementasi (`pemesanan.cpp`), dan driver (`main.cpp`).
* Seluruh subprogram menggunakan parameter (tanpa variabel global) dan dilengkapi spesifikasi **I.S. / F.S.**
* Tidak menggunakan `break` ataupun `return` di dalam perulangan.
* Library yang digunakan terbatas pada I/O (`<iostream>`, `<iomanip>`) dan string (`<string>`).

---

## 📂 Struktur File

```text
TUBES RESTORAN/
├── main.cpp                 # Program utama & antarmuka menu interaktif (0-19)
├── pemesanan.h              # Definisi ADT MLL-02 & BST serta deklarasi subprogram (I.S./F.S.)
├── pemesanan.cpp            # Implementasi seluruh primitif MLL-02, BST, & analisis khusus
├── dummy_data.txt           # Skenario input data uji (7 Order, 6 Menu, 18 Relasi)
├── TUBES_RESTORAN.cbp       # File proyek Code::Blocks
├── TUBES_RESTORAN.depend    # File dependensi Code::Blocks
├── TUBES_RESTORAN.layout    # File tata letak editor Code::Blocks
└── README.md                # Dokumentasi proyek
```

---

## 🚀 Cara Menjalankan Program

### Melalui Terminal (macOS / Linux)
```bash
g++ main.cpp pemesanan.cpp -o pemesanan_app
./pemesanan_app
```

### Melalui Code::Blocks
1. Buka file `TUBES_RESTORAN.cbp`.
2. Klik **Build and Run** (`F9`).

### Mengisi Data Uji Otomatis
Buka file [data](dummy_data.txt), salin seluruh isinya, lalu tempel (*paste*) langsung ke konsol saat program berada pada menu utama untuk memuat 7 transaksi (membentuk BST seimbang dengan tinggi 3), 6 menu, dan 18 item relasi secara instan.
