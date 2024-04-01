#include "main.h"
#include "liblvgl/lvgl.h"
#include "logo_black.h"
lv_color_t fun_green =  lv_color_make(0, 100, 46);
lv_color_t  highlight = lv_palette_main(LV_PALETTE_LIGHT_GREEN);
lv_obj_t * tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 0);
lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Tab 1");
lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");
lv_obj_t * description = lv_textarea_create(tab1);
int auto_picker = 0;
lv_obj_t* createImage(const lv_img_dsc_t* image, lv_obj_t* parent, int width, int height, int x, int y) {
    lv_obj_t* img = lv_img_create(parent);
    lv_img_set_src(img, image);
    lv_obj_set_width(img, width);
    lv_obj_set_height(img, height);
    lv_obj_set_x(img, x);
    lv_obj_set_y(img, y);
    return img;
}
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
static void format_table(lv_event_t * e){
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if(lv_event_get_code(e) == LV_EVENT_DRAW_PART_BEGIN){
        if(dsc->part == LV_PART_ITEMS) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
            dsc->label_dsc->color = lv_color_black();
            dsc->rect_dsc->bg_color = lv_color_white();
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
            dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
            dsc->label_dsc->color = lv_color_black();
            dsc->rect_dsc->bg_color = lv_color_white();
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;  
        }  
    }
}

static void highlight_row(lv_event_t * e){
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_cover_area(e);
    uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
    uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);
    uint16_t rowIndex;
    uint16_t colIndex;
    lv_table_get_selected_cell(obj, &rowIndex, &colIndex);
    printf("Row index: %d\n", rowIndex);
    if(rowIndex == row){
        if(dsc->part == LV_PART_ITEMS) {
            dsc->label_dsc->color = highlight;
            dsc->rect_dsc->bg_color = highlight;
        }  
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
    //style for the description on tab 1
    static lv_style_t ta_style;
    lv_style_init(&ta_style);
    lv_style_set_radius(&ta_style, 10);
    lv_style_set_bg_opa(&ta_style, LV_OPA_COVER);
    lv_style_set_bg_color(&ta_style, lv_color_white());
    lv_style_set_border_color(&ta_style, lv_color_black());
    lv_style_set_border_width(&ta_style, 2);
	lv_style_set_text_color(&ta_style, lv_color_black());
    //description for tab 1
    lv_obj_set_scrollbar_mode(description, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(description, LV_STATE_DISABLED);
    lv_obj_add_style(description, &ta_style, 0);
    lv_obj_set_pos(description, 130, 100);
    lv_obj_set_height(description, 95);
    lv_obj_set_width(description, 300);
    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_set_scrollbar_mode(tab1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(tab2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(tab3, LV_SCROLLBAR_MODE_OFF);
    // tab 1 buttons
    lv_obj_t * btn = lv_btn_create(tab1);
    static lv_style_t btn_style;
    lv_style_init(&btn_style);
    lv_style_set_bg_opa(&btn_style, LV_OPA_COVER);
    lv_style_set_bg_color(&btn_style, lv_color_black());
    lv_style_set_border_color(&btn_style, lv_color_black());
    lv_style_set_border_width(&btn_style, 2);
	lv_style_set_text_color(&btn_style, lv_color_white());
    lv_obj_add_style(btn, &btn_style, 0);
    
    lv_obj_set_pos(btn, 5, 45);
    lv_obj_set_size(btn, 120, 30);
    lv_obj_add_event_cb(btn, near_side_event, LV_EVENT_ALL, NULL);         
    lv_obj_t * label = lv_label_create(btn);         
    lv_label_set_text(label, "Near Side, 9pt");                   
    lv_obj_center(label);

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
    lv_textarea_set_text(description, "Default Auto");
    auto_picker = 0;
    lv_obj_add_style(btn, &btn_style, 0);

    //tab 2 buttons
    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 2.5, 45);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "1");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);
    
    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 80, 45);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "2");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);

    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 2.5, 85);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "3");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);

    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 80, 85);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "4");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);

    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 2.5, 125);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "5");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);

    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 80, 125);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "6");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);
    
    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 2.5, 165);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "7");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);

    // btn = lv_btn_create(tab2);
    // lv_obj_set_pos(btn, 80, 165);
    // lv_obj_set_size(btn, 75, 35);
    // lv_obj_add_event_cb(btn, skills_event, LV_EVENT_ALL, NULL);         
    // label = lv_label_create(btn);         
    // lv_label_set_text(label, "8");                   
    // lv_obj_center(label);
    // lv_obj_add_style(btn, &btn_style, 0);

    lv_obj_t * table = lv_table_create(tab2);
    lv_obj_set_style_border_color(table, lv_color_black(), 0);
    lv_obj_set_style_border_width(table, 2, 0);
    lv_obj_set_style_bg_color(table, lv_color_white(), 0);
    lv_obj_set_style_text_color(table, lv_color_black(), 0);
    lv_obj_set_style_text_align(table, LV_ALIGN_TOP_MID, 0);
    lv_obj_set_style_text_font(table, &lv_font_montserrat_10, 0);
    lv_obj_set_style_border_color(table, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(table, LV_OPA_COVER, 0);
    /*Fill the first column*/
    lv_table_set_cell_value(table, 0, 0, LV_SYMBOL_REFRESH "");
    lv_table_set_cell_value(table, 1, 0, "1");
    lv_table_set_cell_value(table, 2, 0, "2");
    lv_table_set_cell_value(table, 3, 0, "3");
    lv_table_set_cell_value(table, 4, 0, "4");
    lv_table_set_cell_value(table, 5, 0, "5");
    lv_table_set_cell_value(table, 6, 0, "6");
    lv_table_set_cell_value(table, 7, 0, "7");
    lv_table_set_cell_value(table, 8, 0, "8");
    /*Fill the second column*/
    lv_table_set_cell_value(table, 0, 1, LV_SYMBOL_FILE"");
    lv_table_set_cell_value(table, 1, 1, "1");
    lv_table_set_cell_value(table, 2, 1, "2");
    lv_table_set_cell_value(table, 3, 1, "3");
    lv_table_set_cell_value(table, 4, 1, "4");
    lv_table_set_cell_value(table, 5, 1, "5");
    lv_table_set_cell_value(table, 6, 1, "6");
    lv_table_set_cell_value(table, 7, 1, "7");
    lv_table_set_cell_value(table, 8, 1, "8");
    /*fill the third column*/
    lv_table_set_cell_value(table, 0, 2, LV_SYMBOL_CHARGE "");
    lv_table_set_cell_value(table, 1, 2, "1");
    lv_table_set_cell_value(table, 2, 2, "2");
    lv_table_set_cell_value(table, 3, 2, "3");
    lv_table_set_cell_value(table, 4, 2, "4");
    lv_table_set_cell_value(table, 5, 2, "5");
    lv_table_set_cell_value(table, 6, 2, "6");
    lv_table_set_cell_value(table, 7, 2, "7");
    lv_table_set_cell_value(table, 8, 2, "8");
    /*fill the fourth coloumn*/
    lv_table_set_cell_value(table, 0, 3, "%");
    lv_table_set_cell_value(table, 1, 3, "1");
    lv_table_set_cell_value(table, 2, 3, "2");
    lv_table_set_cell_value(table, 3, 3, "3");
    lv_table_set_cell_value(table, 4, 3, "4");
    lv_table_set_cell_value(table, 5, 3, "5");
    lv_table_set_cell_value(table, 6, 3, "6");
    lv_table_set_cell_value(table, 7, 3, "7");
    lv_table_set_cell_value(table, 8, 3, "8");
    /*fill the fifth coloumn*/
    lv_table_set_cell_value(table, 0, 5, LV_SYMBOL_GPS "");
    lv_table_set_cell_value(table, 1, 5, "1");
    lv_table_set_cell_value(table, 2, 5, "2");
    lv_table_set_cell_value(table, 3, 5, "3");
    lv_table_set_cell_value(table, 4, 5, "4");
    lv_table_set_cell_value(table, 5, 5, "5");
    lv_table_set_cell_value(table, 6, 5, "6");
    lv_table_set_cell_value(table, 7, 5, "7");
    lv_table_set_cell_value(table, 8, 5, "8");
    /*fill the sixth column */
    lv_table_set_cell_value(table, 0, 4, LV_SYMBOL_WARNING "");
    lv_table_set_cell_value(table, 1, 4, "1");
    lv_table_set_cell_value(table, 2, 4, "2");
    lv_table_set_cell_value(table, 3, 4, "3");
    lv_table_set_cell_value(table, 4, 4, "4");
    lv_table_set_cell_value(table, 5, 4, "5");
    lv_table_set_cell_value(table, 6, 4, "6");
    lv_table_set_cell_value(table, 7, 4, "7");
    lv_table_set_cell_value(table, 8, 4, "8");
    /*sets all widths of columns*/
    lv_table_set_col_width(table, 0, 50);
    lv_table_set_col_width(table, 1, 50);
    lv_table_set_col_width(table, 2, 50);
    lv_table_set_col_width(table, 3, 50);
    lv_table_set_col_width(table, 4, 50);
    lv_table_set_col_width(table, 5, 50);
    /*sets dimensions + position*/
    lv_obj_set_height(table, 220);
    lv_obj_set_width(table, 298.5);
    lv_obj_set_pos(table, 160, -5);
    lv_obj_set_scrollbar_mode(table, LV_SCROLLBAR_MODE_OFF);
    /*Add an event callback to to apply some custom drawing*/
    lv_obj_add_event_cb(table, format_table, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_add_event_cb(table, highlight_row, LV_EVENT_ALL, NULL);
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
    lv_obj_t * tab_label = lv_label_create(tab1);
    lv_obj_add_style(tab_label, &text_style, 0);
    lv_label_set_text(tab_label, "");
    tab_label = lv_label_create(tab2);
    lv_label_set_text(tab_label, "");
    tab_label = lv_label_create(tab3);
    lv_label_set_text(tab_label, "");
}

lv_obj_t* image = createImage(&logo_black, lv_scr_act(), 169, 120, 220, -5);

static void event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        LV_LOG_USER("Option: %s", buf);
        if (lv_dropdown_get_selected(obj) == 0){
            lv_obj_del(image);
            lv_tabview_set_act(tabview, 0, LV_ANIM_OFF);
            image = createImage(&logo_black, lv_scr_act(), 169, 120, 220, -5);
        } else if (lv_dropdown_get_selected(obj) == 1){
            lv_obj_del(image);
            lv_tabview_set_act(tabview, 1, LV_ANIM_OFF);
            image = createImage(&ghc_logo_black, lv_scr_act(), 150, 125, 12.5, 75);
        } else if (lv_dropdown_get_selected(obj) == 2 ){
            lv_obj_del(image);
            image = createImage(&logo_black, lv_scr_act(), 0, 0, 0, 0);
            lv_tabview_set_act(tabview, 2, LV_ANIM_OFF);
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
    lv_example_dropdown_1();}



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