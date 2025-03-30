Najważniejsza struktura w całej aplikacji. Context.hpp zawiera w sobie strukturę która jest inicjalizowana w klasie Application. Context zawiera referencje do wszystkich sub komponentów które zostały przekazane w klasie Application tj. logger, IBtsPort, IUserPort oraz ITimerPort. 

Context dodatkowo przechowuje w sobie stan w jakim aplikacja aktualnie się znajduje.

Context może ustawiać swój stan przez funkcję setState, która jest metodą szablonową. W skrócie można przekazać tam dowolną klasę stanu, która dziedziczy po BaseState. 

setState pozwala też na przekazywanie customowych parametrów do stanu. Dzięki temu jeżeli w jednym stanie posiadamy pewną informację i chcemy ją przekazać do innego stanu można użyć setState z DOWOLNĄ ilością argumentów. 

Przykład:
```cpp
context.setState<MyCustomState>("param1", 2, "param3")
```

W trakcie jak zmieniamy stan przy użyciu metody setState(), metoda ta przekazuje też referencję do samej siebie do stanu. Dzięki temu w każdym stanie mamy dostęp do wszystkich klas które zarządzają aplikacją. Więcej zostanie opisane w dokumencie State