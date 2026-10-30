// 题目：2113. 查询删除和添加元素后的数组（Elements in Array After Removing and Replacing Elements）
// 思路：操作以 2n 分钟为一个周期：前 n 分钟不断删除首元素（数组左移），后 n 分钟不断在尾部补 0（前缀不变）。
// 时间复杂度：O(m)，m 为查询个数；空间复杂度：O(m)，只存答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> elementInNums(vector<int>& nums, vector<vector<int>>& queries) {  // nums：初始数组；queries 每项 [t, i] 表示第 t 分钟查询下标 i；返回所有查询答案
        int n = nums.size(), m = queries.size();  // n 是数组长度，m 是查询个数
        vector<int> ans(m, -1);  // 答案数组，查不到时保持默认值 -1
        for (int j = 0; j < m; ++j) {  // 逐个回答每个查询
            int t = queries[j][0], i = queries[j][1];  // t：查询时刻；i：要查询的下标
            t %= (n * 2);  // 操作以 2n 分钟为一个周期，先把 t 归约到一个周期内
            if (t < n && i < n - t) {  // 前 n 分钟每分钟删掉首元素：原数组整体左移 t 位，剩余长度 n-t
                ans[j] = nums[i + t];  // 下标 i 对应原数组的 i+t（剩下的正是原数组的后缀）
            } else if (t > n && i < t - n) {  // 后 n 分钟每分钟在尾部补 0：前缀保持原样，且已补了 t-n 个 0
                ans[j] = nums[i];  // i 落在原数组前缀内，值保持不变
            }  // 其余情况（已被删除或已变成 0）保持 -1
        }  // 查询处理完毕
        return ans;  // 返回全部查询结果
    }  // elementInNums 方法结束
};  // Solution 类定义结束