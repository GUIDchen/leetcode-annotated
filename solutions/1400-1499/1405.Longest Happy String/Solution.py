# 题目：1405. 最长快乐字符串（Longest Happy String）
# 思路：小顶堆存 [-剩余次数, 字母]，每次取剩余最多的字母；若答案末尾已是两个相同字母，就改取第二多的字母插一个再放回，直到堆空。
# 时间复杂度：O((a+b+c) log 3)，每步一次堆操作；空间复杂度：O(1)，堆中最多 3 个元素。
class Solution:  # LeetCode 约定的题解类
    def longestDiverseString(self, a: int, b: int, c: int) -> str:  # a、b、c 分别为三个字母的可用次数
        h = []  # 小顶堆：存 [-次数, 字母]，负号让次数多的排前面
        if a > 0:  # 次数为 0 的字母无需入堆
            heappush(h, [-a, 'a'])  # 判题环境已提供 heappush
        if b > 0:  # 同上处理 'b'
            heappush(h, [-b, 'b'])  # 负号把最大次数放到堆顶
        if c > 0:  # 同上处理 'c'
            heappush(h, [-c, 'c'])  # 入堆完成

        ans = []  # 用列表逐字符收集，最后再 join
        while len(h) > 0:  # 堆非空就还有字母可用
            cur = heappop(h)  # 取出剩余次数最多的字母（次数为负，最小即最多）
            if len(ans) >= 2 and ans[-1] == cur[1] and ans[-2] == cur[1]:  # 末尾已连续两个相同字母，不能再拼它
                if len(h) == 0:  # 没有别的字母可以打断
                    break  # 已达最长，结束构造
                nxt = heappop(h)  # 取出第二多的字母作为打断字符
                ans.append(nxt[1])  # 拼上替代字母
                if -nxt[0] > 1:  # 用负值还原真实剩余次数，判断是否还有余量
                    nxt[0] += 1  # 负计数加一，等价于真实次数减一
                    heappush(h, nxt)  # 还有剩余则放回堆中
                heappush(h, cur)  # 原字母未使用，原样放回
            else:  # 末尾不是两个相同字母，可以安全拼接
                ans.append(cur[1])  # 拼上当前字母
                if -cur[0] > 1:  # 还原真实剩余次数并判断是否还有
                    cur[0] += 1  # 负计数加一即消耗一次
                    heappush(h, cur)  # 仍有剩余则放回继续参与选择

        return ''.join(ans)  # 把字符列表拼成最终字符串
