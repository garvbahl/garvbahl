//This file contains the class for HuffmanCoder which contains the 
//functionality
//for the Huffman encoder allowing me to encode the given text and serialize
//a tree or vice versa. A priority queue and vectors were used in this 
//assignment
//Author : Garv Bahl
//Assignment : zap
//Date : 11/19/2024
//Help received : N/A

#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <vector>
#include "HuffmanTreeNode.h"

class HuffmanCoder {
    private:
    void serialize_tree_helper(HuffmanTreeNode* root, std::string &oFile);
    bool serialize_tree(HuffmanTreeNode* root, const std::string &outputFile);
    void addCodes(HuffmanTreeNode* root,
    const std::string& str, std::vector<std::string>& codes);
    void deserialize_tree(HuffmanTreeNode*& root,
    const std::string inputstring, int &pos);
    // Feel free to add additional private helper functions as well as a
    // constructor and destructor if necessary
   public:
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);
};

#endif