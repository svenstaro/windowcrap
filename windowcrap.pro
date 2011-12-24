CONFIG += qt link_pkgconfig
LIBS += -lBox2D
HEADERS = application.hpp \
          physicalwindow.hpp
SOURCES = application.cpp \
          physicalwindow.cpp \
          main.cpp
PKGCONFIG += libwnck-3.0
DEFINES += WNCK_I_KNOW_THIS_IS_UNSTABLE
