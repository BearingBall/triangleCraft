QT       += core gui
QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS   += -lopengl32
LIBS   += -lglu32
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basics/Cube.cpp \
    basics/Triangle.cpp \
    main.cpp \
    mainwindow.cpp \
    widget/COpenGlWidget.cpp

HEADERS += \
    TextureContainer.h \
    basics/Camera.h \
    basics/Cube.h \
    basics/DestroyBuildPointer.h \
    basics/Map.h \
    basics/MeshShard.h \
    basics/Triangle.h \
    mainwindow.h \
    widget/COpenGlWidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    fsh.glsl \
    fshPicking.glsl \
    vsh.glsl \
    vshPicking.glsl
