#pragma once

#define WIN_WIDTH		1224
#define WIN_HEIGHT		968

#define IMGUI_INSPECTOR_WIDTH 300
#define IMGUI_BUT_HEIGHT      20

/* Message Box */
#ifndef			MSG_BOX
#define			MSG_BOX(_message)	MessageBox(NULL, TEXT(_message), L"Message", MB_OK)
#endif


/* Singleton */
#define NO_COPY(CLASSNAME)									\
		private:											\
		CLASSNAME(const CLASSNAME&) = delete;				\
		CLASSNAME& operator = (const CLASSNAME&) = delete;		

#define DECLARE_SINGLETON(CLASSNAME)					\
		NO_COPY(CLASSNAME)								\
		private:										\
		static CLASSNAME*	m_pInstance;				\
		public:											\
		static CLASSNAME*	GetInstance( void );		\
		static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
		CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
			if(NULL == m_pInstance) {					\
				m_pInstance = new CLASSNAME;			\
			}											\
			return m_pInstance;							\
		}												\
		void CLASSNAME::DestroyInstance( void ) {		\
			if(NULL != m_pInstance)	{					\
				delete m_pInstance;						\
				m_pInstance = NULL;						\
			}											\
		}


#define DT CCore::GetInstance()->fDeltaTime

extern HWND g_hWnd;
extern float g_nZoom;
extern bool g_bWheelUpdate;