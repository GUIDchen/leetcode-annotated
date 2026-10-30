// 题目：643. 子数组最大平均数 I（Maximum Average Subarray I）
// 核心思路：固定长度为 k 的滑动窗口，先算首个窗口和，之后每次加右端、减左端，途中记录最大窗口和。
// 时间复杂度：O(n)，窗口只扫一遍；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double findMaxAverage(vector<int>& nums, int k) {  // nums：输入数组；k：固定的窗口长度
        int s = accumulate(nums.begin(), nums.begin() + k, 0);  // 第一个长度为 k 的窗口和
        int ans = s;  // 记录窗口和的最大值
        for (int i = k; i < nums.size(); ++i) {  // 窗口每次右移一格
            s += nums[i] - nums[i - k];  // 加入新右端、去掉旧左端，O(1) 维护窗口和
            ans = max(ans, s);  // 更新最大窗口和
        }  // 滑动结束
        return static_cast<double>(ans) / k;  // 最大窗口和除以 k 就是最大平均数（转成浮点避免整除）
    }  // 方法结束
};  // 类结束