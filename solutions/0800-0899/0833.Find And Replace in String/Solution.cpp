// 题目：833. 字符串中的查找与替换（Find And Replace in String）
// 思路：先校验每个替换是否真的在 indices[k] 处匹配，把「起点 → 替换编号」记入 d 数组；再从左到右扫描原串，命中替换就整段替换并跳过该段，否则逐字符拷贝。
// 时间复杂度：O(n + m·L)，m 为替换个数、L 为被替换子串长度；空间复杂度：O(n)，需要 d 数组与答案串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {  // s 是原串；indices/sources/targets 三个等长数组分别给出替换起点、被匹配子串与替换目标
        int n = s.size();  // 原串长度，后续所有下标都以它为界
        vector<int> d(n, -1);  // d[i] 记录「从 i 开始可执行哪一次替换」，-1 表示该位置没有合法替换
        for (int k = 0; k < indices.size(); ++k) {  // 逐个检查每个候选替换操作
            int i = indices[k];  // 本次替换的起始下标
            if (s.compare(i, sources[k].size(), sources[k]) == 0) {  // 只有 s 在 i 处的内容与 sources[k] 完全一致时，这次替换才合法
                d[i] = k;  // 记下该位置对应的替换编号，供第二遍拼接时查用
            }  // if 结束
        }  // for 结束
        string ans;  // 存放最终答案
        for (int i = 0; i < n;) {  // 从左到右拼接原串，i 的步长取决于该位置是否发生替换
            if (~d[i]) {  // 按位取反判非 -1：-1 取反为 0，可一次区分「有替换」与「无替换」
                ans += targets[d[i]];  // 用替换后的字符串整段拼入答案
                i += sources[d[i]].size();  // 跳过被替换掉的那一段，避免重复输出
            } else {  // 该位置没有合法替换，只能照抄原字符
                ans += s[i++];  // 原样保留当前字符并前进一位
            }  // if-else 结束
        }  // for 结束
        return ans;  // 返回拼好的字符串
    }  // 方法结束
};