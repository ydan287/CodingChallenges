#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <array>
#include <string>
#include <unordered_map>
#include <map>
#include<iomanip> 

using namespace std;
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	return split(s, delim, elems);
}

template <class T>
T stringTo(const std::string &str)
{
	T result;
	std::stringstream ss(str);
	ss >> result;
	return result;
}

template <class Ty, class Container>
std::vector<Ty> convertContainerTo(const Container &source)
{
	std::vector<Ty> result;
	std::for_each(source.begin(), source.end(),
		[&result](const std::string &it) { result.push_back(stringTo<Ty>(it)); });
	return result;
}

typedef unsigned int uint32_t;
typedef uint32_t IpAddress_t;

/** IP address mapping entry */
class IpAddressMapping {
public:
	std::string country;
	IpAddress_t startAddress;
};

/** Class for mapping IP addresses to countries using database
  * from http://software77.net/geo-ip/ */
class IpToCountry
{
	std::array<std::vector<IpAddressMapping>, 256> m_countryIpList;
	static unsigned char GetIndexFromAddress(IpAddress_t address)
	{
		return address >> (3 * 8);
	}

	IpAddressMapping GetCountryFromIndex(const IpAddress_t address, unsigned char index) const
	{
		const auto &list = m_countryIpList[index];
		auto it = std::find_if(list.rbegin(), list.rend(),
			[address](IpAddressMapping it) { return it.startAddress <= address; });
		if (it == list.rend())
			return GetCountryFromIndex(address, index - 1);
		return *it;
	}
public:
	/** Construct new IP-to-country mapper from the specified file. */
	IpToCountry(const std::string &FileName = "IpToCountry.csv")
	{
		std::ifstream file(FileName);
		int i = 1;
		while (file.good() && !file.eof())
		{
			if (i > 197061)
				break;
			std::string line;
			std::getline(file, line);
			if (line.find_first_of('#') == std::string::npos && line.length() > 0)
			{
				IpAddressMapping mapping = ParseSingleLine(line);
				m_countryIpList[GetIndexFromAddress(mapping.startAddress)].push_back(mapping);
			}

			++i;
		}
	}

	/** Find the country for given IP address or throw std::exception. */
	IpAddressMapping GetCountry(const std::string &address) const
	{
		IpAddress_t integerIp = IntegerFromIp(address);
		return GetCountryFromIndex(integerIp, GetIndexFromAddress(integerIp));
	}

	/** Convert a human-readable ipv4 address to integer */
	static IpAddress_t IntegerFromIp(const std::string &ip)
	{
		auto tokens = split(ip, '.');
		auto integers = convertContainerTo<uint32_t>(tokens);
		return (integers[0] << (3 * 8)) +
			(integers[1] << (2 * 8)) +
			(integers[2] << (1 * 8)) +
			integers[3];
	}

private:
	// File format:
	// "1464729600","1464860671","ripencc","1117497600","DE","DEU","Germany"
	static IpAddressMapping ParseSingleLine(const std::string &line)
	{
		IpAddressMapping mapping;
		auto tokens = split(line, ',');
		mapping.country = tokens[6].substr(1, tokens[6].length() - 2);
		mapping.startAddress = stringTo<uint32_t>(tokens[0].substr(1, tokens[0].length() - 2));
		return mapping;
	}
};

IpToCountry iptc;
class Log {
	string clientIP;
	string country;
	//string request_time;
	//string requset;
	//int status_code;
	//int response_size;
	//string refferer;
	//string identafication;
public:
	Log(const string& line) {
		auto tokens = split(line, ' ');
		clientIP = tokens[0];
		country = iptc.GetCountry(clientIP).country;
	}
	string getCountry() {
		return country;
	}
	string getOS() {
	
	}
	string getBrowser() {
	
	}
};

class features {
public:
	int counter;
};

class logFile {
	vector<Log> logs;
	unordered_map<string, features> countryTable;
	unordered_map<string, features> OSTable;
	unordered_map<string, features> BrowsersTable;
	unordered_map<string, features> MethodsTable;
public:
	logFile(const string& filename = "all") {
		ifstream file("all");
		int i = 1;
		while (file.good() && !file.eof()) {
			if (i > 40799) {
				break;
			}
			string line;
			getline(file, line);
			auto log = Log(line);
			logs.push_back(log);
			if (countryTable[log.getCountry()].counter == 0) {
				countryTable[log.getCountry()].counter = 1;
			}
			else {
				countryTable[log.getCountry()].counter += 1;
			}
			i++;
		}
	}
	void printCountryVisitPercentage (){
		double numUser = logs.size();
		map<double, string, greater <double> > m;
		for (auto country : countryTable) {
			m.insert({ country.second.counter, country.first });
		}
		for(auto it = m.rbegin() ; it!= m.rend(); ++it){
			cout << it->second << " - " << setprecision(2) <<((100.0*it->first) / numUser) << "%" << endl;
		}
	}
};

int main(int argc, char** argv) {
	auto logfile = logFile();
	logfile.printCountryVisitPercentage();
	
}