// 题目：3804. 中心子数组的数量（Number of Centered Subarrays）
// 思路：枚举左端点并向右扩展，用集合记录子数组中出现的值、用变量累计元素和，若和恰好在集合中则计数。
// 时间复杂度：O(n^2)，双重循环枚举所有子数组；空间复杂度：O(n)，每个左端点用一个集合记录出现过的值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int centeredSubarrays(vector<int>& nums) {  // 统计满足「存在元素等于子数组和」的子数组个数
        int n = nums.size();  // 数组长度
        int ans = 0;  // 满足条件的子数组个数
        for (int i = 0; i < n; i++) {  // 枚举子数组左端点 i
            unordered_set<int> st;  // 记录当前子数组中出现过的元素
            int s = 0;  // 当前子数组的元素和
            for (int j = i; j < n; j++) {  // 枚举右端点 j，逐步把子数组向右扩展
                s += nums[j];  // 累加新元素到和
                st.insert(nums[j]);  // 把新元素加入集合
                if (st.count(s)) {  // 子数组和恰好是子数组里出现过的某个元素
                    ans++;  // 计数加一
                }  // 结束 if (st.count(s))
            }  // 结束 for (int j = i; j < n; j++)
        }  // 结束 for (int i = 0; i < n; i++)
        return ans;  // 返回答案
    }  // 结束 int centeredSubarrays(vector<int>& nums)
};  // 结束 class Solution
