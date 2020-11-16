/* Pan Tilt Zoom camera controls
 *
 * Copyright 2020 Grant Likely <grant.likely@secretlab.ca>
 *
 * SPDX-License-Identifier: GPLv2
 */
#pragma once

#include <QTimer>
#include <obs.hpp>
#include <QDockWidget>
#include <QtGamepad/QGamepad>

#if LIBVISCA_FOUND
#include <visca/libvisca.h>
#endif

#include "../UI/qt-wrappers.hpp"
#include <../UI/obs-frontend-api/obs-frontend-api.h>

#include "ptz-device.hpp"
#include "ui_ptz-controls.h"

class PTZControls : public QDockWidget {
	Q_OBJECT

private:
	static void OBSFrontendEventWrapper(enum obs_frontend_event event, void *ptr);
	void OBSFrontendEvent(enum obs_frontend_event event);
	void ControlContextMenu();

	std::unique_ptr<Ui::PTZControls> ui;

	std::vector<PTZDevice *> cameras;
	unsigned int current_cam;

	QGamepad *gamepad;
	double joystick_pan, joystick_tilt;

	void SaveConfig();
	void LoadConfig();
	void OpenInterface();

	void full_stop();
	void setPanTilt(double pan, double tilt);

	void setCurrent(unsigned int index);

	PTZDevice * currCamera();

private slots:
	void on_panTiltButton_up_pressed();
	void on_panTiltButton_up_released();
	void on_panTiltButton_upleft_pressed();
	void on_panTiltButton_upleft_released();
	void on_panTiltButton_upright_pressed();
	void on_panTiltButton_upright_released();
	void on_panTiltButton_left_pressed();
	void on_panTiltButton_left_released();
	void on_panTiltButton_right_pressed();
	void on_panTiltButton_right_released();
	void on_panTiltButton_down_pressed();
	void on_panTiltButton_down_released();
	void on_panTiltButton_downleft_pressed();
	void on_panTiltButton_downleft_released();
	void on_panTiltButton_downright_pressed();
	void on_panTiltButton_downright_released();
	void on_panTiltButton_home_released();
	void on_panTiltGamepad();

	void on_zoomButton_tele_pressed();
	void on_zoomButton_tele_released();
	void on_zoomButton_wide_pressed();
	void on_zoomButton_wide_released();

	void on_nextCameraButton_released();
	void on_prevCameraButton_released();

	void on_targetButton_preview_clicked(bool checked);
	void on_targetButton_program_clicked(bool checked);

	void on_cameraList_clicked();

public:
	PTZControls(QWidget *parent = nullptr);
	~PTZControls();
};
