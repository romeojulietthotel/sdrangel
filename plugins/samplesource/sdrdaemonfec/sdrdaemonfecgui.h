///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_SDRDAEMONFECGUI_H
#define INCLUDE_SDRDAEMONFECGUI_H

#include <QTimer>
#include <sys/time.h>
#include "plugin/plugingui.h"

#include "sdrdaemonfecinput.h"

class DeviceSourceAPI;
class FileRecord;

namespace Ui {
	class SDRdaemonFECGui;
}

class SDRdaemonFECGui : public QWidget, public PluginGUI {
	Q_OBJECT

public:
	explicit SDRdaemonFECGui(DeviceSourceAPI *deviceAPI, QWidget* parent = NULL);
	virtual ~SDRdaemonFECGui();
	void destroy();

	void setName(const QString& name);
	QString getName() const;

	void resetToDefaults();
	QByteArray serialize() const;
	bool deserialize(const QByteArray& data);
	virtual qint64 getCenterFrequency() const;
	virtual void setCenterFrequency(qint64 centerFrequency);
	virtual bool handleMessage(const Message& message);

private:
	Ui::SDRdaemonFECGui* ui;

	DeviceSourceAPI* m_deviceAPI;
	QTimer m_updateTimer;
	QTimer m_statusTimer;
	DeviceSampleSource* m_sampleSource;
    bool m_acquisition;
    FileRecord *m_fileSink; //!< File sink to record device I/Q output
    int m_deviceSampleRate;
    quint64 m_deviceCenterFrequency; //!< Center frequency in device
    int m_lastEngineState;

	int m_sampleRate;
	quint64 m_centerFrequency;
	struct timeval m_startingTimeStamp;
	int m_framesDecodingStatus;
	bool m_allBlocksReceived;
	float m_bufferLengthInSecs;
    int32_t m_bufferGauge;
    int m_minNbBlocks;
    int m_minNbOriginalBlocks;
    int m_maxNbRecovery;
    float m_avgNbBlocks;
    float m_avgNbOriginalBlocks;
    float m_avgNbRecovery;
    int m_nbOriginalBlocks;
    int m_nbFECBlocks;

	int m_samplesCount;
	std::size_t m_tickCount;

	QString m_address;
	QString m_remoteAddress;
	quint16 m_dataPort;
	quint16 m_controlPort;
	bool m_addressEdited;
	bool m_dataPortEdited;
	bool m_initSendConfiguration;
	int m_sender;

	bool m_dcBlock;
	bool m_iqCorrection;

    QPalette m_paletteGreenText;
    QPalette m_paletteWhiteText;

	void displaySettings();

	void displayConfigurationParameters(uint32_t freq,
			uint32_t log2Decim,
			uint32_t fcPos,
			uint32_t sampleRate,
			QString& specParms);

	void displayTime();
	void configureUDPLink();
	void configureAutoCorrections();
	void updateWithAcquisition();
	void updateWithStreamData();
	void updateWithStreamTime();
	void sendConfiguration();
    void updateSampleRateAndFrequency();

private slots:
    void handleDSPMessages();
	void handleSourceMessages();
	void on_applyButton_clicked(bool checked);
	void on_dcOffset_toggled(bool checked);
	void on_iqImbalance_toggled(bool checked);
	void on_address_textEdited(const QString& arg1);
	void on_dataPort_textEdited(const QString& arg1);
	void on_controlPort_textEdited(const QString& arg1);
	void on_sendButton_clicked(bool checked);
	void on_freq_textEdited(const QString& arg1);
	void on_sampleRate_textEdited(const QString& arg1);
	void on_specificParms_textEdited(const QString& arg1);
	void on_decim_currentIndexChanged(int index);
	void on_fcPos_currentIndexChanged(int index);
	void on_startStop_toggled(bool checked);
    void on_record_toggled(bool checked);
	void updateStatus();
	void tick();
};

#endif // INCLUDE_SDRDAEMONGUI_H
