/*

some things to point out:
- code bad
i know
- code ugly
i know
- half the stocks dont show
im aware.
- why do random letters come up before numbers
cant be bothered to fix

i guess credit to geeksforgeeks.org for the removehtmltags thing

that should answer all your questions
*/

#include <iostream>
#include <Windows.h>
#include <string>
#include <WinInet.h>
#include <regex>

#pragma comment(lib, "wininet.lib")
using namespace std;

string replaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
std::string RemoveHTMLTags(string s)
{
	const regex pattern("\\<.*?\\>");

	// Use regex_replace function in regex
	// to erase every tags enclosed in <>
	s = regex_replace(s, pattern, "");

	// Print string after removing tags
	//cout << s;

	return s;
}

string DownloadURL(string URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}


int main()
{
	std::cout << "type the code of the stock or whatever its called (amzn for example)" << std::endl;
	std::string didnotusedtosaything;
	std::getline(std::cin, didnotusedtosaything);

	std::string web = "https://finviz.com/quote.ashx?t=" + didnotusedtosaything;
	std::string xddd = DownloadURL(web);
	xddd = RemoveHTMLTags(xddd);
	//std::cout << xddd;
	if (xddd.find("Index"))
	{
		std::string::size_type lol = xddd.find("Index");
		std::string::size_type lol2 = xddd.find("P/E");
		std::string hehehe = xddd.substr(lol + 5, 7);
		std::string pe = xddd.substr(lol2 + 3, 7);
		std::string::size_type tprice = xddd.find("Price");
		std::string tpric = xddd.substr(tprice + 5, 7);

		std::string::size_type rprice = xddd.find("Avg Volume");
		std::string pricee = xddd.substr(rprice + 21, 17);

		std::cout << "Index: " << hehehe << std::endl << "P/E: " << pe << std::endl << "Target Price: " << tpric << std::endl << "Actual Price: " << pricee << std::endl;
	}
	printf("done deal with it");
    return 0;
    
}


