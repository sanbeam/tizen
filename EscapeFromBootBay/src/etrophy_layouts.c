#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <Elementary.h>
#include <app.h>
#include "Etrophy.h"

#if ENABLE_NLS && HAVE_GETTEXT
# include <libintl.h>
# define _(str) dgettext(PACKAGE, str)
#else
# define _(str) str
#endif


static const char *_level_format_default_cb(const char *level);

static Elm_Genlist_Item_Class itc_group;
static Elm_Genlist_Item_Class itc;
static Etrophy_Level_Format_Cb _level_format_cb = _level_format_default_cb;

static const char *
_level_format_default_cb(const char *level EINA_UNUSED)
{
   return _("Level %s");
}

static char *
_group_text_get(void *data, Evas_Object *obj , const char *part )
{
   const Etrophy_Level *level = data;
   const char *level_name;
   char buf[128];

   level_name = etrophy_level_name_get(level);
   snprintf(buf, sizeof(buf), _level_format_cb(level_name), level_name);

   return strdup(buf);
}

static char *
_text_get(void *data, Evas_Object *obj , const char *part)
{
   const Etrophy_Score *score = data;
   char buf[128];

   if (!strcmp(part, "elm.text"))
     {
        const char *name = etrophy_score_player_name_get(score);
        if (name)
          return strdup(name);
        return NULL;
     }

   snprintf(buf, sizeof(buf), "%i", etrophy_score_score_get(score));
   return strdup(buf);
}

static void
_score_level_changed_cb(void *data, Evas_Object *obj, void *event_info )
{
   Evas_Object *genlist = data;
   Elm_Object_Item *item;
   int value, i = 0;

   value = elm_spinner_value_get(obj);
   item = elm_genlist_first_item_get(genlist);
   while (item)
     {
        if (elm_genlist_item_item_class_get(item) == &itc_group)
          if (value == i++)
            elm_genlist_item_bring_in(item, ELM_GENLIST_ITEM_SCROLLTO_TOP);
        item = elm_genlist_item_next_get(item);
     }
}

EAPI Evas_Object *
etrophy_score_layout_add(Evas_Object *parent, Etrophy_Gamescore *gamescore)
{
   Evas_Object *layout, *spinner, *genlist;
   const Eina_List *levels, *l;
   Etrophy_Level *level;
   int i = 0;

   layout = elm_layout_add(parent);
   char path[1024]; snprintf(path, 1025, "%s/etrophy.edj", app_get_resource_path());
   elm_layout_file_set(layout, path, "etrophy/scores/default");
   evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);

   genlist = elm_genlist_add(layout);
   elm_genlist_homogeneous_set(genlist, EINA_TRUE);
   evas_object_size_hint_weight_set(genlist, EVAS_HINT_EXPAND,
                                    EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_layout_content_set(layout, "list", genlist);

   spinner = elm_spinner_add(layout);
   elm_spinner_wrap_set(spinner, EINA_TRUE);
   elm_spinner_step_set(spinner, 1);
   elm_spinner_editable_set(spinner, EINA_FALSE);
   evas_object_smart_callback_add(spinner, "delay,changed",
                                  _score_level_changed_cb, genlist);
   evas_object_size_hint_weight_set(spinner, EVAS_HINT_EXPAND,
                                    EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(spinner, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_layout_content_set(layout, "selector", spinner);

   itc_group.item_style = "group_index";
   itc_group.func.text_get = _group_text_get;
   itc_group.func.content_get = NULL;
   itc_group.func.state_get = NULL;
   itc_group.func.del = NULL;

   itc.item_style = "double_label";
   itc.func.text_get = _text_get;
   itc.func.content_get = NULL;
   itc.func.state_get = NULL;
   itc.func.del = NULL;

   levels = etrophy_gamescore_levels_list_get(gamescore);
   elm_spinner_min_max_set(spinner, 0, eina_list_count(levels) - 1);

   EINA_LIST_FOREACH(levels, l, level)
     {
        Elm_Object_Item *group;
        const Eina_List *scores, *s;
        const char *level_name;
        Etrophy_Score *score;
        char buf[128];

        level_name = etrophy_level_name_get(level);
        snprintf(buf, sizeof(buf), _level_format_cb(level_name), level_name);
        elm_spinner_special_value_add(spinner, i++, buf);

        group = elm_genlist_item_append(genlist, &itc_group, level, NULL,
                                        ELM_GENLIST_ITEM_GROUP, NULL, NULL);
        elm_genlist_item_select_mode_set(group,
                                         ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);

        scores = etrophy_level_scores_list_get(level);
        EINA_LIST_FOREACH(scores, s, score)
          {
             Elm_Object_Item *item;
             item = elm_genlist_item_append(genlist, &itc, score, NULL,
                                            ELM_GENLIST_ITEM_NONE, NULL, NULL);
             elm_genlist_item_select_mode_set(
               item, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);
          }
     }

   return layout;
}

EAPI void
etrophy_level_format_cb_set(Etrophy_Level_Format_Cb callback)
{
   EINA_SAFETY_ON_NULL_RETURN(callback);
   _level_format_cb = callback;
}

EAPI Evas_Object *
etrophy_trophies_layout_add(Evas_Object *parent , Etrophy_Gamescore *gamescore )
{
   /* TODO */
   return NULL;
}

EAPI Evas_Object *
etrophy_locks_layout_add(Evas_Object *parent , Etrophy_Gamescore *gamescore )
{
   /* TODO */
   return NULL;
}
