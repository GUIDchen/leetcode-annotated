// 题目：2090. 半径为 k 的子数组平均值（K Radius Subarray Averages）
// 思路：定长滑动窗口。窗口长度为 2k+1，逐元素累加；窗口填满后写入「以 i-k 为中心」的平均值，再把窗口最左元素移出，继续右滑。
// 时间复杂度：O(n)，每个元素进出窗口各一次；空间复杂度：O(n)，返回的答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getAverages(vector<int>& nums, int k) {  // nums：原数组；k：半径；返回每个中心位置的窗口平均值，半径不足处为 -1
        int n = nums.size();  // 数组长度
        vector<int> ans(n, -1);  // 答案数组，先全部填 -1：半径不足的位置保持 -1
        long long s = 0;  // 窗口内的元素和；用 long long 防止 2k+1 个元素相加溢出 int
        for (int i = 0; i < n; ++i) {  // i 既是右端点下标，也兼作已处理元素个数
            s += nums[i];  // 把当前元素加入窗口
            if (i >= k * 2) {  // 窗口长度已达到 2k+1，说明以 i-k 为中心的窗口已经完整
                ans[i - k] = s / (k * 2 + 1);  // 下标 i-k 的半径为 k 的窗口是 [i-2k, i]，写入其平均值（整数下取整）
                s -= nums[i - k * 2];  // 减去窗口最左元素，窗口整体右移一格，为下一次判断做准备
            }  // if 分支结束
        }  // for 循环结束
        return ans;  // 返回答案数组
    }  // 结束 getAverages 方法
};  // 结束 Solution 类
