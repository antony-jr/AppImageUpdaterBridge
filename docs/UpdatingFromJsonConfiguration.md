---
id: UpdatingFromJsonConfiguration
title: Updating AppImage with Json Configuration
sidebar_label: Updating AppImage with Json Configuration
---

This is a very small example on how to check for updates from the update information extracted from a **Json Configuration file!**   
Please see that you must follow the [AppImageSpec](https://github.com/AppImage/AppImageSpec/blob/master/draft.md#update-information)


**main.cpp**

```
#include <QCoreApplication>
#include "AppImageUpdaterBridge/AIUpdaterBridge.hpp"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    if(argc == 1){ return -1; } // remove this if its self-updating
    AIUpdaterBridge Bridge;

    QObject::connect(&Bridge, &AIUpdaterBridge::updatesAvailable,
    [&](QString appimage, QString sha1) {
        //Start the update // Ask the user a choose about Update here!
        Bridge.startUpdating();
    });
    QObject::connect(&Bridge, &AIUpdaterBridge::updateFinished,
    [&](QString appImage, QString SHA1) {
        qDebug() << "Updated " << appImage << " to " << SHA1;
        qDebug() << "Please Restart AppImage!";
        app.quit();
        return;
    });
    QObject::connect(&Bridge, &AIUpdaterBridge::progress,
    [&](float percentage, qint64 bytesRecived, qint64 bytesTotal, 
        double speed, const QString& unit) {
        qDebug() << "Downloaded:: " << bytesRecived << "bytes of " << bytesTotal
                 <<" Percentage:: " << percentage << " at " << speed << unit;
        return;
    });
    QObject::connect(&Bridge, &AIUpdaterBridge::noUpdatesAvailable,
    [&](QString appImage, QString SHA1) {
        qDebug() << "AppImage Version(" << SHA1 << ")";
        qDebug() << "Starting Application!"; // Run Your App Here
        app.quit();
        return;
    });
    QObject::connect(&Bridge, &AIUpdaterBridge::error,
    [&](QString appImage, short errorCode) {
        qDebug() << "ERROR CODE:: " << errorCode;
        app.quit();
        return;
    });
    QFile config("config.json");
    if(!config.open(QIODevice::ReadOnly)){
       qDebug() << "ERROR CANNOT OPEN CONFIGURATION!";
       return -1; // Since the event loop is not started yet.
    }
    Bridge.doDebug(true);
    Bridge.setAppImageUpdateInformation(
            QJsonDocument::fromJson(config.readAll()).object()
    ); // This is a little sync
    return app.exec();
}

```

**config.json**

```
{
    "appImagePath" : "/path/to/your/AppImage.AppImage",
    "transport" : "gh-releases-zsync",
    "username"  : "antony-jr",
    "repo"      : "AppImage",
    "tag"       : "continous",
    "filename"  : "AppImage*.AppImage.zsync"
}
```

**CMakeLists.txt**

```
CMAKE_MINIMUM_REQUIRED( VERSION 3.2)
project(Updater)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtCore library
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Concurrent)

include_directories(${CMAKE_CURRENT_BINARY_DIR}) # just in case!
# Add include directory
include_directories(AppImageUpdaterBridge)

# include subdirectories 
add_subdirectory(AppImageUpdaterBridge)

add_executable(Updater MyMain.cpp)
target_link_libraries(Updater AIUpdaterBridge Qt5::Core Qt5::Network Qt5::Concurrent)
```

## Compilation and Execution

```
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make -j4
 $ ./Updater
```