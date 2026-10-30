# 题目：777. 在 LR 字符串中交换相邻字符（Swap Adjacent in LR String）
# 思路：'X' 是空位，'R' 只能右移、'L' 只能左移；忽略所有 'X' 后两串字符序列必须相同，且 'L' 在 start 中不能比 end 中更靠右、'R' 不能更靠左。
# 时间复杂度：O(n)，两个指针各扫一遍字符串；空间复杂度：O(1)，只用常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def canTransform(self, start: str, end: str) -> bool:  # start：初始字符串；end：目标字符串；返回能否靠相邻交换转换
        n = len(start)  # n：字符串长度，题目保证两串等长
        i = j = 0  # i 扫 start、j 扫 end，都指向各自下一个非 'X' 字符
        while 1:  # 无限循环，靠内部的 return 退出，每轮对齐一对非 'X' 字符
            while i < n and start[i] == 'X':  # 'X' 不参与配对，先跳过 start 里的 'X'
                i += 1  # 指针后移，继续跳过连续的 'X'
            while j < n and end[j] == 'X':  # 同样跳过 end 里的 'X'
                j += 1  # 指针后移，直到 j 落在非 'X' 字符上
            if i >= n and j >= n:  # 两个串都只剩 'X'：所有非 'X' 字符配对完毕，可以转换
                return True  # 返回成功
            if i >= n or j >= n or start[i] != end[j]:  # 一边先扫完说明非 'X' 个数不同；当前字符不同说明 'L'/'R' 序列不同，均失败
                return False  # 返回失败
            if start[i] == 'L' and i < j:  # 'L' 只能左移，若它在 start 中比 end 中更靠右，就永远追不上
                return False  # 返回失败
            if start[i] == 'R' and i > j:  # 'R' 只能右移，若它在 start 中比 end 中更靠左，同样到不了目标位置
                return False  # 返回失败
            i, j = i + 1, j + 1  # 这一对字符校验通过，两个指针同时后移，继续下一对
