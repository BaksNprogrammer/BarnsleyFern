cmake_minimum_required(VERSION 3.16)
project(BarnsleyFern VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти пакет Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

# Установите директории для исходных и заголовочных файлов
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Укажите файлы переводов
set(TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/BarnsleyFern_ru_RU.ts)

# Укажите исходные файлы
set(PROJECT_SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/fernmodel.cpp
    ${SOURCE_DIR}/fernview.cpp
    ${SOURCE_DIR}/ferncontroller.cpp
)

# Укажите заголовочные файлы
set(PROJECT_HEADERS
    ${INCLUDE_DIR}/fernmodel.h
    ${INCLUDE_DIR}/fernview.h
    ${INCLUDE_DIR}/ferncontroller.h
)

# Создайте исполняемый файл
qt_add_executable(BarnsleyFern
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${TS_FILES}
)
target_include_directories(BarnsleyFern PRIVATE ${INCLUDE_DIR})

# Создайте файлы переводов
qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})

# Свяжите библиотеки
target_link_libraries(BarnsleyFern PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Установите свойства цели
set_target_properties(BarnsleyFern PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установите правила установки
include(GNUInstallDirs)
install(TARGETS BarnsleyFern
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Завершите создание исполняемого файла
qt_finalize_executable(BarnsleyFern)
