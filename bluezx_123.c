/***************************************************************************
 * Copyright (C) 2022, Lanka Hsu, <lankahsu@gmail.com>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include <signal.h>
#include <getopt.h>

#include "utilx9.h"

#define TAG "bluezx_123"

#define USE_BLUEZX
#define USE_DBUSX_API

// ** app **
static int is_quit = 0;
char save_path[LEN_OF_BUF256]="/tmp";

#ifdef USE_BLUEZX
static BlueZX_t bluezx_123 = {
	.name = "bluezx_123",

	.isfree = 0,
	.isinit = 0,
};

void simple_gatt_chrc_write_value_cb(void *user_data, struct chrc *chrc, char *device, char *link)
{
	char *chrc_uuid = chrc->uuid;
	struct service *service = chrc->service;
	char *service_uuid = service->uuid;

	QBUF_t *qbuf = &chrc->qbuf;
	
	DBG_WN_DUMP(qbuf_buff(qbuf), qbuf_total(qbuf), " ", "(service_uuid: %s, chrc_uuid: %s, device: %s, link: %s)", service_uuid, chrc_uuid, device, link)

	chrc_set_short(1000, chrc);
}

void simple_client_ready_cb(GDBusClient *client, void *user_data)
{
	//bluezx_exec_helper(shell_exec_helper, &bluezx_123, "show", NULL);
	{
		char val[LEN_OF_BUF128] = "";
		bluezx_ctrl_property_get("Pairable", val);
		DBG_ER_LN("(Pairable, val: %s)", val);
		bluezx_ctrl_property_get("Address", val);
		DBG_ER_LN("(Address, val: %s)" , val);
	}

	char uuid[LEN_OF_UUID] = "";
	SAFE_SPRINTF(uuid, "0x%04X", UUID16_LANKAHSU520_SERVICE_F999);
	bluezx_exec_helper(shell_exec_helper, &bluezx_123, "gatt.register-service", uuid, NULL);

	SAFE_SPRINTF(uuid, "0x%04X", UUID16_LANKAHSU520_CHRC_F900);
	bluezx_exec_helper(shell_exec_helper, &bluezx_123, "gatt.register-characteristic", uuid, "read,write", NULL);

	SAFE_SPRINTF(uuid, "0x%04X", UUID16_LANKAHSU520_CHRC_F901);
	bluezx_exec_helper(shell_exec_helper, &bluezx_123, "gatt.register-characteristic", uuid, "read,write", NULL);

	bluezx_exec_helper(shell_exec_helper, &bluezx_123, "gatt.register-application", NULL);

	bluezx_exec_helper(shell_exec_helper, &bluezx_123, "advertise.name", "on", NULL);
	bluezx_exec_helper(shell_exec_helper, &bluezx_123, "advertise.timeout", "60", NULL);

	bluezx_exec_helper(shell_exec_helper, &bluezx_123, "advertise", "on", NULL);
}

void bluezx_commander(char *command)
{
	int argc = 0;
	char *argv[LEN_OF_BUF2048];
	char *saveptr = command;
	
	while ( (argv[argc++] = SAFE_STRTOK_R(NULL, "&", &saveptr)) )
	{
	}

	//ARGC_AND_ARGV_DUMP(argc-1, argv);
	shell_exec_helper(argc-1, argv, &bluezx_123);
}

#endif

#ifdef USE_DBUSX_API
static DbusX_t dbusx_123 = {
	.name = "dbusx_123",

	.isfree = 0,
	.isinit = 0,
	.isgdbus =1,

	.path = DBUS_PATH_LANKAHSU520,
	.dbus_conn = NULL,
	.dbus_conn_listen = NULL,
};

DBusHandlerResult demo_method_cb(DBusConnection *connection, DBusMessage *message, void *usr_data)
{
	dbus_bool_t handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	DBusError dbus_err;
	DBusMessage *dbus_msg_res; //response
	char *val = NULL;
	char *retStr = NULL;

	dbus_msg_res = dbus_message_new_method_return(message);
	if (!dbus_msg_res)
	{
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	SAFE_DBUS_ERR_INIT(&dbus_err);

	if (!dbus_message_get_args(message, &dbus_err, DBUS_TYPE_STRING, &val, DBUS_TYPE_INVALID))
	{
		DBG_ER_LN("dbus_message_get_args error !!! (message: %s)", dbus_err.message);
		handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		goto done;
	}

	DBG_DB_LN("%s (val: %s)", DBG_TXT_GOT, val);
#ifdef USE_BLUEZX
	if (val)
	{
		bluezx_commander(val);
	}
#endif

	SAFE_ASPRINTF(retStr, "%s", DBG_TXT_GOT);

	dbus_message_append_args(dbus_msg_res, DBUS_TYPE_STRING, &retStr, DBUS_TYPE_INVALID);
	dbus_connection_send(connection, dbus_msg_res, NULL);

	handled = DBUS_HANDLER_RESULT_HANDLED;

done:
	SAFE_FREE(retStr);
	SAFE_DBUS_MSG_FREE(dbus_msg_res);
	SAFE_DBUS_ERR_FREE(&dbus_err);

	return handled;
}

static DBusHandlerResult dbus_filter_cb(DBusConnection *connection, DBusMessage *message, void *usr_data)
{
	dbus_bool_t handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	//const char *method = dbus_message_get_member(message);
	//const char *iface = dbus_message_get_interface(message);
	//const char *path = dbus_message_get_path(message);

	if ( dbus_message_is_method_call(message, DBUS_M_IFAC_LANKAHSU520_DEMO, DBUS_METHOD_COMMAND))
	{
		handled = demo_method_cb(connection, message, NULL);
	}

	return handled;
}

static int dbus_match_cb(DBusConnection *dbus_listen, DBusError *err, void *usr_data)
{
	int ret = -1;

	dbus_bus_request_name(dbus_listen, DBUS_DEST_LANKAHSU520, DBUS_NAME_FLAG_REPLACE_EXISTING, err);
	if (dbus_error_is_set(err))
	{
		DBG_ER_LN("dbus_bus_request_name error !!! (%s, %s)", DBUS_DEST_LANKAHSU520, err->message );
		goto exit_match;
	}

	ret = 0;

exit_match:

	return ret;
}
#endif

static int app_quit(void)
{
	return is_quit;
}

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static void app_stop(void)
{
	if (app_quit()==0)
	{
		app_set_quit(1);

#ifdef USE_DBUSX_API
		dbusx_thread_close(&dbusx_123);
#endif

#ifdef USE_BLUEZX
		bluezx_thread_stop(&bluezx_123);
		bluezx_thread_close(&bluezx_123);
#endif
	}
}

static void app_loop(void)
{
#ifdef USE_DBUSX_API
	dbusx_thread_init(dbus_match_cb, dbus_filter_cb, &dbusx_123);
#endif

#ifdef USE_DBUSX_API
	{
		bluezx_123.gatt_chrc_write_value_cb = simple_gatt_chrc_write_value_cb;
		bluezx_123.client_ready_cb = simple_client_ready_cb;

		bluezx_thread_init(&bluezx_123, save_path);

		static int count = 0;
		while (app_quit()==0)
		{
			count++;
			if (count == 5)
			{
				bluezx_ctrl_pairable_set("on");
				bluezx_ctrl_pairable_set("off");
			}
			sleep(1);
		}
	}
#endif
}

static int app_init(void)
{
	int ret = 0;

	return ret;
}

static void app_exit(void)
{
	app_stop();
}

static void app_signal_handler(int signum)
{
	DBG_ER_LN("(signum: %d)", signum);
	switch (signum)
	{
		case SIGINT:
		case SIGTERM:
		case SIGHUP:
			app_stop();
			break;
		case SIGPIPE:
			break;

		case SIGUSR1:
			break;

		case SIGUSR2:
			dbg_lvl_round();
			DBG_ER_LN("dbg_lvl_get(): %d", dbg_lvl_get());
			break;
	}
}

static void app_signal_register(void)
{
	signal(SIGINT, app_signal_handler );
	signal(SIGTERM, app_signal_handler );
	signal(SIGHUP, app_signal_handler );
	signal(SIGUSR1, app_signal_handler );
	signal(SIGUSR2, app_signal_handler );

	signal(SIGPIPE, SIG_IGN );
}

int option_index = 0;
const char* short_options = "d:e:sh";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf( "Usage: %s\n"
					"  -d, --debug       debug level\n"
					"  -h, --help\n", TAG);
	printf( "Version: %s\n", version_show());
	printf( "Example:\n"
					"  %s -d 4 -s\n", TAG);
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	while((opt = getopt_long (argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch (opt)
		{
			case 'd':
				if (optarg)
				{
					dbg_lvl_set(atoi(optarg));
				}
				break;
			default:
				app_showusage(-1);
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	app_ParseArguments(argc, argv);
	app_signal_register();
	atexit(app_exit);

	if ( app_init() == -1 )
	{
		return -1;
	}

	app_loop();

	DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
