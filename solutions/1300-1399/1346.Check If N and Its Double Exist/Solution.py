# 题目：1346. 检查整数及其两倍数是否存在（Check If N and Its Double Exist）
# 思路：顺序扫描并用集合记录已经见过的数；对当前 x，检查 2x 是否在集合中，以及 x 为偶数时 x//2 是否在集合中，从而保证两个下标不同。
# 时间复杂度：O(n)，每个元素两次集合查询；空间复杂度：O(n)，集合最多存 n 个数。
class Solution:  # LeetCode 约定的题解类
    def checkIfExist(self, arr: List[int]) -> bool:  # arr 是输入数组，判断是否存在 i != j 使 arr[i] == 2 * arr[j]
        s = set()  # s 保存已经遍历过的数
        for x in arr:  # 按顺序处理每个元素 x
            if x * 2 in s or (x % 2 == 0 and x // 2 in s):  # 先查已见过的数里有没有 2x 或 x/2；用 x % 2 == 0 避免 x/2 取整造成误判
                return True  # 命中即返回 True
            s.add(x)  # 把 x 加入集合，供后续元素查询，保证两个下标不同
        return False  # 遍历结束仍未命中，返回 False
