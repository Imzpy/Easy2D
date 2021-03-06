// Copyright (c) 2016-2018 Easy2D - Nomango
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "time.h"
#include "logs.h"
#include <regex>
#include <unordered_map>

namespace easy2d
{
	namespace time
	{
		//-------------------------------------------------------
		// TimePoint
		//-------------------------------------------------------

		TimePoint::TimePoint()
		{
		}

		TimePoint::TimePoint(long dur)
			: dur_(dur)
		{
		}

		const TimePoint TimePoint::operator+(const Duration & dur) const
		{
			return TimePoint{ dur_ + dur.Milliseconds() };
		}

		const TimePoint TimePoint::operator-(const Duration & dur) const
		{
			return TimePoint{ dur_ - dur.Milliseconds() };
		}

		TimePoint & TimePoint::operator+=(const Duration & other)
		{
			dur_ += other.Milliseconds();
			return (*this);
		}

		TimePoint & TimePoint::operator-=(const Duration &other)
		{
			dur_ -= other.Milliseconds();
			return (*this);
		}

		const Duration TimePoint::operator-(const TimePoint & other) const
		{
			return Duration(dur_ - other.dur_);
		}


		//-------------------------------------------------------
		// Duration
		//-------------------------------------------------------

		const Duration Millisecond	= 1L;
		const Duration Second		= 1000 * Millisecond;
		const Duration Minute		= 60 * Second;
		const Duration Hour			= 60 * Minute;

		namespace
		{
			const auto duration_regex = std::wregex(LR"([-+]?([0-9]*(\.[0-9]*)?[a-z]+)+)");

			typedef std::unordered_map<std::wstring, Duration> UnitMap;
			const auto unit_map = UnitMap
			{
				{L"ms", Millisecond},
				{L"s", Second},
				{L"m", Minute},
				{L"h", Hour}
			};
		}

		Duration::Duration()
			: milliseconds_(0)
		{
		}

		Duration::Duration(long milliseconds)
			: milliseconds_(milliseconds)
		{
		}

		float Duration::Seconds() const
		{
			long long sec = milliseconds_ / Second.milliseconds_;
			long long ms = milliseconds_ % Second.milliseconds_;
			return static_cast<float>(sec) + static_cast<float>(ms) / 1000.f;
		}

		float Duration::Minutes() const
		{
			long long min = milliseconds_ / Minute.milliseconds_;
			long long ms = milliseconds_ % Minute.milliseconds_;
			return static_cast<float>(min) + static_cast<float>(ms) / (60 * 1000.f);
		}

		float Duration::Hours() const
		{
			long long hour = milliseconds_ / Hour.milliseconds_;
			long long ms = milliseconds_ % Hour.milliseconds_;
			return static_cast<float>(hour) + static_cast<float>(ms) / (60 * 60 * 1000.f);
		}

		std::wstring easy2d::time::Duration::ToString() const
		{
			if (IsZero())
			{
				return std::wstring(L"0s");
			}

			std::wstring result;
			long long hour = milliseconds_ / Hour.milliseconds_;
			long long min = milliseconds_ / Minute.milliseconds_ - hour * 60;
			long long sec = milliseconds_ / Second.milliseconds_ - (hour * 60 * 60 + min * 60);
			long long ms = milliseconds_ % Second.milliseconds_;

			if (milliseconds_ < 0)
				result.append(L"-");

			if (hour)
			{
				result.append(std::to_wstring(hour)).append(L"h");
				result.append(std::to_wstring(min)).append(L"m");
			}
			else if(min)
			{
				result.append(std::to_wstring(min)).append(L"m");
			}

			if (ms != 0)
			{
				auto float_to_str = [](float val) -> std::wstring
				{
					wchar_t buf[10] = {};
					::swprintf_s(buf, L"%.2f", val);
					return std::wstring(buf);
				};

				result.append(float_to_str(static_cast<float>(sec) + static_cast<float>(ms) / 1000.f))
					.append(L"s");
			}
			else if (sec != 0)
			{
				result.append(std::to_wstring(sec)).append(L"s");
			}
			return result;
		}

		bool Duration::operator==(const Duration & other) const
		{
			return milliseconds_ == other.milliseconds_;
		}

		bool Duration::operator!=(const Duration & other) const
		{
			return milliseconds_ != other.milliseconds_;
		}

		bool Duration::operator>(const Duration & other) const
		{
			return milliseconds_ > other.milliseconds_;
		}

		bool Duration::operator>=(const Duration & other) const
		{
			return milliseconds_ >= other.milliseconds_;
		}

		bool Duration::operator<(const Duration & other) const
		{
			return milliseconds_ < other.milliseconds_;
		}

		bool Duration::operator<=(const Duration & other) const
		{
			return milliseconds_ <= other.milliseconds_;
		}

		float easy2d::time::Duration::operator/(const Duration & other) const
		{
			return static_cast<float>(milliseconds_) / other.milliseconds_;
		}

		const Duration Duration::operator+(const Duration & other) const
		{
			return Duration(milliseconds_ + other.milliseconds_);
		}

		const Duration Duration::operator-(const Duration & other) const
		{
			return Duration(milliseconds_ - other.milliseconds_);
		}

		const Duration Duration::operator-() const
		{
			return Duration(-milliseconds_);
		}

		const Duration Duration::operator*(int val) const
		{
			return Duration(milliseconds_ * val);
		}

		const Duration easy2d::time::Duration::operator*(unsigned long long val) const
		{
			return Duration(static_cast<long>(milliseconds_ * val));
		}

		const Duration Duration::operator*(float val) const
		{
			return Duration(static_cast<long>(milliseconds_ * val));
		}

		const Duration Duration::operator*(double val) const
		{
			return Duration(static_cast<long>(milliseconds_ * val));
		}

		const Duration Duration::operator*(long double val) const
		{
			return Duration(static_cast<long>(milliseconds_ * val));
		}

		const Duration Duration::operator/(int val) const
		{
			return Duration(milliseconds_ / val);
		}

		const Duration Duration::operator/(float val) const
		{
			return Duration(static_cast<long>(milliseconds_ / val));
		}

		const Duration Duration::operator/(double val) const
		{
			return Duration(static_cast<long>(milliseconds_ / val));
		}

		Duration & Duration::operator+=(const Duration &other)
		{
			milliseconds_ += other.milliseconds_;
			return (*this);
		}

		Duration & Duration::operator-=(const Duration &other)
		{
			milliseconds_ -= other.milliseconds_;
			return (*this);
		}

		Duration & Duration::operator*=(int val)
		{
			milliseconds_ *= val;
			return (*this);
		}

		Duration & Duration::operator/=(int val)
		{
			milliseconds_ = static_cast<long>(milliseconds_ / val);
			return (*this);
		}

		Duration & Duration::operator*=(float val)
		{
			milliseconds_ = static_cast<long>(milliseconds_ * val);
			return (*this);
		}

		Duration & Duration::operator/=(float val)
		{
			milliseconds_ = static_cast<long>(milliseconds_ / val);
			return (*this);
		}

		Duration & Duration::operator*=(double val)
		{
			milliseconds_ = static_cast<long>(milliseconds_ * val);
			return (*this);
		}

		Duration & Duration::operator/=(double val)
		{
			milliseconds_ = static_cast<long>(milliseconds_ / val);
			return (*this);
		}

		const Duration easy2d::time::operator*(int val, const Duration & dur)
		{
			return dur * val;
		}

		const Duration easy2d::time::operator/(int val, const Duration & dur)
		{
			return dur / val;
		}

		const Duration easy2d::time::operator*(float val, const Duration & dur)
		{
			return dur * val;
		}

		const Duration easy2d::time::operator/(float val, const Duration & dur)
		{
			return dur / val;
		}

		const Duration easy2d::time::operator*(double val, const Duration & dur)
		{
			return dur * val;
		}

		const Duration easy2d::time::operator/(double val, const Duration & dur)
		{
			return dur / val;
		}

		const Duration easy2d::time::operator*(long double val, const Duration & dur)
		{
			return dur * val;
		}

		std::wostream & easy2d::time::operator<<(std::wostream & out, const Duration & dur)
		{
			return out << dur.ToString();
		}

		std::wistream & easy2d::time::operator>>(std::wistream & in, Duration & dur)
		{
			std::wstring str;
			in >> str;
			dur = time::ParseDuration(str);
			return in;
		}


		//-------------------------------------------------------
		// Functions
		//-------------------------------------------------------

		TimePoint easy2d::time::Now() E2D_NOEXCEPT
		{
			static LARGE_INTEGER freq = {};
			if (freq.QuadPart == 0LL)
			{
				// the function will always succceed on systems that run Windows XP or later
				QueryPerformanceFrequency(&freq);
			}

			LARGE_INTEGER count;
			QueryPerformanceCounter(&count);

			const long long whole = (count.QuadPart / freq.QuadPart) * 1000LL;
			const long long part = (count.QuadPart % freq.QuadPart) * 1000LL / freq.QuadPart;
			return TimePoint{ static_cast<long>(whole + part) };
		}

		Duration easy2d::time::ParseDuration(const std::wstring & str)
		{
			size_t len = str.length();
			size_t pos = 0;
			bool negative = false;
			Duration d;

			if (!std::regex_match(str, duration_regex))
			{
				E2D_ERROR_LOG(L"time::ParseDuration failed, invalid duration");
				return Duration();
			}

			if (str.empty() || str == L"0") { return d; }

			// 符号位
			if (str[0] == L'-' || str[0] == L'+')
			{
				negative = (str[0] == L'-');
				pos++;
			}

			while (pos < len)
			{
				// 数值
				size_t i = pos;
				for (; i < len; ++i)
				{
					wchar_t ch = str[i];
					if (!(ch == L'.' || L'0' <= ch && ch <= L'9'))
					{
						break;
					}
				}

				std::wstring num_str = str.substr(pos, i - pos);
				pos = i;

				if (num_str.empty() || num_str == L".")
				{
					E2D_ERROR_LOG(L"time::ParseDuration failed, invalid duration");
					return Duration();
				}

				// 单位
				for (; i < len; ++i)
				{
					wchar_t ch = str[i];
					if (ch == L'.' || L'0' <= ch && ch <= L'9')
					{
						break;
					}
				}

				std::wstring unit_str = str.substr(pos, i - pos);
				pos = i;

				if (unit_map.find(unit_str) == unit_map.end())
				{
					E2D_ERROR_LOG(L"time::ParseDuration failed, invalid duration");
					return Duration();
				}

				double num = std::stod(num_str);
				Duration unit = unit_map.at(unit_str);
				d += unit * num;
			}

			if (negative)
			{
				d = -d;
			}
			return d;
		}
	}
}