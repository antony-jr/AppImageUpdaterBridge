INCLUDEPATH += $$PWD $$PWD/include
QT += core network widgets
CONFIG += staticlib
HEADERS += \
    $$PWD/include/appimageupdateinformation_p.hpp \
    $$PWD/include/zsyncremotecontrolfileparser_p.hpp \
    $$PWD/include/zsyncinternalstructures_p.hpp \
    $$PWD/include/zsyncwriter_p.hpp \
    $$PWD/include/rangereply_p.hpp \
    $$PWD/include/rangereply.hpp \
    $$PWD/include/rangedownloader_p.hpp \
    $$PWD/include/rangedownloader.hpp \
    $$PWD/include/qappimageupdateenums.hpp \
    $$PWD/include/qappimageupdatecodes.hpp \
    $$PWD/include/qappimageupdate_p.hpp \
    $$PWD/include/qappimageupdate.hpp \
    $$PWD/include/helpers_p.hpp \
    $$PWD/include/softwareupdatedialog_p.hpp 

SOURCES += \
    $$PWD/src/appimageupdateinformation_p.cc \
    $$PWD/src/zsyncremotecontrolfileparser_p.cc \
    $$PWD/src/zsyncwriter_p.cc \
    $$PWD/src/rangereply_p.cc \
    $$PWD/src/rangereply.cc \
    $$PWD/src/rangedownloader_p.cc \
    $$PWD/src/rangedownloader.cc \
    $$PWD/src/qappimageupdate_p.cc \
    $$PWD/src/qappimageupdate.cc \
    $$PWD/src/helpers_p.cc \
    $$PWD/src/softwareupdatedialog_p.cc


FORMS += $$PWD/src/AppImageUpdaterDialog.ui \
         $$PWD/include/SoftwareUpdateDialog.ui

NO_GUI {
	message(QAppImageUpdate widgets will be disabled for this build.)
	QT -= widgets
        DEFINES += NO_GUI
	HEADERS -= $$PWD/include/softwareupdatedialog_p.hpp
	SOURCES -= $$PWD/src/softwareupdatedialog_p.cc

        FORMS -= $$PWD/src/AppImageUpdaterDialog.ui \
                $$PWD/include/SoftwareUpdateDialog.ui
}

LOGGING_DISABLED {
	message(Logging will be disabled for this build.)
	DEFINES += LOGGING_DISABLED
}

DECENTRALIZED_UPDATE_ENABLED {
	message(Decentralized update feature will be enabled for this build.)	
	DEFINES += DECENTRALIZED_UPDATE_ENABLED
	HEADERS += $$PWD/include/torrentdownloader.hpp
	HEADERS += $$PWD/include/torrentdownloader_p.hpp
	HEADERS += $$PWD/include/seeder.hpp
	HEADERS += $$PWD/include/seeder_p.hpp
	
	SOURCES += $$PWD/src/torrentdownloader.cc
	SOURCES += $$PWD/src/torrentdownloader_p.cc
	SOURCES += $$PWD/src/seeder.cc
	SOURCES += $$PWD/src/seeder_p.cc

	LIBS += -ltorrent
}else {
	message(Decentralized update feature is not enabled.)
}

BUILD_AS_PLUGIN {
	message(QAppImageUpdate will be built as an Qt Plugin)
	CONFIG -= staticlib
	CONFIG += plugin
	DEFINES += BUILD_AS_PLUGIN	
	OTHER_FILES += $$PWD/QAppImageUpdate.json

	HEADERS += $$PWD/include/qappimageupdateinterface.hpp \
                   $$PWD/include/qappimageupdateinterfaceimpl.hpp

	SOURCES += $$PWD/src/qappimageupdateinterfaceimpl.cc
}
