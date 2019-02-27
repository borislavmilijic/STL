#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<unordered_map>
#include<string>
#include<algorithm>
#include<numeric>
#include"spieler.h"

using namespace std;

int main() {
  vector<Spieler> v;

  //hier wird der Vektor v mit Daten gefuellt
  ifstream input{"spieler.txt"};
  Spieler f;
  while (f.read(input)) {
    v.push_back(f);
  }

  // Aufgabe 1

	struct Spieler_struct { 
  	bool operator()(const Spieler& s1, const Spieler& s2) const {
    if (s1.get_team() == s2.get_team()) {
      if (s1.get_position() == s2.get_position())
        return static_cast<int>(s1.get_faehigkeiten() > s2.get_faehigkeiten()); 
      return static_cast<int>(s1.get_position() > s2.get_position());
    }
    return(s1.get_team() > s2.get_team());
  }
};


	std::set<Spieler, Spieler_struct> my_set;
  std::for_each(v.begin(),v.end(),[&my_set](const Spieler& s) {		
		my_set.insert(s); });

	auto smallest50 = my_set.begin();
	auto smallest100 = my_set.begin();

	for(size_t i = 0; i<50; i++)
		smallest50++;

	for(size_t i = 0; i<100; i++)
		smallest100++;

	auto smallest = *(min_element(smallest50, smallest100, [] (const Spieler s1, const Spieler s2) {
		return s1.get_groesse() < s2.get_groesse();	
	})); 

  cout << "Set: " <<  my_set.size() << " items, " << endl;
  cout << "Name of Smallest Groesse: " << smallest.get_name() << endl;

  // Aufgabe 2
  vector<Spieler> v1;

	copy(v.begin(), v.end(), back_inserter(v1));

  double count = 0;
  double d = 0;

  for_each(v1.begin(), v1.end(), [&count, &d] (const Spieler& s) {
    if(s.get_position() == Positionen::Small_Forward) {
      count++;
      d += s.get_groesse();
    }
  });

  d = (d/count);

	size_t sum1{0};
	size_t sum2{0};

	for_each(v1.begin(), v1.end(), [&sum1, &d] (const Spieler& s) {
    if(s.get_groesse() > d && s.get_position() != Positionen::Center) {
      sum1+=s.get_name().size();
    }
  });
	
	for_each(v1.begin(), v1.end(), [] (Spieler& s) {
    if(s.get_position() == Positionen::Point_Guard) {
			s.wachsen();
    }
  });
	
	for_each(v1.begin(), v1.end(), [&sum2, &d] (Spieler& s) {
	if (s.get_groesse() > d && s.get_position() != Positionen::Center)
      sum2+=s.get_name().size();
	});
	

  cout << "d: " << d << ", " ;
  cout << "SUM1: " << sum1 << ", " ;
  cout << "SUM2: " << sum2 << endl;

  // Aufgabe 3

/*
	unordered_map<std::pair int, set<string>> my_map {};

	for_each(v.begin(), v.end(), [&my_map, &v] (const Spieler& spieler) {
		 my_map.insert(std::pair<int, set<string>> {spieler.get_groesse(), spieler.get_name()});
		});

*/

  //cout << "Min: " << [Min] << ", ";
  //cout << "Max: " << [Max] s< endl;

  return 0;
}
