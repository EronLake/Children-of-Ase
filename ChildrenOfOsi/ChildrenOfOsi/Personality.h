#pragma once
class Personality
{
public:
	Personality();
	Personality(int a, int k,int h,int p,int r, int e, int g);
	~Personality();
	void setAggression(int a) { agg=a; };
	void setKindness(int k) { kind=k; };
	void setHonor(int h) { honor=h; };
	void setPride(int p) { pride=p; };
	void setRecklessness(int r) { reck=r; };
	void setExtroversion(int e) { extro=e; };
	void setGreed(int g) { greed=g; };
	int getAggression() { return agg; };
	int getKindness() { return kind; };
	int getHonor() { return honor; };
	int getPride() { return pride; };
	int getRecklessness() { return reck; };
	int getExtroversion() { return extro; };
	int getGreed() { return greed; };
private:
	int agg;
	int kind;
	int honor;
	int pride;
	int reck;
	int extro;
	int greed;
};

