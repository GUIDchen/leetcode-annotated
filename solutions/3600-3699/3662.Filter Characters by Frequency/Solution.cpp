// 3662. Filter Characters by Frequency（3662. 按频率筛选字符）🔒
// 核心思路：先统计 26 个小写字母的出现次数，再按原顺序保留出现次数小于 k 的字符。
// 复杂度：时间 O(n)，空间 O(1)（字母表大小固定为 26）。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    string filterCharacters(string s, int k) {  // 保留 s 中出现次数小于 k 的字符，返回过滤后的字符串
        int cnt[26]{};  // 统计 26 个小写字母的出现次数
        for (char c : s) {  // 第一遍遍历：统计每个字母的频次
            ++cnt[c - 'a'];  // 对应字母计数加一
        }  // 结束统计循环
        string ans;  // 保存过滤后的结果
        for (char c : s) {  // 第二遍遍历：按原顺序筛选字符
            if (cnt[c - 'a'] < k) {  // 频次小于 k 的字符需要保留
                ans.push_back(c);  // 追加到结果末尾
            }  // 结束筛选判断
        }  // 结束筛选循环
        return ans;  // 返回过滤后的字符串
    }  // 结束方法
};  // 结束题解类
