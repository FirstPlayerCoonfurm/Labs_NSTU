#include "Date.h"

int main() {
    Date defaultDate;
    defaultDate.display();

    Date customDate(28, 12, 2024, "Friday");
    customDate.display();

    Date copiedDate(customDate);
    copiedDate.display();

    return 0;
}
