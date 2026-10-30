// 题目：3304. 找出第 K 个字符 I（Find the K-th Character in String Game I）
// 思路：按生成规则不断把「每个字符的下一字母」追加到串尾，直到长度 >= k，直接取第 k 个字符。
// 时间复杂度：O(k)，串长倍增到 >= k，总操作数受 2k 约束；空间复杂度：O(k)，保存生成的整串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    char kthCharacter(int k) {  // k：要查询的位置（从 1 开始）；返回生成串中的第 k 个字符
        vector<int> word;  // word 用 0..25 存字符相对 'a' 的偏移，避免反复操作字符串
        word.push_back(0);  // 初始串就是 "a"，偏移为 0
        while (word.size() < k) {  // 长度不足 k 时继续扩展
            int m = word.size();  // 记录扩展前的长度，只复制这一段并加一
            for (int i = 0; i < m; ++i) {  // 遍历原有部分
                word.push_back((word[i] + 1) % 26);  // 新字符 = 原字符的下一个字母（'z' 之后回绕到 'a'），追加到串尾
            }
        }
        return 'a' + word[k - 1];  // 偏移转回字符：'a' + 偏移（下标从 0 开始，所以是 k-1）
    }
};
