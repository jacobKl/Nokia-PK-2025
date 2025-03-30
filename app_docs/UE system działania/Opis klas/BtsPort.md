Zawiera referencje do logger, trasportera oraz numeru telefonu.

Klasa BtsPort służy do komunikacji z BTS. W skrócie, chcesz wysłać wiadomość do BTS? To jest miejsce gdzie chcesz dodać nową metodę aby wykonać tą akcję.

Plik IBtsPort posiada w sobie 2 klasy, IBtsEventsHandler oraz IBtsPort, pierwszy służy do obsługi zdarzeń w aplikacji a drugi służy do tworzenia nowych akcji które użytkownik może wywołać. Dlatego też dla przykładu w pliku BtsPort.cpp jest funkcja handleMessage, która w zależności od tego jaką wiadomość przyjmie (w tym wypadku nie odnosi się to do wiadomości SMS tylko o informacja o akcji która została wykonana) wywołuje różne funkcje handlerów które są zależne od contextu. W pierwszej implementacji od Nokii mamy dostęp do 2 przykładowych handlerów:
- common::MessageId::Sib
- common::MessageId::AttachResponse

Wszystkie typy wiadomości jakie będą w aplikacji są w folderze COMMON.
