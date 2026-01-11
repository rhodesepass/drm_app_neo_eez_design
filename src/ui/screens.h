#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _groups_t {
    lv_group_t *op;
} groups_t;

extern groups_t groups;

void ui_create_groups();

typedef struct _objects_t {
    lv_obj_t *mainmenu;
    lv_obj_t *oplist;
    lv_obj_t *sysinfo;
    lv_obj_t *spinner;
    lv_obj_t *displayimg;
    lv_obj_t *filemanager;
    lv_obj_t *settings;
    lv_obj_t *warning;
    lv_obj_t *oplst_btn;
    lv_obj_t *sett_btn;
    lv_obj_t *dev_btn;
    lv_obj_t *file_btn;
    lv_obj_t *dispimg_btn;
    lv_obj_t *brightness_scroller;
    lv_obj_t *restart_app_btn;
    lv_obj_t *shutdown_btn;
    lv_obj_t *obj0;
    lv_obj_t *oplst_container;
    lv_obj_t *obj1;
    lv_obj_t *obj1__opbtn;
    lv_obj_t *obj1__oplogo;
    lv_obj_t *obj1__opdesc;
    lv_obj_t *obj1__opname;
    lv_obj_t *obj2;
    lv_obj_t *obj2__opbtn;
    lv_obj_t *obj2__oplogo;
    lv_obj_t *obj2__opdesc;
    lv_obj_t *obj2__opname;
    lv_obj_t *mainmenu_btn;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *back_btn;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *dispimg_no_pic_label;
    lv_obj_t *dispimg_lbl_path;
    lv_obj_t *dispimg_container;
    lv_obj_t *obj11;
    lv_obj_t *file_container;
    lv_obj_t *lowbat_trip;
    lv_obj_t *no_intro_block;
    lv_obj_t *no_overlay_block;
    lv_obj_t *swmode_dropdown;
    lv_obj_t *swint_dropdown;
    lv_obj_t *usbmode_dropdown;
    lv_obj_t *back_btn_1;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAINMENU = 1,
    SCREEN_ID_OPLIST = 2,
    SCREEN_ID_SYSINFO = 3,
    SCREEN_ID_SPINNER = 4,
    SCREEN_ID_DISPLAYIMG = 5,
    SCREEN_ID_FILEMANAGER = 6,
    SCREEN_ID_SETTINGS = 7,
    SCREEN_ID_WARNING = 8,
};

void create_screen_mainmenu();
void tick_screen_mainmenu();

void create_screen_oplist();
void tick_screen_oplist();

void create_screen_sysinfo();
void tick_screen_sysinfo();

void create_screen_spinner();
void tick_screen_spinner();

void create_screen_displayimg();
void tick_screen_displayimg();

void create_screen_filemanager();
void tick_screen_filemanager();

void create_screen_settings();
void tick_screen_settings();

void create_screen_warning();
void tick_screen_warning();

void create_user_widget_operator_entry(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_operator_entry(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/