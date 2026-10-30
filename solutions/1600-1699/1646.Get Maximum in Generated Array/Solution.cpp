// 题目：1646. 获取生成数组中的最大值（Get Maximum in Generated Array）
// 思路：按题意递推，偶数下标取 nums[i/2]，奇数下标取 nums[i/2] + nums[i/2+1]，生成完整数组后取最大值。
// 时间复杂度：O(n)，线性生成加一次扫描；空间复杂度：O(n)，保存生成的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外开放
    int getMaximumGenerated(int n) {  // n：生成数组的下标上界，返回 nums[0..n] 中的最大值
        if (n < 2) {  // n 为 0 或 1 时递推式用不上，直接由定义给出答案
            return n;  // 返回 n 本身（nums[0]=0、nums[1]=1）
        }  // 边界处理结束
        int nums[n + 1];  // 生成数组，下标范围 0..n
        nums[0] = 0;  // 题目给定 nums[0] = 0
        nums[1] = 1;  // 题目给定 nums[1] = 1
        for (int i = 2; i <= n; ++i) {  // 从下标 2 开始按递推式生成
            nums[i] = i % 2 == 0 ? nums[i >> 1] : nums[i >> 1] + nums[(i >> 1) + 1];  // 偶数取 nums[i/2]，奇数取 nums[i/2] + nums[i/2+1]
        }  // 生成循环结束
        return *max_element(nums, nums + n + 1);  // 扫描整个数组取最大值
    }  // 方法结束
};  // 类定义结束