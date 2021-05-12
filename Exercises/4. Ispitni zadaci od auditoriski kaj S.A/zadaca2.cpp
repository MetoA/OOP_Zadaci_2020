/*
Задача 2 Problem 2 (2 / 2)
Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)

100%
*/

#include <iostream>
#include <cstring>

#define MAX 50

using namespace std;

enum typeC{standard, loyal, vip};

class UserExistsException{
public:
  void message(){
    cout<<"The user already exists in the list!"<<endl;
  }  
};

class Customer{
private:
  char ime[50];
  char email[50];
  typeC typeCustomer;
  int numProducts;

public:
  static int osnovenPopust;
  static int dopolnitelenPopust;
  Customer(char *ime = "", char *email = "", typeC typeCustomer = standard, int numProducts = 0){
    strcpy(this->ime, ime);
    strcpy(this->email, email);
    this->typeCustomer = typeCustomer;
    this->numProducts = numProducts;
  }

  const char* printTypeCustomer(int typeCustomer) const{
    switch(typeCustomer){
      case 0: return "standard";
      case 1: return "loyal";
      case 2: return "vip";
    }
  }

  static void setDiscount1(int n){
    Customer::osnovenPopust = n;
  }

  const char* getEmail() const{
    return email;
  }

  const int getType() const{
    return typeCustomer;
  }

  void setType(typeC type){
    typeCustomer = type;
  }

  const int getNumProducts() const{
    return numProducts;
  }

  friend ostream &operator<<(ostream &stream, const Customer &c){
    stream<<c.ime<<endl;
    stream<<c.email<<endl;
    stream<<c.numProducts<<endl;
    stream<<c.printTypeCustomer(c.typeCustomer)<<" ";

    if(c.typeCustomer == loyal){
      stream<<Customer::osnovenPopust<<endl;
    } else if(c.typeCustomer == vip){
      stream<<Customer::dopolnitelenPopust + Customer::osnovenPopust<<endl;
    } else if(c.typeCustomer == standard){
      stream<<"0"<<endl;
    }

    return stream;
  }
};

class FINKI_bookstore{
private:
  Customer *customers;
  int numCustomers;
public:
  FINKI_bookstore(){
    customers = new Customer[0];
    numCustomers = 0;
  }

  FINKI_bookstore &operator+=(const Customer &c){
    for(int i = 0; i < numCustomers; i++){
      if(!(strcmp(c.getEmail(), customers[i].getEmail()))){
        throw UserExistsException();
      }
    }

    Customer *temp = new Customer[numCustomers+1];

    for(int i = 0; i < numCustomers; i++){
      temp[i] = customers[i];
    }

    temp[numCustomers++] = c;

    delete[] customers;
    customers = temp;

    return *this;
  }

  void setCustomers(Customer *customers, int n){
    Customer *temp = new Customer[n];

    for(int i = 0; i < n; i++){
      temp[i] = customers[i];
    }

    delete[] this->customers;
    this->customers = temp;
    this->numCustomers = n;
  }

  void update(){
    for(int i = 0; i < numCustomers; i++){
      if(customers[i].getType() == 1&&customers[i].getNumProducts() > 10) customers[i].setType(vip);
      if(customers[i].getType() == 0&&customers[i].getNumProducts() > 5) customers[i].setType(loyal);
    }
  }

  friend ostream &operator<<(ostream &stream, const FINKI_bookstore &fb){
    for(int i = 0; i < fb.numCustomers; i++){
      stream<<fb.customers[i];
    }

    return stream;
  }
};

int Customer::osnovenPopust = 10;
int Customer::dopolnitelenPopust = 20;

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    try{
      fc+=c;
    } catch(UserExistsException uee){
      uee.message();
    }

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    
    Customer c(name, email, (typeC) tC, numProducts);
    try{
      fc+=c;
    } catch(UserExistsException uee){
      uee.message();
    }
    
    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;
   
}
