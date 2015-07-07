add_executable(fnvesm 
    ESM/Record/FalloutScript.hpp
    ESM/Record/FalloutScript.cpp
    ESM/Record/FieldParser.hpp
    ESM/Record/FieldParser.cpp
    
    ESM/Record/GameSetting.hpp
    ESM/Record/GameSetting.cpp
    ESM/Record/RecordHeader.hpp
    ESM/Record/Records.hpp
    ESM/Record/TextureSet.hpp
    ESM/Record/TextureSet.cpp
    
    
    ESM/ESMStream.hpp
    ESM/ESMStream.cpp
    ESM/ESMTag.hpp
    ESM/FalloutESM.hpp
    ESM/FalloutESM.cpp
    
    FNVESM.hpp
    main.cpp
)

install(TARGETS fnvesm RUNTIME DESTINATION bin)