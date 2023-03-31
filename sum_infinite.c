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
	if (head == NULL)
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

void	sum_infinite(t_list **data, char *str1, char *str2)
{
	bool	add = false;
	bool	neg = false;
	int		n1;
	int		n2;
	int		len1 = ft_strlen(str1) - 1;
	int 	len2 = ft_strlen(str2) - 1;

	if (str1[0] == '-' || str2[0] == '-')
		neg = true;
	while (len1 >= 0 && len2 >= 0 )
	{
		n1 = str1[len1] - '0';
		n2 = str2[len2] - '0';
		// if (neg)
		// 	n1 *= -1;
		n1 += n2;
		if (add)
		{
			n1 += 1;
			add = false;
		}
		if (n1 > 9)
		{
			n1 = n1 % 10;
			add = true;
		}
		add_front(data, lstnew(n1 + '0'));
		len1--;
		len2--;
	}
	if (add)
		add_front(data, lstnew('1'));
}

int main(int argc, char *argv[])
{
	t_list	*data = NULL;
	if (argc != 3)
		return (1);

	sum_infinite(&data, argv[1], argv[2]);
	while (data)
	{
		write(1, &data->data, 1);
		data = data->next;
	}
	write(1, "\n", 1);
	return (0);
}
