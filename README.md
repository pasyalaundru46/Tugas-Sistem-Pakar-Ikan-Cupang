# Sistem Pakar Identifikasi Kemungkinan Penyakit pada Ikan Cupang

## Deskripsi
Program C++ ini membantu melakukan identifikasi awal kemungkinan gangguan kesehatan ikan cupang berdasarkan gejala yang dimasukkan pengguna. Basis pengetahuan disimpan dalam file JSON terpisah dan diproses menggunakan metode Forward Chaining.

## Struktur file
- `main.cpp`: mesin inferensi dan kode untuk membaca JSON.
- `aturan_ikan_cupang.json`: daftar pertanyaan, fakta, aturan IF-THEN, dan kesimpulan.

## Kebutuhan
- Compiler C++ yang mendukung C++17.
- Library `nlohmann/json`.

### Instalasi di Ubuntu
```bash
sudo apt update
sudo apt install g++ nlohmann-json3-dev
```

### Kompilasi
Jalankan dari direktori yang berisi kedua file:
```bash
g++ -std=c++17 main.cpp -o sistem_pakar
```

### Menjalankan
```bash
./sistem_pakar
```

Pastikan `aturan_ikan_cupang.json` berada di direktori kerja yang sama ketika program dijalankan.

## Cara C++ mengakses JSON
1. `#include <nlohmann/json.hpp>` menyertakan library JSON.
2. `ifstream file("aturan_ikan_cupang.json")` membuka file JSON.
3. `file >> basisPengetahuan` membaca dan mengurai JSON menjadi objek.
4. `basisPengetahuan.at("gejala")` mengambil daftar pertanyaan.
5. `basisPengetahuan.at("aturan")` mengambil aturan IF-THEN.
6. `aturan.at("jika")` membaca kondisi, sedangkan `aturan.at("maka")` membaca hasil aturan.

## Ringkasan aturan
| ID | Kondisi IF | Hasil THEN |
|---|---|---|
| R1 | Sirip robek atau berjumbai | Fakta antara: sirip rusak |
| R2 | Sirip rusak DAN pangkal sirip merah/menghitam | Dugaan Fin Rot |
| R3 | Bintik putih DAN menggesekkan tubuh | Dugaan White Spot (Ich) |
| R4 | Mata menonjol | Dugaan Pop-Eye |
| R5 | Bercak keemasan DAN menggesekkan tubuh | Dugaan Velvet |
| R6 | Tubuh membengkak DAN sisik terangkat | Dugaan Dropsy |
| R7 | Ikan lesu DAN nafsu makan menurun | Indikasi gangguan kesehatan |

## Cara kerja Forward Chaining
Program mulai dari fakta awal yang berasal dari jawaban pengguna. Kemudian setiap aturan diperiksa. Jika seluruh kondisi AND atau minimal satu kondisi OR terpenuhi, fakta hasil aturan dimasukkan ke memori. Pemeriksaan diulang sampai tidak ada fakta baru. R1 menghasilkan fakta antara `sirip_rusak`, yang dapat digunakan oleh R2.

## Skenario pengujian
1. **Fin Rot**: jawab Ya untuk sirip robek dan pangkal sirip merah/menghitam. Hasil yang diharapkan: fakta sirip rusak dan dugaan Fin Rot.
2. **White Spot**: jawab Ya untuk bintik putih dan ikan sering menggesekkan tubuh. Hasil yang diharapkan: dugaan White Spot (Ich).
3. **Tanpa kesimpulan**: jawab Ya hanya untuk ikan lesu dan Tidak untuk gejala lainnya. Hasil yang diharapkan: tidak ada kesimpulan dari aturan yang tersedia.

## Batasan
Hasil sistem hanya merupakan dugaan awal berdasarkan gejala yang dipilih. Gejala dapat tumpang tindih dan program tidak menggantikan pemeriksaan dokter hewan atau ahli kesehatan ikan.
