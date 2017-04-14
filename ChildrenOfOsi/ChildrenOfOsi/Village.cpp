#include "stdafx.h"
#include "Village.h"
using namespace std;

vector<Village*> Village::villagesWorld;

Village::Village()
{
  Village::villagesWorld.push_back(this);
  this->barracks.push_back(new Party());
  this->parties.push_back(this->barracks[0]);
}

Village::~Village()
{
  delete this->barracks[0];
}

bool Village::isEnemyParty(Party* p)
{
  for(auto i = enemy_parties.begin(); i != enemy_parties.end(); ++i) {
    if(p == (*i))return true;
  }
  return false;
}

void Village::remove_party(Party* p)
{
  parties.erase(std::remove(parties.begin(), parties.end(), p), parties.end());
}

void Village::remove_enemy_party(Party* p)
{
  enemy_parties.erase(std::remove(enemy_parties.begin(), enemy_parties.end(), p), enemy_parties.end());
}

void Village::remove_member(NPC* n)
{
  if(!this->members.empty())
    this->members.erase(std::remove(this->members.begin(), this->members.end(), n));
}
