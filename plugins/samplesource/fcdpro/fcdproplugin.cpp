///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2015 Edouard Griffiths, F4EXB                                   //
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

#include <QtPlugin>
#include <QAction>
#include "plugin/pluginapi.h"
#include "util/simpleserializer.h"
#include "fcdproplugin.h"
#include "fcdprogui.h"
#include "fcdtraits.h"

const PluginDescriptor FCDProPlugin::m_pluginDescriptor = {
	QString(fcd_traits<Pro>::pluginDisplayedName),
	QString(fcd_traits<Pro>::pluginVersion),
	QString("(c) Edouard Griffiths, F4EXB"),
	QString("https://github.com/f4exb/sdrangel"),
	true,
	QString("https://github.com/f4exb/sdrangel")
};

FCDProPlugin::FCDProPlugin(QObject* parent) :
	QObject(parent)
{
}

const PluginDescriptor& FCDProPlugin::getPluginDescriptor() const
{
	return m_pluginDescriptor;
}

void FCDProPlugin::initPlugin(PluginAPI* pluginAPI)
{
	m_pluginAPI = pluginAPI;

	m_pluginAPI->registerSampleSource(fcd_traits<Pro>::interfaceIID, this);
}

PluginInterface::SampleSourceDevices FCDProPlugin::enumSampleSources()
{
	SampleSourceDevices result;

	int i = 1;
	struct hid_device_info *device_info = hid_enumerate(fcd_traits<Pro>::vendorId, fcd_traits<Pro>::productId);

	while (device_info != 0)
	{
		QString serialNumber = QString::fromWCharArray(device_info->serial_number);
		QString displayedName(QString("%1 #%2 %3").arg(fcd_traits<Pro>::displayedName).arg(i).arg(serialNumber));
		SimpleSerializer s(1);
		s.writeS32(1, 0);
		result.append(SampleSourceDevice(displayedName, fcd_traits<Pro>::interfaceIID, s.final()));

		device_info = device_info->next;
		i++;
	}

	return result;
}

PluginGUI* FCDProPlugin::createSampleSourcePluginGUI(const QString& sourceName, const QByteArray& address)
{
	if(sourceName == fcd_traits<Pro>::interfaceIID)
	{
		FCDProGui* gui = new FCDProGui(m_pluginAPI);
		m_pluginAPI->setInputGUI(gui);
		return gui;
	}
	else
	{
		return NULL;
	}
}