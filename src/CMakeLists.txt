add_subdirectory(app)
add_subdirectory(commands)
add_subdirectory(cptest)

install ( FILES
    cptest_complation_script.sh
    DESTINATION ${BIN_DIR}/bin
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    GROUP_EXECUTE GROUP_READ WORLD_READ WORLD_EXECUTE)
