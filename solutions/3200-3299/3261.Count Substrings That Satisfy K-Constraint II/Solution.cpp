// 题目：3261. 统计满足 K 约束的子字符串数量 II（Count Substrings That Satisfy K-Constraint II）
// 思路：先滑动窗口预处理。d[i] 记录以 i 为左端点时第一个使其不合法的右端点，pre 记录每个右端点对应合法起点数的前缀和；查询 [l, r] 时用 d[l] 定位分界点 p，起点恰为 l 的部分用等差数列求和，起点更大的部分用前缀和相减，两段相加即得答案。
// 时间复杂度：O(n + q)，预处理 O(n) 且每个查询 O(1)；空间复杂度：O(n)，d 与 pre 各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {  // s 只含 '0'/'1'，k 为每种字符个数上限，queries 为一组 [l, r]；返回每个查询的答案
        int cnt[2]{};  // cnt[0]、cnt[1] 统计当前窗口内 '0' 与 '1' 的个数
        int n = s.size();  // n 为字符串长度
        vector<int> d(n, n);  // d[i] 记录以 i 为左端点时第一个使窗口不合法的右端点，始终合法则保持 n
        long long pre[n + 1];  // pre[j+1] 表示前 j+1 个右端点各自合法起点数之和（前缀和）
        pre[0] = 0;  // 前缀和下标 0 处为 0
        for (int i = 0, j = 0; j < n; ++j) {  // i 为窗口左端点、j 为右端点，右端点依次向右扩张
            cnt[s[j] - '0']++;  // 把 s[j] 计入对应字符的计数
            while (cnt[0] > k && cnt[1] > k) {  // 两种字符同时超过 k，窗口不合法，需要收缩左端点
                d[i] = j;  // 记录左端点 i 第一次不合法的右端点 j
                cnt[s[i++] - '0']--;  // 左端字符移出窗口，i 右移一位
            }  // 收缩到窗口重新合法为止
            pre[j + 1] = pre[j] + j - i + 1;  // 以 j 结尾的合法起点共 j-i+1 个，累加进前缀和
        }  // 右端点遍历结束
        vector<long long> ans;  // ans 存放每个查询的答案
        for (const auto& q : queries) {  // 逐个处理查询区间 [l, r]
            int l = q[0], r = q[1];  // 取出该查询的左右端点
            int p = min(r + 1, d[l]);  // p 是区间内第一个非法右端点，同时不超过 r+1
            long long a = (1LL + p - l) * (p - l) / 2;  // 起点恰为 l 的部分：合法终点可取 l..p-1，共 1+2+...+(p-l) 个
            long long b = pre[r + 1] - pre[p];  // 起点大于 l 的部分：直接由前缀和相减得到
            ans.push_back(a + b);  // 两部分相加即为该查询的答案
        }  // 查询处理结束
        return ans;  // 按查询顺序返回答案
    }  // 方法结束
};  // 类定义结束
