#include "FNVESM.hpp"
#include "ESM/ESMTag.hpp"
#include "ESM/Record/Records.hpp"
#include "ESM/ESMStream.hpp"
#include "ESM/FalloutESM.hpp"
#include <iostream>

int main(int argc, char **argv) {
    ESM::FalloutESM mainESM("");
    
    if (mainESM.IsOpen() == false) {
        auto loadMessages = mainESM.GetLoadMessages();
        
        for(auto itr = loadMessages.begin(); itr != loadMessages.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
        
        return -1;
    }
    
    //std::cout << "Successfully loaded." << std::endl;
    
    const auto scripts = mainESM.GetScripts();
    
    std::cout << "There are: " << scripts.size() << " scripts" << std::endl;
    std::cout << "There are: " << mainESM.GetGameSettings().size() << " settings" << std::endl;
    
    /*for(auto itr = scripts.begin(); itr != scripts.end(); ++itr) {
       auto pair = *itr;
       
       std::cout << "<script id=\"" << pair.second.GetEditorID() << "\" form=\"" << pair.first << "\">" << std::endl;
       
       std::cout << pair.second.GetScriptSource() << std::endl;
       
       std::cout << "</script>" << std::endl;
    }*/
    
    return 0;
}
