// 题目：267. 回文排列 II（Palindrome Permutation II）
// 思路：先确定唯一的中间字符（出现奇数次的字符至多一个），再从中间向外成对地放置字符，回溯生成全部回文排列。
// 时间复杂度：O(n!)，最坏要枚举所有排列；空间复杂度：O(n)，递归深度与当前回文长度同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int n;  // 记录原串长度，dfs 用它判断回文是否已经拼满
    vector<string> ans;  // 收集所有合法的回文排列结果
    unordered_map<char, int> cnt;  // 字符频次表：键是字符，值是出现次数

    vector<string> generatePalindromes(string s) {  // s 为输入字符串，返回全部不同的回文排列
        n = s.size();  // 先记下总长度
        for (char c : s) ++cnt[c];  // 统计每个字符出现的次数
        string mid = "";  // mid 保存中间那个字符；偶数长度时为空串
        for (auto& [k, v] : cnt) {  // 遍历频次表，找出出现奇数次的字符
            if (v & 1) {  // v & 1 为真说明该字符出现奇数次
                if (mid != "") {  // 奇数次的字符最多只能有一个，否则无法构成回文
                    return ans;  // 已经存在中间字符，说明无解，返回空答案
                }  // 无解判断结束
                mid += k;  // 把这个字符定为中间字符
            }  // 奇数次判断结束
        }  // 频次遍历结束
        dfs(mid);  // 从中间字符开始向外扩展
        return ans;  // 返回所有结果
    }  // generatePalindromes 方法结束

    void dfs(string t) {  // 回溯函数：t 是当前已经拼好的回文中段
        if (t.size() == n) {  // 长度达到原串长度，说明拼出了一个完整回文
            ans.push_back(t);  // 收进结果集
            return;  // 结束当前递归分支
        }  // 递归出口判断结束
        for (auto& [k, v] : cnt) {  // 枚举还能成对放置的字符
            if (v > 1) {  // 次数大于 1 才能左右各放一个
                v -= 2;  // 用掉两个该字符（v 是引用，会直接改动频次表）
                dfs(k + t + k);  // 把字符包在两侧继续递归
                v += 2;  // 回溯：恢复频次，供其他分支使用
            }  // 成对放置判断结束
        }  // 字符枚举结束
    }  // dfs 方法结束
};  // 类定义结束