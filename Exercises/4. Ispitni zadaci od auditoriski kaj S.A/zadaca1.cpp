/*
Задача 1 Problem 1 (4 / 8)
За потребите на еден хотстинг провајдер потребно е да се моделира систем на наплата.

Да се имплементира абстрактна класа која претставува сервер на хостинг провајдерот (Server). За секој сервер се чуваат:

IP адреса на машината (низа од 45 знаци)
името на хостот (низа од макс 100 знаци)
Да се имплементираат класи за различните типови на сервери: дедициран сервер (DedicatedServer) и виртуелен сервер (VirtualServer)

За секојa сметка за дедициран сервер се чува:

основна цена (реален број)
количина на RAM меморија во гигабајти (цел број)
дин. алоцирана низа од хард дискови (во гигабајти) на дедицираниот сервер. Во низата се чува големината (во GB) на секој хард диск кој е достапен на дедицираниот сервер. Така на пример, доколку има 3 диска, тогаш се чуваат 3 целобројни променливи кои ја претставуваат големината (во гигабајти) на секој диск. Според тоа, низата {20, 100, 8} репрезентира дискови кои се со големина од 20GB, 100GB и 8GB соодветно.
број на дискови (цел број)
За секој виртуелен сервер се чува:

број на алицирани јадра (цел број)
месечен проток на серверот (изразен во гигабајти, цел број)
За секој од серверите да се имплементира пресметка на цена:

за дедициран сервер цената се пресметува на следниот начин: основната цена + хард_диск_простор * 0.5 + рам_меморија * 20.
за виртуелен сервер цената се пресметува на следниот начин: број_на_алоцирани јадра * 5 + месечен_проток * 10.
Да се дефинираат следниве оператори за дедициран сервер:

оператор += - додава нов диск со соодветната големина (дадена како аргумент) во низата од дискови.
оператор ++ (постинкремент) - ја зголемува количината на рам за 1 гигабајт.
Да се дефинираат следниве оператори за виртуелен сервер:

оператор += (постинкремент) - го зголемува бројот на алоцирани јадра за дадената вредност
оператор ++ - го зголемува потрошениот месечен проток за 1 гигабајт
Да се дефинира и оператор > кој ќе споредува два сервери врз основа на цената на нивната цена.

Да се имплементира оператор << кој ќе ги печати сите релевантни информации за секој од серверите во сл. формат: За дедициран сервер:

    [име на хост]: [IP адреса]
    [основна цена], [рам меморија]
    [број на дискови], [вкупен капацитет на сите дискови]
За виртуелен сервер:

    [име на хост]: [IP адреса]
    [број на јардра], [количина на потрошен интернет]
Да се креира функција totalCost која прима низа од покажувачи кон сервери и ја враќа вкупната цена за сите нив.

Да се креира функција biggestInvoice која прима низа од покажувачи кон сервери и го враќа серверот кој има најголема цена.

100%
*/

#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here
class Server{
protected:
    char IP[45];
    char hostName[100];
public:
    Server(char *IP = "", char *hostName = ""){
    	strcpy(this->IP, IP);
        strcpy(this->hostName, hostName);
    }
    
    virtual float total_price() const = 0;
};

class DedicatedServer : public Server{
private:
    float basePrice;
    int RAM;
    int *hardDisks;
    int numHardDisks;
public:
    DedicatedServer(char *IP = "", char *hostName = "", float basePrice = 0, int RAM = 0):Server(IP, hostName){
    	this->basePrice = basePrice;
        this->RAM = RAM;
        numHardDisks = 0;
        this->hardDisks = new int[0];
    }
    
    int vkupenKapacitet() const{
    	int totalSize = 0;
        
        for(int i = 0; i < numHardDisks; i++){
        	totalSize += hardDisks[i];
        }
        
        return totalSize;
    }
    
    float total_price() const{
    	return (basePrice + vkupenKapacitet() * 0.5 + RAM * 20);
    }
    
    DedicatedServer &operator+=(int size){
    	int *temp = new int[numHardDisks+1];
        for(int i = 0; i < numHardDisks; i++){
        	temp[i] = hardDisks[i];
        }
        
        temp[numHardDisks++] = size;
        delete[] hardDisks;
        
        hardDisks = temp;
        
        return *this;
    }
    
    DedicatedServer &operator++(int){
    	DedicatedServer ds(*this);
        RAM++;
        
        return ds;
    }
    
    friend ostream &operator<<(ostream &stream, const DedicatedServer &ds){
    	stream<<ds.hostName<<": "<<ds.IP<<endl;
        stream<<ds.basePrice<<", "<<ds.RAM<<endl;
        stream<<ds.numHardDisks<<", "<<ds.vkupenKapacitet()<<endl;
        
        return stream;
    }
    
    friend bool operator>(const Server &s1, const Server &s2);
};

class VirtualServer : public Server{
private:
    int cores;
    int bandwidth;
public:
    VirtualServer(char *IP = "", char *hostName = "", int cores = 0, int bandwidth = 0):Server(IP, hostName){
    	this->cores = cores;
        this->bandwidth = bandwidth;
    }
    
    float total_price() const{
    	return (cores * 5 + bandwidth * 10);
    }
    
    VirtualServer &operator+=(int size){
    	cores += size;
        
        return *this;
    }
    
    VirtualServer &operator++(int){
    	VirtualServer vs(*this);
        bandwidth++;
        
        return vs;
    }
    
    friend ostream &operator<<(ostream &stream, const VirtualServer &vs){
    	stream<<vs.hostName<<": "<<vs.IP<<endl;
        stream<<vs.cores<<", "<<vs.bandwidth<<endl;
        
        return stream;
    }
    
    friend bool operator>(const Server &s1, const Server &s2);
};

bool operator>(const Server &s1, const Server &s2){
	return (s1.total_price() > s2.total_price());
}

float totalCost(Server** serveri, int n){
    float total = 0;
    
    for(int i = 0; i < n; i++){
    	total+= serveri[i]->total_price();
    }
    
    return total;
}

Server &biggestInvoice(Server** serveri, int n){
    Server *biggestPrice = serveri[0];
    
    for(int i = 0; i < n; i++){
        if(biggestPrice > serveri[i]){
        	biggestPrice = serveri[i];
        }
    }
    
    return *biggestPrice;
}

// Testing
int main() {
  int test_case;
  char hostname[101];
  char ip[46];
  int ram;
  int basic_price;
  int disk_space;
  int num_cores;
  int bandwith;

  int num_inc;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case Business Invoice - Constructor, operator <<
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;
  } else if (test_case == 2) {
    // Test Case Business Invoice - Constructor, operators <<, ++
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      ds++;
    }
    cout << ds;
  } else if (test_case == 3) {
    // Test Case Business Invoice - Constructor, total_price, operators <<,
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      ds++;
    }

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      cin >> disk_space;
      ds += disk_space;
    }

    cout << ds;
  } else if (test_case == 4) {
    cin >> ip >> hostname;
    cin >> basic_price >> ram;
    DedicatedServer ds(ip, hostname, basic_price, ram);
    cout << ds;
    cout << ds.total_price();
    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      ds++;
    }

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      cin >> disk_space;
      ds += disk_space;
    }

    cout << ds;
    cout << ds.total_price();

  } else if (test_case == 5) {
    cin >> ip >> hostname;
    cin >> num_cores >> bandwith;
    VirtualServer vs(ip, hostname, num_cores, bandwith);
    cout << vs;
  } else if (test_case == 6) {
    cin >> ip >> hostname;
    cin >> num_cores >> bandwith;
    VirtualServer vs(ip, hostname, num_cores, bandwith);
    cout << vs;
    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      vs++;
    }

    cin >> num_inc;
    vs += num_inc;

    cout << vs;

  } else if (test_case == 7) {
    cin >> ip >> hostname;
    cin >> num_cores >> bandwith;
    VirtualServer vs(ip, hostname, num_cores, bandwith);
    cout << vs;
    cout << vs.total_price() << endl;

    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
      vs++;
    }

    cin >> num_inc;
    vs += num_inc;
    cout << vs;
    cout << vs.total_price();
  } else if (test_case == 8) {

    int num_servers;
    int server_type;

    cin >> num_servers;
    Server **s = new Server *[num_servers];
    for (int j = 0; j < num_servers; ++j) {

      cin >> server_type;
      if (server_type == 1) {
        cin >> ip >> hostname;
        cin >> basic_price >> ram;
        DedicatedServer *dsp =
            new DedicatedServer(ip, hostname, basic_price, ram);

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
          (*dsp)++;
        }

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
          cin >> disk_space;
          (*dsp) += disk_space;
        }

        cout << *(dsp);
        cout << dsp->total_price() << endl;

        s[j] = dsp;
      }
      if (server_type == 2) {

        cin >> ip >> hostname;
        cin >> num_cores >> bandwith;
        VirtualServer *vsp =
            new VirtualServer(ip, hostname, num_cores, bandwith);

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
          (*vsp)++;
        }

        cin >> num_inc;
        (*vsp) += num_inc;

        cout << (*vsp);
        cout << vsp->total_price() << endl;
        s[j] = vsp;
      }
    }

    cout << "The cost of all servers is:\n";
    cout << totalCost(s, num_servers);
    cout << endl;

    cout << "Biggest invoice:\n";
    Server &server = biggestInvoice(s, num_servers);

    Server *ss = &server;
    DedicatedServer *bip;
    VirtualServer *pip;
    if (dynamic_cast<DedicatedServer *>(ss)) {
      bip = dynamic_cast<DedicatedServer *>(ss);
      cout << *bip << bip->total_price();
    }
    if (dynamic_cast<VirtualServer *>(ss)) {
      pip = dynamic_cast<VirtualServer *>(ss);
      cout << *pip << pip->total_price();
    }
  }
  return 0;
}
