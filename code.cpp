#include <iostream> 
#include <vector> 
#include <string>   
using namespace std; 

// функция разделения строки на подстроки по 9 цифр и занесение их  
// в вектор в виде чисел (с конца) 
void massiv(vector <long int> &a, string s, int len, int part) { 
    string sub; 
    // j - номер элемента в массиве, k - номер подстроки,  
    // i -позиция первого символа в подстроке 
    int k = 1, i = len - 9, j = 0; 
    while (k <= part) { 
        // выделяем подстроку из 9 цифр, двигаясь с конца 
        // если последняя подстрока содержит меньше 9 символов,то 
        // берем с 0-го символа все оставшиеся 
        sub = i >= 0 ? s.substr(i, 9) : s.substr(0, 9 + i); 
        a[j] = stoi(sub.c_str()); // преобразование в число		 
        j++; k++; 
        i -= 9; 
    } 
} 

// функция преобразования числа в строку с добавлением нулей 
// до 9 разрядов 
string to_str(long int m) { 
    string s = to_string(m); 
    s.insert(0, 9 - s.length(), '0'); 
    return s; 
} 

//функция для сложения чисел записанных в типе string
string add(string s1, string s2){ 
    int len1 = s1.length(); 
    int len2 = s2.length(); 
    // добавляем нули слева к меньшей подстроке 
    if (len1 < len2) { 
        s1.insert(0, len2 - len1, '0'); 
    } 
    else if (len1 > len2) 
        s2.insert(0, len1 - len2, '0'); 
    int len = s1.length();	// итоговая длина строки 
    // делим строку на части по 9 символов	 
    int part = len % 9 == 0 ? len / 9 : len / 9 + 1; 

    // выделяем память, включая доп.разряд слева 
    vector <long int> a(part + 1,0); 
    vector <long int> b(part + 1,0);
    vector <long int> c(part + 1,0); 
    
    // вызываем функцию занесения строк в векторы 
    massiv(a, s1, len, part); 
    massiv(b, s2, len, part); 
    // перенос разряда 
    int ost = 0; 
    for (int i = 0; i <= part; i++) { 
        c[i] = (a[i] + b[i]) % 1000000000 + ost; // сумма чисел
        ost = (a[i] + b[i]) / 1000000000; // перенос 
    } 
    string finum;
    for (int i = part; i >= 0; i--){
        finum += to_str(c[i]); 
    }
    // удаление ведущих нулей
    while (finum.substr(0,1) == "0"){
        finum.erase(finum.find("0"), 1);
    }
    return finum;
} 

//вспомогательная функция для вычитания
void difference(vector <long int> x, vector <long int> y, vector <long int> &z, int part){ 
    for (int i = 0; i < part; i++){ // проход по всем разрядам числа, начиная с последнего 
        z[i] = x[i] - y[i]; 
        if (z[i] < 0) { 
            z[i] += 1000000000; 
            x[i + 1]--;//занимаем разряд 
        } 
    } 
} 


//функция для вычитания чисел записанных в типе string
string diff(string s1, string s2) { 
    int len1 = s1.length(); 
    int len2 = s2.length(); 
    // добавляем нули слева к меньшей подстроке 
    int k = 3; //если числа равны  
    if (len1 < len2) { 
        s1.insert(0, len2 - len1, '0'); 
        k = 2; // второе число больше 
    } 
    else 
        if (len1 > len2) { 
            s2.insert(0, len1 - len2, '0'); 
            k = 1; // первое число больше 
        } 
        else { // длины чисел равны     
            for (int i = 0; i < len1; i++){ // поразрядное сравнение весов чисел 
                if (s1[i] > s2[i]){ // если разряд первого числа больше 
                k = 1; // значит первое число длиннее второго 
                break; // выход из цикла for 
                } 
                if (s2[i] > s1[i]){  // если разряд второго числа больше 
                k = 2; // значит второе число длиннее первого 
                break; // выход из цикла for 
                } 
            } // конец for 
        } 
        string finum;
        if (k == 3){ // ни разу не попали в if в предыдущем цикле 
            finum = "0";
            return finum;
        } 
        else { 
            int len = s1.length();	// итоговая длина строки (длины строк уже уравняли) 
            // делим строку на части по 9 символов	 
            int part = len % 9 == 0 ? len / 9 : len / 9 + 1; 
            // выделяем память и заполняем 0 
            vector <long int> a(part,0); 
            vector <long int> b(part, 0); 
            vector <long int> c(part, 0); 
            // вызываем функцию занесения строк в массивы 
            massiv(a, s1, len, part); 
            massiv(b, s2, len, part); 
            if (k == 1) 
                difference(a, b, c, part); 
            else 
                difference(b, a, c, part); 
            if (k == 2) 
                finum = "-"; 
            for (int i = part - 1; i >= 0; i--) { 
                finum += to_str(c[i]);  
            } 
            // удаление ведущих нулей
            while (finum.substr(0,1) == "0"){
                finum.erase(finum.find("0"), 1);
            }
            return finum;
        } 
} 

// функция для умножения
// строка b будет принимать только маленькие значения
string multyply(string a, string b){
    string ans;
    for (int i = 1; i <= stoi(b); i ++){
        ans = add(ans, a);
    }
    return ans;
}

int main(){
    setlocale(LC_ALL,"Russian");
    //Ввод числа с консоли
    string big_number;
    cout << "Введите число для извлечения корня:" << endl;
    cin >> big_number; cout << endl;
    
    //Проверка на корректность введенного числа
    if(big_number.substr(0, 1) == "-") {
        cout << "Ошибка! Число не должно быть отрицательным!";
        return 0;}
        
    else if(big_number.substr(0, 1) == "0") {
        cout << "Ошибка! В числе не должны встречаться ведущие нули!";
        return 0;}

    size_t found=big_number.find_first_not_of("1234567890");
    if (found!=string::npos) {
        cout << "Ошибка! В числе встречаются символы, не являющиеся цифрами!" << endl;
        return 0;
    } 

    if(big_number.length() < 40){
        cout << "Ошибка! Введите число больше 40 разрядов!";
        return 0;
    }

    bool even = big_number.size()%2 == 0; //Проверка на четность числа
    vector<string> pairs;
    for (int i = 0; i <= big_number.size(); i+=2){
        if(even)
            pairs.push_back(big_number.substr(i, 2)); //Если число четное, то делим его на пары
        else{
            pairs.push_back("0" + big_number.substr(i, 1)); //Иначе, к первой цифре числа подставляем ноль вначале
            even = true; //Делаем число четным
            i--;
        }     
    }


    string ans, fstnumsq;
    //Операция над первой парой числа
    //Выявление наибольшего квадрата числа, меньшего значения первой пары числа
    for(int i = 1; i <= 9; i++){
        if(i*i <= stoi(pairs[0])){
            ans = to_string(i);
            fstnumsq = to_string(i*i);
        }
    }
    
    cout << "Квадратный корень: " << endl << ans; //Выводим найденное значение
    string resdiff, subtr, plusans, currsubtr, fstmult;
    resdiff = diff(pairs[0], fstnumsq); //Результат вычитания найденного значения из первой пары
    for(int i = 1; i < pairs.size()-1; i++){
            resdiff += pairs[i]; //Дописываем к результату вычитания следующую пару
            string partfstmult = multyply(ans, "2"); //умножаем ответ на два
            //Поиск цифры, которой, при подстановке к удвоенному произведению текущего ответа и умножения
            //на него же, будет числом, меньшим результата вычитания+подстановки следующей пары
            for(int j = 1; j <= 9; j++){
                fstmult = partfstmult + to_string(j); 
                currsubtr = multyply(fstmult, to_string(j));
                if(j == 1 & diff(resdiff, currsubtr).substr(0,1) == "-"){ //если результат вычитания отрицателен уже при еденице, то
                    subtr = "0"; // вычитаем ноль
                    plusans = "0"; //дописываем ноль к ответу
                    break; // выходим из цикла
                }
                else if((diff(resdiff, currsubtr)).substr(0,1) != "-"){ //если результат вычитания не отрицателен
                    subtr = currsubtr; // приравниваем текущее вычитание к конечному вычитанию
                    plusans = to_string(j); // записываем в переменную текущую цифру 
                }
               
            }
            resdiff = diff(resdiff, subtr); // новый результат вычитания
            ans += plusans; //дописываем к ответу найденное значение
            cout << plusans; //выводим новый разряд
    }
    if(resdiff != "0") cout << ","; //если результат вычитания не равен нулю, то переходим в разряды после запятой
    while(resdiff != "0"){
        resdiff += "00"; //вместо следующей пары дописываем "00"
        string partfstmult = multyply(ans, "2");
            for(int j = 1; j <= 9; j++){
                fstmult = partfstmult + to_string(j);
                currsubtr = multyply(fstmult, to_string(j));
                if(j == 1 & diff(resdiff, currsubtr).substr(0,1) == "-"){
                    subtr = "0";
                    plusans = "0";
                }
                else if((diff(resdiff, currsubtr)).substr(0,1) != "-"){
                    subtr = currsubtr;
                    plusans = to_string(j);
                }
               
            }
        resdiff = diff(resdiff, subtr); // новый результат вычитания
        ans += plusans; //дописываем к ответу найденное значение
        cout << plusans; //выводим новый разряд
        int cntzero; //счетчик для кол-ва нулей после запятой в ответе
        if(plusans == "0") cntzero++;
        else cntzero = 0;
        if(cntzero == 20) break; //если кол-во нулей равно 20, то выходим из цикла
    }
  
}
