//
//  lootfilter_render.h
//  app_core_lootfilter
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#pragma once


namespace lootfilter
{


   class CLASS_DECL_APP_FUEL_LOOTFILTER render :
      virtual public ::thread
   {
   public:


      class filter
      {
      public:

         string         m_strPath;
         bool           m_b;
         bool           m_bNew;

         filter();
         filter(string strPath);
         ~filter();

      };

      double                           m_dRenderFps;
      bool                             m_bDib1;

      bool                             m_bAlternate;

      bool                             m_bLite;

      bool                             m_bImageEnable;

      mutex                            m_mutexWork;
      mutex                            m_mutexDraw;
      mutex                            m_mutexSwap;
      mutex                            m_mutexDib;
      mutex                            m_mutexDib23;

      bool                             m_bNewLayout;
      bool                             m_bHelloRender;
      int                              m_cx;
      int                              m_cy;
      int                              m_cxCache1;
      int                              m_cyCache1;
      int                              m_cxTarget;
      int                              m_cyTarget;

      ::visual::fastblur               m_dibImage;
      ::draw2d::dib_sp                 m_dibOut;
      ::draw2d::dib_sp                 m_dibA;
      ::draw2d::dib_sp                 m_dibB;
      ::visual::dib_sp                 m_dibWork;
      ::visual::fastblur               m_dib;
      ::visual::fastblur               m_dibTint;
      ::visual::dib_sp                 m_dibTemplate;
      ::visual::dib_sp                 m_dibTemplate2;

      bool                             m_bVoidTransfer;
      bool                             m_bFirstDone;

      ::draw2d::font_sp                m_font;

      double                           m_dMinRadius;
      double                           m_dMaxRadius;

      string                           m_strLootFilter;

      rect                             m_rectClient;


      mutex *                          m_pmutexText;

      view *                           m_pview;


      DWORD                            m_dwAnime;
      DWORD                            m_dwLastFast;
      DWORD                            m_dwFastAnime;
      ::visual::dib_sp                 m_dibFast;


      stringa                          m_stra23;
      string_map <::visual::dib_sp>    m_mapDib23;
      bool                             m_b23;
      uint32_t                         m_uiCurrent23;
      string                           m_strCurrent23;
      string                           m_strLast23;
      bool                             m_bFirst23;
      DWORD                            m_dw23;

      array < filter >                  m_filtera;
      DWORD                            m_dwLastOk;


      bool                             m_bFast;
      bool                             m_bFastOnEmpty;

      string                           m_strNewFont;
      string                           m_strHoverFont;
      string                           m_strFont;


      render(::aura::application * papp);
      virtual ~render();


      string get_lootfilter() { synch_lock slText(m_pmutexText);  string str(m_strLootFilter.c_str()); return str; }


      virtual void run() override;

      virtual bool initialize_render(string strId);


      virtual void full_render();
      virtual void lootfilter_render();
      virtual void lootfilter_draw();
      virtual void lootfilter_render(::draw2d::graphics * pgraphics);
      //virtual void lootfilter_render(::draw2d::graphics * pgraphics);

      virtual void lootfilter_render_full_view(::draw2d::graphics * pgraphics);
      virtual void lootfilter_render_lite_view(::draw2d::graphics * pgraphics);


      virtual void _001OnHelloDraw(::draw2d::graphics * pgraphics);

      virtual void defer_update_filter();

      ::visual::dib_sp & dib23(string strDib);

      virtual bool in_anime();
      virtual void lootfilter_fast_render(const string & strLootFilter);


   };


} // namespace lootfilter


