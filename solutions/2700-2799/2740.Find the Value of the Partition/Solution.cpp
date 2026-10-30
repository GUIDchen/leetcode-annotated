// 题目：2740. 找出分区值（Find the Value of the Partition）
// 核心思路：排序后最优划分一定切在相邻两个元素之间，答案是相邻元素差的最小值。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序递归栈的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findValueOfPartition(vector<int>& nums) {  // nums：待划分的正整数数组
        sort(nums.begin(), nums.end());  // 升序排序，让数值相近的元素靠在一起
        int ans = 1 << 30;  // 初始化为足够大的值（2^30），保证第一次取 min 时会被替换
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，考察每一对相邻元素
            ans = min(ans, nums[i] - nums[i - 1]);  // 用当前相邻差更新最小差
        }
        return ans;  // 最小相邻差就是最优分区值
    }
};