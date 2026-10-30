// 题目：796. 旋转字符串（Rotate String）
// 思路：s 的所有循环移位都是 s+s 的子串，所以只要长度相等、且 goal 出现在 s+s 中即可。
// 时间复杂度：O(n)，子串查找；空间复杂度：O(n)，拼接出的 s+s。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool rotateString(string s, string goal) {  // s：原串；goal：目标串
        return s.size() == goal.size() && strstr((s + s).data(), goal.data());  // 长度不同直接 false；否则 goal 必须是 s+s 的子串（s+s 覆盖全部循环移位）
    }  // rotateString 结束
};  // 类定义结束