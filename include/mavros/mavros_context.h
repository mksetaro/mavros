/**
 * @brief MAVROS Plugin context
 * @file mavros_plugin.h
 * @author Vladimir Ermakov <vooon341@gmail.com>
 *
 * @addtogroup plugin
 */
/*
 * Copyright 2014 Vladimir Ermakov.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#pragma once

#include <mavros/mavconn_interface.h>

namespace mavplugin {

/**
 * @brief MAV Context storage
 */
class MavContext {
public:
	MavContext() :
		type(MAV_TYPE_GENERIC),
		autopilot(MAV_AUTOPILOT_GENERIC)
	{};
	~MavContext() {};

	/**
	 * Update autopilot type on every HEARTBEAT
	 */
	void update_heartbeat(uint8_t type_, uint8_t autopilot_) {
		boost::recursive_mutex::scoped_lock lock(mutex);

		type = static_cast<enum MAV_TYPE>(type_);
		autopilot = static_cast<enum MAV_AUTOPILOT>(autopilot_);
	};

	inline enum MAV_TYPE get_type() {
		boost::recursive_mutex::scoped_lock lock(mutex);
		return type;
	};

	inline enum MAV_AUTOPILOT get_autopilot() {
		boost::recursive_mutex::scoped_lock lock(mutex);
		return autopilot;
	};

	/**
	 * For APM quirks
	 */
	inline bool is_ardupilotmega() {
		return MAV_AUTOPILOT_ARDUPILOTMEGA == get_autopilot();
	};

private:
	boost::recursive_mutex mutex;
	enum MAV_TYPE type;
	enum MAV_AUTOPILOT autopilot;
};

}; // namespace mavplugin