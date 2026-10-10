cmake_minimum_required(VERSION 3.16)
project(untitled1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# FIX: Added SvgWidgets component for frontend vector UI rendering
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Svg
        SvgWidgets
        REQUIRED)

# Define your main executable and its source files
add_executable(untitled1
        main.cpp
        mainwindow.h
        Components/mainwindow.cpp
        settingswindow.h
        Components/settingswindow.cpp
        Components/fileexplorer.h
        Components/FIleExplorer.cpp
        Components/agent.h
        Components/agent.cpp
        Components/sidebar.h
        Components/sidebar.cpp
        assets/icons.qrc
)
set_target_properties(untitled1 PROPERTIES OUTPUT_NAME strata)

# FIX: Fixed the colon typo (Qt6:Svg -> Qt6::Svg) and added SvgWidgets
target_link_libraries(untitled1 PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Svg
        Qt6::SvgWidgets
)

install(TARGETS untitled1
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES packaging/strata.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)

set(CPACK_PACKAGE_NAME "strata")
set(CPACK_PACKAGE_VENDOR "Strata")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A lightweight code editor built with Qt 6")
set(CPACK_PACKAGE_CONTACT "Strata maintainers")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Strata maintainers")
set(CPACK_DEBIAN_PACKAGE_SECTION "editors")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_GENERATOR "DEB")
include(CPack)
