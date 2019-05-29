
//  Created by Dan Goldberg on 21/03/11.

#define D_MINUTE 60
#define D_HOUR 3600
#define D_DAY 86400
#define D_WEEK 604800
#define D_YEAR 31556926

#import <Foundation/Foundation.h>

/**
 NSDate helper methods.
 */
@interface NSDate (APAdditions)

/**
 Gets the day month and year values of the date and returns a new date with only these values, and the hour, minutes and seconds set to 0.
 @return The date without time values.
 */
- (NSDate *)timeless;

/**
 Returns a new date incremented by a given number of days.
 @param days The days by which to increment.
 @return The new date.
 */
- (NSDate *)dateByAddingDays:(NSInteger)days;

/**
 Cancels out the timezone value of the NSDate instance and converts it to UTC.
 @return The date in UTC time.
 */
- (NSDate *)dateToUTC;

/**
 @return The date now with zero seconds
 */
+ (NSDate *)currentZeroDate;

/**
 @return The day of the week. weekday 1 = Sunday for Gregorian calendar
 */
+ (NSInteger)dayOfWeekOfDate:(NSDate *)date;

/**
 Combine the date and the time
 @return The date combined
 */
+ (NSDate *)combineDateAndTime:(NSDate *)date time:(NSDate *)time;

/**
 Creating NSDate from string 
 @return the date which created
 */
+ (NSDate *)dateWithStringFormat:(NSString *)format dateAsString:(NSString *)dateAsString;

/**
 Add minutes to date
 @return The date with minutes
 */
+ (NSDate *)addMinutesToDate:(NSDate *)date minutes:(NSInteger)minutes;


/**
 Add seconds to date
 @return The date with seconds
 */
+ (NSDate *)addSecondsToDate:(NSDate *)date seconds:(NSInteger)seconds;

/**
 Add hourse to date
 @return The date with hours
 */
+ (NSDate *)addHoursToDate:(NSDate *)date hours:(NSInteger)hours;

/**
 Add days to date
 @return The date with days
 */
+ (NSDate *)addDaysToDate:(NSDate *)date days:(NSInteger)days;

/**
 Bolean indicated if date is between 2 given dates
 @return yes if its between
 */
- (BOOL)isDateBetween:(NSDate *)firstDate secondDate:(NSDate *)secondDate;

/**
 PHP as unique string
 @return string of the current date formatted from php
 */
- (NSString *)getDateAsPhpString;

/**
 @return Yes if date is same day as other day
 */

- (BOOL)isSameDay:(NSDate*)other;

/**
 Foramtting NSDate to string with given format
 @return date as string
 */
- (NSString *)getDateAsStringWithFormat:(NSString *)format;

/**
 Formatting the date as dd-MM-yyyy
 @return The string formatted
 */
- (NSString *)getDateAsString;

/**
 Formatting the date as HH
 @return The string formatted
 */
- (NSString *)getHourAsString;

/**
 Formatting the date as mm:HH:ss
 @return The string formatted
 */
- (NSString *)getTimeAsStringWithSeconds;

/**
 Formatting the date as HH:mm
 @return The string formatted
 */
- (NSString *)getTimeAsString;

/**
 Cancels out the timezone value of the NSDate instance and converts it to UTC.
 @return The date in UTC time.
 */
- (NSString *)stringWithFormat:(NSString *)format;

/**
 @return The day of the week. weekday 1 = Sunday for Gregorian calendar
 */
- (NSInteger)dayOfWeek;

/**
 @return the date when the day was started
 */
- (NSDate *)dateAtStartOfDay;

/**
 @return the date of the first day of the week
 */
- (NSDate *)getFirstDayOfWeek;

/**
 @return yes if a date is a week from now
 */
- (BOOL)is7DaysFromNow;

/**
 @return yes if a date is yesterday
 */
- (BOOL)isYesterday;

/**
 @return yes if a date is tomorrow
 */
- (BOOL)isTomorrow;

/**
 @return the munites from a specific time
 */
- (long)totalMinutesFromTime;

/**
 @return seconds from a specific time
 */
- (long)totalSecondsFromTime;

/**
 @return yes if a date is after snother date
 */
- (BOOL)isAfter:(NSDate*)other;

/**
 @return yes if date is before another date
 */
- (BOOL)isBefore:(NSDate*)other;

/**
 Cancels out the timezone value of the NSDate instance and converts it to UTC.
 @return The date in UTC time.
 */
- (NSTimeInterval)secondsBeforeDate:(NSDate *)aDate;

/**
 @return seconds after a specific date
 */
- (NSTimeInterval)secondsAfterDate:(NSDate *)aDate;

/**
 @return the minutes before a given date
 */

- (NSInteger)minutesBeforeDate:(NSDate *)aDate;

/**
 @return the minutes after a given date
 */
- (NSInteger)minutesAfterDate:(NSDate *)aDate;

/**
 @return the hours after a given date
 */
- (NSInteger)hoursBeforeDate:(NSDate *)aDate;

/**
 @return the days after a given date
 */
- (NSInteger)hoursAfterDate:(NSDate *)aDate;

/**
 @return the days before a given date
 */
- (NSInteger)daysBeforeDate:(NSDate *)aDate;

/**
 @return the days after a given date
 */
- (NSInteger)daysAfterDate:(NSDate *)aDate;

/**
 Usage example: [NSDate timeAgoStringFromTimeInterval:[myDate timeIntervalSince1970]];
 @return time ago string from time interval since 1970
 */
+ (NSString *)timeAgoStringFromTimeInterval:(NSTimeInterval)seconds;

/**
 Converts timeInterval to time code hh:mm:ss.
 @param timeInterval - double value that display the seconds.
 @return The date normalized to time code in format hh:mm:ss.
 */
+ (NSString*)timeCodeWithInterval:(NSTimeInterval)timeInterval;

@end
