// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2018  Intel Corporation
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/signalfd.h>

#include <glib.h>

#include "mainloop.h"
#include "mainloop-notify.h"
#include "io.h"

static GMainLoop *main_loop;
static int exit_status;

void mainloop_init(void)
{
	main_loop = g_main_loop_new(NULL, FALSE);
	DBG_WN_LN("call mainloop_notify_init ... (main_loop: %p)", main_loop);
	mainloop_notify_init();
}

void mainloop_quit(void)
{
	if (!main_loop)
		return;

	DBG_WN_LN("call g_main_loop_quit ... (exit_status: %d)", exit_status);
	g_main_loop_quit(main_loop);

	mainloop_sd_notify("STOPPING=1");
}

void mainloop_exit_success(void)
{
	exit_status = EXIT_SUCCESS;
	DBG_WN_LN("call mainloop_quit ... (exit_status: %d)", exit_status);
	mainloop_quit();
}

void mainloop_exit_failure(void)
{
	exit_status = EXIT_FAILURE;
	DBG_WN_LN("call mainloop_quit ...");
	mainloop_quit();
}

int mainloop_run(void)
{
	if (!main_loop)
		return -EINVAL;

	DBG_WN_LN("call g_main_loop_run ...");
	g_main_loop_run(main_loop);

	g_main_loop_unref(main_loop);
	main_loop = NULL;

	mainloop_notify_exit();

	return exit_status;
}

int mainloop_add_fd(int fd, uint32_t events, mainloop_event_func callback,
				void *user_data, mainloop_destroy_func destroy)
{
	return -ENOSYS;
}

int mainloop_modify_fd(int fd, uint32_t events)
{
	return -ENOSYS;
}

int mainloop_remove_fd(int fd)
{
	return -ENOSYS;
}

int mainloop_add_timeout(unsigned int msec, mainloop_timeout_func callback,
				void *user_data, mainloop_destroy_func destroy)
{
	return -ENOSYS;
}

int mainloop_modify_timeout(int fd, unsigned int msec)
{
	return -ENOSYS;
}

int mainloop_remove_timeout(int id)
{
	return -ENOSYS;
}

int mainloop_set_signal(sigset_t *mask, mainloop_signal_func callback,
				void *user_data, mainloop_destroy_func destroy)
{
	return -ENOSYS;
}
