// 题目：1528. 重新排列字符串（Shuffle String）
// 思路：新建长度为 n 的结果串，按 indices[i] 给出的目标下标，把 s[i] 直接写到对应位置。
// 时间复杂度：O(n)，只需遍历一次字符串；空间复杂度：O(n)，需要额外的结果串存放 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string restoreString(string s, vector<int>& indices) {  // s：原字符串；indices[i]：s[i] 在结果串中的目标下标
        int n = s.size();  // 长度 n，同时也是结果串的容量
        string ans(n, 0);  // 结果串先按长度 n 分配，字符用 '\0' 占位，随后逐位填满
        for (int i = 0; i < n; ++i) {  // 遍历原串的每个字符
            ans[indices[i]] = s[i];  // 把 s[i] 一步放到它应该出现的位置，无需再整体挪动
        }  // 遍历结束
        return ans;  // 返回重排完成后的字符串
    }  // 方法结束
};  // 题解类结束