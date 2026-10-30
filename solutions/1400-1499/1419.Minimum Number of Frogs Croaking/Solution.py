# 题目：1419. 数青蛙（Minimum Number of Frogs Croaking）
# 核心思路：把每个字母映射成 "croak" 中的阶段下标，逐个检查前一阶段是否还有青蛙可推进，并统计最大并发数。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)，只用长度为 5 的计数数组与 5 个键的映射。
class Solution:  # LeetCode 约定的题解类
    def minNumberOfFrogs(self, croakOfFrogs: str) -> int:  # croakOfFrogs 只含 c、r、o、a、k 这五种字符
        if len(croakOfFrogs) % 5 != 0:  # 一只青蛙叫出 5 个字母，长度必须是 5 的倍数
            return -1  # 长度不合法，直接无解
        idx = {c: i for i, c in enumerate('croak')}  # 建映射：字母 → 阶段下标 0..4
        cnt = [0] * 5  # cnt[i]：当前停在阶段 i 的青蛙数量
        ans = x = 0  # ans 记录最大并发；x 记录当前正在叫的青蛙数
        for i in map(idx.get, croakOfFrogs):  # 把字符串每个字母直接映射成阶段下标后遍历
            cnt[i] += 1  # 阶段 i 的青蛙数加一
            if i == 0:  # i == 0 表示字母是 c：一只新青蛙开始叫
                x += 1  # 正在叫的青蛙数加一
                ans = max(ans, x)  # 更新同时鸣叫的最大青蛙数
            else:  # 其余阶段必须由上一阶段的青蛙推进而来
                if cnt[i - 1] == 0:  # 上一阶段没有可推进的青蛙，说明顺序非法
                    return -1  # 判定此串无效
                cnt[i - 1] -= 1  # 消耗掉一只上一阶段的青蛙
                if i == 4:  # i == 4 表示字母是 k：这一轮叫完了
                    x -= 1  # 该青蛙空闲，正在叫的数量减一
        return -1 if x else ans  # 还有青蛙没叫完则有残缺，否则返回最大并发数
