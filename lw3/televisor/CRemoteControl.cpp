#include "pch.h"
#include "CRemoteControl.h"
#include "CError.h"
#include "CTVSet.h"

CRemoteControl::CRemoteControl(CTVSet& tv, istream& input, ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "TurnOn", [this](istream& strm) { return TurnOn(strm); } },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) },
		  { "Info", bind(&CRemoteControl::Info, this, _1) },
		  { "SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1) } })
{
}

CRemoteControl::~CRemoteControl()
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto instruction = m_actionMap.find(action);
	if (instruction != m_actionMap.end())
	{
		return instruction->second(strm);
	}

	return false;
}

bool CRemoteControl::TurnOn(istream& args)
{
	m_tv.TurnOn();
	m_output << "TV is turned on\n";
	return true;
}

bool CRemoteControl::TurnOff(istream& args)
{
	m_tv.TurnOff();
	m_output << "TV is turned off\n";
	return true;
}

bool CRemoteControl::Info(istream& args)
{
	int currentChannel = m_tv.GetCurrentChannel();
	string info = (m_tv.IsTurnedOn()) ? ("TV is turned on\nChannel is: " + to_string(currentChannel) + "\n") : "TV is turned off";

	m_output << info;

	return true;
}

bool CRemoteControl::SelectChannel(istream& args)
{
	string inputString;
	getline(args, inputString);
	int channelNumber = atoi(inputString.c_str());

	m_tv.SelectChannel(channelNumber);

	if (!m_tv.IsTurnedOn())
	{
		m_output << "ERROR: Turned off TV can't switches channel\n";
	}
	else
	{
		m_output << "Channel changed to " + to_string(m_tv.GetCurrentChannel()) + "\n";
	}

	return true;
}
