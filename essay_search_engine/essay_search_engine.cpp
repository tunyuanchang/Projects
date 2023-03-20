#define FILE_EXTENSION ".txt"
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
//#include<windows.h>

using namespace std;
const int ALPHABET_SIZE = 27;
map<string, int> dict;
vector< set<unsigned int> > container;
unsigned int N = 0, idx = 0;

// Utility Func
vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch)) new_str.push_back(ch);
		}
		parse_string.emplace_back(new_str);
	}
	return parse_string;
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if(str == "") return res;

	char *strs = new char[str.length() + 1];
	strcpy(strs, str.c_str());

	char *d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p;
		res.push_back(s);
		p = strtok(NULL, d);
	}
	return res;
}

struct TrieNode{
    int num;
    TrieNode *children[ALPHABET_SIZE];
};

TrieNode *getNode(void){
	TrieNode *Node = new TrieNode;

	Node->num = -1;
	for(int i = 0; i < ALPHABET_SIZE; i++) Node->children[i] = NULL;

	return Node;
}

int insert(TrieNode *root, string key){
	TrieNode *now = root;
	for(int i = 0; i < key.length(); i++){

		int index = (!isalpha(key[i])) ?26 :(isupper(key[i])) ?key[i] - 'A' :key[i] - 'a';

		if(!now->children[index]) now->children[index] = getNode();
		now = now->children[index];
	}
    return now->num = (now->num == -1) ?N++ :now->num;
}

void search(TrieNode *root, string word){
	TrieNode *now = root;
	for(int i = 0; i < word.length(); i++){
		int index =  (!isalpha(word[i])) ?26 :(isupper(word[i])) ?word[i] - 'A' :word[i] - 'a';

		if(now->num != -1) container[now->num].insert(idx);
		if(!now->children[index]) return;
		now = now->children[index];
	}
	if(now->num != -1) container[now->num].insert(idx);
	return;
}

int main(int argc, char *argv[]){

	//DWORD star_time = GetTickCount();

    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);

	string tmp, str;
	vector<string> tmp_string, query_string;
	fstream fi, fo, q;

	TrieNode *root = getNode();

	//input
	//query
	q.open(query, ios::in);

	while(getline(q, tmp)){
		query_string.push_back(tmp);

		tmp_string = split(tmp, " ");

		for(auto &word: tmp_string){
			switch(word[0]){
				case '"':
					str = word;
                    str.assign(++str.begin(), str.end());
                    dict[word] = insert(root, str);
					break;
				case '*':
					str = word;
                    str.assign(str.rbegin(), --str.rend());
                    dict[word] = insert(root, str);
					break;
				default:
					dict[word] = insert(root, word);
					break;
				case '+': break;
				case '/': break;
			}
		}
	}

	q.close();

	//container
	for(int i = 0 ; i < N ; i++) container.push_back({});

	//search
    string filepath, title_name;
	vector<string> name;
    char s[10];

	//data
    while(1){
        fstream fi;
        sprintf(s,"%d",idx);
        filepath = data_dir + s + ".txt";
        fi.open(filepath, ios::in);
        if(!fi) break;
		
		getline(fi, title_name);
		name.push_back(title_name);
		tmp_string = split(title_name, " ");
		vector<string> title = word_parse(tmp_string);

		for(auto &word: title){
			word += "$";
			search(root, word);
            word.assign(word.rbegin(), word.rend());
            search(root, word);
		}

		while(getline(fi, tmp)){
			tmp_string = split(tmp, " ");
			vector<string> content = word_parse(tmp_string);

			for(auto &word: content){
				word += "$";
                search(root, word);
                word.assign(word.rbegin(), word.rend());
                search(root, word);
            }
		}

		fi.close();
		idx++;
    }
	
	//output
	fo.open(output, ios::out);

	for(auto q_str: query_string){
		tmp_string = split(q_str, " ");

		set<unsigned int> result = container[dict[tmp_string[0]]];

		for(int i = 2 ; i < tmp_string.size() ; i += 2){
			set<unsigned int> operation;
			if(tmp_string[i - 1] == "+")
				set_intersection(result.begin(), result.end(), 
								container[dict[tmp_string[i]]].begin(), container[dict[tmp_string[i]]].end(), 
								inserter(operation, operation.begin()));
            else
				set_union(result.begin(), result.end(), 
						  container[dict[tmp_string[i]]].begin(), container[dict[tmp_string[i]]].end(), 
						  inserter(operation, operation.begin()));
			result = operation;
		}

		if(result.size()) for(auto i: result) fo << name[i] << '\n';
		else fo << "Not Found!" << '\n';
	}

	fo.close();

	//DWORD end_time = GetTickCount();
	//cout << "timeout: " << (end_time - star_time) << "ms." << endl;
	return 0;
}
