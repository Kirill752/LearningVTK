
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Tutorial_Step1)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonTransforms
  FiltersSources
  InteractionStyle
  InteractionWidgets
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Tutorial_Step1: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(Tutorial_Step1 MACOSX_BUNDLE Tutorial_Step1.cxx )
  target_link_libraries(Tutorial_Step1 PRIVATE ${VTK_LIBRARIES}
)
add_executable(Tutorial_Step2 MACOSX_BUNDLE Tutorial_Step2.cxx )
  target_link_libraries(Tutorial_Step2 PRIVATE ${VTK_LIBRARIES}
)
add_executable(Tutorial_Step3 MACOSX_BUNDLE Tutorial_Step3.cxx )
  target_link_libraries(Tutorial_Step3 PRIVATE ${VTK_LIBRARIES}
)
add_executable(Tutorial_Step4 MACOSX_BUNDLE Tutorial_Step4.cxx )
  target_link_libraries(Tutorial_Step4 PRIVATE ${VTK_LIBRARIES}
)
add_executable(Tutorial_Step5 MACOSX_BUNDLE Tutorial_Step5.cxx )
  target_link_libraries(Tutorial_Step5 PRIVATE ${VTK_LIBRARIES}
)
add_executable(Tutorial_Step6 MACOSX_BUNDLE Tutorial_Step6.cxx )
  target_link_libraries(Tutorial_Step6 PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS Tutorial_Step1
  TARGETS Tutorial_Step2
  TARGETS Tutorial_Step3
  TARGETS Tutorial_Step4
  TARGETS Tutorial_Step5
  TARGETS Tutorial_Step6
  MODULES ${VTK_LIBRARIES}
)
