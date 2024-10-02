#include <stdio.h>

// Fungsi utama program
void main() {
    // Deklarasi variabel untuk kode produk, uang, harga, metode pembayaran, dan opsi beli lagi
    int kode, uang, harga = 0, metode;
    char beliLagi;

    // Mulai menampilkan menu
    do {
        // Opening: Menampilkan menu produk
        printf("+------------------------------------------+\n");
        printf("|           VENDING MACHINE CERIA          |\n");
        printf("+------------------------------------------+\n");
        printf("|    Aquah    |   Teh Pucuk   |    Mizon   |\n");
        printf("|   (Rp 4000) |   (Rp 5000)   |  (Rp 9000) |\n");
        printf("|  (Kode: 101)|  (Kode: 102)  | (Kode: 103)|\n");
        printf("+------------------------------------------+\n");
        printf("|   Ciki Cik  |    Doritos    |  Chisato   |\n");
        printf("|  (Rp 4000)  |   (Rp 5000)   | (Rp 10000) |\n");
        printf("| (Kode: 201) |  (Kode: 202)  | (Kode: 203)|\n");
        printf("+------------------------------------------+\n");

        // Input kode dari pengguna
        printf("Masukkan kode produk yang ingin dibeli: ");
        scanf("%d", &kode);

        // Cek kode yang dimasukkan dan tentukan harga
        switch (kode) {
            case 101:
                printf("Anda memilih Aquah. Harga: Rp4000\n");
                harga = 4000;  // Set harga jika Aquah dipilih
                break;
            case 102:
                printf("Anda memilih Teh Pucuk. Harga: Rp5000\n");
                harga = 5000;  // Set harga jika Teh Pucuk dipilih
                break;
            case 103:
                printf("Anda memilih Mizon. Harga: Rp9000\n");
                harga = 9000;  // Set harga jika Mizon dipilih
                break;
            case 201:
                printf("Anda memilih Ciki Cik. Harga: Rp4000\n");
                harga = 4000;  // Set harga jika Ciki Cik dipilih
                break;
            case 202:
                printf("Anda memilih Doritos. Harga: Rp5000\n");
                harga = 5000;  // Set harga jika Doritos dipilih
                break;
            case 203:
                printf("Anda memilih Chisato. Harga: Rp10000\n");
                harga = 10000; // Set harga jika Chisato dipilih
                break;
            default:
                printf("Kode yang dimasukkan tidak valid!\n");
                break;  // Jika kode tidak valid, keluar dari switch
        }

        // Pilih metode pembayaran
        printf("\nPilih metode pembayaran:\n");
        printf("1. Tunai\n");
        printf("2. QRIS\n");
        printf("Masukkan pilihan (1/2): ");
        scanf("%d", &metode);

        // Pembayaran tunai
        if (metode == 1) {
            do {
                printf("Masukkan uang Anda: ");
                scanf("%d", &uang);

                // Cek apakah uang cukup
                if (uang < harga) {
                    printf("Uang tidak cukup. Anda masih membutuhkan Rp%d lagi.\n", harga - uang);
                }
            } while (uang < harga);  // Ulangi sampai uang cukup
            
            // Proses transaksi tunai
            if (uang == harga) {
                printf("Uang pas. Terima kasih telah berbelanja!\n");
            } else {
                int kembalian = uang - harga; // Hitung kembalian
                printf("Terima kasih telah berbelanja! Kembalian Anda: Rp%d\n", kembalian);
            }
        } 
        // Pembayaran menggunakan QRIS
        else if (metode == 2) {
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

            // Informasi pembayaran QRIS
            printf("Silakan lakukan pembayaran sebesar Rp%d dengan QRIS.\n", harga);
            printf("Terima kasih telah berbelanja!\n");
        } else {
            printf("Metode pembayaran tidak valid.\n");
        }

        // Tanyakan apakah ingin membeli lagi
        printf("\nApakah Anda ingin membeli lagi? (y/n): ");
        scanf(" %c", &beliLagi);

    } while (beliLagi == 'y' || beliLagi == 'Y'); // Ulangi jika pengguna ingin membeli lagi

    // Pesan perpisahan
    printf("Terima kasih! Sampai jumpa lagi!\n");
}
