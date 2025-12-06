# Zadanie Q. Kapral

Kapral Leon ma najwyraźniej dobry dzień. Spaceruje po placyku w swoich nowych, lśniąco czystych butach.

— Wstawaaaaać! Co to za wylegiwanie się, żołnierzu? Drużyna! W szeregu zbiórka, ale już! A wy? Co się guzdrzecie?! Szeregowy Rózga i Mochnicki do mnie!! Przecież nie będę sobie brudził butów łażąc po błocie! No i jak wy stoicie?!? Znów niższy przed wyższym! Drużyna, **1000** pompek !!

— Ależ kapralu, aż tysiąc?!? - wydukał chuderlawy Kąkol.

— Bez gadania!! Jak nie umiecie stawać w kolejności malejącej to będziecie pompować.

Po porannej zbiórce ledwo żywy Kąkol żali się kolegom:

— Ja nic nie rozumiem. Jak my się w końcu mamy ustawiać? Przecież wczoraj Lulek, stał przed wyższym od siebie Józkiem i nie pompowaliśmy.

— Ciiiiii !!!!!!!!!!!! Ty pacanie!!! - zirytował się Gumiak. - Na jakim Ty świecie żyjesz?!?

Przecież kapral niedowidzi. Lulek wczoraj stanął na palcach.

Napisz program, który wykorzystując algorytm `<span class="pre">mergesort</span>` wygeneruje właściwe ustawienie żołnierzy (w kolejności od największego do najmniejszego) oraz pomoże obliczyć jakie jest prawdopodobieństwo, że kapral Leon uzna, iż losowo wybrana para żołnierzy stoi w niepoprawnej kolejności.

## Wejście

Pierwsza linia wejścia zawiera liczbę całkowitą **z** – liczbę zestawów danych, których opisy występują kolejno po sobie. Opis jednego zestawu jest następujący:

W pierwszej linii znajduje się liczba naturalna **n** – stan drużyny (**1**≤**n**≤**10**6) oraz liczba **k** (**0**≤**k**≤**10**9) oznaczająca jak wysoko żołnierze potrafią wspiąć się na palce. W drugiej – **n** liczb naturalnych ***a**_1,a_2,**…**,a__n* oznaczających wzrost żołnierzy (*150≤**a_i**≤10^9)*.

## Wyjście

Dla każdego zestawu danych wypisz w pierwszej linii jedną linię zawierającą posortowane nierosnąco wzrosty żołnierzy.

W drugiej linii wypisz liczbę naturalną oznaczającą liczbę błędów w ustawieniu, czyli liczbę par **(**i**,**j**)** takich, że **1**≤**i**<**j**≤**n** oraz **a**_i+**k**<**a**_j. Pamiętaj, że jeśli to korzystne, żołnierze podchodząc do kaprala stają na palcach.

## Przykład

Dla danych wejściowych:
1
5 10
172 191 179 185 189
Poprawną odpowiedzią jest:
191 189 179 172
3
