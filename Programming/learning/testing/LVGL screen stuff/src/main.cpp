#include "main.h"
#include "liblvgl/lvgl.h"
lv_color_t fun_green =  lv_color_make(0, 100, 46);
int updateBlud = 0;
void lv_example_menu_1(void) {
    /*Create a menu object*/
    lv_obj_t * menu = lv_menu_create(lv_scr_act());
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);
    lv_obj_set_style_bg_color(menu, fun_green, 0); 

    lv_obj_t * cont;
    lv_obj_t * label;
    
    /*Creates sub pages for every option*/
    lv_obj_t * autos_sub_page = lv_menu_page_create(menu, NULL);
        lv_obj_set_style_bg_color(autos_sub_page, fun_green, 0);
        cont = lv_menu_cont_create(autos_sub_page);
        label = lv_label_create(cont);
        lv_label_set_text(label, "Hello, this is the autos sub page");


    lv_obj_t * motors_sub_page = lv_menu_page_create(menu, NULL);
        lv_obj_set_style_bg_color(motors_sub_page, fun_green, 0);
        cont = lv_menu_cont_create(motors_sub_page);
        label = lv_label_create(cont);
        lv_label_set_text(label, "Hello, this is the motors sub page");


    lv_obj_t * sensors_sub_page = lv_menu_page_create(menu, NULL);
        lv_obj_set_style_bg_color(sensors_sub_page, fun_green, 0);  
        cont = lv_menu_cont_create(sensors_sub_page);
        label = lv_label_create(cont);
        lv_label_set_text(label, "Hello, this is the sensors sub page");

    /*Create a main page*/
    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_bg_color(main_page, fun_green, 0);

    lv_menu_set_page(menu, main_page);
    switch(updateBlud){
        case 1:
            lv_menu_set_page(menu, autos_sub_page);

        case 2:
            lv_menu_set_page(menu, motors_sub_page);

        case 3:
            lv_menu_set_page(menu, sensors_sub_page);
    }
}
void selector_dropdown(void){

}


bool auto_started = false;



void initialize()
{
    /*Create a Tab view object*/
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 80);
    lv_obj_set_style_bg_color(tabview, fun_green, 0);
    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, fun_green, 0);
    lv_obj_set_style_text_color(tab_btns, fun_green, 0);
    lv_obj_align(tab_btns, LV_ALIGN_TOP_LEFT, 20, 20);
    lv_obj_set_width(tab_btns, 150);
    lv_obj_set_height(tab_btns, 400);
    lv_obj_set_style_bg_color(tabview, fun_green, 0);
    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, LV_SYMBOL_GPS "  AUTOS");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");
    lv_obj_t * label = lv_label_create(tab1);

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
    lv_style_set_border_color(&tab_style, lv_color_black());
	lv_style_set_text_color(&tab_style, lv_color_white());

    lv_obj_add_style(label, &text_style, 0);


    lv_label_set_text(label, "First tab                      this is the first");

    label = lv_label_create(tab2);
    lv_label_set_text(label, "Second tab                      this is the second");

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Third tab                      this is the third");

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
    // if (lv_dropdown_get_selected(dd1) == 0){
    //     printf("hello1");
    //     lv_tabview_set_act(tabview, 0, LV_ANIM_OFF);
    // } else if (lv_dropdown_get_selected(dd1) == 1 ){
    //     printf("hello2");
    //     lv_tabview_set_act(tabview, 1, LV_ANIM_OFF);
    // } else if (lv_dropdown_get_selected(dd1) == 2){
    //     printf("hello3");
    //     lv_tabview_set_act(tabview, 2, LV_ANIM_OFF);
    // } 
    switch(lv_dropdown_get_selected(dd1)){
        case 0: 
            lv_tabview_set_act(tabview, 0, LV_ANIM_ON);
            break;
        case 1: 
            lv_tabview_set_act(tabview, 1, LV_ANIM_ON);
            break;
        case 2: 
            lv_tabview_set_act(tabview, 2, LV_ANIM_ON);
            break;
        case 4: 
            break;
    }
}



void disabled() {}

void competition_initialize() {}

void autonomous() {
    auto_started = true; 
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