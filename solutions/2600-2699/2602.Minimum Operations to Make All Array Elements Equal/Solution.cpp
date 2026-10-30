// 题目：2602. 使数组元素全部相等的最少操作次数（Minimum Operations to Make All Array Elements Equal）
// 思路：排序后做前缀和，对每个查询 x 二分出「小于 x」与「大于 x」的分界，用前缀和 O(1) 累加两侧的调整量。
// 时间复杂度：O(n log n + q log n)，排序加每个查询两次二分；空间复杂度：O(n)，前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {  // nums：待统一的数组；queries：每次的目标值；返回每个查询的最少操作次数
        sort(nums.begin(), nums.end());  // 排序后才能用前缀和 + 二分，把单个查询压到 O(log n)
        int n = nums.size();  // 数组长度
        vector<long long> s(n + 1);  // 前缀和 s：s[i] 表示 nums 前 i 个元素之和，用 long long 防溢出
        for (int i = 0; i < n; ++i) {  // 逐个元素累加，构造前缀和
            s[i + 1] = s[i] + nums[i];  // 前 i 项和加上当前元素，得到前 i+1 项和
        }
        vector<long long> ans;  // 存放每个查询的答案
        for (auto& x : queries) {  // 依次处理每个查询目标值 x
            int i = lower_bound(nums.begin(), nums.end(), x + 1) - nums.begin();  // 第一个大于 x 的下标 i：区间 [i, n) 的元素都需要减到 x
            long long t = s[n] - s[i] - 1LL * (n - i) * x;  // 大于 x 的部分：后半段原和减去它们降到 x 后的和
            i = lower_bound(nums.begin(), nums.end(), x) - nums.begin();  // 第一个大于等于 x 的下标 i：区间 [0, i) 的元素都需要增到 x
            t += 1LL * x * i - s[i];  // 小于 x 的部分：这 i 个元素升到 x 后的和减去它们原来的和
            ans.push_back(t);  // 两侧调整次数相加即为该查询的答案
        }
        return ans;  // 返回全部查询的结果
    }
};