#include <stdlib.h>

void ft_list_remove_if(t_list **beginList, void *refValue, int (*cmp)())
{
    t_list *current = *beginList;
    t_list *prev = NULL;

    while (current != NULL)
    {
        if ((*cmp)(current->data, refValue) == 0)
        {
            if (prev == NULL)
            {
                // Remove the first node
                *beginList = current->next;
                free(current);
                current = *beginList;
            }
            else
            {
                // Remove a middle or last node
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}
