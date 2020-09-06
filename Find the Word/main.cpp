#include <bits/stdc++.h>
using namespace std;

// Structure for Trie
struct Trie {
	bool isEndOfWord;
	unordered_map<char, Trie*> map;
	string meaning;
};

// Function to create a new Trie node
Trie* getNewTrieNode()
{
	Trie* node = new Trie;
	node->isEndOfWord = false;
	return node;
}

// Function to insert a word with its meaning
// in the dictionary built using a Trie
void insert(Trie*& root, const string& str, const string& meaning)
{
	// If root is null
	if (root == NULL)
		root = getNewTrieNode();

	Trie* temp = root;
	for (int i = 0; i < str.length(); i++) {
		char x = str[i];

		// Make a new node if there is no path
		if (temp->map.find(x) == temp->map.end())
			temp->map[x] = getNewTrieNode();

		temp = temp->map[x];
	}

	// Mark end of word and store the meaning
	temp->isEndOfWord = true;
	temp->meaning = meaning;
}

// Function to search a word in the Trie
// and return its meaning if the word exists
string getMeaning(Trie* root, const string& word)
{
	// If root is null i.e. the dictionary is empty
	if (root == NULL)
		return "";

	Trie* temp = root;

	// Search a word in the Trie
	for (int i = 0; i < word.length(); i++) {
		temp = temp->map[word[i]];
		if (temp == NULL)
			return "";
	}

	// If it is the end of a valid word stored
	// before then return its meaning
	if (temp->isEndOfWord)
		return temp->meaning;
	return "";
}

// Driver code
int main()
{
	Trie* root = NULL;

	string path = "EnglishDictionary.csv";
    // Open the file with the given pathname
    ifstream openFile (path);

    string key;
    string value;

    // This while loop will iterate through the CSV file and store the corresponding values in the dictionary
    while (true) {
        // Terminating Condition
        if (!getline(openFile, key, ',')) break;

        // Get the Value from the file
        getline(openFile, value, '\n');

        insert(root, key, value);
    }

    // Take Input from User
	string str;
	cin >> str;
	// Convert it to lowercase as the compare operator deals only with lowercase files
	transform(str.begin(), str.end(), str.begin(), ::tolower);

	string ans = getMeaning(root, str);

	if (ans.size() > 0 ) {
        cout << "YES, " << ans;
	} else {
        cout << "NO";
	}
}
