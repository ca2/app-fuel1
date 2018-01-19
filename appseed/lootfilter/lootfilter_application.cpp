#include "framework.h"


namespace lootfilter
{


   application::application() :
      m_mutexAiFont(this)
   {

      m_ptemplateLootFilterMain = NULL;
      m_ptemplateLootFilterView = NULL;

      m_strAppName = "lootfilter";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strLootFilterDefault = "Loot Filter!!";
      m_strAlternateLootFilterDefault = "Hello!!";

      m_strLootFilter = m_strLootFilterDefault;
      m_strAlternateLootFilter = m_strAlternateLootFilterDefault;

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_faceAi = NULL; // FT_Face m_faceAi;

      m_bMultiverseChat = true;

//      test_clone_local__should_clone_local();
      test_clone_local__hardlinks();


   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      set_local_data_key_modifier();

      ::core::session * pcoression = m_pauraapp->m_pcoresession;

      pcoression->use_font_sel();

      System.factory().creatable_small < ::lootfilter::document >();
      System.factory().creatable_small < ::lootfilter::frame >();
      System.factory().creatable_small < ::lootfilter::main_frame >();
      System.factory().creatable_small < ::user::button_view >();
      System.factory().creatable_small < ::lootfilter::view >();
      System.factory().creatable_small < ::lootfilter::main_view >();
      System.factory().creatable_small < ::lootfilter::pane_view >();

      if (!::sphere::application::init_instance())
      {

         return false;

      }

      string str = handler()->m_varTopicQuery["lootfilter"];

      if (str.has_char())
      {

         m_strLootFilter = str;

      }


      ::user::single_document_template* pDocTemplate;


      pDocTemplate = canew(::user::single_document_template(
                           this,
                           "main",
                           System.type_info < document >(),
                           System.type_info < main_frame >(),
                           System.type_info < pane_view >()));
      m_ptemplateLootFilterMain = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = canew(::user::single_document_template(
                           this,
                           "main",
                           System.type_info < document >(),
                           System.type_info < frame >(),
                           System.type_info < main_view >()));
      m_ptemplateLootFilterView = pDocTemplate;
      add_document_template(pDocTemplate);




      return true;

   }


   void application::term_application()
   {

      ::core::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef DEBUG

      output_debug_string("DEBUG build? (basis)");

      ASSERT(FALSE);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(FALSE);

#endif

#endif

      m_bMultiverseChat = !handler()->m_varTopicQuery["no_hello_edit"].is_set();

      if (m_ptemplateLootFilterMain->get_document_count() == 0)
      {

         m_ptemplateLootFilterMain->request_create(pcreate);

      }

      if (pcreate->m_spCommandLine->m_varFile.has_char())
      {

         m_ptemplateLootFilterView->request_create(pcreate);

      }

      if (handler()->m_varTopicQuery["wfi_maximize"].is_set())
      {

         pcreate->m_spCommandLine->m_varQuery["document"].cast < document >()->get_typed_view < ::userex::pane_tab_view >()->GetTopLevelFrame()->_001WindowMaximize();

      }

      output_debug_string("\nfinished lootfilter::on_request");

   }


   string application::preferred_userschema()
   {

      return "core";

   }


   int64_t application::add_ref()
   {

      return ::object::add_ref();

   }

   int64_t application::dec_ref()
   {

      return ::object::dec_ref();

   }


} // namespace lootfilter




extern "C"
::aura::library * app_core_lootfilter_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::lootfilter::application >(papp, "app-core/lootfilter");

}


aura_app aura_app_core_lootfilter("app-core/lootfilter", &app_core_lootfilter_get_new_library);


