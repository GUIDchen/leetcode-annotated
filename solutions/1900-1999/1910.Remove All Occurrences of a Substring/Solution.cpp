// 题目：1910. 删除一个字符串中所有出现的给定子字符串（Remove All Occurrences of a Substring）
// 思路：只要 s 中还能找到 part，就删掉它第一次出现的那一段；反复执行直到找不到为止。
// 时间复杂度：O(n^2 * m) 最坏（每轮 find/erase 为 O(n*m)，最多 n/m 轮）；空间复杂度：O(n)，erase 会生成新字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeOccurrences(string s, string part) {  // s：原字符串；part：需要删除的子串
        int m = part.size();  // m：子串长度，也是每次要删除的字符数
        while (s.find(part) != -1) {  // find 返回 -1（与 size_t 比较时会转换）表示找不到，循环即可结束
            s = s.erase(s.find(part), m);  // 找到第一次出现的起点，从该位置起删掉 m 个字符，结果覆盖回 s
        }
        return s;  // 返回删除干净后的字符串
    }
};  // 类定义结束