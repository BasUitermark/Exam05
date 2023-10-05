#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list
{
    char            data;
    struct s_list   *next;
}   t_list;

t_list   *lstnew(char data)
{
    t_list  *node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->data = data;
    node->next = NULL;
    return (node);
}

int     ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    add_back(t_list **lst, char data)
{
    t_list  *node = lstnew(data);
    if (!node)
        return;

    if (*lst == NULL)
    {
        *lst = node;
        return;
    }

    t_list *current = *lst;
    while (current->next)
        current = current->next;

    current->next = node;
}

void    mul_infinite(t_list **result, char *str1, char *str2)
{
    int len1 = ft_strlen(str1);
    int len2 = ft_strlen(str2);

    int *temp_res = (int *)malloc((len1 + len2) * sizeof(int));
    for(int i = 0; i < len1 + len2; i++)
        temp_res[i] = 0;

    for(int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        for(int j = len2 - 1; j >= 0; j--)
        {
            int mul = (str1[i] - '0') * (str2[j] - '0') + carry + temp_res[i+j+1];
            temp_res[i+j+1] = mul % 10;
            carry = mul / 10;
        }
        temp_res[i] += carry;
    }

    int start = 0;
    while(start < len1 + len2 - 1 && temp_res[start] == 0)
        start++;

    for(int i = start; i < len1 + len2; i++)
        add_back(result, temp_res[i] + '0');

    free(temp_res);
}

int     main(int argc, char *argv[])
{
    if (argc != 3)
        return (1);

    t_list  *result = NULL;
    bool is_neg1 = (argv[1][0] == '-');
    bool is_neg2 = (argv[2][0] == '-');

    if (is_neg1)
        argv[1]++;
    if (is_neg2)
        argv[2]++;

    mul_infinite(&result, argv[1], argv[2]);

    if ((is_neg1 && !is_neg2) || (!is_neg1 && is_neg2))
        write(1, "-", 1);

    while (result)
    {
        write(1, &result->data, 1);
        result = result->next;
    }
    write(1, "\n", 1);

    return (0);
}
