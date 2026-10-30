// 题目：805. 数组的均值分割（Split Array With Same Average）
// 思路：把「两部分均值相同」等价变形为数组 v*n - s 的某个非空真子集和为 0，于是折半枚举：左半的子集和存入哈希集，右半反查相反数。
// 时间复杂度：O(2^(n/2)·n)；空间复杂度：O(2^(n/2))，哈希集存左半所有子集和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool splitArraySameAverage(vector<int>& nums) {  // nums：输入数组；判断能否拆成两个均值相同的非空子集
        int n = nums.size();  // 元素个数
        if (n == 1) return false;  // 只有一个元素，无法拆成两个非空子集
        int s = accumulate(nums.begin(), nums.end(), 0);  // 数组元素总和
        for (int& v : nums) v = v * n - s;  // 关键变换：子集均值等于整体均值 ⇔ 变换后该子集元素和为 0
        int m = n >> 1;  // 折半点，左半 m 个、右半 n - m 个
        unordered_set<int> vis;  // 记录左半所有非空子集的和
        for (int i = 1; i < 1 << m; ++i) {  // 用位掩码枚举左半的非空子集
            int t = 0;  // 当前子集的元素和
            for (int j = 0; j < m; ++j)  // 逐位检查哪些元素被选中
                if (i >> j & 1) t += nums[j];  // 第 j 位为 1 表示选入该元素
            if (t == 0) return true;  // 左半自身就能给出合法子集
            vis.insert(t);  // 记录子集和，供右半反查
        }  // 左半枚举结束
        for (int i = 1; i < 1 << (n - m); ++i) {  // 枚举右半的非空子集
            int t = 0;  // 当前子集的元素和
            for (int j = 0; j < (n - m); ++j)  // 逐位检查右半元素
                if (i >> j & 1) t += nums[m + j];  // 下标要加上偏移 m 才是右半元素
            if (t == 0 || (i != (1 << (n - m)) - 1 && vis.count(-t))) return true;  // 右半自身为 0，或右半真子集与左半子集凑成 0（排除右半全选，否则另一侧为空）
        }  // 右半枚举结束
        return false;  // 所有组合都试过，不存在合法划分
    }  // 方法结束
};  // 类定义结束