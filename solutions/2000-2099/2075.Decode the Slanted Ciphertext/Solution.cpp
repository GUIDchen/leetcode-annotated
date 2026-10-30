// 题目：2075. 解码斜向换位密码（Decode the Slanted Ciphertext）
// 思路：把密文按 rows 行等宽排成矩阵，从每一列的顶部出发沿右下方向斜走收集字符，最后删掉尾部的补位空格。
// 时间复杂度：O(rows · cols) = O(len(encodedText))；空间复杂度：O(len(encodedText))，用于存放解码结果。
class Solution {  // 题解类：所有题解方法都写在这里
public:  // 方法对外可见（LeetCode 约定）
    string decodeCiphertext(string encodedText, int rows) {  // encodedText 是密文，rows 是原始矩阵的行数
        string ans;  // 按斜线顺序收集解码出的字符
        int cols = encodedText.size() / rows;  // 每行有 cols 个字符，密文长度 = rows * cols
        for (int j = 0; j < cols; ++j) {  // 枚举每条斜线的起点列 j
            for (int x = 0, y = j; x < rows && y < cols; ++x, ++y) {  // 从第 0 行、第 j 列出发，沿右下方向斜走直到越界
                ans += encodedText[x * cols + y];  // 一维下标 = 行号 * 列宽 + 列号
            }  // 内层斜线遍历结束
        }  // 所有起点列遍历结束
        while (ans.size() && ans.back() == ' ') {  // 原文尾部可能有补位空格，需要去掉
            ans.pop_back();  // 逐个弹出末尾空格
        }  // 去空格循环结束
        return ans;  // 返回解码后的原文
    }  // 方法结束
};  // 类定义结束