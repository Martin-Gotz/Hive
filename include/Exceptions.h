#pragma once
#include <string>


using namespace std;

namespace JeuHive {

	class HiveException {
	private:
		string info;
	public:
		HiveException(const string& a) : info(a) {}
		string getInfo() const { return info; }
	};
}