Aby uprościć kolejne dodawanie ekranów powstały typy ekranów. W domyśle są to ekrany które można wybrać z listy na menu głównym.

W Application/Enums/ScreenType.hpp
```cpp
namespace ue{
    enum ScreenType{
        NO_SCREEN = -1,
        COMPOSE_SMS_SCREEN = 0,
        VIEW_SMS_SCREEN = 1
    };
}
```

No_Screen nie powinien nigdy wystąpić w domyśle.
Aby zaimplementować zmianę ekranu należy w connected state zmodyfikować funkcję `changeScreen`. Ta w domyśle zmienia stan, a następnie potem sam state wywołuje odpowiednie metody aby zmiana ekranu nastąpiła.