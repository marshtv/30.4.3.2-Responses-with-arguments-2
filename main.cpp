#include <iostream>
#include <cpr/cpr.h>

int main() {
	cpr::Response get, post;
	std::string key, value;
	std::map<std::string, std::string> oParams;
	std::cout << R"(Input parameters of responses or "get"/"post" for do response.)" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "Input key:";
	std::cin >> key;
	while (key != "get" && key != "post") {
		std::cout << "Input value:";
		std::cin >> value;
		std::pair<std::string, std::string> oPair;
		oPair.first = key;
		oPair.second = value;
		oParams.insert(oPair);

		std::cout << "-------------------------" << std::endl;
		std::cout << "Input key:";
		std::cin >> key;
	}
	if (key == "get" || value == "get") {
		std::string in_param;
		for (auto it = oParams.begin(); it != oParams.end(); it++) {
			in_param += it->first + "=" + it->second;
			if (it++ != oParams.end())
				in_param += "&";
		get = cpr::Get(cpr::Url("https://httpbin.org/get?" + in_param));

			std::cout << get.text;
			std::cout << "----------------------------------------------------------------------------" << std::endl;
		}
	}
	if (key == "post" || value == "post") {
		/*auto it = oParams.begin();
		post = cpr::Post(cpr::Url("https://httpbin.org/post"),
						 cpr::Payload({it = oParams.begin(), it = oParams.end()}));
		std::cout << post.text;
		std::cout << "----------------------------------------------------------------------------" << std::endl;*/

		for (auto it = oParams.begin(); it != oParams.end(); it++) {
			post = cpr::Post(cpr::Url("https://httpbin.org/post"),
							 cpr::Payload({{it->first, it->second}}));
			std::cout << post.text;
			std::cout << "----------------------------------------------------------------------------" << std::endl;
		}

	}
}