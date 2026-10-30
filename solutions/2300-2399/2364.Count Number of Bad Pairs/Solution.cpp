// 题目：2364. 统计坏数对的数目（Count Number of Bad Pairs）
// 思路：好数对满足 nums[j] - nums[i] == j - i，等价于 i - nums[i] == j - nums[j]；用哈希表统计每个差值的历史出现次数，第 i 个位置的坏对数 = i - 同差值的历史个数。
// 时间复杂度：O(n)，每次哈希操作均摊 O(1)；空间复杂度：O(n)，哈希表最多存 n 个不同的差值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countBadPairs(vector<int>& nums) {  // nums 是输入数组，返回坏数对总数
        unordered_map<int, int> cnt;  // 哈希表：键是差值 i - nums[i]，值是它在此之前出现的次数
        long long ans = 0;  // 坏数对总数，最坏约为 n^2/2，用 64 位整数防止溢出
        for (int i = 0; i < nums.size(); ++i) {  // 顺次枚举每个位置作为数对的右端点
            int x = i - nums[i];  // 当前下标与元素的差值，作为分组的键
            ans += i - cnt[x]++;  // 以 i 结尾的数对共 i 个，减去同键的好数对个数即坏数对；后置自增把本次计入
        }
        return ans;  // 返回累加得到的坏数对总数
    }
};