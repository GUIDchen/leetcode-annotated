// 题目：2014. 重复 K 次的最长子序列（Longest Subsequence Repeated k Times）
// 思路：先统计字符频率，只保留出现次数 ≥ k 的字符；再用 BFS 按长度从小到大枚举由这些字符构成的串，用子序列匹配检查它重复 k 次是否仍是 s 的子序列，最后一个通过的串即最长且字典序最大。
// 时间复杂度：O(|Σ|^L · |s|)，L 为答案长度（受频率上限约束，|Σ| ≤ 26）；空间复杂度：O(|Σ|^L)，队列最多存放这么多候选串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestSubsequenceRepeatedK(string s, int k) {  // s：原字符串；k：重复次数；返回重复 k 次后仍为 s 子序列的最长字符串
        auto check = [&](const string& t, int k) -> bool {  // lambda：判断 t 连续重复 k 次后是否仍是 s 的子序列
            int i = 0;  // i 指向 t 中当前等待匹配的字符位置
            for (char c : s) {  // 顺序扫描 s，贪心地匹配 t 的字符
                if (c == t[i]) {  // s 的当前字符与 t 的待匹配字符相同
                    i++;  // 该字符匹配成功，t 前进一位
                    if (i == t.size()) {  // t 已经完整匹配了一遍
                        if (--k == 0) {  // 剩余重复次数减一，减到 0 说明已重复 k 遍
                            return true;  // 校验成功
                        }  // 重复次数判断结束
                        i = 0;  // 重置下标，从头开始匹配下一遍
                    }  // 单遍完成判断结束
                }  // 字符匹配分支结束
            }  // 扫描 s 结束
            return false;  // s 扫完仍未凑满 k 遍，说明 t 不合法
        };  // lambda 定义结束
        int cnt[26] = {};  // cnt[c - 'a'] 记录字符 c 在 s 中出现的次数
        for (char c : s) {  // 遍历 s 统计每个字符的频率
            cnt[c - 'a']++;  // 对应字符的计数加一
        }  // 频率统计结束

        vector<char> cs;  // cs 收集出现次数 ≥ k 的字符，即有可能进入答案的字符
        for (char c = 'a'; c <= 'z'; ++c) {  // 按字典序从小到大遍历 26 个小写字母
            if (cnt[c - 'a'] >= k) {  // 出现次数不足 k 次的字符不可能出现在答案里
                cs.push_back(c);  // 把可用字符加入候选集
            }  // 字符筛选分支结束
        }  // 字符筛选循环结束

        queue<string> q;  // BFS 队列：按长度从小到大枚举候选串
        q.push("");  // 空串作为搜索起点
        string ans;  // ans 记录最后一个通过校验（即最长且字典序最大）的候选串
        while (!q.empty()) {  // 队列非空就继续扩展
            string cur = q.front();  // 取出当前候选串
            q.pop();  // 弹出队首
            for (char c : cs) {  // 尝试在末尾追加每个可用字符
                string nxt = cur + c;  // 拼接出更长一层的候选串
                if (check(nxt, k)) {  // 校验：nxt 重复 k 次后是否仍为 s 的子序列
                    ans = nxt;  // 通过校验就更新答案；BFS 顺序保证后更新的串更长或字典序更大
                    q.push(nxt);  // 继续以它为基础扩展更长的串
                }  // 追加字符分支结束
            }  // 候选字符循环结束
        }  // BFS 结束
        return ans;  // 返回最长且字典序最大的合法子序列
    }  // 方法结束
};  // 类定义结束
