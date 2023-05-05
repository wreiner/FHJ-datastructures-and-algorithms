# Sorting Alogrithm

Elementare Sortierverfahren

## Interne vs Externe Sortierverfahren

### Interne

- Alle zu sortierenden Datensätze finden im Hauptspeicher Platz
- Auf alle Datensätze kann wahlfrei sehr schnell zugegriffen werden

- Insertion sort
- Bubble sort
- Selection sort
- Quick sort in Variante

### Externe

- Die zu sortierenden Datensätze können nicht vollständig im
  Hauptspeicher gehalten werden und liegen auf einem vergleichsweise
  langsamen externen Medium vor
- Ziel: Minimierung der Zugriffe auf das externe Medium

- Merge sort in Variante

## Stabile Sortierverfahren

- Die relative Reihenfolge der Datensätze, deren Sortierschlüssel gleich ist, wird nicht verändert

- Stable sorting algorithms choose one of these, according to the following rule: if two items compare as equal (like the two 5 cards), then their relative order will be preserved, i.e. if one comes before the other in the input, it will come before the other in the output.

- Bubble sort
- Insertion sort
- Merge sort

## Sortierverfahren

### Sortieren durch Auswahl

- kleinste Zahl wird gesucht und mit em Wert der ersten Stelle vertauscht.
  Dann wird wieder eine kleinere Zahl gesucht und nun mit em Wert an der zweiten Stelle getauscht. Alles wird
  wiederholt, bis man fertig ist.

- Anzahl der Vergleiche Θ(n^2)
- Anzahl der Bewegungen Θ(n)

### Sortieren durch Einfügen

- Es wird links begonnen. Die ersten beiden Werte werden verglichen, der kleinere wandert nach links.
  Dann wird die Liste geteilt in eine sortieret und eine unsortierrte Folge. Der erste unsortierte Wert
  wird nun mit dem letzten sortierten verglichen. Der Kleinere wandert nach links, bis links kein Kleinerer
  mehr ist. Nun wird die Sortiergrenze um eins nach rechts verschoben und von Neuem begonnen. 

- Anzahl der Vergleiche Θ(n^2) - Θ(n^2) - Θ(n)
- Anzahl der Bewegungen Θ(n^2) - Θ(n)

### Bubble sort

- Man beginnt links, die ersten beiden Elemente zu vergleichen. Das Größere soll rechts stehen, das Kleinere
  links. Nun vergleicht an Element 2 und 3 usw., bis man am Ende ist. Dann beginnt man von vorne, bis die
  richtige Reihenfolge gegeben ist.

- Anzahl der Vergleiche Θ(n^2) - Θ(n^2) - n-1
- Anzahl der Bewegungen Θ(n^2) - 0

### Quick sort

- Ein Pivotelement wird angenommen, z.B. ganz rechts. Von ihm absteigend wird ein kleineres Element gesucht,
  vom Listenbeginn auftsiegend ein größeres. Hat man sie, weren sie vertauscht. Das macht man, bis man
  nicht mehr tauschen kann. Nun wird das Pivotelement mit dem übrigbleibenden Element vertauscht und steht
  somit an der richtigen Stelle. Nun wird für jede Teilliste (links und Rechts des ehemaligen Pivotelements)
  erneut eine PE genommen und die Sache beginnt von vorne.

- Divide and Conquer
- Pivotelement
- hat in-situ Möglichkeit

- Anzahl der Vergleiche Θ(n^2) - Θ(n log n) - n-1
- Anzahl der Bewegungen Θ(n^2) - 0

### Merge sort

- Eine Liste wir in jedem Schritt halbiert, bis sie in ihre Einzellteile zerlegt ist. Nun werden jeweils 2
  Elemente sortiert und zu einer neuen Liste zusammengefügt. Im nächsten Schritt fügt man wieder zwei Listen
  zusammen und sortiert diese erneut, bis alles in der richtigen Reihenfolge steht.

- aufteilen in gleich lange Teilfolgen mit Verschmelzung
- zusätzlicher Speicherplatz benötigt - kein in-situ
