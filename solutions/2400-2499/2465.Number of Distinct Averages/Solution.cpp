// 题目：2465. 不同的平均值数目（Number of Distinct Averages）
// 核心思路：排序后每次取最小值与最大值配对，用哈希集合统计这些配对的和；配对个数固定，和相同与平均值相同等价，用整数和可避免浮点误差。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，哈希集合最多存 n/2 个和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int distinctAverages(vector<int>& nums) {  // nums：输入数组；返回不同平均值的个数
        sort(nums.begin(), nums.end());  // 排序后最小值在最左、最大值在最右，便于首尾配对
        unordered_set<int> s;  // 哈希集合去重；保存两数之和而不是平均值，避免浮点误差
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n >> 1; ++i) {  // 共配对 n/2 次，n >> 1 等价于 n / 2
            s.insert(nums[i] + nums[n - i - 1]);  // 每次取当前最小值与最大值；每对的元素个数相同，故和相同即平均值相同
        }  // 结束配对循环
        return s.size();  // 集合大小就是不同和（即不同平均值）的个数
    }  // 结束 distinctAverages 方法
};  // 结束 Solution 类