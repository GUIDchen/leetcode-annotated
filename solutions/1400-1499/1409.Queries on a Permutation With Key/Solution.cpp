// 题目：1409. 查询带键的排列（Queries on a Permutation With Key）
// 思路：用数组模拟排列，每次线性查找查询值的位置，把它删掉再插回队首。
// 时间复杂度：O(q * m)，q 为查询个数，每次查找与移位共 O(m)；空间复杂度：O(m)，保存排列与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> processQueries(vector<int>& queries, int m) {  // queries 是查询序列，m 是初始排列的长度；返回每次查询值所在的下标
        vector<int> p(m);  // 申请长度为 m 的数组，作为随查询不断变化的排列
        iota(p.begin(), p.end(), 1);  // 把 p 依次填成 1,2,...,m，得到初始排列
        vector<int> ans;  // 保存每次查询返回的下标
        for (int v : queries) {  // 按顺序处理每一个查询值 v
            int j = 0;  // j 用来记录 v 当前所在的位置，先给默认值 0
            for (int i = 0; i < m; ++i) {  // 在排列中从左到右线性查找 v
                if (p[i] == v) {  // 当前元素正好等于查询值
                    j = i;  // 记下 v 所在的下标 i
                    break;  // 位置已经确定，立即结束内层查找
                }  // 结束命中判断
            }  // 结束内层查找循环
            ans.push_back(j);  // 把本次查询的下标计入答案
            p.erase(p.begin() + j);  // 先删掉原位置的 v，它后面的元素整体前移一位
            p.insert(p.begin(), v);  // 再把 v 插到排列最前面，其余元素整体后移一位
        }  // 结束外层查询循环
        return ans;  // 返回全部查询的结果序列
    }  // 结束题解方法
};  // 结束题解类