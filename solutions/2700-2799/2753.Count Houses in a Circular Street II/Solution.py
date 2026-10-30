# 题目：2753. 计算一个环形街道上的房屋数量 II（Count Houses in a Circular Street II）
# 思路：先向右走到任意一扇开着的门前作为起点，再沿环最多走 k 步，每遇到开着的门就关掉并记下步数，最大步数即房屋总数。
# 时间复杂度：O(n + k)，n 是走到第一扇开门房子的步数；空间复杂度：O(1)，只用了常数个变量。
# 下面是题目给出的 Street 接口说明（实现由判题器提供），本题只能靠它来探索街道。
# Definition for a street.
# class Street:
#     def closeDoor(self):
#         pass
#     def isDoorOpen(self):
#         pass
#     def moveRight(self):
#         pass
class Solution:  # LeetCode 约定的题解类
    def houseCount(self, street: Optional["Street"], k: int) -> int:  # street 是环形街道对象，k 是允许向右移动的最大步数（不小于房屋数）
        while not street.isDoorOpen():  # 先挪到一扇开着的门前，给后面的计数一个确定的起点
            street.moveRight()  # 当前门关着，继续向右走一步
        for i in range(1, k + 1):  # 从起点出发最多再走 k 步，足够绕环整整一圈
            street.moveRight()  # 向右走一扇门
            if street.isDoorOpen():  # 门还开着，说明这是从起点算起第 i 栋还没数过的房子
                ans = i  # 记录这栋房子的距离；题目保证 k 步之内一定会再次遇到开着的门
                street.closeDoor()  # 关掉门做标记，避免绕环时重复计数
        return ans  # 最远的开门距离就是房屋总数
