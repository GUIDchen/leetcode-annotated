// 题目：561. 数组拆分（Array Partition）
// 思路：升序排序后按相邻两个元素分组，每组取较小者（下标 0、2、4…）累加；这样每对的最小值之和最大。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(log n)，排序递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int arrayPairSum(vector<int>& nums) {  // nums 是待配对的整数数组，返回每对较小值之和的最大值
        sort(nums.begin(), nums.end());  // 原地升序排序：相邻两数配对能让每组较小值尽量大
        int ans = 0;  // ans 累计每一对中较小元素的和
        for (int i = 0; i < nums.size(); i += 2) {  // 排序后每两个数为一组，i 每次前进 2，nums[i] 就是该组较小值
            ans += nums[i];  // 把本组较小值累加进答案
        }  // 分组遍历结束
        return ans;  // 返回所有配对较小值之和
    }
};