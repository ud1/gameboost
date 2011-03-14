/***********************************************************************
TODO: 
---  // ok >> Сделать шрифт .
--- сделать обр вызовы : отрисовка, обработку сообщений, клавиши, мышь.
--- 


************************************************************************/

// temp
//#define GB_OPENGL

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN




#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#include <windows.h>

//#include "appl_opengl.h" 
#include <gb/graphics/opengl/winappl/winappl_ogl.h>


// vg
//#include <gb/graphics/visual_geometry/visual_geometry.h>

// NDEBUG

using namespace gb::graphics::opengl::winappl;

// temp  experiment
void drawSampleLines()
{
	glBegin( GL_LINE_STRIP  );
	glVertex2f( 0.0 , 0.0f  );
	glVertex2f( 100.0 , 100.0f  );
	glVertex2f( 100.0 , 200.0f  );
	glVertex2f( 240.0 , 350.0f  );
	glVertex2f( 0.0 , 0.0f  );
	glEnd();
}

void drawSamplePoints()
{

	glPointSize(4);
	glColor3f ( 1.0f, 0.0f , 0.0f  );
	glBegin( GL_POINTS  );
	glVertex2f( 100.0 , 100.0f  );
	glEnd();

	glColor3f ( 0.0f, 1.0f , 0.0f  );
	glBegin( GL_POINTS  );
	glVertex2f( 200.0 , 200.0f  );
	glEnd(); 
 
	glPointSize(1);
}



ApplOpenGL *g_pApplOpenGl = NULL;


void  ReleaseFont(unsigned int base)
{
	if (base != 0)
		glDeleteLists(base, 96);

}
    

HRESULT OnDraw(ApplOpenGL* appl, void* pUserData) 
{
	HRESULT hr =0;
 
	return hr;
};

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
int main() {

#ifdef _DEBUG
	_CrtMemState _ms; 
	_CrtMemCheckpoint(&_ms); 
#endif


	g_pApplOpenGl = new  ApplOpenGL();

	APPL_OPENGL_INIT_DATA idata;
	idata.hInstance = 0 ; // hInstance;
	//idata.bWindowed = FALSE;
	idata.callback_ogl.funcOnFrameDraw  = OnDraw;

	g_pApplOpenGl->init(&idata);
	g_pApplOpenGl->run();


	delete g_pApplOpenGl;
	g_pApplOpenGl = NULL;


#ifdef _DEBUG
	_CrtMemDumpAllObjectsSince(&_ms);  
#endif

	return 0;
}