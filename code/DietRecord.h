#ifndef DIET_RECORD_H
#define DIET_RECORD_H

#include "Date.h"
#include "Food.h"

class DietRecord {
public:
    DietRecord();
    DietRecord(const Date& date, const Food& food, double weight);
    double calculateCalories() const;

    Date getDate() const;
    Food getFood() const;
    double getWeight() const;
    double getCalories() const;

private:
    Date date;
    Food food;
    double weight;
    double calories;
};

#endif
