/*
ListContainer Problem 5 (2 / 7) 
Да се имплементира класа List во којашто ќе се чуваат информации за:

броеви што се дел од листата (динамички алоцирана низа од цели броеви)
бројот на броеви што се дел од листата
За класата да се дефинираат следните методи:

конструктор (со аргументи), copy-конструктор, деструктор, оператор =
void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
int sum() метод што ја враќа сумата на елементите во листата
double average() метод што ќе го враќа просекот на броевите во листата
Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

низа од листи (динамички алоцирана низа од објекти од класата List)
број на елементи во низата од листи (цел број)
број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
За класата потребно е да ги дефинирате следните методи:

конструктор (default), copy-конструктор, деструктор, оператор =
void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
доколку контејнерот е празен се печати само порака The list is empty.
void addNewList(List l) метод со којшто се додава листа во контејнерот
Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
int sum() метод што ја враќа сумата на сите елементи во сите листи
double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

class List{
private:
    int *broevi;
    int brojBroevi;
public:
    List(int *broevi = 0, int brojBroevi = 0){
    	this->brojBroevi = brojBroevi;
        this->broevi = new int[brojBroevi];
        for(int i = 0; i < brojBroevi; i++){
        	this->broevi[i] = broevi[i];
        }
    }
    
    List(const List &list){
    	this->brojBroevi = list.brojBroevi;
        this->broevi = new int[brojBroevi];
        for(int i = 0; i < brojBroevi; i++){
        	this->broevi[i] = list.broevi[i];
        }
    }
    
    List &operator =(const List &list){
        if(this!=&list){
        	delete[] broevi;
            this->brojBroevi = list.brojBroevi;
            this->broevi = new int[brojBroevi];
            for(int i = 0; i < brojBroevi; i++){
                this->broevi[i] = list.broevi[i];
            }
        }
        return *this;
    }
    
    int getBrojBroevi(){
    	return brojBroevi;
    }
    
    int sum(){
    	int sum = 0;
        for(int i = 0; i < brojBroevi; i++){
        	sum += broevi[i];
        }
        return sum;
    }
    
    double average(){
    	return (double)sum()/brojBroevi;
    }
    
    void pecati(){
    	cout << brojBroevi << ": ";
        for(int i = 0; i < brojBroevi; i++){
        	cout << broevi[i] << " " ;
        }
        cout << "sum: " << sum();
        cout << " average: " << average()<< endl;
    }
    
    ~List(){
    	delete[] broevi;
    }
};

class ListContainer{
private:
    List *listi;
    int brojListi;
    int obidi;
public:
    ListContainer(List *list = 0, int brojListi = 0, int obidi = 0){
    	this->brojListi = brojListi;
        this->obidi = obidi;
        this->listi = new List[brojListi];
        for(int i = 0; i < brojListi; i++){
        	this->listi[i] = list[i];
        }
    }
    
    //copy constructor
    ListContainer(const ListContainer &listCopy){
    	this->brojListi = listCopy.brojListi;
        this->obidi = listCopy.obidi;
        this->listi = new List[listCopy.brojListi];
        for(int i = 0; i < listCopy.brojListi; i++){
        	this->listi[i] = listCopy.listi[i];
        }
    }
    
    ListContainer &operator = (const ListContainer &listContainer){
        if(this!=&listContainer){
        	delete[] listi;
            this->brojListi = listContainer.brojListi;
            this->obidi = listContainer.obidi;
            this->listi = new List[listContainer.brojListi];
            for(int i = 0; i < listContainer.brojListi; i++){
                this->listi[i] = listContainer.listi[i];
            }
        }
        return *this;
    }
    
    void addNewList(List l){
    	bool same = false;
        for(int i = 0; i < brojListi; i++){
            if(listi[i].sum() == l.sum()){
            	same = true;
            }
        }
        if(!same){
        	List *newList = new List[brojListi+1];
            for(int i = 0; i < brojListi; i++){
            	newList[i] = listi[i];
            }
            newList[brojListi++] = l;
            delete[] listi;
            listi = newList;
        } else {
        	obidi++;
        }
    }
    
    int sum(){
        int sum = 0;
        for(int i = 0; i < brojListi; i++){
        	sum += listi[i].sum();
        }
        return sum;
    }
    
    double average(){
    	int brojBroevi = 0;
        for(int i = 0; i < brojListi; i++){
        	brojBroevi += listi[i].getBrojBroevi();
        }
        return sum()/(double)brojBroevi;
    }
    
    void print(){
        if(brojListi == 0){
        	cout << "The list is empty" << endl;
        } else {
        	for(int i = 1; i <= brojListi; i++){
        		cout << "List number: " << i << " List info: ";
                listi[i-1].pecati(); 
        	}
            cout << "Sum: " << sum() << " Average: " << average() << endl;
            cout << "Successful attempts: " << brojListi << " Failed attempts: " << obidi << endl;
        }        
    }
    
    ~ListContainer(){
    	delete[] listi;
    }
};

int main() {
	
	ListContainer lc;
	int N;	
	cin>>N;	
    
	for (int i=0;i<N;i++) {
		int n;
		int niza[100];
		
		cin>>n;
       
		for (int j=0;j<n;j++){
			cin>>niza[j];
            
		}
       
		List l=List(niza,n);
	
		lc.addNewList(l);
	}	
	
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
        
    }
    else {
        lc.print();
    }
}