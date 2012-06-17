INCLUDE_DIRECTORIES(sys)
ADD_LIBRARY(pclib
    slint_pc.c
    chmod.c
    drive.c
    cons_nt.c
    dirent_nt.c
    key_nt.c
    util_win32.c
    util_winnt.c
    util_nt.c)

ADD_LIBRARY(shelllib shell.cpp)
