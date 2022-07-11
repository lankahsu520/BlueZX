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
#include "bluezx.h"

static BlueZX_t *bluezx_req_last = NULL;

void bluezx_ctrl_name_cb(char *name)
{
	DBG_IF_LN("(name: %s)", name);

	if (bluezx_req_last)
	{
		CTRL_t *ctrl = &bluezx_req_last->ctrl;
		SAFE_SPRINTF_EX(ctrl->name, "%s", name);
	}
}

void bluezx_ctrl_address_and_name_cb(char *address, char *name)
{
	DBG_IF_LN("(address: %s, name: %s)", address, name);

	if (bluezx_req_last)
	{
		CTRL_t *ctrl = &bluezx_req_last->ctrl;
		SAFE_SPRINTF_EX(ctrl->address, "%s", address);
		SAFE_SPRINTF_EX(ctrl->name, "%s", name);
	}
}

void bluezx_gatt_chrc_write_value_cb(struct chrc *chrc, char *device, char *link)
{
	char *chrc_uuid = chrc->uuid;
	struct service *service = chrc->service;
	char *service_uuid = service->uuid;

	DBG_TR_LN("(service_uuid: %s, chrc_uuid: %s, device: %s, link: %s)", service_uuid, chrc_uuid, device, link);

	if ( (bluezx_req_last) && (bluezx_req_last->gatt_chrc_write_value_cb) )
	{
		bluezx_req_last->gatt_chrc_write_value_cb(bluezx_req_last, chrc, device, link);
	}
}

void bluezx_gatt_application_registered_cb(void)
{
	if ( (bluezx_req_last) && (bluezx_req_last->gatt_application_registered_cb) )
	{
		bluezx_req_last->gatt_application_registered_cb(bluezx_req_last);
	}
}

void bluezx_gatt_register_service_cb(struct service *service)
{
	if ( (bluezx_req_last) && (bluezx_req_last->gatt_application_registered_cb) )
	{
		bluezx_req_last->gatt_register_service_cb(bluezx_req_last, service);
	}
}

void bluezx_gatt_register_chrc_cb(struct chrc *chrc)
{
	if ( (bluezx_req_last) && (bluezx_req_last->gatt_application_registered_cb) )
	{
		bluezx_req_last->gatt_register_chrc_cb(bluezx_req_last, chrc);
	}
}

void bluezx_advertising_set(BlueZX_t *bluezx_req, int isadvertising)
{
	if (bluezx_req)
	{
		bluezx_req->isadvertising = isadvertising;
		DBG_WN_LN("(bluezx_req->isadvertising: %d)", bluezx_req->isadvertising);
	}
}

int bluezx_advertising(BlueZX_t *bluezx_req)
{
	return bluezx_req->isadvertising;
}

void bluezx_advertising_registered_cb(void)
{
	if ( (bluezx_req_last) && (bluezx_req_last->advertising_registered_cb) )
	{
		bluezx_advertising_set(bluezx_req_last, 1);
		bluezx_req_last->advertising_registered_cb(bluezx_req_last);
	}
}

void bluezx_advertising_unregistered_cb(void)
{
	if ( (bluezx_req_last) && (bluezx_req_last->advertising_unregistered_cb) )
	{
		bluezx_advertising_set(bluezx_req_last, 0);
		bluezx_req_last->advertising_unregistered_cb(bluezx_req_last);
	}
}

void bluezx_advertising_released_cb(void)
{
	if ( (bluezx_req_last) && (bluezx_req_last->advertising_released_cb) )
	{
		bluezx_advertising_set(bluezx_req_last, 0);
		bluezx_req_last->advertising_released_cb(bluezx_req_last);
	}
}

void bluezx_agnet_set(BlueZX_t *bluezx_req, int isagent)
{
	if (bluezx_req_last)
	{
		bluezx_req_last->isagent = isagent;
		DBG_WN_LN("(bluezx_req_last->isagent: %d)", bluezx_req_last->isagent);
	}
}

int bluezx_agent(BlueZX_t *bluezx_req)
{
	if (bluezx_req_last)
	{
		return bluezx_req_last->isagent;
	}

	return bluezx_req->isagent;
}

void bluezx_agent_register_reply_cb(DBusMessage *message, void *user_data)
{
	if (bluezx_req_last)
	{
		bluezx_agnet_set(bluezx_req_last, 1);
	}
}

void bluezx_agent_release_cb(void)
{
	if (bluezx_req_last)
	{
		bluezx_agnet_set(bluezx_req_last, 0);
	}
}

void bluezx_client_ready_set(BlueZX_t *bluezx_req, READY_ID ready)
{
	if (bluezx_req)
	{
		bluezx_req->isready = ready;
	}
}

READY_ID bluezx_client_ready(BlueZX_t *bluezx_req)
{
	return bluezx_req->isready;
}

void bluezx_client_ready_cb(GDBusClient *client, void *user_data)
{
	BlueZX_t *bluezx_req = (BlueZX_t *)user_data;
	if (bluezx_req)
	{
		bluezx_client_ready_set(bluezx_req, READY_ID_OK);
		if (bluezx_req->client_ready_cb)
		{
			bluezx_req->client_ready_cb(client, user_data);
		}
	}
}

void bluezx_proxy_added_cb(GDBusProxy *proxy, void *user_data)
{
	BlueZX_t *bluezx_req = (BlueZX_t *)user_data;
	if (bluezx_req)
	{
		if (bluezx_req->proxy_added_cb)
		{
			bluezx_req->proxy_added_cb(proxy, user_data);
		}
	}
}

void bluezx_proxy_removed_cb(GDBusProxy *proxy, void *user_data)
{
	BlueZX_t *bluezx_req = (BlueZX_t *)user_data;
	if (bluezx_req)
	{
		if (bluezx_req->proxy_removed_cb)
		{
			bluezx_req->proxy_removed_cb(proxy, user_data);
		}
		
	}
}

void bluezx_property_changed_cb(GDBusProxy *proxy, const char *name, DBusMessageIter *iter, void *user_data)
{
	BlueZX_t *bluezx_req = (BlueZX_t *)user_data;
	if (bluezx_req)
	{
		if (bluezx_req->property_changed_cb)
		{
			bluezx_req->property_changed_cb(proxy, name, iter, user_data);
		}
		
	}
}

void bluezx_connect_handler_cb(DBusConnection *connection, void *user_data)
{
	BlueZX_t *bluezx_req = (BlueZX_t *)user_data;
	if (bluezx_req)
	{
		if (bluezx_req->connect_handler_cb)
		{
			bluezx_req->connect_handler_cb(connection, user_data);
		}
		
	}
}

void bluezx_disconnect_handler_cb(DBusConnection *connection, void *user_data)
{
	BlueZX_t *bluezx_req = (BlueZX_t *)user_data;
	if (bluezx_req)
	{
		if (bluezx_req->disconnect_handler_cb)
		{
			bluezx_req->disconnect_handler_cb(connection, user_data);
		}
		
	}
}

void bluezx_message_handler_cb(DBusConnection *connection, DBusMessage *message, void *user_data)
{
	BlueZX_t *bluezx_req = (BlueZX_t *)user_data;
	if (bluezx_req)
	{
		if (bluezx_req->message_handler_cb)
		{
			bluezx_req->message_handler_cb(connection, message, user_data);
		}
		
	}
}

static void *bluezx_thread_handler(void *user)
{
	BlueZX_t *bluezx_req = (BlueZX_t*)user;

	if (bluezx_req)
	{
		ThreadX_t *tidx_req = &bluezx_req->tidx;
		threadx_detach(tidx_req);

		int count = 0;
		DBG_IF_LN("(count: %d)", count++);

		if (1)
		{
			//bluezx_exec_helper(bluetoothctl_start, "blueway", "--repeater", NULL);
			DBG_WN_LN("bluezx listen ...");
			bluezx_exec_helper(bluetoothctl_start, bluezx_req, "./blueway", "--repeater", NULL);
		}
		else
		{
			while (threadx_isquit(tidx_req)==0)
			{
				DBG_IF_LN("(count: %d)", count++);
				sleep(1);
			}
		}

		threadx_leave(tidx_req);
	}
	DBG_IF_LN(DBG_TXT_BYE_BYE);

	return NULL;
}

int bluezx_exec_helper(exec_fn cb, void *user_data, char *action, ...)
{
	int ret = 0;
	int argc = 0;
	char *argv[5];

	if (action)
	{
		//argv[argc++] = action;
		SAFE_ASPRINTF(argv[argc++], "%s", action);
		va_list vargs;
		va_start(vargs, action);
		char *s = va_arg(vargs, char*);
		while (s)
		{
			SAFE_ASPRINTF(argv[argc++], "%s", s);
			s = va_arg(vargs, char*);
		}
		va_end(vargs);

		ret = cb(argc,  argv, user_data);

		int i = 0;
		for (i=0; i<argc; i++)
		{
			SAFE_FREE(argv[i]);
		}
	}

	return ret;
}

int bluezx_thread_init(BlueZX_t *bluezx_req, char *save_path)
{
	if ((bluezx_req == NULL) || (save_path==NULL))
	{
		return -1;
	}

	bluezx_req_last = bluezx_req;

	SAFE_SPRINTF(bluezx_req->save_path, "%s", save_path);

	CLIST_STRUCT_INIT(bluezx_req, chrc_list);

	{
		ThreadX_t *tidx_req = &bluezx_req->tidx;
		tidx_req->thread_cb = bluezx_thread_handler;
		tidx_req->data = bluezx_req;
		threadx_init(tidx_req, bluezx_req->name);
	}

	return 0;
}

void bluezx_thread_stop(BlueZX_t *bluezx_req)
{
	bt_shell_quit(EXIT_SUCCESS);

	if (bluezx_req)
	{
		ThreadX_t *tidx_req = &bluezx_req->tidx;
		threadx_stop(tidx_req);
	}
}

void bluezx_thread_close(BlueZX_t *bluezx_req)
{
	if ((bluezx_req) && (bluezx_req->isfree == 0))
	{
		bluezx_req->isfree ++;
	
		ThreadX_t *tidx_req = &bluezx_req->tidx;
		threadx_close(tidx_req);

		clist_free(bluezx_req->chrc_list);

		bluezx_req_last = NULL;
	}
}

