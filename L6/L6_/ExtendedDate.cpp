#include "ExtendedDate.h"
#include <cstdio>
#include <cstring>

// ========== DateWithTime реализации ==========

DateWithTime::DateWithTime() : Date(), hour(0), minute(0), second(0) {}

DateWithTime::DateWithTime(int d, int m, int y, const char* wd, int h, int min, int s) 
    : Date(d, m, y, wd), hour(h), minute(min), second(s) {}

DateWithTime::DateWithTime(const DateWithTime& other) 
    : Date(other), hour(other.hour), minute(other.minute), second(other.second) {}

DateWithTime::~DateWithTime() {}

void DateWithTime::display() const {
    printf("Дата и время: %d.%d.%d %02d:%02d:%02d, День недели: %s\n", 
           day, month+1, year, hour, minute, second, weekDay);
}

const char* DateWithTime::toString() const {
    static char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d-%02d-%04d %02d:%02d:%02d", 
             day, month+1, year, hour, minute, second);
    return buffer;
}

Date* DateWithTime::clone() const {
    return new DateWithTime(*this);
}

bool DateWithTime::isEqual(const Date* other) const {
    const DateWithTime* derived = dynamic_cast<const DateWithTime*>(other);
    if (!derived) return false;
    return Date::isEqual(other) && hour == derived->hour && 
           minute == derived->minute && second == derived->second;
}

void DateWithTime::addSeconds(int seconds) {
    second += seconds;
    while(second >= 60) {
        second -= 60;
        minute++;
        if(minute >= 60) {
            minute = 0;
            hour++;
            if(hour >= 24) {
                hour = 0;
                addDays(1);
            }
        }
    }
}

void DateWithTime::setTime(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

// ========== DateWithEvent реализации ==========

DateWithEvent::DateWithEvent() : Date() {
    eventName = new char[10];
    strcpy(eventName, "Meeting");
    location = new char[10];
    strcpy(location, "Office");
}

DateWithEvent::DateWithEvent(int d, int m, int y, const char* wd, const char* event, const char* loc) 
    : Date(d, m, y, wd) {
    eventName = new char[strlen(event) + 1];
    strcpy(eventName, event);
    location = new char[strlen(loc) + 1];
    strcpy(location, loc);
}

DateWithEvent::DateWithEvent(const DateWithEvent& other) 
    : Date(other) {
    eventName = new char[strlen(other.eventName) + 1];
    strcpy(eventName, other.eventName);
    location = new char[strlen(other.location) + 1];
    strcpy(location, other.location);
}

DateWithEvent::~DateWithEvent() {
    delete[] eventName;
    delete[] location;
}

DateWithEvent& DateWithEvent::operator=(const DateWithEvent& other) {
    if(this != &other) {
        Date::operator=(other);
        
        delete[] eventName;
        delete[] location;
        
        eventName = new char[strlen(other.eventName) + 1];
        strcpy(eventName, other.eventName);
        location = new char[strlen(other.location) + 1];
        strcpy(location, other.location);
    }
    return *this;
}

void DateWithEvent::display() const {
    printf("Дата события: %d.%d.%d, День недели: %s\n", day, month+1, year, weekDay);
    printf("Событие: %s, Место: %s\n", eventName, location);
}

const char* DateWithEvent::toString() const {
    static char buffer[100];
    snprintf(buffer, sizeof(buffer), "%02d-%02d-%04d | Событие: %s | Место: %s", 
             day, month+1, year, eventName, location);
    return buffer;
}

Date* DateWithEvent::clone() const {
    return new DateWithEvent(*this);
}

bool DateWithEvent::isEqual(const Date* other) const {
    const DateWithEvent* derived = dynamic_cast<const DateWithEvent*>(other);
    if (!derived) return false;
    return Date::isEqual(other) && strcmp(eventName, derived->eventName) == 0 && 
           strcmp(location, derived->location) == 0;
}

bool DateWithEvent::writeToTextFile(const char* filename) const {
    FILE* file = fopen(filename, "w");
    if(file == nullptr) {
        return false;
    }
    fprintf(file, "%d %d %d %s %s %s\n", day, month+1, year, weekDay, eventName, location);
    fclose(file);
    return true;
}

void DateWithEvent::setEvent(const char* event, const char* loc) {
    delete[] eventName;
    delete[] location;
    
    eventName = new char[strlen(event) + 1];
    strcpy(eventName, event);
    location = new char[strlen(loc) + 1];
    strcpy(location, loc);
}
