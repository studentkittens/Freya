#include "LogHandler.hh"

using namespace std;

int main() 
{
	_MSG(LOG_OK, "Some cool message.");
    Warning("Informal output");
	Info("printf formatting works %s","too"); 
    Error("Some error.");
    Fatal("This is fatal..");
    Debug("Debug message");
    LogHandler::instance().clear();
    return 0;
}
