// 题目：3255. 长度为 K 的子数组的能量值 II（Find the Power of K-Size Subarrays II）
// 思路：与 I 相同，用线性 DP 求以 i 结尾的「连续递增 1」的最长长度，再对每个长度为 k 的窗口 O(1) 判定并输出能量值，可承受更大的数据范围。
// 时间复杂度：O(n)，每个元素只处理常数次；空间复杂度：O(n)，用于存放 f 数组与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> resultsArray(vector<int>& nums, int k) {  // nums：输入数组；k：子数组长度；返回每个窗口的能量值
        int n = nums.size();  // n：数组长度
        int f[n];  // f[i]：以 i 结尾的「连续递增 1」的最大长度
        f[0] = 1;  // 只有单个元素时连续长度自然是 1
        for (int i = 1; i < n; ++i) {  // 从左到右递推每个位置
            f[i] = nums[i] == nums[i - 1] + 1 ? f[i - 1] + 1 : 1;  // 刚好比前一个数大 1 就延长，否则从 1 重新开始
        }
        vector<int> ans;  // ans：按窗口下标顺序保存答案
        for (int i = k - 1; i < n; ++i) {  // 窗口右端从 k-1 开始，共 n-k+1 个窗口
            ans.push_back(f[i] >= k ? nums[i] : -1);  // 连续长度够 k 时能量值就是右端元素，否则为 -1
        }
        return ans;  // 返回所有窗口的能量值
    }
};
