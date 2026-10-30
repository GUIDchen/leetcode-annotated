// 题目：1031. 两个无重叠子数组的最大和（Maximum Sum of Two Non-Overlapping Subarrays）
// 思路：前缀和 O(1) 取任意窗口和；分别枚举「firstLen 在前」与「secondLen 在前」，用滚动最大值 t 记录左侧最佳窗口。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {  // 求长度分别为 firstLen、secondLen 的两个不重叠子数组的最大元素和
        int n = nums.size();  // 数组长度
        vector<int> s(n + 1);  // 前缀和数组：s[k] 表示 nums 前 k 个元素之和
        for (int i = 0; i < n; ++i) {  // 一次遍历构造前缀和
            s[i + 1] = s[i] + nums[i];  // 递推式：前 i+1 个元素之和 = 前 i 个之和 + nums[i]
        }  // 前缀和构造完毕
        int ans = 0;  // 记录全局最大和
        for (int i = firstLen, t = 0; i + secondLen - 1 < n; ++i) {  // 情况一：firstLen 子数组在前（右端点为 i-1），secondLen 子数组从 i 开始
            t = max(t, s[i] - s[i - firstLen]);  // t 维护已扫过的 firstLen 窗口的最大和
            ans = max(ans, t + s[i + secondLen] - s[i]);  // 用左侧最大窗口 + 右侧当前窗口更新答案
        }  // 情况一枚举结束
        for (int i = secondLen, t = 0; i + firstLen - 1 < n; ++i) {  // 情况二：secondLen 子数组在前，firstLen 子数组在后（两种前后顺序都要试）
            t = max(t, s[i] - s[i - secondLen]);  // t 维护已扫过的 secondLen 窗口的最大和
            ans = max(ans, t + s[i + firstLen] - s[i]);  // 用左侧最大窗口 + 右侧当前窗口更新答案
        }  // 情况二枚举结束
        return ans;  // 返回两种顺序中的最大值
    }  // 方法结束
};  // 类定义结束