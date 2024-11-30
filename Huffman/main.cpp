#include <iostream>
#include "HuffmanCoder.h"  

int main(int argc, char* argv[]) {
    
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] <<
        " [zap | unzap] inputFile outputFile\n";
        return 1;  
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    HuffmanCoder coder;  

    if (mode == "zap") {
        coder.encoder(inputFile, outputFile);
    } else if (mode == "unzap") {
        coder.decoder(inputFile, outputFile);

    } else {

        return 1;
    }

    return 0;
}
