//This file contains the implementation for phaseOne.h
//Author : Garv Bahl
//Assignment : zap
//Date : 11/10/2024
//Help received : n/a

#include "phaseOne.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>


//name : count_freqs()
//purpose : process the input stream to find their characters and their 
//given frequencies. 
//arguments : std::istream &text
//returns : n/a
//effects : prints out the character and its frequency.
void count_freqs(std::istream &text){
    std::vector<int> frequencies(256,0);
    char ch;

    while (text.get(ch)){
        frequencies[ch]++;
    }
    for (int i = 0; i < 256;i++){
        if (frequencies[i] > 0){
            if (i == '\n'){
                std::cout<<std::endl;
                std::cout << ": " << frequencies[i] << std::endl;
                HuffmanTreeNode* node = new HuffmanTreeNode('\n',frequencies[i]);

            }else{
                std::cout << char(i) << ": " << frequencies[i] << 
                std::endl;
                HuffmanTreeNode* node = new HuffmanTreeNode(char(i),frequencies[i]);
            }
        }
    }
}

//name : serialize_tree()
//purpose : recursively traverses the tree and serializes it.
//arguments : a pointer to the root node of the tree.
//returns : a std::string that represents the serialized form of the Huffman
//tree.
//effects : n/a
std::string serialize_tree(HuffmanTreeNode *root){
    std::string result;
    if (!root){
        return result;
    }

    if (root->is_leaf()){
        result += "L";
        result += root->get_val();
    } else{
        result += "I";
        result += serialize_tree(root->get_left());
        result += serialize_tree(root->get_right());
    }
    return result;

}

//name : deserialize_tree()
//purpose : take a serialized string that represents a Huffman tree structure
//and convert it back into a Huffman tree data structure.
//arguments : a reference to a constant string that contains the serialized 
//form of a Huffman tree.
//returns : a pointer to the root of the reconstructed Huffman tree
//effects : if the input string is empty it returns a nullptr.
HuffmanTreeNode* deserialize_tree(const std::string &serial_tree){
    std::vector<HuffmanTreeNode*> nodes;

    for (int i = 0; i < int(serial_tree.size());i++){
        if (serial_tree[i] == 'L'){
            if(i++ < serial_tree.size()){
                nodes.push_back(new HuffmanTreeNode(serial_tree[i])); 
            }  
        } else if (serial_tree[i] == 'I' && (i + 4) < int(serial_tree.size())){
            nodes.push_back(new HuffmanTreeNode('\0'));
        }
    }

    for (int i = 0; i < int(nodes.size()); i++){
        if (nodes[i]->get_val() == '\0' && (i+2) < int(nodes.size())){
            nodes[i]->set_left(nodes[i+1]);
            nodes[i]->set_right(nodes[i+2]);
            i+=2;
        }
    }
    if (nodes.empty()){
        return nullptr;
    }
    else{
        return nodes.front();
    }
}
    
    