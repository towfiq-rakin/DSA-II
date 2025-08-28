#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;
// Function to trim leading whitespace
void trimLeading(string &str) {
size_t start = str.find_first_not_of(" \t\r\n");
if (start != string::npos) {
str = str.substr(start);
} else {
str.clear(); // All whitespace
}
}
int main() {
ifstream file("input.txt");
if (!file) {
return 1;
cerr << "Error: Could not open input.txt" << endl;
}
string line;
cout << "Analyzing lines from input.txt:\n" << endl;
while (getline(file, line)) {
trimLeading(line);
if (line.empty()) continue;
// Remove trailing newline (getline does this already)
if (line.substr(0, 2) == "//") {
cout << "Line: \"" << line << "\"\n This is a single-line comment.\n" << endl;
}
else if (line.substr(0, 2) == "/*" && line.find("*/") != string::npos) {
cout << "Line: \"" << line << "\"\n This is a complete multi-line comment in one
line.\n" << endl;
}
else if (line.substr(0, 2) == "/*") {
cout << "Line: \"" << line << "\"\n This is the start of a multi-line comment.\n" <<
endl;
}
else if (line.find("*/") != string::npos) {
cout << "Line: \"" << line << "\"\n This is the end of a multi-line comment.\n" <<
endl;
}
else {
cout << "Line: \"" << line << "\"\n This is NOT a comment.\n" << endl;
}
}
file.close();
return 0;
}