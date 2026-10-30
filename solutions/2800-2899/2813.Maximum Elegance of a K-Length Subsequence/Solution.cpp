// 题目：2813. 子序列最大优雅度（Maximum Elegance of a K-Length Subsequence）
// 思路：按利润从大到小排序，先贪心取前 k 个得到总利润与类别数；再用后面利润较低但类别全新的元素，替换掉已选中重复类别里利润最小的元素，枚举所有提升类别数的机会取最大优雅度。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(k)，集合与栈最多各存 k 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long findMaximumElegance(vector<vector<int>>& items, int k) {  // items[i] = {利润, 类别}；k：子序列长度；返回最大优雅度
        sort(items.begin(), items.end(), [](const vector<int>& a, const vector<int>& b) {  // 按利润从大到小排序，先贪心取利润最高的 k 个
            return a[0] > b[0];  // 比较函数：利润大的排在前面
        });  // lambda 比较函数结束
        long long tot = 0;  // tot：当前选中元素的总利润
        unordered_set<int> vis;  // vis：当前选中元素涉及的所有类别（去重）
        stack<int> dup;  // dup：已选中元素里「类别重复」的利润，栈顶是其中最小的
        for (int i = 0; i < k; ++i) {  // 先取利润最高的 k 个作为初始方案
            int p = items[i][0], c = items[i][1];  // 取出利润与类别
            tot += p;  // 累加总利润
            if (vis.count(c)) {  // 该类别之前出现过，本次属于重复项
                dup.push(p);  // 记下这个重复项的利润，后面可能被替换掉
            } else {  // 类别第一次出现
                vis.insert(c);  // 加入类别集合，类别数加一
            }  // 分支结束
        }
        int n = items.size();  // 元素总个数
        long long ans = tot + 1LL * vis.size() * vis.size();  // 初始优雅度 = 总利润 + 类别数的平方
        for (int i = k; i < n; ++i) {  // 从第 k 个元素开始向后尝试替换，只可能让类别数增加
            int p = items[i][0], c = items[i][1];  // 候选元素的利润与类别
            if (vis.count(c) || dup.empty()) {  // 类别已存在，或没有可替换的重复项，本轮无法提升
                continue;  // 跳过这个候选，看下一个
            }  // if 结束
            vis.insert(c);  // 候选元素带来全新类别，加入集合
            tot += p - dup.top();  // 用它的利润换掉一个重复项的利润，总利润变化为 p - dup.top()
            dup.pop();  // 弹出这个重复项，保证之后不会被重复使用
            ans = max(ans, tot + (long long) (1LL * vis.size() * vis.size()));  // 更新答案：类别数已加一，重新计算类别数的平方
        }  // 替换循环结束
        return ans;  // 返回枚举过程中的最大优雅度
    }  // 方法结束
};  // 类定义结束