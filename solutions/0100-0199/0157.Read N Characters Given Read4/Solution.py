# 题目：157. 用 Read4 读取 N 个字符（Read N Characters Given Read4）
# 思路：循环调用 read4 把最多 4 个字符读进 buf4，再逐个写入目标 buf，凑够 n 个立即返回；某批不足 4 个说明文件已读完。
# 时间复杂度：O(n)，最多搬运 n 个字符；空间复杂度：O(1)，额外只用长度为 4 的临时列表。
"""
The read4 API is already defined for you.

    @param buf4, a list of characters
    @return an integer
    def read4(buf4):

# Below is an example of how the read4 API can be called.
file = File("abcdefghijk") # File is "abcdefghijk", initially file pointer (fp) points to 'a'
buf4 = [' '] * 4 # Create buffer with enough space to store characters
read4(buf4) # read4 returns 4. Now buf = ['a','b','c','d'], fp points to 'e'
read4(buf4) # read4 returns 4. Now buf = ['e','f','g','h'], fp points to 'i'
read4(buf4) # read4 returns 3. Now buf = ['i','j','k',...], fp points to end of file
"""


class Solution:  # LeetCode 约定的题解类（判题器已提供全局函数 read4）
    def read(self, buf, n):  # buf：目标缓冲区；n：最多要读取的字符数；返回实际读到的字符数
        """
        :type buf: Destination buffer (List[str])
        :type n: Number of characters to read (int)
        :rtype: The number of actual characters read (int)
        """
        i = 0  # 已写入 buf 的字符个数，同时充当下一个写入位置
        buf4 = [0] * 4  # 长度为 4 的临时缓冲区，供 read4 每次最多写入 4 个字符
        v = 5  # v 初始化为 5 只是为了让下面的 while 至少进入一次
        while v >= 4:  # v >= 4 说明上一批读满了，可能还有数据，需要继续读
            v = read4(buf4)  # 调用 read4，返回本批实际读到的字符数（0 表示文件结束）
            for j in range(v):  # 逐个搬运本批读到的字符
                buf[i] = buf4[j]  # 写入目标的第 i 个位置
                i += 1  # 位置指针后移
                if i >= n:  # 已经凑够 n 个字符
                    return n  # 立即返回 n
        return i  # 本批不足 4 个时外层 while 会自然退出，再返回实际读到的总数
