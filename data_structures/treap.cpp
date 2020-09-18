#include <bits/stdc++.h>

using namespace std;

class treap
{
private:
    struct node
    {
        int key;
        int prior;
        int size;
        node* child_left;
        node* child_right;
        node(): key(0), prior(rand()), size(0), child_left(nullptr), child_right(nullptr){}
        node(int key__): key(key__), prior(rand()), size(1), child_left(nullptr), child_right(nullptr){}
    };
    typedef node* ptr_node;
    ptr_node root = nullptr;
    int get_size(ptr_node curr_node)
    {
        if (curr_node == nullptr)
            return 0;
        else
            return curr_node->size;
    }
    void update(ptr_node &curr_node)
    {
        if (curr_node != nullptr)
            curr_node->size = get_size(curr_node->child_left) + get_size(curr_node->child_right) + 1;
    }
    void split (ptr_node curr_node, ptr_node &new_l, ptr_node &new_r, int sep_key)
    {
        if (curr_node == nullptr)
        {
            new_l = nullptr;
            new_r = nullptr;
        }
        else if (curr_node->key < sep_key)
        {
            split(curr_node->child_right, curr_node->child_right, new_r, sep_key);
            new_l = curr_node;
            update(new_l);
        }
        else
        {
            split(curr_node->child_left, new_l, curr_node->child_left, sep_key);
            new_r = curr_node;
            update(new_r);
        }
    }
    void treap_merge(ptr_node &new_root, ptr_node left_treap, ptr_node right_treap)
    {
        if (left_treap == nullptr)
            new_root = right_treap;
        else if (right_treap == nullptr)
            new_root = left_treap;
        else if (right_treap->prior > left_treap->prior)
        {
            treap_merge(right_treap->child_left, left_treap, right_treap->child_left);
            new_root = right_treap;
        }
        else
        {
            treap_merge(left_treap->child_right, left_treap->child_right, right_treap);
            new_root = left_treap;
        }
        update(new_root);
    }
    void print(ptr_node curr_node)
    {
        if (curr_node != nullptr)
        {
            print(curr_node->child_left);
            cout << curr_node->key << " ";
            print(curr_node->child_right);
        }
    }
    bool find(ptr_node curr_node, int value)
    {
        if (curr_node == nullptr)
            return false;
        else if (curr_node->key == value)
            return true;
        else if (curr_node->key > value)
            return find(curr_node->child_left, value);
        else
            return find(curr_node->child_right, value);
    }
    int get_kth(ptr_node curr_node, int index)
    {
        if (curr_node == nullptr)
            return (size_t) -1;
        else if (get_size(curr_node->child_left) > index)
            return get_kth(curr_node->child_left, index);
        else if (get_size(curr_node->child_left) == index)
            return curr_node->key;
        else
            return get_kth(curr_node->child_right, index - get_size(curr_node->child_left) - 1);
    }
    int find_pos(ptr_node curr_node, int value)
    {
        if (curr_node == nullptr)
            return -1;
        else if (curr_node->key == value)
            return get_size(curr_node->child_left) + 1;
        else if (curr_node->key > value)
            return find_pos(curr_node->child_left, value);
        else
            return find_pos(curr_node->child_right, value) + get_size(curr_node->child_left) + 1;
    }
public:
    void print()
    {
        print(root);
        cout << endl;
    }
    bool find(int value)
    {
        return find(root, value);
    }
    void insert(int value)
    {
        ptr_node left_treap;
        ptr_node right_treap;
        ptr_node ins_treap = new node(value);
        split(root, left_treap, right_treap, value);
        treap_merge(root, left_treap, ins_treap);
        treap_merge(root, root, right_treap);
    }
    void erase(int value)
    {
        ptr_node left_treap;
        ptr_node right_treap;
        ptr_node er_treap;
        split(root, left_treap, right_treap, value);
        split(right_treap, er_treap, right_treap, value + 1);
        treap_merge(root, left_treap, right_treap);
    }
    int operator[](int index)
    {
        return get_kth(root, index);
    }
    int find_pos(int value)
    {
        return find_pos(root, value);
    }
    int size()
    {
        return root->size;
    }
};


int main()
{
    char op;
    int val;
    treap my_treap;
    for (int i = 0; i < 100; i++)
    {
        cin >> op >> val;
        if (op == '+')
            my_treap.insert(val);
        else if (op == '-')
            my_treap.erase(val);
        else if (op == '?')
            my_treap.find(val) ? cout << "YES" << endl : cout << "NO" << endl;
        else if (op == 'k')
            cout << my_treap[val - 1] << endl;
        else if (op == 'p')
            cout << my_treap.find_pos(val) << endl;
        my_treap.print();
    }
}
