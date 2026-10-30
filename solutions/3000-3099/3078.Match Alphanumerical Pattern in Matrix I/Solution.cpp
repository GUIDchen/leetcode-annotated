// 题目：3078. 矩阵中的字母数字模式匹配 I（Match Alphanumerical Pattern in Matrix I）🔒
// 思路：枚举所有可能的左上角，逐格校验 pattern 与 board 子矩阵：数字必须完全相同，字母则维护「字母→数字」和「数字→字母」双向映射保证一一对应。
// 时间复杂度：O(m * n * r * c)，每个候选位置检查一次模式大小；空间复杂度：O(r * c + 26)，映射表与常数空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findPattern(vector<vector<int>>& board, vector<string>& pattern) {  // board：数字矩阵；pattern：数字与字母组成的模式；返回匹配子矩阵的左上角坐标，找不到返回 [-1, -1]
        int m = board.size(), n = board[0].size();  // m、n：board 的行数与列数
        int r = pattern.size(), c = pattern[0].size();  // r、c：pattern 的行数与列数，也就是要匹配的子矩阵大小
        auto check = [&](int i, int j) {  // check：检查以 (i, j) 为左上角的子矩阵是否与 pattern 匹配
            vector<int> d1(26, -1);  // d1：字母(0~25) 到 board 数字的映射，-1 表示尚未建立
            vector<int> d2(10, -1);  // d2：board 数字(0~9) 到字母的映射，保证不同字母不会对应同一个数字
            for (int a = 0; a < r; ++a) {  // 遍历模式内的行偏移
                for (int b = 0; b < c; ++b) {  // 遍历模式内的列偏移
                    int x = i + a, y = j + b;  // 换算出对应的 board 坐标
                    if (isdigit(pattern[a][b])) {  // 模式该位是数字时，要求 board 完全相同
                        int v = pattern[a][b] - '0';  // 把数字字符转成对应的整数
                        if (v != board[x][y]) {  // 数字不一致，这个位置不匹配
                            return false;  // 匹配失败，提前返回
                        }
                    } else {  // 模式该位是字母，需要建立并校验双向的一一映射
                        int v = pattern[a][b] - 'a';  // 把字母转成 0~25 的下标
                        if (d1[v] != -1 && d1[v] != board[x][y]) {  // 同一个字母此前已映射到别的数字，违反一致性
                            return false;  // 冲突，匹配失败
                        }
                        if (d2[board[x][y]] != -1 && d2[board[x][y]] != v) {  // 该数字此前已被别的字母占用，违反一一对应
                            return false;  // 冲突，匹配失败
                        }
                        d1[v] = board[x][y];  // 记录正向映射：字母 -> 数字
                        d2[board[x][y]] = v;  // 记录反向映射：数字 -> 字母
                    }
                }
            }
            return true;  // 所有格子都通过校验，说明匹配成功
        };  // 匹配函数定义结束
        for (int i = 0; i < m - r + 1; ++i) {  // 枚举子矩阵左上角的行，最多到 m - r 才能放得下模式
            for (int j = 0; j < n - c + 1; ++j) {  // 枚举子矩阵左上角的列，最多到 n - c
                if (check(i, j)) {  // 该位置能与模式匹配
                    return {i, j};  // 返回找到的左上角坐标
                }
            }
        }
        return {-1, -1};  // 没有任何位置匹配，按题目要求返回 [-1, -1]
    }
};