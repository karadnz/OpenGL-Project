cmake_minimum_required(VERSION 3.10)

include(CMakePrintHelpers)  #cmake_print_variable   fonksiyonu için

project(OpenGLProject)
set(CMAKE_CXX_STANDARD 11)

#proje klasörünün yolu yeni bir değişkene atanıyor
set(Project_Dir ${CMAKE_SOURCE_DIR})

set(Project_Src_Dir ${Project_Dir}/src)
set(Kutuphane_Dir ${Project_Dir}/libs)


set(ImGui_Source_files 
                ${Kutuphane_Dir}/imgui/imgui.cpp
                ${Kutuphane_Dir}/imgui/imgui_draw.cpp
                ${Kutuphane_Dir}/imgui/imgui_tables.cpp
                ${Kutuphane_Dir}/imgui/imgui_widgets.cpp
                ${Kutuphane_Dir}/imgui/backends/imgui_impl_glfw.cpp
                ${Kutuphane_Dir}/imgui/backends/imgui_impl_opengl3.cpp
    )


#Kaynak Dosyalari ekleniyor
set(Project_Source_Files 
                ${Project_Src_Dir}/main.cpp
                ${Project_Src_Dir}/glad.c
                ${Project_Src_Dir}/shaderprogram.cpp
                ${Project_Src_Dir}/vertexbuffer.cpp       
                ${Project_Src_Dir}/vertexarrayobject.cpp        
                ${Project_Src_Dir}/GLWindow.cpp         
                ${Project_Src_Dir}/texturemanager.cpp  
                ${Project_Src_Dir}/indexbuffer.cpp            
                ${Project_Src_Dir}/shapecreator.cpp      
                ${Project_Src_Dir}/transform.cpp             
                ${Project_Src_Dir}/camera.cpp  
                ${Project_Src_Dir}/model.cpp     
                ${Project_Src_Dir}/shadermanager.cpp    
                ${Project_Src_Dir}/Scene.cpp    
                ${Project_Src_Dir}/scenemenu.cpp 
                ${ImGui_Source_files}                                  
    )

add_executable(${PROJECT_NAME} ${Project_Source_Files})

set(glfw3_DIR libs/glfw/lib/cmake/glfw3/)

find_package(glfw3 3.4 REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw)

target_include_directories(
    OpenGLProject
    PRIVATE
    ./include
    libs
    libs/glm
    libs/glad/include
    libs/stb
    libs/imgui
    libs/imgui/backends
    libs/nlohmann
    )