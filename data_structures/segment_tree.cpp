#include <bits/stdc++.h>

using namespace std;

struct node
{
    long long left, right;
    long long value, add;
    node* child_left;
    node* child_right;
};

node* build (vector <long long> &mas, long long l, long long r)
{
    if (l > r)
        return 0;
    node* res = new node;
    res->left = l;
    res->right = r;
    res->add = 0;
    if (l == r)
    {
        res->child_left = nullptr;
        res->child_right = nullptr;
        res->value = mas[l];
    }
    else
    {
        long long mid = (l + r) / 2;
        res->child_left = build(mas, l, mid);
        res->child_right = build(mas, mid + 1, r);
        res->value = min(res->child_left->value, res->child_right->value);
    }
    return res;
}

long long query(node* root, long long l, long long r)
{
    if (r < root->left || l > root->right )
        return 2e9;
    if (l <= root->left && r >= root->right)
        return root->value + root->add;
    long long ans1 = query(root->child_left, l, r);
    long long ans2 = query(root->child_right, l, r);
    return min(ans1, ans2) + root->add;
}

void refresh(node* root, long long l, long long r, long long delta)
{
    if (l > root->right || r < root->left)
        return;
    if (l <= root->left && r >= root->right)
    {
        root->add += delta;
        return;
    }
    refresh(root->child_left, l, r, delta);
    refresh(root->child_right, l, r, delta);
    root->value = min(root->child_left->value + root->child_left->add, root->child_right->value + root->child_right->add);
}

int main()
{
    char c;
    long long N = 0, M = 0, a = 0, u = 0, v = 0, delta = 0;
    cin >> N;
    vector <long long> mas(N, 0);
    for (long long i = 0; i < N; i++)
        cin >> mas[i];
    node* root = build(mas, 0, N - 1);
    cin >> M;
    for (long long i = 0; i < M; i++)
    {
        cin >> c;
        if (c == 'g')
        {
            cin >> a;
            cout << query(root, a - 1, a - 1) << endl;
        }
        else
        {
            cin >> u >> v >> delta;
            refresh(root, u - 1, v - 1, delta);
        }
    }
}
