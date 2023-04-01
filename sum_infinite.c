#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list
{
	char			data;
	struct s_list	*next;
}	t_list;

t_list	*lstnew(char data)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (0);
	head->data = data;
	head->next = NULL;
	return (head);
}

void add_front(t_list **lst, t_list *new_item)
{
	if (!lst)
	{
		*lst = new_item;
		return ;
	}
	new_item->next = *lst;
	*lst = new_item;
}

int	ft_strlen(char *str)
{
	int	i;
	if (!str)
		return (0);

	for (i = 0; str[i]; i++){
	}
	return (i);
}

void swap(char **str1, char **str2)
{
	char *temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

void sum_infinite(t_list **data, char *str1, char *str2, bool neg)
{
	int	n;
	int	carry = 0;
	int	dif;
	int	len1 = ft_strlen(str1);
	int len2 = ft_strlen(str2);


	if (len1 > len2)
		swap(&str1, &str2);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	dif = len2 - len1;

	for (int i = len1 - 1; i >= 0 && str1[i] != '-'; i--)
	{
		n = (str1[i] - '0') + (str2[i + dif] - '0') + carry;
		carry = n / 10;
		add_front(data, lstnew(n % 10 + '0'));
	}
	if (neg)
		len2++;
	for (int i = len2 - len1 - 1; i >= 0 && str2[i] != '-'; i--)
	{
		n = (str2[i] - '0') + carry;
		carry = n / 10;
		add_front(data, lstnew(n % 10 + '0'));
	}
	if (carry)
		add_front(data, lstnew(carry + '0'));
	if (neg)
		add_front(data, lstnew('-'));
}

void order_strings(char **str1, char **str2)
{
	bool	s1_bigger = true;

	int		len1 = ft_strlen(*str1);
	int		len2 = ft_strlen(*str2);
	len1 = *str1[0] == '-' ? len1 += -1 : len1;
	len2 = *str2[0] == '-' ? len2 += -1 : len2;

	if (len1 > len2)
		swap(str1, str2);
	else if (len2 > len1)
		return ;
	else
	{
		len1 = ft_strlen(*str1);
		len2 = ft_strlen(*str2);
		int i = *str1[0] == '-' ? 1 : 0;
		int j = *str2[0] == '-' ? 1 : 0;
		char	*str1t = *str1;
		char	*str2t = *str2;
		while (i < len1 && j < len2)
		{
			if (str1t[i] < str2t[j])
			{
				s1_bigger = false;
				break;
			}
			else if (str2t[j] < str1t[i])
			{
				s1_bigger = true;
				break;
			}
			i++;
			j++;
		}
		if (s1_bigger)
			swap(str1, str2);
		else if (len2 > len1)
			return ;
	}
}

void sub_infinite(t_list **data, char *str1, char *str2)
{
	order_strings(&str1, &str2);
	bool large_neg = str2[0] == '-' ? true : false;

	int len1 = ft_strlen(str2) - 1;
	int len2 = ft_strlen(str1) - 1;
	int carry = 0;
	
	while (len1 >= 0 || len2 >= 0) 
	{
		if (str2[len1] == '-' || str1[len2] == '-')
			break ;
		int num1 = (len1 >= 0) ? (str2[len1--] - '0') : 0;
		int num2 = (len2 >= 0) ? (str1[len2--] - '0') : 0;
		int sub = num1 - num2 - carry;
		if (sub < 0) 
		{
			sub += 10;
			carry = 1;
		}
		else
			carry = 0;
		if (len1 >= 0 && carry)
			add_front(data, lstnew(sub % 10 + '0'));
	}
	if (large_neg)
		add_front(data, lstnew('-'));
}

void	determine_type(t_list **data, char *str1, char *str2)
{
	bool	neg1 = false;
	bool	neg2 = false;

	if (str1[0] == '-')
		neg1 = true;
	if (str2[0] == '-')
		neg2 = true;
	
	if (!neg1 && !neg2)
		sum_infinite(data, str1, str2, false);
	else if (neg1 && neg2)
		sum_infinite(data, str1, str2, true);
	else
		sub_infinite(data, str1, str2);
}

int main(int argc, char *argv[])
{
	t_list	*data = NULL;
	if (argc != 3)
		return (1);
	determine_type(&data, argv[1], argv[2]);
	while (data)
	{
		write(1, &data->data, 1);
		data = data->next;
	}
	write(1, "\n", 1);
	return (0);
}
