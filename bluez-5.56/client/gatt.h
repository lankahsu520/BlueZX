/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2014  Intel Corporation. All rights reserved.
 *
 *
 */
#ifndef __GATT_H__
#define __GATT_H__

#ifdef BLUEZX
#define APP_PATH "/org/bluez/app"
#define DEVICE_INTERFACE "org.bluez.Device1"
#define PROFILE_INTERFACE "org.bluez.GattProfile1"
#define SERVICE_INTERFACE "org.bluez.GattService1"
#define CHRC_INTERFACE "org.bluez.GattCharacteristic1"
#define DESC_INTERFACE "org.bluez.GattDescriptor1"

/* String display constants */
#define COLORED_NEW	COLOR_GREEN "NEW" COLOR_OFF
#define COLORED_CHG	COLOR_YELLOW "CHG" COLOR_OFF
#define COLORED_DEL	COLOR_RED "DEL" COLOR_OFF

#define MAX_ATTR_VAL_LEN	512

struct desc {
	struct chrc *chrc;
	char *path;
	uint16_t handle;
	char *uuid;
	char **flags;
	size_t value_len;
	unsigned int max_val_len;
	uint8_t *value;
};

struct chrc {
	struct service *service;
	GDBusProxy *proxy;
	char *path;
	uint16_t handle;
	char *uuid;
	char **flags;
	bool notifying;
	GList *descs;
	size_t value_len;
	unsigned int max_val_len;
#ifdef BLUEZX
	QBUF_t qbuf;
	union
	{
		uint16_t *value16;
		uint8_t *value;
	};
#else
	uint8_t *value;
#endif
	uint16_t mtu;
	struct io *write_io;
	struct io *notify_io;
	bool authorization_req;
};

struct service {
	DBusConnection *conn;
	GDBusProxy *proxy;
	char *path;
	uint16_t handle;
	char *uuid;
	bool primary;
	GList *chrcs;
	GList *inc;
};
#endif

void gatt_add_service(GDBusProxy *proxy);
void gatt_remove_service(GDBusProxy *proxy);

void gatt_add_characteristic(GDBusProxy *proxy);
void gatt_remove_characteristic(GDBusProxy *proxy);

void gatt_add_descriptor(GDBusProxy *proxy);
void gatt_remove_descriptor(GDBusProxy *proxy);

void gatt_list_attributes(const char *device);
GDBusProxy *gatt_select_attribute(GDBusProxy *parent, const char *path);
char *gatt_attribute_generator(const char *text, int state);

void gatt_read_attribute(GDBusProxy *proxy, int argc, char *argv[]);
void gatt_write_attribute(GDBusProxy *proxy, int argc, char *argv[]);
void gatt_notify_attribute(GDBusProxy *proxy, bool enable);
void gatt_clone_attribute(GDBusProxy *proxy, int argc, char *argv[]);

void gatt_acquire_write(GDBusProxy *proxy, const char *arg);
void gatt_release_write(GDBusProxy *proxy, const char *arg);

void gatt_acquire_notify(GDBusProxy *proxy, const char *arg);
void gatt_release_notify(GDBusProxy *proxy, const char *arg);

void gatt_add_manager(GDBusProxy *proxy);
void gatt_remove_manager(GDBusProxy *proxy);

void gatt_register_app(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);
void gatt_unregister_app(DBusConnection *conn, GDBusProxy *proxy);

void gatt_register_service(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);
void gatt_unregister_service(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);

void gatt_register_chrc(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);
void gatt_unregister_chrc(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);

void gatt_register_desc(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);
void gatt_unregister_desc(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);

void gatt_register_include(DBusConnection *conn, GDBusProxy *proxy,
					int argc, char *argv[]);
void gatt_unregister_include(DBusConnection *conn, GDBusProxy *proxy,
						int argc, char *argv[]);

#ifdef BLUEZX
void chrc_set_short(uint16_t value16, void *user_data);
#endif

#endif
