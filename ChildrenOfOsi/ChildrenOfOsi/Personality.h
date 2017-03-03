#pragma once
class Personality
{
public:
	Personality();
	Personality(int a, int k,int h,int p,int r, int e, int g);
	~Personality();
	void getAggression(int a) { agg=a; };
	void getKindness(int k) { kind=k; };
	void getHonor(int h) { honor=h; };
	void getPride(int p) { pride=p; };
	void getRecklessness(int r) { reck=r; };
	void getExtraversion(int e) { extra=e; };
	void getGreed(int g) { greed=g; };
	int getAggression() { return agg; };
	int getKindness() { return kind; };
	int getHonor() { return honor; };
	int getPride() { return pride; };
	int getRecklessness() { return reck; };
	int getExtraversion() { return extra; };
	int getGreed() { return greed; };
private:
	int agg;
	int kind;
	int honor;
	int pride;
	int reck;
	int extra;
	int greed;
};

