#include <mpd/client.h>
#include <glib.h>
#include <cstdlib>
#include <cstdio>

//--------------------------------

int main(int argc, char *argv[])
{
    struct mpd_connection * con = mpd_connection_new("localhost", 0, 3000);
    if(con != NULL)
    {
        while(true)
        {
            /* Prompt */
            g_printerr("$ ");

            /* Read in command and append a newline */
            char cmdbuf[1024] = {0};
            if(fgets(cmdbuf,1023, stdin) != 0)
            {
                if(g_ascii_strncasecmp(cmdbuf,"exit",4) == 0)
                    break;

                mpd_send_command(con,cmdbuf,NULL);

                struct mpd_pair * it;
                while((it = mpd_recv_pair(con)) != NULL)
                {
                    g_printerr("%s => %s\n",it->name, it->value);
                    mpd_enqueue_pair(con,it);
                }

                if(mpd_connection_get_error(con) != MPD_ERROR_SUCCESS)
                {
                    enum mpd_error err_code = mpd_connection_get_error(con);
                    if(err_code == MPD_ERROR_SERVER)
                    {
                        g_printerr("ServerError #%d: ",mpd_connection_get_server_error(con));
                    }
                    else
                    {
                        g_printerr("Error #%d: ",err_code);
                    }
                    g_printerr("%s\n",mpd_connection_get_error_message(con));

                    if(mpd_connection_clear_error(con) == false)
                    {
                        g_printerr("Mentioned error is fatal.\n");
                    }

                }
            }
            fflush(stdout);
        }

        mpd_connection_free(con);
    }
    return EXIT_SUCCESS;
}
