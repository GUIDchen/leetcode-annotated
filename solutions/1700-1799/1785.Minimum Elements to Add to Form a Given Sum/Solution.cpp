// 题目：1785. 构成特定和需要添加的最少元素（Minimum Elements to Add to Form a Given Sum）
// 思路：先算出数组和与目标值 goal 的差值，每个可加元素的绝对值不超过 limit，最少个数就是差值的向上取整。
// 时间复杂度：O(n)，一次遍历求和；空间复杂度：O(1)，只用到常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minElements(vector<int>& nums, int limit, int goal) {  // nums 是原数组，limit 是每个可加元素的绝对值上限，goal 是目标和
        long long s = accumulate(nums.begin(), nums.end(), 0ll);  // 用 64 位初值 0ll 累加，避免求和溢出
        long long d = abs(s - goal);  // 还差的绝对值，取 64 位重载避免溢出
        return (d + limit - 1) / limit;  // 向上取整：每个元素最多补 limit，整除写法避免浮点误差
    }
};