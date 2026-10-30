// 题目：3227. 字符串元音游戏（Vowels Game in a String）
// 思路：玩家每步只能删掉非空且含元音的连续子串，答案只取决于字符串里有没有元音：有元音 Alice 必胜，没有则 Bob 胜。
// 时间复杂度：O(n)，最多扫一遍字符串；空间复杂度：O(1)，只存 5 个元音字母。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    bool doesAliceWin(string s) {  // 返回先手 Alice 是否必胜
        string vowels = "aeiou";  // 五个元音字母，用于判断某个字符是否为元音
        for (char c : s) {  // 遍历字符串中的每个字符
            if (vowels.find(c) != string::npos) {  // 在元音串中找到了该字符（find 没有返回 npos）
                return true;  // 只要存在元音，Alice 取走奇数个元音即可让 Bob 无元音可删，必胜
            }  // 不是元音则继续检查下一个字符
        }  // 循环结束
        return false;  // 整串没有元音，Alice 第一步就无法操作，Bob 获胜
    }  // 方法结束
};