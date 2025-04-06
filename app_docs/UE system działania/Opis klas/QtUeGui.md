Klasa służąca do obsługiwania komponentów Qt. W domyśle ta klasa nie powinna być modyfikowana ale może się tak zdarzyć że będzie trzeba się bawić z dodawaniem nowych rzeczy bo czegoś brakuje. 

Qt opiera się na metodach SIGNAL oraz SLOT ( jakieś macro ). Rzeczy te są zdefiniowane w pliku QtUeGui w metodzie initInternalSignals.

```cpp
void QtUeGui::initInternalSignals()  
{  
    QObject::connect(&acceptButton,SIGNAL(clicked()),this, SLOT(onAcceptClicked()));  
    QObject::connect(&rejectButton,SIGNAL(clicked()),this, SLOT(onRejectClicked()));  
    QObject::connect(&homeButton,SIGNAL(clicked()),this,SLOT(onHomeClicked()));  
  
    QObject::connect(&listViewMode,SIGNAL(itemDoubleClicked()),this,SLOT(onItemSelected()));  
    QObject::connect(&callMode,SIGNAL(textEntered()),this,SLOT(onTextEntered()));  
  
    QObject::connect(this,SIGNAL(setConnectedStateSignal(QString, bool)),this,SLOT(setConnectedStateSlot(QString, bool)));  
    QObject::connect(this,SIGNAL(setNewMessageSignal(bool)),this,SLOT(setNewMessageSlot(bool)));  
}
```
Rejestruje on kolejno:
- callback dla przycisku zielonej słuchawki, zdarzenie: pojedyncze wciśnięcie 
- callback dla przycisku czerwonej słuchawki, zdarzenie: pojedyncze wciśnięcie
- callback dla przycisku home, zdarzenie: pojedyncze wciśnięcie
- callback dla elementu na liście (compose SMS, view SMS), zdarzenie: podwójne wciśnięcie
- callback dla czegoś związanego z trybem dzwonienia (sorry nie wiem co to jest xddd)
- callback dla klasy QtUeGui, zdarzenie: aplikacja przeszła w stan ConnectedState
- callback dla klasy QtUiGui, zdarzenie: BTS wysłał wiadomość do telefonu

Funkcja QtObject::connect jest metodą, która rejestruje wszystkie sygnały, które aplikacja wysyła. Aby było prościej to będę się posługiwał dla porównania systemem z js do rejestracji zdarzeń (bo opiera się to na prawie tym samym). 
1. Pierwszy argument do jakiego obiektu mamy przypisać zdarzenie.
2. Drugi argument to jakie zdarzenie ma się zdarzyć aby handler/callback miał się wykonać
3. Trzeci argument to context, do czego ma dostęp metoda jeżeli chodzi o klasę (w js byłoby to obiekt na który wskazuje słówko this)
4. Czwarty argument to handler/callback

Metoda ta ma polimorficzne wywołanie więc czasem zamiast 4 argumentów mogą być 3 argumenty.
Więcej na ten temat można poczytać tutaj: 
https://doc.qt.io/qt-6/signalsandslots.html#signals-and-slots-with-default-arguments


```js
//Obiekt na rzecz którego mamy wywołanie pkt 1
const button = document.querySelector(".myBtn");

// addEventListener == QtObject::connect
button.addEventListener(/** Zdarzenie które mamy nasłuchiwać pkt 2 */ "click",
/** Handler pkt 4 */
function(){
	console.log(
	/** Obiekt this jest kontekstem funkcji pkt 3*/
	this.innerText
	)
})
```
