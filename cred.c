#include <cs50.h>
#include <stdio.h>

void test_number(long card_num);
bool algorithm_test(long card_num, int num_long);

int main(void)
{
    long number = 0;

    // Prompts user to input a string of numbers for the card
    do
    {
        number = get_long("Number: ");
    }
    while (!number);

    // Call function to test validity of the card number
    test_number(number);
}

void test_number(long card_num)
{
    // Initialize variables to be the divisor when finding the first number/s of the card
    long amex_15 = 10000000000000;
    long master_16 = amex_15 * 10;
    long visa_16 = master_16 * 10;
    long visa_13 = visa_16 / 1000;

    // Reuse variables to store the first number/s of the card
    amex_15 = card_num / amex_15;
    master_16 = card_num / master_16;
    visa_16 = card_num / visa_16;
    visa_13 = card_num / visa_13;

    // Test if the first number/s is/are valid
    // If valid, call function to perform Luhn's algorithm
    if (amex_15 == 34 || amex_15 == 37)
    {
        if (algorithm_test(card_num, 15))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (master_16 == 51 || master_16 == 52 || master_16 == 53 || master_16 == 54 || master_16 == 55)
    {
        if (algorithm_test(card_num, 16))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (visa_16 == 4 || visa_13 == 4)
    {
        // VISA card numbers can be 16- or 13- digits, so perform Luhn's algorithm according to card length
        if (algorithm_test(card_num, 16) || algorithm_test(card_num, 13))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

bool algorithm_test(long card_num, int num_long)
{
    int loop_times = 0;
    // 15-digit cards can sum 7 (doubled) digits and the 8 remaining digits
    if (num_long == 15)
    {
        loop_times = 7;
    }
    // 16-digit cards can sum 8 (doubled) digits and the 8 remaining digits
    else if (num_long == 16)
    {
        loop_times = 8;
    }
    // 13-digit cards can sum 6 (doubled) digits and the 7 remaining digits
    else if (num_long == 13)
    {
        loop_times = 6;
    }

    long add = 0;
    int sum = 0;
    long mod = 100;
    // Perfom the doubling of every other digit by 2 and add them to the sum
    for (int i = 0; i < loop_times; i++)
    {
        add = card_num % mod;
        add /= mod / 10;
        add *= 2;
        if (add > 9)
        {
            add = (add % 10) + (add / 10);
        }
        sum += add;
        mod *= 100;
    }

    // Increment loop times by 1 for 13- and 15-digit card numbers
    if (num_long == 13 || num_long == 15)
    {
        loop_times++;
    }

    // Look for the remaining non-doubled digits and add them to the sum
    mod = 10;
    for (int i = 0; i < loop_times; i++)
    {
        add = card_num % mod;
        add /= mod / 10;
        sum += add;
        mod *= 100;
    }

    // Check if the last digit of the sum is zero
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}