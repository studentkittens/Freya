#include "Writer.hh"
using namespace std;

int main() 
{
    Warning("Informal output");
	Info("printf formatting works %s","too"); 
    Error("Some error.");
    Fatal("This is fatal..");
    Debug("Debug message");

    Log::Writer::instance().clear();
    return 0;
}
