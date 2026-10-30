// 题目：1023. 驼峰式匹配（Camelcase Matching）
// 思路：对每个查询串用双指针贪心匹配——大写字母必须与 pattern 逐位对齐，小写字母可以跳过；pattern 用完后剩余的字符必须全是小写。
// 时间复杂度：O(m * |queries|)，m 为单个查询串长度；空间复杂度：O(1)，只用双指针（不计答案数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> camelMatch(vector<string>& queries, string pattern) {  // queries：待检查的字符串；pattern：目标驼峰模式；返回每个查询串是否匹配
        vector<bool> ans;  // 顺序记录每个查询串的判定结果
        auto check = [](string& s, string& t) {  // 无捕获的 lambda：判断 s 是否匹配模式 t（不修改入参，所以不用按引用捕获外部变量）
            int m = s.size(), n = t.size();  // m 是查询串长度，n 是模式串长度
            int i = 0, j = 0;  // i 指向 s 的当前字符，j 指向 t 的当前字符
            for (; j < n; ++i, ++j) {  // 逐个吃掉模式串中的字符；每轮 i、j 同时后移
                while (i < m && s[i] != t[j] && islower(s[i])) {  // 小写字母可以被忽略，因此跳过 s 中不匹配的小写字符，直到遇到可能对上的字符
                    ++i;  // 跳过这个无关的小写字母
                }
                if (i == m || s[i] != t[j]) {  // s 已扫描完，或当前字符与 t[j] 不一致（大写字母不允许跳过）
                    return false;  // 匹配失败
                }
            }
            while (i < m && islower(s[i])) {  // 模式串已匹配完，s 末尾残留的字符必须全是小写，否则会多出大写字母
                ++i;  // 跳过允许忽略的尾部小写字母
            }
            return i == m;  // i 走到末尾才说明 s 中没有多余的大写字母，匹配成功
        };
        for (auto& q : queries) {  // 对每个查询串依次判定
            ans.push_back(check(q, pattern));  // 把判定结果追加到答案
        }
        // 所有查询串的下标已按原顺序记录完毕
        return ans;  // 返回结果数组
    }
};