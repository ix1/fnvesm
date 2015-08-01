add_executable(fnvesm 
    ESM/Record/Cell.hpp
    ESM/Record/Cell.cpp
    
    ESM/Record/FalloutScript.hpp
    ESM/Record/FalloutScript.cpp
    
    ESM/Record/FieldParser.hpp
    ESM/Record/FieldParser.cpp
    
    ESM/Record/GameSetting.hpp
    ESM/Record/GameSetting.cpp
    
    ESM/Record/LandDefinition.hpp
    ESM/Record/LandDefinition.cpp
    
    ESM/Record/ModelData.hpp
    ESM/Record/ModelData.cpp
    
    ESM/Record/RecordHeader.hpp
    ESM/Record/Records.hpp
    
    ESM/Record/StaticObject.hpp
    ESM/Record/StaticObject.cpp
    
    ESM/Record/TextureSet.hpp
    ESM/Record/TextureSet.cpp
    
    ESM/Record/WorldObject.hpp
    ESM/Record/WorldObject.cpp
    
    ESM/Record/Worldspace.hpp
    ESM/Record/Worldspace.cpp
    
    ESM/Record/Message.hpp
    ESM/Record/Message.cpp

    ESM/ESMStream.hpp
    ESM/ESMStream.cpp
    
    ESM/ESMTag.hpp
    
    ESM/ESMUtility.hpp
    ESM/ESMUtility.cpp
    
    ESM/FalloutESM.hpp
    ESM/FalloutESM.cpp
    
    FNVESM.hpp
    main.cpp
)

target_link_libraries(fnvesm z)

install(TARGETS fnvesm RUNTIME DESTINATION bin)