/*
SocialNetwork Problem 2 (2 / 4) 
Да се дефинира апстрактна класа User за која ќе се чуваат:

username (char[50])
password (char[50])
email (char[50])
Класата треба да содржи еден чист виртуелен метод double popularity().

Од оваа класа да се изведат две класи и тоа FacebookUser и TwitterUser.

За класата FacebookUser уште се чуваат и:

број на пријатели
број на лајкови и
број на коментари
Популарноста се пресметува така што се собираат бројот на пријатели, бројот на лајкови и бројот на коментари, но притоа бројот на лајкови се множи со коефициент на вредност на лајкот кој е ист за секој корисник и изнесува 0.1, а исто така и бројот на коментари се множи со ист таков коефициент кој е 0.5.

За класата TwitterUser уште се чуваат и:

број на следачи и
број на твитови
Популарноста се пресметува така што се собираат бројот на следачи и бројот на твитови, но притоа бројот на твитови се множи со коефициент на вредност на твитот кој е ист за секој корисник и изнесува 0.5.

Да се креира класа SocialNetwork која ќе содржи:

динамичка низа од покажувачи од класата User
број на тековни корисници и
максимален број на корисници кој може да го содржи мрежата и кој е ист за сите мрежи и иницијално е поставен на 5
Да се преоптовари операторот += со кој ќе се додава нов корисник.

Да се дефинира метод avgPopularity() кој ќе ја враќа просечната популарност на корисниците во мрежата.

Исто така да се овозможи промена на максималната големина на низата преку методот changeMaximumSize(int number).

Потребно е да се справите со следните исклучоци:

Доколку лозинката на корисникот не содржи барем 1 голема буква, 1 мала буква и 1 број да се фрли исклучок од класа InvalidPassword така што како параметар ќе се прати пораката Password is too weak.
Доколку емаилот на корисникот не содржи точно еднаш @ да се фрли исклучок од класа InvalidEmail така што како параметар ќе се прати пораката Mail is not valid.
Доколку проба да се додаде корисник во социјалната мрежа, а веќе максималниот број на корисници е пополнет да се фрли исклучок од класа MaximumSizeLimit така што како параметар ќе се прати максималниот број на корисници во мрежата.
Сите класи кои се справуваат со исклучоци треба да го имаат имплементирано методот void message() така што за првите две класи ќе ја печати пораката којашто е испратена како параметар, а за последната класа ќе печати You can't add more than N users, каде што N е параметарот кој е пратен. Исто така со try-catch блокови справете се со исклучоците на соодветните места во main(), каде што во catch ќе го повикате методот message() од соодветниот исклучок.

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

class InvalidPassword{
private:
    char parameter[50];
public:
    InvalidPassword(char* param){
        strcpy(parameter, param);
    }
    
    void message(){
    	cout<<parameter<<endl;
    }
    
};

class InvalidEmail{
private:
    char parameter[50];
public:
    InvalidEmail(char* param){
        strcpy(parameter, param);
    }
    
    void message(){
    	cout<<parameter<<endl;
    }
};

class MaximumSizeLimit{
private:
    int num;
public:
    MaximumSizeLimit(int num){
    	this->num = num;
    }
    
    void message(){
    	cout<<"You can't add more than "<<num<<" users."<<endl;
    }
};
    
class User{
protected:
    char username[50];
    char password[50];
    char email[50];
    static double likeCoef;
    static double commentCoef;
    static double tweetCoef;
public:
    User(char* username = "", char* password = "", char* email = ""){
    	strcpy(this->username, username);
        setPassword(password);
        setEmail(email);
    }
    
    void setPassword(char* pw){
    	int uppercase = 0;
        int lowercase = 0;
        int numCount = 0;
        
        for(int i = 0; i < strlen(pw); i++){
            if(isupper(pw[i])){
             uppercase++;
            } else if(islower(pw[i])){
            	lowercase++;
            } else if(isdigit(pw[i])){
            	numCount++;
            }
        }
        
        if(uppercase==0 || lowercase==0 || numCount==0){
        	throw InvalidPassword("Password is too weak.");
        }
        
        strcpy(this->password, pw);
    }
    
    void setEmail(char* em){
    	int containsAt = 0;
        
        for(int i = 0; i < strlen(em); i++){
            if(em[i] == '@'){
            	containsAt++;
            }
        }
        
        if(containsAt != 1){
        	throw InvalidEmail("Mail is not valid.");
        }
        
        strcpy(this->email, em);
    }
    
    virtual double popularity() = 0;
};

double User::likeCoef = 0.1;
double User::commentCoef = 0.5;
double User::tweetCoef = 0.5;

class FacebookUser : public User{
private:
    int friendCount;
    int likeCount;
    int commentCount;
public:
    FacebookUser(char* username = "", char* password = "", char* email = "", int friendCount = 0, int likeCount = 0, int commentCount = 0)
    :User(username, password, email){
    	this->friendCount = friendCount;
        this->likeCount = likeCount;
        this->commentCount = commentCount;
    }
    
    double popularity(){
    	return friendCount + likeCount*likeCoef + commentCount*commentCoef;
    }
};

class TwitterUser : public User{
private:
    int followerCount;
    int tweetCount;
public:
    TwitterUser(char* username = "", char* password = "", char* email = "", int followerCount = 0, int tweetCount = 0)
        :User(username, password, email){
        	this->followerCount = followerCount;
            this->tweetCount = tweetCount;
        }
    
    double popularity(){
    	return followerCount + tweetCount*tweetCoef;
    }
};

class SocialNetwork{
private:
    User **users;
    int currentUsers; 
    static int maxNumUsers; 
public:
    SocialNetwork(){
    	users = new User*[0];
        currentUsers = 0;
    }
    
    SocialNetwork &operator+=(User *u){
        if(currentUsers == maxNumUsers){
        	throw MaximumSizeLimit(maxNumUsers);
        }
        
    	User **temp = new User*[currentUsers+1];
        for(int i = 0; i < currentUsers; i++){
        	temp[i] = users[i];
        }
        
        temp[currentUsers++] = u;
        delete[] users;
        users = temp;
        
        return *this;
    }
    
    double avgPopularity(){
    	double totalPopularity = 0;
        
        for(int i = 0; i < currentUsers; i++){
        	totalPopularity += users[i]->popularity();
        }
        
        return totalPopularity/currentUsers;
    }
    
    void changeMaximumSize(int number){
    	maxNumUsers = number;
    }
};

int SocialNetwork::maxNumUsers = 5;

int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;
          
        // TODO: Try-catch
        try{
        	User * u = new FacebookUser(username,password,email,friends,likes,comments);
        	network += u;
      	}catch(InvalidPassword &err) {
    		err.message();
  		}
  		catch (InvalidEmail &err) {
    		err.message();
  		}
  		catch(MaximumSizeLimit &err) {
    		err.message();
  		}
      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;
          
        // TODO: Try-catch 
          	try{
        		User * u= new TwitterUser(username,password,email,followers,tweets);
        		network += u;
          	}catch(InvalidPassword &err) {
    			err.message();
  			}catch (InvalidEmail &err) {
    			err.message();
  			}catch(MaximumSizeLimit &err) {
    			err.message();
  			}
      }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;
    
    // TODO: Try-catch
    try{
    	User * u= new TwitterUser(username,password,email,followers,tweets);
    	network += u;
    }catch(InvalidPassword &err) {
    	err.message();
  	}catch (InvalidEmail &err) {
   	 	err.message();
  	}catch(MaximumSizeLimit &err) {
    	err.message();
  	}
    
    cout << network.avgPopularity();

}
