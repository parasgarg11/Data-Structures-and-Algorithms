/*
Givan n number of words, you need to find if there exist any two words which can be joined to make a palindrome or any word itself is a palindrome.
Return true or false.
Input Format :

Line 1 : Integer n
Line 2 : n words (separated by space)

Output Format :

true ot false

Sample Input 1 :

4
abc def ghi cba

Sample Output 2 :

true

Sample Output 1 Expalanation :
"abc" and "cba" forms a palindrome
Sample Input 2 :

4
abc def ghi hg

Sample Output 2 :

true

Sample Output 2 Expalanation :
"ghi" and "hg" forms a palindrome
 */



#include <string>
#include <vector> 
class TrieNode {
	public :
	char data;
	TrieNode **children;
	bool isTerminal;
	int childCount;

	TrieNode(char data) {
		this -> data = data;
		children = new TrieNode*[26];
		for(int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isTerminal = false;
		childCount = 0;
	}
};

class Trie {
	TrieNode *root;

	public :
	int count;

	Trie() {
		this->count = 0;
		root = new TrieNode('\0');
	}

	bool insertWord(TrieNode *root, string word) {
		// Base case
		if(word.size() == 0) {
			if (!root->isTerminal) {
				root -> isTerminal = true;
				return true;	
			} else {
				return false;
			}
		}

		// Small Calculation
		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index] != NULL) {
			child = root -> children[index];
		}
		else {
			child = new TrieNode(word[0]);
			root -> children[index] = child;
			root->childCount++;
		}

		// Recursive call
		return insertWord(child, word.substr(1));
	}

	// For user
	void insertWord(string word) {
		if (insertWord(root, word)) {
			this->count++;
		}
	}

    string reverse(string in){
        string out="";
        for(int i=in.size()-1;i>=0;i--)
            out+=in[i];
        return out;
    }
    
    bool search(TrieNode* root,string word){
        
        if(word.size()==0 ){
            return root->isTerminal;
        }
        
        int index=word[0]-'a';
        
        bool ans;
        if(root->children[index]!=NULL)
            ans=search(root->children[index],word.substr(1));
        else
            ans=false;
        return ans;
    }
	

	bool findIfPalindromePair(vector<string> arr) {
		// Complete this function
		// Return true or false.
        
        //Store all the words first before searching it's reverse
        for(int i=0; i<arr.size(); i++){
            this->add(arr[i]);
        }
        
        bool ans;
        
        for(int i=0; i<arr.size(); i++){
            
            string out= arr[i];  // the word itself is a palindrome or not
            out = reverse(out);        
            ans = search(root, out);
            
            if(ans){
                return true;
            }
            
            int len = arr[i].length();
            string str = arr[i];
            int j=0;
            while(j<len-1){
                
                if(str[j]==str[j+1]){     // checking first mismatch char   e.g. mmmmabc
                    j++;
                }
                else{
                    break;
                }
            }
            
            out = str.substr(j+1);
            out = reverse(out);
            ans = search(root, out);

            if(ans)
                return true;
            
            //3rd case 
            str = arr[i];
            j=len-1;

            while(j>0){                
                if(str[j]==str[j-1]){    //checking first mismatch char e.g. abcmmmm
                    j--;
                }
                else{
                    break;
                }
            }
            
            out = str.substr(0, j);
            out = reverse(out);
            ans = search(root, out);
            
            if(ans){
                return true;
            }
        }
        return ans;
    }
};


#include <iostream>
#include <string>
using namespace std;
#include <vector>


int main() {
    Trie t;
    vector <string> vect;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;
        vect.push_back(word);
    }
    
    bool ans = t.findIfPalindromePair(vect);
    if (ans){
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}
