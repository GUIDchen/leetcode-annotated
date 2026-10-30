# 题目：2868. 单词游戏（The Wording Game）
# 思路：序列已升序，用两个指针模拟轮流出词；新词必须同首字母且字典序更大，或首字母恰好大 1；谁先无词可出谁就输。
# 时间复杂度：O(n + m)，两个指针各自只扫一遍；空间复杂度：O(1)，只用到下标与当前单词。
class Solution:  # LeetCode 约定的题解类
    def canAliceWin(self, a: List[str], b: List[str]) -> bool:  # a 是 Alice 的词表，b 是 Bob 的词表，均已升序
        i, j, k = 1, 0, 1  # i/j 是 a、b 下一个待考察下标；k=1 表示轮到 Bob（Alice 已用 a[0] 开局）
        w = a[0]  # w 是桌面上最后一个打出的单词，Alice 先出最小的那个
        while 1:  # 双方交替出词，直到某人在分支里 return
            if k:  # 轮到 Bob 出词
                if j == len(b):  # Bob 的词已经全部试过，没有可接的词
                    return True  # Bob 无法出词，Alice 获胜
                if (b[j][0] == w[0] and b[j] > w) or ord(b[j][0]) - ord(w[0]) == 1:  # 同首字母且更大，或首字母恰好大 1
                    w = b[j]  # 合法就把这个词放到桌面上，成为新的当前词
                    k ^= 1  # 切换回合，交还给 Alice
                j += 1  # 无论是否用上，Bob 的指针都只前进，跳过不可能再用的词
            else:  # 轮到 Alice 出词
                if i == len(a):  # Alice 的词已经全部试过，没有可接的词
                    return False  # Alice 无法出词，她输了
                if (a[i][0] == w[0] and a[i] > w) or ord(a[i][0]) - ord(w[0]) == 1:  # 同样的合法性判断
                    w = a[i]  # 合法就更新桌面上的当前词
                    k ^= 1  # 切换回合，交还给 Bob
                i += 1  # Alice 的词表指针向前推进一位
