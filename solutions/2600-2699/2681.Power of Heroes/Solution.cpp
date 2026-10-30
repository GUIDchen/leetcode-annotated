// 题目：2681. 英雄的力量（Power of Heroes）
// 思路：降序排序后逐个充当「最大值」，用滚动变量 p 累积前面所有元素作为最小值时的 2 的幂次权值，把 x^3 与 x*p 累加进答案。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，只用了排序的递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOfPower(vector<int>& nums) {  // nums：英雄的力量值数组
        const int mod = 1e9 + 7;  // 取模常量，答案需要对 1e9+7 取模
        sort(nums.rbegin(), nums.rend());  // 降序排序，这样遍历时可以保证当前 x 就是子集里的最大值
        long long ans = 0, p = 0;  // ans：累加的答案；p：前面元素贡献的 2 次幂加权和
        for (long long x : nums) {  // 按降序依次把每个元素当作最大值处理
            ans = (ans + (x * x % mod) * x) % mod;  // 只含 x 一个元素的子集贡献 x^3，先加上并取模
            ans = (ans + x * p % mod) % mod;  // 以 x 为最大值的更大子集贡献 x*p，再加上并取模
            p = (p * 2 + x * x % mod) % mod;  // 更新 p：多出 x 一个候选最小值后权值整体翻倍，并加上 x^2
        }  // 遍历结束
        return ans;  // 返回取模后的总力量
    }  // 方法结束
};  // 类定义结束