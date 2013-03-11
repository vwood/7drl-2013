#include <iostream>
#include <fstream>
#include <cstring>

using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

bool parse(const char *filename) {
	char buf[MAX_CHARS_PER_LINE];
    ifstream fin;
	fin.open(filename);

    // Handle file not found
	if (!fin.good()) {
		return false; 
	}

	while (!fin.eof()) {
		fin.getline(buf, MAX_CHARS_PER_LINE);

		const char* token_ptrs[MAX_TOKENS_PER_LINE] = {};
    
		token_ptrs[0] = strtok(buf, DELIMITER); // read first token

		int token_count = 0;
        
		if (token_ptrs[0]) {
            token_count = 1;
			while (token_count < MAX_TOKENS_PER_LINE) {
				token_ptrs[token_count] = strtok(0, DELIMITER); // subsequent tokens
				if (!token_ptrs[token_count]) {
                    break; // no more tokens
                }
                token_count++;
			}
		}

		for (int i = 0; i < token_count; i++) {
            cout << "Token[" << i << "] = " << token_ptrs[i] << endl;
		}
		cout << endl;
	}
    
	return true;
}
