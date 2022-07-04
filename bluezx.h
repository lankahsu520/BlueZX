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
#ifndef __BLUEZX_H__
#define __BLUEZX_H__

//******************************************************************************
//** include **
//******************************************************************************
#include "bluetoothctl_api.h"

#include "src/shared/shell.h"
#include "gatt.h"


//******************************************************************************
//** feature **
//******************************************************************************
#define UUID16_LANKAHSU520_SERVICE_F999           0xF999
#define UUID16_LANKAHSU520_CHRC_F900              0xF900
#define UUID16_LANKAHSU520_CHRC_F901              0xF901

#define VENDOR_DEFINED_UUID16_TABLE \
	{ UUID16_LANKAHSU520_SERVICE_F999, "LankaHsu520 service" }, \
	{ UUID16_LANKAHSU520_CHRC_F900, "LankaHsu520 F900" }, \
	{ UUID16_LANKAHSU520_CHRC_F901, "LankaHsu520 F901" }, \

//******************************************************************************
//** define **
//******************************************************************************
#ifndef DBG_COLOR
#define DBG_COLOR(color, format, args...) printf(color"[%02ld/%u] %s:%d - "format""COLORX_NONE,  (long) getpid(), (unsigned int)gettidv1_ex(), __FUNCTION__, __LINE__, ## args)
#define DBG_COLOR_0(color, format, args...) printf(color""format""COLORX_NONE, ## args)
#define DBG_R(format,args...) DBG_COLOR(COLORX_RED, format, ## args)
#define DBG_R_0(format,args...) DBG_COLOR_0(COLORX_RED, format, ## args)
#define DBG_P(format,args...) DBG_COLOR(COLORX_PURPLE, format, ## args)
#define DBG_P_0(format,args...) DBG_COLOR_0(COLORX_PURPLE, format, ## args)
#define DBG_Y(format,args...) DBG_COLOR(COLORX_YELLOW, format, ## args)
#define DBG_Y_0(format,args...) DBG_COLOR_0(COLORX_YELLOW, format, ## args)

#define DBG_ER(format,args...) if (dbg_more>=DBG_LVL_ERROR) DBG_R(format, ## args)
#define DBG_ER_0(format,args...) if (dbg_more>=DBG_LVL_ERROR) DBG_R_0(format, ## args)
#define DBG_WN(format,args...) if (dbg_more>=DBG_LVL_WARN) DBG_P(format, ## args)
#define DBG_WN_0(format,args...) if (dbg_more>=DBG_LVL_WARN) DBG_P_0(format, ## args)
#define DBG_IF(format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_Y(format, ## args)
#define DBG_IF_0(format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_Y_0(format, ## args)
#define DBG_DB(format,args...) if (dbg_more>=DBG_LVL_DEBUG) DBG_W(format, ## args)
#define DBG_DB_0(format,args...) if (dbg_more>=DBG_LVL_DEBUG) DBG_W_0(format, ## args)
#define DBG_TR(format,args...) if (dbg_more>=DBG_LVL_TRACE) DBG_LGR(format, ## args)
#define DBG_TR_0(format,args...) if (dbg_more>=DBG_LVL_TRACE) DBG_LGR_0(format, ## args)

#define ARGC_AND_ARGV_DUMP_COLOR(color,s1,s2) \
	{ int k =0; \
		DBG_COLOR(color,"(argc: %d", s1); \
		for (k = 0; k < s1; k++) \
		{ \
			DBG_COLOR_0(color,", [%s]", s2[k]); \
		} \
		DBG_COLOR_0(color,")\n"); \
	}

#define ARGC_AND_ARGV_ER_DUMP(s1,s2) ARGC_AND_ARGV_DUMP_COLOR(COLORX_RED,s1,s2)
#define ARGC_AND_ARGV_WN_DUMP(s1,s2) ARGC_AND_ARGV_DUMP_COLOR(COLORX_PURPLE,s1,s2)
#define ARGC_AND_ARGV_IF_DUMP(s1,s2) ARGC_AND_ARGV_DUMP_COLOR(COLORX_YELLOW,s1,s2)
#define ARGC_AND_ARGV_DB_DUMP(s1,s2) ARGC_AND_ARGV_DUMP_COLOR(COLORX_WHITE,s1,s2)
#define ARGC_AND_ARGV_TR_DUMP(s1,s2) ARGC_AND_ARGV_DUMP_COLOR(COLORX_LIGHT_GRAY,s1,s2)
#endif

//#define BT_SHELL_DBG(format, args...) bt_shell_printf("%s:%d - "format"", __FUNCTION__, __LINE__, ## args)
#define BT_SHELL_DBG(format, args...) ({ DBG_IF(format, ## args); })
//#define BT_SHELL_DBG_0(format, args...) bt_shell_printf("%s:%d - "format"", __FUNCTION__, __LINE__, ## args)
#define BT_SHELL_DBG_0(format, args...) ({ DBG_IF_0(format, ## args)}; })

#define ARGC_AND_ARGV_DUMP(s1,s2) ARGC_AND_ARGV_DB_DUMP(s1,s2)

typedef struct CHRC_Struct
{
	void* next;

	struct chrc *chrc;
} CHRC_t;

typedef void gatt_chrc_write_value_fn(void *user_data, struct chrc *chrc, char *device, char *link);
typedef void gatt_application_registered_fn(void *user_data);
typedef void gatt_register_service_fn(void *user_data, struct service *service);
typedef void gatt_register_chrc_fn(void *user_data, struct chrc *chrc);

typedef void advertising_registered_fn(void *user_data);
typedef void advertising_unregistered_fn(void *user_data);
typedef void advertising_released_fn(void *user_data);

typedef void client_ready_fn(GDBusClient *client, void *user_data);

typedef void proxy_added_fn(GDBusProxy *proxy, void *user_data);
typedef void proxy_removed_fn(GDBusProxy *proxy, void *user_data);
typedef void property_changed_fn(GDBusProxy *proxy, const char *name, DBusMessageIter *iter, void *user_data);

typedef void connect_handler_fn(DBusConnection *connection, void *user_data);
typedef void disconnect_handler_fn(DBusConnection *connection, void *user_data);
typedef void message_handler_fn(DBusConnection *connection, DBusMessage *message, void *user_data);

typedef struct BlueZX_Struct
{
	char name[LEN_OF_NAME32];

	ThreadX_t tidx;

	int isfree;
	int isinit;
	int isready;

	char save_path[LEN_OF_DIRNAME];

	CLIST_STRUCT(chrc_list);

	int isadvertising;
	int isagent;

	gatt_chrc_write_value_fn *gatt_chrc_write_value_cb;
	gatt_application_registered_fn *gatt_application_registered_cb;
	gatt_register_service_fn *gatt_register_service_cb;
	gatt_register_chrc_fn *gatt_register_chrc_cb;

	advertising_registered_fn *advertising_registered_cb;
	advertising_unregistered_fn *advertising_unregistered_cb;
	advertising_released_fn *advertising_released_cb;

	client_ready_fn *client_ready_cb;
	proxy_added_fn *proxy_added_cb;
	proxy_removed_fn *proxy_removed_cb;
	property_changed_fn *property_changed_cb;

	connect_handler_fn *connect_handler_cb;
	disconnect_handler_fn *disconnect_handler_cb;
	message_handler_fn *message_handler_cb;

	void *data;
} BlueZX_t;

//******************************************************************************
//** function **
//******************************************************************************
void bluezx_gatt_chrc_write_value_cb(struct chrc *chrc, char *device, char *link);
void bluezx_gatt_application_registered_cb(void);
void bluezx_gatt_register_service_cb(struct service *service);
void bluezx_gatt_register_chrc_cb(struct chrc *chrc);

void bluezx_advertising_set(BlueZX_t *bluezx_req, int isadvertising);
int bluezx_advertising(BlueZX_t *bluezx_req);
void bluezx_advertising_registered_cb(void);
void bluezx_advertising_unregistered_cb(void);
void bluezx_advertising_released_cb(void);

void bluezx_agnet_set(BlueZX_t *bluezx_req, int isagent);
int bluezx_agent(BlueZX_t *bluezx_req);
void bluezx_agent_register_reply_cb(DBusMessage *message, void *user_data);
void bluezx_agent_release_cb(void);

void bluezx_client_ready_set(BlueZX_t *bluezx_req, READY_ID ready);
READY_ID bluezx_client_ready(BlueZX_t *bluezx_req);
void bluezx_client_ready_cb(GDBusClient *client, void *user_data);

void bluezx_proxy_added_cb(GDBusProxy *proxy, void *user_data);
void bluezx_proxy_removed_cb(GDBusProxy *proxy, void *user_data);
void bluezx_property_changed_cb(GDBusProxy *proxy, const char *name, DBusMessageIter *iter, void *user_data);

void bluezx_connect_handler_cb(DBusConnection *connection, void *user_data);
void bluezx_disconnect_handler_cb(DBusConnection *connection, void *user_data);
void bluezx_message_handler_cb(DBusConnection *connection, DBusMessage *message, void *user_data);

int bluezx_exec_helper(exec_fn cb, void *user_data, char *action, ...);
void bluezx_ready_set(BlueZX_t *bluezx_req, READY_ID ready);

READY_ID bluezx_ready(BlueZX_t *bluezx_req);

int bluezx_thread_init(BlueZX_t *bluezx_req, char *save_path);
void bluezx_thread_stop(BlueZX_t *bluezx_req);
void bluezx_thread_close(BlueZX_t *bluezx_req);

#endif
