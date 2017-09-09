# Sensor Kecepatan Kendaraan Sederhana
## Modul yang Digunakan
1. Arduino Uno
2. Sensor Doppler HB100
3. Modul RTC DS1302
4. Modul SD Card
5. Lampu LED
6. Shutter Camera Bluetooth (modified)
7. Action Cam Xiaomi Yi
## Cara Kerja
1. Sensor Doppler HB100 membaca kecepatan kendaraan yang lewat.
2. Jika kecepatan kendaraan melebihi batas ketentuan, maka shutter kamera akan ter-trigger dan mengambil gambar kendaraan. Selain itu, lampu LED akan menyala menandakan ada kendaraan yang melebihi batas kecepatan.
3. Batas kecepatan kendaraan di set sebesar 5 km/h hingga 100 km/h. Diatas itu akan mentrigger shutter kamera. 
4. Modul SD Card berfungsi sebagai data logger untuk menyimpan data sensor dan kecepatan kendaraan setiap detik. Kecepatan kendaraan dibawah 5 km/h diabaikan karena dianggap sebagai noise.
5. Modul RTC DS1302 berfungsi sebagai timestamp pada data logger.
## Hasil Percobaan
Menurut hasil percobaan, alat ini memiliki keakuratan pembacaan hingga kurang lebih 5 km/h. Hasil akan lebih baik jika alat dipasang pada jalanan yang lengang.

- Referensi : [epanorama.net](http://www.epanorama.net/newepa/2017/05/02/hb100-microwave-radar-to-arduino/)
