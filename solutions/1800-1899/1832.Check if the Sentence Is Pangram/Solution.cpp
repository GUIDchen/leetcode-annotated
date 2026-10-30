// 题目：1832. 判断句子是否为全字母句（Check if the Sentence Is Pangram）
// 思路：用长度 26 的标记数组记录出现过的字母，再线性扫描确认全部出现过。
// 时间复杂度：O(n + 26)；空间复杂度：O(1)，固定 26 个标记。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkIfPangram(string sentence) {  // sentence：只含小写字母的句子；返回它是否为全字母句
        int vis[26] = {0};  // vis：标记数组，vis[i] = 1 表示第 i 个字母出现过
        for (char& c : sentence) vis[c - 'a'] = 1;  // 遍历句子，按字母下标打标记
        for (int& v : vis)  // 检查 26 个字母
            if (!v) return false;  // 任意一个字母没出现，立即返回 false
        return true;  // 全部出现过，返回 true
    }  // 方法结束
};  // 类定义结束