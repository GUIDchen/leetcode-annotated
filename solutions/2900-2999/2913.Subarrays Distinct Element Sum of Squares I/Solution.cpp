// 题目：2913. 子数组不同元素数目的平方和 I（Subarrays Distinct Element Sum of Squares I）
// 思路：枚举子数组左端点，右端点逐步右移并维护窗口内不同元素个数，边扩边累加其平方。
// 时间复杂度：O(n^2)，枚举所有子数组；空间复杂度：O(V)，V 为值域（这里是 101 个计数桶）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumCounts(vector<int>& nums) {  // nums 是输入数组；返回所有子数组『不同元素个数的平方』之和
        int ans = 0;  // 累加答案
        int n = nums.size();  // 数组长度，后面反复用到
        for (int i = 0; i < n; ++i) {  // 枚举子数组的左端点 i
            int s[101]{};  // 计数桶：统计当前子数组里每个数值出现的次数（题目保证 1 <= nums[i] <= 100）
            int cnt = 0;  // cnt 记录当前子数组中不同元素的个数
            for (int j = i; j < n; ++j) {  // 枚举右端点 j，逐步把 nums[j] 加入窗口
                if (++s[nums[j]] == 1) {  // 先给 nums[j] 的计数加 1；加完恰好等于 1 说明它是窗口里新出现的不同元素
                    ++cnt;  // 不同元素个数加 1
                }
                ans += cnt * cnt;  // 把当前窗口不同元素个数的平方计入答案
            }
        }
        return ans;  // 返回所有子数组的平方和
    }
};