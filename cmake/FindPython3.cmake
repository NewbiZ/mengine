FIND_PACKAGE(PkgConfig)

IF(NOT PKG_CONFIG_FOUND)
    MESSAGE(FATAL_ERROR "Cannot find pkg-config!")
ENDIF(NOT PKG_CONFIG_FOUND)

PKG_CHECK_MODULES(PYTHON3 python3>=3.0)

IF(NOT PYTHON3_FOUND)
    MESSAGE(FATAL_ERROR "Cannot find python 3 using pkg-config."
                        "You may need to set your PKG_CONFIG_PATH environment "
                        "variable to the directory where your Python 3.x "
                        "version stands. \n"
                        "Example:"
                        "PKG_CONFIG_PATH=/path/to/python3/lib/pkgconfig cmake ...")
ENDIF(NOT PYTHON3_FOUND)

