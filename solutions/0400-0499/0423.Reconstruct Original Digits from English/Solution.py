# 题目：423. 从英文中重建数字（Reconstruct Original Digits from English）
# 思路：先统计字母频次，用各数字英文单词的独有字母直接定出 0/2/4/6/8，再扣掉这些数字用掉的字母，依次推出 3/5/7 与 1/9。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)，只用了长度固定的计数数组。
class Solution:  # LeetCode 题解类
    def originalDigits(self, s: str) -> str:  # s：打乱顺序的英文单词拼接串；返回升序排列的原始数字串
        counter = Counter(s)  # 统计 s 中每个字符出现的次数（Counter 由判题环境提供，无需 import）
        cnt = [0] * 10  # cnt[d] 表示数字 d 在原数字序列中出现的次数

        cnt[0] = counter['z']  # zero 独有字母 z，所以 z 的个数就是 0 的个数
        cnt[2] = counter['w']  # two 独有字母 w，w 的个数就是 2 的个数
        cnt[4] = counter['u']  # four 独有字母 u，u 的个数就是 4 的个数
        cnt[6] = counter['x']  # six 独有字母 x，x 的个数就是 6 的个数
        cnt[8] = counter['g']  # eight 独有字母 g，g 的个数就是 8 的个数

        cnt[3] = counter['h'] - cnt[8]  # three 的 h 同时被 eight 占用，减掉 8 的个数才是 3 的个数
        cnt[5] = counter['f'] - cnt[4]  # five 的 f 同时被 four 占用，减掉 4 的个数才是 5 的个数
        cnt[7] = counter['s'] - cnt[6]  # seven 的 s 同时被 six 占用，减掉 6 的个数才是 7 的个数

        cnt[1] = counter['o'] - cnt[0] - cnt[2] - cnt[4]  # one 的 o 同时被 zero/two/four 占用，逐个扣掉已求出的 0、2、4
        cnt[9] = counter['i'] - cnt[5] - cnt[6] - cnt[8]  # nine 的 i 同时被 five/six/eight 占用，逐个扣掉已求出的 5、6、8

        return ''.join(cnt[i] * str(i) for i in range(10))  # 按 0 到 9 的顺序，每个数字重复 cnt[i] 次后拼成答案字符串
