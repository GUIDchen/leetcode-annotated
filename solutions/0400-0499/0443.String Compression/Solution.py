# 题目：443. 压缩字符串（String Compression）
# 思路：双指针原地压缩，i 指向当前连续段的起点，j 向右扫到该段结束；把字符与十进制计数依次写回数组前部，k 是写指针。
# 复杂度：时间复杂度 O(n)，每个字符只被读写常数次；空间复杂度 O(1)，只用了常数个额外变量。
class Solution:  # 题解类：字符串原地压缩
    def compress(self, chars: List[str]) -> int:  # chars 是字符列表（原地修改），返回压缩后的长度
        i, k, n = 0, 0, len(chars)  # i 是段起点，k 是写指针，n 是原长度
        while i < n:  # 逐个连续段处理
            j = i + 1  # j 从段起点的下一个位置开始找段尾
            while j < n and chars[j] == chars[i]:  # 右移到字符变化或走出数组
                j += 1  # 段尾继续右移
            chars[k] = chars[i]  # 写入字符本身
            k += 1  # 写指针后移一位
            if j - i > 1:  # 出现次数大于 1 才需要写计数
                cnt = str(j - i)  # 把计数转成数字字符串，便于逐位写入
                for c in cnt:  # 遍历计数的每一位
                    chars[k] = c  # 写入一位数字
                    k += 1  # 写指针后移
            i = j  # 跳到下一段的起点
        return k  # 写指针的位置就是压缩后的长度
