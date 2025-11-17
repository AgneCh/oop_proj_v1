# 2 užduotis


# (v1.2)

Šioje programos versijoje realizuotas "Rule of three" (kopijavimo konstruktorius, kopijavimo priskirties operatorius, destruktorius). Programoje taip pat realizuoti ir panaudoti įvestie/išvesties operatoriai.

## Realizuoti metodai ir operatoriai

### Rule of three

Student.h faile, Student klasėje sukurtos šios dalys:
`Kopijavimo konstruktorius (copy constructor)`
|Konstruktorius perkelia visas kito objekto reikšmes į naujai kuriamą objektą. Taip užtrikrinama, kad naujai sukurtas objektas turi identiškus duomenis, tačiau yra atskiras objektas atmintyje.|
![alt text](./screenshots/copyConstructor.png)

`Kopijavimo priskirties operatorius (copy assignassigment operator)`
Kopijavimo priskirties operatorius naudojamas tada, kai jau egzistuojančiam Student objektui priskiriamos kito objekto reikšmės.
![alt text](./screenshots/copyAssigmentOperator.png)

`Destruktorius (destructor)`
Destruktorius iškviečiamas, kai Student objektas sunaikinamas.
![alt text](./screenshots/destructor.png)

### Įvestie/išvesties operatoriai
`Kopijavimo konstruktorius (copy constructor)`


## Programos funkcionalumas

### 1. Duomenų įvedimo būdai:

1. **Rankiniu būdu**: vartotojas pats suveda studento vardą, pavardę, namų darbų ir egzamino balus.
2. **Automatiškai**: programa sugeneruoja atsitiktinius duomenis nurodytam studentų kiekiui.
3. **Iš failo**: studentų duomenys nuskaitomi iš tekstinio failo (pvz., `studentai.txt`).

### 2. Duomenų išvedimo būdai:

- **Į ekraną**: studentų duomenys rodomi konsolėje, suformatuoti lentelės pavidalu.
- **Į failą**: sugeneruojamas tekstins failas su studentų duomenimis.

### 1.1 Rankinis duomenų įvedimas




