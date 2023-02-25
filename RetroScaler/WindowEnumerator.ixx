/*
* This file is part of RetroScaler.
*
* RetroScaler is free software : you can redistribute itand /or modify it under the terms of
* the GNU General Public License as published by the Free Software Foundation, either version 2
* of the License, or (at your option) any later version.
*
* RetroScaler is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* RetroScaler.If not, see < https://www.gnu.org/licenses/>.
*/

module;

#include <Windows.h>

#include <string>
#include <vector>

export module WindowEnumerator;

struct WindowInfo
{
	HWND hwnd{ nullptr };
	std::wstring title;
};

export class WindowEnumerator
{
public:
	void RefreshList()
	{
		/*
		* Enumerate windows, will put to container only visible windows,
		* without any parent (top) and with non empty title to get rid of
		* many "helper" invisible windows of many services.
		*/

		windowList.clear();
		EnumWindows(EnumWindowProc, reinterpret_cast<LPARAM>(this));
	}

	size_t GetWindowCount() const { return windowList.size(); }
	
	const std::wstring& GetSelectedWindowTitle(size_t windowIndex) const
	{
		return windowList[windowIndex].title;
	}

	const HWND GetSelectedWindowHandle(size_t windowIndex) const
	{
		return windowList[windowIndex].hwnd;
	}

private:
	using WindowList = std::vector<WindowInfo>;

	WindowList windowList;

	static BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lparam)
	{
		WindowEnumerator* _this{ reinterpret_cast<WindowEnumerator*>(lparam) };

		if (_this == nullptr)
		{
			return FALSE;
		}

		std::vector<wchar_t> buffer;
		int titleLen = GetWindowTextLength(hwnd) + 1;
		buffer.resize(titleLen);
		GetWindowText(hwnd, buffer.data(), titleLen);
		
		if (titleLen > 1 && GetParent(hwnd) == nullptr && IsWindowVisible(hwnd))
		{
			_this->windowList.emplace_back(hwnd, buffer.data());
		}

		return TRUE;
	}
};
