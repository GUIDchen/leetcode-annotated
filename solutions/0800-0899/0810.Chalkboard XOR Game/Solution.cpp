// 题目：810. 黑板异或游戏（Chalkboard XOR Game）
// 思路：数学结论——数字个数为偶数时先手必胜；个数为奇数时，先手必胜当且仅当所有数字异或和为 0。
// 时间复杂度：O(n)，一遍求异或和；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool xorGame(vector<int>& nums) {  // nums 是黑板上的数字，返回先手是否必胜
        if (nums.size() % 2 == 0) return true;  // 个数为偶数时先手必胜，直接返回 true
        int x = 0;  // 累加异或和，初值为 0
        for (int& v : nums) x ^= v;  // 逐个元素异或进 x
        return x == 0;  // 奇数个元素时，只有异或和为 0 先手才必胜
    }  // 方法结束
};  // 类定义结束