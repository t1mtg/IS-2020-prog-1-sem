#include <stdio.h>

int main() {
    //task2
    int time;
    int sub_fee;
    int minute_price;
    int total;
    scanf("%d%d%d", &time, &sub_fee, &minute_price);
    int sub_minute_price = sub_fee / 499;
    if (sub_minute_price > minute_price) {
        printf("Minute in subscription is more expensive than minute over the subscription\n");
    } else {
        if (time <= 499) {
            total = sub_fee;
        } else {
            total = sub_fee + (time - 499) * minute_price;
        }
        printf("%d", total);
    }
    printf("\n");

    //task 5
    float interest_rate;
    float initial_amount;
    int amount_of_months;
    float cur_amount;
    scanf("%d%f%f", &amount_of_months, &initial_amount, &interest_rate);
    printf("%f\n", initial_amount);
    cur_amount = initial_amount;
    interest_rate = 1 + interest_rate / 100;
    for (int i = 1; i < amount_of_months; i++) {
        cur_amount *= interest_rate;
        printf("month %d amount = %f\n", i, cur_amount);
    }

    return 0;
}
