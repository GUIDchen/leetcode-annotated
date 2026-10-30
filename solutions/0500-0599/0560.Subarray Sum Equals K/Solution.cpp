// 题目：560. 和为 K 的子数组（Subarray Sum Equals K）
// 核心思路：用前缀和 + 哈希表计数，遍历到位置 i 时累加「前缀和等于 s-k 的次数」即答案。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，哈希表最多存 n 个前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subarraySum(vector<int>& nums, int k) {  // nums：整数数组（可为负）；k：目标和；返回和为 k 的连续子数组个数
        unordered_map<int, int> cnt{{0, 1}};  // 前缀和计数表，预先放入 {0:1} 表示空前缀，用于统计从下标 0 开始的子数组
        int ans = 0, s = 0;  // ans 统计答案个数，s 记录当前前缀和
        for (int x : nums) {  // 逐个元素遍历数组
            s += x;  // 累加得到以当前元素结尾的前缀和
            ans += cnt[s - k];  // 之前出现过 cnt 次前缀和 s-k，就对应 cnt 个和为 k 的子数组
            ++cnt[s];  // 把当前前缀和记入哈希表，供后面的元素查询
        }  // 遍历结束
        return ans;  // 返回和为 k 的子数组总数
    }  // 方法结束
};  // 类定义结束