// 题目：953. 验证外星语词典（Verifying an Alien Dictionary）
// 思路：按列（第 0 列、第 1 列…）纵向扫描所有单词：某列取值必须非降；某列严格递增后，后面的列无需再检查，只在前缀全部相等的列上继续。
// 时间复杂度：O(20·总字符数)，20 为单词最大长度；空间复杂度：O(1)，26 个元素的映射表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isAlienSorted(vector<string>& words, string order) {  // words：待验证的单词表；order：外星语字母表
        vector<int> m(26);  // m[字母] 记录该字母在外星语中的排名
        for (int i = 0; i < 26; ++i) m[order[i] - 'a'] = i;  // 逐位登记字母表顺序；减去 'a' 把字符转成 0-25 下标
        for (int i = 0; i < 20; ++i) {  // 逐列扫描，单词长度不超过 20，所以最多检查 20 列
            int prev = -1;  // prev 是这一列上一个单词的排名，-1 表示「空」，比任何字母都小
            bool valid = true;  // valid 标记本列是否全部相等（相等才需要继续检查下一列）
            for (auto& x : words) {  // 按顺序遍历每个单词
                int curr = i >= x.size() ? -1 : m[x[i] - 'a'];  // 取第 i 列字符；该单词已结束则记为 -1（最短者排最前）
                if (prev > curr) return false;  // 这一列出现逆序，直接判定不合法
                if (prev == curr) valid = false;  // 相邻单词在这一列不同，说明前 i 列已是共同前缀，全等不成立
                prev = curr;  // 把当前排名留给下一个单词比较
            }
            if (valid) break;  // 整列都相同，需要继续看下一列才能确定顺序
        }
        return true;  // 所有列都合法，返回真
    }
};