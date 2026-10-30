// 题目：219. 存在重复元素 II（Contains Duplicate II）
// 核心思路：哈希表记录每个值最近一次出现的下标，扫描时比较当前下标与最近下标的差是否不超过 k。
// 时间复杂度：O(n)，每个元素只查表一次；空间复杂度：O(n)，哈希表最多存 n 个不同值。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    bool containsNearbyDuplicate(vector<int>& nums, int k) {  // 判断是否存在两个相等元素，其下标差不超过 k
        unordered_map<int, int> d;  // 哈希表：记录每个值最近一次出现的下标
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫描每个元素
            if (d.count(nums[i]) && i - d[nums[i]] <= k) {  // 该值以前出现过，且与最近一次出现的下标差不超过 k
                return true;  // 找到满足条件的重复对
            }  // if 结束
            d[nums[i]] = i;  // 更新为最新下标，使后续判断拿到最小的下标差
        }  // 循环结束
        return false;  // 扫描完仍未找到
    }  // 方法结束
};  // 类定义结束