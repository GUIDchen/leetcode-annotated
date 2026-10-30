// 题目：2996. 大于等于顺序前缀和的最小缺失整数（Smallest Missing Integer Greater Than Sequential Prefix Sum）
// 核心思路：先沿 nums 求出最长的「连续递增且步长为 1」前缀之和 s，再用布尔存在性数组从小到大跳过已经出现过的数，第一个缺口就是答案。
// 时间复杂度：O(n)，两次线性扫描加一次值域内跳跃；空间复杂度：O(1)，值域固定为 51。
class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的解法接口
    int missingInteger(vector<int>& nums) {  // nums 是正整数数组，返回大于等于顺序前缀和的最小缺失整数
        int s = nums[0];  // 顺序前缀和至少包含第一个元素
        for (int j = 1; j < nums.size() && nums[j] == nums[j - 1] + 1; ++j) {  // 只要相邻两数连续（差为 1）就继续累加，遇到第一个断点立即停止
            s += nums[j];  // 把连续段里的下一个数并进前缀和
        }  // 最长顺序前缀之和计算完毕

        const int m = 51;  // 值域上界常量：nums[i] ≤ 50，所以查表只需 51 个槽位
        bool st[m] = {};  // 存在性数组，st[x] 表示数值 x 是否在 nums 中出现过
        for (int x : nums) {  // 遍历所有元素
            st[x] = true;  // 标记该数值出现过
        }  // 标记结束

        while (s < m && st[s]) {  // 从 s 开始找第一个没出现过的数；一旦越过值域上界就可以直接停下
            ++s;  // 该数已经出现，尝试下一个
        }  // 循环结束，s 就是答案
        return s;  // 返回大于等于顺序前缀和的最小缺失整数
    }  // 方法结束
};  // 类结束