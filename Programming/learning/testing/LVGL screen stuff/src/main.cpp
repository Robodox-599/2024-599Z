#include "main.h"
#include "liblvgl/lvgl.h"
#include "logo_black.h"
lv_color_t fun_green =  lv_color_make(0, 100, 46);
lv_obj_t * tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 0);
lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Tab 1");
lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");
lv_obj_t * description = lv_textarea_create(tab1);

lv_obj_t* createImage(const lv_img_dsc_t* image, lv_obj_t* parent, int width, int height, int x, int y) {
    lv_obj_t* img = lv_img_create(parent);
    lv_img_set_src(img, image);
    lv_obj_set_width(img, width);
    lv_obj_set_height(img, height);
    lv_obj_set_x(img, x);
    lv_obj_set_y(img, y);
    return img;
}

int auto_picker = 0;
static void near_side_event(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        lv_textarea_set_text(description, "Half AWP, Gets triball out of matchload zone, then takes it + alliance ball to under alley, finally touches the elevation bar");
        auto_picker = 1;
    }
}
static void far_side_event(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        lv_textarea_set_text(description, "Four ball route, garentees alliance triball in goal + rushes middle to score all 3");
        auto_picker = 2;
    }
}
static void disrupt_event(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        lv_textarea_set_text(description, "Gets triball out of matchload zone, then disrupts middle balls, comes back to matchload zone and pushes 2 more over, lines up for bowling");
        auto_picker = 3; 
    }
}
static void skills_event(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        lv_textarea_set_text(description, "Skills autonomous");
        auto_picker = 4; 
    }
}

void set_tabs(){
    lv_obj_set_style_bg_color(tabview, fun_green, 0);
    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, fun_green, 0);
    lv_obj_set_style_text_color(tab_btns, fun_green, 0);
    lv_obj_align(tab_btns, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(tab_btns, 0);
    lv_obj_set_height(tab_btns, 0);
    lv_obj_set_style_bg_color(tabview, fun_green, 0);
    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/

    lv_obj_set_scrollbar_mode(tab1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(tab2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(tab3, LV_SCROLLBAR_MODE_OFF);
    
    lv_obj_t * btn = lv_btn_create(tab1);
    lv_obj_set_pos(btn, 5, 45);
    lv_obj_set_size(btn, 120, 30);
    lv_obj_add_event_cb(btn, near_side_event, LV_EVENT_ALL, NULL);         
    lv_obj_t * label = lv_label_create(btn);         
    lv_label_set_text(label, "Near Side, 9pt");                   
    lv_obj_center(label);
    
    static lv_style_t ta_style;
    lv_style_init(&ta_style);
    lv_style_set_radius(&ta_style, 10);
    lv_style_set_bg_opa(&ta_style, LV_OPA_COVER);
    lv_style_set_bg_color(&ta_style, lv_color_white());
    lv_style_set_border_color(&ta_style, lv_color_black());
    lv_style_set_border_width(&ta_style, 2);
	lv_style_set_text_color(&ta_style, lv_color_black());

    lv_obj_set_scrollbar_mode(description, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(description, LV_STATE_DISABLED);
    lv_obj_add_style(description, &ta_style, 0);
    lv_obj_set_pos(description, 130, 95);
    lv_obj_set_height(description, 95);
    lv_obj_set_width(description, 300);
    
    static lv_style_t btn_style;
    lv_style_init(&btn_style);
    lv_style_set_bg_opa(&btn_style, LV_OPA_COVER);
    lv_style_set_bg_color(&btn_style, lv_color_black());
    lv_style_set_border_color(&btn_style, lv_color_black());
    lv_style_set_border_width(&btn_style, 2);
	lv_style_set_text_color(&btn_style, lv_color_white());

    lv_obj_add_style(btn, &btn_style, 0);

    btn = lv_btn_create(tab1);
    lv_obj_set_pos(btn, 5, 80);
    lv_obj_set_size(btn, 120, 30);
    lv_obj_add_event_cb(btn, far_side_event, LV_EVENT_ALL, NULL);         
    label = lv_label_create(btn);         
    lv_label_set_text(label, "Far Side, 20pt");                   
    lv_obj_center(label);

    lv_obj_add_style(btn, &btn_style, 0);

    btn = lv_btn_create(tab1);
    lv_obj_set_pos(btn, 5, 115);
    lv_obj_set_size(btn, 120, 30);
    lv_obj_add_event_cb(btn, disrupt_event, LV_EVENT_ALL, NULL);         
    label = lv_label_create(btn);         
    lv_label_set_text(label, "Disrupt, 10pt");                   
    lv_obj_center(label);

    lv_obj_add_style(btn, &btn_style, 0);

    btn = lv_btn_create(tab1);
    lv_obj_set_pos(btn, 5, 150);
    lv_obj_set_size(btn, 120, 30);
    lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    label = lv_label_create(btn);         
    lv_label_set_text(label, "Skills");                   
    lv_obj_center(label);
    lv_textarea_set_text(description, "Default Image");
    auto_picker = 0;

    lv_obj_add_style(btn, &btn_style, 0);
    
    createImage(&logo, tab1, 169, 100, 130, 5);

    lv_obj_t * tab_label = lv_label_create(tab1);
    /*Add content to the tabs*/

    static lv_style_t tab_style;
    lv_style_init(&tab_style);
    lv_style_set_radius(&tab_style, 10);
    lv_style_set_bg_opa(&tab_style, LV_OPA_COVER);
    lv_style_set_bg_color(&tab_style, fun_green);
    lv_style_set_border_color(&tab_style, lv_color_black());
    lv_style_set_border_width(&tab_style, 2);
	lv_style_set_text_color(&tab_style, lv_color_white());

    lv_obj_add_style(tab1, &tab_style, 0);
    lv_obj_add_style(tab2, &tab_style, 0);
    lv_obj_add_style(tab3, &tab_style, 0);
    
    static lv_style_t text_style;
    lv_style_init(&text_style);
    lv_style_set_bg_opa(&tab_style, LV_OPA_COVER);
    lv_style_set_border_color(&tab_style, fun_green);
	lv_style_set_text_color(&tab_style, fun_green);

    lv_obj_add_style(tab_label, &text_style, 0);

    
    lv_label_set_text(tab_label, "");

    tab_label = lv_label_create(tab2);
    lv_label_set_text(tab_label, "");

    tab_label = lv_label_create(tab3);
    lv_label_set_text(tab_label, "");

}

static void event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        LV_LOG_USER("Option: %s", buf);
        if (lv_dropdown_get_selected(obj) == 0){
            lv_tabview_set_act(tabview, 0, LV_ANIM_ON);
        } else if (lv_dropdown_get_selected(obj) == 1){
            lv_tabview_set_act(tabview, 1, LV_ANIM_ON);
        } else if (lv_dropdown_get_selected(obj) == 2 ){
            lv_tabview_set_act(tabview, 2, LV_ANIM_ON);
        }
    }
}

void lv_example_dropdown_1(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 10);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_color_white());
    lv_style_set_border_color(&style, lv_color_black());
    lv_style_set_border_width(&style, 2);
	lv_style_set_text_color(&style, lv_color_black());

    lv_obj_t * dd1 = lv_dropdown_create(lv_scr_act());
    lv_obj_add_style(dd1, &style, 0);
    lv_dropdown_set_options(dd1, LV_SYMBOL_GPS "  AUTOS\n"
                            LV_SYMBOL_DIRECTORY "  MOTORS\n"
                            LV_SYMBOL_WARNING "  SENSORS"
							);
    lv_obj_set_width(dd1, 150);
    lv_dropdown_set_symbol(dd1, &LV_SYMBOL_SETTINGS);	
	lv_dropdown_set_selected_highlight(dd1, true);
    lv_obj_align(dd1, LV_ALIGN_TOP_LEFT, 20, 20);
    lv_obj_add_event_cb(dd1, event_handler, LV_EVENT_ALL, NULL);
}





void initialize() {
    set_tabs();
    lv_example_dropdown_1();
}



void disabled() {}

void competition_initialize() {}

void autonomous() {
    if (auto_picker == 1){
        //code for half AWP here
    } else if (auto_picker == 2){
        //code for far side 20pt here 
    } else if (auto_picker == 3){
        //code for disrupt here
    } else if (auto_picker == 4){
        //code for skills here
    } else {
        //default auto here
    }
}


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