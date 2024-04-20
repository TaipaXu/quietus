set(CPACK_PACKAGE_DESCRIPTION "Quietus")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Quietus")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Taipa Xu <taipaxu@gmail.com>")

    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt6core6 (>= 6.0), libqt6gui6(>= 6.0), libqt6widgets6(>= 6.0), libqt6qml6(>= 6.0), libqt6webenginequick6 (>= 6.0), libqt6network6(>= 6.0)")

    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

    install(TARGETS quietus
        RUNTIME DESTINATION bin
    )

    install(FILES debian/quietus.png DESTINATION share/icons/hicolor/48x48/apps)

    install(FILES ./debian/quietus.desktop DESTINATION share/applications)
endif()

include(CPack)
