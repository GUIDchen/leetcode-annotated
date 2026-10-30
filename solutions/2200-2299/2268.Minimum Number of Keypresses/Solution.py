# 题目：2268. 最少按键次数（Minimum Number of Keypresses）
# 思路：用 Counter 统计字符频次并降序排列，前 9 个高频字母按 1 次键、接下来 9 个按 2 次键、其余按 3 次键，按频次加权累加。
# 时间复杂度：O(n)，统计频次 O(n)、排序最多 26 项；空间复杂度：O(1)，字母种类不超过 26。
class Solution:  # LeetCode 约定的题解类
    def minimumKeypresses(self, s: str) -> int:  # s：输入字符串；返回把字符映射到键盘所需的最少按键次数
        cnt = Counter(s)  # 统计每个字符出现的次数
        ans, k = 0, 1  # ans：累计按键总数；k：当前档位每按一次代表几次击键
        for i, x in enumerate(sorted(cnt.values(), reverse=True), 1):  # 按频次降序列举，i 从 1 开始表示第几个高频字母
            ans += k * x  # 高频字母优先放在按键次数较少的键位上
            if i % 9 == 0:  # 每 9 个字母正好用满一轮 9 个键位
                k += 1  # 后续字母需要多按一次键
        return ans  # 返回最少按键总数
