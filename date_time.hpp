#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include <Windows.h>
#include <utility>
#include <string>
#include "core_macros.hpp"
#include "basic_error.hpp"

namespace dt0
{
	class time
	{
	public:
		___constexpr20___ time() noexcept : _hours(0), _minutes(0), _seconds(0), _milliseconds(0) {}

		time(unsigned short int hours, unsigned short int minutes, unsigned short int seconds, unsigned short int milliseconds)
		{
			if (milliseconds > 999)
				throw basic_error("Invalid value for milliseconds!");

			if (seconds > 59)
				throw basic_error("Invalid value for seconds!");

			if (minutes > 59)
				throw basic_error("Invalid value for minutes!");

			_hours = std::move(hours);
			_minutes = std::move(minutes);
			_seconds = std::move(seconds);
			_milliseconds = std::move(milliseconds);
		}

		time(unsigned int milliseconds)
		{
			_milliseconds = (milliseconds < 1000) ? milliseconds : (milliseconds % 1000);

			_seconds = (milliseconds > 999) ? (milliseconds / 1000) : 0;

			_minutes = (_seconds > 59) ? (_seconds / 60) : 0;

			if (_seconds > 59)
			{
				_seconds %= 100;

				if (_seconds > 59) _seconds %= 10;
			}

			_hours = (_minutes > 59) ? (_minutes / 60) : 0;

			if (_minutes > 59)
			{
				_minutes %= 100;

				if (_minutes > 59) _minutes %= 10;
			}
		}

		time(unsigned short int seconds)
		{
			_milliseconds = 0;

			_seconds = (seconds < 60) ? seconds : (seconds % 100);

			if (_seconds > 59) _seconds %= 10;

			_minutes = (seconds > 59) ? (seconds / 60) : 0;

			_hours = (_minutes > 59) ? (_minutes / 60) : 0;

			if (_minutes > 59)
			{
				_minutes %= 100;

				if (_minutes > 59) _minutes %= 10;
			}
		}

		time(const time& other)
		{
			_hours = other.hours();
			_minutes = other.minutes();
			_seconds = other.seconds();
			_milliseconds = other.milliseconds();
		}

		time(time&& other) noexcept
		{
			_hours = std::move(other.hours());
			_minutes = std::move(other.minutes());
			_seconds = std::move(other.seconds());
			_milliseconds = std::move(other.milliseconds());
		}

		~time() noexcept = default;

		___nodiscard___ unsigned short int hours() const
		{
			return _hours;
		}

		___nodiscard___ unsigned short int minutes() const
		{
			return _minutes;
		}

		___nodiscard___ unsigned short int seconds() const
		{
			return _seconds;
		}

		___nodiscard___ unsigned short int milliseconds() const
		{
			return _milliseconds;
		}

		___nodiscard___ static time now()
		{
			SYSTEMTIME _systime;

			GetLocalTime(&_systime);

			return time(_systime.wHour, _systime.wMinute, _systime.wSecond, _systime.wMilliseconds);
		}

		___nodiscard___ std::string as_string() const
		{
			std::string hour = (_hours < 10) ? std::string("0") + std::to_string(_hours) : std::to_string(_hours);
			std::string minute = (_minutes < 10) ? std::string("0") + std::to_string(_minutes) : std::to_string(_minutes);
			std::string second = (_seconds < 10) ? std::string("0") + std::to_string(_seconds) : std::to_string(_seconds);

			return std::string(hour + std::string(":") + minute + std::string(":") + second + std::string(".") + std::to_string(_milliseconds));
		}

		const time& operator= (const time& other)
		{
			_hours = other.hours();
			_minutes = other.minutes();
			_seconds = other.seconds();
			_milliseconds = other.milliseconds();

			return *this;
		}

		const time& operator= (time&& other) noexcept
		{
			_hours = std::move(other.hours());
			_minutes = std::move(other.minutes());
			_seconds = std::move(other.seconds());
			_milliseconds = std::move(other.milliseconds());

			return *this;
		}

	private:
		unsigned short int _hours;
		unsigned short int _minutes;
		unsigned short int _seconds;
		unsigned short int _milliseconds;
	};

	class day
	{
	public:
		___constexpr20___ day() noexcept : _name(""), _week_index(0), _month_index(0) {}

		day(std::string name, unsigned short int week_index, unsigned short int month_index)
		{
			if ((week_index > 7) || (week_index < 1))
				throw basic_error("Invalid week index!");

			if ((month_index > 31) || (month_index < 1))
				throw basic_error("Invalid week index!");

			_name = std::move(name);
			_week_index = std::move(week_index);
			_month_index = std::move(month_index);
		}

		day(unsigned short int week_index, unsigned short int month_index)
		{
			if ((week_index > 7) || (week_index < 1))
				throw basic_error("Invalid week index!");

			if ((month_index > 31) || (month_index < 1))
				throw basic_error("Invalid week index!");

			_week_index = std::move(week_index);

			_month_index = std::move(month_index);

			switch (_week_index)
			{
			case 1:
				_name = "Monday";
				break;

			case 2:
				_name = "Tuesday";
				break;

			case 3:
				_name = "Wednesday";
				break;

			case 4:
				_name = "Thursday";
				break;

			case 5:
				_name = "Friday";
				break;

			case 6:
				_name = "Saturday";
				break;

			case 7:
				_name = "Sunday";
				break;

			default:
				throw basic_error("Invalid week index!");
				break;
			}
		}

		day(std::string name)
		{
			_month_index = 0;

			if ((name == "Monday") || (name == "monday") || (name == "Mon") || (name == "mon") || (name == "M"))
			{
				_week_index = 1;
			}

			else if ((name == "Tuesday") || (name == "Tue") || (name == "Tues") ||
				(name == "tue") || (name == "tues") || (name == "T") || (name == "Tu"))
			{
				_week_index = 2;
			}

			else if ((name == "Wednesday") || (name == "wednesday") || (name == "Wed") || (name == "wed") || (name == "W"))
			{
				_week_index = 3;
			}

			else if ((name == "Thursday") || (name == "thursday") || (name == "Thu") || (name == "Thur") ||
				(name == "Thurs") || (name == "thu") || (name == "thur") ||
				(name == "thurs") || (name == "Th") || (name == "R"))
			{
				_week_index = 4;
			}

			else if ((name == "Friday") || (name == "friday") || (name == "Fri") || (name == "fri") || (name == "F"))
			{
				_week_index = 5;
			}

			else if ((name == "Saturday") || (name == "saturday") || (name == "Sat") || (name == "sat") || (name == "Sa") || (name == "S"))
			{
				_week_index = 6;
			}

			else if ((name == "Sunday") || (name == "sunday") || (name == "Sun") || (name == "sun") || (name == "Su") || (name == "S") || (name == "U"))
			{
				_week_index = 7;
			}

			else throw basic_error("Invalid name!");

			_name = std::move(name);
		}

		day(const day& other)
		{
			_name = other.name();
			_week_index = other.week_index();
			_month_index = other.month_index();
		}

		day(day&& other) noexcept
		{
			_name = std::move(other.name());
			_week_index = std::move(other.week_index());
			_month_index = std::move(other.month_index());
		}

		~day() noexcept = default;

		___nodiscard___ std::string name() const
		{
			return _name;
		}

		___nodiscard___ unsigned short int week_index() const
		{
			return _week_index;
		}

		___nodiscard___ unsigned short int month_index() const
		{
			return _month_index;
		}

		const day& operator= (const day& other)
		{
			_name = other.name();
			_week_index = other.week_index();
			_month_index = other.month_index();

			return *this;
		}

		const day& operator= (day&& other) noexcept
		{
			_name = std::move(other.name());
			_week_index = std::move(other.week_index());
			_month_index = std::move(other.month_index());

			return *this;
		}

		const day& operator= (std::pair<unsigned short int, unsigned short int> day_indexes)
		{
			if ((day_indexes.first > 7) || (day_indexes.first < 1))
				throw basic_error("Invalid week index!");

			if ((day_indexes.second > 31) || (day_indexes.second < 1))
				throw basic_error("Invalid week index!");

			_week_index = std::move(day_indexes.first);

			_month_index = std::move(day_indexes.second);

			switch (_week_index)
			{
			case 1:
				_name = "Monday";
				break;

			case 2:
				_name = "Tuesday";
				break;

			case 3:
				_name = "Wednesday";
				break;

			case 4:
				_name = "Thursday";
				break;

			case 5:
				_name = "Friday";
				break;

			case 6:
				_name = "Saturday";
				break;

			case 7:
				_name = "Sunday";
				break;

			default:
				throw basic_error("Invalid week index!");
				break;
			}

			return *this;
		}

		const day& operator= (std::string name)
		{
			_month_index = 0;

			if ((name == "Monday") || (name == "monday") || (name == "Mon") || (name == "mon") || (name == "M"))
			{
				_week_index = 1;
			}

			else if ((name == "Tuesday") || (name == "Tue") || (name == "Tues") ||
				(name == "tue") || (name == "tues") || (name == "T") || (name == "Tu"))
			{
				_week_index = 2;
			}

			else if ((name == "Wednesday") || (name == "wednesday") || (name == "Wed") || (name == "wed") || (name == "W"))
			{
				_week_index = 3;
			}

			else if ((name == "Thursday") || (name == "thursday") || (name == "Thu") || (name == "Thur") ||
				(name == "Thurs") || (name == "thu") || (name == "thur") ||
				(name == "thurs") || (name == "Th") || (name == "R"))
			{
				_week_index = 4;
			}

			else if ((name == "Friday") || (name == "friday") || (name == "Fri") || (name == "fri") || (name == "F"))
			{
				_week_index = 5;
			}

			else if ((name == "Saturday") || (name == "saturday") || (name == "Sat") || (name == "sat") || (name == "Sa") || (name == "S"))
			{
				_week_index = 6;
			}

			else if ((name == "Sunday") || (name == "sunday") || (name == "Sun") || (name == "sun") || (name == "Su") || (name == "S") || (name == "U"))
			{
				_week_index = 7;
			}

			else throw basic_error("Invalid name!");

			_name = std::move(name);

			return *this;
		}

		___nodiscard___ static day now()
		{
			SYSTEMTIME _sysinfo;

			GetLocalTime(&_sysinfo);

			return day(_sysinfo.wDayOfWeek, _sysinfo.wDay);
		}

	private:
		std::string _name;
		unsigned short int _week_index;
		unsigned short int _month_index;
	};

	class month
	{
	public:
		___constexpr20___ month() noexcept : _index(0), _name(""), _days(0) 
		{}

		month(unsigned short int index, std::string name, unsigned short int days)
		{
			if ((index > 12) || (index < 1))
				throw basic_error("Invalid month index!");

			if (((index < 8) && (index % 2 == 1)) || ((index > 7) && (index % 2 == 0)))
			{
				if (days != 31) throw basic_error("Invalid ammount of days for month!");
			}

			else if (((index < 8) && (index % 2 == 0) && (index != 2)) || ((index > 7) && (index % 2 == 1)))
			{
				if (days != 30) throw basic_error("Invalid ammount of days for month!");
			}

			else
			{
				if ((days != 28) || (days != 29)) throw basic_error("Invalid ammount of days for month!");
			}

			_index = std::move(index);
			_name = std::move(name);
			_days = std::move(days);
		}

		month(std::string name, unsigned short int index, unsigned short int days)
		{
			if ((index > 12) || (index < 1))
				throw basic_error("Invalid month index!");

			if (((index < 8) && (index % 2 == 1)) || ((index > 7) && (index % 2 == 0)))
			{
				if (days != 31) throw basic_error("Invalid ammount of days for month!");
			}

			else if (((index < 8) && (index % 2 == 0) && (index != 2)) || ((index > 7) && (index % 2 == 1)))
			{
				if (days != 30) throw basic_error("Invalid ammount of days for month!");
			}
			
			else
			{
				if((days != 28) || (days != 29)) throw basic_error("Invalid ammount of days for month!");
			}

			_name = std::move(name);
			_index = std::move(index);
			_days = std::move(days);
		}

		month(unsigned short int index)
		{
			if ((index > 12) || (index < 1))
				throw basic_error("Invalid month index!");

			_index = std::move(index);

			switch (_index)
			{
			case 1:
				_name = "January";
				_days = 31;
				break;

			case 2:
				_name = "Februrary";
				_days = 28;
				break;

			case 3:
				_name = "March";
				_days = 31;
				break;

			case 4:
				_name = "April";
				_days = 30;
				break;

			case 5:
				_name = "May";
				_days = 31;
				break;

			case 6:
				_name = "June";
				_days = 30;
				break;

			case 7:
				_name = "July";
				_days = 31;
				break;

			case 8:
				_name = "August";
				_days = 31;
				break;

			case 9:
				_name = "September";
				_days = 30;
				break;

			case 10:
				_name = "October";
				_days = 31;
				break;

			case 11:
				_name = "November";
				_days = 30;
				break;

			case 12:
				_name = "December";
				_days = 31;
				break;
			}
		}

		month(std::string name)
		{
			if ((name == "January") || (name == "january") || (name == "Jan") || (name == "jan"))
			{
				_index = 1;
				_days = 31;
			}

			else if ((name == "February") || (name == "february") || (name == "Feb") || (name == "feb"))
			{
				_index = 2;
				_days = 28;
			}

			else if ((name == "March") || (name == "march") || (name == "Mar") || (name == "mar"))
			{
				_index = 3;
				_days = 31;
			}

			else if ((name == "April") || (name == "april") || (name == "Apr") || (name == "apr"))
			{
				_index = 4; _days = 30;
			}

			else if ((name == "May") || (name == "may"))
			{
				_index = 5; _days = 31;
			}

			else if ((name == "June") || (name == "june") || (name == "Jun") || (name == "jun"))
			{
				_index = 6;
				_days = 30;
			}

			else if ((name == "July") || (name == "july") || (name == "Jul") || (name == "jul"))
			{
				_index = 7;
				_days = 31;
			}

			else if ((name == "August") || (name == "august") || (name == "Aug") || (name == "aug"))
			{
				_index = 8;
				_days = 31;
			}

			else if ((name == "September") || (name == "september") || (name == "Sep") || (name == "sep"))
			{
				_index = 9;
				_days = 30;
			}

			else if ((name == "October") || (name == "october") || (name == "Oct") || (name == "oct"))
			{
				_index = 10;
				_days = 31;
			}

			else if ((name == "November") || (name == "november") || (name == "Nov") || (name == "nov"))
			{
				_index = 11;
				_days = 30;
			}

			else if ((name == "December") || (name == "december") || (name == "Dec") || (name == "dec"))
			{
				_index = 12;
				_days = 31;
			}

			else throw basic_error("Invalid month name!");

			_name = std::move(name);
		}

		month(const month& other)
		{
			_index = other.index();
			_name = other.name();
			_days = other.days();
		}

		month(month&& other) noexcept
		{
			_index = std::move(other.index());
			_name = std::move(other.name());
			_days = std::move(other.days());
		}

		~month() noexcept = default;

		___nodiscard___ unsigned short int index() const
		{
			return _index;
		}

		___nodiscard___ std::string name() const
		{
			return _name;
		}

		___nodiscard___ unsigned short int days() const
		{
			return _days;
		}

		const month& operator= (const month& other)
		{
			_index = other.index();
			_name = other.name();
			_days = other.days();

			return *this;
		}

		const month& operator= (month&& other) noexcept
		{
			_index = std::move(other.index());
			_name = std::move(other.name());
			_days = std::move(other.days());

			return *this;
		}

		const month& operator= (unsigned short int index)
		{
			if ((index > 12) || (index < 1))
				throw basic_error("Invalid month index!");

			_index = std::move(index);

			switch (_index)
			{
			case 1:
				_name = "January";
				_days = 31;
				break;

			case 2:
				_name = "Februrary";
				_days = 28;
				break;

			case 3:
				_name = "March";
				_days = 31;
				break;

			case 4:
				_name = "April";
				_days = 30;
				break;

			case 5:
				_name = "May";
				_days = 31;
				break;

			case 6:
				_name = "June";
				_days = 30;
				break;

			case 7:
				_name = "July";
				_days = 31;
				break;

			case 8:
				_name = "August";
				_days = 31;
				break;

			case 9:
				_name = "September";
				_days = 30;
				break;

			case 10:
				_name = "October";
				_days = 31;
				break;

			case 11:
				_name = "November";
				_days = 30;
				break;

			case 12:
				_name = "December";
				_days = 31;
				break;
			}

			return *this;
		}

		const month& operator= (std::string name)
		{
			if ((name == "January") || (name == "january") || (name == "Jan") || (name == "jan"))
			{
				_index = 1;
				_days = 31;
			}

			else if ((name == "February") || (name == "february") || (name == "Feb") || (name == "feb"))
			{
				_index = 2;
				_days = 28;
			}

			else if ((name == "March") || (name == "march") || (name == "Mar") || (name == "mar"))
			{
				_index = 3;
				_days = 31;
			}

			else if ((name == "April") || (name == "april") || (name == "Apr") || (name == "apr"))
			{
				_index = 4; _days = 30;
			}

			else if ((name == "May") || (name == "may"))
			{
				_index = 5; _days = 31;
			}

			else if ((name == "June") || (name == "june") || (name == "Jun") || (name == "jun"))
			{
				_index = 6;
				_days = 30;
			}

			else if ((name == "July") || (name == "july") || (name == "Jul") || (name == "jul"))
			{
				_index = 7;
				_days = 31;
			}

			else if ((name == "August") || (name == "august") || (name == "Aug") || (name == "aug"))
			{
				_index = 8;
				_days = 31;
			}

			else if ((name == "September") || (name == "september") || (name == "Sep") || (name == "sep"))
			{
				_index = 9;
				_days = 30;
			}

			else if ((name == "October") || (name == "october") || (name == "Oct") || (name == "oct"))
			{
				_index = 10;
				_days = 31;
			}

			else if ((name == "November") || (name == "november") || (name == "Nov") || (name == "nov"))
			{
				_index = 11;
				_days = 30;
			}

			else if ((name == "December") || (name == "december") || (name == "Dec") || (name == "dec"))
			{
				_index = 12;
				_days = 31;
			}

			else throw basic_error("Invalid month name!");

			_name = std::move(name);

			return *this;
		}

		___nodiscard___ static month now()
		{
			SYSTEMTIME _sysinfo;

			GetLocalTime(&_sysinfo);

			return month(_sysinfo.wMonth);
		}

		___nodiscard___ bool operator== (const month& other) const
		{
			if ((_index == other.index()) && (_name == other.name()) && (_days == other.days()))
				return true;

			return false;
		}

		___nodiscard___ bool operator== (const std::string& other) const
		{
			if (_name == other)
				return true;

			return false;
		}

		___nodiscard___ bool operator== (const unsigned short int& other) const
		{
			if (_index == other)
				return true;

			return false;
		}

	private:
		unsigned short int _index;
		std::string _name;
		unsigned short int _days;
	};

	class year
	{
	public:
		___constexpr20___ year() noexcept : _value(0), _leap_year(false), _bce(false) {}

		year(unsigned __int64 value, bool leap_year, bool bce)
		{
			if (((value % 4) != 0) && (leap_year == true))
				throw basic_error("Year is not a leap year!");

			_value = std::move(value);
			_leap_year = std::move(leap_year);
			_bce = std::move(bce);
		}

		year(unsigned __int64 value, bool bce)
		{
			_value = std::move(value);
			_leap_year = ((_value % 4) == 0) ? true : false;
			_bce = std::move(bce);
		}

		year(unsigned __int64 value)
		{
			_value = std::move(value);
			_leap_year = ((_value % 4) == 0) ? true : false;
			_bce = false;
		}

		year(const year& other)
		{
			_value = other.value();
			_leap_year = other.leap_year();
			_bce = other.bce();
		}

		year(year&& other) noexcept
		{
			_value = std::move(other.value());
			_leap_year = std::move(other.leap_year());
			_bce = std::move(other.bce());
		}

		~year() noexcept = default;

		___nodiscard___ unsigned __int64 value() const
		{
			return _value;
		}

		___nodiscard___ bool leap_year() const
		{
			return _leap_year;
		}

		___nodiscard___ bool bce() const
		{
			return _bce;
		}

		const year& operator= (const year& other)
		{
			_value = other.value();
			_leap_year = other.leap_year();
			_bce = other.bce();

			return *this;
		}

		const year& operator= (year&& other) noexcept
		{
			_value = std::move(other.value());
			_leap_year = std::move(other.leap_year());
			_bce = std::move(other.bce());

			return *this;
		}

		const year& operator= (unsigned __int64 other)
		{
			_value = std::move(other);
			_leap_year = ((_value % 4) == 0) ? true : false;
			_bce = false;

			return *this;
		}

		___nodiscard___ static year now()
		{
			SYSTEMTIME _sysinfo;

			GetLocalTime(&_sysinfo);

			return year(_sysinfo.wYear);
		}

	private:
		unsigned __int64 _value;
		bool _leap_year;
		bool _bce;
	};

	class date
	{
	public:
		___constexpr20___ date() noexcept = default;

		date(year Y, month M, day d) noexcept
		{
			_year = std::move(Y);
			_month = (M == 2 && _year.leap_year()) ? std::move(month(2, M.name(), 29)) : std::move(M);
			_day = std::move(d);
		}

		date(day d, month M, year Y) noexcept
		{
			_day = std::move(d);
			_month = (M == 2 && Y.leap_year()) ? std::move(month(2, M.name(), 29)) : std::move(M);
			_year = std::move(Y);
		}

		date(month M, day d, year Y) noexcept
		{
			_month = (M == 2 && Y.leap_year()) ? std::move(month(2, M.name(), 29)) : std::move(M);
			_day = std::move(d);
			_year = std::move(Y);
		}

		date(const date& other)
		{
			_year = other.get_year();
			_month = other.get_month();
			_day = other.get_day();
		}

		date(date&& other) noexcept
		{
			_year = std::move(other.get_year());
			_month = std::move(other.get_month());
			_day = std::move(other.get_day());
		}

		~date() noexcept = default;

		___nodiscard___ year get_year() const
		{
			return _year;
		}

		___nodiscard___ month get_month() const
		{
			return _month;
		}

		___nodiscard___ day get_day() const
		{
			return _day;
		}

		const date& operator= (const date& other)
		{
			_year = other.get_year();
			_month = other.get_month();
			_day = other.get_day();

			return *this;
		}

		const date& operator= (date&& other) noexcept
		{
			_year = std::move(other.get_year());
			_month = std::move(other.get_month());
			_day = std::move(other.get_day());

			return *this;
		}

		___nodiscard___ static date now()
		{
			return date(year::now(), month::now(), day::now());
		}

	private:
		year _year;
		month _month;
		day _day;
	};

	class date_time
	{
	public:
		___constexpr20___ date_time() noexcept = default;

		date_time(year Y, month M, day D, unsigned short hrs, unsigned short min, unsigned short sec, unsigned short mil) : 
			_date(std::move(date(Y, M, D))), _time(std::move(time(hrs, min, sec, mil))) 
		{}

		date_time(date D, time T) : _date(std::move(D)), _time(std::move(T)) {}

		date_time(time T, date D)
		{
			_time = std::move(T);
			_date = std::move(D);
		}

		date_time(const date_time& other) noexcept
		{
			_date = other.get_date();
			_time = other.get_time();
		}

		date_time(date_time&& other) noexcept
		{
			_date = std::move(other.get_date());
			_time = std::move(other.get_time());
		}

		~date_time() noexcept = default;

		___nodiscard___ date get_date() const
		{
			return _date;
		}

		___nodiscard___ time get_time() const
		{
			return _time;
		}

		const date_time& operator= (const date_time& other) noexcept
		{
			_date = other.get_date();
			_time = other.get_time();

			return *this;
		}

		const date_time& operator= (date_time&& other) noexcept
		{
			_date = std::move(other.get_date());
			_time = std::move(other.get_time());

			return *this;
		}

		___nodiscard___ static date_time now()
		{
			return date_time(date::now(), time::now());
		}

	private:
		date _date;
		time _time;
	};
}

#endif /* DATE_TIME_HPP */
