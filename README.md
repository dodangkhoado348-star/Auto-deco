# AutoDeco (Geode)

## Build bang GitHub Actions (khuyen dung cho Android/dien thoai)
1. Tao repo GitHub, upload toan bo thu muc nay.
2. Vao tab Actions -> Build Binaries -> Run workflow.
3. Tai artifact "Build Output" -> lay file `.geode`.
4. Chep file `.geode` vao thu muc mods cua Geode tren dien thoai
   (Android/data/com.geode.launcher/files/geode/mods) hoac cai qua Geode launcher.

## Build tren may tinh
```
git clone https://github.com/geode-sdk/cli  # hoac cai geode CLI
geode sdk install
geode sdk install-binaries
geode build
```
(Android: `geode build -p android64` can Android NDK)

## Lenh Git de day len GitHub
```
git init
git add .
git commit -m "init autodeco"
git branch -M main
git remote add origin https://github.com/TEN_BAN/AutoDeco.git
git push -u origin main
```
