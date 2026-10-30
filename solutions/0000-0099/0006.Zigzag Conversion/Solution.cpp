// 题目：6. Z 字形变换（Zigzag Conversion）
// 思路：每行准备一个 string，用方向变量 k 让行号在 0 与 numRows-1 之间折返，字符按遍历顺序追加到对应行，最后按行拼接。
// 时间复杂度：O(n)，每个字符只被写入和读出一次；空间复杂度：O(n)，各行的 string 合计存 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string convert(string s, int numRows) {  // s 为输入字符串，numRows 为 Z 字形行数
        if (numRows == 1) {  // 只有一行时 Z 字形退化为原串
            return s;  // 直接返回原串
        }
        vector<string> g(numRows);  // 每行一个缓冲区，收集该行按遍历顺序遇到的字符
        int i = 0, k = -1;  // i 为当前行号，k 为移动方向（+1 下行、-1 上行）
        for (char c : s) {  // 按原顺序遍历每个字符
            g[i] += c;  // 追加到当前行末尾
            if (i == 0 || i == numRows - 1) {  // 到达首行或末行，方向要反弹
                k = -k;  // 方向取反
            }
            i += k;  // 行号沿方向移动一格
        }
        string ans;  // 用于汇总最终答案
        for (auto& t : g) {  // 按行号从小到大遍历各缓冲区
            ans += t;  // 整行拼接到答案末尾
        }
        return ans;  // 返回按行读取的结果
    }
};