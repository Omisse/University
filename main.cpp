#include <cctype>
#include <clocale>
#include <stdio.h>

#define STR_ACTIONS \
"Выберите желаемое действие:\n\
\t0 - Завершить работу.\n\
\t1 - Найти среднее арифметическое элементов списка\n\
\t2 - Определить, входит ли список L1 в cписок L2, вывести адрес начала вхождения\n\
(L1, L2 - списки, введённые первым и вторым соответственно)\n"

#define ERRSTR_INVALID_TASK_INPUT \
"Некорректный ввод, введите 0, 1 или 2!\n"

#define STR_LIST_INPUT \
"Введите список, состоящий из целых чисел в пределах [-2^31; 2^31-1]\n\
Формат ввода: <элемент>, <элемент>, ...\n"

struct List {
    int value;
    List* next;
    List (int val = 0, List* np = NULL) {
        value = val;
        next = np;
    }
};

List* insert(int new_value, List* head) {
    List* new_head = new List(new_value, head);
    return new_head;
}

List* push_back(int new_value, List* head) {
    if (!head) return new List(new_value);

    List* traversal = head;
    while (traversal->next) traversal = traversal->next;
    traversal->next = new List(new_value);
    return head;
}

List* insert_sorted(int new_value, List* head) {
    if (!head) {
        head = new List(new_value);
        return head;
    }

    List* traversal = head;
    while (new_value > traversal->value && traversal->next) traversal = traversal->next;
    List* alloc_ptr = insert(new_value, traversal->next);
    if (alloc_ptr) {
        traversal->next = alloc_ptr;
        if (traversal->value > alloc_ptr->value) {
            alloc_ptr->value = traversal->value;
            traversal->value = new_value;
        }
    }
    return alloc_ptr;
}

List* insert_at(int new_value, int idx, List* head) {
    if (!head) {
        head = new List(new_value);
        return head;
    }

    List* traversal = head;
    while (traversal->next && idx) {
        idx--;
        traversal = traversal->next;
    }
    List* alloc_ptr = insert(new_value, traversal->next);
    if (alloc_ptr) {
        traversal->next = alloc_ptr;
    }

    return alloc_ptr;
}

List* delete_last(List* head, int& out) {
    if (head) {
        List* traversal = head;
        List* old_traversal = NULL;
        while (traversal->next) {
            old_traversal = traversal;
            traversal = traversal->next;
        }
        if (old_traversal) {
            old_traversal->next = NULL;
        } else {
            head = NULL;
        }
        out = traversal->value;
        delete traversal;
    }
    return head;
}

List* delete_first(List* head, int& out) {
    List* retval = NULL;
    if (head) {
        out = head->value;
        retval = head->next;
        delete head;
    }
    return retval;
}

void delete_list(List* head) {
    while (head) {
        List* buff = head->next;
        delete head;
        head = buff;
    }
}


int get_user_choice() {
    printf(STR_ACTIONS);
    int user_choice = fgetc(stdin);
    while (user_choice < '0' || user_choice > '2') {
        printf(ERRSTR_INVALID_TASK_INPUT);
        user_choice = fgetc(stdin);
    }
    char ch = 'f';
    while (ch && ch != '\n' && ch != EOF) ch = fgetc(stdin);
    return user_choice-'0';
}

List* get_user_list() {
    List* out = 0;
    int err = 0;
    char ch = 'f';
    while (ch && ch != '\n' && ch != EOF && !isdigit(ch)) ch = fgetc(stdin);
    while (ch && ch != '\n' && ch != EOF && !err) {
        int new_value = 0;
        int was_value = isdigit(ch);
        while (isdigit(ch)) {
            new_value *= 10;
            new_value += ch - '0';
            ch = fgetc(stdin);
        }
        while (isblank(ch) || ch == ',') ch = fgetc(stdin);
        err = ch != EOF && ch != '\n' && ch != 0 && !isdigit(ch);
        if (was_value && !err) {
            List* alloc_ptr = push_back(new_value, out);
            err = !alloc_ptr;
            if (!err) out = alloc_ptr;
        }
    }
    if (err) {
        while (ch && ch != '\n' && ch != EOF) ch = fgetc(stdin);
        delete_list(out);
        out = 0;
    }
    return out;
}

void print_list(List* head) {
    if (!head) return;

    while (head) {
        printf("%d", head->value);
        head = head->next;
        if (head) printf(", ");
    }
    printf("\n");
}

double get_average(List* head) {
    int elements = 0;
    double sum = 0.0f;
    double out = 0.0f;
    while (head) {
        sum += head->value;
        elements++;
        head = head->next;
    }
    if (elements) out = sum / elements;
    return out;
}

List* lstlst(List* needle, List* haystack) {
    if (!needle || !haystack) {
        return 0;
    }

    List* out = 0;
    while (haystack && !out) {
        if (haystack->value == needle->value) {
            List *hptr = haystack, *nptr = needle;
            long long int val_diff = 0;
            while (hptr && nptr && !val_diff) {
                val_diff = hptr->value - nptr->value;
                hptr = hptr->next;
                nptr = nptr->next;
            }
            if (!val_diff && !nptr) out = haystack;
        }
        haystack = haystack->next;
    }
    return out;
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int user_choice = 3;
    while (user_choice) {
        user_choice = get_user_choice();
        if (user_choice == 1) {
            List* L1 = 0;
            printf(STR_LIST_INPUT);
            printf("L1: ");
            L1 = get_user_list();
            if (!L1) printf("Ошибка ввода.\n");
            else {
                printf("Введённый список: ");
                print_list(L1);
                printf("Среднее арифметическое: %0.3lf\n", get_average(L1));
                delete_list(L1);
            }
        } else if (user_choice == 2) {
            List *L1 = 0, *L2 = 0;
            printf(STR_LIST_INPUT);
            printf("L1: ");
            L1 = get_user_list();
            int err = !L1;
            if (!err) {
                printf(STR_LIST_INPUT);
                printf("L2: ");
                L2 = get_user_list();
                err = !L2;
            }
            if (!err) {
                printf("Введено:\n");
                printf("L1: "); print_list(L1);
                printf("L2: "); print_list(L2);
                List* addr = lstlst(L1, L2);
                if (addr) printf("Вхождение найдено, адрес: %p\n", addr);
                else printf("L1 не входит в L2.\n");
            } else printf("Ошибка ввода.\n");
            delete_list(L1); delete_list(L2);
        }
    }
    
    
    return 0;
}