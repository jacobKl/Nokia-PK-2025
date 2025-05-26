# NOKIA-PK

## Repozytorium grupy 14 KS

### Zespół

- Mateusz Fudala
- Marcin Fortuna
- Hubert Chruścicki
- Mikołaj Munik
- Jakub Klimek

## Tablica z zadaniami

[Github Projects](https://github.com/users/jacobKl/projects/1)

## Build projektu

Przejdź do folderu src i odpal komendy

```
cmake .
cmake --build . --target {UE, UeApplicationUT, all}
```

Z katalogu src odpalamy tą komendę jeśli UE nie chce się zbuildować:
```
find UE \
-depth \
\( -type d -name 'CMakeFiles' \
-o -type f -name 'cmake_install.cmake' \
-o -type f -name 'libUeApplication.a' \
-o -type f -name 'Makefile' \
\) \
-exec rm -rf {} +
```

Na samym początku najlepiej uruchomić z --target all.

## Uruchomienie aplikacji

W folderze UE

```
./UE phone={numer_telefonu}
```

Numer telefonu jest opcjonalny
