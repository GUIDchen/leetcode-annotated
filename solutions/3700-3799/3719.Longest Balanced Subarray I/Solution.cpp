// 题目：3719. 最长平衡子数组 I（Longest Balanced Subarray I）
// 思路：枚举左端点并向右扩展，用集合记录出现过的值，分别累计不同偶数与不同奇数的个数；两者相等时子数组平衡，更新最长长度。
// 时间复杂度：O(n²)，空间复杂度：O(n)，每个左端点需要一个去重集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestBalanced(vector<int>& nums) {  // nums：整数数组；返回最长平衡子数组的长度
        int n = nums.size();  // 数组长度
        int ans = 0;  // 记录最长平衡子数组长度
        for (int i = 0; i < n; ++i) {  // 枚举子数组左端点
            unordered_set<int> vis;  // 当前子数组中已经出现过的值
            int cnt[2]{};  // cnt[0]：不同偶数的个数；cnt[1]：不同奇数的个数
            for (int j = i; j < n; ++j) {  // 枚举子数组右端点
                if (!vis.contains(nums[j])) {  // 该值在当前子数组中首次出现
                    vis.insert(nums[j]);  // 标记为已出现
                    ++cnt[nums[j] & 1];  // 按奇偶性给对应种类的不同值个数加一
                }  // 首次出现处理结束
                if (cnt[0] == cnt[1]) {  // 不同偶数与不同奇数个数相等即为平衡
                    ans = max(ans, j - i + 1);  // 更新最长长度
                }  // 平衡判断结束
            }  // 右端点枚举结束
        }  // 左端点枚举结束
        return ans;  // 返回最长平衡子数组长度
    }  // 方法结束
};  // 类定义结束
