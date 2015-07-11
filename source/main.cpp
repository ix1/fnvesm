#include "FNVESM.hpp"
#include "ESM/ESMTag.hpp"
#include "ESM/Record/Records.hpp"
#include "ESM/ESMStream.hpp"
#include "ESM/FalloutESM.hpp"
#include <iostream>

int main(int argc, char **argv) {    
    if(argc != 2) {
        std::cout << "USAGE: " << argv[0] << " <esm>" << std::endl;
        return -1;
    }
    
    ESM::FalloutESM mainESM(argv[1]);
    
    if (mainESM.IsOpen() == false) {
        auto loadMessages = mainESM.GetLoadMessages();
        
        std::cout << "There was an error loading the ESM. Messages: " << std::endl;
        
        for(auto itr = loadMessages.begin(); itr != loadMessages.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
        
        return -1;
    }

    std::cout << "statics:" << std::endl;
    
    for (auto itr = mainESM.GetStaticObjects().begin(); itr != mainESM.GetStaticObjects().end(); ++itr) {
        (*itr).second.ExportYAML(1, std::cout);
    }
    
    std::cout << std::endl;
    
    std::cout << "interiors:" << std::endl;
    
    for(auto itr = mainESM.GetCells().begin(); itr != mainESM.GetCells().end(); ++itr) {
        if ((*itr).second.IsInterior() == false)
            continue;
        
        (*itr).second.ExportYAML(1, std::cout);
    }
    
    std::cout << std::endl;
    
    std::cout << "worldspaces:" << std::endl;
    
    for(auto itr = mainESM.GetWorldspaces().begin(); itr != mainESM.GetWorldspaces().end(); ++itr) {
        (*itr).second.ExportYAML(1, std::cout, mainESM.GetCells());
    }
    
    return 0;
}
