// 题目：859. 亲密字符串（Buddy Strings）
// 思路：长度与字符频次都必须相同；再统计同位置不同字符的个数：恰好 2 个就交换这两个位置，0 个则必须存在重复字符才能靠「交换相同字符」完成。
// 时间复杂度：O(n + |Σ|)，n 为字符串长度、Σ 为字符集；空间复杂度：O(|Σ|)，两个大小为 26 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool buddyStrings(string s, string goal) {  // 判断能否只交换 s 中的两个字符就得到 goal
        int m = s.size(), n = goal.size();  // 分别取两个字符串的长度
        if (m != n) return false;  // 长度不同，一次交换不可能改变长度
        int diff = 0;  // 统计同下标上字符不同的位置个数
        vector<int> cnt1(26);  // 统计 s 中每个小写字母的出现次数
        vector<int> cnt2(26);  // 统计 goal 中每个小写字母的出现次数
        for (int i = 0; i < n; ++i) {  // 逐位比较两个字符串
            ++cnt1[s[i] - 'a'];  // 累计 s 当前字符的频次
            ++cnt2[goal[i] - 'a'];  // 累计 goal 当前字符的频次
            if (s[i] != goal[i]) ++diff;  // 该位置字符不同，差异计数加一
        }  // for 循环结束
        bool f = false;  // 标记是否存在出现次数大于 1 的字符
        for (int i = 0; i < 26; ++i) {  // 遍历 26 个小写字母
            if (cnt1[i] != cnt2[i]) return false;  // 字符频次不同，交换无法增删字符，直接失败
            if (cnt1[i] > 1) f = true;  // 存在重复字符，才允许「交换两个相同的字符」这种不产生变化但合法的操作
        }  // for 循环结束
        return diff == 2 || (diff == 0 && f);  // 恰好两处不同可互换使其相等；或完全相同且含重复字符
    }  // buddyStrings 方法结束
};  // Solution 类定义结束