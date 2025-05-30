## **Postür Düzeltici Cihaz – STM32F407 & MPU6050 Projesi**

Bu proje, kötü duruş alışkanlıklarını düzeltmeye yardımcı olmak amacıyla geliştirilen bir **postür takip ve uyarı sistemidir**. Sistem, kullanıcının eğik duruşunu MPU6050 ivmeölçer sensörü ile algılar ve belirlenen açı limitlerinin aşılması durumunda **titreşim motorunu** çalıştırarak kullanıcıyı uyarır.

---

## 💪 Kullanılan Donanım

* **STM32F407VG** geliştirme kartı
* **MPU6050** (ivmeölçer + jiroskop modülü)
* **Titreşim motoru**
* **Breadboard** ve bağlantı kabloları
* **Güç kaynağı veya batarya**

---

## ⚙️ Sistem Mimarisi

1. **MPU6050**, duruş verilerini (ivmeölçer kullanarak) I2C üzerinden STM32'ye gönderir.
2. STM32, x ve y eksenlerindeki açıları hesaplar.
3. Bu açılardan herhangi biri 30°’yi geçerse, **titreşim motoru aktif hale gelir**.
4. Kullanıcı postürünü düzeltince motor otomatik olarak kapanır.

---

## 🔧 Kurulum ve Kullanım

1. STM32CubeIDE ile yeni bir STM32F4 projesi oluşturun.
2. I2C1 (PB6, PB7) ve PC8 pinlerini aktif edin.
3. `main.c`, `mpu6050.c` ve `mpu6050.h` dosyalarını projeye ekleyin.
4. MPU6050 sensörünü `PB6 (SCL)` ve `PB7 (SDA)` pinlerine bağlayın.
5. Titreşim motorunu `PC8` pinine bağlayın (gerekirse transistör/mosfet ile).
6. Kodu derleyin ve STM32 kartınıza yükleyin.

---

## 🧠 Algoritma Açıklaması

Sensörden gelen ivme verileriyle açı hesaplaması yapılır:

```c
float ax = mpu_data.Accel_X / 16384.0;
float angle_x = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / 3.141592;
```

* `angle_x` veya `angle_y` 30° sınırını aşarsa, `PC8` pini aktif olur ve titreşim motoru çalışır.
* 300 ms aralıklarla ölçüm tekrarlanır.

---

## 📷 Ekran Görüntüsü / Donanım Kurulumu

---

## 📈 Geliştirmenin Amacı

Bu sistem, uzun süre masa başında oturan kişiler için **anlık postür düzeltme** amacıyla geliştirilmiştir. Duruş bozukluklarına bağlı oluşabilecek omurga sorunlarını önlemeye yardımcı olur.

---
