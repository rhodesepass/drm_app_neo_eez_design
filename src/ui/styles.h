#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: op_btn
lv_style_t *get_style_op_btn_MAIN_DEFAULT();
lv_style_t *get_style_op_btn_MAIN_FOCUSED();
void add_style_op_btn(lv_obj_t *obj);
void remove_style_op_btn(lv_obj_t *obj);

// Style: label_large
lv_style_t *get_style_label_large_MAIN_DEFAULT();
void add_style_label_large(lv_obj_t *obj);
void remove_style_label_large(lv_obj_t *obj);

// Style: label_small
lv_style_t *get_style_label_small_MAIN_DEFAULT();
void add_style_label_small(lv_obj_t *obj);
void remove_style_label_small(lv_obj_t *obj);

// Style: main_btn
lv_style_t *get_style_main_btn_MAIN_DEFAULT();
lv_style_t *get_style_main_btn_MAIN_FOCUSED();
void add_style_main_btn(lv_obj_t *obj);
void remove_style_main_btn(lv_obj_t *obj);

// Style: main_small_btn
lv_style_t *get_style_main_small_btn_MAIN_DEFAULT();
lv_style_t *get_style_main_small_btn_MAIN_FOCUSED();
void add_style_main_small_btn(lv_obj_t *obj);
void remove_style_main_small_btn(lv_obj_t *obj);

// Style: fa_label
lv_style_t *get_style_fa_label_MAIN_DEFAULT();
void add_style_fa_label(lv_obj_t *obj);
void remove_style_fa_label(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/