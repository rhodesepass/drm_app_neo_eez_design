#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

groups_t groups;
static bool groups_created = false;

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

static void event_handler_cb_mainmenu_mainmenu(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
        lv_group_add_obj(groups.op, objects.oplst_btn);
        lv_group_add_obj(groups.op, objects.sett_btn);
        lv_group_add_obj(groups.op, objects.dev_btn);
        lv_group_add_obj(groups.op, objects.file_btn);
        lv_group_add_obj(groups.op, objects.brightness_scroller);
        lv_group_add_obj(groups.op, objects.restart_app_btn);
        lv_group_add_obj(groups.op, objects.shutdown_btn);
    }
}

static void event_handler_cb_mainmenu_brightness_scroller(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_brightness(value);
        }
    }
}

static void event_handler_cb_oplist_oplist(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
        lv_group_add_obj(groups.op, objects.btn1);
        lv_group_add_obj(groups.op, objects.btn2);
        lv_group_add_obj(groups.op, objects.btn3);
        lv_group_add_obj(groups.op, objects.btn4);
        lv_group_add_obj(groups.op, objects.mainmenu_btn);
    }
}

static void event_handler_cb_sysinfo_sysinfo(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
        lv_group_add_obj(groups.op, objects.obj7);
        lv_group_add_obj(groups.op, objects.back_btn);
    }
}

static void event_handler_cb_sysinfo_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_nand_percent(value);
        }
    }
}

static void event_handler_cb_sysinfo_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_sd_percent(value);
        }
    }
}

static void event_handler_cb_spinner_spinner(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
    }
}

static void event_handler_cb_displayimg_displayimg(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
    }
}

static void event_handler_cb_filemanager_filemanager(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
    }
}

static void event_handler_cb_settings_settings(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
        lv_group_add_obj(groups.op, objects.swmode_dropdown);
        lv_group_add_obj(groups.op, objects.swint_dropdown);
        lv_group_add_obj(groups.op, objects.usbmode_dropdown);
        lv_group_add_obj(groups.op, objects.lowbat_trip);
        lv_group_add_obj(groups.op, objects.no_intro_block);
        lv_group_add_obj(groups.op, objects.no_overlay_block);
        lv_group_add_obj(groups.op, objects.back_btn_1);
    }
}

static void event_handler_cb_settings_swmode_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_sw_mode(value);
        }
    }
}

static void event_handler_cb_settings_swint_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_sw_interval(value);
        }
    }
}

static void event_handler_cb_settings_usbmode_dropdown(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            set_var_usb_mode(value);
        }
    }
}

static void event_handler_cb_battery_alert_battery_alert(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: op
        lv_group_remove_all_objs(groups.op);
    }
}

void create_screen_mainmenu() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.mainmenu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)0);
    lv_obj_add_event_cb(obj, event_handler_cb_mainmenu_mainmenu, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 14, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_prts);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 51, 11);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "主菜单");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 19, 296);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "亮度");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 154, 391);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_small(obj);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 20, 391);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_small(obj);
            lv_label_set_text(obj, "电子通行证播放程序\n罗德岛工程部 白银 1097. \nhttps://github.com/rhodesepass");
        }
        {
            // oplst_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.oplst_btn = obj;
            lv_obj_set_pos(obj, 23, 52);
            lv_obj_set_size(obj, 97, 112);
            lv_obj_add_event_cb(obj, action_show_oplist, LV_EVENT_PRESSED, (void *)0);
            add_style_main_btn(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 6, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_fa_label(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 34);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "干员");
                }
            }
        }
        {
            // sett_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.sett_btn = obj;
            lv_obj_set_pos(obj, 129, 52);
            lv_obj_set_size(obj, 97, 112);
            lv_obj_add_event_cb(obj, action_show_settings, LV_EVENT_PRESSED, (void *)0);
            add_style_main_btn(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 3, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_fa_label(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 34);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "设置");
                }
            }
        }
        {
            // dev_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dev_btn = obj;
            lv_obj_set_pos(obj, 235, 52);
            lv_obj_set_size(obj, 97, 112);
            lv_obj_add_event_cb(obj, action_show_sysinfo, LV_EVENT_PRESSED, (void *)0);
            add_style_main_btn(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 10, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_fa_label(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 34);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "设备");
                }
            }
        }
        {
            // file_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.file_btn = obj;
            lv_obj_set_pos(obj, 24, 172);
            lv_obj_set_size(obj, 97, 112);
            lv_obj_add_event_cb(obj, action_show_files, LV_EVENT_PRESSED, (void *)0);
            add_style_main_btn(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 10, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_fa_label(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 34);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "文件");
                }
            }
        }
        {
            // brightness_scroller
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.brightness_scroller = obj;
            lv_obj_set_pos(obj, 84, 304);
            lv_obj_set_size(obj, 251, 13);
            lv_slider_set_range(obj, 1, 9);
            lv_obj_add_event_cb(obj, event_handler_cb_mainmenu_brightness_scroller, LV_EVENT_ALL, 0);
        }
        {
            // restart_app_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.restart_app_btn = obj;
            lv_obj_set_pos(obj, 19, 328);
            lv_obj_set_size(obj, 153, 52);
            lv_obj_add_event_cb(obj, action_restart_app, LV_EVENT_PRESSED, (void *)0);
            add_style_main_small_btn(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "重启程序");
                }
            }
        }
        {
            // shutdown_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.shutdown_btn = obj;
            lv_obj_set_pos(obj, 177, 329);
            lv_obj_set_size(obj, 158, 52);
            lv_obj_add_event_cb(obj, action_shutdown, LV_EVENT_PRESSED, (void *)0);
            add_style_main_small_btn(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "关机");
                }
            }
        }
    }
    
    tick_screen_mainmenu();
}

void tick_screen_mainmenu() {
    {
        const char *new_val = get_var_epass_version();
        const char *cur_val = lv_label_get_text(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_label_set_text(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_brightness();
        int32_t cur_val = lv_slider_get_value(objects.brightness_scroller);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.brightness_scroller;
            lv_slider_set_value(objects.brightness_scroller, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_oplist() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.oplist = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)1);
    lv_obj_add_event_cb(obj, event_handler_cb_oplist_oplist, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_list_create(parent_obj);
            lv_obj_set_pos(obj, 14, 40);
            lv_obj_set_size(obj, 332, 280);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_ON);
            lv_obj_set_scroll_dir(obj, LV_DIR_VER);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn1 = obj;
                    lv_obj_set_pos(obj, 14, 214);
                    lv_obj_set_size(obj, 318, 80);
                    add_style_op_btn(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 300, 64);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            create_user_widget_operator_entry(obj, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                        }
                    }
                }
                {
                    // btn2
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn2 = obj;
                    lv_obj_set_pos(obj, 14, 214);
                    lv_obj_set_size(obj, 318, 80);
                    add_style_op_btn(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj2 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 300, 64);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            create_user_widget_operator_entry(obj, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                        }
                    }
                }
                {
                    // btn3
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn3 = obj;
                    lv_obj_set_pos(obj, 14, 214);
                    lv_obj_set_size(obj, 318, 80);
                    add_style_op_btn(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj3 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 300, 64);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            create_user_widget_operator_entry(obj, 22);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                        }
                    }
                }
                {
                    // btn4
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn4 = obj;
                    lv_obj_set_pos(obj, 14, 214);
                    lv_obj_set_size(obj, 318, 80);
                    add_style_op_btn(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj4 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 300, 64);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            create_user_widget_operator_entry(obj, 24);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 51, 11);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "干员列表");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 14, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_prts);
        }
        {
            // mainmenu_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.mainmenu_btn = obj;
            lv_obj_set_pos(obj, 16, 327);
            lv_obj_set_size(obj, 316, 51);
            lv_obj_add_event_cb(obj, action_show_menu, LV_EVENT_PRESSED, (void *)1);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "主菜单");
                }
            }
        }
    }
    
    tick_screen_oplist();
}

void tick_screen_oplist() {
    tick_user_widget_operator_entry(18);
    tick_user_widget_operator_entry(20);
    tick_user_widget_operator_entry(22);
    tick_user_widget_operator_entry(24);
}

void create_screen_sysinfo() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.sysinfo = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)2);
    lv_obj_add_event_cb(obj, event_handler_cb_sysinfo_sysinfo, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 52, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "设备信息");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 12, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_prts);
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 36, 71);
            lv_obj_set_size(obj, 134, 140);
            lv_obj_add_event_cb(obj, event_handler_cb_sysinfo_obj5, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 191, 71);
            lv_obj_set_size(obj, 136, 140);
            lv_obj_add_event_cb(obj, event_handler_cb_sysinfo_obj6, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 53, 197);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "内部存储");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 230, 197);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "SD卡");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 36, 226);
            lv_obj_set_size(obj, 134, 26);
            add_style_label_small(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj9 = obj;
            lv_obj_set_pos(obj, 191, 227);
            lv_obj_set_size(obj, 136, 25);
            add_style_label_small(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj10 = obj;
            lv_obj_set_pos(obj, 22, 252);
            lv_obj_set_size(obj, 309, 229);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_ON);
            lv_obj_set_scroll_dir(obj, LV_DIR_VER);
            add_style_label_small(obj);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 22, 496);
            lv_obj_set_size(obj, 316, 52);
            lv_obj_add_event_cb(obj, action_format_sd_card, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff8c0f0f), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "格式化SD卡");
                }
            }
        }
        {
            // back_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_btn = obj;
            lv_obj_set_pos(obj, 23, 560);
            lv_obj_set_size(obj, 316, 51);
            lv_obj_add_event_cb(obj, action_show_menu, LV_EVENT_PRESSED, (void *)2);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "返回");
                }
            }
        }
    }
    
    tick_screen_sysinfo();
}

void tick_screen_sysinfo() {
    {
        int32_t new_val = get_var_nand_percent();
        int32_t cur_val = lv_arc_get_value(objects.obj5);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            lv_arc_set_value(objects.obj5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_sd_percent();
        int32_t cur_val = lv_arc_get_value(objects.obj6);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj6;
            lv_arc_set_value(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_nand_label();
        const char *cur_val = lv_label_get_text(objects.obj8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj8;
            lv_label_set_text(objects.obj8, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_sd_label();
        const char *cur_val = lv_label_get_text(objects.obj9);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj9;
            lv_label_set_text(objects.obj9, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_sysinfo();
        const char *cur_val = lv_label_get_text(objects.obj10);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj10;
            lv_label_set_text(objects.obj10, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_spinner() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.spinner = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)3);
    lv_obj_add_event_cb(obj, event_handler_cb_spinner_spinner, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 212, 23);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_small(obj);
            lv_label_set_text(obj, "正在提交反馈至神经...");
        }
        {
            lv_obj_t *obj = lv_spinner_create(parent_obj);
            objects.obj11 = obj;
            lv_obj_set_pos(obj, 159, 9);
            lv_obj_set_size(obj, 43, 44);
            lv_spinner_set_anim_params(obj, 1000, 60);
            lv_obj_set_style_arc_width(obj, 6, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffcdd0d3), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj12 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(50), LV_PCT(10));
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            add_style_label_small(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffa4a4a4), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_sourcesans_reg_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, -3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "RDEP Connection\n====> Rhodes Island\n[OK] TLS Handshake\n[OK] ::3323 -> ::23 Open");
        }
    }
    
    tick_screen_spinner();
}

void tick_screen_spinner() {
}

void create_screen_displayimg() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.displayimg = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_displayimg_key, LV_EVENT_KEY, (void *)0);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)4);
    lv_obj_add_event_cb(obj, event_handler_cb_displayimg_displayimg, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 52, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "扩列信息");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 12, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_prts);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj13 = obj;
            lv_obj_set_pos(obj, 157, 16);
            lv_obj_set_size(obj, 86, 29);
            add_style_label_large(obj);
            lv_label_set_text(obj, "");
        }
        {
            // disp_img_obj
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.disp_img_obj = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
            lv_image_set_src(obj, &img_oplogo);
        }
    }
    
    tick_screen_displayimg();
}

void tick_screen_displayimg() {
    {
        const char *new_val = get_var_displayimg_size_lbl();
        const char *cur_val = lv_label_get_text(objects.obj13);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj13;
            lv_label_set_text(objects.obj13, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_filemanager() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.filemanager = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)5);
    lv_obj_add_event_cb(obj, event_handler_cb_filemanager_filemanager, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            // file_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.file_container = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 360, 640);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_filemanager();
}

void tick_screen_filemanager() {
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)6);
    lv_obj_add_event_cb(obj, event_handler_cb_settings_settings, LV_EVENT_ALL, 0);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 51, 11);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "设备参数定值");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 14, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_prts);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 23, 50);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "切换模式");
        }
        {
            // swmode_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.swmode_dropdown = obj;
            lv_obj_set_pos(obj, 23, 86);
            lv_obj_set_size(obj, 151, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "顺序播放\n随机播放\n手动切换");
            lv_obj_add_event_cb(obj, event_handler_cb_settings_swmode_dropdown, LV_EVENT_ALL, 0);
            lv_obj_set_style_text_font(obj, &ui_font_sourcesans_reg_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_sourcesans_reg_14, LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 195, 50);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "自动切换间隔");
        }
        {
            // swint_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.swint_dropdown = obj;
            lv_obj_set_pos(obj, 195, 85);
            lv_obj_set_size(obj, 144, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "1分钟\n5分钟\n10分钟\n30分钟");
            lv_obj_add_event_cb(obj, event_handler_cb_settings_swint_dropdown, LV_EVENT_ALL, 0);
            lv_obj_set_style_text_font(obj, &ui_font_sourcesans_reg_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_sourcesans_reg_14, LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 138);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "USB模式");
        }
        {
            // usbmode_dropdown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.usbmode_dropdown = obj;
            lv_obj_set_pos(obj, 22, 167);
            lv_obj_set_size(obj, 151, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "文件(MTP)\nShell(串口)\n网络(rndis)\n仅充电");
            lv_obj_add_event_cb(obj, event_handler_cb_settings_usbmode_dropdown, LV_EVENT_ALL, 0);
            lv_obj_set_style_text_font(obj, &ui_font_sourcesans_reg_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_sourcesans_reg_14, LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            // lowbat_trip
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.lowbat_trip = obj;
            lv_obj_set_pos(obj, 279, 233);
            lv_obj_set_size(obj, 60, 29);
            lv_obj_add_event_cb(obj, action_settings_ctrl_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 233);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "低压保护出口软压板");
        }
        {
            // no_intro_block
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.no_intro_block = obj;
            lv_obj_set_pos(obj, 279, 277);
            lv_obj_set_size(obj, 60, 29);
            lv_obj_add_event_cb(obj, action_settings_ctrl_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 277);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "闭锁入场动画软压板");
        }
        {
            // no_overlay_block
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.no_overlay_block = obj;
            lv_obj_set_pos(obj, 279, 320);
            lv_obj_set_size(obj, 60, 29);
            lv_obj_add_event_cb(obj, action_settings_ctrl_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 320);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "闭锁干员信息软压板");
        }
        {
            // back_btn_1
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_btn_1 = obj;
            lv_obj_set_pos(obj, 23, 574);
            lv_obj_set_size(obj, 316, 51);
            lv_obj_add_event_cb(obj, action_show_menu, LV_EVENT_PRESSED, (void *)6);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_label_large(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "返回");
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
    {
        if (!(lv_obj_get_state(objects.swmode_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_sw_mode();
            int32_t cur_val = lv_dropdown_get_selected(objects.swmode_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.swmode_dropdown;
                lv_dropdown_set_selected(objects.swmode_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        if (!(lv_obj_get_state(objects.swint_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_sw_interval();
            int32_t cur_val = lv_dropdown_get_selected(objects.swint_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.swint_dropdown;
                lv_dropdown_set_selected(objects.swint_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        if (!(lv_obj_get_state(objects.usbmode_dropdown) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_usb_mode();
            int32_t cur_val = lv_dropdown_get_selected(objects.usbmode_dropdown);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.usbmode_dropdown;
                lv_dropdown_set_selected(objects.usbmode_dropdown, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_battery_alert() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.battery_alert = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 640);
    lv_obj_add_event_cb(obj, action_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, (void *)7);
    lv_obj_add_event_cb(obj, event_handler_cb_battery_alert_battery_alert, LV_EVENT_ALL, 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffb93030), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 9, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_fa_label(obj);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 69, 3);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_label_large(obj);
            lv_label_set_text(obj, "电池电量严重不足");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj14 = obj;
            lv_obj_set_pos(obj, 261, 3);
            lv_obj_set_size(obj, 99, 63);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff9b9999), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "PRTS Critical Warning\n============\n0xDEADBEEF");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 77, 35);
            lv_obj_set_size(obj, 192, 34);
            add_style_label_small(obj);
            lv_label_set_text(obj, "请尽快将您的通行认证终端\n连接至电源适配器。");
        }
    }
    
    tick_screen_battery_alert();
}

void tick_screen_battery_alert() {
}

void create_user_widget_operator_entry(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 64, 64);
            lv_image_set_src(obj, &img_oplogo);
            lv_image_set_scale(obj, 310);
            lv_image_set_inner_align(obj, LV_IMAGE_ALIGN_STRETCH);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 68, 0);
            lv_obj_set_size(obj, 232, 32);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            add_style_label_large(obj);
            lv_label_set_text(obj, "新约能天使-EP测试1233");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 68, 32);
            lv_obj_set_size(obj, 232, 32);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            add_style_label_small(obj);
            lv_obj_set_style_text_line_space(obj, -1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "谁不喜欢能天使呢？\n素材作者: 白银。");
        }
    }
}

void tick_user_widget_operator_entry(int startWidgetIndex) {
    (void)startWidgetIndex;
}


void ui_create_groups() {
    if (!groups_created) {
        groups.op = lv_group_create();
        groups_created = true;
    }
}


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_mainmenu,
    tick_screen_oplist,
    tick_screen_sysinfo,
    tick_screen_spinner,
    tick_screen_displayimg,
    tick_screen_filemanager,
    tick_screen_settings,
    tick_screen_battery_alert,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    ui_create_groups();
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_mainmenu();
    create_screen_oplist();
    create_screen_sysinfo();
    create_screen_spinner();
    create_screen_displayimg();
    create_screen_filemanager();
    create_screen_settings();
    create_screen_battery_alert();
}
