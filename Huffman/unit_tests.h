#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <ciso646>

void test_count_freqs() {
    std::istringstream text("hello world");
    std::ostringstream output;

    std::streambuf *original_cout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    count_freqs(text);

    std::cout.rdbuf(original_cout);

    std::string expected = " : 1\nd: 1\ne: 1\nh: 1\nl: 3\no: 2\nr: 1\nw: 1\n";
    assert(output.str() == expected and "test_count_freqs failed");
    std::cout << "test_count_freqs passed!" << std::endl;
}


HuffmanTreeNode* create_sample_tree() {
    HuffmanTreeNode* leftLeaf = new HuffmanTreeNode('a', 1);
    HuffmanTreeNode* rightLeaf = new HuffmanTreeNode('b', 1);

    return new HuffmanTreeNode('\0', 2, leftLeaf, rightLeaf);
}

void test_serialize_tree() {
    HuffmanTreeNode* root = create_sample_tree();
    std::string result = serialize_tree(root);
    std::string expected = "ILaLb";

    assert(result == expected and "test_serialize_tree failed");
    std::cout << "test_serialize_tree passed!" << std::endl;

    delete root->get_left();
    delete root->get_right();
    delete root;
}

void test_deserialize_tree() {
    std::string serialized = "ILaLb";
    HuffmanTreeNode* root = deserialize_tree(serialized);

    assert(root != nullptr);
    assert(root->get_left() != nullptr);
    assert(root->get_right() != nullptr);
    assert(not root->is_leaf());
    assert(root->get_left()->get_val() == 'a');
    assert(root->get_right()->get_val() == 'b');

    std::cout << "test_deserialize_tree passed!" << std::endl;

    delete root->get_left();
    delete root->get_right();
    delete root;
}

void test_count_freqs_empty_input() {
    std::istringstream empty_input("");
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    count_freqs(empty_input);
    assert(output.str().empty() and "Output should be empty for empty input");

    std::cout.rdbuf(old_cout); 
    std::cout << "test_count_freqs_empty_input passed!" << std::endl;
}

void test_count_freqs_simple_input() {
    std::istringstream simple_input("abc");
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    count_freqs(simple_input);
    std::string expected = "a: 1\nb: 1\nc: 1\n";
    assert(output.str() == expected and
    "Frequency count is incorrect for simple input");

    std::cout.rdbuf(old_cout);
    std::cout << "test_count_freqs_simple_input passed!" << std::endl;
}

void test_count_freqs_repeated_characters() {
    std::istringstream repeated_input("aaabb");
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    count_freqs(repeated_input);
    std::string expected = "a: 3\nb: 2\n";
    assert(output.str() == expected and
    "Frequency count is incorrect for repeated characters");

    std::cout.rdbuf(old_cout);
    std::cout << "test_count_freqs_repeated_characters passed!" << std::endl;
}

void test_count_freqs_complex_input() {
    std::istringstream complex_input("ab!c a?");
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    count_freqs(complex_input);
    std::string expected = " : 1\n!: 1\n?: 1\na: 2\nb: 1\nc: 1\n";
    assert(output.str() == expected and
    "Frequency count is incorrect for complex input");

    std::cout.rdbuf(old_cout);
    std::cout << "test_count_freqs_complex_input passed!" << std::endl;
}

void test_count_freqs_newline_and_whitespace() {

    std::string input_string = "Test input\n\n   ";  
    std::istringstream input(input_string);
    
    std::ostringstream captured_output;
    std::streambuf* old_cout = std::cout.rdbuf(captured_output.rdbuf());

    count_freqs(input);

    std::cout.rdbuf(old_cout);

    std::string expected_space = " : 4\n";
    std::string expected_newline = ": 2\n"; 
    
    std::string output = captured_output.str();
    assert(output.find(expected_space) != std::string::npos and
     "Space frequency should be correctly output.");
    assert(output.find(expected_newline) != std::string::npos and
     "Newline frequency should be correctly output.");

    std::cout << "test_count_freqs_newline_and_whitespace passed!" 
    << std::endl;
}

void test_count_freqs_hi_input() {
    // Set up the input string as given in the example
    std::string input_string = "hi hi\nhi";
    std::istringstream input(input_string);

    // Capture the output
    std::ostringstream captured_output;
    std::streambuf* old_cout = std::cout.rdbuf(captured_output.rdbuf());

    // Call the function
    count_freqs(input);

    // Restore cout to its original state
    std::cout.rdbuf(old_cout);

    // Expected outputs
    std::string expected_h = "h: 3\n";
    std::string expected_i = "i: 3\n";
    std::string expected_space = " : 1\n";
    std::string expected_newline = "\n: 1\n"; 

    std::string output = captured_output.str();

    assert(output.find(expected_h) != std::string::npos and
     "Frequency of 'h' should be correctly output.");
    assert(output.find(expected_i) != std::string::npos and
     "Frequency of 'i' should be correctly output.");
    assert(output.find(expected_space) != std::string::npos and
     "Frequency of space should be correctly output.");
    assert(output.find(expected_newline) != std::string::npos and
    "Frequency of newline should be correctly output.");
}




