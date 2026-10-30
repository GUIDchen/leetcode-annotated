# 题目：3516. 找到最近的人（Find Closest Person）
# 思路：分别算出两人到位置 z 的距离，比较大小决定返回值，相等则返回 0。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def findClosest(self, x: int, y: int, z: int) -> int:  # x、y：两人的位置；z：参照位置；返回最近的人的编号
        a = abs(x - z)  # a：第一个人到 z 的距离
        b = abs(y - z)  # b：第二个人到 z 的距离
        return 0 if a == b else (1 if a < b else 2)  # 相等返回 0；a 更近返回 1，b 更近返回 2
