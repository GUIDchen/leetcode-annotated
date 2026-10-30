// 题目：791. 自定义字符串排序（Custom Sort String）
// 思路：把 order 中字符出现的位置当作排序权重，再按权重对 s 排序。
// 时间复杂度：O(|order| + |s| log |s|)，来自排序；空间复杂度：O(1)，只有长度 26 的权重表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string customSortString(string order, string s) {  // order 给出自定义字符顺序，s 是待排序字符串，返回重排结果
        int d[26] = {0};  // 权重表：d[c] 是字符 c 在 order 中的下标，未出现的字符保持 0
        for (int i = 0; i < order.size(); ++i) d[order[i] - 'a'] = i;  // 按 order 的顺序给每个字符分配递增的权重
        sort(s.begin(), s.end(), [&](auto a, auto b) { return d[a - 'a'] < d[b - 'a']; });  // 按权重升序排序；order[0] 与 order 中未出现的字符权重都是 0，它们之间顺序不定，题目允许
        return s;  // 返回排好序的字符串
    }  // 方法结束
};  // 题解类结束