// 题目：3805. 统计凯撒加密对数目（Count Caesar Cipher Pairs）
// 思路：把每个单词循环平移成「首字母为 z」的规范形式，规范形式相同的单词两两互为凯撒加密，按组合数累加。
// 时间复杂度：O(L)，L 为所有单词的总字符数；空间复杂度：O(L)，哈希表按规范形式统计个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countPairs(vector<string>& words) {  // 统计可以通过凯撒整体平移互相转化的单词对数量
        unordered_map<string, int> cnt;  // 键：归一化后的字符串；值：该归一化形式出现的次数
        long long ans = 0;  // 答案（成对数量）
        for (auto& s : words) {  // 遍历每个单词
            string t = s;  // 复制一份，准备做归一化
            int k = 'z' - t[0];  // 让首字母平移到 'z' 所需的位移量
            for (int i = 1; i < t.size(); i++) {  // 对首字母之后的每个字符做同样的平移
                t[i] = 'a' + (t[i] - 'a' + k) % 26;  // 在字母表上循环右移 k 位
            }  // 结束 for (int i = 1; i < t.size(); i++)
            t[0] = 'z';  // 首字母统一设为 'z'，使平移后的单词也能直接比较
            cnt[t]++;  // 归一化形式相同的单词归为一类
        }  // 结束 for (auto& s : words)
        for (auto& [key, v] : cnt) {  // 遍历每一类（key 为规范形式，v 为个数）
            ans += 1LL * v * (v - 1) / 2;  // 同类内任意两个都能互相转化，贡献组合数 C(v,2)
        }  // 结束 for (auto& [key, v] : cnt)
        return ans;  // 返回答案
    }  // 结束 long long countPairs(vector<string>& words)
};  // 结束 class Solution
