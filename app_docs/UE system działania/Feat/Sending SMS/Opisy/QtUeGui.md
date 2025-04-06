Aby pozwolić użytkownikowi na wybranie elementu z listy w momencie jak na nią wchodzi został dodany nowy typ eventu dla listy: doubleClickCallback.

Jest to callback który będzie się wywoływał w momencie jak zrobi się double click na element listy.

Przez to w QtUeGui zostały dodane następujące rzeczy:
- onDoubleClicked - funkcja która wywoła nasz callback
- setDoubleClickCallback - funkcja która pozwala na ustawienie funkcji callbackowej

Dodatkowo dodano też opcję zmieniania callback'u dla przycisku home. 


