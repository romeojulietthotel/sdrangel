///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2015 F4EXB                                                      //
// written by Edouard Griffiths                                                  //
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

#include "udpsrcplugin.h"

#include <QtPlugin>
#include <QAction>
#include "plugin/pluginapi.h"

#include "udpsrcgui.h"

const PluginDescriptor UDPSrcPlugin::m_pluginDescriptor = {
	QString("UDP Channel Source"),
	QString("---"),
	QString("(c) Edouard Griffiths, F4EXB"),
	QString("https://github.com/f4exb/sdrangel"),
	true,
	QString("https://github.com/f4exb/sdrangel")
};

UDPSrcPlugin::UDPSrcPlugin(QObject* parent) :
	QObject(parent)
{
}

const PluginDescriptor& UDPSrcPlugin::getPluginDescriptor() const
{
	return m_pluginDescriptor;
}

void UDPSrcPlugin::initPlugin(PluginAPI* pluginAPI)
{
	m_pluginAPI = pluginAPI;

	// register TCP Channel Source
	QAction* action = new QAction(tr("&UDP Source"), this);
	connect(action, SIGNAL(triggered()), this, SLOT(createInstanceUDPSrc()));
	m_pluginAPI->registerChannel("sdrangel.channel.udpsrc", this, action);
}

PluginGUI* UDPSrcPlugin::createChannel(const QString& channelName)
{
	if(channelName == "sdrangel.channel.udpsrc") {
		UDPSrcGUI* gui = UDPSrcGUI::create(m_pluginAPI);
		m_pluginAPI->registerChannelInstance("sdrangel.channel.udpsrc", gui);
		m_pluginAPI->addChannelRollup(gui);
		return gui;
	} else {
		return 0;
	}
}

void UDPSrcPlugin::createInstanceUDPSrc()
{
	UDPSrcGUI* gui = UDPSrcGUI::create(m_pluginAPI);
	m_pluginAPI->registerChannelInstance("sdrangel.channel.udpsrc", gui);
	m_pluginAPI->addChannelRollup(gui);
}