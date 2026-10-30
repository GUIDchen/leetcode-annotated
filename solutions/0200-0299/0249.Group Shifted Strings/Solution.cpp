// 题目：249. 移位字符串分组（Group Shifted Strings）
// 思路：同一移位关系的字符串，把每个字符减去首字符相对 'a' 的偏移后得到同一个基准串；用哈希表按基准串分组。
// 时间复杂度：O(L)，L 为所有字符串的总长度；空间复杂度：O(L)，哈希表保存全部字符。
class Solution {  // LeetCode 约定的题解类
public:  // 成员函数对外可见
    vector<vector<string>> groupStrings(vector<string>& strings) {  // strings：待分组的字符串数组，返回按移位关系分好的各组
        unordered_map<string, vector<string>> g;  // 键是归一化后的基准串，值是同组内的原始字符串
        for (auto& s : strings) {  // 逐个字符串计算它的基准串
            string t;  // 存放归一化后的基准串
            int diff = s[0] - 'a';  // 首字母相对 'a' 的偏移量，用它把所有字符平移回同一起点
            for (int i = 0; i < s.size(); ++i) {  // 逐字符构造基准串
                char c = s[i] - diff;  // 每个字符都减去首字母偏移
                if (c < 'a') {  // 平移后可能越过 'a' 而下溢
                    c += 26;  // 加 26 环绕回合法的小写字母范围
                }  // 结束环绕处理
                t.push_back(c);  // 把结果字符追加到基准串末尾
            }  // 结束单个字符串的字符遍历
            g[t].emplace_back(s);  // 基准串相同的字符串归入同一组
        }  // 结束全部字符串的遍历
        vector<vector<string>> ans;  // 答案：每个分组放入一个 vector
        for (auto& p : g) {  // 遍历哈希表中的每个分组
            ans.emplace_back(move(p.second));  // 用 move 把分组内容整体搬进答案，避免深拷贝
        }  // 结束分组遍历
        return ans;  // 返回全部分组
    }  // 结束 groupStrings 方法
};  // 结束 Solution 类