// 题目：1090. 受标签影响的最大值（Largest Values From Labels）
// 思路：把 (值, 标签) 按值从大到小排序后贪心选取，用哈希表记录每个标签已选次数，未超过 useLimit 就选，选满 numWanted 个立即停止。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，排序数组与标签计数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {  // values 与 labels 一一对应；numWanted 为最多选几个，useLimit 为每个标签最多选几次
        int n = values.size();  // 元素个数
        vector<pair<int, int>> pairs(n);  // 存 (值的相反数, 标签)：取负后默认升序排序就等于值降序
        for (int i = 0; i < n; ++i) {  // 逐个元素构造排序用的 pair
            pairs[i] = {-values[i], labels[i]};  // 取负号让 sort 升序等价于值降序；标签放在第二位用于打破平局
        }  // 结束构造循环
        sort(pairs.begin(), pairs.end());  // 按值与标签排序，值大的排在前面
        unordered_map<int, int> cnt;  // 哈希表：每个标签已经被选中的次数
        int ans = 0, num = 0;  // ans 累加所选值之和，num 记录已选元素个数
        for (int i = 0; i < n && num < numWanted; ++i) {  // 从大到小扫描，选满 numWanted 个就提前结束
            int v = -pairs[i].first, l = pairs[i].second;  // 还原真实的值与标签
            if (cnt[l] < useLimit) {  // 该标签的配额还没用完
                ++cnt[l];  // 该标签已选次数加一
                ++num;  // 已选个数加一
                ans += v;  // 把当前值累加到答案
            }  // 结束配额判断
        }  // 结束扫描
        return ans;  // 返回所选值之和的最大值
    }  // 结束方法体
};  // 类定义结束