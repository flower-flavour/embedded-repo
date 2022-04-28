  cmake_minimum_required(VERSION 3.7)

  set (CMAKE_CXX_STANDARD 11)

# set project_name to name the build results
  set(project_name TEST_repo)
  project(${project_name})

# check glibc version
  set(required_glibc_version "2.23")
  execute_process(COMMAND ${CMAKE_C_COMPILER} -print-file-name=libc.so.6
                  OUTPUT_VARIABLE glibc_version
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  get_filename_component(glibc_version ${glibc_version} REALPATH)
  get_filename_component(glibc_version ${glibc_version} NAME)
  if (NOT glibc_version STREQUAL "libc.so.6")
    string(REPLACE "libc-" "" glibc_version ${glibc_version})
    string(REPLACE ".so" "" glibc_version ${glibc_version})
    if (glibc_version VERSION_LESS ${required_glibc_version})
      message(FATAL_ERROR "Minimum supported glibc version is ${required_glibc_version}, got ${glibc_version}")
    endif(glibc_version VERSION_LESS ${required_glibc_version})
  endif(NOT glibc_version STREQUAL "libc.so.6")

# check libstdc++ version
  set(required_libstdcpp_version "6.0.0")
  execute_process(COMMAND ${CMAKE_C_COMPILER} -print-file-name=libstdc++.so.6
                  OUTPUT_VARIABLE libstdcpp_version
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  get_filename_component(libstdcpp_version ${libstdcpp_version} REALPATH)
  get_filename_component(libstdcpp_version ${libstdcpp_version} NAME)
  string(REPLACE "libstdc++.so." "" libstdcpp_version ${libstdcpp_version})
  string(REPLACE ".so" "" libstdcpp_version ${libstdcpp_version})
  if (NOT libstdcpp_version MATCHES "^[0-9.]+$")
    message(FATAL_ERROR "Unknown libstdc++ version: ${libstdcpp_version}")
  endif(NOT libstdcpp_version MATCHES "^[0-9.]+$")
  if (libstdcpp_version VERSION_LESS ${required_libstdcpp_version})
    message(FATAL_ERROR "Minimum supported libstdc++ version is ${required_libstdcpp_version}, got ${libstdcpp_version}")
  endif(libstdcpp_version VERSION_LESS ${required_libstdcpp_version})

#################### Determine BULD_TYPE flag to choose right version of dependencies (version of libraries app depends on #######################################
  set(IS_DEBUG_BUILD_TYPE ON CACHE BOOL "By default take it's DEBUG BUILD")

  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    unset(IS_DEBUG_BUILD_TYPE CACHE)
    set(IS_DEBUG_BUILD_TYPE OFF CACHE BOOL "Do RELEASE BUILD")
  endif(CMAKE_BUILD_TYPE STREQUAL "Release")

  message(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
#################### Determine if app has to be built as a subproject (using add_subdirectory) #######################################
# or if it is the master project.

  set(MASTER_PROJECT OFF)
  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT ON)
  endif(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
############### add path to custom/own Find*.cmake modules to resolve external dependencies of current project - the libraries which must be in use to ###############
  if(MASTER_PROJECT)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../../libs32/CmakeModules")
  endif(MASTER_PROJECT)
############################################ Boost #####################################################
if(MASTER_PROJECT)

  set (BOOST_VERSION "1.65.1")
# set paths to Boost library
  if(NOT BOOST_ROOT)
    message(STATUS "BOOST_ROOT not defined!")
    string(REPLACE "." "_" BOOST_VERSION_FOLDER ${BOOST_VERSION})
    set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/Boost/boost_${BOOST_VERSION_FOLDER}" CACHE FILEPATH "Root directory of Boost installation")
  endif(NOT BOOST_ROOT)
  message(STATUS "BOOST_ROOT: " ${BOOST_ROOT})

  set(Boost_USE_STATIC_LIBS        ON) # only find static libs
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME    OFF)

  find_package(Boost ${BOOST_VERSION} REQUIRED)
  if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
  endif(Boost_FOUND)

endif(MASTER_PROJECT)
###################################################################################################
############################################# Key ###############################################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/Key")
  find_path(KEY_INCLUDE_DIR IKey.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(Key CACHE)
  set(Key "Key" CACHE STRING "Key library canonical name" FORCE)

  if (IS_DEBUG_BUILD_TYPE)
    set(Key "${Key}d")
  endif (IS_DEBUG_BUILD_TYPE)

  unset(KEY_LIBRARY  CACHE)


# LINUX
  if (NOT WIN32)

    find_library(KEY_LIBRARY
                 ${Key}.so
                 PATHS "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

  elseif (WIN32)

    find_library(KEY_LIBRARY
                 NAMES ${Key}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

  endif (NOT WIN32)

  message(STATUS "Key library Include files is found in: [${KEY_INCLUDE_DIR}].")
  message(STATUS "Key library lib file is found in: [${KEY_LIBRARY}].")

  # the 'Key' is imported from IMPORTED_LOCATION "${KEY_LIBRARY}", there is no need to build 'Key' from src
  add_library(Key STATIC IMPORTED)
  set_property(TARGET Key PROPERTY IMPORTED_LOCATION ${KEY_LIBRARY})

endif(MASTER_PROJECT)
#####################################################################################################
#################################################  Logger #################################################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/Logger")
  find_path(LOGGER_INCLUDE_DIR Logger.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(LOGGER CACHE)
  set(LOGGER "Logger")
  if(IS_DEBUG_BUILD_TYPE)
    set(LOGGER "${LOGGER}d")
  endif(IS_DEBUG_BUILD_TYPE)

  unset(LOGGER_LIBRARY CACHE)

# LINUX
if (NOT WIN32)

    find_library(LOGGER_LIBRARY
                 ${LOGGER}.so
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/" NO_DEFAULT_PATH
                )

else (NOT WIN32)

  find_library(LOGGER_LIBRARY
               NAMES ${LOGGER}
               PATHS
               "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
               )

endif (NOT WIN32)

  message(STATUS "Logger library Include files is found in: [${LOGGER_INCLUDE_DIR}].")
  message(STATUS "Logger library Lib file is found in: [${LOGGER_LIBRARY}].")

# add library as binary one, i.e. merely STATIC! link this APP_NAME with import library libLogger.a
  add_library(Logger STATIC IMPORTED)

# the Logger is imported from IMPORTED_LOCATION ${LOGGER_LIBRARY}/ no need to build 'Logger' from src
  set_property(TARGET Logger PROPERTY IMPORTED_LOCATION ${LOGGER_LIBRARY})

endif(MASTER_PROJECT)
#####################################################################################################
############################################# DataSet ###############################################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/DataSet")
  find_path(DATASET_INCLUDE_DIR DataSet.h "${PATH}/include")

  unset(DATASET CACHE)
  set(DATASET "DataSet")
  if(IS_DEBUG_BUILD_TYPE)
    set(DATASET "${DATASET}d")
  endif(IS_DEBUG_BUILD_TYPE)

  unset(DATASET_LIBRARY CACHE)

# LINUX
if (NOT WIN32)

    find_library(DATASET_LIBRARY
                 ${DATASET}.so
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
                )

else (NOT WIN32)

    find_library(DATASET_LIBRARY
                 NAMES ${DATASET}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

endif (NOT WIN32)

  message(STATUS "DataSet library Include files is found in: [${DATASET_INCLUDE_DIR}].")
  message(STATUS "DataSet library Lib file is found in: [${DATASET_LIBRARY}].")

# add library as binary one, i.e. merely STATIC! link this APP_NAME with import library libDataSet.a
  add_library(DataSet STATIC IMPORTED)

# the DataSet is imported from IMPORTED_LOCATION ${DATASET_LIBRARY}/ no need to build 'DataSet' from src
  set_property(TARGET DataSet PROPERTY IMPORTED_LOCATION ${DATASET_LIBRARY})

endif(MASTER_PROJECT)
#####################################################################################################
############################################# repo_grammar ###############################################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/repo_grammar")
  find_path(REPO_GRAMMAR_INCLUDE_DIR public_interface.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(REPO_GRAMMAR CACHE)
  set(REPO_GRAMMAR "repo_grammar")
  if(IS_DEBUG_BUILD_TYPE)
    set(REPO_GRAMMAR "${REPO_GRAMMAR}d")
  endif(IS_DEBUG_BUILD_TYPE)

  unset(REPO_GRAMMAR_LIBRARY CACHE)

# LINUX
  if (NOT WIN32)

      find_library(REPO_GRAMMAR_LIBRARY
                   ${REPO_GRAMMAR}.so
                   "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                   NO_DEFAULT_PATH
                  )

  else (NOT WIN32)

    find_library(REPO_GRAMMAR_LIBRARY
                 NAMES ${REPO_GRAMMAR}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
                 )

  endif (NOT WIN32)

  message(STATUS "repo_grammar library Include files is found in: [${REPO_GRAMMAR_INCLUDE_DIR}].")
  message(STATUS "repo_grammar library Lib file is found in: [${REPO_GRAMMAR_LIBRARY}].")

  add_library(repo_grammar STATIC IMPORTED)

  set_property(TARGET repo_grammar PROPERTY IMPORTED_LOCATION ${REPO_GRAMMAR_LIBRARY})

endif(MASTER_PROJECT)
#####################################################################################################
############################################## config_parser ##############################################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/config_parser")
  find_path(CONFIG_PARSER_INCLUDE_DIR config_parser.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(CONFIG_PARSER CACHE)
  set(CONFIG_PARSER "config_parser")
  if(IS_DEBUG_BUILD_TYPE)
    set(CONFIG_PARSER "${CONFIG_PARSER}d")
  endif(IS_DEBUG_BUILD_TYPE)

  unset(CONFIG_PARSER_LIBRARY CACHE)
# LINUX
if (NOT WIN32)

    find_library(CONFIG_PARSER_LIBRARY
                 ${CONFIG_PARSER}.so
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
                )

else (NOT WIN32)

    find_library(CONFIG_PARSER_LIBRARY
                 NAMES ${CONFIG_PARSER}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

endif (NOT WIN32)

  message(STATUS "config_parser library Include files is found in: [${CONFIG_PARSER_INCLUDE_DIR}].")
  message(STATUS "config_parser library Lib file is found in: [${CONFIG_PARSER_LIBRARY}].")

# add library as binary one, i.e. merely STATIC! link this APP_NAME with import library libconfig_parser.a
  add_library(config_parser STATIC IMPORTED)

# the config_parser is imported from IMPORTED_LOCATION ${CONFIG_PARSER_LIBRARY}/ no need to build 'config_parser' from src
  set_property(TARGET config_parser PROPERTY IMPORTED_LOCATION ${CONFIG_PARSER_LIBRARY})

endif(MASTER_PROJECT)
#####################################################################################################
############################## RepoTransactions ###############################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/RepoTransactions")
  find_path(REPOTRANSACTIONS_INCLUDE_DIR IPlanTransactions.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(RepoTransactions CACHE)
  set(RepoTransactions "RepoTransactions")

  if (IS_DEBUG_BUILD_TYPE)
    set(RepoTransactions "${RepoTransactions}d")
  endif (IS_DEBUG_BUILD_TYPE)

  unset(REPOTRANSACTIONS_LIBRARY CACHE)

# LINUX
  if (NOT WIN32)

    find_library(REPOTRANSACTIONS_LIBRARY
                 ${RepoTransactions}.so
                 PATHS "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
               )

  elseif (WIN32)

    find_library(REPOTRANSACTIONS_LIBRARY
                 NAMES ${RepoTransactions}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )


  endif (NOT WIN32)

  message(STATUS "RepoTransactions library Include files is found in: [${REPOTRANSACTIONS_INCLUDE_DIR}].")
  message(STATUS "RepoTransactions library lib file is found in: [${REPOTRANSACTIONS_LIBRARY}].")

  # the 'RepoTransactions' is imported from IMPORTED_LOCATION "${REPOTRANSACTIONS_LIBRARY}", there is no need to build 'RepoTransactions' from src
  add_library(RepoTransactions STATIC IMPORTED)
  set_property(TARGET RepoTransactions PROPERTY IMPORTED_LOCATION ${REPOTRANSACTIONS_LIBRARY})

endif(MASTER_PROJECT)
############################## RepoDirectory ###############################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/RepoDirectory")
  find_path(REPODIRECTORY_INCLUDE_DIR IRepoDirectory.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(RepoDirectory CACHE)
  set(RepoDirectory "RepoDirectory")

  if (IS_DEBUG_BUILD_TYPE)
    set(RepoDirectory "${RepoDirectory}d")
  endif (IS_DEBUG_BUILD_TYPE)

  unset(REPODIRECTORY_LIBRARY CACHE)

# LINUX
  if (NOT WIN32)

    find_library(REPODIRECTORY_LIBRARY
                 ${RepoDirectory}.so
                 PATHS "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
               )


  elseif (WIN32)

    find_library(REPODIRECTORY_LIBRARY
                 NAMES ${RepoDirectory}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

  endif (NOT WIN32)

  message(STATUS "RepoDirectory library Include files is found in: [${REPODIRECTORY_INCLUDE_DIR}].")
  message(STATUS "RepoDirectory library lib file is found in: [${REPODIRECTORY_LIBRARY}].")

  # the 'RepoDirectory' is imported from IMPORTED_LOCATION "${REPODIRECTORY_LIBRARY}", there is no need to build 'RepoDirectory' from src
  add_library(RepoDirectory STATIC IMPORTED)
  set_property(TARGET RepoDirectory PROPERTY IMPORTED_LOCATION ${REPODIRECTORY_LIBRARY})

endif(MASTER_PROJECT)
#####################################################################################################
################################ RepoCacheLogic ###############################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/RepoCacheLogic")
  find_path(REPOCACHELOGIC_INCLUDE_DIR IRepoCacheLogic.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(RepoCacheLogic CACHE)
  set(RepoCacheLogic "RepoCacheLogic")

  if (IS_DEBUG_BUILD_TYPE)
    set(RepoCacheLogic "${RepoCacheLogic}d")
  endif (IS_DEBUG_BUILD_TYPE)

  unset(REPOCACHELOGIC_LIBRARY CACHE)

# LINUX
  if (NOT WIN32)

    find_library(REPOCACHELOGIC_LIBRARY
                 ${RepoCacheLogic}.so
                 PATHS "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
                )

  elseif (WIN32)

    find_library(REPOCACHELOGIC_LIBRARY
                 NAMES ${RepoCacheLogic}
                 PATHS
                "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

  endif (NOT WIN32)

  message(STATUS "RepoCacheLogic library Include files is found in: [${REPOCACHELOGIC_INCLUDE_DIR}].")
  message(STATUS "RepoCacheLogic library lib file is found in: [${REPOCACHELOGIC_LIBRARY}].")

  # the 'RepoCacheLogic' is imported from IMPORTED_LOCATION "${REPOCACHELOGIC_LIBRARY}", there is no need to build 'RepoCacheLogic' from src
  add_library(RepoCacheLogic STATIC IMPORTED)
  set_property(TARGET RepoCacheLogic PROPERTY IMPORTED_LOCATION ${REPOCACHELOGIC_LIBRARY})

endif(MASTER_PROJECT)
#####################################################################################################
################################ RepoCache ###############################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/RepoCache")
  find_path(REPOCACHE_INCLUDE_DIR IRepoCache.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(RepoCache CACHE)
  set(RepoCache "RepoCache")

  if (IS_DEBUG_BUILD_TYPE)
    set(RepoCache "${RepoCache}d")
  endif (IS_DEBUG_BUILD_TYPE)

  unset(REPOCACHE_LIBRARY CACHE)

# LINUX
  if (NOT WIN32)

    find_library(REPOCACHE_LIBRARY
                 ${RepoCache}.so
                 PATHS "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
               )

  elseif (WIN32)

    find_library(REPOCACHE_LIBRARY
                 NAMES ${RepoCache}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

  endif (NOT WIN32)

  message(STATUS "RepoCache library Include files is found in: [${REPOCACHE_INCLUDE_DIR}].")
  message(STATUS "RepoCache library lib file is found in: [${REPOCACHE_LIBRARY}].")

  # the 'RepoCache' is imported from IMPORTED_LOCATION "${REPOCACHE_LIBRARY}", there is no need to build 'RepoCache' from src
  add_library(RepoCache STATIC IMPORTED)
  set_property(TARGET RepoCache PROPERTY IMPORTED_LOCATION ${REPOCACHE_LIBRARY})

endif(MASTER_PROJECT)
############################## RepoPersistentStorage ###############################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/RepoPersistentStorage")
  find_path(REPOPERSISTENTSTORAGE_INCLUDE_DIR IRepoPersistentStorage.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(RepoPersistentStorage CACHE)
  set(RepoPersistentStorage "RepoPersistentStorage")

  if (IS_DEBUG_BUILD_TYPE)
    set(RepoPersistentStorage "${RepoPersistentStorage}d")
  endif (IS_DEBUG_BUILD_TYPE)

  unset(REPOPERSISTENTSTORAGE_LIBRARY CACHE)

# LINUX
  if (NOT WIN32)

    find_library(REPOPERSISTENTSTORAGE_LIBRARY
                 ${RepoPersistentStorage}.so
                 PATHS "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
                )

  elseif (WIN32)

    find_library(REPOPERSISTENTSTORAGE_LIBRARY
                 NAMES ${RepoPersistentStorage}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

  endif (NOT WIN32)

  message(STATUS "RepoPersistentStorage library Include files is found in: [${REPOPERSISTENTSTORAGE_INCLUDE_DIR}].")
  message(STATUS "RepoPersistentStorage library lib file is found in: [${REPOPERSISTENTSTORAGE_LIBRARY}].")

  # the 'RepoPersistentStorage' is imported from IMPORTED_LOCATION "${REPOPERSISTENTSTORAGE_LIBRARY}", there is no need to build 'RepoPersistentStorage' from src
  add_library(RepoPersistentStorage STATIC IMPORTED)
  set_property(TARGET RepoPersistentStorage PROPERTY IMPORTED_LOCATION ${REPOPERSISTENTSTORAGE_LIBRARY})

endif(MASTER_PROJECT)
################################ RPSReader ###############################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/RPSReader")
  find_path(RPSREADER_INCLUDE_DIR IStorageReader.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(RPSReader CACHE)
  set(RPSReader "RPSReader")

  if (IS_DEBUG_BUILD_TYPE)
    set(RPSReader "${RPSReader}d")
  endif (IS_DEBUG_BUILD_TYPE)

  unset(RPSREADER_LIBRARY CACHE)

# LINUX
  if (NOT WIN32)

    find_library(RPSREADER_LIBRARY
                 ${RPSReader}.so
                 PATHS "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
               )

  elseif (WIN32)

    find_library(RPSREADER_LIBRARY
                 NAMES ${RPSReader}
                 PATHS
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                )

  endif (NOT WIN32)

  message(STATUS "RPSReader library Include files is found in: [${RPSREADER_INCLUDE_DIR}].")
  message(STATUS "RPSReader library lib file is found in: [${RPSREADER_LIBRARY}].")

  # the 'RPSReader' is imported from IMPORTED_LOCATION "${RPSREADER_LIBRARY}", there is no need to build 'RPSReader' from src
  add_library(RPSReader STATIC IMPORTED)
  set_property(TARGET RPSReader PROPERTY IMPORTED_LOCATION ${RPSREADER_LIBRARY})

endif(MASTER_PROJECT)
############################################## repo ##############################################
if(MASTER_PROJECT)
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs32/repo")
  find_path(REPO_INCLUDE_DIR RepoGrammar.h "${PATH}/include/" NO_DEFAULT_PATH)

  unset(REPO CACHE)
  set(REPO "repo")
  if(IS_DEBUG_BUILD_TYPE)
    set(REPO "${REPO}d")
  endif(IS_DEBUG_BUILD_TYPE)

  unset(REPO_LIBRARY CACHE)
# LINUX
if (NOT WIN32)

    find_library(REPO_LIBRARY
                 ${REPO}.so
                 "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
                 NO_DEFAULT_PATH
                )

else (NOT WIN32)

    find_library(REPO_LIBRARY
                 NAMES ${REPO}
                 PATHS
                "${PATH}/bin/${CMAKE_BUILD_TYPE}/"
               )

endif (NOT WIN32)

  message(STATUS "repo library Include files is found in: [${REPO_INCLUDE_DIR}].")
  message(STATUS "repo library Lib file is found in: [${REPO_LIBRARY}].")

# add library as binary one, i.e. merely STATIC! link this APP_NAME with import library librepo.a
  add_library(repo STATIC IMPORTED)

# the repo is imported from IMPORTED_LOCATION ${REPO_LIBRARY}/ no need to build 'repo' from src
  set_property(TARGET repo PROPERTY IMPORTED_LOCATION ${REPO_LIBRARY})

endif(MASTER_PROJECT)
###################################################################################################

  file (GLOB headers_test_repo
        ./src/parseCLIargs.h
        ./src/DataproviderImpl.h
        ./src/grammar_stuff.h
        ./src/allocateRepository.h
        ./src/test_patterns/pattern_headers.h
        ./src/test_patterns/Urandom_generators.h
       )

  file (GLOB src_test_repo
        ./src/allocateRepository.cpp
        ./src/getRndSizes.cpp
        ./src/getRndValues.cpp
        ./src/parseCLIargs.cpp
        ./src/main.cpp
        ./src/DataproviderImpl.cpp
        ./src/test_patterns/Urandom_request_gen.cpp
       )

  file(GLOB PROJECT_SOURCES_CPP include/*.hpp
                                src/*.cpp)

################################################################################################
  add_executable(${project_name} ${headers_test_repo}
                                 ${src_test_repo}
                )

  set_target_properties(${project_name} PROPERTIES DEBUG_POSTFIX "d")

############################ define compiler/linker options to build app, including the needed defines #########################

  set_source_files_properties(${PROJECT_SOURCES_C}
                                PROPERTIES
                                COMPILE_FLAGS "-std=c99"
                             )

  set_source_files_properties(${PROJECT_SOURCES_CPP}
                                PROPERTIES
                                COMPILE_FLAGS "-std=c++11"
                             )

  if (PLATFORM_TO_BUILD)
    message(STATUS "PLATFORM_TO_BUILD: '${PLATFORM_TO_BUILD}'")
  else (PLATFORM_TO_BUILD)
    # NB!!! by default we compile for 32-bit architecture! => -m32
    set(PLATFORM_TO_BUILD "-m32")
  endif (PLATFORM_TO_BUILD)

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PLATFORM_TO_BUILD}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PLATFORM_TO_BUILD}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${PLATFORM_TO_BUILD}")

if(MASTER_PROJECT)
  # set options of C++'s compiler (g++)
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".lib")

    set_target_properties(${project_name}
                          PROPERTIES
                          COMPILE_FLAGS "-Wall -Wextra -Werror=return-type -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-ignored-qualifiers"
                          COMPILE_FLAGS_DEBUG " -g "
                          COMPILE_FLAGS_RELEASE " -s -O2 -DNDEBUG"
                          LINK_FLAGS "-static-libgcc -static-libstdc++"
                         )

  endif (CMAKE_COMPILER_IS_GNUCXX)
endif(MASTER_PROJECT)

if(MASTER_PROJECT)

    target_compile_definitions(${project_name}
                               PRIVATE
                               "DataProvider_EXPORTS")

    if (IS_DEBUG_BUILD_TYPE)

        target_compile_definitions(${project_name}
                                   PRIVATE
                                   "_DEBUG_DATA_MODEL_TRANSACTIONS_")

    endif (IS_DEBUG_BUILD_TYPE)
endif(MASTER_PROJECT)

############################## link ###############################


  if (NOT WIN32)

      target_link_libraries(${project_name}
                            ${LOGGER_LIBRARY}
                            ${DATASET_LIBRARY}
                            ${REPO_GRAMMAR_LIBRARY}
                            ${CONFIG_PARSER_LIBRARY}
                            ${REPOTRANSACTIONS_LIBRARY}
                            ${REPOCACHELOGIC_LIBRARY}
                            ${REPODIRECTORY_LIBRARY}
                            ${REPOCACHE_LIBRARY}
                            ${REPOPERSISTENTSTORAGE_LIBRARY}
                            ${RPSREADER_LIBRARY}
                            ${REPO_LIBRARY}
                            ${KEY_LIBRARY}
                            pthread
                            dl
                           )

  else (NOT WIN32)

      target_link_libraries(${project_name}
                            ${LOGGER_LIBRARY}
                            ${DATASET_LIBRARY}
                            ${REPO_GRAMMAR_LIBRARY}
                            ${CONFIG_PARSER_LIBRARY}
                            ${REPOTRANSACTIONS_LIBRARY}
                            ${REPOCACHELOGIC_LIBRARY}
                            ${REPODIRECTORY_LIBRARY}
                            ${REPOCACHE_LIBRARY}
                            ${REPOPERSISTENTSTORAGE_LIBRARY}
                            ${RPSREADER_LIBRARY}
                            ${REPO_LIBRARY}
                            ${KEY_LIBRARY}
                           )

  endif (NOT WIN32)


############################################# install ################################################
  install(TARGETS ${project_name} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/")
