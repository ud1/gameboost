 

#include <gb/graphics/d3d9/renderstate/vector_states.h>
#include <gb/system/console.h>


int   main() //int argc, _TCHAR* argv[])
{
	gb::system::console::setTextColorRed();
	printf("sample text \n");


	gb::graphics::d3d9::renderstate::StateValues   st;
	st.addState(  D3DRS_ZENABLE, 0 );
	st.addState( D3DRS_FILLMODE  , D3DFILL_WIREFRAME);

	std::string str;

	st.writeToStr(str, '\n', '=');

	bool bres = st.readFromStr(str, '\n', '=' );



	return 0;
}
