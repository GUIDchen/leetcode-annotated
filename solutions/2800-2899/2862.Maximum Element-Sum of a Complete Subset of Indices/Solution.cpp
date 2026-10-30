// 题目：2862. 完全子集的最大元素和（Maximum Element-Sum of a Complete Subset of Indices）
// 思路：把下标按「去掉平方因子后的核心」分成 k·1²、k·2²、… 各组，同组任意两数之积是完全平方，枚举核心 k 求最大组和。
// 复杂度：时间 O(n·√n)，每个核心 k 只枚举到 √(n/k)；空间 O(1)，只用了累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumSum(vector<int>& nums) {  // nums：数组，元素 nums[i-1] 对应题目里的 1 下标 i
        long long ans = 0;  // 记录所有分组中的最大元素和
        int n = nums.size();  // 数组长度
        for (int k = 1; k <= n; ++k) {  // 枚举每个分组的核心 k（下标去掉平方因子后的基底）
            long long t = 0;  // 当前这一组的元素和
            for (int j = 1; k * j * j <= n; ++j) {  // 组内下标形如 k·j²，只要不超过 n 就继续累加
                t += nums[k * j * j - 1];  // 下标 k·j² 对应数组里的第 k·j²-1 个元素
            }
            ans = max(ans, t);  // 用当前组的和更新最大值
        }
        return ans;  // 返回最大元素和
    }
};