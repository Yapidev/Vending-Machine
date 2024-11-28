#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LENGTH 500

// Struktur untuk menyimpan informasi produk
typedef struct {
    int kode;
    const char *nama;
    int harga;
} Produk;

// Daftar produk yang tersedia
Produk daftarProduk[] = {
    {101, "Aquah", 4000},
    {102, "Teh Pucuk", 5000},
    {103, "Mizon", 9000},
    {201, "Ciki Ciki", 4000},
    {202, "Doritos", 5000},
    {203, "Chisato", 8000}
};
int jumlahProduk = sizeof(daftarProduk) / sizeof(daftarProduk[0]);

// Fungsi untuk mendapatkan pointer produk berdasarkan kode
Produk* pilihProduk(int kode) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].kode == kode) {
            return &daftarProduk[i];
        }
    }
    return NULL; // Produk tidak ditemukan
}

// Fungsi untuk menampilkan menu produk
void tampilkanMenu() {
    printf("+------------------------------------------+\n");
    printf("|           VENDING MACHINE CERIA          |\n");
    printf("+------------------------------------------+\n");
    for (int i = 0; i < jumlahProduk; i++) {
        printf("| %-11s | (Rp %d) | (Kode: %d)    |\n", daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].kode);
    }
    printf("+------------------------------------------+\n");
}

// Fungsi untuk menangani pembayaran tunai
void pembayaranTunai(int harga, int *kembalian) {
    int uang;
    do {
        printf("Masukkan uang Anda: ");
        scanf("%d", &uang);

        if (uang < harga) {
            printf("Uang tidak cukup. Harga produk adalah Rp%d.\n", harga);
        } 

    } while (uang < harga);

    *kembalian = uang - harga;
    if (*kembalian == 0) {
        printf("Uang pas. Terima kasih telah berbelanja!\n");
    } else {
        printf("Terima kasih telah berbelanja! Kembalian Anda: Rp%d\n", *kembalian);
    }
}

// Fungsi untuk menangani pembayaran QRIS
void pembayaranQRIS(int harga, int *kembalian) {
    int uang;
    printf("\n=============== QRIS Payment ===============\n");
    printf("|                                          |\n");
    printf("|      ##############################      |\n");
    printf("|      ##                          ##      |\n");
    printf("|      ##  ##  ####  ##  ##  ####  ##      |\n");
    printf("|      ##  ##    ##  ##  ##    ######      |\n");
    printf("|      ##  ####  ##  ######  ####  ##      |\n");
    printf("|      ##    ##  ##    ##    ##    ##      |\n");
    printf("|      ##############################      |\n");
    printf("|      ##  ##  ##      ######  ##  ##      |\n");
    printf("|      ##      ######    ##      ####      |\n");
    printf("|      ##  ##  ##  ##    ##    ##   #      |\n");
    printf("|      ##  ######  ######  ######  ##      |\n");
    printf("|      ##      ##  ##  ##   ## ######      |\n");
    printf("|      ##############################      |\n");
    printf("|                                          |\n");
    printf("============================================\n");
    printf("|    Scan kode ini menggunakan aplikasi    |\n");
    printf("|     pembayaran QRIS untuk melanjutkan    |\n");
    printf("============================================\n\n");
    
    printf("Silakan lakukan pembayaran sebesar Rp%d dengan QRIS.\n", harga);

    do {
        printf("Masukkan uang Anda: ");
        scanf("%d", &uang);

        if (uang < harga) {
            printf("Uang tidak cukup. Harga produk adalah Rp%d.\n", harga);
        }

    } while (uang < harga);

    *kembalian = uang - harga;
    if (*kembalian == 0) {
        printf("Uang pas. Terima kasih telah berbelanja!\n");
    } else {
        printf("Terima kasih telah berbelanja! Kembalian Anda: Rp%d\n", *kembalian);
    }
}

// Fungsi untuk mencatat rekap pembelian ke dalam file teks
void rekapPembelian(const char *namaProduk, int kode, int harga, int metode, const char *status, int kembalian) {
    FILE *file = fopen("rekap_pembelian.txt", "a");
    
    if (file == NULL) {
        printf("Gagal membuka file untuk rekap pembelian.\n");
        return;
    }

    // Dapatkan tanggal dan waktu saat ini
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char tanggal[20];
    strftime(tanggal, sizeof(tanggal), "%Y-%m-%d %H:%M:%S", tm_info);

    // Tulis rekap pembelian ke dalam file
    fprintf(file, "Tanggal: %s\n", tanggal);
    fprintf(file, "Nama Produk: %s\n", namaProduk);
    fprintf(file, "Kode Produk: %d\n", kode);
    fprintf(file, "Harga: Rp%d\n", harga);
    fprintf(file, "Metode Pembayaran: %s\n", 
        (metode == 1) ? "Tunai" : 
        (metode == 2) ? "QRIS" : 
        "Invalid");
    fprintf(file, "Status Transaksi: %s\n", status);
    if (kembalian > 0) {
        fprintf(file, "Kembalian: Rp%d\n", kembalian);
    }
    fprintf(file, "------------------------------------------\n");

    fclose(file);
}

// Fungsi untuk print Analisis Program
void analisisProgram() {
    printf("\n========== ANALISIS PROGRAM ==========\n");

    printf("\nTUJUAN PROGRAM:\n");

    printf("Program ini adalah simulasi vending machine digital dengan fitur:\n");
    printf("1. Melihat daftar produk yang tersedia.\n");
    printf("2. Memilih produk berdasarkan kode.\n");
    printf("3. Melakukan pembayaran (Tunai/QRIS).\n");
    printf("4. Mencatat transaksi ke dalam file teks.\n");
    printf("5. Memberikan kembalian jika ada.\n");
    printf("6. Mendukung pembatalan transaksi.\n\n");

    printf("STRUKTUR DATA:\n");
    printf("- Struktur Produk menyimpan kode, nama, dan harga produk.\n");
    printf("- Array daftarProduk menyimpan semua produk yang tersedia.\n\n");

    printf("FUNGSI UTAMA:\n");
    printf("1. pilihProduk(kode):\n");
    printf("   - Menemukan produk berdasarkan kode.\n");
    printf("   - Mengembalikan pointer ke produk jika ditemukan.\n");
    printf("\n2. tampilkanMenu():\n");
    printf("   - Menampilkan daftar produk dalam format tabel.\n");
    printf("\n3. pembayaranTunai(harga, *kembalian):\n");
    printf("   - Mengatur pembayaran tunai, memvalidasi jumlah uang, dan menghitung kembalian.\n");
    printf("\n4. pembayaranQRIS(harga, *kembalian):\n");
    printf("   - Mensimulasikan pembayaran QRIS, memvalidasi jumlah uang, dan menghitung kembalian.\n");
    printf("\n5. rekapPembelian(...):\n");
    printf("   - Mencatat transaksi ke dalam file rekap_pembelian.txt, termasuk waktu transaksi.\n");
    printf("\n6. main():\n");
    printf("   - Mengatur alur utama program, termasuk memilih produk, metode pembayaran, dan pembelian berulang.\n\n");

    printf("KEUNGGULAN:\n");
    printf("1. Modular: Fungsi-fungsi terpisah mempermudah pemeliharaan.\n");
    printf("2. Fleksibilitas: Mendukung pembayaran tunai dan QRIS.\n");
    printf("3. Rekap Transaksi: Setiap transaksi tercatat dalam file untuk referensi.\n");

    printf("\nPOTENSI PENINGKATAN:\n");
    printf("1. Validasi input non-numerik pada kode produk dan jumlah uang.\n");
    printf("2. Menambahkan laporan ringkasan pembelian setelah program selesai.\n");
    printf("3. Penanganan error jika file rekap gagal dibuka.\n");
    printf("======================================\n");
}

// Fungsi untuk mengonversi string tanggal ke struktur tm
struct tm string_to_date(const char *date_str) {
    struct tm tm_date = {0};
    
    // Menggunakan sscanf untuk mengekstrak tanggal dan waktu
    sscanf(date_str, "%d-%d-%d %d:%d:%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday,
    &tm_date.tm_hour, &tm_date.tm_min, &tm_date.tm_sec);

    tm_date.tm_year -= 1900; // Menyesuaikan tahun (tm_year adalah tahun sejak 1900)
    tm_date.tm_mon -= 1; // Menyesuaikan bulan (tm_mon dimulai dari 0)
    return tm_date;
}

int is_this_week(struct tm date) {
    time_t t = time(NULL);
    struct tm now = *localtime(&t); // Mengambil waktu saat ini

    struct tm tm_trans = date; // Waktu transaksi

    // Pastikan hari dalam minggu dihitung dengan benar
    mktime(&tm_trans);  // Menghitung kembali nilai tm_wday dan field lainnya

    // Menghitung waktu dalam bentuk time_t untuk sekarang dan transaksi
    time_t time1 = mktime(&now); // Konversi waktu sekarang ke time_t
    time_t time2 = mktime(&tm_trans); // Konversi waktu transaksi ke time_t

    // Menghitung perbedaan waktu dalam detik
    double diff = difftime(time1, time2);
    double seconds_in_a_week = 7 * 24 * 60 * 60;

    // Membandingkan apakah perbedaan waktu dalam seminggu terakhir
    if (diff <= seconds_in_a_week) {
        return 1; // Jika dalam minggu yang sama
    } else {
        return 0; // Jika tidak dalam minggu yang sama
    }
}

int is_this_month(struct tm date) {
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    return now.tm_year == date.tm_year && now.tm_mon == date.tm_mon;
}

int is_this_year(struct tm date) {
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    return now.tm_year == date.tm_year;
}

// Fungsi utama program
int main() {
    int kode, metode, kembalian = 0;
    char beliLagi;
    Produk *produk;

    do {
        tampilkanMenu();

        printf("Masukkan kode produk yang ingin dibeli (atau 0 untuk batal): ");
        scanf("%d", &kode);
        if (kode == 0) {
            rekapPembelian("Tidak ada", kode, 0, 0, "Batal", 0);
            printf("Pembelian dibatalkan.\n");
            break;
        }

        produk = pilihProduk(kode);
        if (produk == NULL) {
            rekapPembelian("Tidak valid", kode, 0, 0, "Batal", 0);
            printf("Kode yang dimasukkan tidak valid!\n\n");
            continue;
        }

        printf("\nPilih metode pembayaran:\n");
        printf("1. Tunai\n");
        printf("2. QRIS\n");
        printf("3. Kembali ke menu awal\n");
        printf("Masukkan pilihan (1/2/3): ");
        scanf("%d", &metode);

        if (metode == 1) {
            pembayaranTunai(produk->harga, &kembalian);
            rekapPembelian(produk->nama, produk->kode, produk->harga, metode, "Sukses", kembalian);
        } else if (metode == 2) {
            pembayaranQRIS(produk->harga, &kembalian);
            rekapPembelian(produk->nama, produk->kode, produk->harga, metode, "Sukses", kembalian);
        } else if (metode == 3) {
            rekapPembelian(produk->nama, produk->kode, produk->harga, metode, "Batal", 0);
            continue;
        } else {
            printf("Metode pembayaran tidak valid!\n");
        }

        printf("\nApakah Anda ingin membeli lagi? (y/n): ");
        scanf(" %c", &beliLagi);

    } while (beliLagi == 'y' || beliLagi == 'Y');

    printf("\nTerima kasih! Sampai jumpa lagi!\n");

    analisisProgram();

    FILE *file = fopen("rekap_pembelian.txt", "r");
    if (file == NULL) {
        perror("File tidak ditemukan");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    double total_week = 0, total_month = 0, total_year = 0;
    while (fgets(line, sizeof(line), file)) {
        char date_str[20], product_name[50], payment_method[20], status[20];
        int product_code, price, change;
        struct tm transaction_date;

        // Membaca data baris per baris
        if (sscanf(line, "Tanggal: %19[^\n]", date_str)) {
            // Convert tanggal ke struct tm
            transaction_date = string_to_date(date_str);
        }
        fgets(line, sizeof(line), file); // Nama Produk
        fgets(line, sizeof(line), file); // Kode Produk
        fgets(line, sizeof(line), file); // Harga
        sscanf(line, "Harga: Rp%d", &price);
        fgets(line, sizeof(line), file); // Metode Pembayaran
        fgets(line, sizeof(line), file); // Status Transaksi
        fgets(line, sizeof(line), file); // Kembalian
        sscanf(line, "Kembalian: Rp%d", &change);
        
        // Memeriksa apakah transaksi minggu ini, bulan ini, atau tahun ini
        if (is_this_week(transaction_date)) {
            total_week += price;
        }
        if (is_this_month(transaction_date)) {
            total_month += price;
        }
        if (is_this_year(transaction_date)) {
            total_year += price;
        }

        // Membaca separator baris
        fgets(line, sizeof(line), file);
    }

    fclose(file);

    // Output total pembelian
    printf("====== PEMBELIAN MINGGU INI ======\n");
    printf("Total pembelian: Rp%.0f\n\n", total_week);

    printf("====== PEMBELIAN BULAN INI ======\n");
    printf("Total pembelian: Rp%.0f\n\n", total_month);

    printf("====== PEMBELIAN TAHUN INI ======\n");
    printf("Total pembelian: Rp%.0f\n", total_year);

    return 0;
}
