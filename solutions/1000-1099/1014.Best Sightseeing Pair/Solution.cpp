// 题目：1014. 最佳观光组合（Best Sightseeing Pair）
// 思路：把得分拆成 (values[i] + i) + (values[j] - j)，边遍历边维护左半部分的最大值，就能在线求最大得分。
// 时间复杂度：O(n)，一趟扫描；空间复杂度：O(1)，只用两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxScoreSightseeingPair(vector<int>& values) {  // values：每个景点的评分
        int ans = 0, mx = 0;  // ans 目前的最优得分，mx 之前所有位置中 values[i] + i 的最大值
        for (int j = 0; j < values.size(); ++j) {  // 枚举作为右端点的景点下标 j
            ans = max(ans, mx + values[j] - j);  // 用此前最优的左端点与当前右端点配对：mx 已含 +i，这里再补上 values[j] - j，更新答案
            mx = max(mx, values[j] + j);  // 把当前景点也纳入左端点候选 values[j] + j，供后面的 j 使用
        }
        return ans;  // 返回最大观光组合得分
    }
};
