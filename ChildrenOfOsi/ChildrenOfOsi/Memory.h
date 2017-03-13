#pragma once

#include "NPC.h"
#define ACTION 0
#define FACT 1

class Memory
{
private:
	int type;                //ACTION (0)                                       or           FACT (1)
	vector<NPC*> people;     //ACTIONS: length of 3 (did, received, for)                     FACTS: length of 2 (who about, who told)
	
	string category;         //ACTIONS: fail, success, incomplete                            FACTS: fact type (i.e. name, origin, etc)
	string content;          //ACTIONS: action name                                          FACTS: actual data (i.e. "Yemoja", "Oasis", etc)
	string where;            //ACTIONS: where the event occured                              
	int why;                 //ACTIONS: do-er's motivation (0=affinity, 1=strength, 2=notoriety, -1=idk)
	int when;                //ACTIONS: when the event occured (incomplete: when it started, complete: when it completed)
	string reason;           //ACTIONS: reason for failure or success

	int time;            //Memory formation timestamp: # frames since start of game

public:
	Memory(int t, int frames, vector<NPC*> p, string cat="",string cont="",string where="",int why=-1, int when=-1);
	~Memory();

	void setType(int t);
	int getType();

	void setPeople(vector<NPC*> p);
	vector<NPC*> getPeople();
	void setCategory(string c);
	string getCategory();
	void setContent(string c);
	string getContent();
	void setWhere(string w);
	string getWhere();
	void setWhy(int w);
	int getWhy();
	void setWhen(int w);
	int getWhen();
	void setReason(string r);
	string getReason();

	void setTime(int t);
	int getTime();


	//ACTIONS
	void doneBy(NPC* w);
	NPC* doer();
	void receivedBy(NPC* w);
	NPC* receiver();
	void instigatedBy(NPC* w);
	NPC* instigator();
	void changeStatus(string s);
	//string status();
	//string name();

	
	//FACTS
	void isAbout(NPC* w);
	NPC* who();
	void toldBy(NPC* w);
	NPC* source();

};

