// 题目：2055. 蜡烛之间的盘子（Plates Between Candles）
// 思路：预处理盘子数量的前缀和，以及每个位置左右最近的蜡烛下标；对每个查询取区间内左右两根蜡烛，用前缀和差值统计中间的盘子。
// 时间复杂度：O(n + q)，n 为字符串长度、q 为查询数；空间复杂度：O(n)，前缀和与左右蜡烛下标数组。
class Solution {  // 题解类
public:  // 对外接口
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {  // s 是蜡烛/盘子串，queries 是一组区间，返回每个区间中两根蜡烛之间的盘子数
        int n = s.size();  // 串长
        vector<int> presum(n + 1);  // presum[i] 表示前 i 个字符中盘子的个数
        for (int i = 0; i < n; ++i) presum[i + 1] = presum[i] + (s[i] == '*');  // 统计盘子的前缀和；字符比较结果是 bool，可直接当 0/1 用
        vector<int> left(n);  // left[i] 表示 i 及其左侧最近的蜡烛下标
        vector<int> right(n);  // right[i] 表示 i 及其右侧最近的蜡烛下标
        for (int i = 0, l = -1; i < n; ++i) {  // 从左往右扫，l 是最近蜡烛位置（-1 表示还没有）
            if (s[i] == '|') l = i;  // 遇到蜡烛就更新最近位置
            left[i] = l;  // 记下 i 左侧最近的蜡烛
        }  // 左扫描结束
        for (int i = n - 1, r = -1; i >= 0; --i) {  // 从右往左扫，r 是最近蜡烛位置（-1 表示还没有）
            if (s[i] == '|') r = i;  // 遇到蜡烛就更新最近位置
            right[i] = r;  // 记下 i 右侧最近的蜡烛
        }  // 右扫描结束
        vector<int> ans(queries.size());  // 每个查询的答案
        for (int k = 0; k < queries.size(); ++k) {  // 逐个处理查询
            int i = right[queries[k][0]];  // 区间左端右侧第一根蜡烛，作为区间内的左蜡烛
            int j = left[queries[k][1]];  // 区间右端左侧第一根蜡烛，作为区间内的右蜡烛
            if (i >= 0 && j >= 0 && i < j) ans[k] = presum[j] - presum[i + 1];  // 两根蜡烛都在区间内且左在右之前，前缀和差值即中间的盘子数
        }  // 查询处理结束
        return ans;  // 返回全部答案
    }  // 方法结束
};  // 类定义结束