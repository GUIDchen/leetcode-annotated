// 题目：1307. 口算难题（Verbal Arithmetic Puzzle）
// 核心思路：把 words 与 result 拼在一起，按“列”从个位向高位逐列做竖式加法回溯，bal 保存当前列的进位与部分和；
//          字母→数字、数字→字母两张表记录映射，遇到已映射字母直接代入，否则枚举未占用数字，回溯时撤销。
// 时间复杂度：O(10! * L)，最坏要枚举字母到数字的全排列，L 为最长单词长度；空间复杂度：O(字母数 + L)，递归深度与两张映射表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isAnyMapping(vector<string>& words, int row, int col, int bal, unordered_map<char, int>& letToDig,  // row 当前处理第几个单词，col 当前列（从个位起），bal 当前列的累加和
        vector<char>& digToLet, int totalRows, int totalCols) {  // digToLet 是数字→字母的反向表，totalRows/totalCols 是行数、最长列数
        // If traversed all columns.
        if (col == totalCols) {  // 所有列都处理完毕
            return bal == 0;  // 最终进位必须恰好为 0 才等式成立
        }

        // At the end of a particular column.
        if (row == totalRows) {  // 一列的单词都加/减完了，需要处理这一列的进位
            return (bal % 10 == 0 && isAnyMapping(words, 0, col + 1, bal / 10, letToDig, digToLet, totalRows, totalCols));  // 本位必须整除 10，再把 bal/10 作为进位进入下一列
        }

        string w = words[row];  // 取出当前正在处理的单词

        // If the current string 'W' has no character in the ('COL')th index.
        if (col >= w.length()) {  // 该单词在这一列没有字符（位数不够）
            return isAnyMapping(words, row + 1, col, bal, letToDig, digToLet, totalRows, totalCols);  // 跳过它，直接处理同列的下一行
        }

        // Take the current character in the variable letter.
        char letter = w[w.length() - 1 - col];  // 从右往左取第 col 位字符，即个位对齐

        // Create a variable 'SIGN' to check whether we have to add it or subtract it.
        int sign;  // 符号：加数取 +1，结果行取 -1

        if (row < totalRows - 1) {  // 前 totalRows-1 行都是加数
            sign = 1;  // 加数，累加进 bal
        } else {  // 最后一行是 result
            sign = -1;  // 结果，从 bal 中减去
        }

        /*
            If we have a prior valid mapping, then use that mapping.
            The second condition is for the leading zeros.
        */
        if (letToDig.count(letter) && (letToDig[letter] != 0 || (letToDig[letter] == 0 && w.length() == 1) || col != w.length() - 1)) {  // 该字母已有映射，且该 0 不在最高位（避免前导零）

            return isAnyMapping(words, row + 1, col, bal + sign * letToDig[letter],  // 直接代入已知数字，继续同列下一行
                letToDig, digToLet, totalRows, totalCols);  // 原样传递两张映射表

        }
        // Choose a new mapping.
        else {  // 字母还没有映射，枚举它可能的数字
            for (int i = 0; i < 10; i++) {  // 依次尝试数字 0 到 9

                // If 'i'th mapping is valid then select it.
                if (digToLet[i] == '-' && (i != 0 || (i == 0 && w.length() == 1) || col != w.length() - 1)) {  // 数字 i 未被占用，且不是最高位上的 0
                    digToLet[i] = letter;  // 建立数字 → 字母映射
                    letToDig[letter] = i;  // 建立字母 → 数字映射

                    // Call the function again with the new mapping.
                    bool x = isAnyMapping(words, row + 1, col, bal + sign * letToDig[letter],  // 带着新映射递归处理下一行
                        letToDig, digToLet, totalRows, totalCols);  // 继续按列推进

                    if (x == true) {  // 后续搜索成功
                        return true;  // 整个等式可解，直接向上返回
                    }

                    // Unselect the mapping.
                    digToLet[i] = '-';  // 回溯：撤销数字 i 的占用
                    if (letToDig.find(letter) != letToDig.end()) {  // 仅当字母映射确实存在时才删除
                        letToDig.erase(letter);  // 回溯：删除字母 → 数字映射
                    }
                }
            }
        }

        // If nothing is correct then just return false.
        return false;  // 所有数字都试过仍不成功，本分支无解
    }  // isAnyMapping 结束

    bool isSolvable(vector<string>& words, string result) {  // 判断由 words 与 result 组成字母竖式是否有解
        // Add the string 'RESULT' in the vector 'WORDS'.
        words.push_back(result);  // 把结果串也并入 words，统一按行处理

        int totalRows;  // 行数：加数个数 + 结果行
        int totalCols;  // 最长单词长度，即竖式的列数

        // Initialize 'TOTALROWS' with the size of the vector.
        totalRows = words.size();  // 此时 words 已包含 result

        // Find the longest string in the vector and set 'TOTALCOLS' with the size of that string.
        totalCols = 0;  // 从 0 开始找最大长度

        for (int i = 0; i < words.size(); i++) {  // 遍历所有单词

            // If the current string is the longest then update 'TOTALCOLS' with its length.
            if (totalCols < words[i].size()) {  // 发现更长的单词
                totalCols = words[i].size();  // 更新最大列数
            }
        }

        // Create a HashMap for the letter to digit mapping.
        unordered_map<char, int> letToDig;  // 字母 → 数字的映射表，空表表示尚未分配

        // Create a vector for the digit to letter mapping.
        vector<char> digToLet(10, '-');  // 数字 → 字母的反向表，'-' 表示该数字还没被占用

        return isAnyMapping(words, 0, 0, 0, letToDig, digToLet, totalRows, totalCols);  // 从个位、第 0 行、进位 0 开始回溯
    }
};
