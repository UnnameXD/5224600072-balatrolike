# DP Week 1 - PreTest
Nama : Muhammmad Syifaul Qolbi
NRP  : 5224600072
Kelas: GT 12-C

# Architecture Overview

Projek ini adalah game **Blackjack Roguelike** berbasis teks (*console-driven*) yang ditulis dalam bahasa C++. Alur permainan (*gameplay loop*) memiliki tingkat kesulitan yang terus meningkat di setiap babak, serta menghadirkan peningkatan kemampuan pemain yang permanen, peningkatan HP, dan elemen prosedural.

Arsitektur sistem dibagi menjadi beberapa lapisan modular:

* **Game Loop & Session State (`RunSession`, `main`)**: 
    `RunSession` mengatur siklus hidup inti dari jalannya permainan, termasuk loop progres babak luar (*outer round progression loop*), variabel status pemain/bandar (`playerHP`, `dealerHP`, `cash`, `round`), dan loop pertarungan babak dalam (*inner combat round loop*).
* **Procedural Item & Upgrade Generation (`Perk`, `PerkFactory`, `Shop`)**: 
    Menangani instansiasi, perolehan dinamis, dan kalkulasi peningkatan dari mekanik pengubah efek (*Perk*). Toko (*Shop*) secara dinamis membuat tampilan pratinjau (*preview*) sebelum memproses pembelian yang sebenarnya.
* **Card & Rule Subsystem (`Card`)**: 
    Lapisan utilitas berbasis data fungsional yang mengabstraksikan atribut kartu standar (angka dan kembang), menangani evaluasi kartu di tangan berbasis vektor (`calculateTotal`), dan mengubah nilai Ace (Soft/Hard Ace) secara dinamis saat penghitungan total poin.

---

# Pattern Usage

Kode ini menerapkan pola desain perangkat lunak (*software design patterns*) tertentu untuk mengelola penambahan fitur dinamis dan pembuatan objek:

### 1. Simple Factory Pattern
Kelas `PerkFactory` bertindak sebagai pusat pembuatan objek untuk menangani alokasi `Perk` yang bersifat polimorfik.
* **Penerapan**: Memisahkan proses pembuatan objek dari alur eksekusi utama game (`RunSession` dan `Shop`). Alih-alih menulis kode instansiasi kelas konkret secara eksplisit menggunakan `new Bonus21Damage()`, sistem mendelegasikannya lewat fungsi `PerkFactory::createStartingPerk()` dan `PerkFactory::createShopPerk(choice)`.
* **Keuntungan**: Memusatkan logika perubahan. Jika ada jenis perk baru yang ditambahkan, perubahan struktur hanya terbatas pada blok `switch` di dalam factory, tanpa mengganggu alur sistem pada toko (*shop*).

### 2. Decorator Pattern (Varian Perilaku / Pipeline)
Meskipun pola Decorator struktural tradisional biasanya membungkus instansi kelas untuk menambah fungsionalitas secara dinamis, sistem perk di sini menggunakan pendekatan jalur fungsional (*functional pipeline*) untuk mengubah nilai mentah game secara dinamis.
* **Penerapan**: Jalur komputasi kerusakan (*damage*) dasar berjalan melalui perulangan dari kumpulan ekstensi polimorfik yang aktif:
    ```cpp
    int damage = playerTotal;
    for(Perk* p : perks)
        damage = p->modifyDamage(damage);
    ```
* **Keuntungan**: Memungkinkan efek modifikasi menumpuk secara berurutan. Sebagai contoh, peningkatan flat tambahan (`FlatDamagePlus5`) dan pengganda persentase (`Bonus21Damage`) dapat ditumpuk pada saat *runtime* tanpa mengubah logika inti dari kalkulasi *damage*.

---

# Modification Log

### 1. Perbaikan Kebocoran Memori (Memory Leak) pada Status Batalkan Belanja
* **Masalah**: Fungsi `Shop::openShop` membuat dua pointer mentah (*raw pointers*) (`preview1`, `preview2`) melalui factory untuk mengambil data nama perk yang akan ditampilkan. Jika pemain memilih opsi `1`, `preview2` mengalami kebocoran memori; jika pemain melewati belanja (*skip*), kedua objek tersebut bocor di dalam *system heap*.
* **Solusi**: Menambahkan pembersihan eksplisit (`delete preview1;`, `delete preview2;`) di semua jalur kondisi (*conditional paths*) yang saling eksklusif di dalam fungsi `Shop::openShop`.

### 2. Polymorphic Destructor Safeguard
* **Masalah**: Kelas dasar `Perk` tidak memiliki destruktor virtual yang terdefinisi. Ketika pembersihan kontainer dilakukan di dalam fungsi `RunSession::run()` melalui perintah `delete p;`, hal ini memicu *undefined behavior* karena melewati proses pembersihan pada sub-kelas konkretnya.
* **Solusi**: Mendeklarasikan fungsi jangkar virtual fallback `virtual ~Perk() {}` di dalam struktur antarmuka (*interface*) dasar `Perk`.

### 3. Dynamic Dealer HP Scaler
* **Masalah**: Pada iterasi awal, tidak ada progres babak yang membuat tingkat kesulitan di akhir game menjadi stagnan.
* **Solusi**: Mengubah algoritma dasar tingkat kesulitan agar otomatis meningkatkan HP musuh secara bertahap di setiap babak yang berhasil dilewati: `int dealerHP = 12 + round * 5;`.

---

# AI Usage Disclosure

### Integrasi Alat
Kecerdasan Buatan (AI) membantu dalam meninjau struktur tata letak kode, mengidentifikasi kerentanan struktural abstrak (seperti destruktor virtual yang hilang), dan melacak jalur alokasi heap untuk menghilangkan pointer yang tidak bersih (*stray pointers*) di dalam mekanik toko game.

### Detail Pembuatan
* **Refaktorisasi**: Mengoptimalkan manajemen heap di dalam cabang kondisi pada file `shop.cpp` untuk mencegah penurunan performa memori pada saat game berjalan (*runtime memory degradation*).
* **Penyusunan Dokumentasi**: Pemisahan kode (*code parsing*) dan penyelarasan struktural dalam ikhtisar teknis ini disusun menggunakan jalur pemrosesan otomatis untuk menyelaraskan implementasi kode dengan deskripsi desain perangkat lunak yang bersih.