# 题目：345. 反转字符串中的元音字母（Reverse Vowels of a String）
# 思路：双指针从两端向中间扫，跳过非元音，遇到成对的元音就交换；因为字符串不可变，先转成字符列表再拼回。
# 时间复杂度：O(n)，两个指针各自单向走完全程；空间复杂度：O(n)，转成了等长的字符列表。
class Solution:  # LeetCode 约定的题解类
    def reverseVowels(self, s: str) -> str:  # s：输入字符串，返回把元音字母反转后的新字符串
        vowels = "aeiouAEIOU"  # 把所有大小写元音放在一个字符串里，用 in 判断成员资格
        i, j = 0, len(s) - 1  # 双指针：i 指向开头，j 指向末尾
        cs = list(s)  # 字符串不可变，先转成字符列表才能逐位交换
        while i < j:  # 两个指针没相遇就继续寻找可交换的元音对
            while i < j and cs[i] not in vowels:  # 左指针跳过非元音字符
                i += 1  # s[i] 不是元音，i 右移一格
            while i < j and cs[j] not in vowels:  # 右指针跳过非元音字符
                j -= 1  # s[j] 不是元音，j 左移一格
            if i < j:  # 两侧都停在元音上时才交换，避免同一位置自交换
                cs[i], cs[j] = cs[j], cs[i]  # 交换两个元音字符
                i, j = i + 1, j - 1  # 两个指针同时向中间收缩
        return "".join(cs)  # 把字符列表拼回字符串返回
