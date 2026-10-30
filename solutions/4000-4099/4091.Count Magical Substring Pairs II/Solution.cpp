// 题目：4091. 统计神奇子字符串对 II（Count Magical Substring Pairs II）
// 思路：calc(s)[r][k] 表示以 r 结尾、不同字符数不超过 k 的后缀个数，用「不同字符数不超过 k」的滑动窗口配合 distinct 计数在 O(26n) 内求出；对 s 与反转后的 s 各算一次，left[j][k] - left[j][k-1] 就是「以 j 结尾且恰含 k 种字符」的左半子串数，右侧同理，按 k 相乘累加。
// 时间复杂度：O(26n)，26 次双指针滑窗再加上一次 26n 的合并；空间复杂度：O(26n)，即 f 数组的大小。
class Solution {  // LeetCode 约定的题解类
    vector<array<long long, 27>> calc(const string& s) {  // 辅助函数（默认私有）：返回 f[r][k] = 以 r 结尾、不同字符数不超过 k 的后缀个数
        int n = s.size();  // n 是字符串长度
        vector<array<long long, 27>> f(n);  // f[r][k] 存上述计数，第二维留 27 个位置以便用 k 直接下标
        for (int k = 1; k <= 26; k++) {  // 对每种允许的不同字符数上限 k 各做一次滑窗
            int cnt[26] = {};  // cnt[c]：窗口内字符 c 的出现次数
            int l = 0, distinct = 0;  // l 是窗口左边界，distinct 是窗口内的不同字符数
            for (int r = 0; r < n; r++) {  // 右端点 r 从左到右扫描
                if (cnt[s[r] - 'a']++ == 0) {  // 新字符第一次进入窗口（先自增计数，再用旧值判断是否为 0）
                    distinct++;  // 不同字符数加一
                }  // 右端点入窗完毕
                while (distinct > k) {  // 不同字符数超过上限，收缩左边界
                    if (--cnt[s[l++] - 'a'] == 0) {  // 左边界字符计数减一；减到 0 说明该字符彻底离开窗口
                        distinct--;  // 不同字符数减一
                    }  // 单个字符移出窗口的判断结束
                }  // 窗口重新满足「不同字符数 <= k」
                f[r][k] = r - l + 1LL;  // 以 r 结尾、满足上限的合法后缀共有 r-l+1 个
            }  // 右端点扫描结束
        }  // 所有 k 处理完毕
        return f;  // 返回二维计数表
    }  // calc 方法结束

public:  // 题解方法对外可见
    long long countMagicalPairs(string s) {  // s：待统计的字符串；返回神奇子字符串对的总数
        int n = s.size();  // n 是字符串长度
        auto left = calc(s);  // 原串上的计数表：left[j][k] 描述以 j 结尾、向左延伸的后缀
        reverse(s.begin(), s.end());  // 原地反转，接下来计算向右侧延伸的计数表
        auto right = calc(s);  // 反转串上的计数表，下标 r 对应原串从右往左的位置
        long long ans = 0;  // ans 累计答案，量级可达 n^2，用 long long
        for (int j = 0; j < n - 1; j++) {  // 枚举分界点 j：左半以 j 结尾，右半从 j+1 开始
            int r = n - 2 - j;  // 反转串中的下标：原串的 j+1 对应反转串的 n-2-j 结尾处
            for (int k = 1; k <= 26; k++) {  // 枚举两半共同的不同字符数 k
                ans += (left[j][k] - left[j][k - 1])  // 「以 j 结尾且恰含 k 种字符」的左半子串个数
                    * (right[r][k] - right[r][k - 1]);  // 乘以「以 j+1 开头且恰含 k 种字符」的右半子串个数
            }  // k 枚举结束
        }  // 分界点枚举结束
        return ans;  // 返回神奇子字符串对的总数
    }  // 方法结束
};  // 类定义结束