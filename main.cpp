#include "MPDConnection.hpp"

using namespace std;

/*---------------------------------------*/

int main(int argc, char *argv[])
{
    MPDConnection my_con;
    my_con.connect();

    // cough.
    sleep(100);

    cout << "- Disconnecting." << endl;
    my_con.disconnect();
    return EXIT_SUCCESS;
}
