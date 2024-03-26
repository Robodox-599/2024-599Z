#include "main.h"
#include "liblvgl/lvgl.h"
lv_color_t fun_green =  lv_color_make(0, 100, 46);

static void auto_scroll_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);
    }
}

void auto_selector_dropdown(void){
	static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 10);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_color_white());
    lv_style_set_border_color(&style, lv_color_black());
    lv_style_set_border_width(&style, 2);
	lv_style_set_text_color(&style, lv_color_black());
    lv_obj_t * dd = lv_dropdown_create(lv_scr_act());
	lv_obj_add_style(dd, &style, 0);
    lv_dropdown_set_options(dd, LV_SYMBOL_GPS "  AUTOS\n"
                            LV_SYMBOL_DIRECTORY "  MOTORS\n"
                            LV_SYMBOL_WARNING "  SENSORS"
							);
	lv_obj_set_width(dd, 150);
	lv_dropdown_set_symbol(dd, &LV_SYMBOL_SETTINGS);	
	lv_dropdown_set_selected_highlight(dd, false);
    lv_obj_align(dd, LV_ALIGN_TOP_LEFT, 20, 20);
    lv_obj_add_event_cb(dd, auto_scroll_event_handler, LV_EVENT_ALL, NULL);
}

/*A vertical tab view with disabled scrolling and some styling*/
void lv_example_tabview_2(void)
{
    /*Create a Tab view object*/
    lv_obj_t * screen_tabview;
    screen_tabview = lv_tabview_create(lv_scr_act(), LV_ALIGN_TOP_LEFT, 150);
    lv_obj_set_style_bg_color(screen_tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0);
    lv_obj_t * tab_buttons = lv_tabview_get_tab_btns(screen_tabview);
    lv_obj_set_style_bg_color(tab_buttons, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    lv_obj_set_style_text_color(tab_buttons, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_side(tab_buttons, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(screen_tabview, LV_SYMBOL_GPS "  AUTOS");
    lv_obj_t * tab2 = lv_tabview_add_tab(screen_tabview, LV_SYMBOL_DIRECTORY "  MOTORS");
    lv_obj_t * tab3 = lv_tabview_add_tab(screen_tabview, LV_SYMBOL_WARNING "  SENSORS");


    lv_obj_set_style_bg_color(tab2, fun_green, 0);
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    /*Add content to the tabs*/
    lv_obj_t * label = lv_label_create(tab1);
    lv_label_set_text(label, LV_SYMBOL_GPS "  AUTOS");

    label = lv_label_create(tab2);
    lv_label_set_text(label, LV_SYMBOL_DIRECTORY "  MOTORS");

    label = lv_label_create(tab3);
    lv_label_set_text(label, LV_SYMBOL_WARNING "  SENSORS");
}


void set_Bg_color(){
	lv_obj_set_style_bg_color(lv_scr_act(), fun_green, LV_PART_MAIN);
}
void initialize()
{
	set_Bg_color();
	auto_selector_dropdown();
	lv_example_tabview_2();
}



void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1,-2,3}); // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4,5,-6}); // Creates a motor group with forwards port 4 and reversed ports 4 & 6

	while (true) {
		// Arcade control scheme
		int dir = master.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X); // Gets the turn left/right from right joystick
		left_mg = dir - turn; // Sets left motor voltage
		right_mg = dir + turn; // Sets right motor voltage
		pros::delay(20); // Run for 20 ms then update
	}
}