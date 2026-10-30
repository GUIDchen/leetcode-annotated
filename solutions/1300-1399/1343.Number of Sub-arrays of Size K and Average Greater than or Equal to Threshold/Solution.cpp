// 题目：1343. 大小为 K 且平均值大于等于阈值的子数组数目（Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold）
// 思路：把「平均值 >= threshold」等价改写为「窗口和 >= threshold * k」，再用定长滑动窗口 O(1) 地更新每个窗口的和并计数。
// 时间复杂度：O(n)，只滑动一次窗口；空间复杂度：O(1)，仅用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {  // arr：原数组；k：子数组长度；threshold：平均值阈值
        threshold *= k;  // 两边同乘 k，把「平均值阈值」放大成「窗口和阈值」，避免浮点除法
        int s = accumulate(arr.begin(), arr.begin() + k, 0);  // 先累加前 k 个元素，得到第一个长度为 k 的窗口之和
        int ans = s >= threshold;  // 第一个窗口就达标则 ans 记为 1，否则为 0（bool 隐式转 int）
        for (int i = k; i < arr.size(); ++i) {  // 窗口右端从下标 k 开始右移，左端始终为 i-k
            s += arr[i] - arr[i - k];  // 定长滑动窗口的核心：加上新进入的 arr[i]，减去滑出的 arr[i-k]
            ans += s >= threshold;  // 当前窗口和达标就把计数加 1
        }  // 滑动循环结束
        return ans;  // 返回所有满足条件的窗口个数
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，逐字节保持不变）