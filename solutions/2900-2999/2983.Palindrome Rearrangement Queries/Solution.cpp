// 题目：2983. 回文串重新排列查询（Palindrome Rearrangement Queries）
// 核心思路：把右半段翻转后与左半段逐位对齐，用两套 26 字母前缀和与「不匹配前缀个数」diff，把每个查询按区间包含/分离/相交三种情况在 O(1) 内判定。
// 时间复杂度：O((n + q) · 26)，建表 O(26n) 后每次查询常数次前缀差；空间复杂度：O(26n)，两套前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的解法接口
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {  // s 为偶数长度字符串，每个查询给出两段可任意重排的区间，返回能否通过重排使 s 变成回文
        int n = s.length();  // 原串长度，用于把右半段的查询下标映射到翻转后的坐标
        int m = n / 2;  // 一半长度：左半段与「右半段翻转」逐位对齐比较
        string t = string(s.begin() + m, s.end());  // t 先取出右半段
        reverse(t.begin(), t.end());  // 翻转 t，使 t[i] 与 s[i] 成为一对镜像字符
        s = string(s.begin(), s.begin() + m);  // s 只保留左半段，后续所有比较都在长度 m 的坐标上进行

        vector<vector<int>> pre1(m + 1, vector<int>(26));  // pre1[i]：左半段前 i 个字符的字母频次前缀和
        vector<vector<int>> pre2(m + 1, vector<int>(26));  // pre2[i]：翻转后的右半段前 i 个字符的字母频次前缀和
        vector<int> diff(m + 1, 0);  // diff[i]：前 i 个位置上 s 与 t 不相等的个数
        for (int i = 1; i <= m; ++i) {  // 逐位建立前缀结构
            pre1[i] = pre1[i - 1];  // 先继承前一项的字母频次
            pre2[i] = pre2[i - 1];  // 右半段同样继承前一项的字母频次
            ++pre1[i][s[i - 1] - 'a'];  // 把位置 i-1 的左半段字符计入频次
            ++pre2[i][t[i - 1] - 'a'];  // 把位置 i-1 的（翻转后）右半段字符计入频次
            diff[i] = diff[i - 1] + (s[i - 1] == t[i - 1] ? 0 : 1);  // 该位置两半字符不相等时，不匹配前缀数加一
        }  // 前缀结构建立完毕

        vector<bool> ans(queries.size(), false);  // 提前分配每个查询的答案，默认 false
        for (int i = 0; i < queries.size(); ++i) {  // 逐个查询处理
            vector<int> q = queries[i];  // 取出当前查询的四元组 [a, b, c, d]
            int a = q[0], b = q[1];  // q[0], q[1] 是左半段可重排的区间 [a, b]
            int c = n - 1 - q[3], d = n - 1 - q[2];  // 把右半段区间映射到翻转坐标：原下标 x 对应 n-1-x
            ans[i] = (a <= c) ? check(pre1, pre2, diff, a, b, c, d) : check(pre2, pre1, diff, c, d, a, b);  // 让左区间起点更靠前；若 a > c 就交换两侧视角，check 内的逻辑是对称的
        }  // 查询处理结束
        return ans;  // 返回每个查询的可行性结论
    }  // 方法结束

private:  // 以下为内部辅助函数
    bool check(const vector<vector<int>>& pre1, const vector<vector<int>>& pre2, const vector<int>& diff, int a, int b, int c, int d) {  // 判断两侧区间 [a, b] 与 [c, d] 重排后能否逐位相等（调用前已保证 a <= c）
        if (diff[a] > 0 || diff[diff.size() - 1] - diff[max(b, d) + 1] > 0) {  // 区间之外的前缀 [0, a) 与后缀 (max(b, d), m) 无法被本次重排改动，必须本来就匹配
            return false;  // 存在补不回来的不匹配位置，直接判失败
        }  // 否则继续按两区间的位置关系分类讨论

        if (d <= b) {  // 情况一：右区间被左区间完全包含
            return count(pre1, a, b) == count(pre2, a, b);  // 只需 [a, b] 上两半的字母多重集相同，重排即可让它们逐位相等
        }  // 否则两区间必然重叠或分离

        if (b < c) {  // 情况二：两区间完全不重叠，中间还有空档
            return diff[c] - diff[b + 1] == 0 && count(pre1, a, b) == count(pre2, a, b) && count(pre1, c, d) == count(pre2, c, d);  // 空档 [b+1, c) 必须已匹配，且两段各自的多重集相同，才能分别内部重排成相等
        }  // 否则两区间只有部分重叠

        vector<int> cnt1 = sub(count(pre1, a, b), count(pre2, a, c - 1));  // 左段独有部分的需求：左半段 [a, b] 的字母数减去右段已覆盖的 [a, c-1]
        vector<int> cnt2 = sub(count(pre2, c, d), count(pre1, b + 1, d));  // 右段独有部分的需求：右半段 [c, d] 的字母数减去左段已覆盖的 [b+1, d]

        return cnt1 != vector<int>() && cnt2 != vector<int>() && cnt1 == cnt2;  // 两侧都不能出现负数（否则说明字符不够用），且剩余需求向量必须完全一致
    }  // check 结束

    vector<int> count(const vector<vector<int>>& pre, int i, int j) {  // 借助前缀和取出闭区间 [i, j] 的 26 个字母频次
        vector<int> cnt(26);  // 存放结果的频次数组
        for (int k = 0; k < 26; ++k) {  // 对每个字母做一次前缀差
            cnt[k] = pre[j + 1][k] - pre[i][k];  // 前缀和要右移一位再相减
        }  // 频次统计结束
        return cnt;  // 返回区间频次
    }  // count 结束

    vector<int> sub(const vector<int>& cnt1, const vector<int>& cnt2) {  // 逐字母作差；任何一位为负说明字符不足，返回空 vector 作为失败标记
        vector<int> cnt(26);  // 存放差值的数组
        for (int i = 0; i < 26; ++i) {  // 遍历 26 个字母
            cnt[i] = cnt1[i] - cnt2[i];  // 计算该字母的剩余需求
            if (cnt[i] < 0) {  // 需求为负，说明这种字母数量不够
                return vector<int>();  // 返回空 vector 表示不可行
            }  // 否则继续检查下一个字母
        }  // 所有字母的需求都非负
        return cnt;  // 返回剩余需求向量
    }  // sub 结束
};  // 类结束