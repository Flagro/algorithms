#include <iostream>
#include <string>

using namespace std;

class treap // Декартово дерево по неявному ключу
{
private:
    struct node
    {
        int key; // Значение узла дерева
        int prior; // Рандомизированный приоритет узла дерева
        int size; // Размер дерева
        int max_value; // Максимальное значение на поддереве
        int min_value; // Минимальное значение на поддереве
        int sum; // Сумма элементов на поддереве
        int add; // "Добавка" к элементам поддерева для групповой операции добавления на отрезке
        bool reversed; // Признак перевернутости элементов поддерева
        node* child_left; // Указатель на левого потомка
        node* child_right; // Указатель на правого потомка
        /* Пустой конструктор */
        node(): key(0), prior(rand()), size(0), max_value(-2e9), min_value(2e9), sum(0), add(0), reversed(false), child_left(nullptr), child_right(nullptr) {}
        /* Конструктор с инициализацией значения узла дерева */
        node(int key__): key(key__), prior(rand()), size(1), max_value(key__), min_value(key__), sum(key__), add(0), reversed(false), child_left(nullptr), child_right(nullptr) {}
    };
    typedef node* ptr_node_type; // Переопределение ссылочного типа для структуры узла
    ptr_node_type treap_root = nullptr; // Корень декартового дерева
    /* Безопасное извлечение размера дерева */
    int get_size(ptr_node_type root)
    {
        if (root == nullptr)
            return 0;
        else
            return root->size;
    }
    /* Безопасное извлечение максимального элемента дерева */
    int get_max(ptr_node_type root)
    {
        if (root == nullptr)
            return -2e9;
        else
            return root->max_value + root->add;
    }
    /* Безопасное извлечение минимального элемента дерева */
    int get_min(ptr_node_type root)
    {
        if (root == nullptr)
            return 2e9;
        else
            return root->min_value + root->add;
    }
    /* Безопасное извлечение суммы элементов дерева */
    long long get_sum(ptr_node_type root)
    {
        if (root == nullptr)
            return 0;
        else
            return root->sum + root->add;
    }
    /* Обновление размера дерева */
    void update(ptr_node_type &root)
    {
        if (root != nullptr)
            root->size = 1 + get_size(root->child_left) + get_size(root->child_right);
    }
    /* Обновление значения максимального элемента дерева */
    void update_max(ptr_node_type &root)
    {
        if (root != nullptr)
            root->max_value = max(max(get_max(root->child_left), get_max(root->child_right)), root->key + root->add);
    }
    /* Обновление значения минимального элемента дерева */
    void update_min(ptr_node_type &root)
    {
        if (root != nullptr)
            root->min_value = min(min(get_min(root->child_left), get_min(root->child_right)), root->key + root->add);
    }
    /* Обновление значения суммы элементов дерева */
    void update_sum(ptr_node_type &root)
    {
        if (root != nullptr)
            root->sum = get_sum(root->child_left) + get_sum(root->child_right) + root->key + root->add;
    }
    /* "Полное" обновление узла дерева */
    void full_update(ptr_node_type &root)
    {
        if (root != nullptr)
        {
            update(root);
            update_max(root);
            update_min(root);
            update_sum(root);
        }
    }
    /* "Проталкивание" значения добавки узла дерева к его потомкам для реализации функции слияния и разделения дерева */
    void push_add(ptr_node_type &root)
    {
        if (root != nullptr)
        {
            if (root->child_left != nullptr)
                root->child_left->add += root->add;
            if (root->child_right != nullptr)
                root->child_right->add += root->add;
            root->key += root->add;
            root->add = 0;
        }
    }
    /* "Проталкивание" признака переворота узла дерева к его потомкам для реализации функции слияния и разделения дерева */
    void push_reversed(ptr_node_type &root)
    {
        if (root != nullptr)
        {
            if (root->child_left != nullptr)
                root->child_left->reversed ^= root->reversed;
            if (root->child_right != nullptr)
                root->child_right->reversed ^= root->reversed;
            if (root->reversed == true)
                swap(root->child_left, root->child_right);
            root->reversed = false;
        }
    }
    /* Функция разделения дерева root на два поддерева left и right таким образом, что в дереве left ровно k элементов */
    void split(ptr_node_type root, ptr_node_type &left, ptr_node_type &right, int k)
    {
        push_add(root);
        push_reversed(root);
        if (root == nullptr)
        {
            left = nullptr;
            right = nullptr;
        }
        else if (get_size(root->child_left) >= k)
        {
            split(root->child_left, left, root->child_left, k);
            right = root;
            full_update(right);
        }
        else
        {
            split(root->child_right, root->child_right, right, k - get_size(root->child_left) - 1);
            left = root;
            full_update(left);
        }
    }
    /* Функция слияния поддеревьев left и right в дерево root */
    void merge(ptr_node_type &root, ptr_node_type left, ptr_node_type right)
    {
        if (left == nullptr)
            root = right;
        else if (right == nullptr)
            root = left;
        else if (right->prior > left->prior)
        {
            push_add(right);
            push_reversed(right);
            merge(right->child_left, left, right->child_left);
            root = right;
        }
        else
        {
            push_add(left);
            push_reversed(left);
            merge(left->child_right, left->child_right, right);
            root = left;
        }
        full_update(root);
    }
    void insert(ptr_node_type &root, int k, int value)
    {
        ptr_node_type left, right;
        ptr_node_type ins = new node(value);
        split(root, left, right, k);
        merge(root, left, ins);
        merge(root, root, right);
    }
    void push_back(ptr_node_type &root, int value)
    {
        ptr_node_type ins = new node(value);
        merge(root, root, ins);
    }
    void push_front(ptr_node_type &root, int value)
    {
        ptr_node_type ins = new node(value);
        merge(root, ins, root);
    }
    void erase(ptr_node_type &root, int k)
    {
        ptr_node_type left, kth, right;
        split(root, left, kth, k);
        split(kth, kth, right, k + 1);
        merge(root, left, right);
    }
    void pop_back(ptr_node_type &root)
    {
        ptr_node_type last;
        split(root, root, last, get_size(root) - 1);
    }
    void print(ptr_node_type root)
    {
        if (root == nullptr)
            return;
        else
        {
            print(root->child_left);
            cout << root->key << " ";
            print(root->child_right);
        }
    }
    int max_query(ptr_node_type root, int left, int right)
    {
        ptr_node_type left_tree, query, right_tree;
        split(root, left_tree, right_tree, left);
        split(right_tree, query, right_tree, right - left + 1);
        int ans = get_max(query);
        merge(root, left_tree, query);
        merge(root, root, right_tree);
        return ans;
    }
    int min_query(ptr_node_type root, int left, int right)
    {
        ptr_node_type left_tree, query, right_tree;
        split(root, left_tree, right_tree, left);
        split(right_tree, query, right_tree, right - left + 1);
        int ans = get_min(query);
        merge(root, left_tree, query);
        merge(root, root, right_tree);
        return ans;
    }
    long long sum_query(ptr_node_type root, int left, int right)
    {
        ptr_node_type left_tree, query, right_tree;
        split(root, left_tree, right_tree, left);
        split(right_tree, query, right_tree, right - left + 1);
        long long ans = get_sum(query);
        merge(root, left_tree, query);
        merge(root, root, right_tree);
        return ans;
    }
    void add_delta(ptr_node_type &root, int left, int right, int delta)
    {
        ptr_node_type left_tree, query, right_tree;
        split(root, left_tree, right_tree, left);
        split(right_tree, query, right_tree, right - left + 1);
        query->add += delta;
        merge(root, left_tree, query);
        merge(root, root, right_tree);
    }
    void reverse_tree(ptr_node_type &root, int left, int right)
    {
        ptr_node_type left_tree, query, right_tree;
        split(root, left_tree, right_tree, left);
        split(right_tree, query, right_tree, right - left + 1);
        query->reversed ^= true;
        merge(root, left_tree, query);
        merge(root, root, right_tree);
    }
    int get_element(ptr_node_type root, int k)
    {
        ptr_node_type left_tree, query, right_tree;
        split(root, left_tree, right_tree, k);
        split(right_tree, query, right_tree, 1);
        int ans = query->key;
        merge(root, left_tree, query);
        merge(root, root, right_tree);
        return ans;
    }
public:
    void insert(int k, int value)
    {
        insert(treap_root, k, value);
    }
    void push_back(int value)
    {
        push_back(treap_root, value);
    }
    void push_front(int value)
    {
        push_front(treap_root, value);
    }
    void erase(int k)
    {
        erase(treap_root, k);
    }
    void pop_back()
    {
        pop_back(treap_root);
    }
    void print()
    {
        print(treap_root);
        cout << endl;
    }
    int max_query(int left, int right)
    {
        return max_query(treap_root, left, right);
    }
    int min_query(int left, int right)
    {
        return min_query(treap_root, left, right);
    }
    long long sum_query(int left, int right)
    {
        return sum_query(treap_root, left, right);
    }
    void add_delta(int left, int right, int delta)
    {
        add_delta(treap_root, left, right, delta);
    }
    void reverse_tree(int left, int right)
    {
        reverse_tree(treap_root, left, right);
    }
    int operator[](int k)
    {
        return get_element(treap_root, k);
    }
};

int main()
{
    string op;
    int value, k, left, right;
    treap my_treap;
    for (int i = 0; i < 100; i++)
    {
        cin >> op;
        if (op == "push")
        {
            cin >> value;
            my_treap.push_back(value);
        }
        else if (op == "insert")
        {
            cin >> k >> value;
            my_treap.insert(k, value);
        }
        else if (op == "erase")
        {
            cin >> k;
            my_treap.erase(k);
        }
        else if (op == "pop")
        {
            my_treap.pop_back();
        }
        else if (op == "max")
        {
            cin >> left >> right;
            cout << my_treap.max_query(left, right) << endl;
        }
        else if (op == "min")
        {
            cin >> left >> right;
            cout << my_treap.min_query(left, right) << endl;
        }
        else if (op == "sum")
        {
            cin >> left >> right;
            cout << my_treap.sum_query(left, right) << endl;
        }
        else if (op == "add")
        {
            int delta = 0;
            cin >> left >> right >> delta;
            my_treap.add_delta(left, right, delta);
        }
        else if (op == "reverse")
        {
            cin >> left >> right;
            my_treap.reverse_tree(left, right);
        }
        else if (op == "get")
        {
            cin >> k;
            cout << my_treap[k] << endl;
        }
        my_treap.print();
    }
}
