#include <stdlib.h>
#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#define _(string) gettext(string)
#define LEFT_BOUND 1
#define RIGHT_BOUND 100
#define BUF_SZ 80

void print_greeting()
{
    printf(_("try to guess number between %d and %d\n"), LEFT_BOUND, RIGHT_BOUND);
}

char is_true_answer(char *ans)
{
    return !strcmp(ans, _("yes"));
}

char is_false_answer(char *ans)
{
    return !strcmp(ans, _("no"));
}

char is_correct_answer(char *ans)
{
    return is_true_answer(ans) || is_false_answer(ans);
}

char check(int x)
{
    printf(_("Is your number less than %d? "), x);
    char buf[BUF_SZ];
    scanf("%s", buf);

    while (!is_correct_answer(buf))
    {
        printf(_("Incorrect input. Please, type again. "));
        scanf("%s", buf);
    }

    return is_true_answer(buf);
}

void print_answer(int answer)
{
    printf(_("Guessed number is %d\n"), answer);
}


int main()
{
	setlocale(LC_ALL, "");
	
	bindtextdomain("binarysearch", ".");
	textdomain("binarysearch");

	print_greeting();


	int bl = LEFT_BOUND, br = RIGHT_BOUND + 1;

	while (br - bl > 1)
    {
	    int bm = (bl + br) / 2;
        if (check(bm))
        {
            br = bm;
        }
        else
        {
            bl = bm;
        }
    }

    print_answer(bl);
	return 0;
}
