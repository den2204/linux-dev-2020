#include <stdlib.h>
#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#define _(string) gettext(string)
/** Minimal bound */
#define LEFT_BOUND 1
/** Maximal bound */
#define RIGHT_BOUND 100
#define BUF_SZ 80

#define HELP_MSG _("Usage: binarysearch [OPTION]..\n\
Guess number from given range\n\
\n\
-r    use roman number notation (arabic by default)\n\
\n\
User should imagine some number from given range.\n\
Program tries to guess this number using binary search.\n")


const char *roman_precalc[] = {"N", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C", "CI"};


/**
 * Transforms arabic number into roman
 *
 * @param x arabic integer
 * @return roman integer
 */
char* arabic_to_roman(int x)
{
    return roman_precalc[x];
}


/**
 * Transforms roman number into arabic
 *
 * @param s roman integer
 * @return arabic integer
 */
int roman_to_arabic(char *s)
{
    for (int i = LEFT_BOUND; i <= RIGHT_BOUND; i++)
    {
        if (!strcmp(roman_precalc[i], s))
        {
            return i;
        }
    }
    return -1;
}

/**
 * Checks answer is `yes`
 * @param ans string
 * @return boolean
 */
char is_true_answer(char *ans)
{
    return !strcmp(ans, _("yes"));
}


/**
 * Checks answer is `no`
 * @param ans string
 * @return boolean
 */
char is_false_answer(char *ans)
{
    return !strcmp(ans, _("no"));
}


/**
 * Checks answer is correct
 * @param ans string
 * @return boolean
 */
char is_correct_answer(char *ans)
{
    return is_true_answer(ans) || is_false_answer(ans);
}

void print_desirable_type(char *buf, int x, char is_roman)
{
    if (is_roman)
    {
        strcpy(buf, roman_precalc[x]);
    }
    else
    {
        sprintf(buf, "%d", x);
    }
}

/**
 * Prints greeting
 * @param is_roman
 */
void print_greeting(char is_roman)
{
    char buf[2][BUF_SZ];
    print_desirable_type(buf[0], LEFT_BOUND, is_roman);
    print_desirable_type(buf[1], RIGHT_BOUND, is_roman);
    printf(_("try to guess number between %s and %s\n"), buf[0], buf[1]);
}


/**
 * Tries to guess number
 * @param x
 * @param is_roman
 * @return boolean
 */
char check(int x, char is_roman)
{
    char buf[BUF_SZ];
    print_desirable_type(buf, x, is_roman);

    printf(_("Is your number less than %s? "), buf);
    scanf("%s", buf);

    while (!is_correct_answer(buf))
    {
        printf(_("Incorrect input. Please, type again. "));
        scanf("%s", buf);
    }

    return is_true_answer(buf);
}

/**
 * Prints imagined number
 * @param answer
 * @param is_roman
 */
void print_answer(int answer, char is_roman)
{
    char buf[BUF_SZ];
    print_desirable_type(buf, answer, is_roman);
    printf(_("Guessed number is %s\n"), buf);
}


int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    bindtextdomain("binarysearch", ".");
    textdomain("binarysearch");

    char is_roman = 0;
    char need_help = 0;

    for (int i = 1; i < argc; i++)
    {
        is_roman |= !strcmp(argv[i], "-r");
        need_help |= !strcmp(argv[i], "--help");
    }

    if (need_help)
    {
        printf(HELP_MSG);
        return 0;
    }

	print_greeting(is_roman);

	int bl = LEFT_BOUND, br = RIGHT_BOUND + 1;

	while (br - bl > 1)
    {
	    int bm = (bl + br) / 2;
        if (check(bm, is_roman))
        {
            br = bm;
        }
        else
        {
            bl = bm;
        }
    }

    print_answer(bl, is_roman);
	return 0;
}
