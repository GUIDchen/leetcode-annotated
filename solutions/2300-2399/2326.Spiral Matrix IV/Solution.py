# 题目：2326. 螺旋矩阵 IV（Spiral Matrix IV）
# 思路：从左上角出发，按右→下→左→上的固定顺序螺旋前进，把链表节点值依次填入 m×n 矩阵；
#       方向走不通就顺时针换向，链表用完立即停止；时间复杂度：O(m×n)，空间复杂度：O(m×n)（答案矩阵）。
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:  # LeetCode 约定的题解类
    def spiralMatrix(self, m: int, n: int, head: Optional[ListNode]) -> List[List[int]]:  # m 行 n 列的目标矩阵；head 是提供填数序列的链表头
        ans = [[-1] * n for _ in range(m)]  # 答案矩阵初始化为 -1，-1 同时充当“该格尚未填数”的标记
        i = j = k = 0  # (i, j) 是当前格子坐标；k 是方向下标，0 右、1 下、2 左、3 上
        dirs = (0, 1, 0, -1, 0)  # 方向增量元组，末尾多一个 0，便于一次取出 dirs[k] 与 dirs[k+1]
        while 1:  # 外层循环：每轮把一个链表节点值放进一个格子
            ans[i][j] = head.val  # 把当前链表节点的值写入当前格子
            head = head.next  # 链表指针后移，准备下一个待填的数字
            if head is None:  # 链表已经走完
                break  # 没有更多数字可填，结束外层循环
            while 1:  # 内层循环：沿当前方向试探下一个可填的相邻格子
                x, y = i + dirs[k], j + dirs[k + 1]  # 当前方向走一步后的候选坐标
                if 0 <= x < m and 0 <= y < n and ans[x][y] == -1:  # 行列都不越界，且该格仍是未填的 -1，才允许走
                    i, j = x, y  # 候选格合法，更新当前坐标
                    break  # 已站在新格子上，跳出内层循环
                k = (k + 1) % 4  # 当前方向被挡住，顺时针旋转到下一个方向再试
        return ans  # 返回填好的螺旋矩阵，未用到的格子保持 -1
