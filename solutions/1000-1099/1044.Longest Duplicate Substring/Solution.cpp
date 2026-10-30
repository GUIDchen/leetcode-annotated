// 题目：1044. 最长重复子串（Longest Duplicate Substring）
// 思路：字符串哈希 + 二分答案；先用 base=131 递推出全部前缀哈希，再二分重复子串长度 mid，每轮用哈希表 O(n) 判断是否存在长度为 mid 的重复子串。
// 时间复杂度：O(n log n)，n 为串长，二分 log n 轮、每轮 O(n) 扫描；空间复杂度：O(n)，前缀哈希数组与去重集合。
typedef unsigned long long ULL;  // 无符号 64 位整数：哈希值溢出时按 2^64 自动取模

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    ULL p[30010];  // p[i] = base^i，按题目长度上限开数组，供区间哈希使用
    ULL h[30010];  // h[i] = 前缀 s[0..i-1] 的哈希值（下标从 1 开始）
    string longestDupSubstring(string s) {  // s：输入字符串；返回其中最长的重复子串
        int base = 131, n = s.size();  // base 取质数 131 以降低碰撞概率；n 为串长
        p[0] = 1;  // base^0 = 1，作为递推起点
        for (int i = 0; i < n; ++i) {  // 一遍递推即可求出所有幂次与前缀哈希
            p[i + 1] = p[i] * base;  // 逐项乘 base 得到 base^(i+1)
            h[i + 1] = h[i] * base + s[i];  // 秦九韶式前缀哈希：把新字符接到已有哈希末尾
        }  // 前缀哈希预处理结束
        int left = 0, right = n;  // 二分区间 [left, right]：答案长度一定落在 [0, n]
        string ans = "";  // 记录当前找到的最长重复子串
        while (left < right) {  // 二分最大的「存在重复」的子串长度
            int mid = (left + right + 1) >> 1;  // 上取整中点，保证 left 单调前进、循环能收敛
            string t = check(s, mid);  // 用哈希表判断长度 mid 是否存在重复子串
            if (t.empty())  // 返回空串说明不存在长度为 mid 的重复子串
                right = mid - 1;  // 长度太大，收缩上界
            else {  // 存在重复，说明可以继续尝试更长的长度
                left = mid;  // 答案至少是 mid，抬高左端点
                ans = t;  // 顺手记下这个可行的重复子串
            }  // 分支结束
        }  // 循环结束
        return ans;  // 二分结束时 ans 就是最长重复子串（无重复则为空串）
    }  // 最长重复子串方法结束

    string check(string& s, int len) {  // 判断是否存在长度为 len 的重复子串，存在则返回其中任意一个
        int n = s.size();  // 串长，用于限定扫描范围
        unordered_set<ULL> vis;  // 记录已经出现过的区间哈希值
        for (int i = 1; i + len - 1 <= n; ++i) {  // i 为区间左端点的 1 基下标，右端点不能超过 n
            int j = i + len - 1;  // j 为区间右端点的 1 基下标
            ULL t = h[j] - h[i - 1] * p[j - i + 1];  // 区间哈希：h[j] - h[i-1]*base^(j-i+1)，无符号溢出等价取模
            if (vis.count(t)) return s.substr(i - 1, len);  // 该哈希出现过，说明子串重复，直接返回这段子串
            vis.insert(t);  // 首次出现，放入集合供后续区间比对
        }  // 扫描结束
        return "";  // 全部扫描完都没有重复，返回空串表示该长度不可行
    }  // check 方法结束
};  // 题解类结束