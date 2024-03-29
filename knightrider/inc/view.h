/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd
 *
 * Licensed under the Flora License, Version 1.1 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://floralicense.org/license/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */ 

#if !defined(_VIEW_H)
#define _VIEW_H

#include <w3cocf.h>

#define EDJ_DASH_FILE "edje/dash.edj"
#define EDJ_WHEEL_FILE "edje/wheel.edj"
#define GRP_MAIN "main"

#define RADIUS_MIN 82
#define CENTER_REF_X 180
#define CENTER_REF_Y 180

/* Slope value for circular touch layer */
#define SLOPE_36_DEGREE 0.7265
#define SLOPE_72_DEGREE 3.0776
#define SLOPE_108_DEGREE -3.0776
#define SLOPE_144_DEGREE -0.7265
#define SLOPE_180_DEGREE 0

#define DAIL_INPUT_MAX 128

/* Text Style for Dial Entry */
#define DIAL_TEXT_STYLE_NORMAL "DEFAULT='font=Tizen:style=Light font_size=34 align=center'"
#define DIAL_TEXT_STYLE_SMALL "DEFAULT='font=Tizen:style=Light font_size=28 align=center'"
#define DIAL_TEXT_STYLE_SMALLER "DEFAULT='font=Tizen:style=Regular font_size=23 align=center'"

#define ENTRY_TEXT_MAX DAIL_INPUT_MAX

/* Entry text Control Option */
#define ENTRY_TEXT_CLEAR_ALL 0
#define ENTRY_TEXT_ADD_TEXT 1
#define ENTRY_TEXT_BACKSPACE 2

#define LONGPRESS_TIME 0.5f

void view_create(void *data);
Evas_Object *view_create_win(const char *pkg_name);
Evas_Object *view_create_conformant_without_indicator(Evas_Object *win);
Evas_Object *view_create_layout(Evas_Object *parent, const char *file_path, const char *group_name, Eext_Event_Cb cb_function, void *user_data);
Evas_Object *view_create_layout_for_conformant(Evas_Object *parent, const char *file_path, const char *group_name, Eext_Event_Cb cb_function, void *user_data);
Evas_Object *view_create_layout_by_theme(Evas_Object *parent, const char *class_name, const char *group_name, const char *style);
void view_destroy(void *data);
void view_set_image(Evas_Object *parent, const char *part_name, const char *image_path);
void view_set_text(Evas_Object *parent, const char *part_name, const char *text);
void view_set_color(Evas_Object *parent, const char *part_name, int r, int g, int b, int a);
void view_set_button(Evas_Object *parent, const char *part_name, const char *style, const char *image_path, const char *text,
		Evas_Object_Event_Cb down_cb, Evas_Object_Event_Cb up_cb, Evas_Smart_Cb clicked_cb, void *user_data);
Evas_Object *view_create_entry(Evas_Object *parent, const char *part_name, Evas_Smart_Cb clicked_cb, void *user_data);

Evas_Object *view_dialer_create_rectangle(void *data);
void view_dialer_create(void *data, const char *file_path);
int view_dialer_set_entry_text(void *data, int operation, const char *text);
void view_dialer_set_entry(void *data, const char *part_name);
Evas_Object *view_dialer_get_layout_object(void *data);
void create_base_gui(void *data);
#endif
