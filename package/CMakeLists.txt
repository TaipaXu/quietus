set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Browser Accessibility from the System Tray")
set(CPACK_PACKAGE_DESCRIPTION "Easily access your browser directly from the system tray\n with this advanced tool, providing quick and convenient web surfing\n at your fingertips.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Taipa Xu <taipaxu@gmail.com>")

    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libqt6core6 (>= 6.0), libqt6gui6(>= 6.0), libqt6widgets6(>= 6.0), libqt6qml6(>= 6.0), libqt6webenginequick6 (>= 6.0), libqt6network6(>= 6.0)")

    set(CPACK_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

    set(CHGLOG_PATH ${CMAKE_SOURCE_DIR}/package/debian/changelog)
    set(CHGLOG_GZ_PATH ${CMAKE_SOURCE_DIR}/package/debian/changelog.gz)
    add_custom_target(compress_changelog ALL
        COMMAND gzip -9 -n -c ${CHGLOG_PATH} > ${CHGLOG_GZ_PATH}
        DEPENDS ${CHGLOG_PATH}
        COMMENT "Compressing changelog"
        VERBATIM
    )

    install(TARGETS quietus
        RUNTIME DESTINATION bin
    )
    install(FILES debian/quietus16x16.png DESTINATION share/icons/hicolor/16x16/apps RENAME quietus.png)
    install(FILES debian/quietus24x24.png DESTINATION share/icons/hicolor/24x24/apps RENAME quietus.png)
    install(FILES debian/quietus32x32.png DESTINATION share/icons/hicolor/32x32/apps RENAME quietus.png)
    install(FILES debian/quietus48x48.png DESTINATION share/icons/hicolor/48x48/apps RENAME quietus.png)
    install(FILES debian/quietus64x64.png DESTINATION share/icons/hicolor/64x64/apps RENAME quietus.png)
    install(FILES debian/quietus128x128.png DESTINATION share/icons/hicolor/128x128/apps RENAME quietus.png)
    install(FILES debian/quietus256x256.png DESTINATION share/icons/hicolor/256x256/apps RENAME quietus.png)
    install(FILES debian/quietus.desktop DESTINATION share/applications)
    install(FILES debian/changelog.gz DESTINATION share/doc/quietus)
    install(FILES debian/copyright DESTINATION share/doc/quietus)
endif()

include(CPack)
