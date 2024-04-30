Aceasta este implementarea mea pentru Tema 2

Am ales sa ridic dificulatatea temei prin a folosi date generice de tip void *
pentru a-mi consolida mai bine cunostinele. Am ales sa imi modularizez codul cat mai mult
pentru a fi usor de citit si inteles, fiecare parte din program avand functia/fisierul ei.
Cred ca tema mea se distinge de celelate teme prin aceste abordari + prin faptul ca fiecare
variabila este alocata dinamic si memoria este folosita foarte eficient.


In main.c am doar citirea din fisiere si prelucrarea datelor.
In train.c am fiecare functie care se ocupa cu managementul triei.
In utils.c am functii pe care le folsoesc des pentru a da check la alocarile dinamice
sau la existenta fisierelor.


Taskul 1

Am implementat taskul 1 printr-o metoda simpla prin care am inceput
iteratiile de la finalul cuvant si creand un nod nou pentru fiecare litera
din sufix care nu se afla in arbore. Daca gaseam o litera care exista deja parcurgeam
arborele pana in acel punct.
Pentru printarea arborelui am folosit un BFS clasic folosind o coada pe care am alocat-o dinamic
in functie de cate frunze are arborele, si am tot marit-o pe parcurs deoarece trebuia sa adaug si 
\n.

Task 2

Pentru fiecare subpunct am folosit implementari recursive prin care parcurg arborele si
verific fiecare cerinta. Am facut o implemetare frumoasa deoarece am scris codul in asa fel
incat utilizatorul sa nu fie lasat sa foloseasca un alt nod de inceput fata de radacina.

Task 3

Pentru implementarea taskului 3 am folosit tot o metoda recursiva in care caut fiecare litera
din sufix in noduri si acutalizez indicele literei. Daca i este la fel de lung ca si cuvantul
si in nodul in care ma aflu exista $ inseamna ca am gasit acel sufix.

Task 4

Pentrul taskul 4 am incercat prima data o implementare prin care fac direct tria compacta
insa mi-am dat seama ca nu e o metoda fiabila deoarece daca am apple, cuvant pe care eu in metoda mea
l-as fi adaugat direct ca si cuvant, apoi un sufix ar, ar fi trbuit sa sparg apple in a-pple ca sa adaug
a-r, ceea ce ar fi fost mult mai dificil de facut. Avand acestea in minte am decis sa schimb
abordarea si am pornit pe fiecare ramura a arboreului in cautarea unui nod care nu e sfarsit
de cuvant si care are doar 1 copil, apoi am concatenat copilul la nodul respectiv si am transferat
vectorul de copii al copilului nodului in cauza. Apoi pornesc recursiv din nou din nodul cel mare in cautarea altui copil.

Tema mi-a placut, o singura problema am avut, la taskul 4 local valgrind-ul local rulat cu aceleasi
rules imi da 0 leaks si nicio eroare insa valgrind-ul rulat cu ./checker.sh imi da ceva eroare la alocarea
nodurlior care mi se pare putin ciudat pt ca ar fi trb. sa imi dea aceeasi eroare si pentru celalate taskuri
ma gandesc.. Nu stiu exact ce se intampla acolo, poate o sa poata sa ma lamureasca cineva :)