#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"
#include "RPNCalc.h"

// void test_empty(){
//     DatumStack stack;
//     assert(stack.isEmpty());
// }

// void test_pushandtop(){
//     DatumStack stack;
//     stack.push(Datum(5));
//     assert(stack.top().getInt() == 5);
// }

// void test_pop(){
//     DatumStack stack;
//     stack.push(Datum(5));
//     stack.push(Datum(6));
//     stack.pop();
//     assert(stack.top().getInt() == 5);
//     stack.pop();
//     assert(stack.isEmpty());
// }

// void test_top_throw(){
//     DatumStack stack;
//     try{
//         stack.top();
//         assert(false);
//     }catch(const std::runtime_error& e){
//         assert(std::string(e.what()) == "empty_stack");
//     }
// }

// void test_pop_throw(){
//     DatumStack stack;
//     try{
//         stack.pop();
//         assert(false);
//     }catch(const std::runtime_error& e){
//         assert(std::string(e.what()) == "empty_stack");
//     }
// }

void test_simpleRString() {
    std::istringstream input("1 2 + } ");
    std::string expected = "{ 1 2 + }";
    assert(parseRString(input) == expected);
}

// void test_nestedRString() {
//     std::istringstream input("{ 1 2 + } { 3 4 + } - }");
//     std::string expected = "{ { 1 2 + } { 3 4 + } - }";
//     assert(parseRString(input) == expected);
// }

// void test_unbalancedBraces() {
//     std::istringstream input("{ 1 2 } +");
//     try {
//         parseRString(input);
//         assert(false); 
//     } catch (const std::runtime_error& e) {
//         assert(std::string(e.what()) == "Unmatched braces in input");
//     }
// }

// void test_crazySpaces(){
//     std::istringstream input("1                                  2 + }");
//     std::string expected = "{ 1 2 + }";
//     assert(parseRString(input) == expected);
// }

// void test_processCommand_numbers() {
//     RPNCalc calc;
//     calc.processCommand("5");
//     calc.processCommand("3");
//     assert(calc.stack.top().getInt() == 3);
//     assert(calc.stack.size() == 2);
    
// }

// void test_processCommand_addition() {
//     RPNCalc calc;
//     calc.processCommand("5 3 +");
//     assert(calc.stack.top().getInt() == 8);
//     assert(calc.stack.size() == 1);
    
// }

// void test_processCommand_subtraction() {
//     RPNCalc calc;
//     calc.processCommand("10 2 -");
//     assert(calc.stack.top().getInt() == 8);
    
// }

// void test_processCommand_multiplication() {
//     RPNCalc calc;
//     calc.processCommand("4 6 *");
//     assert(calc.stack.top().getInt() == 24);
    
// }

// void test_processCommand_division() {
//     RPNCalc calc;
//     calc.processCommand("20 5 /");
//     assert(calc.stack.top().getInt() == 4);
// }

// void test_processCommand_divisionByZero() {
//     RPNCalc calc;
//     try{
//         calc.processCommand("20 0 /");
//         assert(false);
//     }catch(const std::runtime_error& e){
//     }
//     assert(calc.stack.size() == 0);
// }

// void test_mod(){
//     RPNCalc calc;
//     calc.processCommand("17 5 mod");
//     assert(calc.stack.top().getInt() == 2);
// }

// void test_processCommand_invalidInput() {
//     RPNCalc calc;
//     try {
//         calc.processCommand("10 2 ^");  
//         assert(false);  
//     } catch (const std::runtime_error& e) {
//     }
// }

// void test_comparison_less(){
//     RPNCalc calc;
//     calc.processCommand("3 4 <");
//     assert(calc.stack.top().getBool() == true);
//     calc.stack.clear();

//     calc.processCommand("4 3 <");
//     assert(calc.stack.top().getBool() == false);
// }

// void test_comparison_more(){
//     RPNCalc calc;
//     calc.processCommand("3 4 >");
//     assert(calc.stack.top().getBool() == false);
//     calc.stack.clear();

//     calc.processCommand("4 3 >");
//     assert(calc.stack.top().getBool() == true);
// }

// void test_comparison_less2(){
//     RPNCalc calc;
//     calc.processCommand("3 4 <=");
//     assert(calc.stack.top().getBool() == true);
//     calc.stack.clear();
//     calc.processCommand("4 4 <=");
//     assert(calc.stack.top().getBool() == true);
//     calc.processCommand("4 3 <=");
//     assert(calc.stack.top().getBool() == false);
// }

// void test_comparison_more2(){
//     RPNCalc calc;
//     calc.processCommand("4 3 >=");
//     assert(calc.stack.top().getBool() == true);
//     calc.processCommand("4 4 >=");
//     assert(calc.stack.top().getBool() == true);
//     calc.stack.clear();
//     calc.processCommand("3 4 >=");
//     assert(calc.stack.top().getBool() == false);
// }

// void test_comparison_equal(){
//     RPNCalc calc;
//     calc.processCommand("4 4 ==");
//     assert(calc.stack.top().getBool() == true);
//     calc.processCommand("4 3 ==");
//     assert(calc.stack.top().getBool() == false);
// }

