cmake_minimum_required(VERSION 3.18)

project(Project_1945_by_Tronus LANGUAGES C)

#[[
  CMAKE_MODULE_PATH da usare quando cerco librerie di tipo MODULO (ovvero Find*.cmake)

  NOTA: E' piu' corretto settarlo fuori da CMakeLists.txt cosi da rendere l'esecuzione CMAKE
        indipendente dal workspace locale.
        => Settato nel file settings.json, cosi venga configurato dal plugin CMAKE
]] 
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake/")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/")


find_package(SDL2 MODULE REQUIRED)
find_package(SDL2_IMAGE MODULE REQUIRED)
find_package(SDL2TTF MODULE REQUIRED)
find_package(SDL2_MIXER MODULE REQUIRED)

if(SDL2_FOUND 
    AND SDL2_IMAGE_FOUND 
    AND SDL2TTF_FOUND 
    AND SDL2_MIXER_FOUND 
    )
    message(${SDL2_INCLUDE_DIR})
    message(${SDL2_LIBRARY})
    message(${SDL2_IMAGE_INCLUDE_DIR})
    message(${SDL2_IMAGE_LIBRARY})
    message(${SDL2TTF_INCLUDE_DIR})
    message(${SDL2TTF_LIBRARY})
    message(${SDL2_MIXER_INCLUDE_DIR})
    message(${SDL2_MIXER_LIBRARY})
endif()


#[[
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
  message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
]] 
FILE(GLOB MyCSources "src/*.c")
SET(WINDOWS_RESOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources/ui/appicon.rc)

add_executable(Project_1945_by_Tronus WIN32 ${MyCSources} ${WINDOWS_RESOURCE_PATH})

# link diretto sulla .lib
target_link_libraries(Project_1945_by_Tronus 
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARY}
  ${SDL2TTF_LIBRARY}
  ${SDL2_MIXER_LIBRARY}
) 
target_include_directories(Project_1945_by_Tronus 
  PRIVATE 

    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2TTF_INCLUDE_DIR} 
    ${SDL2_MIXER_INCLUDE_DIR}  
    include
)

#Per Windows: il file .exe ha bisogno della .dll vicino a se.

#NOTA: Differenziare la copia tra .dll di debug e .dll di release se esiste
if(WIN32) 
    include(GNUInstallDirs)
    set(SDL2_DLL ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2/lib/x64/SDL2.dll)
    file(GLOB SDL2IMAGE_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2_image/lib/x64/*.dll")
    file(GLOB SDL2ITTF_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2_ttf/lib/x64/*.dll")
    file(GLOB SDL2MIXER_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2_mixer/lib/x64/*.dll")
    set(DLL_LIST "${SDL2_DLL}" "${SDL2IMAGE_DLLS}" "${SDL2ITTF_DLLS}" "${SDL2MIXER_DLLS}")
   
    foreach(EACH_DLL ${DLL_LIST})
      add_custom_command(TARGET Project_1945_by_Tronus POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EACH_DLL} $<TARGET_FILE_DIR:Project_1945_by_Tronus>
      )
    endforeach()
  
endif(WIN32)

# Post build: Copy Resources to bin
set(ResourcesPath ${CMAKE_CURRENT_SOURCE_DIR}/resources)
add_custom_command(TARGET Project_1945_by_Tronus POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Copy Resources..."
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${ResourcesPath} $<TARGET_FILE_DIR:Project_1945_by_Tronus>/resources
    )