#include <iostream>
#include <set>

int GCD(int val1, int val2)
{
    if (val1 < val2)
        return GCD(val2, val1);

    if (!(val1 % val2))
        return val2;

    while (val2) {
        int temp_val = val2;
        val2 = val1 % val2;
        val1 = temp_val;
    }
    return val1;
}

bool can_weight(const std::set<int>& weights)
{
    auto count = weights.size();
    if (count == 1)
        return (*weights.begin() == 1);

    auto it = weights.begin();
    int val2 = *it++;
    while (it != weights.end()) {
        int res = GCD(*it, val2);
        if (res == 1)
            return true;
        else
            val2 = res;
        ++it;
    }
    return false;
}

int main()
{
    int count = 0, weight;
    std::cin >> count;
    std::set<int> weights;
    for (int i=0; i<count; ++i) {
        std::cin >> weight;
        weights.insert(weight);
    }
    std::cout << (can_weight(weights) ? "YES" : "NO") << std::endl;
    return 0;
}
