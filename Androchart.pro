TEMPLATE = app

QT += qml quick widgets network

SOURCES += main.cpp \
    androchartmanager.cpp \
    chartmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    chartentry.h \
    rsssource.h \
    androchartmanager.h \
    chartmodel.h \
    chartsource.h \
    nyaasource.h
