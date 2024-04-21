find_package(Qt6 REQUIRED COMPONENTS Core Widgets Quick QuickControls2 Qml Network Multimedia WebEngineQuick LinguistTools)
find_package(Threads)

configure_file(./appConfig.hpp.in ./appConfig.hpp)

if(APPLE)
    set(CMAKE_MACOSX_BUNDLE ON)
endif()

set(TARGET quietus)
set(SOURCES
        main.cpp
        core.hpp
        core.cpp

        links/favorite.hpp
        links/favorite.cpp

        widgets/quietus.hpp
        widgets/quietus.cpp

        models/website.hpp
        models/website.cpp
        models/favorite.hpp
        models/favorite.cpp

        persistence/persistence.hpp
        persistence/persistence.cpp
        persistence/website.hpp
        persistence/website.cpp
        persistence/favorite.hpp
        persistence/favorite.cpp

        network/faviconManager.hpp
        network/faviconManager.cpp

        utils/common.hpp
        utils/common.cpp

        assets.qrc
)

add_executable(
    ${TARGET}
    ${SOURCES}
)

if(UNIX AND NOT APPLE)
add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND strip $<TARGET_FILE:quietus>
        COMMENT "Stripping executable $<TARGET_FILE:quietus>")
endif()

target_link_libraries(${TARGET} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${WebEngineQuick}::WebEngineQuick
    ${CMAKE_THREAD_LIBS_INIT})

qt_add_qml_module(${TARGET}
    URI qml
    NO_RESOURCE_TARGET_PATH
    QML_FILES
        "widgets/Window.qml"
        "widgets/Browser.qml"
        "widgets/FavoriteGroups.qml"
        "widgets/FavoriteGroup.qml"
        "widgets/Favorite.qml"
        "widgets/AddEditFavoriteGroupDialog.qml"
        "widgets/FavoriteDialog.qml"
        "widgets/EventBus.qml"
)
