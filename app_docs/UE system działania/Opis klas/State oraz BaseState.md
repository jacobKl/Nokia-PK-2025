Klasy w których wywoływane są customowe akcje zdefiniowane przez nas.

Każdy stan musi dziedziczyć po klasie BaseState. Następnie każdy stan ustawia pewne akcje dla pewnych guzików w telefonie, bądź też funkcje callbackowe dla różnych sytuacji które się zdarzą w aplikacji. Dzięki temu podejściu możemy dodawać nowe funkcjonalności które są niezależne od pozostałych, oraz ich nie zmieniać. 

Ponieważ stany posiadają różne akcje, które mogą wykonać BaseState musi posiadać każdą metodę w sobie, a później klasy pochodne nadpisują sobie interesujące je metody. Musi to wyglądać w taki sposób ponieważ w przeciwnym przypadku cpp by miało problem z odwołaniem się do danej metody (np. connectedState nie będzie potrzebowało metody handleSendCallTalk ale wciąż chcemy mieć informację że taka metoda istnieje ponieważ stany aplikacji są dynamiczne, a jakiś stan może taką akcję implementować).

Flow dodawania nowego handlera wygląda jak w wykresie który jest dołączony poniżej:
[[Flow dodawania nowego handlera.canvas|Flow dodawania nowego handlera]]
