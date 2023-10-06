#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int     ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char* mul_infinite(char *str1, char *str2)
{
    int len1 = ft_strlen(str1);
    int len2 = ft_strlen(str2);

    char *temp_res = (char *)malloc((len1 + len2 + 1) * sizeof(char));  // Added 1 for null terminator
    for(int i = 0; i < len1 + len2; i++)
        temp_res[i] = '0'; // Initialize with character '0' instead of number 0
    temp_res[len1 + len2] = '\0'; // Null terminate

    for(int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        for(int j = len2 - 1; j >= 0; j--)
        {
            int mul = (str1[i] - '0') * (str2[j] - '0') + carry + (temp_res[i+j+1] - '0');
            temp_res[i+j+1] = (mul % 10) + '0';
            carry = mul / 10;
        }
        temp_res[i] += carry;
    }

    int start = 0;
    while (temp_res[start] == '0' && start < len1 + len2 - 1)
        start++;

    return temp_res + start;
}

int     main(int argc, char *argv[])
{
    if (argc != 3)
        return (1);

    bool is_neg1 = (argv[1][0] == '-');
    bool is_neg2 = (argv[2][0] == '-');

    if (is_neg1)
        argv[1]++;
    if (is_neg2)
        argv[2]++;

    char * result = mul_infinite(argv[1], argv[2]);

    if ((is_neg1 && !is_neg2) || (!is_neg1 && is_neg2))
        write(1, "-", 1);

    for (int i = 0; result[i]; i++)
    {
        write(1, &result[i], 1);
    }
    write(1, "\n", 1);

    return (0);
}
