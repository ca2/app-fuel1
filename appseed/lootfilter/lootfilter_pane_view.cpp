#include "framework.h"
#include <math.h>


namespace lootfilter
{

   pane_view::pane_view(::aura::application * papp) :
      object(papp),
      ::user::tab(papp),

      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
      m_pviewLast = NULL;
      m_pviewLastBilbo = NULL;
      m_prollfps = NULL;
      m_pviewdataTopic = NULL;
   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_view::install_message_routing(::message::sender * pinterface)
   {

      ::userex::pane_tab_view::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(::message::message * pobj)
   {
      if(pobj->previous())
         return;

      set_tab("Menu",::lootfilter::PaneViewMenu);
      set_tab("lootfilter", ::lootfilter::PaneViewLootFilter);
      set_tab("switcher",::lootfilter::PaneViewLootFilterSwitcher);
      set_tab("Font","font_sel");
#if 1
      set_tab("Open", "file_manager");
#endif

      //set_cur_tab_by_id(::lootfilter::PaneViewGcom);
      set_cur_tab_by_id(::lootfilter::PaneViewLootFilter);



   }



   void pane_view::_001OnNcDraw(::draw2d::graphics * pgraphics)
   {

      ::userex::pane_tab_view::_001OnNcDraw(pgraphics);

   }


   void pane_view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::userex::pane_tab_view::_001OnDraw(pgraphics);

   }


   void pane_view::on_show_view()
   {

      ::userex::pane_tab_view::on_show_view();
      string strId = get_view_id();
      stringa stra;
      m_prollfps = NULL;
      m_checkptraBilbo.remove_all();

      stra.explode("->:<-",strId);

      if (get_pane_by_id(::lootfilter::PaneViewMenu) != NULL && get_pane_by_id(::lootfilter::PaneViewMenu)->m_pholder != NULL)
      {

         get_pane_by_id(::lootfilter::PaneViewMenu)->m_pholder->ShowWindow(SW_HIDE);

      }

      if(get_view_id() == ::lootfilter::PaneViewLootFilter
            || get_view_id() == ::lootfilter::PaneViewLootFilterSwitcher
            || stra.contains(::str::from((int)::lootfilter::PaneViewLootFilter))
            || stra.contains(::str::from((int)::lootfilter::PaneViewLootFilterSwitcher)))
      {



         if(get_pane_by_id("file_manager") != NULL && get_pane_by_id("file_manager")->m_pholder != NULL)
         {

            get_pane_by_id("file_manager")->m_pholder->ShowWindow(SW_HIDE);

         }

         if (get_pane_by_id("font_sel") != NULL && get_pane_by_id("font_sel")->m_pholder != NULL)
         {

            get_pane_by_id("font_sel")->m_pholder->ShowWindow(SW_HIDE);

         }

         m_pviewLast = NULL;
         m_pviewLastBilbo = NULL;

         if(get_view_id() == ::lootfilter::PaneViewLootFilter)
         {

            m_pviewLast = dynamic_cast < view_base * > (get_pane_by_id(::lootfilter::PaneViewLootFilter)->m_pholder->get_child_by_id("lootfilter_view"));
            m_pviewLastBilbo = dynamic_cast < view * > (get_pane_by_id(::lootfilter::PaneViewLootFilter)->m_pholder->get_child_by_id("lootfilter_view"));
            m_pviewLast->set_need_layout();
            m_pviewdataTopic = m_pviewdata;
            m_strTopicTitle = get_pane_by_id(::lootfilter::PaneViewLootFilter)->m_straTitle.implode(" ");

         }
         else if (get_view_id() == ::lootfilter::PaneViewLootFilterSwitcher)
         {

            m_pviewLast = dynamic_cast < view_base * > (get_pane_by_id(::lootfilter::PaneViewLootFilterSwitcher)->m_pholder->get_child_by_id("lootfilter_view"));
            m_pviewLastBilbo = dynamic_cast < view * > (get_pane_by_id(::lootfilter::PaneViewLootFilterSwitcher)->m_pholder->get_child_by_id("lootfilter_view"));
            m_pviewLast->set_need_layout();
            m_pviewdataTopic = m_pviewdata;
            m_strTopicTitle = get_pane_by_id(::lootfilter::PaneViewLootFilterSwitcher)->m_straTitle.implode(" ");

         }


      }
      else if (get_view_id() == ::lootfilter::PaneViewMenu)
      {

         //::user::tab_pane * ppane = get_pane(id_pane(get_view_id()));

         ::file::path path = prepare_menu_view();

         m_pdocMenu->open_document(path);

//         if (m_pviewdata->m_pwnd != NULL)
//         {
//
//            m_pviewdata->m_pwnd->ShowWindow(SW_HIDE);
//
//         }

         string str;

         ::user::impact * pview = m_pdocMenu->get_view(0);

         m_prollfps = dynamic_cast <::calculator::plain_edit_view *> (pview->get_child_by_id("roll_fps"));

         m_pviewLast->data_get("cur_fps_text", str);

         if (m_prollfps != NULL)
         {

            m_prollfps->_001SetText(str, ::action::source_database);

         }

         if (m_pviewLastBilbo != NULL)
         {

            int i = 1;

            for (auto & filter : m_pviewLastBilbo->m_prender->m_filtera)
            {

               m_checkptraBilbo.add(dynamic_cast <::user::check_box *> (pview->get_child_by_id("filter" + ::str::from(i))));

               m_checkptraBilbo.last()->_001SetCheck(filter.m_b ? ::check::checked : ::check::unchecked, ::action::source_sync);

               i++;

            }

         }

      }
      else if (get_view_id() == "font_sel")
      {

         sp(::user::font_list_view) pfontview = get_pane_by_id("font_sel")->m_pholder->get_child_by_id("font_list_view");

         if (m_pviewLast != NULL && pfontview.is_set())
         {

            pfontview->set_sel_by_name(m_pviewLast->m_prender->m_strFont);

         }

      }


   }



   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      switch(pcreatordata->m_id)
      {
      case PaneViewMenu:
      {

         m_pdocMenu = Application.create_child_form(this,pcreatordata->m_pholder);

         ::user::impact * pview = m_pdocMenu->get_view(0);

         m_pviewdata->m_pwnd = pview->GetParentFrame();


         //::file::path path = prepare_menu_view();

         //m_pdocMenu->open_document(path);


//         m_prollspf = pview->get_child_by_id("roll_spf");
         //try
         //{
         //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(Application.should_auto_launch_clockverse_on_hover(),::action::source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag")->_001SetCheck(Application.should_bind_flag_country_ca2_domain_image_on_hover(),::action::source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag_auto")->_001SetCheck(Application.should_auto_launch_flag_on_hover(),::action::source_initialize);
         //}
         //catch(...)
         //{
         //}



      }
      break;
      case PaneViewLootFilter:
      {

         Application.m_ptemplateLootFilterView->create_subdocument(pcreatordata);

      }
      break;
      }

      ::userex::pane_tab_view::on_create_view(pcreatordata);

   }


   bool pane_view::BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent)
   {

      if(m_pdocMenu != NULL && dynamic_cast < ::user::impact * > (pview) == m_pdocMenu->get_view(0) && pevent->m_puie != NULL)
      {

         if(pevent->m_eevent == ::user::event_after_change_text)
         {

            if(m_prollfps != NULL && pevent->m_puie->m_id == "roll_fps" && !pevent->m_actioncontext.is_source(::action::source_initialize)
                  && !pevent->m_actioncontext.is_source(::action::source_database))
            {

               try
               {
                  string str;
                  double d = m_prollfps->get_ex_value()["real"];
                  if(m_pviewLast != NULL)
                  {


                     {

                        string str;

                        m_prollfps->_001GetText(str);

                        m_pviewLast->data_set("cur_fps_text",str);

                     }

                     {

                        var v;

                        v = d;

                        m_pviewLast->data_set("cur_fps",v);

                     }
                     m_pviewLast->m_dFps = d;
                     m_pviewLast->m_dwRoll = ::get_tick_count();
                  }
                  //if(fabs(d) < 0.0000000001)
                  //{
                  //   m_prollspf->_001SetText("",::action::source_initialize);
                  //}
                  //else
                  //{
                  //   m_prollspf->_001SetText(::str::from(1.0/d),::action::source_initialize);
                  //}
               }
               catch(...)
               {
               }

            }
            //else if(pevent->m_puie->m_id == "roll_spf" && !pevent->m_actioncontext.is_source(::action::source_initialize))
            //{

            //   try
            //   {
            //      string str;
            //      m_prollspf->_001GetText(str);
            //      double d = atof(str);
            //      if(fabs(d) < 0.0000000001)
            //      {
            //         m_prollfps->_001SetText("",::action::source_initialize);
            //      }
            //      else
            //      {
            //         m_pflagview->m_dFps = 1.0/ d;
            //         m_pflagview->m_dwRoll = ::get_tick_count();
            //         m_prollfps->_001SetText(::str::from(1.0 / d),::action::source_initialize);
            //      }
            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }
         else if (pevent->m_eevent == ::user::event_set_check && pevent->m_puie != NULL)
         {

            string strCheck = pevent->m_puie->m_id;


            if (::str::begins_eat_ci(strCheck, "filter"))
            {

               if (pevent->m_puie != NULL && !pevent->m_actioncontext.is_source(::action::source_initialize)
                     && !pevent->m_actioncontext.is_source(::action::source_sync))
               {

                  int iCheck = atoi(strCheck);

                  sp(::user::check) pcheck = pevent->m_puie;

                  if (m_pviewLastBilbo != NULL && pcheck.is_set())
                  {

                     m_pviewLastBilbo->m_prender->m_filtera[iCheck - 1].m_bNew = pcheck->_001GetCheck() == ::check::checked;

                     m_pviewLastBilbo->m_prender->defer_update_filter();

                  }

               }

            }

         }

         //if(pevent->m_puie->m_id == "clockverse")
         //   {
         //      Application.set_binding_clockverse_country_time_zone_set_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "clockverse_auto")
         //   {
         //      Application.set_auto_launch_clockverse_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "flag")
         //   {
         //      Application.set_binding_flag_country_ca2_domain_image_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "flag_auto")
         //   {
         //      Application.set_auto_launch_flag_on_hover(pevent->m_puie->_001GetCheck() == ::check::checked);
         //      return true;
         //   }
         //}
      }

      return false;
   }


   ::file::path pane_view::prepare_menu_view()
   {

      string str;

      string strBilbo;

      if (m_pviewLast == NULL && m_pviewLastBilbo == NULL)
      {

         str = Application.file().as_string("matter://home.html");

      }
      else
      {

         str = Application.file().as_string("matter://menu.html");

      }

      if (m_pviewLastBilbo != NULL)
      {

         int i = 1;

         for (auto & filter : m_pviewLastBilbo->m_prender->m_filtera)
         {

            ::file::path path = filter.m_strPath;

            string strName = path.name();

            strBilbo += "<input type=\"checkbox\" id=\"filter" + str::from(i) + "\" />filter &quot;" + strName + "&quot;<br/>\n<br/>";

            i++;

         }

      }

      if (m_strTopicTitle.has_char())
      {

         str.replace("Hellomultiverse!!", m_strTopicTitle);

      }
      else
      {

         str.replace("Hellomultiverse!!", "");

      }

      str.replace("***filter***", strBilbo);

      ::file::path path;

      path = Application.dir().userappdata() / "lootfilter_menu.html";

      Application.file().put_contents(path, str);

      return path;

   }


   void pane_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      ::user::view_update_hint * puh = dynamic_cast <::user::view_update_hint *> (phint);

      if (puh != NULL)
      {

         if (puh->m_ehint == ::user::view_update_hint::hint_control_event
               && puh->m_pui == m_pfontview
               && m_pviewLast != NULL)
         {

            if(puh->m_pusercontrolevent->m_eevent == ::user::event_after_change_cur_sel)
            {

               string strFont = m_pfontview->m_pview->get_cur_sel_face_name();

               if (strFont.has_char())
               {

                  m_pviewLast->m_prender->m_strHoverFont = strFont;

                  m_pviewLast->m_prender->m_strNewFont = strFont;

                  m_pviewLast->data_set("cur_font", strFont);

                  m_pviewLast->set_need_layout();

               }

            }
            else if (puh->m_pusercontrolevent->m_eevent == ::user::event_after_change_cur_hover)
            {

               string strFont = m_pfontview->m_pview->get_cur_hover_face_name();

               if (strFont.has_char())
               {

                  m_pviewLast->m_prender->m_strHoverFont = strFont;

                  m_pviewLast->set_need_layout();

               }

            }

         }

      }

      ::userex::pane_tab_view::on_update(pSender, lHint, phint);

   }


} // namespace lootfilter





