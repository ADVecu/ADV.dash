SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_rpmscalet_png.c
    fonts/ui_font_RussoOne14.c
    fonts/ui_font_RussoOne50.c
    fonts/ui_font_ArameBold100.c
    fonts/ui_font_ArameBold150.c
    fonts/ui_font_ArameBold50.c
    fonts/ui_font_ArameBold14.c
    fonts/ui_font_ArameBold30.c)

add_library(ui ${SOURCES})
