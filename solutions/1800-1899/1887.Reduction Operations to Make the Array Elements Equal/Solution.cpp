// 题目：1887. 使数组元素相等的减少操作次数（Reduction Operations to Make the Array Elements Equal）
// 思路：升序排序后按值分层，cnt 记录当前元素需要降过的层数，每个元素都要降 cnt 次，累加即得总操作次数。
// 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(1)，只用了常数个额外变量（排序原地进行）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int reductionOperations(vector<int>& nums) {  // nums 是待统一的数组
        ranges::sort(nums);  // 升序排序，让相等元素相邻，便于分层统计
        int ans = 0, cnt = 0;  // ans 是总操作次数，cnt 是当前元素需要跨越的不同值层数
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，与前一个元素比较
            cnt += nums[i] != nums[i - 1];  // 出现更大的新值则层数加一，后面的元素要降更多次
            ans += cnt;  // 当前元素需要 cnt 次操作才能降到数组最小值
        }
        return ans;  // 返回所有元素降到最小值所需的总操作次数
    }
};
