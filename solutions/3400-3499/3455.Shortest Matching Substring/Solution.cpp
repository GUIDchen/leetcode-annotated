// 3455. 最短匹配子字符串 / Shortest Matching Substring
// 核心思路：用 KMP 分别求出三段模式串在 s 中所有出现位置，再用两个指针做单调递增的贪心匹配，取最短的覆盖区间。
// 复杂度：时间复杂度 O(|s| + |p|)，空间复杂度 O(|s|)。
class Solution {  // 题解类
public:  // 公有接口
    int shortestMatchingSubstring(string s, string p) {  // 求 s 中最短的匹配 p 的子串长度
        int star = p.find('*');  // 第一个 '*' 的位置
        int star2 = p.find('*', star + 1);  // 第二个 '*' 的位置
        string a = p.substr(0, star);  // 第一段：第一个 '*' 之前的模式串
        string b = p.substr(star + 1, star2 - star - 1);  // 第二段：两个 '*' 之间的模式串
        string c = p.substr(star2 + 1);  // 第三段：第二个 '*' 之后的模式串
        vector<int> A = starts(s, a), B = starts(s, b), C = starts(s, c);  // 三段的全部出现位置，均升序
        int ans = s.size() + 1;  // 答案初值取一个不可能达到的长度
        int j = 0, k = 0;  // j、k 分别指向 B、C 中待考察的位置，随 i 增大单调右移
        for (int i : A) {  // 枚举第一段的每一个出现位置
            while (j < (int) B.size() && B[j] < i + (int) a.size()) {  // 第二段必须严格排在 a 之后
                ++j;  // 不满足就继续右移
            }  // 结束第二段调整
            if (j == (int) B.size()) {  // 第二段已经没有可用的位置
                break;  // 后面的 i 更大，更不可能匹配，直接结束
            }  // 结束第二段检查
            while (k < (int) C.size() && C[k] < B[j] + (int) b.size()) {  // 第三段必须严格排在 b 之后
                ++k;  // 不满足就继续右移
            }  // 结束第三段调整
            if (k == (int) C.size()) {  // 第三段已经没有可用的位置
                break;  // 后面的 i 更大，更不可能匹配，直接结束
            }  // 结束第三段检查
            ans = min(ans, C[k] + (int) c.size() - i);  // 区间右端减左端，得到当前匹配长度
        }  // 结束枚举
        return ans > (int) s.size() ? -1 : ans;  // 没有找到合法匹配则返回 -1
    }  // 结束 shortestMatchingSubstring

private:  // 私有辅助函数
    vector<int> starts(const string& s, const string& pat) {  // 用 KMP 求 pat 在 s 中所有出现的起始下标
        int n = s.size();  // 主串长度
        if (pat.empty()) {  // 空模式串可以匹配任意位置
            vector<int> res(n + 1);  // 共 n+1 个可匹配位置
            iota(res.begin(), res.end(), 0);  // 依次填入 0 到 n
            return res;  // 返回全部位置
        }  // 结束空串特判
        int m = pat.size();  // 模式串长度
        vector<int> lps(m);  // KMP 的最长公共前后缀数组
        for (int i = 1, len = 0; i < m;) {  // 递推计算 lps
            if (pat[i] == pat[len]) {  // 字符相同，前后缀可以同时延长
                lps[i++] = ++len;  // 记录长度并前进一位
            } else if (len) {  // 失配时回退到更短的公共前后缀
                len = lps[len - 1];  // 用已知结果回退，i 不动
            } else {  // 已无更短前缀可回退
                ++i;  // 当前位 lps 为 0，直接前进
            }  // 结束分支
        }  // 结束 lps 计算
        vector<int> res;  // 保存所有匹配起点
        for (int i = 0, j = 0; i < n;) {  // 在主串上扫描
            if (s[i] == pat[j]) {  // 当前字符匹配
                ++i;  // 主串指针右移
                ++j;  // 模式串指针右移
                if (j == m) {  // 整个模式串匹配成功
                    res.push_back(i - m);  // 起点为 i-m
                    j = lps[j - 1];  // 利用 lps 继续寻找重叠的下一处匹配
                }  // 结束整体匹配判断
            } else if (j) {  // 失配但还有已匹配前缀
                j = lps[j - 1];  // 回退模式串指针，主串指针不动
            } else {  // 失配且没有任何已匹配前缀
                ++i;  // 主串指针右移
            }  // 结束分支
        }  // 结束扫描
        return res;  // 返回所有匹配起点
    }  // 结束 starts
};  // 结束题解类
