/* Pan Tilt Zoom camera pelco-p instance
 *
 * Copyright 2021 Luuk Verhagen <developer@verhagenluuk.nl>
 * Copyright 2020-2021 Grant Likely <grant.likely@secretlab.ca>
 *
 * SPDX-License-Identifier: GPLv2
 */

#pragma once
#include "ptz-device.hpp"
#include <util/base.h>
#include <QObject>
#include <QDebug>
#include <QStringListModel>
#include <QtGlobal>
#include "protocol-helpers.hpp"

/*
* General Serial UART class
*/
class PelcoPUART : public PTZUARTWrapper {
	Q_OBJECT

private:
	static std::map<QString, PelcoPUART*> interfaces;
	const int messageLength = 8;

public:
	PelcoPUART(QString& port_name) : PTZUARTWrapper(port_name) { }
	void receive_datagram(const QByteArray& packet);
	void receiveBytes(const QByteArray& packet);

	static PelcoPUART* get_interface(QString port_name);
};

class PTZPelcoP : public PTZDevice {
private:
	PelcoPUART* iface;
	void attach_interface(PelcoPUART* new_iface);
	char checkSum(QByteArray &data);

protected:
	unsigned int address;

	void send(const QByteArray &msg);
	void send(const unsigned char data_1, const unsigned char data_2,
		  const unsigned char data_3, const unsigned char data_4);
	void zoom_speed_set(double speed);
	void receive(const QByteArray &msg);

public:
	PTZPelcoP(OBSData data);
	~PTZPelcoP();

	void set_config(OBSData ptz_data);
	OBSData get_config();
	obs_properties_t *get_obs_properties();

	void pantilt(double pan, double tilt);
	void pantilt_rel(int pan, int tilt);
	void pantilt_stop();
	void pantilt_home();
	void zoom_stop();
	void zoom_tele(double speed);
	void zoom_wide(double speed);
	void memory_reset(int i);
	void memory_set(int i);
	void memory_recall(int i);
};
