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

#ifndef __BLUETOOTHCTL_API_H__
#define __BLUETOOTHCTL_API_H__

//******************************************************************************
//** include **
//******************************************************************************
#include <glib.h>
#include "gdbus/gdbus.h"


//******************************************************************************
//** feature **
//******************************************************************************



//******************************************************************************
//** define **
//******************************************************************************
typedef int exec_fn(int argc, char *argv[], void *user_data);


//******************************************************************************
//** function **
//******************************************************************************
GList *bluezx_gatt_local_services_get(void);
GList *bluezx_gatt_services_get(void);
GList *bluezx_gatt_characteristics_get(void);
GList *bluezx_gatt_descriptors_get(void);;
GList *bluezx_gatt_managers_get(void);
GList *bluezx_gatt_uuids_get(void);
struct chrc *bluezx_gatt_read_chrc(char *service, char *chrc);

struct adapter *bluezx_ctrl_get(void);
GDBusProxy *bluezx_dev_get(void);
GDBusProxy *bluezx_attr_get(void);
GList *bluezx_ctrl_list_get(void);
GList *bluezx_battery_proxies_get(void);

int bluezx_ctrl_property_get(const char *name, char *value);

int bluetoothctl_start(int argc, char *argv[], void *user_data);


#endif
