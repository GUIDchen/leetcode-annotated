// 题目：1800. 最大升序子数组和（Maximum Ascending Subarray Sum）
// 思路：从左到右扫描，t 维护当前递增段的累加和，遇到不再递增就换段，全程用 ans 记录最大值。
// 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxAscendingSum(vector<int>& nums) {  // 返回数组中元素和最大的严格升序连续子数组的和
        int ans = 0, t = 0;  // ans 存最终答案；t 存当前正在累加的升序段和，均从 0 开始
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫描每个元素
            if (i == 0 || nums[i] > nums[i - 1]) {  // i == 0 或当前元素大于前一个：升序段可以继续延伸
                t += nums[i];  // 把当前元素并进当前升序段
                ans = max(ans, t);  // 随时刷新最大值
            } else {  // 否则升序被打断
                t = nums[i];  // 以当前元素为起点另起新的一段
            }
        }
        return ans;  // 返回最大升序子数组和
    }
};