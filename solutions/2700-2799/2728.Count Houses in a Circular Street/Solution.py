# 题目：2728. 计算一个环形街道上的房屋数量（Count Houses in a Circular Street）
# 思路：先把向左的 k 个房间的门都打开作为标记，再一路向左走，遇到仍然关着的门就说明绕完一圈。
# 时间复杂度：O(k + n)，n 为房屋数量；空间复杂度：O(1)。
# Definition for a street.
# class Street:
#     def openDoor(self):
#         pass
#     def closeDoor(self):
#         pass
#     def isDoorOpen(self):
#         pass
#     def moveRight(self):
#         pass
#     def moveLeft(self):
#         pass
class Solution:  # LeetCode 约定的题解类
    def houseCount(self, street: Optional["Street"], k: int) -> int:  # k 为房屋数量上限；返回环形街道上的房屋总数
        for _ in range(k):  # 先把左侧 k 个房间的门都打开，形成一段连续的标记区间
            street.openDoor()  # 打开当前房间的门（已经开着则无副作用）
            street.moveLeft()  # 向左移动一格
        ans = 0  # 计数器：统计到的房屋数量
        while street.isDoorOpen():  # 一直向左走，遇到没开的门就说明绕完了一圈
            street.closeDoor()  # 关掉这扇门，防止绕回来时重复计数
            street.moveLeft()  # 继续向左移动
            ans += 1  # 房屋数量加一
        return ans  # 返回房屋总数
