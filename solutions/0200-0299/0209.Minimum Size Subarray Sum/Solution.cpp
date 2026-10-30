// 题目：209. 长度最小的子数组（Minimum Size Subarray Sum）
// 思路：前缀和 + 二分。对每个左端点 i，二分找到第一个满足 s[j] - s[i] >= target 的 j，用 j - i 更新答案。
// 时间复杂度：O(n log n)，n 次二分每次 O(log n)；空间复杂度：O(n)，前缀和数组长度为 n + 1。
class Solution {  // LeetCode 约定的题解类
public:  // 解题接口对外可见
    int minSubArrayLen(int target, vector<int>& nums) {  // target 是目标和，nums 是正整数数组
        int n = nums.size();  // 数组长度
        vector<long long> s(n + 1);  // 前缀和数组：s[i] = nums[0] + ... + nums[i-1]，约定 s[0] = 0
        for (int i = 0; i < n; ++i) {  // 从左到右递推求前缀和
            s[i + 1] = s[i] + nums[i];  // 前 i+1 项之和等于前 i 项之和再加上当前元素
        }  // 前缀和构造完成
        int ans = n + 1;  // 答案先设为不可能取到的 n + 1，方便后面取 min
        for (int i = 0; i <= n; ++i) {  // 枚举子数组左端点对应的前缀和下标 i
            int j = lower_bound(s.begin(), s.end(), s[i] + target) - s.begin();  // 二分查找第一个使 s[j] - s[i] >= target 的下标 j（减去首迭代器得到下标）
            if (j <= n) {  // 找到的 j 没有越界，说明存在满足条件的右端点
                ans = min(ans, j - i);  // 用当前子数组长度 j - i 更新最小长度
            }  // if 分支结束
        }  // 左端点枚举结束
        return ans <= n ? ans : 0;  // 答案始终没被更新过说明不存在这样的子数组，按题意返回 0
    }  // 方法结束
};  // 类定义结束（源文件末尾没有换行符，此处保持原样）