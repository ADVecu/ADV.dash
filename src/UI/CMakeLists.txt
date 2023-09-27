SET(SOURCES screens/ui_WelcomeScreen.c
    screens/ui_MainScreen.c
    screens/ui_Screen2.c
    screens/ui_Screen3.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_advecu200_png.c
    images/ui_img_rpmscalet_png.c
    images/ui_img_arcscalenored_png.c
    images/ui_img_barscale_png.c
    images/ui_img_arcscale_png.c
    images/ui_img_barscalered_png.c
    fonts/ui_font_ArameBold100.c
    fonts/ui_font_ArameBold14.c
    fonts/ui_font_ArameBold150.c
    fonts/ui_font_ArameBold20.c
    fonts/ui_font_ArameBold30.c
    fonts/ui_font_ArameBold40.c
    fonts/ui_font_ArameBold50.c)

add_library(ui ${SOURCES})
