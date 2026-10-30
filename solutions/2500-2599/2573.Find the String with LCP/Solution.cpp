// 题目：2573. 找出对应 LCP 矩阵的字符串（Find the String with LCP）
// 思路：先按字母从小到大贪心填：lcp[i][j] > 0 说明 s[i] 与 s[j] 同字母；再从右下角向左上角验证 LCP 矩阵是否自洽。
// 时间复杂度：O(n^2)，填字母与校验各一次二维扫描；空间复杂度：O(n)，只存结果字符串与若干下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string findTheString(vector<vector<int>>& lcp) {  // lcp：n × n 的 LCP 矩阵，返回对应的字符串，无解则返回空串
        int i = 0, n = lcp.size();  // i 是尚未赋值的最小下标；n 是字符串长度
        string s(n, '\0');  // 用空字符占位，表示该位置还未确定字母
        for (char c = 'a'; c <= 'z'; ++c) {  // 按字母表从小到大贪心分配
            while (i < n && s[i]) {  // 跳过已经赋过字母的位置
                ++i;  // 移到下一个未赋值位置
            }
            if (i == n) {  // 所有位置都已赋值，字母够用
                break;  // 提前结束分配
            }
            for (int j = i; j < n; ++j) {  // 与 i 的 LCP 大于 0 的位置必须和 i 是同一个字母
                if (lcp[i][j]) {  // LCP 大于 0 说明 s[i] 与 s[j] 相同
                    s[j] = c;  // 把这些位置统一赋成当前字母
                }
            }
        }
        if (s.find('\0') != -1) {  // 仍有位置没被赋值，说明需要超过 26 种字母，无解
            return "";  // 返回空串表示不存在这样的字符串
        }
        for (i = n - 1; ~i; --i) {  // 从右下角开始校验，保证用到的 lcp[i+1][j+1] 已经就绪
            for (int j = n - 1; ~j; --j) {  // 逐列向左扫描
                if (s[i] == s[j]) {  // 两个字符相同时，LCP 必须比右下方大 1
                    if (i == n - 1 || j == n - 1) {  // 边界情况：某一行或某一列已经到末尾
                        if (lcp[i][j] != 1) {  // 边界上同字母的 LCP 必须正好是 1
                            return "";  // 不满足说明矩阵非法，返回空串
                        }
                    } else if (lcp[i][j] != lcp[i + 1][j + 1] + 1) {  // 内部位置：LCP 应当等于右下方 LCP 加 1
                        return "";  // 不满足说明矩阵非法，返回空串
                    }
                } else if (lcp[i][j]) {  // 字符不同时 LCP 必须为 0
                    return "";  // LCP 不为 0 说明矩阵非法，返回空串
                }
            }
        }
        return s;  // 所有校验通过，返回构造出的字符串
    }
};