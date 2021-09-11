cmake_minimum_required(VERSION 3.5)

project(task_draw)

find_package(Qt6Widgets)

qt_wrap_cpp(
	MOC_WRAPPERS
	mainwindow.h
	datadialog.h
	paintArea.h
)

set(PROJECT_SOURCES
	main.cpp
	mainwindow.cpp
	mainwindow.h
	paintArea.h
	paintArea.cpp
	datadialog.h
	datadialog.cpp
)

add_executable(
	task_draw WIN32
	${PROJECT_SOURCES}
	${MOC_WRAPPERS}
)

target_link_libraries(task_draw PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

