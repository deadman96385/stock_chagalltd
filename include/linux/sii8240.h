/*
 * Copyright (C) 2012 Samsung Electronics
 *
 * Author: Dharam Kumar <dharam.kr@samsung.com>
 *
 * Date: 3:00 PM, 31st May,2012
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __SII8240_H__
#define __SII8240_H__

#include <linux/notifier.h>
/* Different MHL Dongle/bridge which are used; may be
 * these enums are Samsung-Specific,but they do represent various
 * versions of dongles.
 */
enum dongle_type {
	DONGLE_NONE = 0,
	DONGLE_9290,
	DONGLE_9292,
};

enum connector_type {
	CONN_NONE = 0,
	CONN_5_PIN,	/* USB-type */
	CONN_11_PIN,	/* Galaxy-S3? */
	CONN_30_PIN,	/* Galaxy Tabs */
};

enum mhl_attached_type {
	MHL_DETTACHED = 0,
	MHL_ATTACHED,
};
struct sii8240_platform_data {

	/* Called to setup board-specific power operations */
	void (*power)(int on);
	/* In case,when connectors are not able to automatically switch the
	 * D+/D- Path to SII8240,do the switching manually.
	 */
	void (*enable_path)(bool enable);

	struct i2c_client *tmds_client;
	struct i2c_client *hdmi_client;
	struct i2c_client *disc_client;
	struct i2c_client *tpi_client;
	struct i2c_client *cbus_client;

	/* to handle board-specific connector info & callback */
	enum dongle_type dongle;
	enum connector_type conn;
	int (*reg_notifier)(struct notifier_block *nb);
	int (*unreg_notifier)(struct notifier_block *nb);

	u8 power_state;
	u8 swing_level;
	int ddc_i2c_num;

	void (*init)(void);
	void (*mhl_sel)(bool enable);
	void (*hw_onoff)(bool on);
	void (*hw_reset)(void);
	bool (*vbus_present)(void);
	void (*charger_mhl_cb)(bool attached, int charger);

#ifdef CONFIG_EXTCON
	const char *extcon_name;
#endif
};

void acc_notify(int event);

#endif /* __SII8240_H__ */
