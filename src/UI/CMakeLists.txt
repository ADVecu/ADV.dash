SET(SOURCES screens/ui_WelcomeScreen.c
    screens/ui_MainScreen.c
    screens/ui_GraphScreen.c
    screens/ui_FinalScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    images/ui_img_e30_png.c
    images/ui_img_banner_png.c
    images/ui_img_proup_png.c
    images/ui_img_proadvv1amarillo_png.c
    images/ui_img_rpmscalev3t_png.c
    images/ui_img_arcscalenored_png.c
    images/ui_img_barscale_png.c
    images/ui_img_arcscalerr_png.c
    images/ui_img_arcscalerb_png.c
    images/ui_img_arcscale_png.c
    images/ui_img_barscalerb_png.c
    images/ui_img_barscalered_png.c
    images/ui_img_advecu200_png.c
    images/ui_img_rpmscalev2_png.c
    images/ui_img_usersett50_png.c
    fonts/ui_font_ArameBold100.c
    fonts/ui_font_ArameBold14.c
    fonts/ui_font_ArameBold150.c
    fonts/ui_font_ArameBold20.c
    fonts/ui_font_ArameBold30.c
    fonts/ui_font_ArameBold30c.c
    fonts/ui_font_ArameBold40.c
    fonts/ui_font_ArameBold50.c)

add_library(ui ${SOURCES})
