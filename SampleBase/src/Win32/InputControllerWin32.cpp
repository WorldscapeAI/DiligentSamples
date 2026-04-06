/*
 *  Copyright 2019-2022 Diligent Graphics LLC
 *  Copyright 2015-2019 Egor Yusov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  In no event and under no legal theory, whether in tort (including negligence),
 *  contract, or otherwise, unless required by applicable law (such as deliberate
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental,
 *  or consequential damages of any character arising as a result of this License or
 *  out of the use or inability to use the software (including but not limited to damages
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and
 *  all other commercial damages or losses), even if such Contributor has been advised
 *  of the possibility of such damages.
 */

#include "InputController.hpp"
#include <algorithm>

#include "WinHPreface.h"
#include <Windows.h>
#include "WinHPostface.h"

namespace Diligent
{

InputKeys MapCameraKeyWnd(UINT nKey)
{
    switch (nKey)
    {
        case VK_CONTROL:
            return InputKeys::ControlDown;

        case VK_SHIFT:
            return InputKeys::ShiftDown;

        case VK_MENU:
            return InputKeys::AltDown;

        case VK_LEFT:
        case 'A':
            return InputKeys::MoveLeft;

        case VK_RIGHT:
        case 'D':
            return InputKeys::MoveRight;

        case VK_UP:
        case 'W':
            return InputKeys::MoveForward;

        case VK_DOWN:
        case 'S':
            return InputKeys::MoveBackward;

        case VK_PRIOR:
        case 'E':
            return InputKeys::MoveUp; // pgup

        case VK_NEXT:
        case 'Q':
            return InputKeys::MoveDown; // pgdn

        case 'Z':
            return InputKeys::RollCounterClockwise;

        case 'C':
            return InputKeys::RollClockwise;

    	case VK_HOME:
            return InputKeys::Reset;

        case VK_ADD:
            return InputKeys::ZoomIn;

        case VK_SUBTRACT:
            return InputKeys::ZoomOut;

        default:
            return InputKeys::Unknown;
    }
}

KeyboardKey WindowsKeyToKeyboardKey(UINT virtualKey)
{
    switch (virtualKey)
    {
    case 0x30:
        return KeyboardKey::Key_0;
        break;
    case 0x31:
        return KeyboardKey::Key_1;
        break;
    case 0x32:
        return KeyboardKey::Key_2;
        break;
    case 0x33:
        return KeyboardKey::Key_3;
        break;
    case 0x34:
        return KeyboardKey::Key_4;
        break;
    case 0x35:
        return KeyboardKey::Key_5;
        break;
    case 0x36:
        return KeyboardKey::Key_6;
        break;
    case 0x37:
        return KeyboardKey::Key_7;
        break;
    case 0x38:
        return KeyboardKey::Key_8;
        break;
    case 0x39:
        return KeyboardKey::Key_9;
        break;

    case 0x41:
        return KeyboardKey::Key_A;
        break;
    case 0x42:
        return KeyboardKey::Key_B;
        break;
    case 0x43:
        return KeyboardKey::Key_C;
        break;
    case 0x44:
        return KeyboardKey::Key_D;
        break;
    case 0x45:
        return KeyboardKey::Key_E;
        break;
    case 0x46:
        return KeyboardKey::Key_F;
        break;
    case 0x47:
        return KeyboardKey::Key_G;
        break;
    case 0x48:
        return KeyboardKey::Key_H;
        break;
    case 0x49:
        return KeyboardKey::Key_I;
        break;
    case 0x4A:
        return KeyboardKey::Key_J;
        break;
    case 0x4B:
        return KeyboardKey::Key_K;
        break;
    case 0x4C:
        return KeyboardKey::Key_L;
        break;
    case 0x4D:
        return KeyboardKey::Key_M;
        break;
    case 0x4E:
        return KeyboardKey::Key_N;
        break;
    case 0x4F:
        return KeyboardKey::Key_O;
        break;
    case 0x50:
        return KeyboardKey::Key_P;
        break;
    case 0x51:
        return KeyboardKey::Key_Q;
        break;
    case 0x52:
        return KeyboardKey::Key_R;
        break;
    case 0x53:
        return KeyboardKey::Key_S;
        break;
    case 0x54:
        return KeyboardKey::Key_T;
        break;
    case 0x55:
        return KeyboardKey::Key_U;
        break;
    case 0x56:
        return KeyboardKey::Key_V;
        break;
    case 0x57:
        return KeyboardKey::Key_W;
        break;
    case 0x58:
        return KeyboardKey::Key_X;
        break;
    case 0x59:
        return KeyboardKey::Key_Y;
        break;
    case 0x5A:
        return KeyboardKey::Key_Z;
        break;

    case VK_LEFT:
        return KeyboardKey::Key_LEFT;
        break;
    case VK_UP:
        return KeyboardKey::Key_UP;
        break;
    case VK_RIGHT:
        return KeyboardKey::Key_RIGHT;
        break;
    case VK_DOWN:
        return KeyboardKey::Key_DOWN;
        break;
    case VK_TAB:
        return KeyboardKey::Key_TAB;
        break;
    case VK_RETURN:
        return KeyboardKey::Key_RETURN;
        break;
    case VK_SHIFT:
        return KeyboardKey::Key_SHIFT;
        break;
    case VK_CONTROL:
        return KeyboardKey::Key_CONTROL;
        break;

    case VK_SPACE:
        return KeyboardKey::Key_SPACE;
        break;
    case VK_PRIOR:
        return KeyboardKey::Key_PAGEUP;
        break;
    case VK_NEXT:
        return KeyboardKey::Key_PAGEDOWN;
        break;
    case VK_END:
        return KeyboardKey::Key_END;
        break;
    case VK_HOME:
        return KeyboardKey::Key_HOME;
        break;
    case VK_CAPITAL:
        return KeyboardKey::Key_CAPITAL;
        break;
    case VK_ESCAPE:
        return KeyboardKey::Key_ESCAPE;
        break;

    case VK_NUMPAD0:
        return KeyboardKey::Key_NUMPAD0;
        break;
    case VK_NUMPAD1:
        return KeyboardKey::Key_NUMPAD1;
        break;
    case VK_NUMPAD2:
        return KeyboardKey::Key_NUMPAD2;
        break;
    case VK_NUMPAD3:
        return KeyboardKey::Key_NUMPAD3;
        break;
    case VK_NUMPAD4:
        return KeyboardKey::Key_NUMPAD4;
        break;
    case VK_NUMPAD5:
        return KeyboardKey::Key_NUMPAD5;
        break;
    case VK_NUMPAD6:
        return KeyboardKey::Key_NUMPAD6;
        break;
    case VK_NUMPAD7:
        return KeyboardKey::Key_NUMPAD7;
        break;
    case VK_NUMPAD8:
        return KeyboardKey::Key_NUMPAD8;
        break;
    case VK_NUMPAD9:
        return KeyboardKey::Key_NUMPAD9;
        break;


    case VK_F1:
        return KeyboardKey::Key_F1;
        break;
    case VK_F2:
        return KeyboardKey::Key_F2;
        break;
    case VK_F3:
        return KeyboardKey::Key_F3;
        break;
    case VK_F4:
        return KeyboardKey::Key_F4;
        break;
    case VK_F5:
        return KeyboardKey::Key_F5;
        break;
    case VK_F6:
        return KeyboardKey::Key_F6;
        break;
    case VK_F7:
        return KeyboardKey::Key_F7;
        break;
    case VK_F8:
        return KeyboardKey::Key_F8;
        break;
    case VK_F9:
        return KeyboardKey::Key_F9;
        break;
    case VK_F10:
        return KeyboardKey::Key_F10;
        break;
    case VK_F11:
        return KeyboardKey::Key_F11;
        break;
    case VK_F12:
        return KeyboardKey::Key_F12;
        break;

    case VK_MULTIPLY:
        return KeyboardKey::Key_MULTIPLY;
        break;
    case VK_ADD:
        return KeyboardKey::Key_ADD;
        break;
    case VK_SEPARATOR:
        return KeyboardKey::Key_SEPARATOR;
        break;
    case VK_SUBTRACT:
        return KeyboardKey::Key_SUBTRACT;
        break;
    case VK_DECIMAL:
        return KeyboardKey::Key_DECIMAL;
        break;
    case VK_DIVIDE:
        return KeyboardKey::Key_DIVIDE;
        break;

    case VK_LSHIFT:
        return KeyboardKey::Key_LSHIFT;
        break;
    case VK_RSHIFT:
        return KeyboardKey::Key_RSHIFT;
        break;
    case VK_LCONTROL:
        return KeyboardKey::Key_LCONTROL;
        break;
    case VK_RCONTROL:
        return KeyboardKey::Key_RCONTROL;
        break;

    default:
        //This is to be expected, we are not handling all keys.
        return KeyboardKey::Unknown;
        break;
    }
}

InputControllerWin32::InputControllerWin32()
{
    UpdateMousePos();
}

const MouseState& InputControllerWin32::GetMouseState()
{
    UpdateMousePos();
    return InputControllerBase::GetMouseState();
}

bool InputControllerWin32::HandleNativeMessage(const void* MsgData)
{
    struct WindowMessageData
    {
        HWND   hWnd;
        UINT   message;
        WPARAM wParam;
        LPARAM lParam;
    };
    const WindowMessageData& WndMsg = *reinterpret_cast<const WindowMessageData*>(MsgData);

    auto hWnd   = WndMsg.hWnd;
    auto uMsg   = WndMsg.message;
    auto wParam = WndMsg.wParam;
    auto lParam = WndMsg.lParam;


    bool MsgHandled = false;
    switch (uMsg)
    {
        case WM_KEYDOWN:
        {
            // Map this key to a InputKeys enum and update the
            // state of m_aKeys[] by adding the INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN|INPUT_KEY_STATE_FLAG_KEY_IS_DOWN mask
            // only if the key is not down
            auto mappedKey = MapCameraKeyWnd((UINT)wParam);
            if (mappedKey != InputKeys::Unknown && mappedKey < InputKeys::TotalKeys)
            {
                auto& Key = m_Keys[static_cast<size_t>(mappedKey)];
                Key &= ~INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN;
                Key |= INPUT_KEY_STATE_FLAG_KEY_IS_DOWN;
            }
            MsgHandled = true;

			//Record input for timed and repeated tracking
            KeyboardKey keyboard_key = WindowsKeyToKeyboardKey((UINT)wParam);
            if (keyboard_key != KeyboardKey::Unknown)
            {
                RecordKeyboardEvent(keyboard_key, KeyboardAction::Key_Down);
            }
            break;
        }

        case WM_KEYUP:
        {
            // Map this key to a InputKeys enum and update the
            // state of m_aKeys[] by removing the INPUT_KEY_STATE_FLAG_KEY_IS_DOWN mask.
            auto mappedKey = MapCameraKeyWnd((UINT)wParam);
            if (mappedKey != InputKeys::Unknown && mappedKey < InputKeys::TotalKeys)
            {
                auto& Key = m_Keys[static_cast<Int32>(mappedKey)];
                Key &= ~INPUT_KEY_STATE_FLAG_KEY_IS_DOWN;
                Key |= INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN;
            }
            MsgHandled = true;

			//Record input for timed and repeated tracking
            KeyboardKey keyboard_key = WindowsKeyToKeyboardKey((UINT)wParam);
            if (keyboard_key != KeyboardKey::Unknown)
            {
                RecordKeyboardEvent(keyboard_key, KeyboardAction::Key_Up);
            }
            break;
        }

        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
        case WM_LBUTTONDBLCLK:
        {
            // Update member var state
            if ((uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK))
            {
                m_MouseState.ButtonFlags |= MouseState::BUTTON_FLAG_LEFT;
            }
            if ((uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK))
            {
                m_MouseState.ButtonFlags |= MouseState::BUTTON_FLAG_MIDDLE;
            }
            if ((uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK))
            {
                m_MouseState.ButtonFlags |= MouseState::BUTTON_FLAG_RIGHT;
            }

            // Capture the mouse, so if the mouse button is
            // released outside the window, we'll get the WM_LBUTTONUP message
            SetCapture(hWnd);
            UpdateMousePos();

            MsgHandled = true;
            break;
        }

        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_LBUTTONUP:
        {
            // Update member var state
            if (uMsg == WM_LBUTTONUP)
            {
                m_MouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_LEFT;
            }
            if (uMsg == WM_MBUTTONUP)
            {
                m_MouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_MIDDLE;
            }
            if (uMsg == WM_RBUTTONUP)
            {
                m_MouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_RIGHT;
            }

            // Release the capture if no mouse buttons down
            if ((m_MouseState.ButtonFlags & (MouseState::BUTTON_FLAG_LEFT | MouseState::BUTTON_FLAG_MIDDLE | MouseState::BUTTON_FLAG_RIGHT)) == 0)
            {
                ReleaseCapture();
            }

            MsgHandled = true;
            break;
        }

        case WM_CAPTURECHANGED:
        {
            if ((HWND)lParam != hWnd)
            {
                if ((m_MouseState.ButtonFlags & MouseState::BUTTON_FLAG_LEFT) ||
                    (m_MouseState.ButtonFlags & MouseState::BUTTON_FLAG_MIDDLE) ||
                    (m_MouseState.ButtonFlags & MouseState::BUTTON_FLAG_RIGHT))
                {
                    m_MouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_LEFT;
                    m_MouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_MIDDLE;
                    m_MouseState.ButtonFlags &= ~MouseState::BUTTON_FLAG_RIGHT;
                    ReleaseCapture();
                }
            }

            MsgHandled = true;
            break;
        }

        case WM_MOUSEWHEEL:
            // Update member var state
            m_MouseState.WheelDelta = (float)((short)HIWORD(wParam)) / (float)WHEEL_DELTA;
            MsgHandled              = true;
            break;
    }

    return MsgHandled;
}

void InputControllerWin32::UpdateMousePos()
{
    POINT MousePosition;
    GetCursorPos(&MousePosition);
    ScreenToClient(GetActiveWindow(), &MousePosition);
    m_MouseState.PosX = static_cast<float>(MousePosition.x);
    m_MouseState.PosY = static_cast<float>(MousePosition.y);

    /*if( m_bResetCursorAfterMove )
    {
        // Set position of camera to center of desktop, 
        // so it always has room to move.  This is very useful
        // if the cursor is hidden.  If this isn't done and cursor is hidden, 
        // then invisible cursor will hit the edge of the screen 
        // and the user can't tell what happened
        POINT ptCenter;

        // Get the center of the current monitor
        MONITORINFO mi;
        mi.cbSize = sizeof( MONITORINFO );
        DXUTGetMonitorInfo( DXUTMonitorFromWindow( DXUTGetHWND(), MONITOR_DEFAULTTONEAREST ), &mi );
        ptCenter.x = ( mi.rcMonitor.left + mi.rcMonitor.right ) / 2;
        ptCenter.y = ( mi.rcMonitor.top + mi.rcMonitor.bottom ) / 2;
        SetCursorPos( ptCenter.x, ptCenter.y );
        m_ptLastMousePosition = ptCenter;
    }*/
}


bool InputControllerWin32::RecordKeyboardEvent(KeyboardKey key, KeyboardAction action)
{
    if (action == KeyboardAction::Key_Up)
    {
        if (m_KeyboardKeys[static_cast<size_t>(key)] != KEYBOARD_STATE_FLAGS_KEY_UP)
        {
            m_KeyboardKeys[static_cast<size_t>(key)] = KEYBOARD_STATE_FLAGS_KEY_RISING;
        }
    }
    else
    {
        if (m_KeyboardKeys[static_cast<size_t>(key)] != KEYBOARD_STATE_FLAGS_KEY_DOWN)
        {
            m_KeyboardKeys[static_cast<size_t>(key)] = KEYBOARD_STATE_FLAGS_KEY_FALLING;
        }
    }
        
    m_KeyboardKeyFramesRepeated[static_cast<size_t>(key)] = 0;
    return true;
}

} // namespace Diligent
