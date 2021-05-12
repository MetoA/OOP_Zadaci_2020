/*
NBA Problem 3 (2 / 2) 
NBAPlayer
Да се дефинира класа NBAPlayer за која ќе се чуваат:

динамички алоцирана низа од карактери за името на играчот
низа од максимум 40 карактери за тимот во кој играчот моментално настапува
просечен број на поени на играчот оваа сезона (double)
просечен број на асистенции на играчот оваа сезона (double)
просечен број на скокови на играчот оваа сезона (double)
За потребите на класата да се дефинираат:

default конструктор и конструктор со аргументи
copy constructor и оператор =
деструктор
метод rating() кој го враќа рејтингот на кошаркарот кој се пресметува како:

45% од поените + 30% од асистенциите + 25% од скоковите

метод print() кој го печати играчот во следниот формат:

Име - тим

Points: поени

Assists: асистенции

Rebounds: скокови

Rating: рејтинг

AllStarPlayer
Од претходната класа NBAPlayer да се изведе класата AllStarPlayer за која дополнително ќе се чуваат и:

просечен број на поени на играчот од All Star натпреварите (double)
просечен број на асистенции на играчот од All Star натпреварите (double)
просечен број на скокови на играчот од All Star натпреварите (double)
За потребите на класата да се дефинираат:

default конструктор
конструктор кој прима објект од NBAPlayer и плус додатните информации (погледни main)
конструктор кој ги прима сите аргументи (погледни main)
copy constructor, оператор =, деструктор
метод allStarRating() кој го враќа рејтингот на кошаркарот од All Star натпреварите и кој се пресметува како:

30% од поените + 40% од асистенциите + 30% од скоковите

Да се препокријат методите:

rating() кој го враќа просекот од обичниот рејтинг на кошаркарот и неговиот All Star рејтинг
print() кој покрај основните информации за кошаркарот печати и:

All Star Rating: рејтингот од All Star натпреварите

New Rating: просечниот рејтинг

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

class NBAPlayer{
protected:
    char *playerName;
    char teamName[40];
    double points;
    double assists;
    double jumps;
public: 
    NBAPlayer(const char *playerName = "", const char *teamName = "", double points = 0, double assists = 0, double jumps = 0){
    	this->playerName = new char[strlen(playerName)+1];
        strcpy(this->playerName, playerName);
        strcpy(this->teamName, teamName);
        this->points = points;
        this->assists = assists;
        this->jumps = jumps;
    }
    
    //Copy Constructor
    NBAPlayer(const NBAPlayer &player){
    	this->playerName = new char[strlen(player.playerName)+1];
        strcpy(this->playerName, player.playerName);
        strcpy(this->teamName, player.teamName);
        this->points = player.points;
        this->assists = player.assists;
        this->jumps = player.jumps;
    }
    
    NBAPlayer &operator=(const NBAPlayer &player){
        if(this!=&player){
            delete[] playerName;
        	this->playerName = new char[strlen(player.playerName)+1];
            strcpy(this->playerName, player.playerName);
            strcpy(this->teamName, player.teamName);
            this->points = player.points;
            this->assists = player.assists;
            this->jumps = player.jumps;
        }
        return *this;
    }
    
    ~NBAPlayer(){
    	delete[] playerName;
    }
    
    double rating(){
    	return points/100.0*45 + assists/100.0*30 + jumps/100.0*25;
    }
    
    void print(){
    	cout << playerName   << " - " << teamName <<endl;
        cout << "Points: "   << points << endl;
        cout << "Assists: "  << assists << endl;
        cout << "Rebounds: " << jumps << endl;
        cout << "Rating: "   << rating() << endl;
    }
};

class AllStarPlayer : public NBAPlayer{
private:
    double allStarPoints;
    double allStarAssists;
    double allStarJumps;
public: 
    AllStarPlayer(){}
    
    AllStarPlayer(const NBAPlayer &player, double allStarPoints, double allStarAssists, double allStarJumps)
    : NBAPlayer(player){
    	this->allStarPoints = allStarPoints;
        this->allStarAssists = allStarAssists;
        this->allStarJumps = allStarJumps;
    }
    
    AllStarPlayer(const char *playerName, const char *teamName, double points, double assists, double jumps, 
                  double allStarPoints, double allStarAssists, double allStarJumps)
    : NBAPlayer(playerName, teamName, points, assists, jumps){
    	this->allStarPoints = allStarPoints;
        this->allStarAssists = allStarAssists;
        this->allStarJumps = allStarJumps;
    }
    
    //Copy Constructor
    AllStarPlayer(const AllStarPlayer &ASPlayer) : NBAPlayer(ASPlayer){
    	this->allStarPoints = ASPlayer.allStarPoints;
        this->allStarAssists = ASPlayer.allStarAssists;
        this->allStarJumps = ASPlayer.allStarJumps;
    }
    
    AllStarPlayer &operator=(const AllStarPlayer &ASPlayer){
        if(this!=&ASPlayer){
        	delete[] playerName;
        	this->playerName = new char[strlen(ASPlayer.playerName)+1];
            strcpy(this->playerName, ASPlayer.playerName);
            strcpy(this->teamName, ASPlayer.teamName);
            this->points = ASPlayer.points;
            this->assists = ASPlayer.assists;
            this->jumps = ASPlayer.jumps;
            this->allStarPoints = ASPlayer.allStarPoints;
            this->allStarAssists = ASPlayer.allStarAssists;
            this->allStarJumps = ASPlayer.allStarJumps;
        }
        
        return *this;
    }
    
    ~AllStarPlayer(){}
    
    double allStarRating(){
    	return allStarPoints/100.0*30 + allStarAssists/100.0*40 + allStarJumps/100.0*30;
    }
    
    double rating(){
    	return (NBAPlayer::rating() + allStarRating()) / 2.0;
    }
    
    void print(){
    	NBAPlayer::print();
        cout << "All Star Rating: " << allStarRating() << endl;
        cout << "New Rating: " << rating() << endl;
    }
        
};

int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }
    
    delete [] players;
    delete [] asPlayers;
}
