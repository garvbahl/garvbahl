//This file contains the implementation for the HuffmanCoder class
//Author : Garv Bahl
//Assignment : zap
//Date : 11/19/2024
//Help received : N/A

#include "HuffmanCoder.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "HuffmanTreeNode.h"
#include <queue>
#include <string>
#include "ZapUtil.h"
#include <filesystem>
#include <ciso646>

//name: addCodes
//purpose: Recursively generate Huffman codes for each character in the 
//Huffman tree.
//arguments: HuffmanTreeNode* root (current node), const std::string& str
// (current code string), std::vector<std::string>& codes (array of codes)
//returns: n/a
//effects: Populates the codes vector where the index corresponds to the 
//character's ASCII value and the value at that index is the Huffman code.

void HuffmanCoder::addCodes(HuffmanTreeNode* root, const std::string& str,
std::vector<std::string>& codes){
    if (root == nullptr){
        return;
    }
    
    if (root->is_leaf()) {
        codes[static_cast<unsigned char>(root->get_val())] = str;
    } else {
        addCodes(root->get_left(), str + "0", codes);
        addCodes(root->get_right(), str + "1", codes);
    }

}


//name: serialize_tree
//purpose: Serializes the Huffman tree to a file.
//arguments: HuffmanTreeNode* root (the root of the Huffman tree), const 
//std::string &outputFile (file path to save the serialized tree)
//returns: bool (true if serialization was successful, false otherwise)
//effects: Writes the serialized form of the Huffman tree to the outputFile.
// If the file cannot be opened, returns false.

bool HuffmanCoder::serialize_tree(HuffmanTreeNode* root,
const std::string &outputFile){
    std::ofstream oFile(outputFile);
    if (not oFile.is_open()) {
        std::cerr << "Failed to open the file for writing: " << outputFile
        << std::endl;
        return false; 
    }
    std::string serialized_tree;
    serialize_tree_helper(root, serialized_tree); 

    oFile.close(); 
    return true;
}

//name: serialize_tree_helper
//purpose: Helper function to recursively serialize the Huffman tree into 
//a string.
//arguments: HuffmanTreeNode* root (current node), std::string &oFile 
//(string to append serialized data to)
//returns: n/a
//effects: Appends the serialized data of the Huffman tree to the string 
//oFile, using 'L' for leaves and 'I' for internal nodes.

void HuffmanCoder::serialize_tree_helper(HuffmanTreeNode* root,
 std::string &oFile){
   if (root == nullptr){
    return;
   }
    if (root->is_leaf()) {
        oFile += 'L';
        oFile += root->get_val();
    } else {
        oFile += 'I'; 
        serialize_tree_helper(root->get_left(), oFile);  
        serialize_tree_helper(root->get_right(), oFile); 
    }
}

//name: encoder
//purpose: Encodes the contents of an input file using Huffman coding and 
//writes the encoded data to an output file.
//arguments: const std::string &inputFile (file path of the input file), 
//const std::string &outputFile (file path to save the encoded data)
//returns: n/a
//effects: Reads the input file, builds a Huffman tree, generates Huffman 
//codes, and writes the encoded text to the output file. If the file cannot
// be opened, an error message is printed to cerr.

void HuffmanCoder::encoder(const std::string &inputFile,
 const std::string &outputFile){
    std::ifstream file(inputFile);
    if (not file.is_open()) {
        std::cerr << "Error opening file: " << inputFile << std::endl;
        return;
    }
    std::ofstream oFile(outputFile);
    if (not oFile.is_open()) {
        std::cerr << "Failed to open file for writing: "
         << outputFile << std::endl;
        return;
    }

    std::vector<int> frequencies(256,0);
    char ch;

    while (file.get(ch)) {
    frequencies[static_cast<unsigned char>(ch)]++;  
}

    file.close();

    if (std::filesystem::is_empty(inputFile)) {
        std::cout << inputFile << " is empty and cannot be compressed.\n";
        return;
    }

    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>,
    NodeComparator> pq;

    for (int i = 0; i < 256;i++){
        if (frequencies[i] > 0){
            if (i == '\n'){
                pq.push(new HuffmanTreeNode('\n', frequencies[i]));

            }else{
                pq.push(new HuffmanTreeNode(static_cast<char>(i),
                frequencies[i]));
            }
        }
    }

    while (pq.size() > 1){
        HuffmanTreeNode* left = pq.top();
        pq.pop();
        HuffmanTreeNode* right = pq.top();
        pq.pop();
        int sum = left->get_freq() + right->get_freq();
        pq.push(new HuffmanTreeNode('\0',sum,left,right));
    }

    HuffmanTreeNode* root = pq.top();
    std::string serialized_tree;
    serialize_tree_helper(root, serialized_tree);


    std::vector<std::string> codes(256);
    addCodes(root, "", codes);
    std::string encodedStr;

    file.open(inputFile);
    while(file.get(ch)){
        if (not codes[ch].empty()){
            encodedStr += codes[ch];
        }
    }
    std::cout<<"Success! Encoded given text using " << encodedStr.size()
     << " bits."<<std::endl;
    writeZapFile(outputFile, serialized_tree,encodedStr);

}

//name: deserialize_tree
//purpose: Recursively reconstructs a Huffman tree from a serialized string.
//arguments: HuffmanTreeNode*& root (reference to the root node pointer), 
//const std::string stringinput (serialized string input), int& pos 
//(current position in the string)
//returns: n/a
//effects: Constructs the Huffman tree based on the serialized data starting
//from the current position. Updates the position index as it progresses 
//through the string.

void HuffmanCoder::deserialize_tree(HuffmanTreeNode*& root,
const std::string stringinput, int& pos){
    
    if (pos >= int(stringinput.length())) {
        return; 
    }

    char type = stringinput[pos++]; 

    if (type == 'L') {
        if (pos < int(stringinput.length())) {
            char ch = stringinput[pos++];
            root = new HuffmanTreeNode(ch, 0); 
        }
    } else if (type == 'I') {
        HuffmanTreeNode* left = nullptr;
        HuffmanTreeNode* right = nullptr;

        deserialize_tree(left, stringinput, pos); 
        deserialize_tree(right, stringinput, pos); 

        root = new HuffmanTreeNode(0, left, right); 
    }
    else{
        root = new HuffmanTreeNode(stringinput[pos], 0);
    }
}

//name: decoder
//purpose: Decodes a Huffman encoded string using the tree reconstructed from 
//a serialized representation.
//arguments: const std::string &inputFile (file path containing the serialized
//tree and encoded data), const std::string &outputFile (file path to save 
//the decoded text)
//returns: n/a
//effects: Reads the serialized tree and encoded data from inputFile, 
//reconstructs the Huffman tree, decodes the encoded string, and writes 
//the decoded text to outputFile. If errors occur during tree construction or
//decoding,
//an exception is thrown or error messages are printed to cerr.

void HuffmanCoder::decoder(const std::string &inputFile,
const std::string &outputFile){
    std::pair<std::string, std::string> zapData;
    zapData = readZapFile(inputFile);
    std::string encodedStr = zapData.second;

    HuffmanTreeNode* root = nullptr;
    int pos = 0;
    deserialize_tree(root, zapData.first, pos);
    

    std::ifstream iFile(inputFile);
    if (not iFile.is_open()) {
        std::cerr << "Failed to open the input file: " <<
         inputFile << std::endl;
        return;
    }

    std::ofstream oFile(outputFile);
    if (not oFile.is_open()) {
        std::cerr << "Failed to open the output file: " <<
         outputFile << std::endl;
        return;
    }

    
    if (not root) {
        std::cerr << "Failed to deserialize the Huffman tree." << std::endl;
        iFile.close();
        oFile.close();
        return;
    }

    std::string decodedText;
    HuffmanTreeNode* currentNode = root;


    for (char bit : encodedStr) {
        if (currentNode == nullptr){
            oFile.close();
            throw std::runtime_error("Encoding did not match Huffman tree.");
            return;
        }
        if (bit == '0') {
            currentNode = currentNode->get_left();
        } else if (bit == '1') {
            currentNode = currentNode->get_right();
        }

        if (not currentNode) {
            throw std::runtime_error("Encoding did not match Huffman tree.");
            return;
        }

        if (currentNode->is_leaf() and currentNode) {
            decodedText.push_back(currentNode->get_val());
            currentNode = root; 
        }
    }
    
    if (currentNode != root) {
        oFile.close();
        throw std::runtime_error("Encoding did not match Huffman tree.");
        return;
    }

    oFile << decodedText;
    oFile.close();
}