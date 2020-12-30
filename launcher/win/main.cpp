#include <XE.h>

#include <Windows.h>

LRESULT WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_DESTROY:
	case WM_QUIT:
		XE::IFramework::GetCurrentFramework()->Exit();
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}

void MessageLoop()
{
	MSG msg;
	if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

int main( int argc, char ** argv )
{
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = GetModuleHandle( NULL );
	wndclass.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wndclass.hCursor = LoadCursor( NULL, IDC_CROSS );
	wndclass.hbrBackground = (HBRUSH )GetStockObject( BLACK_BRUSH );
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "XE";

	RegisterClass( &wndclass );

	XE::CoreFramework framework;

	atexit( []()
			{
				XE::IFramework::GetCurrentFramework()->Exit();
			} );

	return framework.Exec( argc, argv, MessageLoop );
}