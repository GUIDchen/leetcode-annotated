# 题目：2165. 重排数字的最小值（Smallest Value of the Rearranged Number）
# 思路：统计 0-9 各位出现次数；负数时数字降序拼成绝对值最大的数再取负，正数时最小非零数字打头、其余升序拼接。
# 时间复杂度：O(log num)，只看数字位数；空间复杂度：O(1)，固定 10 个桶。
class Solution:  # LeetCode 约定的题解类
    def smallestNumber(self, num: int) -> int:  # num：输入整数；返回重排后能得到的最小值
        neg = num < 0  # 记录正负，最后用它决定是否取负
        num = abs(num)  # 统一转成非负数，后续只关心各位数字
        cnt = [0] * 10  # cnt[d] 统计数字 d 出现的次数
        while num:  # 逐位拆解直到 num 归零
            cnt[num % 10] += 1  # 最低位对应数字的计数加一
            num //= 10  # 整除 10 去掉最低位
        ans = 0  # ans 用来累积拼接结果
        if neg:  # 负数：绝对值越大数值越小，所以按降序拼接
            for i in reversed(range(10)):  # 9 到 0 逆序遍历，保证高位放更大的数字
                for _ in range(cnt[i]):  # 数字 i 有几个副本就拼几次
                    ans *= 10  # 左移一位腾出个位
                    ans += i  # 把数字 i 加到个位
            return -ans  # 取负得到负数情形的最小值
        if cnt[0]:  # 原数含 0 时必须先放一个非零数字在最高位，否则会出现前导 0
            for i in range(1, 10):  # 从 1 开始找最小的非零数字
                if cnt[i]:  # 找到可用的最小非零数字
                    ans = i  # 把它定为最高位
                    cnt[i] -= 1  # 计数减一，防止下面重复使用
                    break  # 首位已确定，跳出查找
        for i in range(10):  # 剩下的数字从小到大拼接
            for _ in range(cnt[i]):  # 每个数字的所有副本依次追加
                ans *= 10  # 左移一位腾出个位
                ans += i  # 把数字 i 放到个位
        return ans  # 返回正数情形下的最小值
