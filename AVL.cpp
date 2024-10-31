#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include "AVL.h"

using namespace std;

int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

Node* newNode(string name, string id) {
    Node* node = new Node();
    node->name = name;
    node->ufid = stoi(id);
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return(node);
}

bool isValidInput(string input) {
    // check for non-alphanumeric characters
    for(char c : input) {
        if(!isalnum(c) && c != ' ' && c != '\"') {
            return false;
        }
    }

    // separate arguments into vector args
    string word = "";
    bool nameMode = false;
    vector<string> args = {};
    stringstream iss(input);
    while (iss >> word) {
        if (word.substr(0, 1) == "\"" && word.substr(word.size()-1) != "\"") {
                nameMode = true;
                args.push_back(word);
        }
        else if (nameMode == true) {
            if (word.substr(word.size()-1) == "\""){
                nameMode = false;
            }
            args[args.size()-1] += " " + word;
        }
        else
            args.push_back(word);
    }
    
    if(args.size() == 0 || args.size() > 4)
        return false;
    // validate command name
    vector<string> commandNames = {"insert", "remove", "search", "printInorder", "printPreorder", "printPostorder", "printLevelCount", "removeInorder"};
    if(find(commandNames.begin(), commandNames.end(), args[0]) == commandNames.end()) {
        return false;
    }

    // validates 0 argument commands
    if((args[0] == "printInorder" || args[0] == "printPreorder" || args[0] == "printPostorder" || args[0] == "printLevelCount") && args.size() == 1)
        return true;
    // validates 1 argument commands (NAME OR ID)
    if(args[0] == "remove" || args[0] == "search" || args[0] == "removeInorder") {
        // validate argument
        if(args.size() == 2) {
            if((args[0] == "search" || args[0] == "remove")) { // check for name on search command
                if(args[1][0] == '\"' && args[1][args[1].size()-1] == '\"' && args[1].size() > 2) {
                    for (int i = 1; i < args[1].size()-1; i++) {
                        if (!isalpha(args[1][i]) && args[1][i] != ' ')
                            return false;
                    }
                    return true;
                } 
                if (args[1].size() == 8) { // checks for valid UFID
                    try {
                        stoi(args[1]);
                        return true;
                    } 
                    catch (const std::invalid_argument& e) {
                        return false;
                    }
                }
            }
            else if (args[0] == "removeInorder" && args[1].size() >= 0) {
                try {
                    stoi(args[1]);
                    return true;
                } 
                catch (const std::invalid_argument& e) {
                    return false;
                }
            }
        }
    }
    // validates 2 argument command (NAME & ID)
    if (args.size() == 3) {
        if(args[0] == "insert" && args[1][0] == '\"' && args[1][args[1].size()-1] == '\"' && args[1].size() > 2) {
            if(args[2].size() == 8) {
                for (int i = 1; i < args[1].size()-1; i++) {
                    if (!isalpha(args[1][i]) && args[1][i] != ' ')
                        return false;
                }
                try {
                    stoi(args[2]);
                    return true;
                } catch (const std::invalid_argument& e) {
                    return false;
                }
            }
        }
    }
    return false;
}

int main() {
    AVLTree t;
    bool validInput = false;
    string input;
    string commandCount;
    getline(cin, commandCount);

    for(int i = 0; i < stoi(commandCount); i++) {
        getline(cin, input);
        // input validation
        while(!isValidInput(input)){
            cout << "unsuccessful\n";
            cin.clear();
            cin.sync();
            getline(cin, input);
        }

        string word = "";
        bool nameMode = false;
        vector<string> args = {};
        istringstream iss(input);
        while (iss >> word) {
            if (word.substr(0, 1) == "\"" && word.substr(word.size()-1) != "\"") {
                    nameMode = true;
                    args.push_back(word);
            }
            else if (nameMode == true) {
                if (word.substr(word.size()-1) == "\""){
                    nameMode = false;
                }
                args[args.size()-1] += " " + word;
            }
            else
                args.push_back(word);
        }

        if(args[0] == "insert") {
            if (!t.inTree(t.root, stoi(args[2]))) {
                t.insert(args[1].substr(1, args[1].size()-2), args[2]);
            }
            else
                cout << "unsuccessful\n";
        }
        else if(args[0] == "remove") {
            // t.remove(args[1]);
        }
        else if(args[0] == "search") {
            try {
                if (t.inTree(t.root, stoi(args[1]))) 
                    t.searchID(stoi(args[1])); // ID search
                else
                    cout << "unsuccessful\n";
            }
            catch (const std::invalid_argument& e) {
                if (t.inTree(t.root, args[1].substr(1, args[1].size()-2))) {
                    t.searchName(args[1].substr(1, args[1].size()-2)); // Name search
                }

                else
                    cout << "unsuccessful\n";
            }
        }
        else if(args[0] == "printInorder") {
            t.printInorder(t.root);
            cout << endl;
        }
        else if(args[0] == "printPreorder") {
            t.printPreorder(t.root);
            cout << endl;
        }
        else if(args[0] == "printPostorder") {
            t.printPostorder(t.root);
            cout << endl;
        }
        else if(args[0] == "printLevelCount") {
            t.printLevelCount(t.root);
        }
        else if(args[0] == "removeInorder") {
            cout << "removing inorder\n";
            // t.removeInorder(stoi(args[1]));
        }
        cin.clear();
        cin.sync();
    }

    return 0;
}

// sources and citations:
/*
https://stackoverflow.com/questions/6277646/in-c-check-if-stdvectorstring-contains-a-certain-value

https://www.geeksforgeeks.org/insertion-in-an-avl-tree/#

https://www.geeksforgeeks.org/introduction-to-avl-tree/#

https://www.tutorialspoint.com/cplusplus-program-to-implement-avl-tree

https://www.programiz.com/dsa/avl-tree
*/