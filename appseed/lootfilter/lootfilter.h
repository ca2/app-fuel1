#pragma once


#include "sphere/sphere/sphere.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "core/user/userex/userex.h"
#include "core/user/html/html/html.h"
#include "app-core/appseed/gcom/gcom/gcom.h"

#ifdef _APP_FUEL_LOOTFILTER_LIBRARY
#define CLASS_DECL_APP_FUEL_LOOTFILTER  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_FUEL_LOOTFILTER  CLASS_DECL_IMPORT
#endif


namespace user
{

   typedef ::user::show < ::user::button > button_view;

} // namespace user

//void test_clone_local__should_clone_local(void);
void test_clone_local__hardlinks(void);
namespace lootfilter
{

   class application;
   class main_view;
   class document;
   class view;

} // namespace flag


#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::lootfilter::application > ())


#include "lootfilter_render.h"

#include "lootfilter_document.h"
#include "lootfilter_view_base.h"
#include "lootfilter_view.h"
//#include "lootfilter_lite_view.h"
//#include "lootfilter_full_view.h"
#include "lootfilter_main_view.h"
#include "lootfilter_frame.h"
#include "lootfilter_main_frame.h"
#include "lootfilter_pane_view_update_hint.h"
#include "lootfilter_pane_view.h"

#include "lootfilter_application.h"

