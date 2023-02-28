
#include "Editor.h";

int main() { 
	Editor* pEditor = new Editor;
	int exitCode = pEditor->Run();
	delete pEditor;
	return exitCode;
}