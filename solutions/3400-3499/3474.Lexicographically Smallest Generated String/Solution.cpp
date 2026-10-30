// 3474. Lexicographically Smallest Generated String / 3474. 字典序最小的生成字符串
// 核心思路：先按所有 T 位置把 t 强制写入，再从右往左为仍与 t 相同的 F 窗口放一个 'b' 破坏匹配，从而字典序增量最小。
// 复杂度：时间 O((n + m) * m)，空间 O(n + m)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 公有接口
    string generateString(string s, string t) {  // 返回满足所有 T/F 约束的字典序最小字符串
        int n = s.size(), m = t.size();  // n 为约束个数，m 为模式串 t 的长度
        string ans(n + m - 1, 'a');  // 结果串长度固定为 n + m - 1，先全部填字典序最小的 'a'
        vector<bool> fixed(n + m - 1, false);  // 标记每个位置是否已被 T 约束强制写死

        for (int i = 0; i < n; i++) {  // 先处理所有 T 约束
            if (s[i] != 'T') continue;  // 只处理要求完全匹配的位置
            for (int j = 0; j < m; j++) {  // 把模式串逐位写入窗口
                int k = i + j;  // 对应的结果串下标
                if (fixed[k] && ans[k] != t[j]) return "";  // 与之前写死的字符冲突，直接返回空串表示无解
                ans[k] = t[j];  // 写入模式串字符
                fixed[k] = true;  // 标记该位置已固定
            }  // 窗口写入结束
        }  // T 约束处理结束

        for (int i = 0; i < n; i++) {  // 再处理所有 F 约束
            if (s[i] != 'F') continue;  // 只处理要求不完全匹配的位置

            bool same = true;  // 先判断当前窗口是否恰好等于模式串
            for (int j = 0; j < m; j++) {  // 逐位比较窗口与模式串
                if (ans[i + j] != t[j]) {  // 出现不同字符
                    same = false;  // 已经满足 F 约束
                    break;  // 无需继续比较
                }  // 不同字符分支结束
            }  // 逐位比较结束
            if (!same) continue;  // 不相等则无需处理

            bool ok = false;  // 标记是否成功放置字符来破坏匹配
            for (int j = i + m - 1; j >= i; j--) {  // 从右往左找第一个可自由修改的位置
                if (!fixed[j]) {  // 找到非固定位置
                    ans[j] = 'b';  // 改成 'b' 破坏匹配，且字典序增加最少
                    ok = true;  // 标记成功
                    break;  // 只改一个字符即可
                }  // 非固定位置分支结束
            }  // 从右往左查找结束
            if (!ok) return "";  // 窗口内全被固定，无法破坏匹配，无解
        }  // F 约束处理结束

        return ans;  // 返回构造出的字典序最小字符串
    }  // 方法结束
};  // 类定义结束
