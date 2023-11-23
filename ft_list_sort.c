void selectionSort(t_list *head) {
    t_list *current = head;
    while (current) {
        t_list *minNode = current;
        t_list *temp = current->next;

        while (temp) {
            if (temp->data < minNode->data) {
                minNode = temp;
            }
            temp = temp->next;
        }

        swapData(current, minNode);
        current = current->next;
    }
}
