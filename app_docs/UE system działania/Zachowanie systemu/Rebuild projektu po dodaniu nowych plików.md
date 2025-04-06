System z jakiegoś powodu w momencie dodawania nowych stanów o nowej sygnaturze (nowa nazwa klasy) NIE CHCE SIĘ KOMPILOWAĆ XD. Żeby temu zaradzić należy wywalić wszystkie pliki która powstają w trakcie builda i od nowa zbudować cały projekt. Ja usunąłem następujące pliki aby build poszedł (wszystko będzie z folder UE):
- Application/CMakeFiles
- Application/cmake_install.cmake
- Application/libUeApplication.a
- Application/Makefile
Być może usunąłem jeszcze jakieś pliki ale ciężko to stwierdzić bo nie pamiętam już dokładnie.

