ADD_LIBRARY(mclib
    terms.c
    user.c
    file.c
    listmode.c
    cmd.c
    command.c
    help.c
    menu.c
    view.c
    dir.c
    info.c
    widget.c
    option.c
    dlg.c
    panelize.c
    profile.c
    util.c
    dialog.c
    ext.c
    color.c
    layout.c
    setup.c
    regex.c
    hotlist.c
    tree.c
    win.c
    complete.c
    find.c
    wtools.c
    boxes.c
    background.c
    popt.c
    text.c
    screen.c)


ADD_EXECUTABLE(mc main.c)
TARGET_LINK_LIBRARIES(mc
    slanglib
    mclib
    pclib
    shelllib
    editlib)
