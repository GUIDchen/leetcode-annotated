// 题目：1250. 检查「好数组」（Check If It Is a Good Array）
// 思路：裴蜀定理——数组中存在若干数配上整数系数后和为 1，当且仅当这整组数的最大公约数为 1；于是只需一趟归约求出全体元素的 gcd。
// 时间复杂度：O(n log V)，n 为数组长度、V 为元素最大值（每次 gcd 是对数级）；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isGoodArray(vector<int>& nums) {  // nums：输入数组，元素均为正整数；返回这组数是否构成「好数组」
        int g = 0;  // g 保存已遍历元素的 gcd；用 0 作初值是因为 gcd(0, x) == x，正好不影响结果
        for (int x : nums) {  // 逐个枚举数组中的元素
            g = gcd(x, g);  // 把当前元素并入累计 gcd（std::gcd 定义在 <numeric>）
        }
        return g == 1;  // 裴蜀定理的结论：全体元素 gcd 为 1 时才能凑出和 1，否则凑不出
    }
};