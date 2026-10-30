// 题目：2100. 适合野炊的日子（Find Good Days to Rob the Bank）
// 思路：先两遍递推求出每个位置向左、向右的「非递增连续天数」，再挑出左右两侧天数都不少于 time 的日子。
// 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，left 与 right 两个计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {  // security：每天安保人数；time：要求左右各连续非递增的天数
        int n = security.size();  // 总天数
        if (n <= time * 2) return {};  // 天数不足以在中间某天左右各留出 time 天，任何一天都不可能满足
        vector<int> left(n);  // left[i]：以 i 结尾、向左看有多少天满足非递增
        vector<int> right(n);  // right[i]：以 i 开头、向右看有多少天满足非递增
        for (int i = 1; i < n; ++i)  // 从左往右递推，算出每个位置的左侧天数
            if (security[i] <= security[i - 1])  // 今天人数不多于昨天，才能继续向左边延伸
                left[i] = left[i - 1] + 1;  // 在昨天的基础上加一，形成更长的非递增前缀
        for (int i = n - 2; i >= 0; --i)  // 从右往左递推，算出每个位置的右侧天数
            if (security[i] <= security[i + 1])  // 今天人数不多于明天，才能继续向右边延伸
                right[i] = right[i + 1] + 1;  // 在后一天的基础上加一，形成更长的非递增后缀
        vector<int> ans;  // 收集所有适合打劫（野炊）的日子
        for (int i = time; i < n - time; ++i)  // 合法日子必须左右各留出 time 天，所以区间是 [time, n-time)
            if (time <= min(left[i], right[i]))  // 左右两侧的非递增天数都不少于 time 才满足题意
                ans.push_back(i);  // 记录这一天
        return ans;  // 返回所有满足条件的日子
    }
};