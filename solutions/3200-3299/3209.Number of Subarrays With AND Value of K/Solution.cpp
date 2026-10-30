// 题目：3209. 子数组按位与值为 K 的数目（Number of Subarrays With AND Value of K）
// 思路：按位与越与越小，以 i 结尾的子数组只有 O(log U) 种不同结果，用哈希表保存「按位与值 → 个数」逐步滚动转移。
// 时间复杂度：O(n log U)，每个元素只与上一轮的少量不同值相与；空间复杂度：O(log U)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countSubarrays(vector<int>& nums, int k) {  // nums：输入数组；k：目标按位与值
        long long ans = 0;  // 答案最多可达 O(n^2) 个，用 long long 防止溢出
        unordered_map<int, int> pre;  // pre：以 i-1 结尾的子数组「按位与值 → 出现次数」
        for (int x : nums) {  // 枚举子数组的右端点
            unordered_map<int, int> cur;  // cur：以当前元素结尾的子数组统计结果
            for (auto& [y, v] : pre) {  // 结构化绑定遍历上一轮的每种按位与结果 y 与其个数 v
                cur[x & y] += v;  // 上一轮每种结果都与 x 相与，个数直接累加
            }
            cur[x]++;  // 只含 x 自身的长度 1 子数组
            ans += cur[k];  // 按位与恰为 k 的子数组个数计入答案
            pre = cur;  // 滚动：本轮结果作为下一轮的前缀集合
        }
        return ans;  // 返回满足条件的子数组总数
    }
};