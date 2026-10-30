// 题目：364. 嵌套列表加权和 II（Nested List Weight Sum II）
// 思路：DFS 同时求最大深度 maxDepth、元素总和 s 与按真实深度加权的和 ws，答案 = (maxDepth+1)*s - ws 即按反深度加权。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归深度 h。
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {  // LeetCode 题解类
public:  // 对外接口
    int depthSumInverse(vector<NestedInteger>& nestedList) {  // nestedList 是嵌套列表的根层元素集合
        int maxDepth = 0, ws = 0, s = 0;  // maxDepth 最大深度；ws 深度加权和；s 元素总和
        function<void(NestedInteger&, int)> dfs = [&](NestedInteger& x, int d) {  // 递归函数：x 是当前节点，d 是当前深度（根为 1）
            maxDepth = max(maxDepth, d);  // 维护遍历到的最大深度
            if (x.isInteger()) {  // 是单个整数则直接累加
                ws += x.getInteger() * d;  // 按「当前深度」加权计入 ws
                s += x.getInteger();  // 同时累加原始值到 s
            } else {  // 否则是嵌套列表
                for (auto& y : x.getList()) {  // 递归处理每个子元素
                    dfs(y, d + 1);  // 子元素深度加一
                }  // 子元素循环结束
            }  // 分支结束
        };  // lambda 定义结束
        for (auto& x : nestedList) {  // 遍历根层的每个元素
            dfs(x, 1);  // 根层深度为 1，开始 DFS
        }  // 根层循环结束
        return (maxDepth + 1) * s - ws;  // 反深度权 = (maxDepth+1-d)，展开后即 (maxDepth+1)*s - ws
    }  // 方法结束
};  // 题解类结束