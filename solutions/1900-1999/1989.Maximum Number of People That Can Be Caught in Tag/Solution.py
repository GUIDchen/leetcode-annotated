# 题目：1989. 捉迷藏中可捕获的最大人数（Maximum Number of People That Can Be Caught in Tag）
# 思路：贪心双指针。i 扫描抓人者（team[i]=1），j 扫描尚未用掉的可抓者（team[j]=0）；j 只增不减，遇到被抓人者占用或距离超限就跳过，配对成功后 j 再前进一位。
# 时间复杂度：O(n)，i 与 j 各自单调右移；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def catchMaximumAmountofPeople(self, team: List[int], dist: int) -> int:  # team：0 表示可被抓的人、1 表示抓人者；dist：可捕获的最大距离
        ans = j = 0  # ans 记录已捕获人数；j 是下一个候选可抓者下标，二者都从 0 开始
        n = len(team)  # 人数，先取出来避免循环中反复求长度
        for i, x in enumerate(team):  # 同时取得下标 i 与人 i 的身份 x
            if x:  # 只有 x 为 1（抓人者）时才需要配对
                while j < n and (team[j] or i - j > dist):  # 跳过本身就是抓人者的位置，以及距离超过 dist 的候选
                    j += 1  # j 单调右移：被跳过的 0 对更靠右的抓人者只会更远
                if j < n and abs(i - j) <= dist:  # 找到距离不超过 dist 的可抓者（abs 兼容 j 落在 i 左右两侧）
                    ans += 1  # 成功捕获一人
                    j += 1  # 这个 0 已被使用，j 前进，保证每人最多被抓一次
        return ans  # 返回最大可捕获人数
