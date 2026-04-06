/*
 *  Copyright 2019-2024 Diligent Graphics LLC
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

#pragma once

#include "BasicTypes.h"
#include "FlagEnum.h"

namespace Diligent
{

struct MouseState
{
    enum BUTTON_FLAGS : Uint8
    {
        BUTTON_FLAG_NONE   = 0x00,
        BUTTON_FLAG_LEFT   = 0x01,
        BUTTON_FLAG_MIDDLE = 0x02,
        BUTTON_FLAG_RIGHT  = 0x04,
        BUTTON_FLAG_WHEEL  = 0x08
    };

    Float32      PosX        = -1;
    Float32      PosY        = -1;
    BUTTON_FLAGS ButtonFlags = BUTTON_FLAG_NONE;
    Float32      WheelDelta  = 0;

    constexpr bool IsValid()
    {
        return PosX >= 0 && PosY >= 0;
    }
    explicit constexpr operator bool()
    {
        return IsValid();
    }
};
DEFINE_FLAG_ENUM_OPERATORS(MouseState::BUTTON_FLAGS)


enum class InputKeys
{
    Unknown = 0,
    MoveLeft,
    MoveRight,
    MoveForward,
    MoveBackward,
    MoveUp,
    MoveDown,
    RollClockwise,
	RollCounterClockwise,
    Reset,
    ControlDown,
    ShiftDown,
    AltDown,
    ZoomIn,
    ZoomOut,
    TotalKeys
};

enum INPUT_KEY_STATE_FLAGS : Uint8
{
    INPUT_KEY_STATE_FLAG_KEY_NONE     = 0x00,
    INPUT_KEY_STATE_FLAG_KEY_IS_DOWN  = 0x01,
    INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN = 0x80
};
DEFINE_FLAG_ENUM_OPERATORS(INPUT_KEY_STATE_FLAGS)

enum class KeyboardAction { Key_Up, Key_Down};

enum class KeyboardKey
{
    Unknown = -1,
    Key_0 = 0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,

    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,
    
    Key_LEFT,
    Key_UP,    
    Key_RIGHT,
    Key_DOWN,
    Key_TAB,   
    Key_RETURN,
    Key_SHIFT,
    Key_CONTROL,

    Key_CAPITAL,
    Key_ESCAPE,

    Key_SPACE,
    Key_PAGEUP,	
    Key_PAGEDOWN,
    Key_HOME,
    Key_END,   

    Key_NUMPAD0,
    Key_NUMPAD1,
    Key_NUMPAD2,
    Key_NUMPAD3,
    Key_NUMPAD4,
    Key_NUMPAD5,
    Key_NUMPAD6,
    Key_NUMPAD7,
    Key_NUMPAD8,
    Key_NUMPAD9,

    Key_MULTIPLY,
    Key_ADD,
    Key_SEPARATOR,
    Key_SUBTRACT,
    Key_DECIMAL,
    Key_DIVIDE,
    Key_F1,
    Key_F2,
    Key_F3,
    Key_F4,
    Key_F5,
    Key_F6,
    Key_F7,
    Key_F8,
    Key_F9,
    Key_F10,	
    Key_F11,
    Key_F12,

    Key_LSHIFT,
    Key_RSHIFT,
    Key_LCONTROL,
    Key_RCONTROL,
    TotalKeys
};

enum KEYBOARD_STATE_FLAGS : Uint8
{
    KEYBOARD_STATE_FLAGS_KEY_INVALID    = 0x00,
    KEYBOARD_STATE_FLAGS_KEY_DOWN       = 0x01,
    KEYBOARD_STATE_FLAGS_KEY_FALLING    = 0x03,
    KEYBOARD_STATE_FLAGS_KEY_UP         = 0x10,
    KEYBOARD_STATE_FLAGS_KEY_RISING     = 0x30
};

class InputControllerBase
{
public:

    InputControllerBase()
    {
       for (int keyboardIdx = 0; keyboardIdx != static_cast<size_t>(KeyboardKey::TotalKeys); ++keyboardIdx)
        {
            m_KeyboardKeys[static_cast<size_t>(keyboardIdx)] = KEYBOARD_STATE_FLAGS::KEYBOARD_STATE_FLAGS_KEY_UP;
            m_LastFrameKeyboardKeys[static_cast<size_t>(keyboardIdx)] = KEYBOARD_STATE_FLAGS::KEYBOARD_STATE_FLAGS_KEY_UP;
            m_KeyboardKeyFramesRepeated[static_cast<size_t>(keyboardIdx)] = 0;
            m_KeyboardKeyTimestampSwitch[static_cast<size_t>(keyboardIdx)] = 0.0;
        }
    }


    const MouseState& GetMouseState() const
    {
        return m_MouseState;
    }

    INPUT_KEY_STATE_FLAGS GetKeyState(InputKeys Key) const
    {
        return m_Keys[static_cast<size_t>(Key)];
    }

    bool IsKeyDown(InputKeys Key) const
    {
        return (GetKeyState(Key) & INPUT_KEY_STATE_FLAG_KEY_IS_DOWN) != 0;
    }

    KEYBOARD_STATE_FLAGS GetKeyboardState(KeyboardKey Key) const
    {
        return m_KeyboardKeys[static_cast<size_t>(Key)];
    }

    Uint8 GetKeyboardRepeat(KeyboardKey Key) const
    {
        return m_KeyboardKeyFramesRepeated[static_cast<size_t>(Key)];
    }

    double GetKeyboardSwitchTimestamp(KeyboardKey Key) const
    {
        return m_KeyboardKeyTimestampSwitch[static_cast<size_t>(Key)];
    }


    void ClearState()
    {
        m_MouseState.WheelDelta = 0;

        for (Uint32 i = 0; i < static_cast<Uint32>(InputKeys::TotalKeys); ++i)
        {
            auto& KeyState = m_Keys[i];
            if (KeyState & INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN)
            {
                KeyState &= ~INPUT_KEY_STATE_FLAG_KEY_WAS_DOWN;
            }
        }
    }
    
    void Update(const double current_time)
    {
        for(int keyboardIdx = 0; keyboardIdx != static_cast<size_t>(KeyboardKey::TotalKeys); ++keyboardIdx)
        {
            if(m_KeyboardKeys[keyboardIdx] == m_LastFrameKeyboardKeys[keyboardIdx])
            {
                if(m_KeyboardKeyFramesRepeated[keyboardIdx] != USHRT_MAX)
                    ++m_KeyboardKeyFramesRepeated[keyboardIdx];
            }
            else
            {
                m_KeyboardKeyTimestampSwitch[keyboardIdx] = current_time;
            }
        }

        for (int keyboardIdx = 0; keyboardIdx != static_cast<size_t>(KeyboardKey::TotalKeys); ++keyboardIdx)
        {
            m_LastFrameKeyboardKeys[keyboardIdx] = m_KeyboardKeys[keyboardIdx];
            
            if (m_KeyboardKeys[keyboardIdx] == KEYBOARD_STATE_FLAGS_KEY_FALLING)
            {
                m_KeyboardKeys[keyboardIdx] = KEYBOARD_STATE_FLAGS_KEY_DOWN;
            }
            if (m_KeyboardKeys[keyboardIdx] == KEYBOARD_STATE_FLAGS_KEY_RISING)
            {
                m_KeyboardKeys[keyboardIdx] = KEYBOARD_STATE_FLAGS_KEY_UP;
            }
        }
    }

protected:
    MouseState            m_MouseState;
    INPUT_KEY_STATE_FLAGS m_Keys[static_cast<size_t>(InputKeys::TotalKeys)] = {};

    KEYBOARD_STATE_FLAGS  m_KeyboardKeys[static_cast<size_t>(KeyboardKey::TotalKeys)] = {};
    KEYBOARD_STATE_FLAGS  m_LastFrameKeyboardKeys[static_cast<size_t>(KeyboardKey::TotalKeys)] = {};
    double                m_KeyboardKeyTimestampSwitch[static_cast<size_t>(KeyboardKey::TotalKeys)] = {};
    Uint8                 m_KeyboardKeyFramesRepeated[static_cast<size_t>(KeyboardKey::TotalKeys)] = {};
};

} // namespace Diligent

// clang-format off
#if PLATFORM_WIN32
    #include "Win32/InputControllerWin32.hpp"
    namespace Diligent
    {
        using InputController = InputControllerWin32;
    }
#elif PLATFORM_UNIVERSAL_WINDOWS
    #include "UWP/InputControllerUWP.hpp"
    namespace Diligent
    {
        using InputController = InputControllerUWP;
    }
#elif PLATFORM_MACOS
    #include "MacOS/InputControllerMacOS.hpp"
    namespace Diligent
    {
        using InputController = InputControllerMacOS;
    }
#elif PLATFORM_IOS
    #include "iOS/InputControllerIOS.hpp"
    namespace Diligent
    {
        using InputController = InputControllerIOS;
    }
#elif PLATFORM_LINUX
    #include "Linux/InputControllerLinux.hpp"
    namespace Diligent
    {
        using InputController = InputControllerLinux;
    }
#elif PLATFORM_ANDROID
    #include "Android/InputControllerAndroid.hpp"
    namespace Diligent
    {
        using InputController = InputControllerAndroid;
    }
#elif PLATFORM_WEB
    #include "Emscripten/InputControllerEmscripten.hpp"
    namespace Diligent
    {
        using InputController = InputControllerEmscripten;
    }
#else
    namespace Diligent
    {
        class DummyInputController
        {
        public:
            const MouseState& GetMouseState()const{return m_MouseState;}

            INPUT_KEY_STATE_FLAGS GetKeyState(InputKeys Key)const{return INPUT_KEY_STATE_FLAG_KEY_NONE;}

            bool IsKeyDown(InputKeys Key)const{return false;}

            void ClearState(){}

        private:
            MouseState m_MouseState;
        };
        using InputController = DummyInputController;
    }
#endif
// clang-format on
