#include "S2D3DJoypad.h"

int S2D3DJoypad::sm_nController = 0;

///////
S2D3DJoypad::S2D3DJoypad()
:m_nControllerNum(-1)
{
	XINPUT_CAPABILITIES caps;
	ZeroMemory(&caps, sizeof(XINPUT_CAPABILITIES));
	XInputGetCapabilities(m_nControllerNum, XINPUT_FLAG_GAMEPAD, &caps);
    if (caps.Type == XINPUT_DEVTYPE_GAMEPAD)
    {
        m_nControllerNum = ++sm_nController;
    }
}


bool S2D3DJoypad::GetInput()
{
	// 置空内存区
	ZeroMemory(&m_sControllerState, sizeof(XINPUT_STATE));

	// 取得状态
	DWORD Result = XInputGetState(m_nControllerNum, &m_sControllerState);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/////////////////

//按键
bool S2D3DJoypad::IsButtonDown(WORD wButtom)
{
	if (m_sControllerState.Gamepad.wButtons & wButtom)
		return true;
	else
		return false;
}
//扳机触发
bool S2D3DJoypad::IsTriggerDown(JoypadDirection dir)
{
	if (dir == JoypadDirection::Left)
	{
		if (m_sControllerState.Gamepad.bLeftTrigger)
			return true;
		else
			return false;
	}
	else if (dir == JoypadDirection::Right)
	{
		if (m_sControllerState.Gamepad.bRightTrigger)
			return true;
		else
			return false;
	}
	return false;
}
//摇杆触发
S2Point S2D3DJoypad::GetThumbPos(JoypadDirection dpaddir)
{
	S2Point pt{0, 0};
	if (dpaddir == JoypadDirection::Left)
	{
		pt.x = m_sControllerState.Gamepad.sThumbLX;
		pt.y = m_sControllerState.Gamepad.sThumbLY;
	}
	else if (dpaddir == JoypadDirection::Right)
	{
		pt.x = m_sControllerState.Gamepad.sThumbRX;
		pt.y = m_sControllerState.Gamepad.sThumbRY;
	}
	return pt;
}

//摇杆触发
bool S2D3DJoypad::IsThumbMove(JoypadDirection dpaddir, JoypadDirection whichdir, int nMin, int nMax)
{
	if (dpaddir == JoypadDirection::Left)
	{
		if (whichdir == JoypadDirection::Left)
		{
			if (m_sControllerState.Gamepad.sThumbLX < nMin)
				return true;
			else
				return false;
		}
		else if (whichdir == JoypadDirection::Right)
		{
			if (m_sControllerState.Gamepad.sThumbLX > nMax)
				return true;
			else
				return false;
		}
		else if (whichdir == JoypadDirection::Up)
		{
			if (m_sControllerState.Gamepad.sThumbLY > nMax)
				return true;
			else
				return false;
		}
		else if (whichdir == JoypadDirection::Down)
		{
			if (m_sControllerState.Gamepad.sThumbLY < nMin)
				return true;
			else
				return false;
		}
	}
	else if (dpaddir == JoypadDirection::Right)
	{
		if (whichdir == JoypadDirection::Left)
		{
			if (m_sControllerState.Gamepad.sThumbRX < nMin)
				return true;
			else
				return false;
		}
		else if (whichdir == JoypadDirection::Right)
		{
			if (m_sControllerState.Gamepad.sThumbRX > nMax)
				return true;
			else
				return false;
		}
		else if (whichdir == JoypadDirection::Up)
		{
			if (m_sControllerState.Gamepad.sThumbRY > nMax)
				return true;
			else
				return false;
		}
		else if (whichdir == JoypadDirection::Down)
		{
			if (m_sControllerState.Gamepad.sThumbRY < nMin)
				return true;
			else
				return false;
		}
	}
	return false;
}

int S2D3DJoypad::GetThumbX(JoypadDirection dpaddir)
{
	if (dpaddir == JoypadDirection::Left)
	{
		return m_sControllerState.Gamepad.sThumbLX;
	}
	else if (dpaddir == JoypadDirection::Right)
	{
		return m_sControllerState.Gamepad.sThumbRX;
	}
	return 0;
}
int S2D3DJoypad::GetThumbY(JoypadDirection dpaddir)
{
	if (dpaddir == JoypadDirection::Left)
	{
		return m_sControllerState.Gamepad.sThumbLY;
	}
	else if (dpaddir == JoypadDirection::Right)
	{
		return m_sControllerState.Gamepad.sThumbRY;
	}
	return 0;
}

void S2D3DJoypad::Vibrate(int leftVal, int rightVal)
{
	// 创建一个 震动 状态
	XINPUT_VIBRATION Vibration;

	// 置空内存区
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// 设置震动属性
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// 开始震动
	XInputSetState(m_nControllerNum, &Vibration);
}