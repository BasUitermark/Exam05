#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list
{
	char			data;
	struct s_list	*next;
}	t_list;

t_list	*lstnew(char data)
{
	t_list	*node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

void	add_front(t_list **lst, char data)
{
	t_list	*node = lstnew(data);
	if (!node)
		return;
	node->next = *lst;
	*lst = node;
}

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	sum_infinite(t_list **result, char *str1, char *str2)
{
	int	len1 = ft_strlen(str1);
	int	len2 = ft_strlen(str2);
	int	carry = 0;

	while (len1 > 0 || len2 > 0 || carry)
	{
		int num1 = (len1-- > 0) ? (str1[len1] - '0') : 0;
		int num2 = (len2-- > 0) ? (str2[len2] - '0') : 0;
		int sum = num1 + num2 + carry;

		add_front(result, (sum % 10) + '0');
		carry = sum / 10;
	}
}

void	sub_infinite(t_list **result, char *str1, char *str2)
{
	int len1 = ft_strlen(str1);
	int len2 = ft_strlen(str2);
	int carry = 0;

	while (len1 > 0 || len2 > 0)
	{
		int num1 = (len1-- > 0) ? (str1[len1] - '0') : 0;
		int num2 = (len2-- > 0) ? (str2[len2] - '0') : 0;
		int diff = num1 - num2 - carry;

		if (diff < 0)
		{
			diff += 10;
			carry = 1;
		}
		else
			carry = 0;

		add_front(result, (diff % 10) + '0');
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (1);

	t_list	*result = NULL;
	bool is_neg1 = (argv[1][0] == '-');
	bool is_neg2 = (argv[2][0] == '-');

	if (is_neg1)
		argv[1]++;
	if (is_neg2)
		argv[2]++;

	if (is_neg1 == is_neg2)
		sum_infinite(&result, argv[1], argv[2]);
	else
		sub_infinite(&result, argv[1], argv[2]);

	if ((is_neg1 && !is_neg2 && ft_strlen(argv[1]) > ft_strlen(argv[2])) || (is_neg2 && !is_neg1 && ft_strlen(argv[2]) > ft_strlen(argv[1])))
		write(1, "-", 1);

	while (result)
	{
		write(1, &result->data, 1);
		result = result->next;
	}
	write(1, "\n", 1);

	return (0);
}
