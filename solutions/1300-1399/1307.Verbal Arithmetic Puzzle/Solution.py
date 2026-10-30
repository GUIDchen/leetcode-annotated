# 题目：1307. 口算难题（Verbal Arithmetic Puzzle）
# 核心思路：把 result 并入 words 后按“列”从个位向高位做竖式加法回溯，bal 保存当前列累加和；
#           已映射字母直接代入，未映射字母枚举可用数字，递归返回失败时撤销映射（回溯）。
# 时间复杂度：O(10! * L)，最坏枚举字母到数字的全排列；空间复杂度：O(字母数 + L)，映射表与递归栈开销。
class Solution:  # LeetCode 约定的题解类
    def isAnyMapping(  # 回溯主体：逐列、逐行地给字母分配数字
        self, words, row, col, bal, letToDig, digToLet, totalRows, totalCols  # row 当前行，col 当前列（从个位起），bal 当前列累加和
    ):  # letToDig：字母→数字；digToLet：数字→字母（"-" 表示未占用）
        # If traversed all columns.
        if col == totalCols:  # 所有列都已处理完
            return bal == 0  # 最终没有剩余进位才算等式成立

        # At the end of a particular column.
        if row == totalRows:  # 一列的所有行都算完了
            return bal % 10 == 0 and self.isAnyMapping(  # 本位必须能被 10 整除（本位数字相等）
                words, 0, col + 1, bal // 10, letToDig, digToLet, totalRows, totalCols  # 用 bal//10 作为进位进入下一列
            )  # 下一列从第 0 行重新开始

        w = words[row]  # 当前正在处理的单词

        # If the current string 'w' has no character in the ('col')th index.
        if col >= len(w):  # 该单词这一列没有字符（位数较短）
            return self.isAnyMapping(  # 直接跳到下一行
                words, row + 1, col, bal, letToDig, digToLet, totalRows, totalCols  # 列与累加和都不变
            )  # 返回下一行的搜索结果

        # Take the current character in the variable letter.
        letter = w[len(w) - 1 - col]  # 从右往左取第 col 位，保证个位对齐

        # Create a variable 'sign' to check whether we have to add it or subtract it.
        if row < totalRows - 1:  # 前面的行都是加数
            sign = 1  # 加数，累加进 bal
        else:  # 最后一行是 result
            sign = -1  # 结果，从 bal 中减去

        # If we have a prior valid mapping, then use that mapping.
        # The second condition is for the leading zeros.
        if letter in letToDig and (  # 字母已有映射
            letToDig[letter] != 0  # 映射到的不是 0，任何位置都合法
            or (letToDig[letter] == 0 and len(w) == 1)  # 或者 0 出现在单字符单词里，不算前导零
            or col != len(w) - 1  # 或者该位不是最高位，也不是前导零
        ):  # 三者满足其一即可安全代入

            return self.isAnyMapping(  # 代入已知数字后继续同列下一行
                words,  # 单词表
                row + 1,  # 行号加一
                col,  # 列号不变
                bal + sign * letToDig[letter],  # 按符号把该位数字累加进 bal
                letToDig,  # 映射表保持不变
                digToLet,  # 反向表保持不变
                totalRows,  # 总行数
                totalCols,  # 总列数
            )  # 返回递归结果

        # Choose a new mapping.
        else:  # 字母还没有映射，需要枚举数字
            for i in range(10):  # 依次尝试 0 到 9
                # If 'i'th mapping is valid then select it.
                if digToLet[i] == "-" and (  # 数字 i 尚未被占用
                    i != 0 or (i == 0 and len(w) == 1) or col != len(w) - 1  # 且 i=0 时不能位于最高位（前导零）
                ):  # 满足条件才可尝试
                    digToLet[i] = letter  # 记录数字 i 分配给了 letter
                    letToDig[letter] = i  # 记录 letter 的值为 i

                    # Call the function again with the new mapping.
                    if self.isAnyMapping(  # 带着新映射递归处理下一行
                        words,  # 单词表
                        row + 1,  # 行号加一
                        col,  # 列号不变
                        bal + sign * letToDig[letter],  # 把该位数字累加进 bal
                        letToDig,  # 字母→数字表
                        digToLet,  # 数字→字母表
                        totalRows,  # 总行数
                        totalCols,  # 总列数
                    ):  # 若递归返回真
                        return True  # 说明找到合法映射，向上传递成功

                    # Unselect the mapping.
                    digToLet[i] = "-"  # 回溯：释放数字 i
                    if letter in letToDig:  # 确认字母映射存在
                        del letToDig[letter]  # 回溯：删除字母的映射

        # If nothing is correct then just return false.
        return False  # 所有数字都试过仍无解，返回失败

    def isSolvable(self, words, result):  # 判断字母竖式是否有解
        # Add the string 'result' in the list 'words'.
        words.append(result)  # 把结果串并入 words，统一按行处理

        # Initialize 'totalRows' with the size of the list.
        totalRows = len(words)  # 行数：加数个数 + 结果行

        # Find the longest string in the list and set 'totalCols' with the size of that string.
        totalCols = max(len(word) for word in words)  # 最长单词长度即竖式列数

        # Create a HashMap for the letter to digit mapping.
        letToDig = {}  # 字母 → 数字映射表，初始为空

        # Create a list for the digit to letter mapping.
        digToLet = ["-"] * 10  # 数字 → 字母反向表，"-" 表示未占用

        return self.isAnyMapping(  # 从个位、第 0 行、进位 0 开始回溯
            words, 0, 0, 0, letToDig, digToLet, totalRows, totalCols  # 传入初始状态
        )  # 返回是否有解
