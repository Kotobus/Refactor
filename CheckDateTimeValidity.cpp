#include <string_view>
enum class TimeValidityError {
    OK,
    YEAR_TOO_SMALL,
    YEAR_TOO_BIG,
    MONTH_TOO_SMALL,
    MONTH_TOO_BIG,
    DAY_TOO_SMALL,
    DAY_TOO_BIG,
    HOUR_TOO_SMALL,
    HOUR_TOO_BIG,
    MINUTE_TOO_BIG,
    MINUTE_TOO_SMALL,
    SECOND_TOO_BIG,
    SECOND_TOO_SMALL,
};

bool IsError(TimeValidityError error) {
    return error != TimeValidityError::OK;
}
const std::string_view ErrorMessage(TimeValidityError error) {
   std::string_view ErrorMessages[] = {
        "ok",
        "year is too small",
        "year is too big",
        "month is too small",
        "month is too big",
        "day is too small",
        "day is too big",
        "hour is too small",
        "hour is too big",
        "minute is too small",
        "minute is too big",
        "second is too small",
        "second is too big"
    };
    return ErrorMessages[static_cast<int>(error)];
}

TimeValidityError CheckDateTimeValidity(const DateTime& dt) {
    if (dt.year < 1) {
        return TimeValidityError::YEAR_TOO_SMALL;
    }
    if (dt.year > 9999) {
        return TimeValidityError::YEAR_TOO_BIG;

    }

    if (dt.month < 1) {
        return TimeValidityError::MONTH_TOO_SMALL;
    }
    if (dt.month > 12) {
        return TimeValidityError::MONTH_TOO_BIG;
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dt.day < 1) {
        return TimeValidityError::DAY_TOO_SMALL;
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        return TimeValidityError::DAY_TOO_BIG;
    }

    if (dt.hour < 0) {
        return TimeValidityError::HOUR_TOO_SMALL;
    }
    if (dt.hour > 23) {
        return TimeValidityError::HOUR_TOO_BIG;
    }

    if (dt.minute < 0) {
        return TimeValidityError::MINUTE_TOO_SMALL;
    }
    if (dt.minute > 59) {
        return TimeValidityError::MINUTE_TOO_BIG;
    }

    if (dt.second < 0) {
        return TimeValidityError::SECOND_TOO_SMALL;
    }
    if (dt.second > 59) {
        return TimeValidityError::SECOND_TOO_BIG;
    }
}
TimeValidityError CheckValidity(const DateTime& dt) {
    auto error = CheckDateTimeValidity(dt);
    if (IsError(error)) {
        throw ErrorMessage(error);
    }
    else return TimeValidityError::OK;
}