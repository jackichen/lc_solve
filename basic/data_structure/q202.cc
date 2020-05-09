// detect circle in a list
class Solution {
    int get_next(int n) {
        int sum = 0;
        while (n) {
            int digit = n % 10;
            sum += digit*digit;
            n /= 10;
        }
        return sum;
    }
public:
    bool isHappy(int n) {
        int slow_sum = get_next(n);
        if (slow_sum == 1) return true;
        int fast_sum = get_next(slow_sum);
        while (fast_sum != 1 && fast_sum != slow_sum) {
            slow_sum = get_next(slow_sum);
            fast_sum = get_next(get_next(fast_sum));
        }
        return fast_sum == 1;
    }
};
