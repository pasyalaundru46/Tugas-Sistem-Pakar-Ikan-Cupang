# SISTEM PAKAR IDENTIFIKASI MASALAH KESEHATAN IKAN CUPANG

## **1. Nama dan NIM**

- **Nama:** [Muhammad Abdiel Pasya Laundru]
- **NIM:** [F1D02510080]
- **Program Studi:** Teknik Informatika

## **2. Topik dan Cara Menjalankan Program**

### Topik Program

Program ini merupakan sistem pakar sederhana untuk mengidentifikasi kemungkinan masalah kesehatan pada ikan cupang berdasarkan gejala yang dialami. Sistem dibuat menggunakan bahasa pemrograman C++ dengan metode Forward Chaining.

Program bekerja dengan mengumpulkan gejala dari pengguna, mencocokkannya dengan aturan yang terdapat dalam basis pengetahuan, kemudian menghasilkan kesimpulan berdasarkan aturan yang terpenuhi.

### Bahasa dan Versi

- **Bahasa Pemrograman:** C++
- **Standar:** C++11 atau lebih baru
- **Compiler:** GCC / MinGW
- **Library:** C++ Standard Library

### Library yang Digunakan

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
```

### Cara Menjalankan Program

**Kompilasi menggunakan GCC:**

```bash
g++ main.cpp -o sistem_pakar
```

**Menjalankan program pada Linux:**

```bash
./sistem_pakar
```

**Menjalankan program pada Windows:**

```bash
sistem_pakar.exe
```

Program tidak memerlukan file JSON maupun library eksternal karena basis pengetahuan telah dimasukkan langsung ke dalam kode C++.

## **3. Daftar Sumber dan Tabel Aturan**

### Daftar Sumber

**S1**
- Judul: Bacterial Identification of Ornamental Betta Fish (Betta splendens)
- Penerbit: University of Florida IFAS Extension
- URL: [https://jurnal.usk.ac.id/JMV/article/view/29323/0]
- Tanggal akses: [11 November 2026]

**S2**
- Judul: Ornamental Fish Health Management
- Penerbit: Journal of Aquatic Animal Health
- URL: [https://ph02.tci-thaijo.org/index.php/tsujournal/article/view/257870]
- Tanggal akses: [12 November 2026]

### Tabel Aturan

Basis pengetahuan program terdiri dari lima aturan yang digunakan untuk proses inferensi.

| ID | Kondisi (IF) | Operator | Kesimpulan (THEN) |
|---|---|---|---|
| R1 | Sirip robek atau koyak; tepi sirip menghitam | OR | Indikasi infeksi bakteri |
| R2 | Indikasi infeksi bakteri; suhu air terlalu dingin atau kotor | AND | Sirip busuk (Fin Rot) |
| R3 | Tubuh membengkak seperti buah pinus; sisik berdiri | AND | Penyakit Dropsy |
| R4 | Muncul bintik putih seperti garam di tubuh; ikan sering bergesekan dengan dekorasi | AND | Penyakit Ich (White Spot) |
| R5 | Ikan pasif di dasar akuarium; warna tubuh memudar | OR | Stres lingkungan |

Keterangan:
- **AND:** Seluruh kondisi dalam aturan harus terpenuhi.
- **OR:** Minimal satu kondisi dalam aturan harus terpenuhi.

## **4. Metode yang Dipilih dan Alasannya**

### Metode Forward Chaining

Metode yang digunakan dalam program ini adalah **Forward Chaining (FC)**. Forward Chaining merupakan metode penalaran yang dimulai dari fakta awal, kemudian mencocokkan fakta tersebut dengan aturan yang tersedia untuk memperoleh kesimpulan.

Metode ini dipilih karena proses identifikasi dimulai dari gejala yang dimasukkan oleh pengguna. Gejala tersebut menjadi fakta awal yang digunakan sistem untuk menghasilkan kesimpulan secara bertahap.

### Tahapan Proses

**1. Input Fakta**

Pengguna menjawab pertanyaan mengenai gejala yang dialami ikan cupang. Jawaban positif akan disimpan sebagai fakta awal.

**2. Pencocokan Aturan**

Sistem memeriksa setiap aturan dalam basis pengetahuan dan mencocokkan kondisi aturan dengan fakta yang tersedia.

**3. Proses Inferensi**

Jika kondisi aturan terpenuhi, sistem menghasilkan fakta baru berdasarkan bagian THEN dari aturan tersebut.

**4. Penambahan Fakta Baru**

Kesimpulan yang diperoleh dimasukkan ke dalam memori fakta sehingga dapat digunakan untuk memeriksa aturan berikutnya.

**5. Pengulangan**

Proses pencocokan aturan dilakukan kembali sampai tidak ditemukan aturan baru yang dapat dijalankan.

**6. Hasil Identifikasi**

Sistem menampilkan kesimpulan dan jejak aturan yang berhasil dijalankan.

### Contoh Perhitungan Forward Chaining

Misalnya, pengguna memberikan fakta awal:

- F1 = Sirip robek atau koyak
- F2 = Suhu air terlalu dingin atau kotor

Proses inferensi:

**Aturan R1:**

IF sirip robek atau koyak OR tepi sirip menghitam

THEN indikasi infeksi bakteri

Karena F1 terpenuhi, maka:

F1 → Indikasi infeksi bakteri

**Aturan R2:**

IF indikasi infeksi bakteri AND suhu air terlalu dingin atau kotor

THEN sirip busuk (Fin Rot)

Karena indikasi infeksi bakteri telah diperoleh dari R1 dan F2 merupakan fakta awal, maka:

Indikasi infeksi bakteri AND F2 → Sirip busuk (Fin Rot)

**Kesimpulan:**

Sistem menghasilkan kesimpulan berupa kemungkinan masalah kesehatan ikan cupang, yaitu **Sirip Busuk (Fin Rot)**.

## **5. Tiga Kasus Uji dan Screenshot**

Pengujian dilakukan untuk mengetahui apakah sistem dapat menghasilkan kesimpulan berdasarkan fakta yang dimasukkan pengguna.

### Kasus Uji 1: Stress Lingkungan
Input gejala:
Apakah ikan pasif di dasar aquarium? (y/t) > y
Apakah ikan sering gesekan badan ke dekorasi? (y/t) > t
Apakah muncul bintik putih seperti garam di tubuh? (y/t) > y
Apakah sirip robek atau koyak? (y/t) > t
Apakah sisik berdiri? (y/t) > t
Apakah suhu air terlalu dingin atau kotor? (y/t) > t
Apakah tepi sirip menghitam? (y/t) > t
Apakah tubuh membengkak seperti buah pinus? (y/t) > t
Apakah warna tubuh memudar? (y/t) > t

Hasil yang diharapkan:
- R1 Stress Lingkungan.

Screenshot hasil pengujian:

[Masukkan Screenshot Kasus Uji 1]

### Kasus Uji 2: Infeksi

Input gejala:
Apakah ikan pasif di dasar aquarium? (y/t) > t
Apakah ikan sering gesekan badan ke dekorasi? (y/t) > t
Apakah muncul bintik putih seperti garam di tubuh? (y/t) > t
Apakah sirip robek atau koyak? (y/t) > y
Apakah sisik berdiri? (y/t) > y
Apakah suhu air terlalu dingin atau kotor? (y/t) > t
Apakah tepi sirip menghitam? (y/t) > t
Apakah tubuh membengkak seperti buah pinus? (y/t) > t
Apakah warna tubuh memudar? (y/t) > t

Hasil yang diharapkan:
- R3 Indikasi Infeksi.

Screenshot hasil pengujian:

[Masukkan Screenshot Kasus Uji 2]

### Kasus Uji 3: Tidak Ditemukan Kesimpulan

Input gejala:
- Seluruh gejala yang ditanyakan = Tidak

Hasil yang diharapkan:
- Tidak ada aturan yang terpenuhi.
- Sistem tidak menghasilkan kesimpulan masalah kesehatan.

Screenshot hasil pengujian:

[Masukkan Screenshot Kasus Uji 3]

## **6. Batas Keberlakuan Sistem**

Sistem pakar ini menggunakan basis pengetahuan yang terdiri dari lima aturan mengenai kemungkinan masalah kesehatan ikan cupang, dengan informasi yang dirujuk dari literatur perawatan ikan hias dan kesehatan ikan. Pengetahuan tersebut digunakan untuk membantu mengidentifikasi kemungkinan masalah berdasarkan gejala yang dimasukkan pengguna. Sistem ini ditujukan sebagai alat bantu identifikasi awal, bukan untuk menggantikan pemeriksaan atau diagnosis dari dokter hewan maupun tenaga profesional di bidang kesehatan ikan. Hasil yang diberikan hanya berupa saran awal sehingga pengguna tetap perlu melakukan pemeriksaan lebih lanjut untuk memastikan kondisi ikan cupang.

**Catatan:** Bagian batas keberlakuan juga perlu ditampilkan pada program C++ agar sesuai dengan ketentuan tugas.

## **7. Penggunaan Alat Bantu AI**

AI digunakan sebagai alat bantu dalam proses penyusunan dokumentasi program, penjelasan metode Forward Chaining, serta penyusunan README. Implementasi dan pengujian program tetap perlu diperiksa dan dipahami oleh pengembang agar sesuai dengan kebutuhan tugas.

