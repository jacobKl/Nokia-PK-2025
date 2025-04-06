#### Ważne
Transporter = Transport
Używam Transporter bo lepiej brzmi i lepiej oddaje czym ta klasa jest. 

Brama komunikacyjna z aplikacją BTS. Tworzy się automatycznie przy uruchamianiu aplikacji w main.cpp z ApplicationEnvironment.

Jakbym miał to wytłumaczyć na nasze i z tego co rozumiem Transporter jest czymś w rodzaju komunikatora w stylu Database Gateway. Tworzy nakładkę na bezpośrednie połącznie z BTS przez uproszczony interfejs (jedną metodę), dzięki czemu nie musimy przejmować jak to działa pod spodem tylko wysyłamy wiadomość z odpowiednimi danymi i to działa.

Patrząc na interfejs ITransport w pliku ITransport.hpp najważniejszą dla nas metodą jest sendMessage typu BinaryMessage (gdzieś jest to opisane w pliku od Nokii). Dzięki tej metodzie można wysyłać bezpośrednio wiadomość do BTS który później sobie przetwarza dane i daje informacje zwrotne. Są jeszcze jakieś dwie metody ale nie są na ten moment dla nas potrzebne.