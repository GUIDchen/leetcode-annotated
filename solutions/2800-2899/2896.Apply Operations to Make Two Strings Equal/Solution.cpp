// 题目：2896. 执行操作使两个字符串相等（Apply Operations to Make Two Strings Equal）
// 思路：先记下两个字符串所有不同的位置；区间 DP 枚举一次翻转两端（代价 x）、或成对消掉左侧/右侧相邻两个位置（代价为下标差），取最小值。
// 时间复杂度：O(m^2)，m 为不同位置个数，每个区间只算一次；空间复杂度：O(m^2)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(string s1, string s2, int x) {  // s1、s2：两个等长字符串；x：一次操作同时翻转两个不同位置的代价
        vector<int> idx;  // idx：记录所有 s1 与 s2 不相同的下标
        for (int i = 0; i < s1.size(); ++i) {  // 逐位比较两个字符串
            if (s1[i] != s2[i]) {  // 该位不相等，说明这个位置需要被操作奇数次
                idx.push_back(i);  // 把这个位置记下来
            }
        }  // m：不同位置的总数
        int m = idx.size();  // 不同位置为奇数个，每次操作只能消掉 2 个
        if (m & 1) {  // 不可能全部消掉，无解
            return -1;
        }  // 两个字符串本来就相同
        if (m == 0) {  // 不需要任何操作
            return 0;
        }  // 记忆化数组：f[i][j] 表示消掉 idx[i..j] 这段的最小代价
        int f[m][m];  // 初始化为 -1，表示该状态尚未计算
        memset(f, -1, sizeof(f));  // dfs(i, j)：递归处理不同位置列表的区间 [i, j]
        function<int(int, int)> dfs = [&](int i, int j) {  // 区间为空，说明这段已全部消完
            if (i > j) {  // 不需要代价
                return 0;
            }  // 该状态之前算过
            if (f[i][j] != -1) {  // 直接返回记忆化结果
                return f[i][j];
            }  // 三种消去方案取最小：同时翻两端、从左端成对消、从右端成对消
            f[i][j] = min({dfs(i + 1, j - 1) + x, dfs(i + 2, j) + idx[i + 1] - idx[i], dfs(i, j - 2) + idx[j] - idx[j - 1]});  // 返回并写入记忆化表
            return f[i][j];
        };  // 从整个区间开始求解
        return dfs(0, m - 1);
    }
};